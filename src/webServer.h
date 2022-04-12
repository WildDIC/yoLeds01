// #include <WebServer.h>
#include "ESPAsyncWebServer.h"


AsyncWebServer server(80);

#define NUM_RANGES  4
#define NUM_BUTTONS 12

const char* PARAM_INPUT_1 = "funcID";  
const char* PARAM_INPUT_2 = "value";

button bList[NUM_BUTTONS];
range rList[NUM_RANGES];

void collectData(){
	bList[0] =  { 551489775, "Power ON/OFF"};
	bList[1] =  { 1262530894, "White Color"};
	bList[2] =  { 1262547214, "Pallette test"};
	bList[3] =  { 1262529364, "Wave 01"};
	bList[4] =  { 1262513044, "Костерок 01"};
	bList[5] =  { 1262545684, "Flasher"};
	bList[6] =  { 1262492644, "8 waves"};
	bList[7] =  { 1262525284, "Crepping rainbow"};
	bList[8] =  { 1262508964, "Musix echo"};
	bList[9] =  { 1262541604, "Fire 2012"};
	bList[10] = { 1262500804, "Костерок 02"};
	bList[11] = { 1262533444, "Wave shit"};

	rList[0] = { 1066677700, 5, 255, "Brightness"};
	rList[1] = { 1066677701, 0, 255, "Saturations"};
	rList[2] = { 1066677702, 0, TEMP_IND_MAX, "Temperature"};
	rList[3] = { 1066677703, 0, 30, "Speed"};
}

