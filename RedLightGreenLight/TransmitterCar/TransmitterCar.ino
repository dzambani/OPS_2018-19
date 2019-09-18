#define button1 2
#define button2 6
#define led 4
#include "transmitter.h"

boolean flag = true;
int score = 0;
int randNum;
int state;

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(led, OUTPUT);
  transmitter_setup();
  Serial.begin(9600);
}

void loop() {
  if (flag == true)
  {
    flag = false;
    randomSeed(analogRead(15));
    randNum = random(300);
    state = randNum % 2;
  }

  if (state == 0)
  {
    Serial.println("Press button 1");
    sending(3.7);
    //Serial.println("sent 1.1");
  }
  if (state == 1)
  {
    Serial.println("Press button 2");
    sending(4.7);
    //Serial.println("sent 2.1");
  }

  if (digitalRead(button1) == LOW && state == 0)
  {
    sending(5.7);
    //Serial.println("sent 3.1");
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    score++;
    Serial.println("The score is: ");
    Serial.print(score);
    delay(1000);
    flag = true;
  }

  if (digitalRead(button2) == LOW && state == 1)
  {
    sending(6.7);
    //Serial.println("sent 4.1");
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    score++;
    Serial.println("The score is: ");
    Serial.print(score);
    delay(1000);
    flag = true;
  }
  
  if ((digitalRead(button1) == LOW && state == 1) ||
       digitalRead(button2) == LOW && state == 0)
  {
    sending(7.7);
    //Serial.println("sent 5.1");
    digitalWrite(led, HIGH);          //blinks 5 times if lost
    delay(5000);
    digitalWrite(led, LOW);
    Serial.println("You lost. Score: ");
    Serial.print(score);
    score = 0;
    delay(1000);
    flag = true;
  }
  delay(100);
}
