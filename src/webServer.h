// #include <WebServer.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "config.h"

// need replace in  												    .pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h:63
//C:\Users\vanilka\Documents\PlatformIO\Projects\220401-111103-esp32dev\.pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h
// #define TEMPLATE_PLACEHOLDER '`'
AsyncWebServer server(80);
AsyncEventSource events("/events");


byte NUM_RANGES = 1;
byte NUM_BUTTONS = 1;			
String CSS_HOLDER = "\n";		// css градиенты для select палитров
String RANGE_HOLDER = "\n";		// полоски-двигалки
String ROOT_HOLDER = ":root{\n" ;
String colorString = "";

#define PARAM_INPUT_1 "funcID"
#define PARAM_INPUT_2  "value"

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

void makeColorString(){
	colorString  = "\"vC1\": \"rgb("	+ String( yo.c1.r) + "," + String( yo.c1.g) + "," + String( yo.c1.b) + ")\", ";
	colorString += "\"vC2\": \"rgb("	+ String( yo.c2.r) + "," + String( yo.c2.g) + "," + String( yo.c2.b) + ")\", ";
	colorString += "\"vC3\": \"rgb("	+ String( yo.c3.r) + "," + String( yo.c3.g) + "," + String( yo.c3.b) + ")\", ";
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
	
	ROOT_HOLDER += "\t\t--gr0: #181E28;\n";
	ROOT_HOLDER += "\t\t--gr2: #181E28;\n";
	ROOT_HOLDER += "\t\t--gr3: linear-gradient( 90deg, #181E28, #ff0000);\n";
	ROOT_HOLDER += "\t\t--gr4: linear-gradient( 90deg, #181E28, #ff0000, #00ff00);\n";
	ROOT_HOLDER += "\t\t--gr5: linear-gradient( 90deg, #181E28, #ff0000, #00ff00, #0000ff);\n";
	
	// собираем css градиенты для выбора палитр
	String coma = "%,";
	const byte shift = 6;
	byte tcp[72]; //support gradient palettes with up to 18 entries
	for ( int i = 0; i < 58 + 11; i++){
		memcpy_P(tcp, (byte*)pgm_read_dword(&(gGradientPalettes[i])), 72);		

		CSS_HOLDER +=  "\t#ui-id-"+ String( i+ shift) +"::before{ content: ''; width: 330px; height: 5px; position: absolute; left: 10px; top: 20px; border-radius: 3px; background: var( --gr"+ String( i + shift)+")}\n";
		ROOT_HOLDER += "\t\t--gr"+ String( i+ shift) +": linear-gradient( 90deg, ";

		for ( byte ind = 0; ind < sizeof(tcp); ind+=4){			
			if ( tcp[ind] == 255){ coma = "%";}
			else{ coma = "%,";}			
			ROOT_HOLDER += "rgb("+ String( tcp[ind+1]) +","+ String( tcp[ind+2]) +","+ String( tcp[ind+3]) +") "+ String( (tcp[ind]*100/255)) + coma;
			if ( tcp[ind]== 255){ break;}
		}
		ROOT_HOLDER += ");\n";
	}
	ROOT_HOLDER += "}";

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

	if(var == "CSSPLACEHOLEDFR"){	return ROOT_HOLDER + "\n" + CSS_HOLDER;}
	if(var == "RANGEPLACEHOLDER"){ 	return RANGE_HOLDER;}
	if(var == "SELECTHOLDER"){
		String buttons = "";
		String active = "";			
		buttons += "\n<div class=\"selectZ\">\n\t<select name=\"pollitres\" id=\"pollitres\">\n";
		for (size_t i = 0; i < NUM_POLLITR; i++){
			if ( myPal[i].name.length() > 0){				
				if ( i == mButtons[yo.lastPressed].min){ active = "selected = \"selected\"";} 
				else{	active = ""; }
				if ( i == 17){
					buttons += "\t<optgroup label=\"WLEDs Pollitres(c)\">\n";
				}
				
				if ( i == mButtons[yo.lastPressed].min){ active = " selected = 'selected'";} 
				else{	active = ""; }

				buttons += "\t\t<option id='option-poll-"+ String( i) +"'"+ active +" value='"+ String( i) +"'>"+ myPal[i].name +"</option>\n";
			}
		}
		buttons += "\t</optgroup>\n</select></div>\n\n";

		return buttons;
	}

	if(var == "BUTTONPLACEHOLDER"){
		String buttons = "";
		String active = "";			
		if ( yo.ONOFF == true){ active = " active"; }
		buttons += "\n";
		// buttons += "<div><button onclick='buttonClick(this)' id='"+ String( bList[1].code) +"' class='power"+ active +"'>"+ bList[1].name +"</button></div>\n";

		for ( int i = 2; i < NUM_BUTTONS; i++ ){ active = "";			
			if ( yo.lastPressed == bList[i].code){ active = " active"; }
			buttons += "<div><button onclick='buttonClick(this)' id='"+ String( bList[i].code) +"' class='wave"+ active +"'>"+ bList[i].name +"</button></div>\n";
		}
		return buttons;
	}
	return String();
}


