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

  if(sensorState != sensorPrevState){
    Serial.print("Sensor state changed to: ");
    Serial.println(sensorState);    
  }
  sensorPrevState = sensorState;

  if (sensorState == HIGH) {
    blinkLed(HIGH); // turn LED blink on:
  } else {
    blinkLed(LOW); // turn LED blink off:
  }
}

void blinkLed(bool blink){
  if(blink){
    ledState = !ledState;
    digitalWrite(PIN_LED, ledState);
    delay(500);
    digitalWrite(PIN_LED, ledState);
    delay(500);    
  }
  else{
    digitalWrite(PIN_LED, LOW);
  }
}
