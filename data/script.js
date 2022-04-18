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