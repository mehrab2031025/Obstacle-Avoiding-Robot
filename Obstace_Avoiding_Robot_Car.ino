#include <AFMotor.h>
#include <Servo.h>
Servo servo;

AF_DCMotor LF(1);
AF_DCMotor LB(2);
AF_DCMotor RF(4);
AF_DCMotor RB(3);
#define trigPin  A0  
#define echoPin  A1  

void setup()
  {
    Serial.begin(9600);
    servo.attach(10);
    pinMode(trigPin, OUTPUT);          // Declare "trigPin" as "Output Pin". 
    pinMode(echoPin, INPUT);           // Declare "echoPin" as "Input Pin". 
    LF.setSpeed(100);
    LB.setSpeed(100);
    RF.setSpeed(100);
    RB.setSpeed(100);
  }

void loop()
  {
    float distance = 0.00;
    float RightDistance = 0.00;
    float LeftDistance = 0.00;    
    distance = search(); 
    Serial.println(distance); 
        
    if(distance <= 30) // If obstracle found in 40 CM.
      {
          RobotStop(); //Robot Stop
          delay(300);
          servo.write(10);
          delay(500);
          RightDistance = search();
          Serial.print("Right:");
          Serial.println(RightDistance);
          delay(200);
          servo.write(180);
          delay(500);
          LeftDistance = search();
          Serial.print("Left:");
          Serial.println(LeftDistance);
          delay(200);
          servo.write(90);
          delay(400);
         if(LeftDistance > RightDistance)
           { 
              RobotBackward();
              delay(100);
              RobotStop();
              delay(100);
              RobotLeft();
              delay(520);
              RobotStop();
              delay(100);  
           }
          else 
            {
              RobotBackward();
              delay(100);
              RobotStop();
              delay(100);
              RobotRight();
              delay(515); 
              RobotStop();
              delay(100);             
            }
      }
   else
   {
     RobotForward();
   }
}


float search(void)
  {
    float duration = 0.00;             // Float type variable declaration 
    float CM = 0.00;      
    digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level) 
    delayMicroseconds(2);              // Delay for 2 us    
    //Send 10us High Pulse to Ultra-Sonic Sonar Sensor "trigPin" 
    digitalWrite(trigPin, HIGH);       // Trig_pin output as 5V (Logic High-Level)
    delayMicroseconds(10);             // Delay for 10 us     
    digitalWrite(trigPin, LOW);        // Trig_pin output as OV (Logic Low-Level)    
    duration = pulseIn(echoPin, HIGH); // Start counting time, upto again "echoPin" back to Logical "High-Level" and puting the "time" into a variable called "duration" 
    CM = (33200*(duration/2))/1000000;
       
    return CM;
  }

void RobotForward()
{
  LF.run(FORWARD);
  RF.run(FORWARD);
  LB.run(FORWARD);
  RB.run(FORWARD);
}
void RobotBackward()
{
  LF.run(BACKWARD);
  LB.run(BACKWARD);
  RF.run(BACKWARD);
  RB.run(BACKWARD);
}
void RobotLeft()
{
  LF.run(BACKWARD);
  LB.run(BACKWARD);
  RF.run(FORWARD);
  RB.run(FORWARD);
}
void RobotRight()
{
  LF.run(FORWARD);
  LB.run(FORWARD);
  RF.run(BACKWARD);
  RB.run(BACKWARD);
}
void RobotStop()
{
  LF.run(RELEASE);
  LB.run(RELEASE);
  RF.run(RELEASE);
  RB.run(RELEASE);
}

  
