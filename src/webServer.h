// #include <WebServer.h>
#include "ESPAsyncWebServer.h"

AsyncWebServer server(80);

byte NUM_RANGES = 1;
byte NUM_BUTTONS = 1;

const char* PARAM_INPUT_1 = "funcID";  
const char* PARAM_INPUT_2 = "value";
// extern void irdaServer( int codeFromWeb, int mbIter);

button bList[20];
range rList[10];

void collectData(){	
	mbIter = mButtons.begin();
	for (int i = 0; mbIter != mButtons.end(); mbIter++, i++) {		
		mbIter->second.code = mbIter->first;
		if ( mbIter->second.indForWeb){
			if ( mbIter->second.typeWeb == 1){
				NUM_BUTTONS++;
				bList[mbIter->second.indForWeb] = { mbIter->second.code, mbIter->second.name };		
			}
			else if ( mbIter->second.typeWeb == 2){
				NUM_RANGES++;
				rList[mbIter->second.indForWeb] = { mbIter->second.code, mbIter->second.min, mbIter->second.max, mbIter->second.name};
			}			
		} 
		// if ( mbIter->second.pollitra > 0){
			// yo.savePollitre[i] = { mbIter->first, mbIter->second.pollitra};
		// }
    }	
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
		
		select { width: 350px; background: #181E28;  border: 0; border-radius: 5px; color: #E1E1E1; padding: 8px 16px; margin: 10px; font-size: 1.1em; font-family: 'Microsoft JhengHei UI', 'Open Sans', Arial, sans-serif;}    
        option.default    { color: #3CB371;, font-weight: 600;}
        option.opt-active { background: #21252B;  font-weight: 600;}

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
	<script>
		const wave = document.querySelectorAll('.wave');
		function buttonClick( element) {
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
			var json = JSON.parse(xhr.responseText);
			var def = document.querySelector( ".default");
			if ( def){ def.classList.remove( 'default'); }		

			def = document.querySelector( ".opt-active");
			if ( def){ def.classList.remove( 'opt-active'); }			

			document.getElementById( 1066677700).value 				= json.vBrightness;
			document.getElementById( 1066677701).value 				= json.vSaturn;
			document.getElementById( 1066677702).value 				= json.vTemp;
			document.getElementById( 1066677703).value 				= json.vSpeed;
			document.querySelector( ".upser").innerHTML 			= json.vPressed;
			document.querySelector( ".Brightness-value").innerHTML 	= json.vBrightness;
			document.querySelector( ".Saturations-value").innerHTML = json.vSaturn;
			document.querySelector( ".Temperature-value").innerHTML = json.vTemp;
			document.querySelector( ".Speed-value").innerHTML 		= json.vSpeed;
			document.getElementById( "pollitre-select").value 		= json.vPollCurrent;

			wave.forEach((element) => element.classList.remove('active'));
			document.getElementById( json.vPressed).classList.add('active');	

			document.getElementById( json.vPollDefault).classList.add( 'default');  
			document.getElementById( json.vPollCurrent).classList.add( 'opt-active');

			var onoff = document.getElementById( 551489775);
			if ( json.vONOFF == 1){ onoff.classList.add('active');}
			else{ 					onoff.classList.remove('active'); }
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

		function changeOption(){     			
			wave.forEach((element) => {
				if ( element.classList.contains("active") == true) {
					var value = document.getElementById( "pollitre-select").selectedOptions[0].value;
					var xhr = new XMLHttpRequest();
					xhr.open("GET", "/select?funcID="+value+"&value="+value, true); 
					xhr.send();	  
				};
			});
		} 
		document.getElementById( "pollitre-select").addEventListener("change", changeOption);

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
		for(int i = 1; i < NUM_RANGES; i++){
			int rValue = rState(i);
			buttons += "<div><span class='textLabel'>"+rList[i].name+": </span><span class='textLabel "+rList[i].name+"-value' id=''>"+rValue+"</span>\n";
			buttons += "<input id='"+String( rList[i].code)+"' class='"+rList[i].name+"' type='range' min='"+rList[i].min+"' max='"+rList[i].max+"' step='1' value='"+rValue+"' onchange='rInput(this)';></div>\n";
		}
		
		String active = "";			
		buttons += "\n<div class='select'>\n\t<select name='pollitres' id='pollitre-select'>\n";
		for (size_t i = 0; i < NUM_POLLITR; i++){
			if ( myPal[i].name.length() > 0){				
				if ( i == mButtons[yo.lastPressed].min){ active = "selected = 'selected'";} 
				else{	active = ""; }
				buttons += "\t\t<option value='"+ String( i) +"' class='option"+ String( i) +"' id='"+ String( i) +"' "+ active +">"+ myPal[i].name +"</option>\n";
			}
		}
		buttons += "</select></div>\n";

		active = "";			
		if ( yo.ONOFF == true){ active = " active"; }
		buttons += "\n";
		buttons += "<div><button onclick='buttonClick(this)' id='"+ String( bList[1].code) +"' class='power"+ active +"'>"+ bList[1].name +"</button></div>\n";

		for ( int i = 2; i < NUM_BUTTONS; i++ ){ active = "";			
			if ( yo.lastPressed == bList[i].code){ active = " active"; }
			buttons += "<div><button onclick='buttonClick(this)' id='"+ String( bList[i].code) +"' class='wave"+ active +"'>"+ bList[i].name +"</button></div>\n";
		}
		return buttons;
	}
	return String();
}

/*
Поднимаем и настраиваем Веб-сервер ESPAsyncWebServer
*/
void webServerStartUP(){
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
			irdaServer( atoi( inputMessage01.c_str()), atoi( inputMessage02.c_str()));
		}
		request->send(200, "text/plain", "OK");
	});

	server.on("/select", HTTP_GET, [] (AsyncWebServerRequest *request) {
		if (request->hasParam(PARAM_INPUT_1)) {			
			String inputMessage01 = request->getParam(PARAM_INPUT_1)->value();				
			paletteSetActive( atoi( inputMessage01.c_str()));
		}
		request->send(200, "text/plain", "OK");
	});

	server.on("/reset", HTTP_GET, [] (AsyncWebServerRequest *request) {
		// Serial.println( "Send update to client...");
		String out = "{";
		out += "\"vBrightness\": "	+ String(yo.currentBrightness)					+", ";
		out += "\"vSaturn\": "		+ String(yo.currentSaturn)						+", ";
		out += "\"vTemp\": "		+ String(yo.currentTemp)						+", ";
		out += "\"vSpeed\": "		+ String(yo.currentSpeed)						+", ";
		out += "\"vPressed\": "		+ String(yo.lastPressed)						+", ";
		out += "\"vONOFF\": "		+ String(yo.ONOFF)								+", ";
		out += "\"vPollCurrent\": "	+ String(mButtons[yo.lastPressed].pollCurrent)	+", ";
		out += "\"vPollDefault\": "	+ String(mButtons[yo.lastPressed].pollDefault)	+" ";
		out += "}";      // 	ЗАРЯТАЯ НА ПРЕДПОСЛЕДНЕМ ЭЛЕМЕНТЕ !!! ПРОВЕРЬ!!! НЕ ЗАБУДЬ!!!!!
		request->send(200, "application/json", out);
	});

	server.begin();
}
