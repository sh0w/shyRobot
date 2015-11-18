int motor1_A=6;
int motor1_B=11;
int motor1_Speed=9;
  
int motor2_A=5;
int motor2_B=10;
int motor2_Speed=9;

const int trigPin = 4;
const int echoPin = 2;
  
boolean currentlyEscaping;
  
void setup(){
  pinMode(motor1_A,OUTPUT);
  pinMode(motor1_B,OUTPUT);
  
  pinMode(motor2_A,OUTPUT);
  pinMode(motor2_B,OUTPUT);
  
  Serial.begin(9600);
  
  currentlyEscaping = false;
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
  
  
  Serial.print(cm);
  Serial.print("cm\n");
  
  if(cm < 35) {
    
    if(!currentlyEscaping) {
      
      Serial.println("OMG OMG OMG i am so scared i gotta leave!!!!!");
      for (int i=0; i < 255; i+=5){
        digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor1_B,LOW);
        analogWrite(motor1_Speed,i); // speed counts from 0 to 255
        digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
        digitalWrite(motor2_B,LOW);
        analogWrite(motor2_Speed,i); // speed counts from 0 to 255
        delay(10);
      }
      currentlyEscaping = true;
      
    } else {
      
      Serial.println("you're still too close - i'm still leaving !!!!! ");
      digitalWrite(motor1_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
      digitalWrite(motor1_B,LOW);
      analogWrite(motor1_Speed,255); // speed counts from 0 to 255
      digitalWrite(motor2_A,HIGH); // A = HIGH and B = LOW means the motor will turn right
      digitalWrite(motor2_B,LOW);
      analogWrite(motor2_Speed,255); // speed counts from 0 to 255
      delay(200);
     
    }
  } else {
    
    if(currentlyEscaping) {
      
      Serial.println("phew, i escaped you! i can slow down now!!");
      
      for (int i=255; i > 0; i-=5){
        digitalWrite(motor1_A,HIGH);
        digitalWrite(motor1_B,LOW);
        analogWrite(motor1_Speed,i);
        digitalWrite(motor2_A,HIGH);
        digitalWrite(motor2_B,LOW);
        analogWrite(motor2_Speed,i);
        delay(10);
      }
      
      
    } else {
   
      Serial.println("i'm ok !");
      
      digitalWrite(motor1_A,LOW);
      digitalWrite(motor1_B,LOW);
      analogWrite(0,0); 
      digitalWrite(motor2_A,LOW);
      digitalWrite(motor2_B,LOW);
      analogWrite(0,0);
      
    }
  }
      
  currentlyEscaping = false;
      
  delay(100);
}


long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
