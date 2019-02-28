/* Copyright 2018 Roch D'Amour
 * Copyright 2017 Aubert Guillemette
 *
 * JardinIoT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * JardinIoT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JardinIoT. If not, see <http://www.gnu.org/licenses/>.
 */

var express = require("express");
var dataConn = require("./sqlite_connector.js");

const mqtt = require("./mqtt_connector.js");
mqtt.init(dataConn);

// TODO: devrait être loadé à partir d'un fichier de config.
const PORT = 8080;
const LIMIT_BLUE  = 170;
const LIMIT_WHITE = 170;
const LIMIT_RED   = 170;
const LIMIT_FAN   = 170;

var api = express();

//For debugging purposes
api.use(enableCORS);
function enableCORS(req, res, next) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
    next();
}

// Don't Repeat Yourself
function sendHTTPResponse(err,result,res){
    if(err) {
        res.status(500).send('Welp');
    } else {
        res.status(200).send(JSON.stringify(result));
    }
}

/*
 * Bucket list
 */
api.get('/buckets', function(req, res, next) {
    listBuckets(req, res);
});

/*
 * Bucket post
 */
api.post('/buckets', function(req, res, next) {
    bucketCreate(req,res);
});

/*
 * Bucket info
 */
api.get('/buckets/:bucketId', function(req, res, next) {
    bucketInfo(req, res);
});

/*
 * Sensor info
 */
api.get('/buckets/:bucketId/sensor/:sensorId', function(req, res, next) {
    getSensorValue(req, res);
});

/*
 * Sensor info
 */
api.get('/buckets/:bucketId/sensor/:sensorId/latest', function(req, res, next) {
    getLatestSensorValue(req, res);
});

/*
 * Command
 */
api.post('/command/:commandId', function(req, res, next) {
    sendCommand(req, res);
});

api.listen(PORT, function() {
    console.log('Api running on port ' + PORT );
});


//==============================Handling functions==============================

//Get bucket list
function listBuckets(req, res){
    dataConn.getBucketList(function(err, result){
        sendHTTPResponse(err,result,res);
    });
}

//Get bucket info
function bucketInfo(req, res) {
    var id = req.params.bucketId;
    if (isNaN(id) || id == "") {
        res.status(400).send(JSON.stringify({error: "Invalid bucket number."}));
        return;
    }
    dataConn.getBucketInfo(id, function(err, result){
        sendHTTPResponse(err,result,res);
    });
}

//Post bucket
function bucketCreate(req, res) {

    // Receive data from http post
    var postData = "";
    req.on('data', function(dataChunk) {
        postData += dataChunk;
        console.log('received '+dataChunk);
    });

    req.on('end', handleCommand);

    function handleCommand() {
        
        if (postData == "") {
            res.status(400).send(JSON.stringify({error: "Erreur: received post data are invalid!:"+postData}));
            return;
        }

        var datas = JSON.parse(postData);
        var name = datas.name;
        var ip = datas.ip;
        
        if (name == "") {
            res.status(400).send(JSON.stringify({error: "Invalid bucket name."}));
            return;
        }
        if (ip == "") {
            res.status(400).send(JSON.stringify({error: "Invalid bucket ip."}));
            return;
        }
        
        dataConn.createBucket(name,ip, sendHTTPResponse);
    }
}

//Get sensor value
function getSensorValue(req, res){
    var id = req.params.sensorId;
    if (isNaN(id) || id == "") {
        res.status(400).send(JSON.stringify({error: "Invalid bucket number."}));
        return;
    }

    var sensorInfo = dataConn.getSensorValue(id, function(err, result){
        sendHTTPResponse(err,result,res);
    });
}

//Get latest sensor value
function getLatestSensorValue(req, res){
    var id = req.params.sensorId;
    if (isNaN(id) || id == "") {
        res.status(400).send(JSON.stringify({error: "Invalid bucket number."}));
        return;
    }

    var sensorInfo = dataConn.getLatestSensorValue(id, function(err, result){
        sendHTTPResponse(err,result,res);
    });
}


//Post command to ESP
function sendCommand(req, res){
    var id = req.params.commandId;

    if (isNaN(id) || id == "") {
        cb(JSON.stringify({error: "Invalid bucket number."}));
        return;
    }

    //Receive the data first, then handle. (LET THEM FINISH THEIR SENTENCE!)
    var postData = "";
    req.on("data", function(dataChunk) {
        postData += dataChunk;
    });

    req.on('end', handleCommand);

    function handleCommand() {
        if (postData == "") {
            res.status(400).send(JSON.stringify({error: "Error: POST data received is invalid"}));
            return;
        }

        try
        {
            //Est-ce que mes données sont du JSON valide?
            var data = JSON.parse(postData);

            //TODO: Regarder si celui qui a envoyé les données a le droit de le faire.

            //Si on est ici, le JSON est valide. Contient-il ce qu'on veut?
            var dataIsValid =
                //Est-ce que l'objet a les bonnes propriétés?
                data.hasOwnProperty("blue") &&
                data.hasOwnProperty("white") &&
                data.hasOwnProperty("red") &&
                data.hasOwnProperty("fan") &&
                //Est-ce que ce sont des nombres?
                Number.isInteger(parseFloat(data.blue)) &&
                Number.isInteger(parseFloat(data.white)) &&
                Number.isInteger(parseFloat(data.red)) &&
                Number.isInteger(parseFloat(data.fan)) &&
                //Est-ce que ces nombres sont des valeurs valides?
                //La validité des valeurs sont définies dans Wiki:
                //voir https://github.com/ClubCedille/jardiniot/wiki/Connectivit%C3%A9-entre-ESP-et-API-(MQTT)
                data.blue >= 0 &&
                data.white >= 0 &&
                data.red >= 0 &&
                data.fan >= 0 &&
                data.blue <= LIMIT_BLUE &&
                data.white <= LIMIT_WHITE &&
                data.red <= LIMIT_RED &&
                data.fan <= LIMIT_FAN;
            //...and this is how you do condition short-circuiting.

            if (!dataIsValid) throw "Data received is invalid.";

            //Si on est ici, les données sont valides!
            //Let's treat it! (Post it check it treat it send it ♫)
            dataConn.getBucketNameById(id, function(bucketName){
                mqtt.send(bucketName, data);
            });
        }
        catch (e)
        {
            //Les données sont invalides, on envoie un msg d'erreur en console :-(
            console.warn("");
            console.warn("WARNING: In api::sendCommand()");
            console.warn("       : " + e);
            console.warn("       : Not sending the command. :(");
            console.warn("");
        }
    }
}
