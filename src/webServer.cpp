#include "webServer.h"

// need replace in  												    .pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h:63
//C:\Users\vanilka\Documents\PlatformIO\Projects\-=>YOUR_PROJECT_NAME<=-\.pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h
// #define TEMPLATE_PLACEHOLDER '`'  - from '%'
AsyncWebServer server(80);
AsyncEventSource events("/events");

String RANGE_HOLDER = "\n";		// полоски-двигалки
String BUTTON_HOLDER = "\n";
String SELECT_HOLDER = "";

#define PARAM_INPUT_1 "id"
#define PARAM_INPUT_2  "v"

// возможно не стоит это выносить сыда, а вернуть в процессорку 200
// int rState(int numValue)
// {
// 	switch (numValue)
// 	{		
// 		case 0: numValue = yo.currentBrightness; break;
// 		case 1: numValue = yo.currentSaturn; break;
// 		case 2: numValue = yo.currentTemp; break;		
// 		case 3: numValue = yo.currentSpeed; break;
// 	}
// 	return numValue;
// }


void collectData()
{	
	// RANGERS собираем полоски-двигалки 
	for( auto ind : a.vRanges)
	{
		if ( ind == 10000004)  // уменьшалка - ( speed)
		{
			RANGE_HOLDER += "\t\t<div class='raiser' id='raiser' style='display: none;'>\n\n";
		}
		RANGE_HOLDER += "\t\t<div><span class='" + mWaves[ind].name+"-name' id='" + mWaves[ind].name + "-name'>" + mWaves[ind].name + ": </span><span class='" + mWaves[ind].name+"-value' id=''> 0</span>\n";
		RANGE_HOLDER += "\t\t\t<input id='"+String( mWaves[ind].code) + "' class='" + mWaves[ind].name + "' type='range' min='" + mWaves[ind].min + "' max='" + mWaves[ind].max + "' step='1' value='0' onchange='rInput(this)';></div>\n";
	}	

	// BUTTONS
	for ( auto ind : a.vButton )
	{ 
		String active = ( yo.waveID == mWaves[ind].code) ? " active" : "";
		BUTTON_HOLDER += "\t<div><button onclick='buttonClick(this)' id='" + String( mWaves[ind].code) + "' class='wave"+ active + "'>" + mWaves[ind].name + "</button></div>\n";
	}

	// SELECTORS
	SELECT_HOLDER += "\n\t<div class=\"selectZ\">\n\t\t<select name=\"pollitres\" id=\"pollitres\">\n";
	for (size_t i = 1; i < yo.palTotal; i++)
	{
		if ( i == yo.palCust + 1){ SELECT_HOLDER += "\t\t<optgroup label=\"WLEDs Pollitres(c)\">\n"; }				
		String active = ( i == mWaves[yo.waveID].palCurrent) ? " selected = 'selected'" : "";
		SELECT_HOLDER += "\t\t\t<option id='option-poll-" + String( i) + "'" + active + " value='" + String( i) + "'>" + myPal[i].name + "</option>\n";
	}
	SELECT_HOLDER += "\t\t</optgroup>\n\t</select></div>\n\n";
}


/*Собираем здесь, отдельно, а в джонсоне*/
String makeColorString()
{
	String colorString   = "\"vC1\":\"rgb("	+ String( yo.c1.r) + "," + String( yo.c1.g) + "," + String( yo.c1.b) + ")\",";
	colorString 		+= "\"vC2\":\"rgb("	+ String( yo.c2.r) + "," + String( yo.c2.g) + "," + String( yo.c2.b) + ")\",";
	colorString 		+= "\"vC3\":\"rgb("	+ String( yo.c3.r) + "," + String( yo.c3.g) + "," + String( yo.c3.b) + ")\",";
	return colorString;
}


