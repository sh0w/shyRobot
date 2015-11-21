int motor1_A=6;
int motor1_B=11;
int motor1_Speed=9;
  
int motor2_A=5;
int motor2_B=10;
int motor2_Speed=9;

const int trigPin = 4;
const int echoPin = 2;

int calibrationTime = 20;        
int pirPin = 12;    //the digital pin connected to the PIR sensor's output
long unsigned int pause = 50;  
  
boolean currentlyEscaping;
  
void setup(){
  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
  
  pinMode(motor2_A,OUTPUT);
  pinMode(motor2_B,OUTPUT);
  
  Serial.begin(9600);

  currentlyEscaping = false;
  
  
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
    }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}
  
void loop(){
  long duration, cm;
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  Serial.println("\n");
  Serial.print(cm);
  Serial.println("cm");
  
  Serial.print("move: ");
  Serial.println(digitalRead(pirPin));
  
  Serial.print("escape: ");
  Serial.println(currentlyEscaping);
   
  
  if(digitalRead(pirPin) && cm > 35) {
    
    if(!currentlyEscaping) {
      currentlyEscaping = true;
      Serial.println("OMG OMG OMG i am so scared i gotta leave!!!!!");
      for (int i=0; i < 255; i+=5){
        digitalWrite(motor1_A,LOW); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor1_B,HIGH);
        analogWrite(motor1_Speed,i); // speed counts from 0 to 255
        digitalWrite(motor2_A,LOW); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor2_B,HIGH);
        analogWrite(motor2_Speed,i); // speed counts from 0 to 255
        delay(5);
      }
    } else {
      Serial.println("you're still too close - i'm still leaving!!!!!");
      digitalWrite(motor1_A,LOW); // A = HIGH and B = LOW means the motor will turn right
      digitalWrite(motor1_B,HIGH);
      analogWrite(motor1_Speed,255); // speed counts from 0 to 255
      digitalWrite(motor2_A,LOW); // A = HIGH and B = LOW means the motor will turn right
      digitalWrite(motor2_B,HIGH);
      analogWrite(motor2_Speed,255); // speed counts from 0 to 255
      delay(10);
    }
  } else {
    if(currentlyEscaping && cm > 35) {
      
      Serial.println("phew, i escaped you! i can slow down now!!");
      /* /// slow down:
      for (int i=255; i > 0; i-=5){
        digitalWrite(motor1_A,LOW);
        digitalWrite(motor1_B,HIGH);
        analogWrite(motor1_Speed,i);
        digitalWrite(motor2_A,LOW);
        digitalWrite(motor2_B,HIGH);
        analogWrite(motor2_Speed,i);
        delay(10);
      }*/
      
      digitalWrite(motor1_A,LOW);
      digitalWrite(motor1_B,HIGH);
      analogWrite(motor1_Speed,50); 
      digitalWrite(motor2_A,LOW);
      digitalWrite(motor2_B,HIGH);
      analogWrite(motor1_Speed,50);
      delay(50);
      
      currentlyEscaping = false;
    } else {
      Serial.println("i'm ok !");
    }
  }

  if(cm <= 35) {
    // TURN AROUND IF OBSTACLE DETECTED!
    currentlyEscaping = false;
    if(random(10) < 5) {
      for (int i=0; i < 255; i+=5){
        digitalWrite(motor1_A,LOW); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor1_B,HIGH);
        analogWrite(motor1_Speed,i); // speed counts from 0 to 255
        digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor2_B,LOW);
        analogWrite(motor2_Speed,i); // speed counts from 0 to 255
        delay(13);
      }
    } else {
      for (int i=0; i < 255; i+=5){
        digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor1_B,LOW);
        analogWrite(motor1_Speed,i); // speed counts from 0 to 255
        digitalWrite(motor2_A,LOW); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor2_B,HIGH);
        analogWrite(motor2_Speed,i); // speed counts from 0 to 255
        delay(13);
      }
    }
  }
  
  delay(100);
}


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
