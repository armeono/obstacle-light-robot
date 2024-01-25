
const int MOTOR1_IN1 =  P6_7;
const int  MOTOR1_IN2 = P6_6;
const int SPEED_CONTROL1 = P2_3;


const int  MOTOR2_IN1 = P2_7;
const int MOTOR2_IN2 = P2_6;
const int SPEED_CONTROL2 = P2_4;

const int RIGHT_LDR = A6;
const int LEFT_LDR = A3;


const int ECHO = P6_4; 
const int TRIG = P6_5;

const int BUTTON = P4_1;
const int LED = P4_3;

long duration = 4;
int distance = 5;

int buttonRead = 0;

boolean ledState = false;

int leftLDR = 0;
int rightLDR = 0;

void setup() {
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);
  pinMode(MOTOR2_IN2, OUTPUT);

  pinMode(SPEED_CONTROL1, OUTPUT);
  pinMode(SPEED_CONTROL2, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  pinMode(RIGHT_LDR, INPUT);
  pinMode(LEFT_LDR, INPUT);

  Serial.begin(9600);
}

void loop() {

     rightLDR = analogRead(LEFT_LDR);
     leftLDR = analogRead(RIGHT_LDR);

     digitalWrite(TRIG, LOW);
     delayMicroseconds(2);
     digitalWrite(TRIG, HIGH);
     delayMicroseconds(10);
     digitalWrite(TRIG, LOW);
    

     duration = pulseIn(ECHO, HIGH);
 
     distance = duration * 0.034 / 2;

     buttonRead = digitalRead(BUTTON);

     if(buttonRead == 0) {
        digitalWrite(LED, HIGH);
     }else {
        digitalWrite(LED, LOW);
     }

     if(buttonRead == 0){
        if(distance > 5){
            if(rightLDR > leftLDR) {
              light_rotateRobotRight();
             }
    
            if(leftLDR > rightLDR){
              light_rotateRobotLeft();
             }
      
             if(areSimilar(rightLDR, leftLDR)) {
              disableMotors();
              runMotors();     
             }
         }else {
              rotateRobotLeft();
         }

     }else {
      disableMotors();
     }
}

void runMotors() {
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, HIGH);  

    analogWrite(SPEED_CONTROL1, 80);

    digitalWrite(MOTOR2_IN1, LOW);
    digitalWrite(MOTOR2_IN2, HIGH); 

    analogWrite(SPEED_CONTROL2, 80);
}

void disableMotors() {

    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, HIGH);  

    analogWrite(SPEED_CONTROL1, 0);

    digitalWrite(MOTOR2_IN1, HIGH);
    digitalWrite(MOTOR2_IN2, HIGH); 

    analogWrite(SPEED_CONTROL2, 0);
}

void rotateRobotLeft() {

    disableMotors();

    for(int i = 0; i < 30000; i++){

      digitalWrite(MOTOR1_IN1, LOW);
      digitalWrite(MOTOR1_IN2, HIGH);  

      analogWrite(SPEED_CONTROL1, 80);

      digitalWrite(MOTOR2_IN1, HIGH);
      digitalWrite(MOTOR2_IN2, LOW); 

      analogWrite(SPEED_CONTROL2, 80);
      
     }

}

void rotateRobotRight() {

    disableMotors();

    for(int i = 0; i < 30000; i++){

      digitalWrite(MOTOR1_IN1, HIGH);
      digitalWrite(MOTOR1_IN2, LOW);  

      analogWrite(SPEED_CONTROL1, 80);

      digitalWrite(MOTOR2_IN1, LOW);
      digitalWrite(MOTOR2_IN2, HIGH); 

      analogWrite(SPEED_CONTROL2, 80);
      
     }

}

void light_rotateRobotLeft() {

      digitalWrite(MOTOR1_IN1, LOW);
      digitalWrite(MOTOR1_IN2, HIGH);  

      analogWrite(SPEED_CONTROL1, 100);

      digitalWrite(MOTOR2_IN1, HIGH);
      digitalWrite(MOTOR2_IN2, LOW); 

      analogWrite(SPEED_CONTROL2, 100);
      


}

void light_rotateRobotRight() {


      digitalWrite(MOTOR1_IN1, HIGH);
      digitalWrite(MOTOR1_IN2, LOW);  

      analogWrite(SPEED_CONTROL1, 100);

      digitalWrite(MOTOR2_IN1, LOW);
      digitalWrite(MOTOR2_IN2, HIGH); 

      analogWrite(SPEED_CONTROL2, 100);
      
}


bool areSimilar(int right, int left){
  return abs(right - left) <= 100;
}
