var llUrl = "https://launchlibrary.net/1.2/launch/next/1?limit=1"
var keys = require('message_keys');

function fetchNext(){

	var req = new XMLHttpRequest();
	req.onreadystatechange = function() {
		if (req.readyState == 4 && req.status == 200){
			var str = req.responseText;
			//console.log(str); NEVER LOG THE ENTIRE THING - HOLY COW IS IT BIG
			var key_items = {};
			var str_dict = JSON.parse(str)['launches'][0];
			key_items.NextLaunchName = str_dict['name'];
			key_items.NextLaunchNet = str_dict['net'];
			key_items.NextLaunchLocation = str_dict['location']['name'];
			key_items.NextLaunchStatus = str_dict['status'];
			console.log(JSON.stringify(key_items));
			Pebble.sendAppMessage(str_dict, function(e){
				console.log("Success sending next launch to watch");
			}, function(e){
				console.log("Error sending next launch to watch");
			});
		}
	};
	req.open("GET", llUrl, false);
	req.send();
}

module.exports.fetchNext = fetchNext;