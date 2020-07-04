/*
  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when sensor (attached to pin 2) is activated

  The circuit:
  - LED attached from pin 13 to ground (default built in LED
  - sensor attached to pin 2 from +5V
*/

#define PIN_SENSOR  2       // the number of the pushbutton pin
#define PIN_LED     13      // the number of the LED pin


int sensorState = 0;        // current sensor status
int sensorPrevState = 0;    // previous sensor status
bool ledState = false;
bool ledBlinkOn = false;
int interval = 250;
int blinkDelay = 60000;
int blinkCounter = 0;
bool fallingEdgeDetected = false;

void setup() {
  Serial.begin(19200);
  delay(1000);

  Serial.println("HUMAN MON starting...");
  
  // initialize the LED pin as an output:
  pinMode(PIN_LED, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(PIN_SENSOR, INPUT);

  Serial.println("HUMAN MON started!");
}

void loop() {
  // read the state of the pushbutton value:
  sensorState = digitalRead(PIN_SENSOR);

  if ( (sensorState == false) && (sensorState != sensorPrevState)){ // falling edge
    fallingEdgeDetected = true;
    Serial.print("Sensor state changed to: ");
    Serial.println(sensorState);
  }
  sensorPrevState = sensorState;

  if (sensorState == HIGH) {
    fallingEdgeDetected = false;
    ledBlinkOn = true;
    blinkCounter = 0;
  } else {
    blinkLed(LOW, interval); // turn LED blink off:
  }

  if ((blinkCounter < blinkDelay) || (sensorState == HIGH)) {
    blinkLed(HIGH, interval); // turn LED blink on:
  }
  
  if(blinkCounter >= 5000){
    //blinkCounter = 0;
  }
}

void blinkLed(bool blink, int interval){
  if(blink){
    ledState = !ledState;
    digitalWrite(PIN_LED, ledState);
    delay(interval);

    if(fallingEdgeDetected)
      blinkCounter += interval;
  }
  else{
    digitalWrite(PIN_LED, LOW);
  }
}
