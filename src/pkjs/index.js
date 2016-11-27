var sending = require("./image_sending.js");
var fetching = require("./launch_fetching.js");

Pebble.addEventListener("ready", function(e){
  console.log("JS is as ready as it'll ever be");
  //Let the watch know it's ok to send messages
  Pebble.sendAppMessage({ 'Ready' : true });
  Pebble.addEventListener("appmessage", function(e) {
    console.log("Got message: " + JSON.stringify(e.payload));
    var input = e.payload;
    if(input['qr_outbound']){
      var received_message = input['qr_outbound'];
      console.log("Going to fetch " + received_message);
      sending.fetchCode(received_message);
    }
    if(input['GetNextLaunch']){
      console.log("Fetching next launch");
      fetching.fetchNext();
    }
  });
});

//Clay Stuff

var Clay = require("pebble-clay");
var clayConfig = require("./config");
var clayEvents = require("./clay_events");
var clay = new Clay(clayConfig, clayEvents, { autoHandleEvents: false });

var countries = {
  10000: "DZA",
  10001: "AUS",
  10002: "PRK",
  10003: "GUF",
  10004: "JPN",
  10005: "KEN",
  10006: "NZL",
  10007: "CHN",
  10008: "IND",
  10009: "IRN",
  10010: "KAZ",
  10011: "RUS",
  10012: "UNK",
  10013: "KOR",
  10014: "ISR",
  10015: "USA"
};

Pebble.addEventListener('showConfiguration', function(e) {
  Pebble.openURL(clay.generateUrl());
});

Pebble.addEventListener('webviewclosed', function(e) {
  var dict = clay.getSettings(e.response);
  console.log("I got a dict with " + Object.keys(dict).length + " items in it");
  var subscribeList = [];
  var unsubscribeList = [];
  for (var key in dict) { 
    if (dict.hasOwnProperty(key)) {
      if (dict[key]) { subscribeList.push(countries[key]); }
      else { unsubscribeList.push(countries[key]); }
    }
  }
  for (var s_item in subscribeList){
    Pebble.timelineSubscribe(subscribeList[s_item]);
  }
  for (var u_item in unsubscribeList){ 
    Pebble.timelineUnsubscribe(unsubscribeList[u_item]);
  }
  
  Pebble.timelineSubscriptions(function(topics) {
    // List all the subscribed topics
    console.log('Subscribed to ' + topics.join(', '));
  }, function(errorString) {
    console.log('Error getting subscriptions: ' + errorString);
  });

});

