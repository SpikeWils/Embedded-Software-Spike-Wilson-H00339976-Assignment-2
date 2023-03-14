/*
NOTES

Task 1 = Output signal
Task 2 = Measure square wave frequency 333-1000Hz
Task 3 = Measure square wave frequency 500-1000Hz
Task 4 = 
Task 5 =

*/

/*****************************************************
   PREPROCESSOR DIRECTIVES
*****************************************************/

#include <B31DGMonitor.h>
#include <Ticker.h>

#define SIGNAL_OUTPUT_PIN 17
#define SQUARE_WAVE_1_PIN 33
#define SQUARE_WAVE_2_PIN 32
#define FRAME_DURATION_MS 2  // 2ms

/*****************************************************
   DECLARATIONS
*****************************************************/

int SignalOutputPin = SIGNAL_OUTPUT_PIN;
int SquareWave1Pin = SQUARE_WAVE_1_PIN;
int SquareWave2Pin = SQUARE_WAVE_2_PIN;

int inputPin = 13;
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
      JobTask3();

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
  unsigned int period_high = pulseIn(SquareWave1Pin, HIGH);
  //unsigned int period_low = pulseIn(inputPin, LOW);

  // calculate the frequency from the period~_high and print it to the serial monitor
  float frequency = 1.0 / ((period_high * 2) * 0.000001);
  
  Serial.print(frequency);

  return frequency;
  monitor.jobEnded(2);
}


void JobTask3(void)
{
  monitor.jobStarted(3);
  delayMicroseconds(1000);
  monitor.jobEnded(3);
}


void JobTask4(void)
{
  monitor.jobStarted(4);
  delayMicroseconds(2000);
  monitor.jobEnded(4);
}


void JobTask5(void)
{
  monitor.jobStarted(5);
  delayMicroseconds(2000);
  monitor.jobEnded(5);
}