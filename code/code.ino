#include <MyoController.h>
#define trigPin 12
#define echoPin 13
#include <Adafruit_MotorShield.h>


int inputPin=4; 
int outputPin=5; 

//Create the myo object 
MyoController myo = MyoController();

//Create the motor shield object 
Adafruit_MotorShield AFMS = Adafruit_MotorShield();  

//Select port M1 motor shield board  
Adafruit_DCMotor *M1 = AFMS.getMotor(1);    

//Select port M2 motor shield board 
Adafruit_DCMotor *M2 = AFMS.getMotor(2);

void setup() {
  
    Serial.begin(9600);           
    Serial.println("Adafruit Motorshield v2 - DC Motor test!");
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    AFMS.begin();  // create with the default frequency 1.6KHz
    
    myo.initMyo();
}

void loop() {

   //call getMyoGesture Function
   getMyoGestures();
   
   //set deley after method call 
   delay(75); 
  
}

void getMyoGestures(){
  
    myo.updatePose();
    
    switch ( myo.getCurrentPose() ) {
      case rest:
      
          //when the arm is relaxed RELEASE 
          M1->run(RELEASE);
          M2->run(RELEASE);
          break;
      case fist:
      
          //When the arm makes a fist set motor speed and drive motors FORWARD
          M1->setSpeed(150);
          M2->setSpeed(150);
          M1->run(FORWARD);
          M2->run(FORWARD);
          break;
      case waveIn:
      
          //When the arm makes a WaveIn set motor speed and drive one motor FORWARD and one motor BACKWARD
          M1->setSpeed(100);
          M2->setSpeed(100);
          M1->run(BACKWARD);
          M2->run(FORWARD);
          break;
      case waveOut:
      
          //When the arm makes a WaveIn set motor speed and drive one motor FORWARD and one motor BACKWARD    
          M1->setSpeed(100);
          M2->setSpeed(100);
          M1->run(FORWARD);
          M2->run(BACKWARD);
          break;
      case fingersSpread:
      
           //When the arm spreads the fingers set motor speed and drive motors BACKWARD
           M1->setSpeed(150);
           M2->setSpeed(150);
           M1->run(BACKWARD);
           M2->run(BACKWARD);
          break;
    }
}
