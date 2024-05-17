int motor1Pin1 = 32; 
int motor1Pin2 = 33; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel0 = 0;
const int pwmChannel1 = 1;
const int resolution = 8;
int dutyCycle = 200;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  
  // configure PWM functionalitites
  ledcSetup(pwmChannel0, freq, resolution);
  ledcSetup(pwmChannel1, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motor1Pin1, pwmChannel0);
  ledcAttachPin(motor1Pin2, pwmChannel1);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  // Move the DC motor forward at maximum speed
  go_forward(255);
  delay(2000);

  // Stop the DC motor
  slow_brake();
  delay(1000);

  // Move DC motor backwards at maximum speed
  go_backward(255);
  delay(2000);

  // Stop the DC motor
  slow_brake();
  delay(1000);

  // Move DC motor forward with increasing speed
  while (dutyCycle <= 255){
    go_forward(dutyCycle);  
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(100);
  }

   dutyCycle = 0;
}

void go_forward(int speed){
  ledcWrite(pwmChannel0, speed); 
  ledcWrite(pwmChannel1, 0); 
  Serial.print("Moving Forward ");
  Serial.println(dutyCycle);
}

void go_backward(int speed){
  ledcWrite(pwmChannel0, 0); 
  ledcWrite(pwmChannel1, speed);
  Serial.print("Moving Backward ");
  Serial.println(dutyCycle); 
}

void turn_right(int speed){
  // Your Code for turn Right
}

void turn_left(int speed){
  // Your Code for turn Left
}

void slow_brake(){
  Serial.println("Slow Brake");
  ledcWrite(pwmChannel0, 0); 
  ledcWrite(pwmChannel1, 0); 
}