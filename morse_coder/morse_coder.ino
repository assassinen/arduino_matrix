#include <Servo.h>
Servo servo;

//РџРёРЅ РїРѕРґРєР»СЋС‡РµРЅ Рє ST_CP (12) РІС…РѕРґСѓ 74HC595
int latchPin = 8;
//РџРёРЅ РїРѕРґРєР»СЋС‡РµРЅ Рє SH_CP (11) РІС…РѕРґСѓ 74HC595
int clockPin = 12;
//РџРёРЅ РїРѕРґРєР»СЋС‡РµРЅ Рє DS (14) РІС…РѕРґСѓ 74HC595
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
int dash = dot * 3;
int symbolInterval = dot;
int letterInterval = 3 * dot;
int wordInterval = 7 * dot;

int letter = 0;
int dot_symbol = 1;
int dash_symbol = 2;

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

int morse_port = 13;
int distance_meter_vcc_port = 3;
int distance_meter_trig_port = 4;
int distance_meter_echo_port = 5;
int distance_meter_gnd_port = 6;


void setup() {
  servo.attach(10);
  pinMode(morse_port, OUTPUT);
  pinMode(distance_meter_vcc_port, OUTPUT);
  pinMode(distance_meter_trig_port, OUTPUT);
  pinMode(distance_meter_echo_port, INPUT);
  pinMode(distance_meter_gnd_port, OUTPUT);
  
  digitalWrite(distance_meter_vcc_port, HIGH);
  digitalWrite(distance_meter_gnd_port, LOW);
  Serial.begin(9600);
  
  
}

int get_count_code(int morseCode) {
  int n = 1;
  while ((morseCode /= 10) > 0)
  {
    n++;
  }
  return n;
}


void blink_morse(int digit) {
  if (digit == 0) {
    delay(letterInterval - symbolInterval);
  }
  if (digit == 1) {
    digitalWrite(morse_port, HIGH);
    delay(dot);
    digitalWrite(morse_port, LOW);
    delay(symbolInterval);
  }
  if (digit == 2) {
    digitalWrite(morse_port, HIGH);
    delay(dash);
    digitalWrite(morse_port, LOW);
    delay(symbolInterval);
  }
}

void letter_coder(int letter_number) {
  int morse_code = morseCodeInt[letter_number];
  int n = get_count_code(morse_code);
  int rank;
  int digit;
  for (int i = n - 1; i >= 0; i--) {
    rank = 1;
    for (int j = 0; j < i; j++) { 
      rank *= 10;
    }
    digit = morse_code / rank;
    blink_morse(digit);
    morse_code -= digit * rank;
  }
  blink_morse(0);
}


void distance_meter() {
  int duration, cm; 
  digitalWrite(distance_meter_trig_port, LOW); 
  delayMicroseconds(2); 
  digitalWrite(distance_meter_trig_port, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(distance_meter_trig_port, LOW); 
  duration = pulseIn(distance_meter_echo_port, HIGH); 
  cm = duration / 58 / 100;
  Serial.print(cm); 
  Serial.println(" cm"); 
  delay(100);
}


void loop() {
  //distance_meter();
  
  letter_coder(62-32);
  
  letter_coder(43-32);
  letter_coder(61-32);
  letter_coder(33-32);
  letter_coder(43-32);
  letter_coder(61-32);

  letter_coder(48-32);
  letter_coder(37-32);
  letter_coder(42-32);
  letter_coder(46-32);
  letter_coder(48-32);
  letter_coder(36-32);
  
}

