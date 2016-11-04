function updateHardware(input_model) {
    var hardwareLabel = document.getElementById("model");
    var screenshot_1 = document.getElementById("shot1");
    var screenshot_2 = document.getElementById("shot2");
    var screenshot_3 = document.getElementById("shot3");
    console.log(input_model);
    switch (input_model) {
        case "0":
            screenshot_1.setAttribute("src", "images/screenshots/diorite/diorite_1.png");
            screenshot_2.setAttribute("src", "images/screenshots/diorite/diorite_2.png");
            screenshot_3.setAttribute("src", "images/screenshots/diorite/diorite_3.png");
            screenshot_1.setAttribute("class", "screenshot");
            screenshot_2.setAttribute("class", "screenshot");
            screenshot_3.setAttribute("class", "screenshot");
            hardwareLabel.textContent = "Diorite";
            //Do diorite stuff here
            break;
        case "1":
            screenshot_1.setAttribute("src", "images/screenshots/basalt/basalt_1.png");
            screenshot_2.setAttribute("src", "images/screenshots/basalt/basalt_2.png");
            screenshot_3.setAttribute("src", "images/screenshots/basalt/basalt_3.png");
            screenshot_1.setAttribute("class", "screenshot");
            screenshot_2.setAttribute("class", "screenshot");
            screenshot_3.setAttribute("class", "screenshot");
            hardwareLabel.textContent = "Basalt";
            //Do basalt stuff here
            break;
        case "2":
            screenshot_1.setAttribute("src", "images/screenshots/chalk/chalk_1.png");
            screenshot_2.setAttribute("src", "images/screenshots/chalk/chalk_2.png");
            screenshot_3.setAttribute("src", "images/screenshots/chalk/chalk_3.png");
            screenshot_1.setAttribute("class", "screenshot round");
            screenshot_2.setAttribute("class", "screenshot round");
            screenshot_3.setAttribute("class", "screenshot round");
            hardwareLabel.textContent = "Chalk";
            //Do chalk stuff here
            break;
        case "3":
            screenshot_1.setAttribute("src", "images/screenshots/emery/emery_1.png");
            screenshot_2.setAttribute("src", "images/screenshots/emery/emery_2.png");
            screenshot_3.setAttribute("src", "images/screenshots/emery/emery_3.png");
            screenshot_1.setAttribute("class", "screenshot");
            screenshot_2.setAttribute("class", "screenshot");
            screenshot_3.setAttribute("class", "screenshot");
            hardwareLabel.textContent = "Emery";
            //Do emery stuff here
            break;
        default:
            //Yell
            console.log("Something's wrong in script.js");
    }
    if (typeof (Storage) !== "undefined") {
        localStorage.setItem("hardware", input_model);
    }
}
window.onload = function () {
    //Look in localstorage for the hardwareLabel, if it exists set it.
    if (typeof (Storage) !== "undefined") {
        var saved_value = localStorage.getItem("hardware");
        if (saved_value !== null) {
            document.getElementById("hardwareSlider").value = saved_value;
            updateHardware(saved_value);
        }
    }
}