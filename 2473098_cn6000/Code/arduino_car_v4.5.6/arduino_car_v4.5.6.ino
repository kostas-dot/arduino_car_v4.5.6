// LIBRARIES
#include <Arduino.h>
#include "Arduino_LED_Matrix.h"
#include "index.h"
#include <Servo.h>
#include <ShiftRegister74HC595.h>
#include <string>
#include <vector>
#include <WebSocketServer.h>
#include <WiFiS3.h>
//map vector dimentions
#define ROWS 10
#define COLS 10
//for strings
using namespace std;
// Instance of the ArduinoLEDMatrix class
ArduinoLEDMatrix matrix;
// Frames of the matrix
// MAIN FRAME THAT CHANGES
// THIS IS THE ONE ARDUINO MATRIX SHOWS
byte frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
// FRAME IMAGE FOR MOVING FORWARD
byte forward_b[8][12] = {
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }
};
// FRAME IMAGE FOR MOVING BACKWARDS
byte backwards_b[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 }
};
// FRAME IMAGE FOR TURNING RIGHT
byte turn_right_b[8][12] = {
  { 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0 },
  { 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0 }
};
// FRAME IMAGE FOR TURNING LEFT
byte turn_left_b[8][12] = {
  { 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
  { 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0 },
  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0 },
  { 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0 },
  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 }
};
//MAP OF SPACE
std::vector<std::vector<int>> vec_map = {
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
};
//POSITION VALUES
int curren_p_x = 9;
int curren_p_y = 9;
//0 IS LOOKING LEFT 1 IS LOOKING RIGHT
int echo_pos = 0;
//full_vector = true when vec_map has no -1 values
bool full_vector = false;
//STRUCT CLASS FOR MAP AND PATH
struct Point {
  int x, y;
};
//DEFAULT VALUES
Point start = { 0, 0 };
Point go_pos = { 9, 9 };
//COMMANDS
#define CMD_STOP 0
#define CMD_FORWARD 1
#define CMD_BACKWARDS 2
#define CMD_LEFT 3
#define CMD_RIGHT 4
#define CMD_ASSIST 5
#define CMD_NO_ASSIST 6
#define CMD_AUTO_ON 7
#define CMD_AUTO_OFF 8
#define CMD_LIGHTS_ON 9
#define CMD_LIGHTS_OFF 10
#define CMD_SERVO_MAX_LEFT 11
#define CMD_SERVO_LEFT 12
#define CMD_SERVO_CENTER 13
#define CMD_SERVO_RIGHT 14
#define CMD_SERVO_MAX_RIGHT 15
#define CMD_SPEED_0 16
#define CMD_SPEED_1 17
#define CMD_SPEED_2 18
#define CMD_SPEED_3 19
#define CMD_SPEED_4 20
#define CMD_SPEED_5 21
int command = 0;  //general global command variable
//SERVO PIN AND ANGLE
Servo pin0;
int angle = 90;
//SHIFT REGISTER PINS FOR THE LIGHT SHOW
const int numberOfShiftRegisters = 2;  // number of shift registers attached in series
const int dataPin = 9;                 // DS data send to the shift register
const int latchPin = 8;                // STCP change data of the shift register
const int clockPin = 7;                // SHCP for time
bool lights_en = false;                // Lights on or off
double current_mil = 0;                // current time
double next_mil = 0;                   // next time change
int light_current_id = -1;             //type of light pattern
bool flash = false;                    //change lights
int servo_flash = 0;                   //servo motor lightshow
ShiftRegister74HC595<numberOfShiftRegisters> sr(dataPin, clockPin, latchPin);
//SENSOR PIN POWER AND STATUS CONNECTIONS
bool sensor_power_en = false;
//ULTRASONIC SENSOR FRONT
const int trigPinF = 12;
const int echoPinF = 13;
//ULTRASONIC SENSOR BACK
const int trigPinB = 1;
const int echoPinB = 2;
//ULTRASONIC SENSOR RIGHT
const int trigPinR = 3;
const int echoPinR = 4;
//ULTRASONIC SENSOR LEFT
const int trigPinL = A4;
const int echoPinL = A5;
//MOTOR PIN CONNECTIONS
//RIGHT SIDE
const int rightB = 6;
const int rightF = 5;
//LEFT SIDE
const int leftB = 10;
const int leftF = 11;
//SPEED VARIABLE SET TO MAX
int speed = 255;
//STEP COUNTERS VARIABLES FOR DATA COLLECTION
const int stepFR = A0;
const int stepFL = A1;
const int stepBR = A2;
const int stepBL = A3;
int countFR = 0;
int countFL = 0;
int countBR = 0;
int countBL = 0;
bool cur_fr = false;
bool prev_fr = false;
bool cur_fl = false;
bool prev_fl = false;
bool cur_br = false;
bool prev_br = false;
bool cur_bl = false;
bool prev_bl = false;
//WIFI CREDENTIALS
const char ssid[] = "ARDUINO_WIFI_V4.5.6";  // WIFI POINT NAME
const char password[] = "12345678";         // MIN CHAR LENGTH 8
using namespace net;
//WEBSOCKET SERVER
WebSocketServer webSocket(81);
//WIFI SERVER AND STATUS
WiFiServer server(80);
int status = WL_IDLE_STATUS;
//VARIABLES FOR BETTER SERIAL PRINTS
bool better_serial = false;
bool first_loop = true;
//VARIABLES FOR MOVE COMMANDS
bool en_assist = false;
bool en_auto = false;
// main function that runs before loop starts running
void setup() {
  Serial.begin(9600);
  delay(1500);
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("FIRMWARE VERSION CHECK"));
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) { Serial.println(F("PLEASE UPDATE THE FIRMWARE VERSION!")); }
  Serial.println("FIRMWARE VERSION CHECK SUCCESSFUL!");
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("MATRIX SETUP."));
  matrix.loadSequence(LEDMATRIX_ANIMATION_STARTUP);
  matrix.begin();
  matrix.play(true);
  Serial.println(F("MATRIX SETUP SUCCESSFUL!"));
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("8-BIT SHIFT REGISTER CONNECTIONS SETUP START."));
  sr.setAllHigh();
  delay(500);
  sr.setAllLow();
  Serial.println(F("8-BIT SHIFT REGISTER CONNECTIONS SETUP SUCCESSFUL!"));
  Serial.println(F("8-BIT SHIFT REGISTER LIGHTS AND ULTRASONIC SENSORS SET TO OFF."));
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("MOTOR CONNECTIONS SETUP START."));
  pinMode(rightF, OUTPUT);
  Serial.println(rightF);
  pinMode(rightB, OUTPUT);
  Serial.println(rightB);
  pinMode(leftF, OUTPUT);
  Serial.println(leftF);
  pinMode(leftB, OUTPUT);
  Serial.println(leftB);
  Serial.println(F("MOTOR CONNECTIONS SETUP SUCCESSFUL!"));
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("ULTRASONIC SENSOR CONNECTIONS SETUP START."));
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinB, OUTPUT);
  pinMode(echoPinB, INPUT);
  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  Serial.println(F("ULTRASONIC SENSOR CONNECTIONS CHECK SUCCESSFUL!"));
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("MOTOR INFRARED STEP COUNTER SETUP START."));
  for (int i = 4; i < 8; i++) {
    sr.set(i, HIGH);
  }
  pinMode(stepFR, INPUT);
  pinMode(stepFL, INPUT);
  pinMode(stepBR, INPUT);
  pinMode(stepBL, INPUT);
  Serial.println(F("MOTOR INFRARED STEP COUNTER SETUP SUCCESSFUL!"));
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("ATTACH PIN 0 TO SERVO MOTOR INPUT."));
  pin0.attach(0);
  Serial.println(F("ATTACH PIN 0 TO SERVO MOTOR SUCCESSFUL!"));
  Serial.println(F("SERVO MOTOR SET TO 90 DEGREES!"));
  pin0.write(angle);
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("IP ADDRESS CREATION."));
  WiFi.config(IPAddress(192, 48, 56, 2));
  Serial.println(F("IP ADDRESS CREATION SUCCESSFUL!"));
  Serial.print(F("CREATING ACCESS POINT NAMED: "));
  Serial.println(ssid);
  Serial.print(F("WITH PASSWORD: "));
  Serial.println(password);
  // IF WIFI ACCESS POINT ISN'T CREATED PROGRAMM WON'T CONTINUE
  status = WiFi.beginAP(ssid, password);
  if (status != WL_AP_LISTENING) {
    Serial.println(F("CREATING ACCESS POINT FAILED!"));
    // DON'T CONTINUE
    while (true)
      ;
  }
  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("SERVER INITIALIZATION."));
  server.begin();
  Serial.println(F("SERVER INITIALIZATION SUCCESSFUL!"));
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  Serial.println(F("WEBSOCKET SETUP."));
  webSocket.onConnection([](WebSocket &ws) {
    //SETS AUTOMATICALLY THE PROTOCOL TYPE
    const auto protocol = ws.getProtocol();
    if (protocol) {
      Serial.print(F("Client protocol: "));
      Serial.println(protocol);
    }
    web_me3("//////// Hello from Arduino server! ////////");
    const char *remote = ws.getRemoteIP().toString().c_str();
    std::string str = "New WebSocket Connnection from client: " + std::string(remote);
    const char *r = (const char *)str.c_str();
    web_me3(r);
    str.clear();
    ws.onMessage([](WebSocket &ws, const WebSocket::DataType dataType, const char *message, uint16_t length) {
      if (string(message).substr(0, 3) == "map") {
        ws.send(WebSocket::DataType::TEXT, message, strlen(message));
        String cmd_str = String((char *)message);
        if (full_vector) {
          cmd_str.trim();  // remove whitespace/newlines
          // Split the string by '-'
          int firstDash = cmd_str.indexOf('-');  // index of first '-'
          int secondDash = cmd_str.indexOf('-', firstDash + 1);
          int thirdDash = cmd_str.indexOf('-', secondDash + 1);
          String part1 = cmd_str.substring(0, firstDash);               // "box"
          String part2 = cmd_str.substring(firstDash + 1, secondDash);  // "7"
          String part3 = cmd_str.substring(secondDash + 1, thirdDash);  // "10"
          String symbol = cmd_str.substring(thirdDash + 1);             // "O" or "X"
          go_pos = { part2.toInt(), part3.toInt() };
          start = { (curren_p_x, curren_p_y) };
          shortestPathWithTrace(vec_map, start, go_pos);
        }
      } else {
        String cmd_str = String((char *)message);
        command = cmd_str.toInt();
        Serial.print("Command id received: ");
        Serial.println(command);
        //ACTION BASED ON WEBSOCKET
        switch (dataType) {
          case WebSocket::DataType::TEXT:
            if (!en_auto) {
              auto_off_switch();
            } else {
              auto_on_switch();
            }
            break;
          case WebSocket::DataType::BINARY:
            web_me3("Received binary data!");
            command = 0;
            break;
        }
      }
    });
    //WEBSOCKET CLOSING
    ws.onClose([](WebSocket &ws, const WebSocket::CloseCode, const char *, uint16_t) {
      Serial.println(F("Disconnected"));
      matrix.loadFrame(LEDMATRIX_LIKE);
      turnservo(90);
      en_auto = false;
      command = 0;
      better_serial = false;
      first_loop = true;
      en_assist = false;
      sensor_power_en = false;
      lights_en = false;
      flash = false;
      servo_flash = 0;
      light_current_id = -1;
      current_mil = 0;
      next_mil = 0;
      Serial.println(F("Everything was reset!"));
    });
  });
  webSocket.begin();
  Serial.println(F("WEBSOCKET SETUP SUCCESSFUL!"));
  Serial.println(F("////////////////////////////////////////////////////////////////////////////////////////////////"));
  delay(1000);
  matrix.clear();
  matrix.loadFrame(LEDMATRIX_LIKE);
}
// main loop that runs 
void loop() {
  webSocket.listen();
  move();
  steps();
  WiFiClient client = server.available();
  if (client) {
    // read the HTTP request header line by line
    Serial.println(F("New client connected"));
    while (client.connected()) {
      if (client.available()) {
        String HTTP_header = client.readStringUntil('\n');  // read the header line of HTTP request
        if (HTTP_header.equals("\r"))                       // the end of HTTP request
          break;
        Serial.print(F("<< "));
        Serial.println(HTTP_header);  // print HTTP request to Serial Monitor
      }
    }
    // send the HTTP response header
    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("Connection: close"));  // the connection will be closed after completion of the response
    client.println();                        // the separator between HTTP header and body
    delay(500);
    client.println(F(HTML_CONTENT));
    delay(1000);
    Serial.println(F("Serving client the HTML page."));
    client.flush();
    // give the web browser time to receive the data
    delay(500);
    Serial.println(F("Flushing client the HTML page."));
    // close the connection:
    client.stop();
    Serial.println(F("Ready."));
  }
}
// runs if auto move is enabled
void auto_on_switch() {
  switch (command) {
    case CMD_AUTO_OFF:
      web_me3("Command No Auto received!");
      web_me3("Ending of Auto Move.");
      en_auto = false;
      for (int i = 0; i < 4; i++) {
        sr.set(i, LOW);
        Serial.println("LOW");
      }
      break;
    case CMD_LIGHTS_ON:
      web_me3("Command Lights ON received!");
      break;
    case CMD_LIGHTS_OFF:
      web_me3("Command Lights OFF received!");
      break;
    case CMD_SPEED_0:
      speed = 0;
      stop();
      web_me3("Speed set to 0...");
      break;
    case CMD_SPEED_1:
      speed_set(1);
      stop();
      web_me3("Speed set to first level.");
      break;
    case CMD_SPEED_2:
      speed_set(2);
      stop();
      web_me3("Speed set to second level.");
      break;
    case CMD_SPEED_3:
      speed_set(3);
      stop();
      web_me3("Speed set to third level.");
      break;
    case CMD_SPEED_4:
      speed_set(4);
      stop();
      web_me3("Speed set to fourth level.");
      break;
    case CMD_SPEED_5:
      speed_set(5);
      stop();
      web_me3("Speed set to fifth (MAX) level!");
      break;
    default:
      command = 0;
      break;
  }
}
// runs if auto move is not enabled
void auto_off_switch() {
  switch (command) {
    case CMD_STOP:
      web_me3("Command Stop received!");
      matrix.loadFrame(LEDMATRIX_EMOJI_BASIC);
      break;
    case CMD_FORWARD:
      web_me3("Command Forward received!");
      break;
    case CMD_BACKWARDS:
      web_me3("Command Backwards received!");
      break;
    case CMD_LEFT:
      web_me3("Command Turn Left received!");
      break;
    case CMD_RIGHT:
      web_me3("Command Turn Right received!");
      break;
    case CMD_ASSIST:
      web_me3("Command Assist received!");
      web_me3("Initialization of Assited Move.");
      en_assist = !en_assist;
      command = 0;
      break;
    case CMD_NO_ASSIST:
      web_me3("Command No Assist received!");
      web_me3("Ending of Assited Move.");
      en_assist = !en_assist;
      command = 0;
      break;
    case CMD_AUTO_ON:
      web_me3("Command Auto received!");
      web_me3("Initialization of Auto Move.");
      en_auto = true;
      speed = 255;
      web_me3("Speed set to fifth (MAX) level!");
      web_box(curren_p_x, curren_p_y, "-o");
      vec_map[curren_p_x][curren_p_y - 1] = 0;
      for (int i = 0; i < 4; i++) {
        sr.set(i, HIGH);
        Serial.println("HIGH");
      }
      break;
    case CMD_AUTO_OFF:
      web_me3("Command No Auto received!");
      web_me3("Ending of Auto Move.");
      en_auto = false;
      break;
    case CMD_LIGHTS_ON:
      web_me3("Command Lights ON received!");
      break;
    case CMD_LIGHTS_OFF:
      web_me3("Command Lights OFF received!");
      break;
    case CMD_SERVO_MAX_LEFT:
      web_me3("Command Servo Max Left received!");
      break;
    case CMD_SERVO_LEFT:
      web_me3("Command Servo Left received!");
      break;
    case CMD_SERVO_CENTER:
      web_me3("Command Servo Center received!");
      break;
    case CMD_SERVO_RIGHT:
      web_me3("Command Servo Right received!");
      break;
    case CMD_SERVO_MAX_RIGHT:
      web_me3("Command Servo Max Right received!");
      break;
    case CMD_SPEED_0:
      speed = 0;
      stop();
      web_me3("Speed set to 0...");
      break;
    case CMD_SPEED_1:
      speed_set(1);
      stop();
      web_me3("Speed set to first level.");
      break;
    case CMD_SPEED_2:
      speed_set(2);
      stop();
      web_me3("Speed set to second level.");
      break;
    case CMD_SPEED_3:
      speed_set(3);
      stop();
      web_me3("Speed set to third level.");
      break;
    case CMD_SPEED_4:
      speed_set(4);
      stop();
      web_me3("Speed set to fourth level.");
      break;
    case CMD_SPEED_5:
      speed_set(5);
      stop();
      web_me3("Speed set to fifth (MAX) level!");
      break;
    default:
      web_me3("Unknown command received!");
      command = 0;
      break;
  }
}
// sends messages to HTML page
void web_me3(const char *message) {
  if (message != "") {
    if (string(message).substr(0, 2) == "SE") {
      webSocket.broadcast(WebSocket::DataType::TEXT, message, strlen(message));
      webSocket.broadcast(WebSocket::DataType::TEXT, "", strlen(""));
      double x = millis();
      x = std::round(x) / 1000;
      std::string str = std::to_string(x).substr(0, 5) + " : Servo Motor Angle set at :" + std::string(message).substr(2, strlen(message));
      const char *r = (const char *)str.c_str();
      webSocket.broadcast(WebSocket::DataType::TEXT, r, strlen(r));
      Serial.println(F(r));
    } else if (string(message).substr(0, 4) == "STEP") {
      webSocket.broadcast(WebSocket::DataType::TEXT, message, strlen(message));
      webSocket.broadcast(WebSocket::DataType::TEXT, "", strlen(""));
      Serial.println(F(message));
    } else if (string(message).substr(0, 3) == "map") {
      webSocket.broadcast(WebSocket::DataType::TEXT, message, strlen(message));
      webSocket.broadcast(WebSocket::DataType::TEXT, "", strlen(""));
      double x = millis();
      x = std::round(x) / 1000;
      std::string str = std::to_string(x).substr(0, 5) + " : Current position : " + message;
      const char *r = (const char *)str.c_str();
      webSocket.broadcast(WebSocket::DataType::TEXT, r, strlen(r));
      Serial.println(F(r));
    } else {
      double x = millis();
      x = std::round(x) / 1000;
      std::string str = std::to_string(x).substr(0, 5) + " : " + message;
      const char *r = (const char *)str.c_str();
      webSocket.broadcast(WebSocket::DataType::TEXT, r, strlen(r));
      Serial.println(F(r));
    }
  } else {
    webSocket.broadcast(WebSocket::DataType::TEXT, message, strlen(message));
  }
}
// sends position on the map
void web_box(int p_x, int p_y, const char *d) {
  p_x++;
  p_y++;
  std::string str = "map-" + std::to_string(p_x) + "-" + std::to_string(p_y) + d;
  const char *r = (const char *)str.c_str();
  web_me3(r);
}
// function for automated move
void auto_run() {
  if (!full_vector) {
    switch (echo_pos) {
      case 0:
        if (curren_p_x > 0) {
          if (curren_p_y > 0) {
            if (average_d(trigPinF, echoPinF) >= 20.0) {
              web_box(curren_p_x, curren_p_y - 1, "-o");
              vec_map[curren_p_x][curren_p_y - 1] = 0;
              forward_pin();
              delay(600);
              stop();
            } else {
              web_box(curren_p_x, curren_p_y - 1, "-x");
              vec_map[curren_p_x][curren_p_y - 1] = 1;
            }
            if (average_d(trigPinL, echoPinL) >= 20.0) {
              web_box(curren_p_x - 1, curren_p_y, "-o");
              vec_map[curren_p_x - 1][curren_p_y] = 0;
            } else {
              web_box(curren_p_x - 1, curren_p_y, "-x");
              vec_map[curren_p_x - 1][curren_p_y] = 1;
            }
            curren_p_y--;
          } else {
            if (average_d(trigPinL, echoPinL) >= 20.0) {
              web_box(curren_p_x - 1, curren_p_y, "-o");
              vec_map[curren_p_x - 1][curren_p_y] = 0;
              left_pin();
              delay(600);
              forward_pin();
              delay(600);
              left_pin();
              delay(600);
              stop();
              curren_p_x--;
              echo_pos = 1;
            } else {
              web_box(curren_p_x - 1, curren_p_y, "-x");
              vec_map[curren_p_x - 1][curren_p_y] = 1;
            }
          }
        }
        break;
      case 1:
        if (curren_p_x < 9) {
          if (curren_p_y < 9) {
            if (average_d(trigPinF, echoPinF) >= 20.0) {
              web_box(curren_p_x, curren_p_y + 1, "-o");
              vec_map[curren_p_x][curren_p_y + 1] = 0;
              forward_pin();
              delay(600);
              stop();
            } else {
              web_box(curren_p_x, curren_p_y + 1, "-x");
              vec_map[curren_p_x][curren_p_y + 1] = 1;
            }
            if (average_d(trigPinR, echoPinR) >= 20.0) {
              web_box(curren_p_x - 1, curren_p_y, "-o");
              vec_map[curren_p_x - 1][curren_p_y] = 0;
            } else {
              web_box(curren_p_x - 1, curren_p_y, "-x");
              vec_map[curren_p_x - 1][curren_p_y] = 1;
            }
            curren_p_y++;
          } else {
            if (average_d(trigPinR, echoPinR) >= 20.0) {
              web_box(curren_p_x - 1, curren_p_y, "-o");
              vec_map[curren_p_x - 1][curren_p_y] = 0;
              right_pin();
              delay(1200);
              forward_pin();
              delay(600);
              right_pin();
              delay(1200);
              stop();
              curren_p_x++;
              echo_pos = 0;
            } else {
              web_box(curren_p_x - 1, curren_p_y, "-x");
              vec_map[curren_p_x - 1][curren_p_y] = 1;
            }
          }
        }
        break;
    }
    if (curren_p_x == 0 && curren_p_y == 0 && check_full(vec_map)) {
      Serial.println("Vector map before flood fill:");
      print_vec(vec_map);
      Serial.println("Perform flood fill...");
      detect(vec_map);
      // Print the array after flood fill
      Serial.println("Vector map after flood fill:");
      print_vec(vec_map);
      full_vector = true;
      left_pin();
      delay(400);
      stop();
    }
  }
  average_step();
}
// checks if vector is full
bool check_full(std::vector<std::vector<int>> &vec) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (vec[i][j] = -1) {
        return false;
      }
    }
  }
  return true;
}
// prints vector
void print_vec(const std::vector<std::vector<int>> &vec) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      Serial.print(vec[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
// reverse flood fill function 
void flood_fill(std::vector<std::vector<int>> &vec, int pos_x, int pos_y, int target_color, int color, int wall) {
  if (pos_x < 0 || pos_x >= ROWS || pos_y < 0 || pos_y >= COLS) return;
  if (vec[pos_x][pos_y] == wall) return;          // If it's a wall, return
  if (vec[pos_x][pos_y] != target_color) return;  // If it's not target color, return
  // Change the current cell to the new color
  vec[pos_x][pos_y] = color;
  // Recursive flood fill for the four adjacent cells
  flood_fill(vec, pos_x + 1, pos_y, target_color, color, wall);  // Down
  flood_fill(vec, pos_x - 1, pos_y, target_color, color, wall);  // Up
  flood_fill(vec, pos_x, pos_y + 1, target_color, color, wall);  // Right
  flood_fill(vec, pos_x, pos_y - 1, target_color, color, wall);  // Left
}
// checks for valid move in the path
bool isValid(int x, int y, const std::vector<std::vector<int>> &grid, std::vector<std::vector<bool>> &visited) {
  return (x >= 0 && x < ROWS && y >= 0 && y < COLS && grid[x][y] == 0 && !visited[x][y]);
}
// finds shortest path from one box in the vector to another
void shortestPathWithTrace(const std::vector<std::vector<int>> &grid, Point start, Point end) {
  int rowDir[] = { -1, 1, 0, 0 };  // Direction vectors for up, down, left, right
  int colDir[] = { 0, 0, -1, 1 };

  std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
  std::vector<std::vector<Point>> parent(ROWS, std::vector<Point>(COLS));
  std::vector<std::vector<int>> dist(ROWS, std::vector<int>(COLS, 0));

  // Start with the start point
  visited[start.x][start.y] = true;
  dist[start.x][start.y] = 0;
  parent[start.x][start.y] = { -1, -1 };  // No parent for start

  std::vector<Point> q;  // Simple queue using vector
  q.push_back(start);    // Enqueue the start point

  while (!q.empty()) {
    Point curr = q.front();
    q.erase(q.begin());  // Dequeue
    if (curr.x == end.x && curr.y == end.y) {
      // Backtrack the path
      Point p = end;
      while (p.x != -1 && p.y != -1) {
        Serial.print("(");
        Serial.print(p.x);
        Serial.print(", ");
        Serial.print(p.y);
        Serial.print(") ");
        p = parent[p.x][p.y];
      }
      Serial.println();
      return;
    }

    // Explore neighbors (up, down, left, right)
    for (int i = 0; i < 4; i++) {
      int newRow = curr.x + rowDir[i];
      int newCol = curr.y + colDir[i];

      if (isValid(newRow, newCol, grid, visited)) {
        visited[newRow][newCol] = true;
        parent[newRow][newCol] = curr;
        q.push_back({ newRow, newCol });  // Enqueue the new point
        int po = 0;
        if (newCol > curren_p_y) {
          po = newCol - curren_p_y;
          for (int i = 0; i < po; i++) {
            forward_pin();
            delay(600);
            stop();
          }
          curren_p_y = newCol;
        } else {
          po = curren_p_y - newCol;
          for (int i = 0; i < po; i++) {
            backwards_pin();
            delay(600);
            stop();
          }
          curren_p_y = newCol;
        }
        po = 0;
        if (newRow > curren_p_x) {
          po = newRow - curren_p_x;
          right_pin();
          delay(200);
          for (int i = 0; i < po; i++) {
            forward_pin();
            delay(600);
            stop();
          }
          left_pin();
          delay(200);
          curren_p_x = newRow;
        } else {
          po = curren_p_x - newRow;
          left_pin();
          delay(200);
          for (int i = 0; i < po; i++) {
            forward_pin();
            delay(600);
            stop();
          }
          right_pin();
          delay(200);
          curren_p_x = newRow;
        }
      }
    }
  }

  // No path found
  Serial.println("No path found.");
}
// reverse flood fill function to detect encased spaces
void detect(std::vector<std::vector<int>> &vec) {
  Serial.println("Flood filling...");
  fill_shape(vec, -1, 2);           // Convert all '-1' cells to '2'
  flood_fill(vec, 9, 9, 0, 2, 10);  // Use 10 as wall for flood fill
  Serial.println("Shape detection...");
  fill_shape(vec, 0, 1);  // Convert all '0' cells to '1'
  fill_shape(vec, 2, 0);  // Convert flood fill cells (2) back to '0'
}
// changes vector box value from one to another
void fill_shape(std::vector<std::vector<int>> &vec, int to_change, int to_new) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (vec[i][j] == to_change) {
        vec[i][j] = to_new;
      }
    }
  }
}
// returns average step turn
void average_step() {
  int sum = countFR + countFL + countBR + countBL;
  sum = sum / 4;
  std::string str = "STEP" + std::to_string(sum);
  const char *r = (const char *)str.c_str();
  web_me3(r);
  str.clear();
}
// run all counters
void steps() {
  ir_countfr();
  ir_countfl();
  ir_countbr();
  ir_countbl();
}
// function to count steps from front right ir sensor
void ir_countfr() {
  if (analogRead(stepFR) > 512) {
    cur_fr = true;
  } else {
    cur_fr = false;
  }
  if (prev_fr != cur_fr) {
    countFR++;
    prev_fr = cur_fr;
  }
}
// function to count steps from front left ir sensor
void ir_countfl() {
  if (analogRead(stepFL) > 512) {
    cur_fl = true;
  } else {
    cur_fl = false;
  }
  if (prev_fl != cur_fl) {
    countFL++;
    prev_fl = cur_fl;
  }
}
// function to count steps from back right ir sensor
void ir_countbr() {
  if (analogRead(stepBR) > 512) {
    cur_br = true;
  } else {
    cur_br = false;
  }
  if (prev_br != cur_br) {
    countBR++;
    prev_br = cur_br;
  }
}
// function to count steps from back left ir sensor
void ir_countbl() {
  if (analogRead(stepBL) > 512) {
    cur_bl = true;
  } else {
    cur_bl = false;
  }
  if (prev_bl != cur_bl) {
    countBL++;
    prev_bl = cur_bl;
  }
}
// servo angle control function
void angle_turn() {
  switch (command) {
    case CMD_SERVO_MAX_LEFT:
      turnservo(180);
      web_me3("SE180");
      break;
    case CMD_SERVO_LEFT:
      if (angle < 180) {
        turnservo(angle + 1);
        std::string str = "SE" + std::to_string(angle);
        const char *r = (const char *)str.c_str();
        web_me3(r);
        str.clear();
      }
      break;
    case CMD_SERVO_CENTER:
      turnservo(90);
      web_me3("SE90");
      break;
    case CMD_SERVO_RIGHT:
      if (angle > 0) {
        turnservo(angle - 1);
        std::string str = "SE" + std::to_string(angle);
        const char *r = (const char *)str.c_str();
        web_me3(r);
        str.clear();
      }
      break;
    case CMD_SERVO_MAX_RIGHT:
      turnservo(0);
      web_me3("SE0");
      break;
    default:
      break;
  }
  web_me3("");
}
// sets the servo degree
void turnservo(int n) {
  if (n > angle) {
    while (n > angle) {
      pin0.write(angle);
      angle++;
      delayMicroseconds(10);
    }
    pin0.write(angle);
  } else if (n < angle) {
    while (n < angle) {
      pin0.write(angle);
      angle--;
      delayMicroseconds(10);
    }
    pin0.write(angle);
  }
}
// chage the frame's image
void frame_change(byte arr[8][12]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 12; j++) {
      frame[i][j] = arr[i][j];
    }
  }
}
// change matrix frame
void matrix_move(byte arr[8][12]) {
  matrix.clear();
  frame_change(arr);
  matrix.renderBitmap(frame, 8, 12);
}
//the light enable function
void light_show() {
  bool residual = false;
  switch (command) {
    case CMD_LIGHTS_ON:
      if (!lights_en) {
        web_me3("Lights Turned ON!");
        for (int i = 8; i < 16; i++) {
          sr.set(i, HIGH);
        }
        lights_en = true;
        residual = true;
        light_current_id = -1;
        flash = true;
        delay(1000);
        for (int i = 10; i < 14; i++) {
          sr.set(i, LOW);
        }
      }
      break;
    case CMD_LIGHTS_OFF:
      if (lights_en) {
        for (int i = 8; i < 16; i++) {
          sr.set(i, LOW);
        }
        web_me3("Lights Turned OFF...");
        lights_en = false;
        residual = true;
        flash = false;
        light_current_id = -1;
      }
      break;
    default:
      break;
  }
  if (lights_en) lights();
  if (residual) web_me3("");
}
// the light control function
void lights() {
  switch (command) {
    case CMD_STOP:
      if (light_current_id != CMD_STOP) {
        for (int i = 10; i < 14; i++) {
          sr.set(i, LOW);
        }
        sr.set(8, HIGH);
        sr.set(9, HIGH);
        sr.set(14, HIGH);
        sr.set(15, HIGH);
        light_current_id = CMD_STOP;
        flash = false;
      }
      break;
    case CMD_FORWARD:
      if (light_current_id != CMD_FORWARD) {
        sr.set(8, HIGH);
        sr.set(9, HIGH);
        for (int i = 10; i < 16; i++) {
          sr.set(i, LOW);
        }
        light_current_id = CMD_FORWARD;
      }
      break;
    case CMD_BACKWARDS:
      current_mil = millis();
      if (light_current_id != CMD_BACKWARDS) {
        next_mil = current_mil + 500.0;
        light_current_id = CMD_BACKWARDS;
        flash = !flash;
        sr.set(8, HIGH);
        sr.set(9, HIGH);
        for (int i = 10; i < 14; i++) {
          sr.set(i, LOW);
        }
      }
      if (flash) {
        sr.set(14, HIGH);
        sr.set(15, HIGH);
      } else {
        sr.set(14, LOW);
        sr.set(15, LOW);
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    case CMD_LEFT:
      current_mil = millis();
      if (light_current_id != CMD_LEFT) {
        next_mil = current_mil + 500.0;
        light_current_id = CMD_LEFT;
        flash = !flash;
        sr.set(8, HIGH);
        sr.set(9, HIGH);
        for (int i = 10; i < 16; i++) {
          sr.set(i, LOW);
        }
      }
      if (flash) {
        sr.set(10, HIGH);
        sr.set(11, HIGH);
      } else {
        sr.set(10, LOW);
        sr.set(11, LOW);
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    case CMD_RIGHT:
      current_mil = millis();
      if (light_current_id != CMD_RIGHT) {
        next_mil = current_mil + 500.0;
        light_current_id = CMD_RIGHT;
        flash = !flash;
        sr.set(8, HIGH);
        sr.set(9, HIGH);
        for (int i = 10; i < 16; i++) {
          sr.set(i, LOW);
        }
      }
      if (flash) {
        sr.set(12, HIGH);
        sr.set(13, HIGH);
      } else {
        sr.set(12, LOW);
        sr.set(13, LOW);
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    case CMD_SERVO_MAX_LEFT:
      current_mil = millis();
      if (light_current_id != CMD_SERVO_MAX_LEFT) {
        next_mil = current_mil + 50.0;
        light_current_id = CMD_SERVO_MAX_LEFT;
        flash = !flash;
        for (int i = 8; i < 16; i++) {
          sr.set(i, LOW);
        }
      }
      if (flash) {
        for (int i = 10; i < 14; i++) {
          sr.set(i, HIGH);
        }
      } else {
        for (int i = 10; i < 14; i++) {
          sr.set(i, LOW);
        }
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    case CMD_SERVO_LEFT:
      current_mil = millis();
      if (light_current_id != CMD_SERVO_LEFT) {
        next_mil = current_mil + 50.0;
        light_current_id = CMD_SERVO_LEFT;
        servo_flash++;
        for (int i = 8; i < 16; i++) {
          sr.set(i, LOW);
        }
      }
      switch (servo_flash) {
        case 1:
          sr.set(12, LOW);
          sr.set(10, HIGH);
          break;
        case 2:
          sr.set(10, LOW);
          sr.set(11, HIGH);
          break;
        case 3:
          sr.set(11, LOW);
          sr.set(13, HIGH);
          break;
        case 4:
          sr.set(13, LOW);
          sr.set(12, HIGH);
          servo_flash = 0;
          break;
        default:
          servo_flash = 0;
          break;
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    case CMD_SERVO_CENTER:
      current_mil = millis();
      if (light_current_id != CMD_SERVO_CENTER) {
        next_mil = current_mil + 50.0;
        light_current_id = CMD_SERVO_CENTER;
        flash = !flash;
        for (int i = 8; i < 16; i++) {
          sr.set(i, LOW);
        }
      }
      if (flash) {
        for (int i = 10; i < 14; i++) {
          sr.set(i, HIGH);
        }
      } else {
        for (int i = 10; i < 14; i++) {
          sr.set(i, LOW);
        }
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    case CMD_SERVO_RIGHT:
      current_mil = millis();
      if (light_current_id != CMD_SERVO_LEFT) {
        next_mil = current_mil + 50.0;
        light_current_id = CMD_SERVO_LEFT;
        servo_flash++;
        for (int i = 8; i < 16; i++) {
          sr.set(i, LOW);
        }
      }
      switch (servo_flash) {
        case 1:
          sr.set(10, LOW);
          sr.set(12, HIGH);
          break;
        case 2:
          sr.set(12, LOW);
          sr.set(13, HIGH);
          break;
        case 3:
          sr.set(13, LOW);
          sr.set(11, HIGH);
          break;
        case 4:
          sr.set(11, LOW);
          sr.set(10, HIGH);
          servo_flash = 0;
          break;
        default:
          servo_flash = 0;
          break;
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    case CMD_SERVO_MAX_RIGHT:
      current_mil = millis();
      if (light_current_id != CMD_SERVO_MAX_RIGHT) {
        next_mil = current_mil + 50.0;
        light_current_id = CMD_SERVO_MAX_RIGHT;
        flash = !flash;
        for (int i = 8; i < 16; i++) {
          sr.set(i, LOW);
        }
      }
      if (flash) {
        for (int i = 10; i < 14; i++) {
          sr.set(i, HIGH);
        }
      } else {
        for (int i = 10; i < 14; i++) {
          sr.set(i, LOW);
        }
      }
      if (next_mil < current_mil) {
        light_current_id = -1;
      }
      break;
    default:
      break;
  }
}
// main move control function
// contains all others
void move() {
  if (!en_auto) {
    if (en_assist) {
      if (sensor_power_en == false) {
        sensor_power_en = true;
        for (int i = 0; i < 4; i++) {
          sr.set(i, HIGH);
        }
      }
      light_show();
      move_assist();
      angle_turn();
    } else {
      if (sensor_power_en == true) {
        sensor_power_en = false;
        for (int i = 0; i < 4; i++) {
          sr.set(i, LOW);
        }
      }
      light_show();
      move_no_assist();
      angle_turn();
    }
  } else {
    auto_run();
    light_show();
  }
}
// function to move without sensor assistance
void move_no_assist() {
  switch (command) {
    case CMD_STOP:
      stop();
      if (!first_loop) {
        first_loop = true;
        better_serial = false;
        average_step();
      }
      break;
    case CMD_FORWARD:
      forward_no_assist();
      if (IR_output(stepFR) > 512) countFR++;
      break;
    case CMD_BACKWARDS:
      backwards_no_assist();
      break;
    case CMD_LEFT:
      turn_left_no_assist();
      break;
    case CMD_RIGHT:
      turn_right_no_assist();
      break;
    default:
      break;
  }
}
// function to move forward without sensor assistance
void forward_no_assist() {
  bool residual = false;
  if (!better_serial || first_loop) {
    forward_pin();
    web_me3("Moving Forward.");
    matrix_move(forward_b);
    better_serial = !better_serial;
    residual = !residual;
    if (first_loop) { first_loop = false; }
  }
  if (residual) web_me3("");
}
// function to move backwards without sensor assistance
void backwards_no_assist() {
  bool residual = false;
  if (!better_serial || first_loop) {
    backwards_pin();
    web_me3("Moving Backwards.");
    matrix_move(backwards_b);
    better_serial = !better_serial;
    residual = !residual;
    if (first_loop) { first_loop = false; }
  }
  if (residual) web_me3("");
}
// function to turn right without sensor assistance
void turn_right_no_assist() {
  bool residual = false;
  if (!better_serial || first_loop) {
    right_pin();
    web_me3("Turning Right.");
    matrix_move(turn_right_b);
    better_serial = !better_serial;
    residual = !residual;
    if (first_loop) { first_loop = false; }
  }
  if (residual) web_me3("");
}
// function to turn left without sensor assistance
void turn_left_no_assist() {
  bool residual = false;
  if (!better_serial || first_loop) {
    left_pin();
    web_me3("Turning Left.");
    matrix_move(turn_left_b);
    better_serial = !better_serial;
    residual = !residual;
    if (first_loop) { first_loop = false; }
  }
  if (residual) web_me3("");
}
// function to move with sensor assistance
void move_assist() {
  switch (command) {
    case CMD_STOP:
      stop();
      if (!first_loop) {
        first_loop = true;
        better_serial = false;
        average_step();
      }
      break;
    case CMD_FORWARD:
      forward_assist();
      break;
    case CMD_BACKWARDS:
      backwards_assist();
      break;
    case CMD_LEFT:
      turn_left_assist();
      break;
    case CMD_RIGHT:
      turn_right_assist();
      break;
    default:
      break;
  }
}
// function to move forward with sensor assistance
void forward_assist() {
  bool residual = false;
  if (checkDistanceUltrasonic(trigPinF, echoPinF) >= 20.0) {
    if (!better_serial || first_loop) {
      forward_pin();
      web_me3("Moving Forward, no object found.");
      matrix_move(forward_b);
      better_serial = !better_serial;
      residual = !residual;
      if (first_loop) { first_loop = false; }
    }
  } else {
    if (better_serial || first_loop) {
      stop();
      web_me3("Object found, can't move Forward!");
      matrix.clear();
      matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
      better_serial = !better_serial;
      residual = !residual;
      if (first_loop) {
        first_loop = false;
        better_serial = !better_serial;
      }
    }
  }
  if (residual) web_me3("");
}
// function to move back with sensor assistance
void backwards_assist() {
  bool residual = false;
  if (checkDistanceUltrasonic(trigPinB, echoPinB) >= 20.0) {
    if (!better_serial || first_loop) {
      backwards_pin();
      web_me3("Moving Backwards, no object found.");
      matrix_move(backwards_b);
      better_serial = !better_serial;
      residual = !residual;
      if (first_loop) { first_loop = false; }
    }
  } else {
    if (better_serial || first_loop) {
      stop();
      web_me3("Object found, can't move Backwards!");
      matrix.clear();
      matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
      better_serial = !better_serial;
      residual = !residual;
      if (first_loop) {
        first_loop = false;
        better_serial = !better_serial;
      }
    }
  }
  if (residual) web_me3("");
}
// function to turn right with sensor assistance
void turn_right_assist() {
  bool residual = false;
  if (checkDistanceUltrasonic(trigPinR, echoPinR) >= 20.0) {
    if (!better_serial || first_loop) {
      right_pin();
      web_me3("Turning Right, no object found.");
      matrix_move(turn_right_b);
      better_serial = !better_serial;
      if (first_loop) { first_loop = false; }
    }
  } else {
    if (better_serial || first_loop) {
      stop();
      web_me3("Object found, can't turn Right!");
      matrix.clear();
      matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
      better_serial = !better_serial;
      if (first_loop) {
        first_loop = false;
        better_serial = !better_serial;
      }
    }
  }
  if (residual) web_me3("");
}
// function to turn left with sensor assistance
void turn_left_assist() {
  bool residual = false;
  if (checkDistanceUltrasonic(trigPinL, echoPinL) >= 20.0) {
    if (!better_serial || first_loop) {
      left_pin();
      web_me3("Turning Left, no object found.");
      matrix_move(turn_left_b);
      better_serial = !better_serial;
      if (first_loop) { first_loop = false; }
    }
  } else {
    if (better_serial || first_loop) {
      stop();
      web_me3("Object found, can't turn Left!");
      matrix.clear();
      matrix.loadFrame(LEDMATRIX_EMOJI_SAD);
      better_serial = !better_serial;
      if (first_loop) {
        first_loop = false;
        better_serial = !better_serial;
      }
    }
  }
  if (residual) web_me3("");
}
// check the mean distance from ultrasonic sensors
float average_d(int trigP, int echoP) {
  float sum = 0;
  for (int i = 0; i < 5; i++) {
    sum = sum + checkDistanceUltrasonic(trigP, echoP);
  }
  return sum / 5;
}
// check the distance from ultrasonic sensors
float checkDistanceUltrasonic(int trigP, int echoP) {
  float distance, duration;
  digitalWrite(trigP, LOW);
  delayMicroseconds(2);
  digitalWrite(trigP, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigP, LOW);
  duration = pulseIn(echoP, HIGH);
  distance = (duration * .0343) / 2;
  return distance;
}
// get infrared output
int IR_output(int output) {
  int res = analogRead(output);
  Serial.println(res);
  return res;
}
// setting speed
void speed_set(int x) {
  speed = (x - 1) * (255 - 125) / (5 - 1) + 125;
}
// function to turn left
void left_pin() {
  //////RIGHT CHECK
  analogWrite(rightF, speed);
  analogWrite(rightB, 0);
  //////LEFT CHECK
  analogWrite(leftF, speed);
  analogWrite(leftB, 0);
}
// function to turn right
void right_pin() {
  //////RIGHT CHECK
  analogWrite(rightF, 0);
  analogWrite(rightB, speed);
  //////LEFT CHECK
  analogWrite(leftF, 0);
  analogWrite(leftB, speed);
}
// function to move forward
void forward_pin() {
  //////RIGHT CHECK
  analogWrite(rightF, 0);
  analogWrite(rightB, speed);
  //////LEFT CHECK
  analogWrite(leftF, speed);
  analogWrite(leftB, 0);
}
// function to move backwards
void backwards_pin() {
  //////RIGHT CHECK
  analogWrite(rightF, speed);
  analogWrite(rightB, 0);
  //////LEFT CHECK
  analogWrite(leftF, 0);
  analogWrite(leftB, speed);
}
// function to stop motors
void stop() {
  //////RIGHT CHECK
  analogWrite(rightF, 0);
  analogWrite(rightB, 0);
  //////LEFT CHECK
  analogWrite(leftF, 0);
  analogWrite(leftB, 0);
}