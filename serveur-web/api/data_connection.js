module.exports = {
  getBucketList: function(){
    //This is a stub
    var bucketArray = [
      "bucket1",
      "bucket2",
      "bucket3"
    ];

    return bucketArray;
  },

  getSensorsList: function(bucketId){
    //This is a stub
    var sensorObj = {};
    sensorObj.water = 3;
    sensorObj.light = 4;
    sensorObj.heat  = 5;
    return sensorObj;
  }
}
