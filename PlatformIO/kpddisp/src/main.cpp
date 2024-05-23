#include <Arduino.h>
#include <Keypad.h>
#include <IRremote.h>
#include <EEPROM.h>

#define IR A2
IRrecv irrecv(IR);

///////////////////////////// SET TO TRUE TO SAVE MEMORY
///////////////////////////////////////////////////////
#define SAVE_MEMORY false ////////////////////////////
/////////////////////////////////////////////////////

int EEPROM_SIZE = 512;
int num_size = 5;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {10, 12, 11, 8};
byte colPins[COLS] = {4, 3, A1, A0};
Keypad Kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

byte b[] = {3, 159, 37, 13, 153, 73, 65, 31, 1, 9};
byte t[] = {2, 158, 36, 12, 152, 72, 64, 30, 0, 8};

#define nullpin -1
int clk[] = {nullpin, 5, 9, 6, 2}; // 5 is for 3 digit
int pin = 0;
int eeprom_store_pos = -1;

int LEDdata = 7;

void setup()
{
  Serial.begin(9600);
  Serial.println("begin");

  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(LEDdata, OUTPUT);

  shiftOut(LEDdata, 9, LSBFIRST, 19);
  shiftOut(LEDdata, 9, LSBFIRST, 131);
  shiftOut(LEDdata, 9, LSBFIRST, 225);
  shiftOut(LEDdata, 9, LSBFIRST, 97);
  shiftOut(LEDdata, 9, LSBFIRST, 99);

  shiftOut(LEDdata, 2, LSBFIRST, 19);
  shiftOut(LEDdata, 2, LSBFIRST, 131);
  shiftOut(LEDdata, 2, LSBFIRST, 225);
  shiftOut(LEDdata, 2, LSBFIRST, 97);
  shiftOut(LEDdata, 2, LSBFIRST, 99);

  shiftOut(LEDdata, 6, LSBFIRST, 19);
  shiftOut(LEDdata, 6, LSBFIRST, 131);
  shiftOut(LEDdata, 6, LSBFIRST, 225);
  shiftOut(LEDdata, 6, LSBFIRST, 97);
  shiftOut(LEDdata, 6, LSBFIRST, 99);

  shiftOut(LEDdata, 5, LSBFIRST, 17);
  shiftOut(LEDdata, 5, LSBFIRST, 225);
  shiftOut(LEDdata, 5, LSBFIRST, 99);

  delay(1000);

  if (SAVE_MEMORY)
  {
    // load from eeprom and show
    for (int i = 0; i < 4; i++)
    {
      int addr = num_size * i;
      for (int j = 0; j < num_size; j++)
      {
        shiftOut(LEDdata, clk[i + 1], LSBFIRST, t[EEPROM.read(addr + j)]);
        Serial.print(EEPROM.read(addr + j));
      }
      Serial.print(" ");
    }
    Serial.println();
  }

  irrecv.enableIRIn();
  Serial.println("Enabled IRin");
  // Initialize_streamer();
}

// 0   4 5   9
// 00000 00000 00000 00000

void shift_eeprom(int num)
{
  if (eeprom_store_pos != -1)
  {
    int addr = eeprom_store_pos;
    for (int i = 0; i < num_size; i++)
    {
      int write_addr = addr + i;
      if (i == num_size - 1)
      {
        EEPROM.write(write_addr, num);
      }
      else
      {
        EEPROM.write(write_addr, EEPROM.read(write_addr + 1));
      }
    }
  }
}

void loop()
{

  char key = Kpd.getKey();
  decode_results result;

  if (key || irrecv.decode(&result))
  {
    Serial.println(key);
    Serial.println(result.value);

    switch (result.value)
    {
    case 824:
    case 551505585:
      key = 'A';
      break;
    case 2872:
    case 551521905:
      key = 'B';
      break;
    case 1848:
    case 551536185:
      key = 'C';
      break;
    case 3896:
    case 551519865:
      key = 'D';
      break;

    case 2320:
    case 551487735:
      key = '0';
      break;
    case 16:
    case 551520375:
      key = '1';
      break;
    case 2064:
    case 551504055:
      key = '2';
      break;
    case 1040:
    case 551536695:
      key = '3';
      break;
    case 3088:
    case 551495895:
      key = '4';
      break;
    case 528:
    case 551528535:
      key = '5';
      break;
    case 2576:
    case 551512215:
      key = '6';
      break;
    case 1552:
    case 551544855:
      key = '7';
      break;
    case 3600:
    case 551491815:
      key = '8';
      break;
    case 272:
    case 551524455:
      key = '9';
      break;
    case 1680:
    case 551541285:
      key = '#';
      break;
    }

    switch (key)
    {
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
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[0]);
      shift_eeprom(0);
      break;
    case '1':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[1]);
      shift_eeprom(1);
      break;
    case '2':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[2]);
      shift_eeprom(2);
      break;
    case '3':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[3]);
      shift_eeprom(3);
      break;
    case '4':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[4]);
      shift_eeprom(4);
      break;
    case '5':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[5]);
      shift_eeprom(5);
      break;
    case '6':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[6]);
      shift_eeprom(6);
      break;
    case '7':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[7]);
      shift_eeprom(7);
      break;
    case '8':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[8]);
      shift_eeprom(8);
      break;
    case '9':
      shiftOut(LEDdata, clk[pin], LSBFIRST, b[9]);
      shift_eeprom(9);
      break;
    case 'A':
      pin = 1;
      eeprom_store_pos = num_size * 0;
      break;
    case 'B':
      pin = 2;
      eeprom_store_pos = num_size * 1;
      break;
    case 'C':
      pin = 3;
      eeprom_store_pos = num_size * 2;
      break;
    case 'D':
      pin = 4;
      eeprom_store_pos = num_size * 3;
      break;

      // default:
      //   pin=nullpin;
      // break;
    }
    for (int i = 0; i < 4; i++)
    {
      int addr = num_size * i;
      for (int j = 0; j < num_size; j++)
      {
        Serial.print(EEPROM.read(addr + j));
      }
      Serial.print(" ");
    }
    Serial.println();
    delay(250);

    irrecv.resume();
  }
}
