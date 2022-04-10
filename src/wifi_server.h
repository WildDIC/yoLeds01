#include <WiFi.h>
// #include <WebServer.h>
#include "ESPAsyncWebServer.h"
#include "pass.h"

AsyncWebServer server(80);
// Set number of relays
#define NUM_RELAYS  5
// Set to true to define Relay as Normally Open (NO)
#define RELAY_NO    true
// Assign each GPIO to a relay
int relayGPIOs[NUM_RELAYS] = {2, 26, 27, 25, 33};
// void (*pt2WebFunc)()[12]; 				// Указатель на функцию для CASE
// Foo *array[12];

const char* PARAM_INPUT_1 = "relay";  
const char* PARAM_INPUT_2 = "state";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
  	<style>
    	html {font-family: Arial; display: inline-block; text-align: center;}
    	h2 {font-size: 3.0rem;}
    	p {font-size: 3.0rem;}
    	body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    	.switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    	.switch input {display: none}
    	.slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 34px}
    	.slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 68px}
    	input:checked+.slider {background-color: #2196F3}
    	input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  	</style>
</head>
<body>
  	<h2>ESP Web Server</h2>
  	%BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  	var xhr = new XMLHttpRequest();
  	if(element.checked){ xhr.open("GET", "/update?relay="+element.id+"&state=1", true); }
  	else { xhr.open("GET", "/update?relay="+element.id+"&state=0", true); }
  	xhr.send();}
</script>
</body>
</html>
)rawliteral";

String relayState(int numRelay){
	if( true){
		if(digitalRead(relayGPIOs[numRelay-1])){
			return "not checked";
		}
		else {
			return "checked";
		}
	}
	else {
		if(digitalRead(relayGPIOs[numRelay-1])){
			return "checked";
		}
		else {
			return "2 not checked";
		}
	}
	return "3 not checked";
}


// Replaces placeholder with button section in your web page
String processor(const String& var){
	//Serial.println(var);
	if(var == "BUTTONPLACEHOLDER"){
		String buttons ="";
		for(int i=1; i<=NUM_RELAYS; i++){
			String relayStateValue = relayState(i);
			buttons+= "<h4>Relay #" + String(i) + " - GPIO " + relayGPIOs[i-1] + "</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"" + String(i) + "\" "+ relayStateValue +"><span class=\"slider\"></span></label>";
		}
		return buttons;
	}
	return String();
}

/* Поднимаем ВайФай и подключаемся к домашней сети.
WIFI_SSID и WIFI_PASS прописываем в файле pass.h:

const char* WIFI_SSID = "";
const char* WIFI_PASS = "";
*/
void wifiConnect(){
    Serial.printf( "\nConnect to: %s\n", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      	delay(500);
      	Serial.print(".");
    }
    Serial.print("\nWiFi connected.\nIP address: ");
      	Serial.println( WiFi.localIP());

      	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send_P(200, "text/html", index_html, processor);
        }
    );

	server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
		String inputMessage;
		String inputParam;
		String inputMessage2;
		String inputParam2;
		// GET input1 value on <ESP_IP>/update?relay=<inputMessage>
		if (request->hasParam(PARAM_INPUT_1) & request->hasParam(PARAM_INPUT_2)) {
			inputMessage = request->getParam(PARAM_INPUT_1)->value();
			inputParam = PARAM_INPUT_1;
			inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
			inputParam2 = PARAM_INPUT_2;
			if(RELAY_NO){
				Serial.print("NO ");
				digitalWrite(relayGPIOs[inputMessage.toInt()-1], !inputMessage2.toInt());
			}
			else{
				Serial.print("NC ");
				digitalWrite(relayGPIOs[inputMessage.toInt()-1], inputMessage2.toInt());
			}
		}
		else {
			inputMessage = "No message sent";
			inputParam = "none";
		}
		Serial.println(inputMessage + inputMessage2);
		request->send(200, "text/plain", "OK");
	});

	// Start server
	server.begin();
}


// String makeHTML(){
//     String ret = "<!DOCTYPE html><html><body>";
//         ret += "<h1>My First Web Server with ESP32 - Station Mode &#128522;</h1>";
//         ret += "<h2>Speed: " + String( yo.currentSpeed) + " mS</h2>";
//         ret += "</body></html>";
//     return ret;
// } 