#include <Servo.h>
const int trigPin = 11;
const int echoPin = 12;
const int triggerPaper = 9;
Servo servo;
Servo servo2;
int angle = 10;
//value to see if bin is closed
int value = 1;  
int val2 = 1;

// defines variables
long duration; 
int distance;

void setup() {
  servo.attach(7);
  servo.write(angle);
  servo2.attach(6);
  servo2.write(angle);
  pinMode(13, OUTPUT); //LED to indicate that it works
  pinMode(10, INPUT);  //input from esp to check if OPENPMD message was sent
  pinMode(trigPin, OUTPUT);   // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);    // Sets the echoPin as an Input
  pinMode(triggerPaper, INPUT);
  Serial.begin(9600);         // Starts the serial communication
}

// set pin to input


void loop() 
{ 
 // scan from 0 to 180 degrees
  if (digitalRead(10) == HIGH && value == 1 ) {
    openTrash();
  } else if(digitalRead(triggerPaper)==HIGH && val2 == 1) {
    openPaper();
  } else if(digitalRead(triggerPaper) == LOW && val2 == -1) {
    closePaper();
  }
}

void openTrash() {
   for(angle = 10; angle < 100; angle++)  
    {                                  
    servo.write(angle);               
    delay(15);                   
    } 
    value = -1;
    digitalWrite(13, HIGH);
    delay(500);
    measureDistance();
}

void closeTrash() {
  for(angle = 100; angle > 10; angle--)    
    {                                
      servo.write(angle);           
      delay(15);       
    }
    value = 1;
    digitalWrite(13, LOW);
  
}
void measureDistance() {
  distance = 8000;
  while(distance > 11) {
     // Clears the trigPin
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    distance= duration*0.034/2;
    
    // Prints the distance on the Serial Monitor
    Serial.println(distance);
    delay(1);
  }
  closeTrash();

  
  
}

void openPaper() {
  for(angle = 10; angle < 100; angle++)  
    {                                  
    servo2.write(angle);               
    delay(15);                   
    } 
    digitalWrite(13, HIGH);
    val2 = -1;
}

void closePaper() {
  for(angle = 100; angle > 10; angle--)    
    {                                
      servo2.write(angle);           
      delay(15);       
    }
    val2 = 1;
}
