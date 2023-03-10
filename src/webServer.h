// #include <WebServer.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "config.h"

extern void powerONOFF();

// need replace in  												    .pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h:63
//C:\Users\vanilka\Documents\PlatformIO\Projects\-=>YOUR_PROJECT_NAME<=-\.pio\libdeps\IR Test with FastLED 01\ESPAsyncWebServer-esphome\src\WebResponseImpl.h
// #define TEMPLATE_PLACEHOLDER '`'  - from '%'
AsyncWebServer server(80);
AsyncEventSource events("/events");


byte NUM_RANGES = 1;
byte NUM_BUTTONS = 1;			
String RANGE_HOLDER = "\n";		// полоски-двигалки
String ROOT_HOLDER = ":root{\n" ;

#define PARAM_INPUT_1 "funcID"
#define PARAM_INPUT_2  "value"

button bList[25];
range rList[10];

// возможно не стоит это выносить сыда, а вернуть в процессорку 200
int rState(int numValue)
{
	switch (numValue)
	{		
		case 0: numValue = yo.currentBrightness; break;
		case 1: numValue = yo.currentSaturn; break;
		case 2: numValue = yo.currentTemp; break;		
		case 3: numValue = yo.currentSpeed; break;
	}
	return numValue;
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
String webServerMakeJSON()
{
	String out = "{";
	out += "\"vBri\":"		+ String(yo.currentBrightness)	+",";
	out += "\"vSat\":"		+ String(yo.currentSaturn)		+",";
	out += "\"vTmp\":"		+ String(yo.currentTemp)		+",";
	out += "\"vSpd\":"		+ String(yo.currentSpeed)		+",";
	out += "\"vPressed\":"	+ String(yo.lastPressed)		+",";
	out += "\"vONOFF\":"	+ String(yo.ONOFF)				+",";
	out += "\"vUnsave\":"	+ String(yo.isNeedSaveEEPROM)	+",";
	out += "\"vPCur\":"		+ String(yo.pollCurrent)		+",";
	out += "\"vStyle\":"	+ yo.rndStyle 					+",";
	out += "\"vCndl\":"		+ String( yo.candle) 			+",";
	out += "\"vIsCndl\":"	+ String( yo.iscandle) 			+",";
	out += "\"v010\":"		+ String( yo.AUX010) 			+",";
	out += "\"v100\":"		+ String( yo.AUX100)			+",";
	out += "\"v255\":"		+ String( yo.AUX255)			+",";
	out += "\"v355\":"		+ String( yo.AUX355)			+",";
	out += "\"v455\":"		+ String( yo.AUX455)			+",";
	out += "\"n010\":\""	+ String( yo.name010)			+"\",";
	out += "\"n100\":\""	+ String( yo.name100)			+"\",";
	out += "\"n255\":\""	+ String( yo.name255)			+"\",";
	out += "\"n355\":\""	+ String( yo.name355)			+"\",";
	out += "\"n455\":\""	+ String( yo.name455)			+"\",";
	out += "\"nSpd\":\""	+ String( yo.nameSpeed) 		+"\",";
	out += makeColorString();
	out += "\"vPDef\":"		+ String(yo.pollDefault)		+" ";
	out += "}";      // 	ЗАПЯТАЯ НА ПРЕДПОСЛЕДНЕМ ЭЛЕМЕНТЕ !!! ПРОВЕРЬ!!! НЕ ЗАБУДЬ!!!!!
	return out;
}


void collectData()
{	
	mbIter = mWaves.begin();
	for (int i = 0; mbIter != mWaves.end(); mbIter++, i++) 
	{		
		mbIter->second.code = mbIter->first;
		if ( mbIter->second.indForWeb)
		{
			if ( mbIter->second.typeWeb == 1)
			{
				NUM_BUTTONS++;
				bList[mbIter->second.indForWeb] = { mbIter->second.code, mbIter->second.name };		
			}
			else if ( mbIter->second.typeWeb == 2)
			{
				NUM_RANGES++;
				rList[mbIter->second.indForWeb] = { mbIter->second.code, mbIter->second.min, mbIter->second.max, mbIter->second.name};
			}			
		} 
    }	
	
	ROOT_HOLDER += "\t\t\t--gr0: #181E28;\n";
	ROOT_HOLDER += "\t\t\t--gr2: #181E28;\n";
	ROOT_HOLDER += "\t\t\t--gr3: linear-gradient( 90deg, #181E28, #ff0000);\n";
	ROOT_HOLDER += "\t\t\t--gr4: linear-gradient( 90deg, #181E28, #ff0000, #00ff00);\n";
	ROOT_HOLDER += "\t\t\t--gr5: linear-gradient( 90deg, #181E28, #ff0000, #00ff00, #0000ff);\n";
	ROOT_HOLDER += "\t\t\t--gr6: #181E28;\n";
	ROOT_HOLDER += "\t\t\t--gr7: linear-gradient( 90deg, #181E28, #ff0000);\n";
	ROOT_HOLDER += "\t\t\t--gr8: linear-gradient( 90deg, #181E28, #ff0000, #0000ff);\n";
	

	// собираем css градиенты для выбора палитр
	byte tcp[72]; //support gradient palettes with up to 18 entries
	
	for ( int i = 0; i < 58 + 11; i++){   // ЗДЕСЯ ИНДЕКСЫ ПАЛИТР МЕНЯТЬ КОЛИЧЕСТВО РАЗНЫЕ НАДО МНОГО СИЛЬНО  + ТАКОЕ в ПАЛЛЕТЕ++ ( 23)

		memcpy_P(tcp, (byte*)pgm_read_dword(&(gGradientPalettes[i])), 72);		
		// CSS_HOLDER теперь в css -=> "div[id^="ui-id-"]" and js -=> var items = document.querySelectorAll(".ui-menu-item-wrapper");
		ROOT_HOLDER += "\t\t\t--gr"+ String( i + yo.lastCustPal) +": linear-gradient( 90deg, ";

		for ( byte ind = 0; ind < sizeof( tcp); ind += 4)
		{
			String coma = ( tcp[ind] == 255) ? "%" : "%,";
			ROOT_HOLDER += "rgb("+ String( tcp[ind+1]) +","+ String( tcp[ind+2]) +","+ String( tcp[ind+3]) +") "+ String( (tcp[ind]*100/255)) + coma;
			if ( tcp[ind]== 255){ break;}
		}
		ROOT_HOLDER += ");\n";
	}
	ROOT_HOLDER += "\t\t}";


	// RANGERS собираем полоски-двигалки 
	for(int i = 1; i < NUM_RANGES; i++)
	{
		int rValue = rState(i);
		// уменьшалка
		if ( i == 2) 
		{
			RANGE_HOLDER += "\t\t<div class='raiser' id='raiser' style='display: none;'>\n\n";
		}
		RANGE_HOLDER += "\t\t<div><span class='textLabel "+rList[i].name+"-name' id='"+rList[i].name+"-name'>"+rList[i].name+": </span><span class='textLabel "+rList[i].name+"-value' id=''>"+rValue+"</span>\n";
		RANGE_HOLDER += "\t\t\t<input id='"+String( rList[i].code)+"' class='"+rList[i].name+"' type='range' min='"+rList[i].min+"' max='"+rList[i].max+"' step='1' value='"+rValue+"' onchange='rInput(this)';></div>\n";
	}	
}


// Replaces placeholder with button section in your web page
String processor(const String& var)
{
	if(var == "CSSPLACEHOLEDFR"){	return ROOT_HOLDER ;}
	if(var == "RANGEPLACEHOLDER"){ 	return RANGE_HOLDER;}
	if(var == "SELECTHOLDER")
	{
		String buttons = "";
		buttons += "\n\t<div class=\"selectZ\">\n\t\t<select name=\"pollitres\" id=\"pollitres\">\n";
		for (size_t i = 0; i < NUM_POLLITR; i++)
		{
			if ( myPal[i].name.length() > 0)
			{		
				if ( i == yo.lastCustPal + 11){ buttons += "\t\t<optgroup label=\"WLEDs Pollitres(c)\">\n"; }				
				String active = ( i == mWaves[yo.lastPressed].min) ?" selected = 'selected'" : "";
				buttons += "\t\t\t<option id='option-poll-"+ String( i) +"'"+ active +" value='"+ String( i) +"'>"+ myPal[i].name +"</option>\n";
			}
		}
		buttons += "\t\t</optgroup>\n\t</select></div>\n\n";
		return buttons;
	}

	// BUTTONRS replacer
	if(var == "BUTTONPLACEHOLDER")
	{
		String buttons = "\n";

		for ( int i = 2; i < NUM_BUTTONS; i++ )
		{ 
			String active = ( yo.lastPressed == bList[i].code) ? " active" : "";
			buttons += "\t<div><button onclick='buttonClick(this)' id='"+ String( bList[i].code) +"' class='wave"+ active +"'>"+ bList[i].name +"</button></div>\n";
		}
		return buttons;
	}
	return String();
}


/* запуск эвента, который сообщает клиенту, что что-то изменались и пихаем в тексте псевдо-джсон с данными для разбора в скрипте.
Так делать плохо, надо как-то по нормаольному, с запросом данных, а не через текст слать...*/
void webServerUpdate()
{
	String out 	 = webServerMakeJSON();
	char * chOut = new char [out.length()+1];
	strcpy ( chOut, out.c_str());
	events.send( chOut, "update", millis());
}

//передаем через эвет состояние сохранености в еепром изменений
void webServerUnsave()
{
	events.send( yo.isNeedSaveEEPROM ? "1" : "0", "unsave", millis());
}

/*Поднимаем и настраиваем Веб-сервер ESPAsyncWebServer*/
void webServerStartUP()
{
	collectData();
	yo.pt2webUpdate = &webServerUpdate;
	yo.pt2webUnsave = &webServerUnsave;

	if(!SPIFFS.begin(true))
	{
 	 	Serial.println("An Error has occurred while mounting SPIFFS");
  		return;
	}
	
	server.on("/", 			HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/index.htm", String(), false, processor); });
  	server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/style.css", "text/css"); });
  	server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/script.js", "text/css"); });
	server.on("/reset", 	HTTP_GET, [](AsyncWebServerRequest *request){ request->send( 200,    "application/json", webServerMakeJSON());});
	// server.on("/json", 		HTTP_GET, [](AsyncWebServerRequest *request){ request->send( SPIFFS, "/config.txt", "application/json"); });
	server.on( "/save",     HTTP_GET, [](AsyncWebServerRequest *request){ yo.EEPROMsaveTime = 0; 			request->send(200, "text/plain", "Saved.");});
	server.on( "/candle",   HTTP_GET, [](AsyncWebServerRequest *request){ yo.iscandle = !yo.iscandle; 		request->send(200, "text/plain", "Candle.");});
	server.on( "/power",    HTTP_GET, [](AsyncWebServerRequest *request){ powerONOFF();	webServerUpdate(); 	request->send(200, "text/plain", "Powered.");});

	server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) 
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
			strcpy (cstr, inputMessage01.c_str());

			char * pch;
			pch = strtok ( cstr, "-");
			while (pch != NULL)	
			{				
				colors[ind] = parseInt( pch);
				ind++;
				pch = strtok (NULL, "-");	
			}

			setColors( CRGB( colors[0], colors[1], colors[2]), CRGB( colors[3], colors[4], colors[5]), CRGB( colors[6], colors[7], colors[8]));
			paletteSetActive( yo.pollCurrent, false);
			webServerUpdate();
		}
		request->send(200, "text/plain", "OK");
	});


	events.onConnect([](AsyncEventSourceClient *client)
	{
		if(client->lastId())
		{
			Serial.printf("Client reconnected! Last message ID that it gat is: %u\n", client->lastId());
		}
		//send event with message "hello!", id current millis and set reconnect delay to 1 second
		client->send( "Цarь vo dvorцa!!", NULL, millis(), 1000);
	});
	//HTTP Basic authentication
	// events.setAuthentication("user", "pass");
	server.addHandler(&events);
	
	server.begin();
}


		// CSS_HOLDER +=  "\t\t#ui-id-"+ String( i + yo.lastCustPal) +"::before{ background: var( --gr"+ String( i + yo.lastCustPal)+")}\n";
		// CSS_HOLDER +=  "\t\t#ui-id-"+ String( i + yo.lastCustPal) +"::before{ content: ''; width: 330px; height: 5px; position: absolute; left: 10px; top: 20px; border-radius: 3px; background: var( --gr"+ String( i + yo.lastCustPal)+")}\n";

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