#ifndef __WEBSERV_H
#define __WEBSERV_H

#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "config.h"
#include "palettes.h"
#include "leds.h"
#include "animeClass.h"
// #include "irda.h"

void webServerUpdate();
void webServerUnsave();
void webServerStartUP();
void webServerUpRange( const String &name, uint8_t value);

#endif

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



	// собираем css градиенты для выбора палитр
	// byte tcp[72]; //support gradient palettes with up to 18 entries
	
	// for ( int i = yo.palRandom + 1; i < yo.palTotal; i++) 						// ЗДЕСЯ ИНДЕКСЫ ПАЛИТР МЕНЯТЬ КОЛИЧЕСТВО РАЗНЫЕ НАДО МНОГО СИЛЬНО  + ТАКОЕ в ПАЛЛЕТЕ++ ( 23)
	// {   																		// CSS_HOLDER теперь в css -=> "div[id^="ui-id-"]" and js -=> var items = document.querySelectorAll(".ui-menu-item-wrapper");
		
		
		// memcpy_P(tcp, (byte*) pgm_read_dword( &( ps.pals)), 72);		
		
		// Serial.println( ps.name);

		// for ( byte ind = 0; ind < sizeof( tcp); ind += 4)
		// {
		// 	String coma = ( tcp[ind] == 255) ? "%" : "%,";
		// 	ROOT_HOLDER += "rgb("+ String( tcp[ind+1]) +","+ String( tcp[ind+2]) +","+ String( tcp[ind+3]) +") "+ String( (tcp[ind]*100/255)) + coma;
		// 	if ( tcp[ind]== 255){ break;}
		// }
		
		// ROOT_HOLDER += ");\n";
	// }
	// ROOT_HOLDER = ROOT_HOLDER + PALL_HOLDER;
	// ROOT_HOLDER += "\t\t}";

		// memcpy_P(tcp, (byte*)pgm_read_dword(&(gGradientPalettes[i])), 72);		
		// // CSS_HOLDER теперь в css -=> "div[id^="ui-id-"]" and js -=> var items = document.querySelectorAll(".ui-menu-item-wrapper");
		// ROOT_HOLDER += "\t\t\t--gr"+ String( i + yo.palRandom) +": linear-gradient( 90deg, ";

		// for ( byte ind = 0; ind < sizeof( tcp); ind += 4)
		// {
		// 	String coma = ( tcp[ind] == 255) ? "%" : "%,";
		// 	ROOT_HOLDER += "rgb("+ String( tcp[ind+1]) +","+ String( tcp[ind+2]) +","+ String( tcp[ind+3]) +") "+ String( (tcp[ind]*100/255)) + coma;
		// 	if ( tcp[ind]== 255){ break;}
		// }