/*Делаем псевдо джонсон с текущими оперативными данными*/
String webServerMakeJSON( bool fullUp)
{
	String out = "{";
	if ( fullUp)
	{
		out += "\"vBri\":"		+ String(yo.currentBri)			+",";
		out += "\"vSat\":"		+ String(yo.currentSaturn)		+",";
		out += "\"vTmp\":"		+ String(yo.currentTemp)		+",";
		out += "\"vSpd\":"		+ String(yo.currentSpeed)		+",";
		out += "\"v010\":"		+ String( yo.AUX010) 			+",";
		out += "\"v100\":"		+ String( yo.AUX100)			+",";
		out += "\"v255\":"		+ String( yo.AUX255)			+",";
		out += "\"v355\":"		+ String( yo.AUX355)			+",";
		out += "\"v455\":"		+ String( yo.AUX455)			+",";	
		out += "\"vShift\":"	+ String( yo.shiftServ) 		+",";
		out += "\"vCandle\":"	+ String( yo.candleServ) 		+",";
		out += makeColorString();
	}
	
	out += "\"vIsFull\":"	+ String( fullUp) 				+",";
	out += "\"vIsShft\":"	+ String( yo.ishifter) 			+",";
	out += "\"vIsCndl\":"	+ String( yo.iscandle) 			+",";
	out += "\"vUnsave\":"	+ String(yo.isNeedSaveEEPROM)	+",";
	out += "\"vStyle\":"	+ yo.rndStyle 					+",";
	out += "\"vPCur\":"		+ String(yo.palCurrent)			+",";
	out += "\"vONOFF\":"	+ String(yo.ONOFF)				+",";
	out += "\"vPressed\":"	+ String(yo.waveID)				+",";
	out += "\"vPDef\":"		+ String(yo.palDefault)			+" ";
	out += "}";      // 	ЗАПЯТАЯ НА ПРЕДПОСЛЕДНЕМ ЭЛЕМЕНТЕ !!! ПРОВЕРЬ!!! НЕ ЗАБУДЬ!!!!!
	return out;
}


/*Делаем псевдо джонсон с текущими оперативными данными*/
String webServerMakeJSONForRanges()
{
	String out = "{";
	out += "\"n010\":\""	+ String( yo.name010)			+"\",";
	out += "\"n100\":\""	+ String( yo.name100)			+"\",";
	out += "\"n255\":\""	+ String( yo.name255)			+"\",";
	out += "\"n355\":\""	+ String( yo.name355)			+"\",";
	out += "\"n455\":\""	+ String( yo.name455)			+"\",";
	out += "\"nSpd\":\""	+ String( yo.nameSpeed) 		+"\" ";
	out += "}";      // 	ЗАПЯТАЯ НА ПРЕДПОСЛЕДНЕМ ЭЛЕМЕНТЕ !!! ПРОВЕРЬ!!! НЕ ЗАБУДЬ!!!!!
	return out;
}


void webServerUpColor()
{
	String out = "{";
	out += makeColorString();
	out += "\"v\":\"empty\"";
	out += "}";      // 	ЗАПЯТАЯ НА ПРЕДПОСЛЕДНЕМ ЭЛЕМЕНТЕ !!! ПРОВЕРЬ!!! НЕ ЗАБУДЬ!!!!!

	char * chOut = new char [out.length()+1];
	strcpy ( chOut, out.c_str());
	events.send( chOut, "upRange", millis());
}


void webServerUpRange( const String& name, uint8_t value)
{
	String out = "{";
	out += "\"name\":\""+ name				+"\",";
	out += "\"value\":"	+ String( value)	;
	out += "}";      // 	ЗАПЯТАЯ НА ПРЕДПОСЛЕДНЕМ ЭЛЕМЕНТЕ !!! ПРОВЕРЬ!!! НЕ ЗАБУДЬ!!!!!

	char * chOut = new char [out.length()+1];
	strcpy ( chOut, out.c_str());
	
	events.send( chOut, "upRange", millis());
}


/**/
void webServerUpRanges()
{
	String out 	 = webServerMakeJSONForRanges();
	char * chOut = new char [out.length()+1];
	strcpy ( chOut, out.c_str());
	events.send( chOut, "haveRanges", millis());
	// events.send( "NULL", "haveRanges", millis());

	yo.isNeedUpWeb = false;
}


/* запуск эвента, который сообщает клиенту, что что-то изменались и пихаем в тексте псевдо-джсон с данными для разбора в скрипте.
Так делать плохо, надо как-то по нормаольному, с запросом данных, а не через текст слать...*/
void webServerUpdate()
{
	String out 	 = webServerMakeJSON( false);
	char * chOut = new char [out.length()+1];
	strcpy ( chOut, out.c_str());
	events.send( chOut, "haveNewData", millis());
	// events.send( "NULL", "haveNewData", millis());
}


//передаем через эвет состояние сохранености в еепром изменений
void webServerUnsave()
{
	events.send( yo.isNeedSaveEEPROM ? "1" : "0", "unsave", millis());
}


// Replaces placeholder with button section in your web page
String webServerProcessor(const String& var)
{
	if(var == "CSSPLACEHOLEDFR")	return PALL_HOLDER;
	if(var == "RANGEPLACEHOLDER") 	return RANGE_HOLDER;
	if(var == "BUTTONPLACEHOLDER")  return BUTTON_HOLDER;
	if(var == "SELECTHOLDER")		return SELECT_HOLDER;
	return String();
}


