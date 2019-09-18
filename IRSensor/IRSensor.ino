unsigned long zero_one = 0;
unsigned long zero_two = 0;
#define IR_one 17
#define IR_two 19
#define LED_one 3
#define LED_two 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IR_one, INPUT);
  pinMode(IR_two, INPUT);
  pinMode(LED_one, OUTPUT);
  pinMode(LED_two, OUTPUT);
  
  for(int i = 0; i < 100; i++)
  {
    zero_one += analogRead(IR_one);
    zero_two += analogRead(IR_two);
  }

  zero_one /= 100;
  zero_two /= 100;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int val_one = analogRead(IR_one);
  int val_two = analogRead(IR_two);

  val_one = map(val_one, zero_one, 1023, 0, 255);
  val_two = map(val_two, zero_two, 1023, 0, 255);

  constrain(val_one, 0, 255);
  constrain(val_two, 0, 255);

  analogWrite(LED_one, val_one);
  analogWrite(LED_two, val_two);

  Serial.print(val_one);
  Serial.print (" ");
  Serial.println(val_two);
  
}
