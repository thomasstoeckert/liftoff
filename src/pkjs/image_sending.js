var MAX_CHUNK_SIZE = 32000;
var TESTING = false;

//QR Stuff
var keys = require('message_keys');

function sendChunk(array, index, arrayLength) {
  var chunkSize = MAX_CHUNK_SIZE;
  if(arrayLength - index < MAX_CHUNK_SIZE) {
    chunkSize = arrayLength - index;
  }

  var dict = {
    'DataChunk' : array.slice(index, index + chunkSize),
    'ChunkSize' : chunkSize,
    'Index': index
  };

  Pebble.sendAppMessage(dict, function() {
    index += chunkSize;

    if(index < arrayLength) {
      sendChunk(array, index, arrayLength);
    } else {
      Pebble.sendAppMessage({'Complete': 0});
    }
  }, function(e) {
    console.log('Failed to send chunk with index ' + index);
  });
}

function transmitImage(array){
  var index = 0;
  var arrayLength = array.length;

  Pebble.sendAppMessage({'DataLength' : arrayLength}, function(e) {
    sendChunk(array, index, arrayLength);
  }, function(e) {
    console.log("Error initializing image transfer!");
  })
}

function processImage(responseData) {
  var byteArray = new Uint8Array(responseData);
  var array = [];
  for(var i = 0; i < byteArray.byteLength; i++) {
    array.push(byteArray[i]);
  }

  transmitImage(array);
}

function downloadImage(url) {
  var request = new XMLHttpRequest();
  request.onload = function() {
    processImage(this.response);
  }
  request.responseType = "arraybuffer";
  request.open("GET", url);
  request.send();
}

function fetchCode(code){
  var mode = code % 10;
  var launchId = Math.floor(code / 10);
  var imageUrl = "https://thomasstoeckert.pythonanywhere.com/liftoff_images/?";
  var typeArg;
  var idArg;
  if(mode == 0){
    typeArg = "type=info";
  } else if (mode == 1) {
    typeArg = "type=video";
  } else {
    typeArg = "type=error";
  }
  idArg = "id=" + launchId;
  var requestUrl = imageUrl.concat(idArg, "&", typeArg);
  if(TESTING){
    requestUrl = requestUrl.concat("&testing=true");
  }
  downloadImage(requestUrl);
}

module.exports.fetchCode = fetchCode;