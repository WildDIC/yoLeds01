#ifndef __WAVE_CLASS_H
#define __WAVE_CLASS_H

typedef void (*func_ptr)(int);

class waveClass{
	private: // спецификатор доступа private
		int day, // день
			month, // месяц
			year; // год
	public: // спецификатор доступа public
		int minute;
		waveClass(int, int, int); // конструктор класса
    	func_ptr  method;
		void message(); // функция (метод класса) выводящая сообщение на экран
		void setDate(int, int, int); // установка даты в формате дд.мм.гг
		void getDate(); // отобразить текущую дату
};

#endif