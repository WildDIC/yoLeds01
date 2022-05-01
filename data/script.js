//console.log( [...document.querySelector("#pollitres").options].map( opt => opt.value ) );
var localSelect = true;

$( function() {
	// $( "#pollitres" ).selectmenu( "instance" )._refreshMenu();
	$( "#pollitres" ).selectmenu( "open");
	$( "#pollitres" ).selectmenu( "close");
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
			xhr.open("GET", "/select?funcID="+select+ "&value=" +value, true); 
			xhr.send();	  

			// if ( event.originalEvent) { updateDate();}					// если сделаи выбор палитры мышкой сами, то надо обновить цвет кнопки, стригерив "ресет" 
		}
		localSelect = true;
	}
});

// добавляем листенер эвентов от сервера
if (!!window.EventSource) {
	var source = new EventSource('/events');

	source.addEventListener('open',   function(e) { updateDate( true); console.log("Events Connected"); }, false);
	source.addEventListener('unsave', function(e) { unsave( e.data);}, false);
	source.addEventListener('update', function(e) { reseter( e.data); }, false);
	source.addEventListener('error',  function(e) { 
		if (e.target.readyState != EventSource.OPEN) { console.log("Events Disconnected"); } }, false);	
}


function unsave( request){
	if ( request == 1){ 
		document.querySelector(".unsaver0").classList.add( 'unsave');
		document.querySelector(".unsaver1").classList.add( 'unsave');
	}
	else{ 			    
		document.querySelector(".unsaver0").classList.remove('unsave'); 
		document.querySelector(".unsaver1").classList.remove('unsave'); 
	}
}

function buttonClick( element) {
	var value = "&value=0"; 													// 0 - если кнопку активности нажал новую ты, обновления палитры что бы не обновлять случайные цвета
	if ( element.classList.contains("powerbutton")) { element.classList.toggle("active"); };
	if ( element.classList.contains("active")) { value = "&value=1"; };			// 1 - нажал нопку опять ты для цветов обновления случайных
	
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/update?funcID="+element.id + value, true); 
	xhr.send();
}

// двигалка ранжеров: посылаем на сервер новые данные
function rInput( element) {
	var value = element.value;
	var classValue = '.' + element.className + '-value';
	var target = document.querySelector( classValue);
	target.innerHTML = value;

	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/update?funcID="+element.id+"&value="+value, true); 
	xhr.send();
}  

//	d.getElementById('buttonPower').className = (isOn) ? "active":"";

const wave = document.querySelectorAll('.wave');
// обновление данных на странице
function reseter( data){
	var json = JSON.parse( data);
	var item = document.querySelector( ".default"); 		// очищаем класс в списке палитр
	if ( item){ item.classList.remove( 'default'); }		

	item = document.querySelector( ".opt-active");		// очищаем класс в списке палитр
	if ( item){ item.classList.remove( 'opt-active'); }			

	document.getElementById( 10000003).value 				= json.vBrightness;
	document.getElementById( 10000004).value 				= json.vSaturn;
	document.getElementById( 10000005).value 				= json.vTemp;
	document.getElementById( 10000006).value 				= json.vSpeed;
	// document.querySelector( ".upser").innerHTML 			= json.vPressed;
	document.querySelector( ".Brightness-value").innerHTML 	= json.vBrightness;
	document.querySelector( ".Saturations-value").innerHTML = json.vSaturn;
	document.querySelector( ".Temperature-value").innerHTML = json.vTemp;
	document.querySelector( ".Speed-value").innerHTML 		= json.vSpeed;	
	unsave( json.vUnsave);

	if ( json.vRndStyle){  document.documentElement.setAttribute("style", json.vRndStyle); 	} 	// обновляем переменные стиля кнопки селекта для "случайных" палитр
	

	item = document.getElementById( "pollitres-button"); 							// обновляем стиля для кнопки выбора палитр
	if ( json.vPollCurrent > 1) {			
		item.style.background = "var(--gr"+json.vPollCurrent+")";
	} else {
		item.style.background = "var(--gr0)";
	}

	var menu = $( "#pollitres" ).selectmenu( "instance" ); 								// ссылка на обьект джиквери-меню
	if ( document.querySelector( ".ui-menu-item")) {		
		if ( menu.isOpen == false){ 
			if ( $('#pollitres option:selected').val() != json.vPollCurrent){			// текущий елемент меню не равен серверному
				localSelect = false;													// фэлсим, что бы при выполнении селекта оно не выслалось обратно на сервер
				item = menu.menuItems.eq( json.vPollCurrent-1 ).parent( "li" );			// пытаемся установить выбранный елемент меню с сервера активным на странице
				menu._select( item.data( "ui-selectmenu-item" ))						// и обновить его в меню
			}					
		} 
		var sItem = document.getElementById( "ui-id-" + json.vPollDefault); 			// устанавливаем класс в списке палитр
		if ( sItem){ sItem.classList.add( 'default');  }
		var aItem = document.getElementById( "ui-id-" + json.vPollCurrent); 			// устанавливаем класс в списке палитр
		if ( aItem){ aItem.classList.add( 'opt-active');}
	}

	wave.forEach((element) => element.classList.remove('active'));						// убираем активную кнопку

	if ( document.getElementById( json.vPressed)){
		document.getElementById( json.vPressed).classList.add('active');				// ставим новую активную кнопку
	}	

	var onoff = document.getElementById( 551489775);									// кнопка питания он-оффф
	if ( json.vONOFF == 1 && onoff){ onoff.classList.add('active');}
	else{ 					onoff.classList.remove('active'); }


	if ( json.vC1){ var c1 = new iro.Color( json.vC1); colorPicker.colors[0].set(c1);}
	if ( json.vC2){ var c2 = new iro.Color( json.vC2); colorPicker.colors[1].set(c2);}
	if ( json.vC3){ var c3 = new iro.Color( json.vC3); colorPicker.colors[2].set(c3);}
}

