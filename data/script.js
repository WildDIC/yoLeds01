//console.log( [...document.querySelector("#pollitres").options].map( opt => opt.value ) );
var localSelect = true;


$( function() {
	// $( "#pollitres" ).selectmenu( "instance" )._refreshMenu();
	$( "#pollitres" ).selectmenu( "open");
	$( "#pollitres" ).selectmenu( "close");

	document.querySelectorAll(".ui-menu-item-wrapper").forEach( function( item, i) {
		if ( i >= 8 ){
			item.style.setProperty("--bcolor", "var( --gr" + ( i + 1) + ")")	// вместо CSS_HOLDER из webServer.h
			// item.style.background = "var( --gr" + i + ")";
		}
	});
} );

$( "#pollitres" ).selectmenu().selectmenu( "menuWidget" ).addClass( "overflow" ); 


// эвенты селект-меню
$( "#pollitres" ).selectmenu({
	change: function( event, ui ) {
		// console.log( "Change event. " + event.originalEvent + " LocalSelect =" + localSelect);
		var value = 0;		
		if ( event.originalEvent) { value = 1} 						// если сделаи выбор палитры мышкой сами
		
		if ( localSelect){											// только, елси селект был сделан с мышки на клиенте, фэлсится, при получении ресета от сервера
			var select = $('#pollitres option:selected').val();
			var xhr = new XMLHttpRequest();
			xhr.open("GET", "/select?id="+select+ "&v=" +value, true); 
			xhr.send();	  

			// if ( event.originalEvent) { updateDate();}					// если сделаи выбор палитры мышкой сами, то надо обновить цвет кнопки, стригерив "ресет" 
		}
		localSelect = true;
	}
});


// добавляем листенер эвентов от сервера
if (!!window.EventSource) {
	var source = new EventSource('/events');

	source.addEventListener('open', function(e) { 
		requestNewData( true); 	
		requestNewRanger( ); 
		console.log("Events Connected. Несите medovuha!"); }, false);
	source.addEventListener('haveNewData', 	function(e) { reseter( e.data);   }, false);
	source.addEventListener('haveRanges', 	function(e) { setRanges( e.data); }, false);
	source.addEventListener('upRange', 		function(e) { setRange( e.data);  }, false);
	source.addEventListener('unsave', 		function(e) { unsave( e.data);    }, false);
	source.addEventListener('error',  		function(e) { if (e.target.readyState != EventSource.OPEN) { console.log("Events Disconnected"); } }, false); 
	// source.addEventListener('update', 		function(e) { reseter( e.data); }, false);
}


function raiserFunc( elemnt, raiser){
	var x = document.getElementById( raiser);

	if (x.style.display === "none") {
		x.style.display = "block";
		elemnt.classList.add( 'unrise');
	} else {
		x.style.display = "none";
		elemnt.classList.remove( 'unrise');
	}
}


function unsave( request){
	if ( request == true){ 
		document.querySelector(".isave").classList.add( 'unsave');
	}
	else{ 			    
		document.querySelector(".isave").classList.remove('unsave'); 
	}
}


function pButtonClick( element) {
	// var value = "&value=0"; 													// 0 - если кнопку активности нажал новую ты, обновления палитры что бы не обновлять случайные цвета
	element.classList.toggle("active");
	// if ( element.classList.contains("active")) { value = "&value=1"; };		// 1 - нажал нопку опять ты для цветов обновления случайных
	
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/power", true); 
	xhr.send();
}


function sButtonClick( element) {
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/save", true); 
	xhr.send();
}


function cButtonClick( element) {
	element.classList.toggle("active");
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/candle", true); 
	xhr.send();
}

function fButtonClick( element) {
	element.classList.toggle("active");
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/shift", true); 
	xhr.send();
}



function buttonClick( element) {
	var value = "&v=0"; 													// 0 - если кнопку активности нажал новую ты, обновления палитры что бы не обновлять случайные цвета
	// if ( element.classList.contains("powerbutton")) { element.classList.toggle("active"); };
	if ( element.classList.contains("active")) { value = "&v=1"; };			// 1 - нажал нопку опять ты для цветов обновления случайных
	
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/update?id="+element.id + value, true); 
	xhr.send();
}



