// Define pins
#define SIGNAL_A_PIN 32
#define SIGNAL_B_PIN 33

#define timeout 10000

// Global variables
int signalAFrequency = 0;
int signalBFrequency = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.setTimeout(timeout);

  // Set pin modes
  pinMode(SIGNAL_A_PIN, OUTPUT);
  pinMode(SIGNAL_B_PIN, OUTPUT);

  // Set up PWM channels
  ledcSetup(0, 0, 8);  // channel 0 for signal A
  ledcSetup(2, 0, 8);  // channel 2 for signal B
}

void loop() {
  // Ask user to enter signal
  Serial.println("Enter signal (A or B): ");
  
  // Wait for user input
  while (!Serial.available()) {
    // Wait for user input
  }

  // Read user input
  char signal = Serial.read();

  // Choose signal based on user input
  switch (signal) {
    case 'A':
      // Set signal A frequency
      Serial.println("Enter frequency for Signal A: ");
      while (!Serial.available()) {
        // Wait for user input
      }
      signalAFrequency = Serial.parseInt();

      // Set PWM frequency for signal A
      ledcWrite(0, 0);  // turn off signal A
      ledcSetup(0, signalAFrequency, 8);
      ledcAttachPin(SIGNAL_A_PIN, 0);
      ledcWrite(0, 127);  // turn on signal A
      break;

    case 'B':
      // Set signal B frequency
      Serial.println("Enter frequency for Signal B: ");
      while (!Serial.available()) {
        // Wait for user input
      }
      signalBFrequency = Serial.parseInt();

      // Set PWM frequency for signal B
      ledcWrite(2, 0);  // turn off signal B
      ledcSetup(2, signalBFrequency, 8);
      ledcAttachPin(SIGNAL_B_PIN, 2);
      ledcWrite(2, 127);  // turn on signal B
      break;

    default:
      Serial.println("Invalid signal. Please enter A or B.");
      break;
  }

}