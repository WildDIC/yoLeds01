#ifndef __WAVE_CLASS_H
#define __WAVE_CLASS_H

#include "config.h"
#include <FastLED.h>
#include <unordered_set>
// #include <set>

class animeClass
{
	public:	
		int indAnime	= 0;
		int indSetter 	= 0;	
		bool changed 	= false;   		// something chaged from web or irda

		std::unordered_set <int> forSave;
    	std::unordered_set <int> keysAll;  // чекаем уникальность введенных ИД для активностей, вроде как пофик, но вот чёта хочется.
    	std::unordered_set <int> keysWeb;  // чекаем уникальность введенных ИД для активностей, вроде как пофик, но вот чёта хочется.
		
		std::unordered_set <int> :: iterator itForSave; // = forSave.begin(); //insert erase couunt
		std::pair<std::unordered_set <int> :: iterator, bool> itKeys; // итератор для анордеред_мапы с ИД активностей

		animeClass(){
			indAnime 	= 0;
			indSetter 	= 0;			
		}

		/*Возвращает true ( bool Ledas.changed), 
		если в настройках с сайта или ИРы что-то поменялось.
		Сбрасывается на false, после первого обращения к себе.*/
		bool isChanged(){
			bool result = this->changed;
			this->changed = false;
			return result;
		}

		/*
		@param id Unical ID. irDA code даже лучше будет
		@param name Animation name for web ( Here - Nah)
		@param ptStatic указатель на функию аминации, выполняется разово ( не в лупе) = &staticFuuctionName
		@param forWeb публиковать на сайте ( будет в виде кнопки вызова анимации), позиция в странице зависит от порядка при добавлении
		@param polDefault ИД политры по-умолчанию для анимации, берется из таблицы myPal из palettes.cpp ( 9 - радуга)
		*/
		void addStatic( 	int id, String name, void (*ptStatic)(), 		bool forWeb = false, 	uint8_t polDefault 	= 9);		
		void addAmine( 		int id, String name, void (*ptAnime)(), 		bool forWeb = false, 	uint8_t polDefault 	= 9, 	void (*ptAnimePre)() = nullptr);
		void addSetter( 	int id, String name, void (*ptSetter)(int), 	int min 	= 0, 		int max 			= 255 );
		void addChanger( 	int id, String name, void (*ptChanger)(int),	byte delta 	= 1);		
		bool isInID( 		int id);
	
	private:
		waveItem addDefault( int id);
};

// todo ПРИКРУТИТЬ rButton and rRange

extern animeClass a;

#endif