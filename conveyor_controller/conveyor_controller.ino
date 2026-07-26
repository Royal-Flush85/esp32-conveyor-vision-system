

int motor1Pin1 = 17; 
int motor1Pin2 = 16; 
int enable1Pin = 5; 
const int motionPin = 4;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

void setup() {
  // sets the pins as outputs:
  pinMode(motionPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  ledcAttach(enable1Pin, freq, resolution);
  ledcWrite(enable1Pin, dutyCycle);

  Serial.begin(115200);
  delay(10000);
  Serial.println("Booting...");

  // testing
  Serial.print("Testing DC Motor...");
  ledcWrite(enable1Pin, dutyCycle); 
}

unsigned long previousMillis = 0;
const long forwardDuration = 2000;
const long stopDuration = 1000;

//defining states
enum State { IDLE, RUNNING, STOPPING };
State conveyorState = IDLE;

void loop() {
  unsigned long currentMillis = millis();

  int motionDetected = digitalRead(motionPin);

  switch(conveyorState) {
    case IDLE:
    if (motionDetected == HIGH) {
        Serial.println("Motion detected. Moving Forward.");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        previousMillis = currentMillis; // Start the timer
        conveyorState = RUNNING;
      }
      break;

    case RUNNING:
      // Has 2000ms passed?
      if (currentMillis - previousMillis >= forwardDuration) {
        Serial.println("Motor stopped");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        previousMillis = currentMillis; // Reset timer for the stop phase
        conveyorState = STOPPING;
      }
      break;

    case STOPPING:
      // Has 1000ms passed?
      if (currentMillis - previousMillis >= stopDuration) {
        // Ready to detect motion again
        conveyorState = IDLE; 
      }
      break;
  }
}





// past implementation
//  Serial.println(digitalRead(motionPin));
//  if (digitalRead(motionPin) == HIGH) {
//    Serial.println("Moving Forward");
//    digitalWrite(motor1Pin1, LOW);
//    digitalWrite(motor1Pin2, HIGH); 
//    delay(2000);
//  
//    // Stop the DC motor
//    Serial.println("Motor stopped");
//    digitalWrite(motor1Pin1, LOW);
//    digitalWrite(motor1Pin2, LOW);
//    delay(1000);
//  }
//  delay(500);
