#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {10, 12, 11, 8}; 
byte colPins[COLS] = {4, 3, A1,A0};
Keypad Kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

byte b[]={3,159,37,13,153,73,65,31,1,9};
byte t[]={2,158,36,12,152,72,64,30,0,8};

#define nullpin -1
int clk[]={nullpin,5,9};//5 is for 3 digit
int pin = 0;

int LEDdata = 7;


void setup() {
  Serial.begin(9600);
  Serial.println("begin");
  
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(LEDdata, OUTPUT); 


shiftOut(LEDdata,9,LSBFIRST,19);
shiftOut(LEDdata,9,LSBFIRST,131);
shiftOut(LEDdata,9,LSBFIRST,225);
shiftOut(LEDdata,9,LSBFIRST,97);
shiftOut(LEDdata,9,LSBFIRST,99);

//shiftOut(LEDdata,5,LSBFIRST,252);
shiftOut(LEDdata,5,LSBFIRST,17);
shiftOut(LEDdata,5,LSBFIRST,225);
shiftOut(LEDdata,5,LSBFIRST,99);
//shiftOut(LEDdata,5,LSBFIRST,252);


}

void loop() {
  
  
  
  char key = Kpd.getKey();

  if (key){
    Serial.println(key);
     switch(key){      
      // case '*':
      //   if(pin>=3){
      //    pin = 0;
      //   }
      //   else{
      //    pin++;
      //   }
      // break;
       case '#':
         pin = nullpin;
       break;
       case '0':       
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[0]);        
       break;
       case '1': 
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[1]);   
       break;
       case '2':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[2]);
       break;
       case '3':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[3]);
       break;
       case '4':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[4]);
       break;
       case '5':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[5]);
       break;
       case '6':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[6]);
       break;
       case '7':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[7]);
       break;
       case '8':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[8]);
       break;
       case '9':
         shiftOut(LEDdata,clk[pin],LSBFIRST,b[9]);
       break;
       case'A':
         pin=1;
       break;
       case'B':
         pin=2;
       break;
      
       default:
         pin=nullpin;
       break;
       
     
       
     }
   }
 
}
