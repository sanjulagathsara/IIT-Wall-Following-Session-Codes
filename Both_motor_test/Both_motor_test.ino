int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

int motor2Pin1 = 25;
int motor2Pin2 = 34;
int enable2Pin = 12;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
int dutyCycle = 200;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure PWM functionalitites
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  // Move the DC motor forward at maximum speed
  go_forward(255,255);
  delay(2000);

  // Stop the DC motor
  slow_brake();
  delay(1000);

  // Move DC motor backwards at maximum speed
  go_forward(-255,-255);
  delay(2000);

  // Stop the DC motor
  slow_brake();
  delay(1000);

  // Move DC motor forward with increasing speed
  while (dutyCycle <= 255){
    go_forward(dutyCycle,dutyCycle);  
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(100);
  }

   dutyCycle = 0;
}

void go_forward(int Lspeed , int Rspeed){

  if(Lspeed > 0){
  ledcWrite(pwmChannel1, Lspeed); 
  
  Serial.print("Moving Left Motor Forward ");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  
  }
  else{
    ledcWrite(pwmChannel1, -Lspeed); 

    Serial.print("Moving Left Motor Backward ");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
  }


  if(Rspeed > 0){
    ledcWrite(pwmChannel2, Rspeed);

    Serial.print("Moving Right Motor Forward ");
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW); 
  }
  else{
    ledcWrite(pwmChannel2, -Rspeed);

    Serial.print("Moving Right Motor Backward ");
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH); 
  }


}


void turn_right(int speed){
  // Your Code for turn Right
}

void turn_left(int speed){
  // Your Code for turn Left
}

void slow_brake(){
  Serial.println("Slow Brake");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW); 
}

void quick_brake(){
  Serial.println("Quick Brake");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, HIGH); 
}
