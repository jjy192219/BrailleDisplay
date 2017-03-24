#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

#define DOT_1 A0
#define DOT_2 A1
#define DOT_3 A2
#define DOT_4 A3
#define DOT_5 A4
#define DOT_6 A5

SoftwareSerial mySerial(6, 7); // RX, TX

int16_t iterator;
byte letter;
byte filenum;
byte volume = 20;
String content = "";
char character;
unsigned long previousMillis = 0;

const uint16_t interval = 400;
const bool braille[27][6] = 
  {
    { true,   false,  false,  false,  false,  false},   // A
    { true,   true,   false,  false,  false,  false},   // B
    { true,   false,  false,  true,   false,  false},   // C
    { true,   false,  false,  true,   true,   false},   // D
    { true,   false,  false,  false,  true,   false},   // E
    { true,   true,   false,  true,   false,  false},   // F
    { true,   true,   false,  true,   true,   false},   // G
    { true,   true,   false,  false,  true,   false},   // H
    { false,  true,   false,  true,   false,  false},   // I
    { false,  true,   false,  true,   true,   false},   // J
    { true,   false,  true,   false,  false,  false},   // K
    { true,   true,   true,   false,  false,  false},   // L
    { true,   false,  true,   true,   false,  false},   // M
    { true,   false,  true,   true,   true,   false},   // N
    { true,   false,  true,   false,  true,   false},   // O
    { true,   true,   true,   true,   false,  false},   // P
    { true,   true,   true,   true,   true,   false},   // Q
    { true,   true,   true,   false,  true,   false},   // R
    { false,  true,   true,   true,   false,  false},   // S
    { false,  true,   true,   true,   true,   false},   // T
    { true,   false,  true,   false,  false,  true},    // U
    { true,   true,   true,   false,  false,  true},    // V
    { false,  true,   false,  true,   true,   true},    // W
    { true,   false,  true,   true,   false,  true},    // X
    { true,   false,  true,   true,   true,   true},    // Y
    { true,   false,  true,   false,  true,   true},    // Z
    { false,  false,  false,  false,  false,  false}    // SPACE
  };

void setup () {
	Serial.begin (9600);
	mySerial.begin (9600);
	mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
	mp3_set_volume (volume);
  pinMode (DOT_1, OUTPUT);
  pinMode (DOT_2, OUTPUT);
  pinMode (DOT_3, OUTPUT);
  pinMode (DOT_4, OUTPUT);
  pinMode (DOT_5, OUTPUT);
  pinMode (DOT_6, OUTPUT);
}


//
void loop () {        
	
	while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
  }
  if (content != "") {
    if ((content == "++") && (volume < 30)) {
      volume++;
      mp3_set_volume(volume); 
      content = "";
    }
    if ((content == "--") && (volume > 0)) {
      volume--;
      mp3_set_volume(volume);
      content = "";
    }
  }
  if (content != "") {
    //Serial.println(content);
    iterator = content.length();

    //for (int i=0;i<content.length();i++) {
    while (iterator >= 0) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
          // DO Stuff
        if (iterator >= 1) {
          
          letter = byte(content.charAt(content.length()-iterator));
          Serial.println(letter);
          if ((letter>96) && (letter<123)) {  // Upper Case Letters
            filenum=letter-97;
          } else if ((letter>64) && (letter<91)) {  // Lower Case Letters
            filenum=letter-65;
          } else if (letter == 32) {  // SPACE
            filenum=26;
          } else if (letter == 13) {  // CARRIAGE RETURN
            filenum=26;
          }
          
          digitalWrite(DOT_1, braille[filenum][0]);
          digitalWrite(DOT_2, braille[filenum][1]);
          digitalWrite(DOT_3, braille[filenum][2]);
          digitalWrite(DOT_4, braille[filenum][3]);
          digitalWrite(DOT_5, braille[filenum][4]);
          digitalWrite(DOT_6, braille[filenum][5]);
          
          mp3_play(filenum);
        } else {
          Serial.println("EOF");
          digitalWrite(DOT_1, LOW);
          digitalWrite(DOT_2, LOW);
          digitalWrite(DOT_3, LOW);
          digitalWrite(DOT_4, LOW);
          digitalWrite(DOT_5, LOW);
          digitalWrite(DOT_6, LOW);
        }
        iterator--;
        //Serial.println(iterator);
      }
      
    }
    content="";
  }

}


 
/*
   mp3_play ();		//start play
   mp3_play (5);	//play "mp3/0005.mp3"
   mp3_next ();		//play next 
   mp3_prev ();		//play previous
   mp3_set_volume (uint16_t volume);	//0~30
   mp3_set_EQ ();	//0~5
   mp3_pause ();
   mp3_stop ();
   void mp3_get_state (); 	//send get state command
   void mp3_get_volume (); 
   void mp3_get_u_sum (); 
   void mp3_get_tf_sum (); 
   void mp3_get_flash_sum (); 
   void mp3_get_tf_current (); 
   void mp3_get_u_current (); 
   void mp3_get_flash_current (); 
   void mp3_single_loop (boolean state);	//set single loop 
   void mp3_DAC (boolean state); 
   void mp3_random_play (); 
 */

