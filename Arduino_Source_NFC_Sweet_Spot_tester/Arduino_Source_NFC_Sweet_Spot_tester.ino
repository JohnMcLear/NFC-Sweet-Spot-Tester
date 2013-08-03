

//Pin Definitions
int pinXStep = 2;
int pinXDir = 3;

int pinYStep = 4;
int pinYDir = 5;

int pinEnable  = 8;

//Direction Variables
int xCCW = LOW;
int xCW = HIGH;

int yCCW = LOW;
int yCW = HIGH;

int stepSpeed = 50*5; //milliseconds delay between pulses

long widthSteps = 105000/5;
long heightSteps = 140000/5;

long widthDivisions = 4;
long heightDivisions = 4;

int testDelay = 1000;
int sampleDelay = 1000;

void setup() {
  delay(5000);
  pinMode(pinXStep, OUTPUT);
  pinMode(pinXDir, OUTPUT);

  pinMode(pinYStep, OUTPUT);
  pinMode(pinYDir, OUTPUT);  
  
  pinMode(pinEnable, OUTPUT);  
  digitalWrite(pinEnable, HIGH);

}

void loop() {
  for(int height = 0; height < heightDivisions; height++){
     for(int width = 0; width <  widthDivisions; width++){
       moveY(widthSteps/widthDivisions);
       takeSample();      
     }
  moveY(-widthSteps); 
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

