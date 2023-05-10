/* @file MultiKey.ino
|| @version 1.0
|| @author Trey Breshears
|| @contact tlbnf5@mst.edu
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| #
*/

#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 9; //corresponds to keyboard columns
const byte COLS = 6; //corresponds to keyboard rows
//define the cymbols on the buttons of the keypads

char lastkey, lastspec, lastnum, lastnav;

char hexaKeys[ROWS][COLS] = {
{'1', 'q', 'a', 'z', '©', '!'},
{'2', 'w', 's', 'x', '©', '@'},
{'3', 'e', 'd', 'c', ' ', '#'},
{'4', 'r', 'f', 'v', '©', '$'},
{'5', 't', 'g', 'b', '©', '%'},
{'6', 'y', 'h', 'n', '©', '^'},
{'7', 'u', 'j', 'm', '©', '&'},
{'8', 'i', 'k', ',', '©', '*'},
{'9', 'o', 'l', '.', '©', 27},
//{'0', 'p', ';', '/', ' ', 'f'}
};

//defining the pins where rows and cols are connected
byte rowPins[ROWS] = {8,14,16,15,17,4,1,0,2}; //C1, C2, C3, C4, C5, C6, C7, C8, C9, C10 (3)
byte colPins[COLS] = {6,10,11,12,30,7}; //R0, R1, R2, R3, R4, R10

Keypad kpd = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );

char hexaKeysr[4][6] = {
{27, 9, 'c', 's', 'c', 'f'},
{'-', '[', 39, 's', ' ', 'f'},
{'=', ']', 'e', ' ', ' ', 'f'},
{8, 92, ' ', ' ', ' ', 'f'}
};

//defining the pins where rows and cols are connected
byte rowPinsR[4] = {9,A5,A4,A3}; //C0, C11, C12, C13
byte colPinsR[6] = {6,10,11,12,30,7}; //R0, R1, R2, R3, R4, R10

Keypad kpdr = Keypad( makeKeymap(hexaKeysr), rowPinsR, colPinsR, 4, 6);

char hexaKeysSpc[3][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};

byte rowPinsSpc[3] = {0, 2, 3}; //
byte colPinsSpc[3] = {A2,A1,A0}; //

Keypad spc = Keypad( makeKeymap(hexaKeysSpc), rowPinsSpc, colPinsSpc, 3, 3);

char hexaKeysNav[3][4] = {
  {'i', 'd', ' ', 'l'},
  {'h', 'e', 'p', 'w'},
  {'u', 'n', ' ', 'r'}
};

byte rowPinsNav[3] = {8,14,16}; //
byte colPinsNav[4] = {A2,A1,A0,5}; //

Keypad nav = Keypad( makeKeymap(hexaKeysNav), rowPinsNav, colPinsNav, 3, 4);

char hexaKeysNum[4][5] = {
  {'l', '7', '4', '1', '0'},
  {'/', '8', '5', '2', ' '},
  {'*', '9', '6', '3', 'd'},
  {'-', '=', 'e', 'e', ' '}
};

byte rowPinsNum[4] = {15, 17, 4, 1}; //
byte colPinsNum[5] = {A2, A1, A0, 5, 13}; //

Keypad num = Keypad( makeKeymap(hexaKeysNum), rowPinsNum, colPinsNum, 4, 5);

unsigned long loopCount;
unsigned long startTime;
String msg;


