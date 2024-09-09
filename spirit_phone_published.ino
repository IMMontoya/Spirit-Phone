#include <Arduino.h>

// Description: Controls an 'old-timey' telephone to play radio waves through the listening piece
// when the phone is off the hook. Calls a ringing pattern after a randomly chosen interval when phone is on the hook.

// Enum to represent operation modes
enum Mode { BellMode, RadioMode } currentMode;

// Pin definitions
const int BELL_PIN = 2;
const int RADIO_PIN = 4;
const int LED_PIN = 6; // Powers an LED to keep current draw above battery pack's threshold
const int SENSOR_PIN = A0; // Analog pin for reading the sensor value

// Threshold value for switching between modes
const int THRESHOLD = 1015;

// Declare a range for generating a random interval between Rings
// Define a Structure for the Range
struct Range {
  int min;
  int max;
};

Range RING_INVERVAL = {(5*60), (10*60)}; // Arguments in seconds


// 'Wait' for a specified number of deciseconds. Constantly checks the sensor value at each decisecond.
bool Wait_Decisecond(int deciseconds) {
  unsigned long startMillis = millis();
  int decisecondCount = 0;

  while (decisecondCount < deciseconds) {
    unsigned long currentMillis = millis();

    // Perform the sensor check at each decisecond
    if (readSensorValue() < THRESHOLD) {
      digitalWrite(BELL_PIN, LOW); // Turn off Bell if sensor value drops below threshold
      Serial.println("Wait ABORTED: Sensor value below threshold.");
      return false; // Exit the function early if the condition is met, return false
    }

    // Check if a decisecond has passed
    if (currentMillis - startMillis >= 100) {
      startMillis = currentMillis; // Update startMillis to the current time
      decisecondCount++; // Increment the count of deciseconds that have passed

      // Debug info printed once every decisecond
      Serial.print("Mode: ");
      Serial.println(currentMode == BellMode ? "BellMode" : "RadioMode");
      Serial.print("Sensor Value: ");
      Serial.println(readSensorValue());
    }

    // Here, you can place other non-blocking tasks that should run during the wait, if needed.
  }
  
  return true; // If the loop completes without the condition being met, return true
}

// Produce the 3-ring pattern
void ThreeRingBell() {
  for (int i = 0; i < 3; i++) {
    if (readSensorValue() < THRESHOLD) {
      digitalWrite(BELL_PIN, LOW); // Exit if sensor value drops below threshold
      return;
    }
    digitalWrite(BELL_PIN, HIGH);
    delay(500); // Ring for half a second
    digitalWrite(BELL_PIN, LOW);
    if (readSensorValue() < THRESHOLD) {
      return;
    }
    delay(500); // Half a second
  }
}

// Read Sensor Value Function. Returns the median value of a sample of readings.
#define SAMPLE_SIZE 50

int readSensorValue() {
  int sensorValues[SAMPLE_SIZE];

  // Step 1: Gather readings
  for(int i = 0; i < SAMPLE_SIZE; i++) {
    sensorValues[i] = analogRead(SENSOR_PIN); 
    delay(1); // Short delay to prevent reading the sensor too rapidly
  }

  // Step 2: Sort the array - simple insertion sort
  for (int i = 1; i < SAMPLE_SIZE; i++) {
    int key = sensorValues[i];
    int j = i - 1;

    // Move elements of sensorValues[0..i-1], that are greater than key, to one position ahead of their current position
    while (j >= 0 && sensorValues[j] > key) {
      sensorValues[j + 1] = sensorValues[j];
      j = j - 1;
    }
    sensorValues[j + 1] = key;
  }

  // Step 3: Find the median
  int medianValue;
  if (SAMPLE_SIZE % 2 == 0) {
    medianValue = (sensorValues[SAMPLE_SIZE/2] + sensorValues[(SAMPLE_SIZE/2) - 1]) / 2;
  } else {
    medianValue = sensorValues[SAMPLE_SIZE/2];
  }

  return medianValue;
}


// Setup routine
void setup() {
  Serial.begin(9600);
  pinMode(BELL_PIN, OUTPUT);
  pinMode(RADIO_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Ensure LED is on to maintain current draw, keeps battery pack from shutting off.
  randomSeed(analogRead(0));
}

// Main Loop Routine
void loop() {
  if (readSensorValue() >= THRESHOLD) {
    currentMode = BellMode;
    digitalWrite(BELL_PIN, LOW);
    digitalWrite(RADIO_PIN, LOW);

    // Debug output
    Serial.print("Mode: ");
    Serial.println(currentMode == BellMode ? "BellMode" : "RadioMode");
    Serial.print("Sensor Value: ");
    Serial.println(readSensorValue());
    int randomSeconds = random(RING_INVERVAL.min, RING_INVERVAL.max); // Generate a random delay
    
    // Convert seconds to deciseconds, wait, and proceed based on the return value
    if (Wait_Decisecond(randomSeconds * 10)) { // If true, the wait was completed without interruption. Ring the Bell
      ThreeRingBell();
    } else {
      // If false, the wait was aborted. Continue with the next loop iteration.
      return; // Early return to start the next iteration of the loop
    }

  } else {
    currentMode = RadioMode;
    digitalWrite(RADIO_PIN, HIGH);
    digitalWrite(BELL_PIN, LOW);

    // Debug output
    Serial.print("Mode: ");
    Serial.println(currentMode == BellMode ? "BellMode" : "RadioMode");
    Serial.print("Sensor Value: ");
    Serial.println(readSensorValue());
  }
  
}
