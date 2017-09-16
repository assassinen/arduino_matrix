#include <Servo.h>
Servo servo;
#define Trig 4 /* Обозначаем пин подачи импульса*/ 
#define Echo 5 /* Обозначаем пин приема импульса*/ 
void setup() { 
pinMode (Trig, OUTPUT); /*инициируем как выход */ 
pinMode (Echo, INPUT); /*инициируем как вход */ 
Serial.begin (9600); /* устанавливаем скорость порта */
servo.attach(10, 0, 180);
} 
unsigned int impulseTime=0; 
unsigned int distance_sm=0; 

void loop() { 
digitalWrite (Trig, HIGH); /* Подаем импульс на вход trig дальномера */ 
delayMicroseconds (10); /* Импульс длится 10 микросекунд */ 
digitalWrite (Trig, LOW); // Отключаем подачу импульса 
impulseTime=pulseIn (Echo, HIGH); 
/*Принимаем импульс и подсчитываем его длину*/ 
distance_sm =impulseTime/58; /* Пересчитываем его значение в сантиметры */ 
Serial.println( distance_sm); /* Выводим значение на порт программы */ 
int sss = map(distance_sm, 0, 180, 0, 300);
servo.write(sss);
//Serial.println(sss);
delay (200); 
}
