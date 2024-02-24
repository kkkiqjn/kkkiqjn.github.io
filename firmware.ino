#include <SD.h>
#include "RTClib.h"
#include <LiquidCrystal.h> // Include the LiquidCrystal library


const int rs = A9, en = A8;
LiquidCrystal lcd(rs, en,A0,A1,A2,A3,A4,A5,A6,A7 );
RTC_DS1307 rtc;


#define CS_PIN A10



File root;

void setup() {
  Serial.begin(115200);

  
  
  if (!SD.begin(CS_PIN)) {
    Serial.println("Card initialization failed!");
    while (true);
  }

  Serial.println("initialization done.");

  

  
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  lcd.begin(16, 2);
  

  
  Serial.println("Initializing SD card... ");


  

  
  if (!SD.begin(CS_PIN)) {
    Serial.println("Card initialization failed!");
    while (true);
  }

  Serial.println("initialization done.");

 

  
  
  int i=0;
  while(i<5){
i++;

  File textFile = SD.open("data.txt",FILE_WRITE);
if(textFile){
  String str=  rtcfunc();
  lcd.print(str);
  delay(100);
  lcd.display();  
  for(int i=0;i<24;i++){
  lcd.scrollDisplayLeft();
  delay(200);
  if(textFile){
    for(auto ele:str){
      textFile.write(ele);
    }
    textFile.write('\n');

  }
  textFile.close();
  }
  lcd.clear();
 
}
 else{
    Serial.println("Error in opening file");
  } 
  
  
  delay(4000);
  }
  Serial.println();
  Serial.println("Writing completed");
  delay(1000);
  File readf=SD.open("data.txt");
  Serial.println();
  Serial.println("Reading from SD card");
  while(readf.available()){
    Serial.write(readf.read());
    delay(100);
  }
  readf.close();
  Serial.println("reading completed");
  Serial.println();
Serial.println("Files in the card:");
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("");
}






void loop() {
 
}







void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}



String rtcfunc()
{
  DateTime now = rtc.now();

  String str="";
  str+=String(now.day());
  str+='/';
  str+=String(now.month());
  str+='/';
  str+=String(now.year());
  str+="    ";
  str+=String(now.hour());
  str+=":";
  str+=String(now.minute());
  str+=":";
  str+=String(now.second());
  str+="    ";
  str+="Temperature:";
  str+=String(temp());


  Serial.println(str);
  return str;
}


int temp(){
  int i=0;
  float celsius;
  while(i<3){
   int analogValue = analogRead(A15);
   celsius = 1 / (log(1 / (1023. / analogValue - 1)) / 3950 + 1.0 / 298.15) - 273.15;
  i++;
  delay(100);
  }
  return celsius;
}
