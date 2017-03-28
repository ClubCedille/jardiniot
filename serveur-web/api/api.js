const PORT = 8080;

var http = require("http");
var dataConn = require("./data_connection.js");

//Defining handling functions
var listBuckets = function(url, data){
  var bucketArray = dataConn.getBucketList();
  return JSON.stringify(bucketArray);
};

var listSensors = function(url, data){
  id = url.replace("/bucket/", "");
  if (isNaN(id) || id == ""){return JSON.stringify({error: "Invalid bucket number."});}

  var sensorArray = dataConn.getSensorsList(id);
  return JSON.stringify(sensorArray);
};


//Defining the regexes that corresponds to the handling functions
var handles = [
  {regex: /^\/buckets$/i, func: listBuckets},
  {regex: /^\/bucket\//i, func: listSensors}
]


//Function that handles and dispatches HTTP requests
function handleRequest(request, response){

  if(request.method == "POST" || request.method == "GET")
  {
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
          response.end(val.func(request.url, postData));
        }
      });

      //If no handler was called, close the connection and notify the client.
      if (!handled) {response.end(JSON.stringify({error: "Invalid endpoint."}))}
    });
  }

}


//We're good to go I guess...
var server = http.createServer(handleRequest);
server.listen(PORT, function(){
  console.log("Api started on port " + PORT);
});