/*Поднимаем и настраиваем Веб-сервер ESPAsyncWebServer*/
void webServerStartUP()
{
	if(!SPIFFS.begin(true))
	{
 	 	Serial.println("webs| An Error has occurred while mounting SPIFFS");
  		return;
	}
	
	collectData();
	yo.pt2webUpdate 	= &webServerUpdate;
	yo.pt2webUnsave 	= &webServerUnsave;
	yo.pt2webUpColor	= &webServerUpColor;
	yo.pt2webUpRange 	= &webServerUpRange;
	yo.pt2webUpRanges 	= &webServerUpRanges;


	server.on( "/", 			HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/index.htm", "text/html", false, webServerProcessor); });
  	server.on( "/style.css",	HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/style.css", "text/css"); });
  	server.on( "/script.js",	HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/script.js", "text/css"); });
  	server.on( "/favicon.ico",	HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/favicon.ico", "image/vnd.microsoft.icon"); });

	server.on( "/giveRanger",	HTTP_GET, [](AsyncWebServerRequest *request){ request->send( 200,    "application/json", webServerMakeJSONForRanges());});
	// server.on("/json", 		HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/config.txt", "application/json"); });
	server.on( "/save",     	HTTP_GET, [](AsyncWebServerRequest *request){ yo.EEPROMsaveTime = 0; 				request->send(200, "text/plain", "Saved.");});
	server.on( "/candle",   	HTTP_GET, [](AsyncWebServerRequest *request){ yo.iscandle = !yo.iscandle; 			request->send(200, "text/plain", "Candle.");});
	server.on( "/shift",   		HTTP_GET, [](AsyncWebServerRequest *request){ yo.ishifter = !yo.ishifter; 			request->send(200, "text/plain", "Shifter.");});
	server.on( "/power",    	HTTP_GET, [](AsyncWebServerRequest *request){ led.powerONOFF();	webServerUpdate(); 	request->send(200, "text/plain", "Powered.");});


	server.on( "/giveData",		HTTP_GET, [](AsyncWebServerRequest *request)
	{ 
		bool fullUp = false;		
		if (request->hasParam( "full")) fullUp = true; // request->getParam( PARAM_INPUT_2)->value();
		request->send( 200,    "application/json", webServerMakeJSON( fullUp));
	});


	server.on( "/update", 		HTTP_GET, [](AsyncWebServerRequest *request) 
	{
		if (request->hasParam( PARAM_INPUT_1)) 
		{  
			String inputMessage01 = request->getParam( PARAM_INPUT_1)->value();
			String inputMessage02 = "0";

			if (request->hasParam( PARAM_INPUT_2)) 
			{ 
				inputMessage02 = request->getParam( PARAM_INPUT_2)->value();
				yo.againButton = atoi( inputMessage02.c_str());
			}			
			irdaServer( atoi( inputMessage01.c_str()), atoi( inputMessage02.c_str()));
		}
		request->send(200, "text/plain", "OK");
	});


	server.on("/select", HTTP_GET, [] (AsyncWebServerRequest *request) 
	{
		if (request->hasParam( PARAM_INPUT_2)) 
		{ 
			String inputMessage02 = request->getParam( PARAM_INPUT_2)->value();
			yo.againButton = atoi( inputMessage02.c_str());
		}	
		if (request->hasParam( PARAM_INPUT_1)) 
		{			
			String inputMessage01 = request->getParam( PARAM_INPUT_1)->value();	
			paletteSetActive( atoi( inputMessage01.c_str()), true);
			webServerUpdate();
		}
		request->send(200, "text/plain", "OK");
	});


	server.on("/colorset", HTTP_GET, [] (AsyncWebServerRequest *request) 
	{
		if (request->hasParam( PARAM_INPUT_1)) 
		{
			String inputMessage01 = request->getParam( PARAM_INPUT_1)->value();	
			
			uint8_t colors[9];
			int ind = 0;
			char * cstr = new char [inputMessage01.length()+1];
			strcpy( cstr, inputMessage01.c_str());

			char * pch;
			pch = strtok( cstr, "-");
			while ( pch != NULL)	
			{				
				colors[ind] = parseInt( pch);
				ind++;
				pch = strtok( NULL, "-");	
			}

			led.setColors( CRGB( colors[0], colors[1], colors[2]), CRGB( colors[3], colors[4], colors[5]), CRGB( colors[6], colors[7], colors[8]));
			paletteSetActive( yo.palCurrent, false);
			webServerUpdate();								// todo check non color pall
		}
		request->send(200, "text/plain", "OK");
	});



	events.onConnect([](AsyncEventSourceClient *client)
	{
		if(client->lastId())
		{
			Serial.printf("webs| Client reconnected! Last message ID that it gat is: %u\n", client->lastId());
		}
		//send event with message "hello!", id current millis and set reconnect delay to 1 second
		client->send( "Цarь vo dvorцa!!", NULL, millis(), 1000);
	});
	//HTTP Basic authentication
	// events.setAuthentication("user", "pass");
	server.addHandler(&events);
	
	server.begin();
}