void setup() {
    //Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {
    loopCount++;
    if ( (millis()-startTime)>60000 ) {
        Serial.print("Average loops per second = ");
        Serial.println(loopCount/60);
        startTime = millis();
        loopCount = 0;
    }

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
              switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                  case PRESSED:
                  msg = " PRESSED.";
              break;
                  case HOLD:
                  msg = " HOLD.";
              break;
                  case RELEASED:
                  msg = " RELEASED.";
              break;
                  case IDLE:
                  msg = " IDLE.";
              }
                Serial.print("Key ");
                Serial.print(kpd.key[i].kchar);
                Serial.println(msg);
            }

            char c = kpd.key[i].kchar;
            long t;

            if((c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || c == '*') && (c != lastkey || (millis()-t) > 200)){
              switch (c){
                case '!':
                  Keyboard.press(KEY_LEFT_GUI);
                  Keyboard.press('r');
                  delay(10);
                  Keyboard.releaseAll();
                  delay(200);
 
                  Keyboard.print("spotify.exe");
                  Keyboard.press(KEY_RETURN);
                  delay(100);
                  Keyboard.releaseAll();
                  break;
                case '@':
                  Keyboard.press(KEY_LEFT_GUI);
                  Keyboard.press('r');
                  delay(10);
                  Keyboard.releaseAll();
                  delay(200);
 
                  Keyboard.print("chrome.exe");
                  Keyboard.press(KEY_RETURN);
                  delay(100);
                  Keyboard.releaseAll();
                  break;
                case '#':
                  Keyboard.press(KEY_LEFT_CTRL);
                  Keyboard.press('c');
                  delay(10);
                  Keyboard.releaseAll();
                  break;
                case '$':
                  Keyboard.press(KEY_LEFT_CTRL);
                  Keyboard.press('v');
                  delay(10);
                  Keyboard.releaseAll();
                  break;
                case '%':
                  Keyboard.press(KEY_LEFT_CTRL);
                  Keyboard.press('z');
                  delay(10);
                  Keyboard.releaseAll();
                  break;
                case '^':
                  Keyboard.print("What Brain Cells?");
                  break;
                case '&':
                  Keyboard.press(KEY_LEFT_GUI);
                  Keyboard.press('r');
                  delay(10);
                  Keyboard.releaseAll();
                  delay(200);
 
                  Keyboard.print("explorer");
                  Keyboard.press(KEY_RETURN);
                  delay(100);
                  Keyboard.releaseAll();
                  break;
                case '*':
                  Keyboard.press(KEY_LEFT_GUI);
                  Keyboard.press('r');
                  delay(10);
                  Keyboard.releaseAll();
                  delay(200);
 
                  Keyboard.print("C:\\Users\\alpha\\AppData\\Local\\Discord\\app-1.0.9012\\Discord.exe");
                  Keyboard.press(KEY_RETURN);
                  delay(100);
                  Keyboard.releaseAll();
                  break;
              }
              lastkey = c;
              t = millis();
            }
            else if (kpd.key[i].kstate == PRESSED && c != '©' && c != lastkey || (millis()-t) > 200){
              Keyboard.write(c);
              lastkey = c;
              t = millis();
            }
            
        }
    }

    if (kpdr.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpdr.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpdr.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key R ");
                Serial.print(kpdr.key[i].kchar);
                Serial.println(msg);
                Keyboard.write(kpdr.key[i].kchar);
            }
        }
    }

  if (spc.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( spc.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (spc.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Special key ");
                Serial.print(spc.key[i].kchar);
                Serial.println(msg);
                Keyboard.write(spc.key[i].kchar);
            }
        }
    }

  if (nav.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( nav.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (nav.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Navigation key ");
                Serial.print(nav.key[i].kchar);
                Serial.println(msg);
                //Keyboard.write(nav.key[i].kchar);
            }
            
            char n = nav.key[i].kchar;
            if(n=='l' && nav.key[i].kstate == PRESSED && lastnav != n){ //ADD MILLIS CHECK
              Keyboard.press(KEY_LEFT_ARROW);
              delay(100);
              Keyboard.release(KEY_LEFT_ARROW);
            }
            else if(n=='r' && nav.key[i].kstate == PRESSED && lastnav != n){
              Keyboard.press(KEY_RIGHT_ARROW);
              delay(100);
              Keyboard.release(KEY_RIGHT_ARROW);
            }
            else if(n=='w' && nav.key[i].kstate == PRESSED && lastnav != n){
              Keyboard.press(KEY_DOWN_ARROW);
              delay(100);
              Keyboard.release(KEY_DOWN_ARROW);
            }
        }
    }
  if (num.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( num.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (num.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Number pad key ");
                Serial.print(num.key[i].kchar);
                Serial.println(msg);
            }

            char c = num.key[i].kchar;
            long t;

            if (num.key[i].kstate == PRESSED && c != '©' && c != 'e' && (c != lastkey || (millis()-t) > 200)){
              Keyboard.write(c);
              lastkey = c;
              t = millis();
            }
            if(num.key[i].kstate == PRESSED && c == 'e'){
              Keyboard.press(KEY_KP_ENTER);
              delay(100);
              Keyboard.release(KEY_KP_ENTER);
            }
        }
    }
}  // End loop
