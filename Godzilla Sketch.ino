#include <Adafruit_NeoPixel.h>

// NeoPixels Configuration
#define neopixelsPin    6
#define neopixelsCount 35
Adafruit_NeoPixel strip(neopixelsCount, neopixelsPin, NEO_GRB + NEO_KHZ800);

// Variables and junk
uint32_t blue = 255;        // This is just me setting the colours.  Change this if you want wicked different colours.
uint32_t greenred = 150;    // This is just me setting the colours.  Change this if you want wicked different colours.
int smokePin = 9;   // This is what the input pin of the relay connects to
int buttonPin = 2;  // This is what the +V of the button connects to
int buttonState = 0;  
int ledPin =  13;   // This is the internal led, don't change it.    

void setup() {
  // Set the Vape Pin to High
  digitalWrite(smokePin, HIGH);
  
  // Set the button pin to Input
  pinMode(buttonPin, INPUT);

  // Initialize the Neopixels
  strip.begin();           
  strip.show();            
  strip.setBrightness(255);

  // Set the smokePin and neoPin as outputs
  pinMode(smokePin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check for a button press
  buttonState = digitalRead(buttonPin);

  // If the button is pressed
  if (buttonState == HIGH) {
    // Turn the onboard light on - this is for debug
    digitalWrite(ledPin, HIGH);

    // Run the button action function
    buttonAction();
  } 


  // Wait 20 ms and then turn the onboard LED off.
  delay(20);
  digitalWrite(ledPin, LOW);
}

void buttonAction () {
  // Run the tailwipe function
  tailWipe(128); // Blue

  // Run the dip function
  dip(50,1);

  // Turn the smoker on
  smokeOn();

  // Run the blast function
  blast();
  for( uint32_t tStart = millis();  (millis()-tStart) < 5000;){
    // Run the crackle function
    crackle();
  }

  // Turn the smoker off
  smokeOff();

  // Clear the neopixels
  strip.clear();
  strip.show();
}

void smokeOn() {
  digitalWrite(smokePin, LOW);
}

void smokeOff() {
  digitalWrite(smokePin, HIGH);
}

// This is a slow building lightning effect up the spine
void tailWipe(int intensity) {
  for(int i=0; i<strip.numPixels()-2; i++) { // For each pixel in strip...
    for (int j=0;j<64;j++) {
      strip.setPixelColor(i,greenred*j/intensity,greenred*j/intensity,blue*j/intensity); // go from 192-255
      strip.show(); 
      for (int k=0;k<i-1;k++) {
        int randfluc = random(1,50);
        strip.setPixelColor(k,greenred*randfluc/100,greenred*randfluc/100,blue*randfluc/100);
      }
    }
  }
}


// This is a crackling effect on the whole strip, it simulates lightning
void crackle() {
  for(int i=0; i<strip.numPixels()-2; i++) { // For each pixel in strip...
    int randfluc = random(1,50);
    strip.setPixelColor(i,greenred*randfluc/100,greenred*randfluc/100,blue*randfluc/100);
  }
  strip.show();
}

void dip (int minbright,int wait) {
  for (int j=50;j>1;j=j-2) {
    for(int i=0; i<strip.numPixels()-2; i++) {
      strip.setPixelColor(i,greenred*j/100,greenred*j/100,blue*j/100);
      strip.show();
    }
  }
}

// This turns the last two pixels on the strip to MAX POWER!
void blast () {
  strip.setPixelColor(strip.numPixels()-1,greenred,greenred,blue);
  strip.setPixelColor(strip.numPixels()-2,greenred,greenred,blue);
}