String webServerMakeJSON(){
	makeColorString();

	String out = "{";
	out += "\"vBrightness\": "	+ String(yo.currentBrightness)					+", ";
	out += "\"vSaturn\": "		+ String(yo.currentSaturn)						+", ";
	out += "\"vTemp\": "		+ String(yo.currentTemp)						+", ";
	out += "\"vSpeed\": "		+ String(yo.currentSpeed)						+", ";
	out += "\"vPressed\": "		+ String(yo.lastPressed)						+", ";
	out += "\"vONOFF\": "		+ String(yo.ONOFF)								+", ";
	out += "\"vUnsave\": "		+ String(yo.isNeedSaveEEPROM)					+", ";
	out += "\"vPollCurrent\": "	+ String(mButtons[yo.lastPressed].pollCurrent)	+", ";
	out += "\"vRndStyle\": "	+ yo.rndStyle 									+", ";
	out += colorString;
	out += "\"vPollDefault\": "	+ String(mButtons[yo.lastPressed].pollDefault)	+" ";
	out += "}";      // 	ЗАПЯТАЯ НА ПРЕДПОСЛЕДНЕМ ЭЛЕМЕНТЕ !!! ПРОВЕРЬ!!! НЕ ЗАБУДЬ!!!!!
	
	colorString = "";
	
	return out;
}


// запуск эвента, который сообщает клиенту, что что-то изменались и ему надо запросить данные с сервера.
void webServerUpdate(){
	String out 	 = webServerMakeJSON();
	char * chOut = new char [out.length()+1];
	strcpy ( chOut, out.c_str());

	events.send( chOut,"update", millis());
}

//передаем через эвет "рэндомные" палитры для подмены фона кнопки селектора
void webServerUnsave(){
	events.send( yo.isNeedSaveEEPROM ? "1" : "0", "unsave", millis());
}

