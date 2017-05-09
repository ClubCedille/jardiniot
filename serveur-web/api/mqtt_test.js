var dataConn = require("./sqlite_connector.js");
const mqtt = require("./mqtt_connector.js");
mqtt.init(dataConn);

setInterval(function(){
  mqtt.send("DEADBEEF", {blue: 10, white: 10, red: 10, fan: 170});
}, 1000);
