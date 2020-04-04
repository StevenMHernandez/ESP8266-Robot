const char MAIN_page[] PROGMEM = R"=====(
<html><head>
  <meta http-equiv="content-type" content="text/html; charset=UTF-8">
  <title>Control-a-bot</title>
  <meta http-equiv="content-type" content="text/html; charset=UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">

  <style type="text/css">
    html, body {
      width: 100%;
      display: block;
      touch-action: none;
    }
    div {
      padding: 20px;
      border: 1px solid black;
      width: 80%;
    }
    div.controls {
      margin: 0 auto;
      height: 300px;
      width: 35%;
      display: inline-block;
    }
    input {
      display:block;
      width: 80%;
      margin: 0 auto;
    }
    span {
      margin: 0 auto;
      margin-bottom: 50px;
      display: block;
      border: 1px solid black;
      height: 120px;
      width: 80%;
    }
  </style>
</head>
<body>
<div>
  <input type="number" onclick="new_speed()" min="1" max="90" value="50" id="new_speed">
</div>
<div class="controls">
  <span id="left_joy_forwards" ontouchstart="left(1)" ontouchend="left(0)"></span>
  <span id="left_joy_backwards" ontouchstart="left(-1)" ontouchend="left(0)"></span>
</div>
<div class="controls">
  <span id="right_joy_forwards" ontouchstart="right(1)" ontouchend="right(0)"></span>
  <span id="right_joy_backwards" ontouchstart="right(-1)" ontouchend="right(0)"></span>
</div>

<script>
  function new_speed(evt) {
    var x = document.getElementByID("new_speed").value;
    ajax("setSpeed?speed=" + x);
  }
  
  function left(direction) {
    console.log("test");
    if (direction == 1) {
      beginTouch("left_joy_forwards");
    } else if (direction == -1) {
      beginTouch("left_joy_backwards");
    } else {
      endTouch("left_joy_forwards");
      endTouch("left_joy_backwards");
    }
    ajax("setLeft?direction=" + direction);
  }
  
  function right(direction) {
    if (direction == 1) {
      beginTouch("right_joy_forwards");
    } else if (direction == -1) {
      beginTouch("right_joy_backwards");
    } else {
      endTouch("right_joy_forwards");
      endTouch("right_joy_backwards");
    }
    ajax("setRight?direction=" + direction);
  }
  
  function beginTouch(selector) {
    document.getElementById(selector).style.backgroundColor = "#6cc";
  }
  
  function endTouch(selector) {
    document.getElementById(selector).style.backgroundColor = "#fff";
  }
  
  function ajax(location) {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", location, true);
    xhttp.send();
  }
</script>
</body>
</html>
)=====";
