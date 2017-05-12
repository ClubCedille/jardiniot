var http = require("http");
var dataConn = require("./sqlite_connector.js");

const mqtt = require("./mqtt_connector.js");
mqtt.init(dataConn);

//Ceci devrait être loadé à partir d'un fichier de config.
const PORT = 8080;
const LIMIT_BLUE  = 170;
const LIMIT_WHITE = 170;
const LIMIT_RED   = 170;
const LIMIT_FAN   = 170;

//==============================Handling functions==============================

//Get bucket list
var listBuckets = function(url, data, cb){
  dataConn.getBucketList(function(rst){
    cb(JSON.stringify(rst));
  });
};

//Get bucket info
var bucketInfo = function(url, data, cb){
  id = url.replace("/bucket/", "");
  if (isNaN(id) || id == "") {
    cb(JSON.stringify({error: "Invalid bucket number."}));
  }

  //Hein? On a reçu des données?
  if (data != "")
  {
    try
    {
      //Est-ce que mes données sont du JSON valide?
      var data = JSON.parse(data);

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
      console.error("Api --> bucketInfo --> Data received invalid" + e);
    }
  }

  dataConn.getBucketInfo(id, function(rst){
    cb(JSON.stringify(rst));
  });
};

//Get sensor value
var getSensorValue = function(url, data, cb){
  var urlParts = url.split("/");
  var id = urlParts[urlParts.length - 1];
  if (isNaN(id) || id == "") {
    cb(JSON.stringify({error: "Invalid sensor number."}));
  }

  var sensorInfo = dataConn.getSensorValue(id, function(rst){
    cb(JSON.stringify(rst));
  });
}
//==============================================================================


//Définition des regexes qui redirigent vers les handling functions
var handles = [
  {regex: /^\/buckets$/i, func: listBuckets},
  {regex: /^\/bucket\/[0-9]+$/i, func: bucketInfo},
  {regex: /^\/bucket\/[0-9]+\/sensor\/[0-9]+$/i, func: getSensorValue}
]


//Fonction qui dispatch les requêtes HTTP à la bonne handling function
function handleRequest(request, response){

  if(request.method == "POST" || request.method == "GET")
  {
    var postData = "";
    //Receive the data first, then handle. (LET THEM FINISH THEIR SENTENCE!)
    var postData = "";
    request.on("data", function(dataChunk) {
        postData += dataChunk;
    });

    //Dispatchons
    request.on("end", function() {
      var handled = false;

      handles.forEach(function(val, key){
        if (val.regex.test(request.url)) {
          handled = true;
          val.func(request.url, postData, function(responseData){
            response.end(responseData);
          });
        }
      });

      //Si aucune handling function n'a été appelée, on envoie une erreur.
      if (!handled) {response.end(JSON.stringify({error: "Invalid endpoint."}))}
    });

  }
  else
  {
    //Si la méthode n'est pas un POST ou un GET
    response.end(JSON.stringify({error: "HTTP method not supported."}))
  }

}

//We're good to go I guess...
var server = http.createServer(handleRequest);
server.listen(PORT, function(){
  console.log("Api started on port " + PORT);
});
