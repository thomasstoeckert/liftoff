module.exports = function(minified){
  var clayConfig = this;
  var _ = minified._;
  var $ = minified.$;
  var HTML = minified.HTML;
  
  var countries=[
    "Algeria",
    "Australia",
    "Democratic People's Republic of Korea",
    "French Guiana",
    "Japan",
    "Kenya",
    "New Zealand",
    "People's Republic of China",
    "Republic of India",
    "Republic of Iran",
    "Republic of Kazakhstan",
    "Russian Federation",
    "Sea Launch/Unknown",
    "South Korea",
    "States of Israel",
    "United States of America"
  ];
  
  
  function selectAll(){
    var boxGroup = clayConfig.getItemByMessageKey('countries');
    var trueArray = [];
    for (var i = 0; i < countries.length; i++) { trueArray[i] = true; }
    boxGroup.set(trueArray);
  }
  
  function deselectAll(){
    var boxGroup = clayConfig.getItemByMessageKey('countries');
    var falseArray = [];
    for (var i = 0; i < countries.length; i++) { falseArray[i] = false; }
    boxGroup.set(falseArray);
  }
  
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {
    var sel_a_button = clayConfig.getItemById('select_all');
    var sel_d_button = clayConfig.getItemById('deselect_all');
    sel_a_button.on('click', selectAll);
    sel_d_button.on('click', deselectAll);
  });
};