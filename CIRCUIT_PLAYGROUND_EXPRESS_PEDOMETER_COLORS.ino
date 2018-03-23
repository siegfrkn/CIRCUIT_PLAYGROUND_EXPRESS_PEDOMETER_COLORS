///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Express Pedometer Color Change Neopixels
//
// Author: Katrina Siegfried
// MIT License (https://opensource.org/licenses/MIT)
// Based on the Circuit Playground Tap Code by Carter Nelson and Bike Light Rainbow Chaser by Carter Nelson
 
#include <Adafruit_CircuitPlayground.h>
 
#define TAP_THRESHOLD       50          // Tap detect threshold
#define ROTATION_RATE       200         // lower is faster
 
bool tapDetected;

// Define 10 colors here.
// Must be 10 entries.
// Use 0x000000 if you want a blank space.
uint32_t colors[] = {
  0xFF0000,   //RED
  0xFF5500,   //PURPLE
  0xFFFF00,   //YELLOW
  0x00FF00,   //LIME GREEN
  0x0000FF,   //BLUE
  0xFF00FF,   //FUCHSIA
  0xFF0000,   //RED
  0xFF5500,   //PURPLE
  0xFFFF00,   //YELLOW
  0x00FF00,   //LIME GREEN
};

int colorIndex;
int startIndex;

//// For future use
//unsigned long startTime;
//unsigned long endTime;
//unsigned long duration;
//byte timerRunning;
 
///////////////////////////////////////////////////////////////////////////////
void tapCallback() {
  tapDetected = true;
}
 
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
  Serial.begin(9600);
 
  CircuitPlayground.begin();

  CircuitPlayground.setBrightness(255);
  
  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
  CircuitPlayground.setAccelTap(1, TAP_THRESHOLD);
  
  attachInterrupt(digitalPinToInterrupt(36), tapCallback, FALLING);
 
  tapDetected = false;

  // Start at beginning
  startIndex = 0;
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {

//  // For future use
//  if (timerRunning == 0 && tapDetected == false){ // button pressed & just tapped
//  startTime = millis();
//  timerRunning = 1;
//  }
//  if (timerRunning == 1 && tapDetected == true){ // timer running, not in a tap
//  endTime = millis();
//  timerRunning = 0;
//  duration = endTime - startTime;
//  Serial.print ("button press time in milliseconds: ");
//  Serial.println (duration);
//  }

  // Turn off the Neopixels
  CircuitPlayground.clearPixels();
  
  if (tapDetected) {
    Serial.println("TAP!");

    CircuitPlayground.clearPixels();

    // Loop through and set pixels
    colorIndex = startIndex;
    for (int pixel=0; pixel<10; pixel++) {
      CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
      colorIndex++;
      if (colorIndex > 9) colorIndex = 0;
    }
   
    // Increment start index into color array
    startIndex++;
   
    // Check value and reset if necessary
    if (startIndex > 9) startIndex = 0;
   
    // Wait a little bit so we don't spin too fast
    delay(ROTATION_RATE);
    
    tapDetected = false;
    
  }


}