const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML><html>
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1" charset="UTF-8">
  	<style>
    	html {font-family: Arial; display: inline-block; text-align: center;}
    	h2 {font-size: 3.0rem;}
		div { align-self: center;}
    	body {max-width: 600px; margin:0px auto; background: #21252B; color: #E1E1E1; display: flex; flex-direction: column; align-items: flex-start; 
			font-family: 'Microsoft JhengHei UI', 'Open Sans', Arial, sans-serif;}
    	
		button { width: 350px; background: #181E28; appearance: none; border: 0; border-radius: 5px; color: #E1E1E1; padding: 8px 16px; margin: 10px; font-size: 1.1em;}
		button.active {background: #2196F3}
		button:hover {   background: #474747}
		button:active {  background-color: #2196F3;}		
		button.power {background: #FF0E90}
		button.power.active{background: #3CB371} 
		
		.textLabel { text-align: center; font-weight: bold; font-size: 1.2em; margin: 10px auto; text-shadow: black 1px 1px 1px;}
		
		input[type="range"] { display: block; -webkit-appearance: none; background-color: #bdc3c7; width: 350px; height: 5px; border-radius: 5px; margin: 10px auto; margin-bottom: 20px; outline: 0;}
		input[type="range"]::-webkit-slider-thumb { -webkit-appearance: none; background-color: #181E28; width: 20px; height: 20px; border: 2px solid white; cursor: pointer; transition: .3s ease-in-out; border-radius: 10px;}​
  		input[type="range"]::-webkit-slider-thumb:hover { background-color: white; border: 2px solid #e74c3c; }
  		input[type="range"]::-webkit-slider-thumb:active { transform: scale(1.3); }
  	</style>
</head>
<body>
    <div><h2>noisex led server</h2></div>  	
	<div class="upser">upser</div>

	%RANGEPLACEHOLDER%
    %BUTTONPLACEHOLDER%
       
	<script>
		const wave = document.querySelectorAll('.wave');
		function buttonClick(element) {
			if ( element.classList.contains("power") == true) {
				element.classList.toggle("active");   
			};
			
			var xhr = new XMLHttpRequest();
			xhr.open("GET", "/update?funcID="+element.id, true); 
			xhr.send();
			updateDate();
		}
		function rInput( element) {
			var value = element.value;
			var classValue = '.' + element.className + '-value';
			var target = document.querySelector( classValue);
			target.innerHTML = value;

			var xhr = new XMLHttpRequest();
			xhr.open("GET", "/update?funcID="+element.id+"&value="+value, true); 
			xhr.send();
		}  
		function reseter( xhr){
			wave.forEach((element) => element.classList.remove('active'));
			var json = JSON.parse(xhr.responseText);
			
			document.querySelector( ".upser").innerHTML = json.vPressed;
			document.getElementById( json.vPressed).classList.add('active');

			document.getElementById( 1066677700).value = json.vBrightness;
			document.getElementById( 1066677701).value = json.vSaturn;
			document.getElementById( 1066677702).value = json.vTemp;
			document.getElementById( 1066677703).value = json.vSpeed;

			document.querySelector( ".Brightness-value").innerHTML = json.vBrightness;
			document.querySelector( ".Saturations-value").innerHTML = json.vSaturn;
			document.querySelector( ".Temperature-value").innerHTML = json.vTemp;
			document.querySelector( ".Speed-value").innerHTML = json.vSpeed;

			var onoff = document.getElementById( 551489775)
			if ( json.vONOFF == 1){
				onoff.classList.add('active');
			}else{
				onoff.classList.remove('active');
			}
		}
		function updateDate(){
			var xhr = new XMLHttpRequest();            
			xhr.onreadystatechange = function() {
				if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
					reseter( xhr);    
				}
			};
			xhr.open("GET", "/reset", true); 
			xhr.send();
		}
		(function updateSelfDate(){ updateDate(); setTimeout(updateSelfDate, 3000);})();
	</script>
</body>
</html>
)rawliteral";

int rState(int numValue){
	switch (numValue){		
		case 0: numValue = yo.currentBrightness; break;
		case 1: numValue = yo.currentSaturn; break;
		case 2: numValue = yo.currentTemp; break;		
		case 3: numValue = yo.currentSpeed; break;
	}
	return numValue;
}

// Replaces placeholder with button section in your web page
String processor(const String& var){
	//Serial.println(var);
	if(var == "RANGEPLACEHOLDER"){
		String buttons ="\n";		
		for(int i = 0; i < NUM_RANGES; i++){
			int rValue = rState(i);
			buttons += "<div><span class='textLabel'>"+rList[i].name+": </span><span class='textLabel "+rList[i].name+"-value' id=''>"+rValue+"</span>\n";
			buttons += "<input id='"+String( rList[i].code)+"' class='"+rList[i].name+"' type='range' min='"+rList[i].min+"' max='"+rList[i].max+"' step='1' value='"+rValue+"' onchange='rInput(this)';></div>\n";
		}
		
		String active = "";			
		if ( yo.ONOFF == true){
			active = " active";
		}
		buttons += "\n";
		buttons += "<div><button onclick='buttonClick(this)' id='"+ String( bList[0].code) +"' class='power"+ active +"'>"+ bList[0].name +"</button></div>\n";

		for ( int i = 1; i < NUM_BUTTONS; i++ ){
			active = "";			
			if ( yo.lastPressed == bList[i].code){
				active = " active";
			}
			buttons += "<div><button onclick='buttonClick(this)' id='"+ String( bList[i].code) +"' class='wave"+ active +"'>"+ bList[i].name +"</button></div>\n";
		}
		return buttons;
	}
	return String();
}

extern void irServer( int codeFromWeb, int webValue);

/*
Поднимаем и настраиваем Веб-сервер ESPAsyncWebServer
*/
void webServerStart(){
	collectData();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send_P(200, "text/html", index_html, processor);
        }
    );

	server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
		if (request->hasParam(PARAM_INPUT_1)) {			
			String inputMessage01 = request->getParam(PARAM_INPUT_1)->value();
			String inputMessage02 = "0";

			if (request->hasParam(PARAM_INPUT_2)) {
				inputMessage02 = request->getParam(PARAM_INPUT_2)->value();
			}
			irServer( atoi( inputMessage01.c_str()), atoi( inputMessage02.c_str()));
		}
		request->send(200, "text/plain", "OK");
	});

	server.on("/reset", HTTP_GET, [] (AsyncWebServerRequest *request) {
		// Serial.println( "Send update to client...");
		String out = "{";
		out += "\"vBrightness\": "	+ String(yo.currentBrightness)	+", ";
		out += "\"vSaturn\": "		+ String(yo.currentSaturn)		+", ";
		out += "\"vTemp\": "		+ String(yo.currentTemp)		+", ";
		out += "\"vSpeed\": "		+ String(yo.currentSpeed)		+", ";
		out += "\"vPressed\": "		+ String(yo.lastPressed)		+", ";
		out += "\"vONOFF\": "		+ String(yo.ONOFF)				+" ";
		out += "}";
		request->send(200, "application/json", out);
	});

	server.begin();
}

/*



		String out = "{";
		out += "\"0\": {\"id\": 1066677700, \"val\": "+ String(yo.currentBrightness)+"},";
		out += "\"1\": {\"id\": 1066677701, \"val\": "+ String(yo.currentSaturn)+"},";
		out += "\"2\": {\"id\": 1066677702, \"val\": "+ String(yo.currentTemp)+"},";
		out += "\"3\": {\"id\": 1066677703, \"val\": "+ String(yo.currentSpeed)+"},";
		out += "}";
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(200, "application/json", "{\"message\":\"Welcome\"}");
});

Хранение многострочной строки JSON в переменной JS
используя новые литералы шаблона ES6 

var json = `{
    "book": {
        "name": "Harry Potter and the Goblet of Fire",
        "author": "J. K. Rowling",
        "year": 2000,
        "characters": ["Harry Potter", "Hermione Granger", "Ron Weasley"],
        "genre": "Fantasy Fiction",
        "price": {
            "paperback": "$10.40", "hardcover": "$20.32", "kindle": "$4.11"
        }
    }
}`;

// Преобразование объекта JSON в объект JS
var obj = JSON.parse(json);

// Рекурсивная функция для печати вложенных значений
function printValues(obj) {
    for(var k in obj) {
        if(obj[k] instanceof Object) {
            printValues(obj[k]);
        } else {
            document.write(obj[k] + "<br>");
        };
    }
};

// Печать всех значений из результирующего объекта
printValues(obj);

document.write("<hr>");

// Печать одного значения
document.write(obj["book"]["author"] + "<br>");  // Выводит: J. K. Rowling
document.write(obj["book"]["characters"][0] + "<br>");  // Выводит: Harry Potter
document.write(obj["book"]["price"]["hardcover"]);  // Выводит: $20.32
*/