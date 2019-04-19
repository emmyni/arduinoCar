int motor1Pin1 = 6;  // pin 2
int motor1Pin2 = 7;  // pin 7
int enable1Pin = 5;  // pin 1
int motor2Pin1 = 9;  // pin 10
int motor2Pin2 = 10;  // pin 15
int enable2Pin = 8;  // pin 9
int flag = 0;
int state = 0;
int stateStop = 0;

int trigPin = 2;
int echoPin = 3;
long duration, cm;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}
void goForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH); 
  digitalWrite(motor2Pin2, LOW);  
  if (flag == 0) {                                                                                                                                                                                                                                                                                                                                                                                    
    Serial.println("GO FORWARD!");  
    flag = 1;                        
  }
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH); 
  digitalWrite(motor2Pin2, LOW);  
  if (flag == 0) {
    Serial.println("TURN LEFT");  
    flag = 1;                        
  }
  delay(500);
  state = 10;
  stateStop = 1;
}

void selfTurn() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW); 
  digitalWrite(motor2Pin2, LOW);
  delay(500);  
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH); 
  digitalWrite(motor2Pin2, LOW);  
  if (flag == 0) {
    Serial.println("TURN LEFT");  
    flag = 1;                        
  }
  delay(1500);
  stateStop = 1;
}
void loop() {
  if (Serial.available() > 0){
    state = Serial.read();
  }
  // forward
  if (state == '0') {
    goForward();
  }
  // backward
  else if (state == '1') {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, LOW); 
    digitalWrite(motor2Pin2, HIGH);  
    if (flag == 0) {
      Serial.println("GO BACKWARD!");  
      flag = 1;                        
    }
  }
//left
  else if (state == '2') {
    turnLeft();
  }
  // right
  else if (state == '3') {
   digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW); 
    digitalWrite(motor2Pin2, LOW);  
    if (flag == 0) {
      Serial.println("TURN RIGHT");  
      flag = 1;                        
    }
    delay(500);
    state = 10;
    stateStop = 1;
  }
  // stop
  else if (state == '4' || stateStop == 1) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW); 
    digitalWrite(motor2Pin2, LOW);  
    if (flag == 0) {
      Serial.println("STOP");  
      flag = 1;                        
    }
    stateStop = 0;
  }
  // ultrasonic
  else if (state == '7') {
    do {
       if (Serial.available() > 0){
         state = Serial.read();
         if (state != '7'){
           break;
        }  
       }
      goForward();
      
      digitalWrite(trigPin, LOW);
      delayMicroseconds(5);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);

      cm = (duration/2) / 29.1;

      Serial.print(cm);
      Serial.print("cm");
      Serial.println();
   } while (cm > 35);
   if (state == '7') {
    selfTurn();
   }
  }
  // spin left
  else if (state == '5') {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, HIGH); 
    digitalWrite(motor2Pin2, LOW);  
    if (flag == 0) {
      Serial.println("TURN LEFT");  
      flag = 1; 
    }                       
   }
//  spin right
  else if (state == '6') {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW); 
    digitalWrite(motor2Pin2, LOW);  
    if (flag == 0) {
      Serial.println("TURN RIGHT");  
      flag = 1;                        
    }
  }
}
