// #include <WebServer.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// need replace in  												    .pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h:63
//C:\Users\vanilka\Documents\PlatformIO\Projects\220401-111103-esp32dev\.pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h
// #define TEMPLATE_PLACEHOLDER '`'
AsyncWebServer server(80);

byte NUM_RANGES = 1;
byte NUM_BUTTONS = 1;			
String CSS_HOLDER = "\n";		// css градиенты для select палитров
String RANGE_HOLDER = "\n";		// полоски-двигалки

const char* PARAM_INPUT_1 = "funcID";  
const char* PARAM_INPUT_2 = "value";

button bList[20];
range rList[10];

// возможно не стоит это выносить сыда, а вернуть в процессорку 200
int rState(int numValue){
	switch (numValue){		
		case 0: numValue = yo.currentBrightness; break;
		case 1: numValue = yo.currentSaturn; break;
		case 2: numValue = yo.currentTemp; break;		
		case 3: numValue = yo.currentSpeed; break;
	}
	return numValue;
}

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
	
	// собираем css градиенты для выбора палитр
	String coma = "%,";
	byte tcp[72]; //support gradient palettes with up to 18 entries
	for ( int i = 0; i < 58; i++){
		memcpy_P(tcp, (byte*)pgm_read_dword(&(gGradientPalettes[i])), 72);
		CSS_HOLDER += "\t#ui-id-"+ String(i+17) +", .ui-id-"+ String(i+17) +" { background: linear-gradient(to right, ";

		for ( byte ind = 0; ind < sizeof(tcp); ind+=4){			
			if ( tcp[ind] == 255){ coma = "%";}
			else{ coma = "%,";}			
			CSS_HOLDER += "rgb("+ String( tcp[ind+1]) +","+ String( tcp[ind+2]) +","+ String( tcp[ind+3]) +") "+ String( (tcp[ind]*100/255)) + coma;
			// Serial.printf( "\ti=%d, byte=%d (%d.%d.%d)\n", ind, (tcp[ind]*100/255), tcp[ind+1], tcp[ind+2], tcp[ind+3]);
			if ( tcp[ind]== 255){ break;}
		}
		CSS_HOLDER += ")}\n";
	}

	// собираем полоски-двигалки 
	for(int i = 1; i < NUM_RANGES; i++){
		int rValue = rState(i);
		RANGE_HOLDER += "<div><span class='textLabel'>"+rList[i].name+": </span><span class='textLabel "+rList[i].name+"-value' id=''>"+rValue+"</span>\n";
		RANGE_HOLDER += "<input id='"+String( rList[i].code)+"' class='"+rList[i].name+"' type='range' min='"+rList[i].min+"' max='"+rList[i].max+"' step='1' value='"+rValue+"' onchange='rInput(this)';></div>\n";
	}
}

