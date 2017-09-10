//Пин подключен к ST_CP (12) входу 74HC595
int latchPin = 8;
//Пин подключен к SH_CP (11) входу 74HC595
int clockPin = 12;
//Пин подключен к DS (14) входу 74HC595
int dataPin = 11;

int photo_pin = 0;

int letter_number = 55;
int pin_value = 0;
int last_pin_value = 0;
int change_value = 140;
int bitsToSend = 0;

unsigned long ledTime = 0;
unsigned long darkTime = 0;
unsigned long timeDiff = 0;

const int dot = 500;
const int approx = 100;
int dash = dot*3;
int symbolInterval = dot;
int letterInterval = 3*dot;
int wordInterval = 7*dot; 

int letter = 0; 
int dot_symbol = 1;
int dash_symbol = 2;

static byte letters[][8] = {
  { B01110, B10001, B10001, B11111, B10001, B10001, B10001, B00000 }, //A
  { B11110, B10000, B10000, B11110, B10001, B10001, B11110, B00000 }, //Б
  { B11110, B10001, B10001, B11110, B10001, B10001, B11110, B00000 }, //B
  { B11111, B10001, B10000, B10000, B10000, B10000, B10000, B00000 }, //Г
  { B01110, B01010, B01010, B01010, B01010, B11111, B10001, B00000 }, //Д
  { B11111, B10000, B10000, B11110, B10000, B10000, B11111, B00000 }, //E
  { B10101, B10101, B10101, B01110, B10101, B10101, B10101, B00000 }, //Ж
  { B01110, B10001, B00001, B01110, B00001, B10001, B01110, B00000 }, //З
  { B10001, B10001, B10011, B10101, B11001, B10001, B10001, B00000 }, //И
  { B10101, B10101, B10011, B10101, B11001, B10001, B10001, B00000 }, //Й
  { B10001, B10010, B10100, B11000, B10100, B10010, B10001, B00000 }, //K
  { B00111, B01001, B01001, B01001, B01001, B01001, B10001, B00000 }, //Л
  { B10001, B11011, B10101, B10101, B10001, B10001, B10001, B00000 }, //M
  { B10001, B10001, B10001, B11111, B10001, B10001, B10001, B00000 }, //H
  { B01110, B10001, B10001, B10001, B10001, B10001, B01110, B00000 }, //O
  { B11111, B10001, B10001, B10001, B10001, B10001, B10001, B00000 }, //П
  { B11110, B10001, B10001, B11110, B10000, B10000, B10000, B00000 }, //P
  { B01110, B10001, B10000, B10000, B10000, B10000, B10001, B01110 }, //C
  { B11111, B00100, B00100, B00100, B00100, B00100, B00100, B00000 }, //T
  { B10001, B10001, B10001, B01111, B00001, B10001, B01110, B00000 }, //У
  { B01110, B10101, B10101, B10101, B01110, B00100, B00100, B00000 },//Ф
  { B10001, B10001, B01010, B00100, B01010, B10001, B10001, B00000 }, //X
  { B10001, B10001, B10001, B10001, B10001, B10001, B11111, B00001 },//Ц
  { B10001, B10001, B10001, B01111, B00001, B00001, B00001, B00000 },//Ч
  { B10101, B10101, B10101, B10101, B10101, B10101, B11111, B00000 },//Ш
  { B10101, B10101, B10101, B10101, B10101, B10101, B11111, B00001 },//Щ
  { B10001, B10001, B10001, B11101, B10101, B10101, B11101, B00000 },//Ы
  { B10000, B10000, B10000, B11110, B10001, B10001, B11110, B00000 },//Ь
  { B11110, B00001, B00001, B01111, B00001, B00001, B11110, B00000 },//Э
  { B10111, B10101, B10101, B11101, B10101, B10101, B10111, B00000 },//Ю
  { B01111, B10001, B10001, B01111, B10001, B10001, B10001, B00000 },//Я
  //
  { B01110, B10001, B10011, B10101, B11001, B10001, B01110, B00000 },  //"0",
  { B00001, B00011, B00101, B00001, B00001, B00001, B11111, B00000 },  //"1",
  { B01110, B10001, B00001, B00010, B00100, B01000, B11111, B00000 },  //"2",
  { B11111, B00010, B00100, B00010, B00001, B10001, B01110, B00000 },  //"3",
  { B00010, B00110, B01010, B10010, B11111, B00010, B00010, B00000 },  //"4",
  { B11111, B10000, B11110, B00001, B00001, B10001, B01110, B00000 },  //"5",
  { B00110, B01000, B10000, B11110, B10001, B10001, B01110, B00000 },  //"6",
  { B11111, B00001, B00010, B00100, B01000, B01000, B01000, B00000 },  //"7",
  { B01110, B10001, B10001, B01110, B10001, B10001, B01110, B00000 },  //"8",
  { B01110, B10001, B10001, B01110, B00001, B00010, B01100, B00000 }, //"9",
  
  { B00000, B00000, B00000, B00000, B00000, B00110, B00110, B00000 },//".",
  { B00000, B00000, B00000, B00000, B00000, B00110, B00010, B00100 },//",",
  { B00000, B00000, B00110, B00110, B00000, B00110, B00110, B00000 },//":",
  { B00000, B00000, B00110, B00110, B00000, B00110, B00010, B00100 },//";"
  { B00010, B00010, B00010, B00010, B00010, B00000, B00010, B00000 },//"!",
  { B01110, B10001, B00001, B00010, B00100, B00000, B00100, B00000 },//"?", 
  { B00000, B00000, B11111, B00000, B11111, B00000, B00000, B00000 },//"=",
  { B01010, B01010, B01010, B00000, B00000, B00000, B00000, B00000 },//"""",
  { B00000, B00100, B10101, B01110, B10101, B00100, B00000, B00000 },//"*",
  { B00000, B00001, B00010, B00100, B01000, B10000, B00000, B00000 },//"()",
  //
  { B01010, B01010, B11111, B01010, B11111, B01010, B01010, B00000 },//"/", 
  { B00000, B00000, B00000, B11111, B00000, B00000, B00000, B00000 },//"-", 
  { B00000, B00000, B00000, B00000, B00000, B10001, B11111, B00000 },//"_", 
  { B01110, B10001, B10111, B10101, B10111, B10000, B01111, B00000 },//"@", 
    
  { B00000, B00100, B01000, B11111, B01000, B00100, B00000, B00000 },//"ERROR" };
  { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000 } //clear
};
//Morse code table: 1 - "dot", 2 - "dash", 0 - "error"
const int morseCodeInt[] = {
  12,       2111,     122,    221,     211,        1,     1112,     2211,     11,   1222, 
  212,      1211,      22,     21,     222,     1221,      121,      111,      2,    112, 
  1121,     1111,    2121,   2221,    2222,     2212,     2122,     2112,  11211,   1122, 
  1212,  
  22222,   12222,   11222,  11122,   11112,    11111,    21111,    22111,  22211,   22221, 
  111111, 121212,  222111, 212121,   221122,   112211,   21112,   121121, 122221,  212212, 
  21121,  211112,  112212, 122121, 11111111 
};

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 
  pinMode(clockPin, OUTPUT);

  pinMode(photo_pin, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);  

  pin_value = analogRead(photo_pin);
  if (pin_value > change_value) {
    last_pin_value = pin_value;
  } else {
    last_pin_value = pin_value;
  }
}

