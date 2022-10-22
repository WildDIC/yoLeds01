#include "waveClass.h"
 
waveClass::waveClass(int date_day, int date_month, int date_year ){
	setDate(date_day, date_month, date_year); // вызов функции установки даты
}
 
void waveClass::message(){
}
 
void waveClass::setDate(int date_day, int date_month, int date_year){
	day   = date_day; // инициализация день
	month = date_month; // инициализация месяц
	year  = date_year; // инициализация год
}
 
void waveClass::getDate(){
}