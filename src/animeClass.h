#ifndef __WAVE_CLASS_H
#define __WAVE_CLASS_H

#include "config.h"
#include <FastLED.h>
#include <unordered_set>
#include <set>


class animeClass
{
	public:	
		int indAnime	= 0;
		int indSetter 	= 0;	
		uint8_t countWaves = 0;
		uint8_t countRanges = 0;
		bool changed 	= false;   				// something chaged from web or irda

		std::set <int> forSave;					// сет для НЕ СОХРАНЕННЫХ ключей "ИД волн", которые необходимо сохранить, так как у них что-то изменилось
    	std::set <int> keysAll;  				// сет для ВСЕХ ИД, чекаем уникальность введенных ИД для активностей, вроде как пофик, но вот чёта хочется.
    	std::set <int> keyRange;  				// сет для РЭНДЖЕЙ - полоски-двиалки для сайта
    	std::unordered_set <int> keyButton; 	// сет для КНОПОК - активности типа статик или анимашка для веба, по факту - хранит активные активности.
		
		std::set <int> :: iterator itForSave; 	// = forSave.begin(); //insert erase couunt
		std::unordered_set <int> :: iterator itButtons; 	
		std::pair<std::set <int> :: iterator, bool> itKeys; // итератор для анордеред_мапы с ИД активностей


		/*		Какая-то функция, которая запускается после всего для чего-то, что надо сделать потом.*/
		void makeWebLists();

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
		@param polDefault ИД политры по-умолчанию для анимации, берется из таблицы myPal из palettes.cpp ( 9 - радуга)*/
		void addStatic( 	int id, const String& name, void (*ptStatic)(), 	bool forWeb = false, 	uint8_t polDefault 	= 9);		
		/*
		@param id Unical ID. irDA code даже лучше будет
		@param name Animation name for web ( Here - Nah)
		@param ptAnime указатель на функию аминации, выполняется в цикле loop = &staticFuuctionName
		@param forWeb публиковать на сайте ( будет в виде кнопки вызова анимации), позиция в странице зависит от порядка при добавлении
		@param polDefault ИД политры по-умолчанию для анимации, берется из таблицы myPal из palettes.cpp ( 9 - радуга)
		@param ptAnimePre указатель на функция "пре", выполнится один раз перед первым запуском функции с анимацией = &staticFuuctionName*/
		void addAmine( 		int id, const String& name, void (*ptAnime)(), 		bool forWeb = false, 	uint8_t polDefault 	= 9, 	void (*ptAnimePre)() = nullptr);
		/*
		Добавляем "сеттер", добавляется на страницу в виде рэнджа, вызывается из веба, при изменениии рэнджа с передацей значения в функцию.
		@param id Unical ID. irDA code даже лучше будет
		@param name Animation name for web ( Here - Nah)
		@param ptSetter указатель на функцию "сеттер" = &staticFuuctionName
		@param min мин
		@param max  макс*/
		void addSetter( 	int id, const String& name, void (*ptSetter)(int), 	int min 	= 0, 		int max 			= 255 );
		/*
		Добавляем "Чэнджер", для тыканья с пульта ИД и вызова функций
			с передачей +/-дельты в нее. Не для веба.

		@param id Unical ID. irDA code даже лучше будет. Доп коды в таблице keyCodes в irda.cpp
		@param name Animation name ( Here - Nah), просто для понимания, что это такое.
		@param ptChanger pointer to changer function = &staticFuuctionName
		@param delta +/- add/sub, передаем это значение в функцию*/
		void addChanger( 	int id, const String& name, void (*ptChanger)(int),	byte delta 	= 1);		
		bool isInID( 		int id);
	
	private:
		waveItem* addDefault( int id);
};

// в тут хранятся... да тут только одбавляшки и сэты из индексов уже добавленных активностей. еще isChanged есть полезный.
extern animeClass a;

#endif