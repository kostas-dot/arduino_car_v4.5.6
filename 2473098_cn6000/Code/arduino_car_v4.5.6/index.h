const char * HTML_CONTENT PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <title>Arduino Control Car via Web</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style type="text/css">
        .chat-container {
            border-style: solid;
            border-color: black;
            background: linear-gradient(135deg, SpringGreen 10%, LightSeaGreen 30%, SteelBlue 50%, SlateBlue 70%, RebeccaPurple 90%);
            display: block;
            grid-template-columns: 1fr;
            width: 100%;
            text-align: center;
            margin-left: auto;
            margin-right: auto;
            margin: 0 auto;
            padding: 10px;
        }

        .chat-messages {
            text-align: center;
            display: block;
            margin-left: auto;
            margin-right: auto;
            height: 250px;
            overflow-y: auto;
            padding: 5px;
            width: 100%;
            margin-bottom: 5px;
            grid-template-columns: 1fr;
        }

        .message-received {
            text-align: left;
            display: block;
            margin-left: auto;
            margin-right: auto;
            margin-top: 1%;
            margin-bottom: 1%;
            /*border-radius: 25px;*/
            background-color: white;
            width: 90%;
            padding: 10px 10px;
            grid-template-columns: 1fr;
        }

        body {
            max-width: 100%;
            height: auto;
            position: -webkit-sticky;
            text-align: center;
            font-size: 24px;
            background-color: FloralWhite;
        }

        button {
            text-align: center;
            font-size: 24px;
            padding: 15px 5px;
            border-radius: 60px;
            width: 40%;
            height: auto;
            position: relative;
            margin-left: auto;
            margin-right: auto;
        }

        #container {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            margin-block-start: auto;
            margin-block-end: auto;
            margin-right: auto;
            margin-left: auto;
        }

        #container2 {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr 1fr 1fr;
            margin-block-start: auto;
            margin-block-end: auto;
            margin-right: auto;
            margin-left: auto;
        }

        #container3 {
            display: grid;
            grid-template-columns: repeat(10, 1fr);
            border: 2px solid #333;
            background-color: black;
            gap: 1px;
            width: 90vw;
            max-width: 500px;
            height: auto;
            margin-left: auto;
            margin-right: auto;
            margin: 20px auto;
            aspect-ratio: 1 / 1;
        }

        .b_map {
            background-color: white;
            border: 2px solid black;
            width: 100%;
            aspect-ratio: 1 / 1;
            box-sizing: border-box;
            text-align: center;
        }

        .b_map:hover {
            background-color: #b4c439;
            color: rgb(221, 223, 164);
        }

        .b_mapL:active {
            background-color: #ebbc20;
            box-shadow: 0 5px #ecd71b;
        }

        div[class^='button'] {
            margin: auto;
            margin-block-start: 10px;
            margin-block-end: 10px;
            width: auto;
        }

        .button_STL {
            background-color: #058ec4;
            border: none;
            color: white;
            padding: 20px 30px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 24px;
            cursor: pointer;
            outline: auto;
            border-radius: 300px;
            box-shadow: 0 9px #095cc9;
            width: auto;
            background-size: contain;
        }

        .button_STL:hover {
            background-color: #5239c4;
            color: rgb(29, 201, 207);
        }

        .button_STL:active {
            background-color: #89bdd4;
            box-shadow: 0 5px #8aa8b4;
        }

        .button_SERVO {
            background-color: #c40505;
            border-style: dashed;
            border: auto;
            border-color: rgb(35, 11, 11);
            color: black;
            padding: 10px 20px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 20px;
            cursor: pointer;
            outline: burlywood;
            border-radius: 300px;
            box-shadow: 0 9px #db9f08;
            width: auto;
            background-size: contain;
        }

        .button_SERVO:hover {
            background-color: #980707;
            color: rgb(255, 177, 31);
        }

        .button_SERVO:active {
            background-color: #ec2f04;
            box-shadow: 0 5px #e0d512;
        }

        .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
        }

        /* Hide default HTML checkbox */
        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        /* The slider */
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .4s;
            transition: .4s;
        }

        .slider:before {
            position: absolute;
            content: '';
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
        }

        input:checked+.slider {
            background-color: #2196F3;
        }

        input:focus+.slider {
            box-shadow: 0 0 1px #2196F3;
        }

        input:checked+.slider:before {
            -webkit-transform: translateX(26px);
            -ms-transform: translateX(26px);
            transform: translateX(26px);
        }

        /* Rounded sliders */
        .slider.round {
            border-radius: 34px;
        }

        .slider.round:before {
            border-radius: 50%;
        }

        .switch1 {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;

        }

        .switch1 input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        .slider1 {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .4s;
            transition: .4s;
        }

        .slider1:before {
            position: absolute;
            content: '';
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
        }

        input:checked+.slider1 {
            background-color: #21f32f;
        }

        input:focus+.slider1 {
            box-shadow: 0 0 1px #21f32f;
        }

        input:checked+.slider1:before {
            -webkit-transform: translateX(26px);
            -ms-transform: translateX(26px);
            transform: translateX(26px);
        }

        .slider1.round {
            border-radius: 34px;
        }

        .slider1.round:before {
            border-radius: 50%;
        }

        .switch3 {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;

        }

        .switch3 input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        .slider3 {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            -webkit-transition: .4s;
            transition: .4s;
        }

        .slider3:before {
            position: absolute;
            content: '';
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
        }

        input:checked+.slider3 {
            background-color: #fffb00;
        }

        input:focus+.slider3 {
            box-shadow: 0 0 1px #fffb00;
        }

        input:checked+.slider3:before {
            -webkit-transform: translateX(26px);
            -ms-transform: translateX(26px);
            transform: translateX(26px);
        }

        /* Rounded sliders */
        .slider3.round {
            border-radius: 34px;
        }

        .slider3.round:before {
            border-radius: 50%;
        }

        body:has(input[id="slider1"]:checked) .button_STL {
            background-color: #38c405;
            border: none;
            color: white;
            padding: 20px 30px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 24px;
            cursor: pointer;
            outline: auto;
            border-radius: 300px;
            box-shadow: 0 9px #3dac33;
            width: auto;
            background-size: contain;
            transition: all .2s;
        }

        body:has(input[id="slider1"]:checked) .button_STL:hover {
            background-color: #085108;
            color: rgb(12, 238, 103);
        }

        body:has(input[id="slider1"]:checked) .button_STL:active {
            background-color: #89d48f;
            box-shadow: 0 5px #8ab497;
        }

        .switch_text_a {
            font-size: 20px;
            color: red;
        }

        body:has(input[id="slider1"]:checked) .switch_text_a {
            font-size: 20px;
            color: #260ff0;
            transition: all .2s;
        }

        body:has(input[id="slider2"]:checked) .button_STL {
            background-color: #5a5a5a;
            border: none;
            color: white;
            padding: 20px 30px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 24px;
            cursor: pointer;
            outline: grey;
            border-radius: 300px;
            box-shadow: 0 9px #383a3e;
            width: auto;
            background-size: contain;
            transition: all .2s;
        }

        body:has(input[id="slider2"]:checked) .button_STL:hover {
            background-color: #4d4d4d;
            color: rgb(158, 158, 158);
        }

        body:has(input[id="slider2"]:checked) .button_STL:active {
            background-color: #efefef;
            box-shadow: 0 5px #eeeeee;
        }

        body:has(input[id="slider2"]:checked) .button_SERVO {
            background-color: #5a5a5a;
            border-style: dashed;
            border: auto;
            border-color: grey;
            color: black;
            padding: 10px 20px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 20px;
            cursor: pointer;
            outline: ghostwhite;
            border-radius: 300px;
            box-shadow: 0 9px #383a3e;
            width: auto;
            background-size: contain;
        }

        body:has(input[id="slider2"]:checked) .button_SERVO:hover {
            background-color: #4d4d4d;
            color: rgb(158, 158, 158);
        }

        body:has(input[id="slider2"]:checked) .button_SERVO:active {
            background-color: #efefef;
            box-shadow: 0 5px #eeeeee;
        }

        .switch_text_b {
            font-size: 20px;
            color: red;
        }

        body:has(input[id="slider2"]:checked) .switch_text_b {
            font-size: 20px;
            color: #260ff0;
            transition: all .2s;
        }

        body:has(input[id="slider2"]:checked) .switch_text_a {
            font-size: 20px;
            color: #3c3c3c;
            transition: all .2s;
        }

        body:has(input[id="slider2"]:checked) .switch1 {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;

        }

        body:has(input[id="slider2"]:checked) .switch1 input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        body:has(input[id="slider2"]:checked) .slider1 {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #4d4d4d;
            -webkit-transition: .4s;
            transition: .4s;
        }

        body:has(input[id="slider2"]:checked) .slider1:before {
            position: absolute;
            content: '';
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: rgb(95, 95, 95);
            -webkit-transition: .4s;
            transition: .4s;
        }

        body:has(input[id="slider2"]:checked) input:checked+.slider1 {
            background-color: #4d4d4d;
        }

        body:has(input[id="slider2"]:checked) input:focus+.slider1 {
            box-shadow: 0 0 1px #4d4e4d;
        }

        body:has(input[id="slider2"]:checked) input:checked+.slider1:before {
            -webkit-transform: translateX(26px);
            -ms-transform: translateX(26px);
            transform: translateX(26px);
        }

        body:has(input[id="slider2"]:checked) .slider1.round {
            border-radius: 34px;
        }

        body:has(input[id="slider2"]:checked) .slider1.round:before {
            border-radius: 50%;
        }

        .switch_text_c {
            font-size: 20px;
            color: rgb(0, 0, 0);
        }

        body:has(input[id="slider3"]:checked) .switch_text_c {
            font-size: 20px;
            color: #fffb00;
            transition: all .2s;
        }

        .slide4container {
            margin: auto;
            margin-block-start: 10px;
            margin-block-end: 10px;
            width: auto;
        }

        .slider4 {
            -webkit-appearance: none;
            width: 80%;
            height: 15px;
            border-radius: 5px;
            background: #ead77c;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }

        .slider4::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #15cd18;
            cursor: pointer;
        }

        .slider4::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #15cd18;
            cursor: pointer;
        }
    </style>
    <script>
        var CMD_STOP = 0;
        var CMD_FORWARD = 1;
        var CMD_BACKWARDS = 2;
        var CMD_LEFT = 3;
        var CMD_RIGHT = 4;
        var CMD_ASSIST = 5;
        var CMD_NO_ASSIST = 6;
        var CMD_AUTO_ON = 7;
        var CMD_AUTO_OFF = 8;
        var CMD_LIGHTS_ON = 9;
        var CMD_LIGHTS_OFF = 10;
        var CMD_SERVO_MAX_LEFT = 11;
        var CMD_SERVO_LEFT = 12;
        var CMD_SERVO_CENTER = 13;
        var CMD_SERVO_RIGHT = 14;
        var CMD_SERVO_MAX_RIGHT = 15;
        var CMD_SPEED_0 = 16;
        var CMD_SPEED_1 = 17;
        var CMD_SPEED_2 = 18;
        var CMD_SPEED_3 = 19;
        var CMD_SPEED_4 = 20;
        var CMD_SPEED_5 = 21;
        var ws = null;
        var wsm_max_len = 4096;
        var prev_box_id = "";

        function init() {
            var container = document.querySelector("#container");
            var container2 = document.querySelector("#container2");
            var container3 = document.querySelector("#container3");
            container.addEventListener("touchstart", mouse_down);
            container.addEventListener("touchend", mouse_up);
            container.addEventListener("touchcancel", mouse_up);
            container.addEventListener("mousedown", mouse_down);
            container.addEventListener("mouseup", mouse_up);
            container.addEventListener("mouseout", mouse_up);
            container2.addEventListener("touchstart", mouse_down);
            container2.addEventListener("touchend", mouse_up);
            container2.addEventListener("touchcancel", mouse_up);
            container2.addEventListener("mousedown", mouse_down);
            container2.addEventListener("mouseup", mouse_up);
            container2.addEventListener("mouseout", mouse_up);
            container3.addEventListener("touchstart", mouse_down);
            container3.addEventListener("mousedown", mouse_down);
            const slider1 = document.getElementById("slider1");
            slider1.addEventListener("change", slider_1);
            const slider2 = document.getElementById("slider2");
            slider2.addEventListener("change", slider_2);
            const slider3 = document.getElementById("slider3");
            slider3.addEventListener("change", slider_3);
            const slider4 = document.getElementById("myRange");
            slider4.addEventListener("input", update_speed_slider);
            const gridSize = 10;
            for (let row = 1; row < gridSize + 1; row++) {
                for (let col = 1; col < gridSize + 1; col++) {
                    const box = document.createElement('div');
                    box.className = 'b_map';
                    box.id = `map-${row}-${col}`; // unique ID by row and column
                    container3.appendChild(box);
                }
            }
        }

        function slider_1() {
            if (slider1.checked) {
                document.getElementById("text1").innerHTML = "Sensor assistance Enabled.";
                send_command_slider(CMD_ASSIST);
            } else {
                document.getElementById("text1").innerHTML = "Sensor assistance Disabled.";
                send_command_slider(CMD_NO_ASSIST);
            }
            event.stopPropagation();
            event.preventDefault();
        }

        function slider_2() {
            if (slider2.checked) {
                document.getElementById("text2").innerHTML = "Auto mode ON.";
                document.body.style.backgroundColor = "GhostWhite";
                send_command_slider(CMD_AUTO_ON);
                var slider_Speed = document.getElementById("myRange");
                slider_Speed.value = 5;
                update_speed_slider();
            } else {
                document.getElementById("text2").innerHTML = "Auto mode OFF.";
                document.body.style.backgroundColor = "FloralWhite";
                send_command_slider(CMD_AUTO_OFF);
            }
            event.stopPropagation();
            event.preventDefault();
        }

        function slider_3() {
            if (slider3.checked) {
                document.getElementById("text3").innerHTML = "Lights ON.";
                send_command_slider(CMD_LIGHTS_ON);
            } else {
                document.getElementById("text3").innerHTML = "Lights OFF.";
                send_command_slider(CMD_LIGHTS_OFF);
            }
            event.stopPropagation();
            event.preventDefault();
        }

        function update_text(text) {
            var chat_messages = document.getElementById("chat-messages");
            chat_messages.innerHTML += '<div>' + text + '</div>';
            chat_messages.scrollTop = chat_messages.scrollHeight;
        }

        function update_text_servo(text) {
            var servo_angle = document.getElementById("servo_angle");
            servo_angle.innerHTML = text;
        }

        function update_text_step(text) {
            var step = document.getElementById("step_value");
            step.innerHTML = text;
        }

        function update_speed_slider() {
            var slider_Speed = document.getElementById("myRange");
            var output = document.getElementById("myRange_value");
            output.innerHTML = slider_Speed.value;
            switch (slider_Speed.value) {
                case "0":
                    send_command_slider(CMD_SPEED_0);
                    break;
                case "1":
                    send_command_slider(CMD_SPEED_1);
                    break;
                case "2":
                    send_command_slider(CMD_SPEED_2);
                    break;
                case "3":
                    send_command_slider(CMD_SPEED_3);
                    break;
                case "4":
                    send_command_slider(CMD_SPEED_4);
                    break;
                case "5":
                    send_command_slider(CMD_SPEED_5);
                    break;
                default:
                    send_command_slider(CMD_STOP);
                    break;
            }
            event.stopPropagation();
            event.preventDefault();
        }

        function ws_onmessage(e_msg) {
            e_msg = e_msg || window.event; // MessageEvent
            console.log(e_msg.data);
            if (e_msg.data.toString().slice(0, 2) == "SE") {
                update_text_servo(e_msg.data.toString().slice(2, e_msg.data.toString().wsm_max_len));
            } else if (e_msg.data.toString().startsWith("map")) {
                const box_id = e_msg.data.trim();
                const parts = box_id.split("-");
                const symbol = parts[3];
                const actual_id = `${parts[0]}-${parts[1]}-${parts[2]}`;
                const currentBox = document.getElementById(actual_id);
                if (currentBox) {
                    if (symbol === "x") {
                        const c_pos = document.getElementById("c_pos");
                        c_pos.innerHTML = box_id;
                        currentBox.style.setProperty("background-color", "red", "important");
                    } else if (symbol === "o") {
                        const c_pos = document.getElementById("c_pos");
                        c_pos.innerHTML = box_id;
                        currentBox.style.setProperty("background-color", "green", "important");
                    } else {
                        const b_map_value = document.getElementById("b_map_value");
                        const prev_box_id = b_map_value.innerHTML;
                        if (prev_box_id !== "NONE") {
                            const prevBox = document.getElementById(prev_box_id);
                            if (prevBox) {
                                prevBox.style.setProperty("background-color", "white", "important");
                            }
                        }
                        b_map_value.innerHTML = box_id;
                        if (currentBox) {
                            currentBox.style.setProperty("background-color", "blue", "important");
                        }
                        currentBox.style.setProperty("background-color", "blue", "important");
                    }
                }

            } else if (e_msg.data.trim().slice(0, 4) == "STEP") {
                update_text_step(e_msg.data.trim().slice(4, e_msg.data.trim().wsm_max_len))
            } else {
                if (e_msg.data != "") {
                    update_text('<div class="message-received">' + e_msg.data + '</div>');
                }
            }
        }

        function ws_onopen() {
            document.getElementById("ws_state").innerHTML = "OPEN";
            document.getElementById("wc_conn").innerHTML = "Disconnect";
            update_speed_slider();
        }

        function ws_onclose() {
            document.getElementById("ws_state").innerHTML = "CLOSED";
            document.getElementById("wc_conn").innerHTML = "Connect";
            console.log("socket was closed");
            update_text('<div class="message-received">////////////Socket was closed...////////////</div>');
            update_text_servo("90");
            ws.onopen = null;
            ws.onclose = null;
            ws.onmessage = null;
            ws = null;
        }

        function wc_onclick() {
            if (ws == null) {
                ws = new WebSocket("ws://" + window.location.host + ":81");
                document.getElementById("ws_state").innerHTML = "CONNECTING";
                ws.onopen = ws_onopen;
                ws.onclose = ws_onclose;
                ws.onmessage = ws_onmessage;
            }
            else
                ws.close();
        }

        function mouse_down(event) {
            if (event.target !== event.currentTarget) {
                var id = event.target.id;
                send_command(event, id);
            }
            event.stopPropagation();
            event.preventDefault();
        }

        function mouse_up(event) {
            if (event.target !== event.currentTarget) {
                var id = event.target.id;
                send_command(CMD_STOP);
            }
            event.stopPropagation();
            event.preventDefault();
        }

        function send_command(event, cmd) {
            if (ws != null)
                if (ws.readyState == 1) {
                    ws.send(cmd + "\r\n");
                }
        }

        function send_command_slider(cmd) {
            if (ws != null)
                if (ws.readyState == 1) {
                    ws.send(cmd + "\r\n");
                }
        }

        window.onload = init;
    </script>
