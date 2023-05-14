#ifndef __EEPCLASS_H
#define __EEPCLASS_H

#include <EEPROM.h>
#include "config.h"

class eeClass
{
	public:	
		int saveCounter = 0;

		int readStartHere( int addr){
			eepromCurrentAddr = addr;
			return addr;
		}

		int getCurrenRead(){
			return eepromCurrentAddr;
		}
		
		uint16_t read16t(){
			uint16_t data16t   = EEPROM.read( eepromCurrentAddr);
			eepromCurrentInt   = eepromCurrentAddr;			
			eepromCurrentAddr += 2;	
			return data16t;
		}

		int readINT(){	
			int dataINT 	   = EEPROM.read( eepromCurrentAddr);
			eepromCurrentInt   = eepromCurrentAddr;			
			eepromCurrentAddr += 4;	
			return dataINT;
		}

		byte readBYTE(){
			byte dataBYTE 	   = EEPROM.read( eepromCurrentAddr);
			eepromCurrentByte  = eepromCurrentAddr;			
			eepromCurrentAddr += 1;	
			return dataBYTE;
		}

		bool readBOOL(){
			bool dataBOOL      = EEPROM.read( eepromCurrentAddr);
			eepromCurrentByte  = eepromCurrentAddr;			
			eepromCurrentAddr += 1;		
			return dataBOOL > 0 ? 1 : 0;
		}

		void saveData( int addr, int data) 		{ 	  int res = EEPROM.read( addr);	if ( res != data) EEPROM.put( addr, data);	}
		void saveData( int addr, uint8_t data)  { uint8_t res = EEPROM.read( addr);	if ( res != data) EEPROM.put( addr, data);	}

		void saveData( uint16_t data) { if ( read16t()  != data) fWriteDATA( data);}
		void saveData( int data) 	  { if ( readINT()  != data) fWriteDATA( data);}
		void saveData( byte data)	  { if ( readBYTE() != data) fWriteDATA( data);}
		void saveData( bool data)	  { if ( readBOOL() != data) fWriteDATA( data);}
	
	private:
		int eepromCurrentAddr = 0;				// указывает на адрес последней считанной ячейки памяти функциями фРидХХХХ, 
		int eepromCurrentByte = 0;				// именно в туда мы будем потом, если надо (записываемые данные не совпали с сохраненными ранее),
		int eepromCurrentInt  = 0;				// записывать проверяемые данные.

		void fWriteDATA( uint16_t data)	{ EEPROM.put( eepromCurrentInt,  data); ++saveCounter; }
		void fWriteDATA( int data)		{ EEPROM.put( eepromCurrentInt,  data); ++saveCounter; }
		void fWriteDATA( byte data)		{ EEPROM.put( eepromCurrentByte, data); ++saveCounter; }
		void fWriteDATA( bool data)		{ EEPROM.put( eepromCurrentByte, data); ++saveCounter; }

};

#endif