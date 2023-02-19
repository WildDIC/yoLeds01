#include "json_save.h"

const char *filename = "/config.txt";  // <- SD library uses 8.3 filenames

DynamicJsonDocument doc(10240);




// Loads the configuration from a file
void jsonLoadWave() {

	File file = SPIFFS.open(filename);
	DeserializationError error = deserializeJson(doc, file);
	if (error)
		Serial.println(F("Failed to read file, using default configuration"));

	file.close();

	// yo.currentBrightness 	= doc["bri"].as<uint8_t>()  | 128;
	// yo.currentTemp 			= doc["tmp"].as<uint8_t>()  | TEMP_IND_MAX;
	// yo.currentSpeed 		= doc["spd"].as<uint8_t>()  | 5;
	// yo.currentSaturn		= doc["sat"].as<uint8_t>()  | 100;
	// yo.antiSaturn 			= doc["ast"].as<uint8_t>()  | 0;
	// yo.ONOFF 				= doc["on"].as<bool>()  	| true;
	// yo.lastReceive 			= doc["lRc"].as<uint8_t>()  | 0;
	// yo.lastPressed 			= doc["lPr"].as<uint8_t>()  | 0;
	// yo.pollCurrent			= doc["pol"].as<uint8_t>()  | 10;

	// yo.c1.r = doc["c1"]["r"].as<uint8_t>() | 255; 	yo.c1.g = doc["c1"]["g"].as<uint8_t>() | 0; 	yo.c1.b = doc["c1"]["b"].as<uint8_t>() | 0;
	// yo.c2.r = doc["c2"]["r"].as<uint8_t>() | 0;		yo.c2.g = doc["c2"]["g"].as<uint8_t>() | 255;	yo.c2.b = doc["c2"]["b"].as<uint8_t>() | 0;
	// yo.c3.r = doc["c3"]["r"].as<uint8_t>() | 0;		yo.c3.g = doc["c3"]["g"].as<uint8_t>() | 0;		yo.c3.b = doc["c3"]["b"].as<uint8_t>() | 255;	
	// yo.AUX010 = doc["010"].as<uint8_t>()   | 5;		yo.AUX100 = doc["100"].as<uint8_t>()   | 50;	yo.AUX255 = doc["255"].as<uint8_t>()   | 128;

	// JsonArray repos = doc["waves"]; 	
	// for (JsonObject repo : repos) {
	// 	int waveID = repo["id"].as<int>();

	// 	mWaves[waveID].pollCurrent 	= repo["pol"].as<uint8_t>() | mWaves[waveID].pollDefault;
	// 	// mWaves[waveID].bright 		= repo["bri"].as<uint8_t>();
	// 	mWaves[waveID].speed 		= repo["spd"].as<uint8_t>() | 5;
	// 	mWaves[waveID].aux010 		= repo["010"].as<uint8_t>() | 5;
	// 	mWaves[waveID].aux100 		= repo["100"].as<uint8_t>() | 50;
	// 	mWaves[waveID].aux255 		= repo["255"].as<uint8_t>() | 128;
	// 	mWaves[waveID].temp 		= repo["tmp"].as<uint8_t>() | TEMP_IND_MAX;
	// 	mWaves[waveID].saturn 		= repo["sat"].as<uint8_t>() | 100;

	// 	mWaves[waveID].c1.r 		= repo["c1"]["r"].as<uint8_t>() | 255; 		mWaves[waveID].c1.g = repo["c1"]["g"].as<uint8_t>() | 0; 		mWaves[waveID].c1.b = repo["c1"]["b"].as<uint8_t>() | 0;
	// 	mWaves[waveID].c2.r 		= repo["c2"]["r"].as<uint8_t>() | 0;		mWaves[waveID].c2.g = repo["c2"]["g"].as<uint8_t>() | 255;		mWaves[waveID].c2.b = repo["c2"]["b"].as<uint8_t>() | 0;
	// 	mWaves[waveID].c3.r 		= repo["c3"]["r"].as<uint8_t>() | 0;		mWaves[waveID].c3.g = repo["c3"]["g"].as<uint8_t>() | 0;		mWaves[waveID].c3.b = repo["c3"]["b"].as<uint8_t>() | 255;

	// 	// Serial.print(" - ");
	// 	// Serial.print( waveID);
	// 	// Serial.print(", pol: ");
	// 	// Serial.print( mWaves[waveID].pollCurrent);
	// 	// Serial.print(", spd: ");
	// 	// Serial.println( mWaves[waveID].speed);
	// }
	Serial.println( "Loaded wave und datas from JSON file.");
}





