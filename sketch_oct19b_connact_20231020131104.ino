#include "config.h"
AdafruitIO_Feed *buttonfeed = io.feed("buttonfeed");
AdafruitIO_Feed *counter = io.feed("project1", "Zahhak");
const int ledPin1=27;
const int ledPin2=12;
const int ledPin3=13;
const int pushButtonPin=33;
int pushButtonState=0;
float YJbtn;


void setup() {
  Serial. begin(115200);
  while (! Serial);

  Serial.print("Connecting to Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());

  pinMode(pushButtonPin,INPUT);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  counter->onMessage(handleMessage);
  counter->get();

}

void loop() {
  io.run();
  pushButtonState = digitalRead(pushButtonPin);
  Serial.println(pushButtonState);

  if(pushButtonState == HIGH) {
    //Mode 1
    buttonfeed->save(1);
    pushButtonState = LOW;
    Mode1();
  }else{
    //Mode 2
    Mode2();
  }
  delay(3000);

  if(YJbtn == 1){
  ledPin1(HIGH);
  }
}

void Mode1(){
  digitalWrite(ledPin2,HIGH);
  delay(1000);
  digitalWrite(ledPin3,HIGH);
  digitalWrite(ledPin2,LOW);
  delay(1000);
  digitalWrite(ledPin3,LOW);
}

void Mode2(){
  digitalWrite(ledPin1,HIGH);
  delay(3000);
  digitalWrite(ledPin3,LOW);
  delay(1000);
}

void handleMessage(AdafruitIO_Data *data){
  Serial.print("Received:");
  Serial.println(data->toFloat());
  YJbtn = data->toFloat();
}