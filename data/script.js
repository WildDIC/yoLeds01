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
	// document.querySelector( ".upser").innerHTML 			= json.vPressed;
	document.querySelector( ".Brightness-value").innerHTML 	= json.vBrightness;
	document.querySelector( ".Saturations-value").innerHTML = json.vSaturn;
	document.querySelector( ".Temperature-value").innerHTML = json.vTemp;
	document.querySelector( ".Speed-value").innerHTML 		= json.vSpeed;	
		
	var menu = $( "#pollitres" ).selectmenu( "instance" );

	if ( document.querySelector( ".ui-menu-item")) {		
		if ( menu.isOpen == false){ 
			var oldValue = $('#pollitres option:selected').val();
			// console.log( "Old value: " + $('#pollitres option:selected').val());

			if ( oldValue != json.vPollCurrent){
				// document.getElementById( "pollitres").value 		= json.vPollCurrent;
				var item = menu.menuItems.eq( json.vPollCurrent-1 ).parent( "li" );		
				menu._select( item.data( "ui-selectmenu-item" ))

				// console.log( "Current value: " + menu.focusIndex);
				// console.log( item );
			}					
			// $( "#pollitres option[value="+ json.vPollCurrent +"]" ).prop('selected', 'selected');
			// $( "#pollitres" ).trigger( "change" );
			// $( "#pollitres" ).selectmenu( "instance" )._renderButtonItem( );
			// $('#pollitres').selectmenu('refresh', true);
		} 
		var sItem = document.getElementById( "ui-id-" + json.vPollDefault);
		if ( sItem){ sItem.classList.add( 'default');  }
		var aItem = document.getElementById( "ui-id-" + json.vPollCurrent);
		if ( aItem){ aItem.classList.add( 'opt-active');}
	}
	
	// $( "#pollitres option[value="+ json.vPollCurrent +"]" ).attr('selected', 'selected');
	// $("#pollitres").val( json.vPollCurrent).change();
	// $("#pollitres").trigger("change");
	// $( "#pollitres" ).selectmenu( "option", "selected",  json.vPollCurrent ).trigger( "change" );
	//.prop('selected', true);;

	var value = $('#pollitres option:selected').val();
	document.querySelector( ".upser").innerHTML 			= "new value: " + oldValue + " -=- " + json.vPollCurrent + " -=- " + value;
	// console.log( "new value: " + json.vPollDefault + " -=- " + json.vPollCurrent + " -=- " + value);

	wave.forEach((element) => element.classList.remove('active'));

	if ( document.getElementById( json.vPressed)){
		document.getElementById( json.vPressed).classList.add('active');	
	}	

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

// function changeOption(){     			
// 	wave.forEach((element) => {
// 		if ( element.classList.contains("active") == true) {
// 			var value = document.getElementById( "pollitre-select").selectedOptions[0].value;
// 			var xhr = new XMLHttpRequest();
// 			xhr.open("GET", "/select?funcID="+value+"&value="+value, true); 
// 			xhr.send();	  
// 		};
// 	});
// } 
// document.getElementById( "pollitre-select").addEventListener("change", changeOption);

(function updateSelfDate(){ updateDate(); setTimeout(updateSelfDate, 3000);})();