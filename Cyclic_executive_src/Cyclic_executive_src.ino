/*
NOTES

Task 1 = Output signal
Task 2 = Measure square wave frequency 333-1000Hz
Task 3 = Measure square wave frequency 500-1000Hz
Task 4 = Read average analogue value & set LED
Task 5 = Print frequency of task 2 & 3 and map it to 0-99

*/

/*****************************************************
   PREPROCESSOR DIRECTIVES
*****************************************************/

#include <B31DGMonitor.h>
#include <Ticker.h>

#define SIGNAL_OUTPUT_PIN 17
#define SQUARE_WAVE_1_PIN 33
#define SQUARE_WAVE_2_PIN 32
#define POT_PIN 36
#define LED_PIN 19
#define FRAME_DURATION_MS 2  // 2ms

/*****************************************************
   DECLARATIONS
*****************************************************/

int SignalOutputPin = SIGNAL_OUTPUT_PIN;
int SquareWave1Pin = SQUARE_WAVE_1_PIN;
int SquareWave2Pin = SQUARE_WAVE_2_PIN;
int LEDpin = LED_PIN;
int PotPin = POT_PIN;
float frequency1 = 0.0;
float frequency2 = 0.0;
int frequency1mapped = 0;
int frequency2mapped = 0;


unsigned long frameTime = 0;
unsigned long frameCounter = 0;

Ticker ticker;
B31DGCyclicExecutiveMonitor monitor;

/*****************************************************
   SETUP
*****************************************************/

void setup(void)
{
  Serial.begin(9600);
  while (!Serial);
  monitor.startMonitoring();
  Serial.println("Ready");
  frame();
  ticker.attach_ms(4, frame);

  pinMode(PotPin, INPUT);
  pinMode(LEDpin, OUTPUT);

}

/*****************************************************
   SCHEDULE
*****************************************************/

void frame()
{

  unsigned int slot = frameCounter % 10;
  switch (slot) {
    case 0:

      JobTask1();

      break;

    case 1:

      JobTask2(SquareWave1Pin);

      break;

    case 2:

      JobTask1();

      break;

    case 3:

      JobTask4();

      break;

    case 4:

      JobTask2(SquareWave1Pin);

      break;

    case 5:

      JobTask1();

      break;

    case 6:

      JobTask2(SquareWave1Pin);

      break;

    case 7:

      JobTask1();

      break;

    case 8:

      JobTask1();

      break;

    case 9:

      JobTask2(SquareWave1Pin);

      break;
  }
}

/*****************************************************
   MAIN LOOP
*****************************************************/

void loop(void)
{

}

/*****************************************************
   TASK FUNCTIONS
*****************************************************/

float JobTask1(void)
{
  monitor.jobStarted(1);

  digitalWrite(SignalOutputPin, HIGH);
  delayMicroseconds(200);
  digitalWrite(SignalOutputPin,LOW);
  delayMicroseconds(50);
  digitalWrite(SignalOutputPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(SignalOutputPin,LOW);

  monitor.jobEnded(1);
}



float JobTask2(int SquareWave1Pin)
{
  monitor.jobStarted(2);
  // measure the period~_high of the input signal using the pulseIn function
  unsigned int period_high1 = pulseIn(SquareWave1Pin, HIGH);
  //unsigned int period_low = pulseIn(inputPin, LOW);

  // calculate the frequency from the period~_high and print it to the serial monitor
  frequency1 = 1.0 / ((period_high1 * 2) * 0.000001);
  
  Serial.print(frequency1);

  return frequency1;
  monitor.jobEnded(2);
}


float JobTask3(int SquareWave2Pin)
{
  monitor.jobStarted(3);
  // measure the period~_high of the input signal using the pulseIn function
  unsigned int period_high2 = pulseIn(SquareWave2Pin, HIGH);
  //unsigned int period_low = pulseIn(inputPin, LOW);

  // calculate the frequency from the period~_high and print it to the serial monitor
  frequency2 = 1.0 / ((period_high2 * 2) * 0.000001);
  
  Serial.print(frequency2);

  return frequency2;
  monitor.jobEnded(3);
}



void JobTask4(void)
{
  monitor.jobStarted(4);
  int reading1 = analogRead(PotPin);
  int reading2 = analogRead(PotPin);
  int reading3 = analogRead(PotPin);
  int reading4 = analogRead(PotPin);
  int readingavg = (reading1 + reading2 + reading3 + reading4) / 4;

  if (readingavg > (4095/2))
  {
  digitalWrite(LEDpin, HIGH);
  }
  else
  {
  digitalWrite(LEDpin, LOW);
  }
  monitor.jobEnded(4);
}


void JobTask5(void)
{
  monitor.jobStarted(5);

  frequency1mapped = map(frequency1, 333, 1000, 0, 99);
  frequency2mapped = map(frequency2, 500, 1000, 0, 99);

  Serial.print(frequency1mapped);
  Serial.print(",");
  Serial.println(frequency2mapped);

  monitor.jobEnded(5);
}