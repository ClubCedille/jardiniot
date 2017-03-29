//These are stubs, I need to implement connection to a database

module.exports = {
  getBucketList: function(){
    //This is a stub
    var bucketArray = [];

    var bucketObj = {};
    bucketObj.id = 1;
    bucketObj.name = "Sample bucket";

    bucketArray[0] = bucketObj;

    var bucketObj = {};
    bucketObj.id = 2;
    bucketObj.name = "Sample bucket 2";

    bucketArray[1] = bucketObj;

    return bucketArray;
  },

  getBucketInfo: function(bucketId){
    //This is a stub
    var bucketObj = {};
    bucketObj.name = "Sample bucket";
    bucketObj.ip = "192.168.?.?";
    bucketObj.sensorsId = {};
    bucketObj.sensorsId.water = 3;
    bucketObj.sensorsId.light = 4;
    bucketObj.sensorsId.heat  = 5;
    bucketObj.controlsId = {};
    bucketObj.controlsId.water = 6;
    bucketObj.controlsId.light = 7;
    bucketObj.controlsId.heat  = 8;
    return bucketObj;
  },

  getSensorValue: function(sensor){
    //This is a stub
    var sensorObj = {};
    sensorObj.name = "water";
    sensorObj.value = "70%";
    return sensorObj;
  }
}