// Replaces placeholder with button section in your web page
String processor(const String& var){
	//Serial.println(var);

	if(var == "CSSPLACEHOLEDFR"){	return CSS_HOLDER;}
	if(var == "RANGEPLACEHOLDER"){ 	return RANGE_HOLDER;}
	if(var == "SELECTHOLDER"){
		String buttons = "";
		String active = "";			
		buttons += "\n<div class=\"select\">\n\t<select name=\"pollitres\" id=\"pollitres\">\n";
		for (size_t i = 0; i < NUM_POLLITR; i++){
			if ( myPal[i].name.length() > 0){				
				if ( i == mButtons[yo.lastPressed].min){ active = "selected = \"selected\"";} 
				else{	active = ""; }
				if ( i == 17){
					buttons += "<optgroup label=\"WLEDs Pollitres(c)\">";
				}
				buttons += "\t\t<option>"+ myPal[i].name +"</option>\n";
			}
		}
		buttons += "\t</optgroup>\n</select></div>\n\n";

		// String active = "";			
		buttons += "\n<div class='select'>\n\t<select name='pollitres' id='pollitre-select'>\n";
		for (size_t i = 0; i < NUM_POLLITR; i++){
			if ( myPal[i].name.length() > 0){				
				if ( i == mButtons[yo.lastPressed].min){ active = "selected = 'selected'";} 
				else{	active = ""; }
				buttons += "\t\t<option value='"+ String( i) +"' class='option"+ String( i) +"' id='"+ String( i) +"' "+ active +">"+ myPal[i].name +"</option>\n";
			}
		}
		buttons += "</select></div>\n";
		return buttons;
	}

	if(var == "BUTTONPLACEHOLDER"){
		String buttons = "";
		String active = "";			
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

	if(!SPIFFS.begin(true)){
 	 	Serial.println("An Error has occurred while mounting SPIFFS");
  		return;
	}

// request->send(SPIFFS, "/index.htm", String(), false, processor);
// server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
//   request->send(SPIFFS, "/style.css","text/css");
// });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send( SPIFFS, "/index.htm", String(), false, processor);
    	// request->send_P(200, "text/html", index_html, processor);
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

	// Route to load style.css file
  	server.on("/style.css", 		HTTP_GET, [](AsyncWebServerRequest *request){ request->send(SPIFFS, "/style.css", 		"text/css"); });
  	// server.on("/jquery-ui.css", 	HTTP_GET, [](AsyncWebServerRequest *request){ request->send(SPIFFS, "/jquery-ui.css", 	"text/css"); });
  	// server.on("/jquery-3.6.0.js", 	HTTP_GET, [](AsyncWebServerRequest *request){ request->send(SPIFFS, "/jquery-3.6.0.js", "text/css"); });
  	// server.on("/jquery-ui.js", 		HTTP_GET, [](AsyncWebServerRequest *request){ request->send(SPIFFS, "/jquery-ui.js", 	"text/css"); });
  	server.on("/script.js", 		HTTP_GET, [](AsyncWebServerRequest *request){ request->send(SPIFFS, "/script.js", 		"text/css"); });


	server.begin();
}


/*

// const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML><html>
// <head>
// 	<meta name="viewport" content="width=device-width, initial-scale=1" charset="UTF-8">

// )rawliteral";


<div class="lstI btn fxbtn " data-id="46" onclick="setPalette(46)"> 
   <label class="radio fxchkl"> 
    <input type="radio" value="46" name="palette"> 
    <span class="radiomark"></span> 
   </label> 
      <span class="lstIname"> April Night</span> 
    <div class="lstIprev" style="background: linear-gradient(to right, rgb(1, 5, 45) 0%, rgb(1, 5, 45) 3.92157%, rgb(5, 169, 175) 9.80392%, rgb(1, 5, 45) 15.6863%, rgb(1, 5, 45) 23.9216%, rgb(45, 175, 31) 29.8039%, rgb(1, 5, 45) 35.6863%, rgb(1, 5, 45) 43.9216%, rgb(249, 150, 5) 49.8039%, rgb(1, 5, 45) 56.0784%, rgb(1, 5, 45) 63.5294%, rgb(255, 92, 0) 69.8039%, rgb(1, 5, 45) 75.6863%, rgb(1, 5, 45) 83.9216%, rgb(223, 45, 72) 89.8039%, rgb(1, 5, 45) 95.6863%, rgb(1, 5, 45) 100%);">
	</div> 
</div>

	<div class="select"> 
		<select name="pollitres" id="pollitres">
			<optgroup label="Scripts">
				<option>1</option>
				<option selected="selected">2</option>
				<option>3</option>
				<option>4</option>
				<option>5</option>
			</optgroup>
			<optgroup label="Other files">
				<option color="red">666 text</option>
				<option>7</option>
				<option>8</option>
				<option>9</option>
				<option>10</option>
				<option>11</option>
				<option>12</option>
				<option>13</option>
				<option>14</option>
				<option>15</option>
				<option>16</option>
				<option>17</option>
				<option>18</option>
				<option>19</option>
			</optgroup>
		</select>
	</div>
*/