// двигалка ранжеров: посылаем на сервер новые данные
function rInput( element) {
	var value = element.value;
	var classValue = '.' + element.className + '-value';
	var target = document.querySelector( classValue);
	target.innerHTML = value;

	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/update?id="+element.id+"&v="+value, true); 
	xhr.send();
}  



function setRange( data){
	var json = JSON.parse( data);
	
	if ( json.name)
	{
		document.querySelector( "." + json.name).value					= json.value;
		document.querySelector( "." + json.name + "-value").innerHTML 	= json.value;	
	}

	if ( json.vC1){ var c1 = new iro.Color( json.vC1); colorPicker.colors[0].set(c1);}
	if ( json.vC2){ var c2 = new iro.Color( json.vC2); colorPicker.colors[1].set(c2);}
	if ( json.vC3){ var c3 = new iro.Color( json.vC3); colorPicker.colors[2].set(c3);}
}


function setRanges( data){
	var json = JSON.parse( data);

	document.querySelector( ".AUX010-name").innerHTML 		= json.n010 + ": ";
	document.querySelector( ".AUX100-name").innerHTML	 	= json.n100 + ": ";
	document.querySelector( ".AUX255-name").innerHTML	 	= json.n255 + ": ";
	document.querySelector( ".AUX355-name").innerHTML	 	= json.n355 + ": ";
	document.querySelector( ".AUX455-name").innerHTML	 	= json.n455 + ": ";
	document.querySelector( ".Speed-name" ).innerHTML	 	= json.nSpd + ": ";
}



const wave = document.querySelectorAll('.wave');
// обновление данных на странице
function reseter( data){
	var json = JSON.parse( data);
	var item = document.querySelector( ".default"); 		// очищаем класс в списке палитр
	if ( item){ item.classList.remove( 'default'); }		

	item = document.querySelector( ".opt-active");			// очищаем класс в списке палитр
	if ( item){ item.classList.remove( 'opt-active'); }			

	if ( json.vIsFull == true)
	{
		document.querySelector( ".Brightness").value			= json.vBri;
		document.querySelector( ".Speed").value					= json.vSpd;
		document.querySelector( ".Temperature").value 			= json.vTmp;
		document.querySelector( ".Saturations").value 			= json.vSat;	
		document.querySelector( ".AUX010").value 				= json.v010;
		document.querySelector( ".AUX100").value 				= json.v100;
		document.querySelector( ".AUX255").value 				= json.v255;
		document.querySelector( ".AUX355").value 				= json.v355;
		document.querySelector( ".AUX455").value 				= json.v455;
		document.querySelector( ".shift").valuue	 			= json.vShift;	
		document.querySelector( ".candle").value		 		= json.vCandle;	

		document.querySelector( ".Brightness-value").innerHTML 	= json.vBri;
		document.querySelector( ".Saturations-value").innerHTML = json.vSat;
		document.querySelector( ".Temperature-value").innerHTML = json.vTmp;
		document.querySelector( ".Speed-value").innerHTML 		= json.vSpd;		
		document.querySelector( ".AUX010-value").innerHTML 		= json.v010;	
		document.querySelector( ".AUX100-value").innerHTML	 	= json.v100;	
		document.querySelector( ".AUX255-value").innerHTML	 	= json.v255;	
		document.querySelector( ".AUX355-value").innerHTML	 	= json.v355;	
		document.querySelector( ".AUX455-value").innerHTML	 	= json.v455;	
		document.querySelector( ".shift-value").innerHTML	 	= json.vShift;	
		document.querySelector( ".candle-value").innerHTML	 	= json.vCandle;	

		if ( json.vC1){ var c1 = new iro.Color( json.vC1); colorPicker.colors[0].set(c1);}
		if ( json.vC2){ var c2 = new iro.Color( json.vC2); colorPicker.colors[1].set(c2);}
		if ( json.vC3){ var c3 = new iro.Color( json.vC3); colorPicker.colors[2].set(c3);}
	}

	unsave( json.vUnsave);
	
	if ( json.vStyle)  { document.documentElement.setAttribute("style", json.vStyle);} 	// обновляем переменные стиля кнопки селекта для "случайных" палитр

	item = document.getElementById( "pollitres-button"); 						// обновляем стиля для кнопки выбора палитр
	if ( json.vPCur > 1) {			
		item.style.background = "var(--gr"+json.vPCur+")";
	} else {
		item.style.background = "var(--gr0)";
	}

	var menu = $( "#pollitres" ).selectmenu( "instance" ); 						// ссылка на обьект джиквери-меню
	if ( document.querySelector( ".ui-menu-item")) {		
		if ( menu.isOpen == false){ 
			if ( $('#pollitres option:selected').val() != json.vPCur){			// текущий елемент меню не равен серверному
				localSelect = false;											// фэлсим, что бы при выполнении селекта оно не выслалось обратно на сервер
				item = menu.menuItems.eq( json.vPCur-1 ).parent( "li" );		// пытаемся установить выбранный елемент меню с сервера активным на странице
				menu._select( item.data( "ui-selectmenu-item" ))				// и обновить его в меню
			}					
		} 
		var sItem = document.getElementById( "ui-id-" + json.vPDef); 			// устанавливаем класс в списке палитр
		if ( sItem){ sItem.classList.add( 'default');  }
		var aItem = document.getElementById( "ui-id-" + json.vPCur); 			// устанавливаем класс в списке палитр
		if ( aItem){ aItem.classList.add( 'opt-active');}
	}

	wave.forEach((element) => element.classList.remove('active'));				// убираем активную кнопку
	item = document.getElementById( json.vPressed);								// ставим новую активную кнопку
	if ( item){	item.classList.add('active');}	

	item = document.getElementById( 'ishift');									// кнопка ыршаеf YCD pyufxtybq
	if ( json.vIsShft && item){ item.classList.add('active');}
	else{ 						item.classList.remove('active'); }

	item = document.getElementById( 'icandl');									// кнопка тряски свечки
	if ( json.vIsCndl && item){ item.classList.add('active');}
	else{ 						item.classList.remove('active'); }

	item = document.getElementById( 551489775);									// кнопка питания он-оффф
	if ( json.vONOFF && item){ item.classList.add('active');}
	else{ 				 	   item.classList.remove('active'); }
}