void toLed(int letter_number) {
  for (int whichPin = 0; whichPin < 8; whichPin++) {
    bitsToSend = 0;
    bitWrite(bitsToSend, whichPin, HIGH);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
    bitsToSend = 0xFF^letters[letter_number][whichPin];
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
    digitalWrite(latchPin, HIGH);
  }
}

void cleareLed() {
  for (int whichPin = 0; whichPin < 8; whichPin++) {
    bitsToSend = 0;
    bitWrite(bitsToSend, whichPin, HIGH);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
    bitsToSend = 1;
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
    digitalWrite(latchPin, HIGH);
  }
}

int time_counter(bool pin_HIGH) {
  if (pin_HIGH) {
    ledTime = millis();
    return ledTime - darkTime;
  } else {
    darkTime = millis();
    return darkTime - ledTime;
  }
}
 
int get_number_letter(int letter) {
  for (int i = 0; morseCodeInt[i] != '\0'; i++) {
    if (morseCodeInt[i] == letter) {
      return i;
    }
  }
  return 55;
}

void signal_processing(int last_pin_value) {
  if (last_pin_value > change_value) {
    //процедура обработки включенного состояния
    timeDiff = time_counter(true);
    if (letter != 1111111 && timeDiff < dot + approx && timeDiff > dot - approx) {
      letter = letter*10 + dot_symbol;
    } else if (letter != 1111111 && timeDiff < dash + approx && timeDiff > dash - approx) {
      letter = letter*10 + dash_symbol;
    } else {
      letter = 1111111;
    }
  } else {
    //процедура обработки выключенного состояния
    timeDiff = time_counter(false);
    if (timeDiff < letterInterval + approx && timeDiff > letterInterval - approx) {
      letter_number = get_number_letter(letter);
      letter = 0;
    } else if (timeDiff < wordInterval + approx && timeDiff > wordInterval - approx) {
      letter_number = get_number_letter(letter);
      letter = 0;
    } else if (timeDiff < symbolInterval - approx || 
              (timeDiff > symbolInterval + approx && timeDiff < letterInterval - approx) ||
              (timeDiff > letterInterval + approx && timeDiff < wordInterval - approx) ||
              timeDiff > wordInterval + approx) {
      letter_number = 55;
      letter = 0;
    }
  }
}

/*
void loop() {
  pin_value = analogRead(photo_pin);
  
  if (pin_value > (change_value + last_pin_value)) {
    digitalWrite(13,HIGH); 
    signal_processing(last_pin_value);
    last_pin_value = pin_value;
  }
  else if (last_pin_value > (change_value + pin_value)) {
    digitalWrite(13,LOW); 
    signal_processing(last_pin_value);
    last_pin_value = pin_value;
  } 
  
  toLed(letter_number);
}
*/

void loop() {
  toLed(8);
  delay(2);
  //cleareLed();
  
}
