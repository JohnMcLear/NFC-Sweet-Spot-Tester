  /*******************************
  *
  * RESET THE MACHINE BACK TO 0,0 
  *
  ********************************/

// motors (x and y)
int pinXStep = 2;
int pinXDir = 3;
int pinYStep = 4;
int pinYDir = 5;

// Switches that are triggered when max and min Y are reached
int pinXSwitch = 12;
int pinYSwitch = 11;

int pinEnable  = 8; // not used...

//Direction Variables
int xCCW = LOW;
int xCW = HIGH;
int yCCW = LOW;
int yCW = HIGH;

int step = 10000; // The size of the step to take when resetting

int stepSpeed = 50*5; //milliseconds delay between pulses

long widthSteps = 105000;
long heightSteps = 140000;

long widthDivisions = 10;
long heightDivisions = 10;

int testDelay = 1000;
int sampleDelay = 1000;

int reset = 0; // has reset been completed?
int xReset = 0; // is X reset?
int yReset = 0; // is Y reset?

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  pinMode(pinXSwitch, INPUT);
  pinMode(pinYSwitch, INPUT);
 

  delay(500);
  pinMode(pinXStep, OUTPUT);
  pinMode(pinXDir, OUTPUT);

  pinMode(pinYStep, OUTPUT);
  pinMode(pinYDir, OUTPUT);  
  
  pinMode(pinEnable, OUTPUT);  
  digitalWrite(pinEnable, HIGH);
 
  delay(500);
  

}

void loop() {
  
  /*******************************
  *
  * RESET THE MACHINE BACK TO 0,0 
  *
  ********************************/
  
  if (reset == 0){ // Should we be resetting the position?
    // Until PinX Goes High Reset the motor
    Serial.println("Resetting");
    
    if(xReset == 0){
      Serial.println("Resetting X");
      while(digitalRead(pinXSwitch) == 0){ // While the switch isn't depressed
        Serial.println("Moving X back to 0");
        moveX(-500);
      }
      if(digitalRead(pinXSwitch) == 1){
        xReset = 1; 
      }
    }

    if(yReset == 0){
      Serial.println("Resetting Y");
      Serial.println(digitalRead(pinYSwitch));
      // Until PinY Goes High Reset the motor
      while(digitalRead(pinYSwitch) == 0){ // While the switch isn't depressed
        Serial.println("Moving Y back to 0");
        moveY(-500);
      }
      if(digitalRead(pinYSwitch) == 1){
        yReset = 1; 
      }
    }
    reset = 1; // reset is now completed, yay :)
  }
  
  /*******************************
  *
  * GO OVER THE TARGET DEVICE
  *
  ********************************/
  

  for(int height = 0; height < heightDivisions; height++){
    for(int width = 0; width <  widthDivisions; width++){
      moveY(widthSteps/widthDivisions);
      takeSample();      
    }

//    moveY(-widthSteps); 
      while(digitalRead(pinYSwitch) == 0){ // While the switch isn't depressed
        Serial.println("Moving Y back to 0");
        moveY(-500);
      }
    delay(testDelay);  
    moveX(heightSteps/heightDivisions);
    delay(testDelay);
  }    
  
  for(int width = 0; width <  widthDivisions; width++){
    moveY(widthSteps/widthDivisions);
    takeSample();      
  }
  moveY(-widthSteps);
  moveX(-heightSteps);
  delay(10000);
  
}
  
  

void takeSample(){
  delay(sampleDelay);
  
}

void moveY(long steps){
   if(steps < 0){
      digitalWrite(pinYDir, yCW);
   }else{
      digitalWrite(pinYDir, yCCW);  
   } 
  for(int i = 0; i < abs(steps); i++){
   digitalWrite(pinYStep, HIGH);
   delayMicroseconds(stepSpeed/2);
   digitalWrite(pinYStep, LOW);
   delayMicroseconds(stepSpeed/2);
  }   
} 
  
void moveX(long steps){
  Serial.print("Moving");
  Serial.print(steps);
   if(steps < 0){
      digitalWrite(pinXDir, xCW);
   }
   else{
      digitalWrite(pinXDir, xCCW);  
   } 
  for(int i = 0; i < abs(steps); i++){
   digitalWrite(pinXStep, HIGH);
   delayMicroseconds(stepSpeed/2);
   digitalWrite(pinXStep, LOW);
   delayMicroseconds(stepSpeed/2);
  }   
} 