// запрашиваем обновление данных с сервера и устанавливаем листенер = reseter()
function requestNewData( fullUpdate){
	var xhr = new XMLHttpRequest();
	var fullStr = "";            
	xhr.onreadystatechange = function() {
		if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) { reseter( xhr.responseText);  }
	};
	if ( fullUpdate){ fullStr = "?full=true";}

	xhr.open("GET", "/giveData" + fullStr, true); 
	xhr.send();
}


function requestNewRanger(){
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() {
		if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) { setRanges( xhr.responseText);  }
	};

	xhr.open("GET", "/giveRanger", true); 
	xhr.send();
}



///////////////////////////////////////////////////////////
//
//				COLORPICKER
//////////////////////////////////////////////////////////

const colorList 	= document.getElementById("colorList");
const activeColor 	= document.getElementById("activeColor");
var colorPicker 	= new iro.ColorPicker("#picker", 
{
	width: 220,
	colors: [
    	"rgb(255, 0, 0)",
    	"rgb(0, 255, 0)",
    	"rgb(0, 0, 255)",
  	],
  	handleRadius: 14,
	activeHandleRadius: 16,
	sliderSize: 35,
	borderWidth: 1,
	borderColor: "#fff",
});


function setColor(colorIndex){ colorPicker.setActiveColor(colorIndex);}


// https://iro.js.org/guide.html#color-picker-events
colorPicker.on(["input:end"], function()
{
	var ret = "";
	colorPicker.colors.forEach(color => 
	{
		ret += color.red + '-' + color.green + '-' + color.blue + '-';
	});
	console.log( "kek: " + ret);	
	
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/colorset?id="+ret, true); 
	xhr.send();
});


colorPicker.on(["mount", "color:change"], function()
{
  colorList.innerHTML = '';
  colorPicker.colors.forEach(color => 
  {
    const index = color.index;
    const hexString = color.hexString;	

    colorList.innerHTML += `
      	<div class="onecolor" onClick="setColor(${ index })">
        	<div class="swatch" style="background: ${ hexString }">	</div>
        	<span>
				${ hexString }<br>
				hsv[${ Math.ceil( (color.hue * 255) / 360) }, ${ Math.ceil( color.saturation * 2.55) }, ${ Math.ceil( color.value * 2.55) }]<br>
				${ color.rgbString }
			</span>
    	</div>
    `;
  });
});