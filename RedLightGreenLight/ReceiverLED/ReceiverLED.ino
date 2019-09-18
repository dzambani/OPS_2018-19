#include "receiver.h"
#define YLED 9
#define RLED 5
float blah;
bool check = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  receiver_setup();
  pinMode(YLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  digitalWrite(YLED, LOW);
  digitalWrite(RLED,LOW);
}

void loop() {
  if(receiving(blah))
  {
    Serial.println(blah);
    if (blah == 3.7 && check == false){
      digitalWrite(YLED, HIGH);
      check = true;
    }
    else if (blah == 4.7 && check == false){
      digitalWrite(RLED, HIGH);
      check = true;
    }
    if (blah == 5.7 && digitalRead(YLED) == HIGH && check == true){
     digitalWrite(RLED, LOW);
     digitalWrite(YLED, LOW);
     check = false;
     }
    else if (blah == 6.7 && digitalRead(RLED) == HIGH && check == true){
      digitalWrite(RLED, LOW);
      digitalWrite(YLED, LOW);
      check = false;
     }
    else if (blah == 7.7 && (digitalRead(RLED) == HIGH || digitalRead(YLED) == HIGH) && check == true){
     digitalWrite(RLED, LOW);
     digitalWrite(YLED, LOW);
     check = false;
     }
  }
   else 
    Serial.println("not receiving");
   delay(100);

}