/*Поднимаем и настраиваем Веб-сервер ESPAsyncWebServer*/
void webServerStartUP(){
	collectData();
	yo.pt2webUpdate = &webServerUpdate;
	yo.pt2webUnsave = &webServerUnsave;

	if(!SPIFFS.begin(true)){
 	 	Serial.println("An Error has occurred while mounting SPIFFS");
  		return;
	}

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    	request->send( SPIFFS, "/index.htm", String(), false, processor);
    	// request->send_P(200, "text/html", index_html, processor);
        }
    );

	server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
		if (request->hasParam( PARAM_INPUT_1)) {  
			String inputMessage01 = request->getParam( PARAM_INPUT_1)->value();
			String inputMessage02 = "0";

			if (request->hasParam( PARAM_INPUT_2)) { 
				inputMessage02 = request->getParam( PARAM_INPUT_2)->value();
				yo.againButton = atoi( inputMessage02.c_str());
			}			
			irdaServer( atoi( inputMessage01.c_str()), atoi( inputMessage02.c_str()));
		}
		request->send(200, "text/plain", "OK");
	});

	server.on("/select", HTTP_GET, [] (AsyncWebServerRequest *request) {
		if (request->hasParam( PARAM_INPUT_2)) { 
			String inputMessage02 = request->getParam( PARAM_INPUT_2)->value();
			yo.againButton = atoi( inputMessage02.c_str());
		}	
		if (request->hasParam( PARAM_INPUT_1)) {			
			String inputMessage01 = request->getParam( PARAM_INPUT_1)->value();				
			paletteSetActive( atoi( inputMessage01.c_str()));
			webServerUpdate();
		}
		request->send(200, "text/plain", "OK");
	});

	server.on("/colorset", HTTP_GET, [] (AsyncWebServerRequest *request) {
		if (request->hasParam( PARAM_INPUT_1)) {
			String inputMessage01 = request->getParam( PARAM_INPUT_1)->value();	
			
			uint8_t colors[9];
			int ind = 0;
			char * cstr = new char [inputMessage01.length()+1];
			strcpy (cstr, inputMessage01.c_str());

			char * pch;
			pch = strtok ( cstr, "-");
			while (pch != NULL)	{				
				colors[ind] = parseInt( pch);
				ind++;
				pch = strtok (NULL, "-");	
			}

			yo.c1 = CRGB( colors[0], colors[1], colors[2]);
			yo.c2 = CRGB( colors[3], colors[4], colors[5]);
			yo.c3 = CRGB( colors[6], colors[7], colors[8]);
			// makeColorString();
			webServerUpdate();
			// Serial.printf( "%d.%d.%d\n", yo.c1.r, yo.c1.g, yo.c1.b);
			// Serial.printf( "%d.%d.%d\n", colors[0], colors[1], colors[2]);
		}
		request->send(200, "text/plain", "OK");
	});

	server.on("/reset", HTTP_GET, [] (AsyncWebServerRequest *request) {		
		request->send(200, "application/json", webServerMakeJSON());		
	});

  	server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){ request->send(SPIFFS, "/style.css", "text/css"); });
  	server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){ request->send(SPIFFS, "/script.js", "text/css"); });


	events.onConnect([](AsyncEventSourceClient *client){
		if(client->lastId()){
			Serial.printf("Client reconnected! Last message ID that it gat is: %u\n", client->lastId());
		}
		//send event with message "hello!", id current millis and set reconnect delay to 1 second
		client->send( "hello!", NULL, millis(), 1000);
	});
	//HTTP Basic authentication
	// events.setAuthentication("user", "pass");
	server.addHandler(&events);
	
	server.begin();
}


/*
// request->send(200, "application/json", webServerMakeJSON());


document.documentElement.style.cssText = "--main-background-color: red";
or
document.documentElement.style.setProperty("--main-background-color", "green");
or
document.documentElement.setAttribute("style", "--main-background-color: green");


		$( "#pollitres" ).selectmenu( "open")._refreshMenu();
		$( "#pollitres" ).selectmenu( "close");

		<!-- $('#pollitres').selectmenu( "instance" )._refreshMenu(); -->

		<!-- $('#pollitres').val( 1);
		$('#pollitres').selectmenu('refresh', true); -->

	<script type="text/javascript">
   		$( "#pollitres" ).selectmenu().selectmenu( "menuWidget" ).addClass( "overflow" ); 
   		<!-- $( "#pollitres" ).selectmenu( "open"); -->

   		$('#pollitres').selectmenu('instance')._renderButtonItem = function( item ) {
  			var buttonItem = $( "<span>", {
    			"class": "ui-selectmenu-text"
  			})
  			this._setText( buttonItem, item.label );

  			var value = $('#pollitres option:selected').val();
  			
  			buttonItem.addClass( "ui-id-" + value);
			
			var xhr = new XMLHttpRequest();
			xhr.open("GET", "/select?funcID="+value+"&value="+value, true); 
			xhr.send();	  
			return buttonItem;
		}

   		$( "#pollitres111" ).selectmenu();	
	</script>

	
// const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML><html>
// <head>
// 	<meta name="viewport" content="width=device-width, initial-scale=1" charset="UTF-8">

// )rawliteral";

*/