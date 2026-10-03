// ESP32-S3 PIR-Triggered DC Motor Controller
//
// HC-SR501 PIR sensor triggers the motor.
// A finite-state machine controls timed motor operation without
// blocking delay() calls.

const int motorPin1 = 17;
const int motorPin2 = 16;
const int enablePin = 5;
const int pirPin = 4;

// PWM configuration
const int pwmFrequency = 30000;
const int pwmResolution = 8;
const int dutyCycle = 200;

// Timing
const unsigned long runDuration = 2000;   // Motor runs for 2 seconds
const unsigned long stopDuration = 1000;  // Wait 1 second before re-arming

enum State {
    IDLE,
    RUNNING,
    STOPPING
};

State motorState = IDLE;
unsigned long stateStartTime = 0;

void setup() {
    pinMode(pirPin, INPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(enablePin, OUTPUT);

    // Configure PWM for motor enable
    ledcAttach(enablePin, pwmFrequency, pwmResolution);
    ledcWrite(enablePin, dutyCycle);

    // Start with motor stopped
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);

    Serial.begin(115200);
    Serial.println("PIR-triggered motor controller started.");
}

void loop() {
    unsigned long currentTime = millis();
    int motionDetected = digitalRead(pirPin);

    switch (motorState) {

        case IDLE:
            if (motionDetected == HIGH) {
                Serial.println("Motion detected - motor started.");

                digitalWrite(motorPin1, LOW);
                digitalWrite(motorPin2, HIGH);

                stateStartTime = currentTime;
                motorState = RUNNING;
            }
            break;

        case RUNNING:
            if (currentTime - stateStartTime >= runDuration) {
                Serial.println("Motor stopped.");

                digitalWrite(motorPin1, LOW);
                digitalWrite(motorPin2, LOW);

                stateStartTime = currentTime;
                motorState = STOPPING;
            }
            break;

        case STOPPING:
            if (currentTime - stateStartTime >= stopDuration) {
                Serial.println("System ready for motion detection.");
                motorState = IDLE;
            }
            break;
    }
}
