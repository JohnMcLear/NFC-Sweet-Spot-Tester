#include <Ethernet.h>
#include <SPI.h>

/*******************************
*
* Ethernet Config
*
********************************/
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 177);
EthernetServer server(80);

/*******************************
*
* PIN DECLARATIONS
*
********************************/

// motors (x and y)
int pinXStep = 2;
int pinXDir = 3;
int pinYStep = 4;
int pinYDir = 5;

// Switches that are triggered when max and min Y are reached
int pinXSwitch = 9;
int pinYSwitch = 8;

/*******************************
*
* ENVIRONMENT DECLARATIONS
*
********************************/

//Direction Variables
int xCCW = LOW;
int xCW = HIGH;
int yCCW = LOW;
int yCW = HIGH;

int x = 0; // current X position
int y = 0; // current Y position

int step = 10000; // The size of the step to take when resetting

int stepSpeed = 50*5; //milliseconds delay between pulses

long widthSteps = 105000; // The Width we should move across (Y)
long heightSteps = 120000; // The Height we should move across (X)
long widthDivisions = 10; // How many steps across should we take on our journey?
long heightDivisions = 10; // How many steps up should we take on our journey?

int testDelay = 1000; // The delay to wait for to move to the next point
int sampleDelay = 1000; // The delay to wait for the NFC to register.

int reset = 0; // has reset been completed?
int xReset = 0; // is X reset?
int yReset = 0; // is Y reset?

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  
  // Begin Ethernet Stuff
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
  
  // set pin Modes
  //pinMode(pinXSwitch, INPUT);
  //pinMode(pinYSwitch, INPUT);
  
  // delay(500);
  pinMode(pinXStep, OUTPUT);
  pinMode(pinXDir, OUTPUT);

  pinMode(pinYStep, OUTPUT);
  pinMode(pinYDir, OUTPUT);
  
  // delay(500);

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
        // Serial.println("Moving X back to 0");
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
        // Serial.println("Moving Y back to 0");
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

    while(digitalRead(pinYSwitch) == 0){ // While the switch isn't depressed
        // Serial.println("Moving Y back to 0");
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
  EthernetClient client = server.available();
  if (client) { // Note that the client will only respond if we're not in a delay (blocking...)
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
      
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><body>");
          // output the value of each analog input pin
          client.print(x);       
          client.print(",");
          client.print(y);       
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    client.stop();
  }
  // End Ethernet stuff
  
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

