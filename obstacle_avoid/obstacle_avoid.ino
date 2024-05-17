int motor1Pin1 = 32; 
int motor1Pin2 = 33; 

int motor2Pin1 = 27; 
int motor2Pin2 = 26; 

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;


// Setting PWM properties
const int freq = 30000;
const int pwmChannel0 = 0;
const int pwmChannel1 = 1;
const int pwmChannel2 = 2;
const int pwmChannel3 = 3;
const int resolution = 8;
int dutyCycle = 200;

void setup() {

  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // configure PWM functionalitites
  ledcSetup(pwmChannel0, freq, resolution);
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  ledcSetup(pwmChannel3, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motor1Pin1, pwmChannel0);
  ledcAttachPin(motor1Pin2, pwmChannel1);
  ledcAttachPin(motor2Pin1, pwmChannel2);
  ledcAttachPin(motor2Pin2, pwmChannel3);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}



void go_forward(int LSpeed,int RSpeed){

  if(LSpeed > 0){
  ledcWrite(pwmChannel0, LSpeed); 
  ledcWrite(pwmChannel1, 0);
  
  }
  else{
    ledcWrite(pwmChannel0, 0); 
  ledcWrite(pwmChannel1, -LSpeed);
  }

  if(RSpeed > 0){
    ledcWrite(pwmChannel2, RSpeed); 
    ledcWrite(pwmChannel3, 0);
  }
  else{
    ledcWrite(pwmChannel2, 0); 
    ledcWrite(pwmChannel3, -RSpeed);
  }


}

void slow_brake(){
  Serial.println("Slow Brake");
  ledcWrite(pwmChannel0, 0); 
  ledcWrite(pwmChannel1, 0);
  ledcWrite(pwmChannel2, 0); 
  ledcWrite(pwmChannel3, 0); 
}

void turn_left(int speed){
  Serial.println("Turn left");
  ledcWrite(pwmChannel0, 0); 
  ledcWrite(pwmChannel1, speed);
  ledcWrite(pwmChannel2, speed); 
  ledcWrite(pwmChannel3, 0); 
  delay(300);
}

void loop() {
 
   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  // Move DC motor forward with increasing speed
  
    if (distanceCm < 15){
        turn_left(255);
    }
    else{
         // Move the DC motor forward at maximum speed
        go_forward(255,255);
        delay(100);
    }
  
}