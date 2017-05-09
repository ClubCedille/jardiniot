var http = require("http");
var dataConn = require("./sqlite_connector.js");
const mqtt = require("./mqtt_connector.js")(dataConn);

//This should be loaded from a conf. file.
const PORT = 8080;

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


//Defining the regexes that corresponds to the handling functions
var handles = [
  {regex: /^\/buckets$/i, func: listBuckets},
  {regex: /^\/bucket\/[0-9]+$/i, func: bucketInfo},
  {regex: /^\/bucket\/[0-9]+\/sensor\/[0-9]+$/i, func: getSensorValue}
]


//Function that handles and dispatches HTTP requests
function handleRequest(request, response){

  if(request.method == "POST" || request.method == "GET")
  {
    var postData = "";
    //Receive the data first, then handle. (LET THEM FINISH THEIR SENTENCE!)
    var postData = "";
    request.on("data", function(dataChunk) {
        postData += dataChunk;
    });

    //Let's dispatch
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

      //If no handler was called, close the connection and notify the client.
      if (!handled) {response.end(JSON.stringify({error: "Invalid endpoint."}))}
    });

  }
  else
  {
    //If method isn't POST or GET
    response.end(JSON.stringify({error: "HTTP method not supported."}))
  }

}

//We're good to go I guess...
var server = http.createServer(handleRequest);
server.listen(PORT, function(){
  console.log("Api started on port " + PORT);
});