// запрашиваем обновление данных с сервера и устанавливаем листенер = reseter()
function updateDate( fullUpdate){
	var xhr = new XMLHttpRequest();
	var fullStr = "";            
	xhr.onreadystatechange = function() {
		if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) { 
			reseter( xhr.responseText);  
		}
	};
	if ( fullUpdate){
		fullStr = "?full=true";
	}
	xhr.open("GET", "/reset" + fullStr, true); 
	xhr.send();
}


///////////////////////////////////////////////////////////
//
//				COLORPICKER
//////////////////////////////////////////////////////////

const colorList = document.getElementById("colorList");
const activeColor = document.getElementById("activeColor");

var colorPicker = new iro.ColorPicker("#picker", {
	width: 220,
	// color: "#f00",
	colors: [
    	"rgb(255, 0, 0)",
    	"rgb(0, 255, 0)",
    	"rgb(0, 0, 255)",
  	],
  	handleRadius: 14,
	activeHandleRadius: 20,
	sliderSize: 35,
	borderWidth: 1,
	borderColor: "#fff",
});

function setColor(colorIndex) {
  colorPicker.setActiveColor(colorIndex);
}

// https://iro.js.org/guide.html#color-picker-events
colorPicker.on(["input:end"], function(){
	var ret = "";
	colorPicker.colors.forEach(color => {
		ret += color.red + '-' + color.green + '-' + color.blue + '-';
	});
	console.log( "kkk " + ret);	
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/colorset?funcID="+ret, true); 
	xhr.send();
});

colorPicker.on(["mount", "color:change"], function(){
  colorList.innerHTML = '';
  colorPicker.colors.forEach(color => {
    const index = color.index;
    const hexString = color.hexString;	
    colorList.innerHTML += `
      <div class="onecolor" onClick="setColor(${ index })">
        <div class="swatch" style="background: ${ hexString }"></div>
        <span>${ hexString }<br>${ color.hslString }<br>${ color.rgbString }</span>
      </div>
    `;
  });
});

// updateDate();


//обработка эвента сервера на обновление цвета кнопки комбобокса с палитрами и подменой градиентов
// function randomUpdate( request){
// 	var json = JSON.parse( request);
// 	if ( json.p01){  document.documentElement.setAttribute("style", json.p01); 	}
// }

// $( "#pollitres" ).selectmenu( "instance" )._renderButtonItem = function( item ) {
// 	var buttonItem = $( "<span>", { "class": "ui-selectmenu-text" })
// 	this._setText( buttonItem, item.label );

// 	var value = $('#pollitres option:selected').val();
// 	var button = document.getElementById( "pollitres-button");
// 	if ( value > 1) {			
// 		button.style.background = "var(--gr"+value+")";
// 	} else {
// 		button.style.background = "var(--gr0)";
// 	}
// 	return buttonItem;
// }



  	// <script>
  	// 	$( function() {
    // 		$( "#pollitres" ).selectmenu().selectmenu( "menuWidget" ).addClass( "overflow" ); 
  	// 	} );
  	// </script>

			// $( "#pollitres option[value="+ json.vPollCurrent +"]" ).prop('selected', 'selected');
			// $( "#pollitres" ).trigger( "change" );
			// $( "#pollitres" ).selectmenu( "instance" )._renderButtonItem( );
			// $('#pollitres').selectmenu('refresh', true);

	// $( "#pollitres option[value="+ json.vPollCurrent +"]" ).attr('selected', 'selected');
	// $("#pollitres").val( json.vPollCurrent).change();
	// $("#pollitres").trigger("change");
	// $( "#pollitres" ).selectmenu( "option", "selected",  json.vPollCurrent ).trigger( "change" );
	//.prop('selected', true);;

	// var value = $('#pollitres option:selected').val();
	// document.querySelector( ".upser").innerHTML 			= "new value: " + oldValue + " -=- " + json.vPollCurrent + " -=- " + value;
	// console.log( "new value: " + json.vPollDefault + " -=- " + json.vPollCurrent + " -=- " + value);



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

//(function updateSelfDate(){ updateDate(); setTimeout(updateSelfDate, 3000);})();