</head>

<body>
    <h2>Arduino Car via Web</h2>
    <div id="container" style="max-width:100%; height:auto; position: -webkit-sticky;">
        <div></div>
        <div id="1" class="button_STL">&uarr;</div>
        <div></div>
        <div id="3" class="button_STL">&larr;</div>
        <div id="0" class="button_STL">&nhArr;</div>
        <div id="4" class="button_STL">&rarr;</div>
        <div></div>
        <div id="2" class="button_STL">&darr;</div>
        <div></div>
    </div>
    <div id="container2" style="max-width:100%; height:auto; position: -webkit-sticky;">
        <div id="11" class="button_SERVO">180°</div>
        <div id="12" class="button_SERVO">+1°</div>
        <div id="13" class="button_SERVO">90°</div>
        <div id="14" class="button_SERVO">-1°</div>
        <div id="15" class="button_SERVO">0°</div>
    </div>
    <div class="slide4container">
        <input type="range" class="slider4" min="0" max="5" value="3" id="myRange">
    </div>
    <p
        style="max-width:30%; padding: 10px 10px; height:auto; position: relative;  display: block; margin-left: auto; margin-right: auto; border-style:dotted; border-color: rgb(0, 255, 4); background-color: whitesmoke;">
        Speed is set at : <span id="myRange_value">3</span> Level.</p>
    <p
        style="max-width:30%; padding: 10px 10px; height:auto; position: relative;  display: block; margin-left: auto; margin-right: auto; border-style: dashed; border-color: red; background-color: whitesmoke;">
        Servo Angle is : <span id="servo_angle" style="color:rgb(246, 5, 5);">90</span><br>
    </p>
    <p
        style="max-width:30%; padding: 10px 10px; height:auto; position: relative;  display: block; margin-left: auto; margin-right: auto; border-style: double; border-color: rgb(0, 38, 255); background-color: whitesmoke;">
        WebSocket : <span id="ws_state" style="color:blue;">CLOSED</span><br>
    </p>
    <button id="wc_conn" type="button" onclick="wc_onclick();">Connect</button>
    <br>
    <br>
    <div id="container" style="grid-template-columns: 1fr 1fr 1fr; ">
        <div>
            <div><label class="switch1">
                    <input type="checkbox" id="slider1">
                    <span class="slider1 round"></span>
                </label>
            </div>
            <div>
                <p id="text1" class="switch_text_a">Sensor assistance Disabled.</p>
            </div>
        </div>
        <div>
            <div><label class="switch">
                    <input type="checkbox" id="slider2">
                    <span class="slider round"></span>
                </label>
            </div>
            <div>
                <p id="text2" class="switch_text_b">Auto mode off.</p>
            </div>
        </div>
        <div>
            <div><label class="switch">
                    <input type="checkbox" id="slider3">
                    <span class="slider3 round"></span>
                </label>
            </div>
            <div>
                <p id="text3" class="switch_text_c">Lights OFF.</p>
            </div>
        </div>
    </div>
    <div class="container" style="max-width:80%; height:auto; display: block; margin-left: auto; margin-right: auto;">
        <div class="chat-container">
            <div class="chat-messages" id="chat-messages">
            </div>
        </div>
    </div>
    <div id="container3">
    </div>
    <p
        style="max-width:30%; padding: 10px 10px; height:auto; position: relative; margin-left: auto; margin-right: auto; display: block; border-style:dotted; border-color: rgb(0, 0, 0); background-color: whitesmoke;">
        Current position on the map :<br> <span id="c_pos">NONE</span></p>
    <div style="display: flex; justify-content: center; gap: 20px;">
        <p
            style="max-width:30%; padding: 10px 10px; height:auto; position: relative;  display: block; border-style:dotted; border-color: rgb(0, 0, 0); background-color: whitesmoke;">
            Id button map pressed :<br> <span id="b_map_value">NONE</span></p>
        <p
            style="max-width:30%; padding: 10px 10px; height:auto; position: relative;  display: block; border-style:dotted; border-color: rgb(0, 0, 0); background-color: whitesmoke;">
            Average steps done :<br> <span id="step_value">0</span></p>
    </div>
</body>

</html>
)=====";