// Saves the configuration to a file
// void saveConfiguration(const char *filename, const Config &config) {
void jsonSaveWave() {
	// Delete existing file, otherwise the configuration is appended to the file
	// const char *filename = ""
	SPIFFS.remove( filename);

	Serial.println( "Save wave datas into JSON file.");

	// Open file for writing
	File file = SPIFFS.open(filename, FILE_WRITE);
	if (!file) {
		Serial.println(F("Failed to create file"));
		return;
	}

	// DynamicJsonDocument doc(10240);

	doc["bri"]	= yo.currentBrightness;
	doc["tmp"]	= yo.currentTemp;
	doc["spd"]	= yo.currentSpeed;
	doc["sat"]	= yo.currentSaturn;
	doc["ast"]	= yo.antiSaturn;
	doc["on"]	= yo.ONOFF;
	doc["lRc"]	= yo.lastReceive;
	doc["lPr"]	= yo.lastPressed;
	doc["pol"]  = yo.pollCurrent;
	
	doc["c1r"]	= yo.c1.r; 		doc["c1g"]  = yo.c1.g; 		doc["c1b"] 	= yo.c1.b;
	doc["c2r"]	= yo.c2.r;		doc["c2g"]  = yo.c2.g;		doc["c2b"] 	= yo.c2.b;
	doc["c3r"]	= yo.c3.r;		doc["c3g"]  = yo.c3.g;		doc["c3b"] 	= yo.c3.b;	
	doc["010"]	= yo.AUX010;	doc["100"]	= yo.AUX100;	doc["255"]	=  yo.AUX255;

	int ind = 0;
	mbIter = mWaves.begin();
	for (int i = 0; mbIter != mWaves.end(); mbIter++, i++) {  
		
		if ( mbIter->second.typeWeb == 1){										// если ваве-кнопка)
			
			// Serial.print( mbIter->second.name);
			// Serial.println( mbIter->second.needSave);
			// Serial.println( mbIter->first != doc["waves"][ind]["id"].as<int>());
			
			if ( mbIter->second.needSaveJSON || mbIter->first != doc["waves"][ind]["id"].as<int>()){

				doc["waves"][ind]["id"]  	 =  mbIter->first;
				doc["waves"][ind]["pol"] 	 =  mbIter->second.pollCurrent;
				// doc["waves"][ind]["bri"] 	 =  mbIter->second.bright;				
				doc["waves"][ind]["spd"] 	 =  mbIter->second.speed;
				doc["waves"][ind]["010"] 	 =  mbIter->second.aux010;
				doc["waves"][ind]["100"] 	 =  mbIter->second.aux100;
				doc["waves"][ind]["255"] 	 =  mbIter->second.aux255;
				doc["waves"][ind]["tmp"] 	 =  mbIter->second.temp;
				doc["waves"][ind]["sat"] 	 =  mbIter->second.saturn;
				// doc["waves"][ind]["name"]	 =  mbIter->second.name;

				doc["waves"][ind]["c1r"] =  mbIter->second.c1.r;		
				doc["waves"][ind]["c1g"] =  mbIter->second.c1.g;		
				doc["waves"][ind]["c1b"] =  mbIter->second.c1.b;
				doc["waves"][ind]["c2r"] =  mbIter->second.c2.r;		
				doc["waves"][ind]["c2g"] =  mbIter->second.c2.g;		
				doc["waves"][ind]["c2b"] =  mbIter->second.c2.b;
				doc["waves"][ind]["c3r"] =  mbIter->second.c3.r;		
				doc["waves"][ind]["c3g"] =  mbIter->second.c3.g;		
				doc["waves"][ind]["c3b"] =  mbIter->second.c3.b;

				Serial.print( mbIter->second.name);
				Serial.printf( " -=> wave saved to json id=%d, (is=%d), ind=%d[%d], spd=%d, need=%d\n", 
															mbIter->first, 
																	mbIter->first == doc["waves"][ind]["id"].as<int>(),
																			ind, 
																				doc["waves"][ind]["id"].as<int>(), 
																						mbIter->second.speed, 
																								mbIter->second.needSaveJSON);
				
				mbIter->second.needSaveJSON = false;
			}
			ind++;		
		}
	}


	// JsonArray repos = doc["waves"]; // ["viewer"]["repositories"]["nodes"];
	// // Print the values
	// for (JsonObject repo : repos) {
	// 	Serial.print(" - ");
	// 	Serial.print(repo["id"].as<int>());
	// 	Serial.print(", speed: ");
	// 	Serial.println(repo["spd"].as<int>());
	// 	// Serial.print(", issues: ");
	// 	// Serial.println(repo["issues"]["totalCount"].as<int>());
	// }

	// Serialize JSON to file
	// serializeJsonPretty

	// if (serializeJson(doc, file) == 0) {
	// 	Serial.println(F("Failed to write to file"));
	// }

	file.close();
}





// Prints the content of a file to the Serial
void printFile(const char *filename) {
	// Open file for reading
	File file = SPIFFS.open(filename);
	if (!file) {
		Serial.println(F("Failed to read file"));
		return;
	}

	// Extract each characters by one by one
	while (file.available()) {
		Serial.print((char)file.read());
	}
	file.close();
}





void jsonStartUP(){
	
	if(!SPIFFS.begin(true)){
 	 	Serial.println("An Error has occurred while mounting SPIFFS");
  		return;
	}

	// Dump config file
	// Serial.println(F("Print config file..."));
	// printFile(filename);
	

	// File file = SPIFFS.open("/config.txt");
 	// if(!file){
    // 	Serial.println("Failed to open file for reading");
  	// }else{
	// 	Serial.println("File Content:");
  	// 	while(file.available()){
    // 		Serial.write(file.read());
  	// 	}
	// }  	
  	// file.close();
}

