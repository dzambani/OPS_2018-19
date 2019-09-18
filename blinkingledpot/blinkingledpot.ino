#define POT 4
#define LED 12
int vIn = 0;
const int multiplier = 1;

void setup(){
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop(){
 vIn = analogRead(POT);
 digitalWrite(LED, HIGH);
 Serial.println(vIn);
 delay(vIn*multiplier);
 digitalWrite(LED, LOW);
 delay(vIn*multiplier);
}
