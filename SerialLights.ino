// define the pin numberings
const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;
const int H = 9;
const int I = 10;

// instantiate other global variables
int i = 0;
const int chanCount = 9;
int incomingByte[chanCount + 1];
boolean frameComplete = false;
byte prevbyte = 0;
byte inbyte = 0;

// setup function runs once at beginning of program
void setup()
{
  // initialize the serial connection at 9600 baud
  Serial.begin(9600);

  // set all the pins as outputs for controlling the relays
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
  pinMode(I, OUTPUT);

  // run the test function
  setupTest();
}

// test function to make sure each relay is working.
// it turns on each relay one-by-one for 500 milliseconds 
void setupTest()
{
  digitalWrite(A,HIGH);
  delay(500);
  digitalWrite(A,LOW);
  digitalWrite(B,HIGH);
  delay(500);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  delay(500);
  digitalWrite(C,LOW);
  digitalWrite(D,HIGH);
  delay(500);
  digitalWrite(D,LOW);
  digitalWrite(E,HIGH);
  delay(500);
  digitalWrite(E,LOW);
  digitalWrite(F,HIGH);
  delay(500);
  digitalWrite(F,LOW);
  digitalWrite(G,HIGH);
  delay(500);
  digitalWrite(G,LOW);
  digitalWrite(H,HIGH);
  delay(500);
  digitalWrite(H,LOW);
  digitalWrite(I,HIGH);
  delay(500);
  digitalWrite(I,LOW);
}

// the loop runs continuously after the setup is complete
void loop()
{
  // listen for new serial data
  serialCatch();

  // if we have a complete frame of data, then write it to the output pins
  if (frameComplete == true) {
    digitalWrite(A, incomingByte[0]);
    digitalWrite(B, incomingByte[1]);
    digitalWrite(C, incomingByte[2]);
    digitalWrite(D, incomingByte[3]);
    digitalWrite(E, incomingByte[4]);
    digitalWrite(F, incomingByte[5]);
    digitalWrite(G, incomingByte[6]);
    digitalWrite(H, incomingByte[7]);
    digitalWrite(I, incomingByte[8]);

    // reset variables to go catch the next frame of data
    frameComplete = false;
    i = 0;
  }
}

// function for capturing one frame of serial data
void serialCatch() {
  
  //loop is true as long as data is in the serial receive buffer
  while(Serial.available()) {
    prevbyte = inbyte;
    inbyte = Serial.read();
//    Serial.println((char)inbyte);

    // if true, then we are at the end of the footer
    // the footer is >?
    if (prevbyte == 62 && inbyte == 63) {
//      Serial.println("found footer");
      frameComplete = true;
      return;
    }
    else {
      incomingByte[i] = inbyte;
    }
    i++;
  }
}
