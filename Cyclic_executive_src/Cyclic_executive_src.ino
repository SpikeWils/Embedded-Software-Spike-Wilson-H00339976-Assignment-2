/*
NOTES

Task 1 = Output signal
Task 2 = Measure square wave frequency 333-1000Hz
Task 3 = Measure square wave frequency 500-1000Hz
Task 4 = Read average analogue value & set LED
Task 5 = Map frequency of task 2 & 3 to 0-99 and print to serial monitor

*/

/*****************************************************
   PREPROCESSOR DIRECTIVES
*****************************************************/

#include <B31DGMonitor.h>
#include <Ticker.h>

#define SIGNAL_OUTPUT_PIN 17                          //Pin to output task1 signal
#define SQUARE_WAVE_1_PIN 33                          //Pin to read task2 signal
#define SQUARE_WAVE_2_PIN 32                          //Pin to read task3 signal
#define POT_PIN 36                                    //Pin to read task4 pot value
#define LED_PIN 19                                    //Pin to control task4 LED
#define FRAME_DURATION_MS 4                           //Frame duration (ms)
#define MAX_ANALOG_RANGE 4095                         //Max analog range of ADC

/*****************************************************
   DECLARE VARIABLES
*****************************************************/

const int SignalOutputPin = SIGNAL_OUTPUT_PIN;        //Declare task1 signal output pin
const int SquareWave1Pin = SQUARE_WAVE_1_PIN;         //Declare task2 signal pin
const int SquareWave2Pin = SQUARE_WAVE_2_PIN;         //Declare task3 signal pin
const int LEDpin = LED_PIN;                           //Declare task4 LED pin
const int PotPin = POT_PIN;                           //Declare task4 pot pin

unsigned int period_high1 = 0;                        //Declare variable for high period of measured square wave for task2
unsigned int period_high2 = 0;                        //Declare variable for high period of measured square wave for task3

int frequency1mapped = 0;                             //Declare variable for task5 to map frequency of task2 from 0>99
int frequency2mapped = 0;                             //Declare variable for task5 to map frequency of task3 from 0>99

float frequency1 = 0.0;                               //Declare variable for task2 to store measured frequency
float frequency2 = 0.0;                               //Declare variable for task3 to store measured frequency

unsigned long frameTime = 0;                          //Declare variable for frame time
unsigned long frameCounter = 0;                       //Declare variable for frame count

/*****************************************************
   DECLARE OBJECTS & CLASSES
*****************************************************/

Ticker ticker;                                        //Create ticker object
B31DGCyclicExecutiveMonitor monitor;                  //Create monitor object

/*****************************************************
   SETUP
*****************************************************/

void setup(void)
{
  Serial.begin(9600);                                 //Initialise serial communication @9600 baud

  while (!Serial);                                    //Wait for serial communication to be established
  {
    //Do nothing
  }
  
  Serial.println("Serial comm init");                 //Print to serial monitor

  monitor.startMonitoring();                          //Monitor object begin monitoring function
  frame();                                            //Call frame function
  ticker.attach_ms(FRAME_DURATION_MS, frame);         //ticker object call frame function at frame duration intervals

  pinMode(SignalOutputPin, OUTPUT);                   //Set pin as output
  pinMode(SquareWave1Pin, INPUT);                     //Set pin as input
  pinMode(SquareWave2Pin, INPUT);                     //Set pin as input
  pinMode(PotPin, INPUT);                             //Set pin as input
  pinMode(LEDpin, OUTPUT);                            //Set pin as output

}

/*****************************************************
   SCHEDULE
*****************************************************/

void frame()                                          //Declare frame function
{

  unsigned int slot = frameCounter % 10;              //Calculate remainder of framecounter/10 and store in slot
 
  switch (slot)
  {
    case 0:

      JobTask1();

      break;

    case 1:

      //JobTask2(SquareWave1Pin);

      break;

    case 2:

      JobTask1();

      break;

    case 3:

      JobTask4();

      break;

    case 4:

      //JobTask2(SquareWave1Pin);

      break;

    case 5:

      JobTask1();

      break;

    case 6:

      //JobTask2(SquareWave1Pin);

      break;

    case 7:

      JobTask1();

      break;

    case 8:

      JobTask1();

      break;

    case 9:

      //JobTask2(SquareWave1Pin);

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

/*-----------------
   TASK 1 JOBS
------------------*/

void JobTask1(void)                                   //Declare function JobTask1 [Output signal]
{
  monitor.jobStarted(1);                              //Call jobstarted function of monitor object

  digitalWrite(SignalOutputPin, HIGH);                //Set pin HIGH
  delayMicroseconds(200);                             //Wait 200µS
  digitalWrite(SignalOutputPin,LOW);                  //Set pin low
  delayMicroseconds(50);                              //Wait 50µS
  digitalWrite(SignalOutputPin, HIGH);                //Set pin high
  delayMicroseconds(30);                              //Wait 30µS
  digitalWrite(SignalOutputPin,LOW);                  //Set pin low

  monitor.jobEnded(1);                                //Call jobended function of monitor object
}

/*-----------------
   TASK 2 JOBS
------------------*/

float JobTask2a(int SquareWave1Pin)                    //Declare function JobTask2 [Measure square wave frequency]
{
  monitor.jobStarted(2);                              //Call jobstarted function of monitor object
  
  period_high1 = pulseIn(SquareWave1Pin, HIGH);    //Measure the period_high1 of the input signal using the pulseIn function

  monitor.jobEnded(2);                                //Call jobended function of monitor object
}

//--------------------

float JobTask2b(int SquareWave1Pin)                    //Declare function JobTask2 [Measure square wave frequency]
{
  monitor.jobStarted(2);                              //Call jobstarted function of monitor object

  frequency1 = 1.0 / ((period_high1 * 2) * 0.000001);           //Calculate the frequency from the period_high1 [high period multiplied by 2 as square wave is symmetrical]

  return frequency1;                                  //Return value of frequency1 and terminate function

  monitor.jobEnded(2);                                //Call jobended function of monitor object
}

/*-----------------
   TASK 3 JOBS
------------------*/

float JobTask3a(int SquareWave2Pin)                    //Declare function JobTask3 [Measure square wave frequency]
{
  monitor.jobStarted(3);                              //Call jobstarted function of monitor object

  period_high2 = pulseIn(SquareWave2Pin, HIGH);    //Measure the period_high2 of the input signal using the pulseIn function

  monitor.jobEnded(3);                                //Call jobended function of monitor object
}

//--------------------

float JobTask3b(int SquareWave2Pin)                    //Declare function JobTask3 [Measure square wave frequency]
{
  monitor.jobStarted(3);                              //Call jobstarted function of monitor object

  frequency2 = 1.0 / ((period_high2 * 2) * 0.000001);           //Calculate the frequency from the period_high2 [high period multiplied by 2 as square wave is symmetrical]
  
  return frequency2;                                  //Return value of frequency2 and terminate function

  monitor.jobEnded(3);                                //Call jobended function of monitor object
}

/*-----------------
   TASK 4 JOBS
------------------*/

void JobTask4(void)                                   //Declare function JobTask4 [Read analog val]
{
  monitor.jobStarted(4);                              //Call jobstarted function of monitor object

  int reading1 = analogRead(PotPin);                  //Declare int and initialise with value of analogRead
  int reading2 = analogRead(PotPin);                  //Declare int and initialise with value of analogRead
  int reading3 = analogRead(PotPin);                  //Declare int and initialise with value of analogRead
  int reading4 = analogRead(PotPin);                  //Declare int and initialise with value of analogRead
  int readingavg = (reading1 + reading2 + reading3 + reading4) / 4;          //Declare int and calculate average of readings

  if (readingavg > (MAX_ANALOG_RANGE/2))                          //If average > half total analog range
  {
  digitalWrite(LEDpin, HIGH);                                     //Light LED
  }

  else                                                            //Otherwise
  {
  digitalWrite(LEDpin, LOW);                                      //Do not light LED
  }

  monitor.jobEnded(4);                                //Call jobended function of monitor object
}

/*-----------------
   TASK 5 JOBS
------------------*/

void JobTask5a(void)                                   //Declare function JobTask5 [Map & print frequency vals]
{
  monitor.jobStarted(5);                              //Call jobstarted function of monitor object

  frequency1mapped = map(frequency1, 333, 1000, 0, 99);   //Map value of frequency1 (333>1000Hz) to (0>99) and store in variable frequency1mapped
  frequency2mapped = map(frequency2, 500, 1000, 0, 99);   //Map value of frequency2 (500>1000Hz) to (0>99) and store in variable frequency1mapped

  monitor.jobEnded(5);                                //Call jobended function of monitor object
}

//--------------------

void JobTask5b(void)                                   //Declare function JobTask5 [Map & print frequency vals]
{
  monitor.jobStarted(5);                              //Call jobstarted function of monitor object

  Serial.print(frequency1mapped);                     //Print value of frequency1mapped to serial monitor
  Serial.print(", ");                                 //Print to serial monitor
  Serial.println(frequency2mapped);                   //Print value of frequency2mapped to serial monitor on new line

  monitor.jobEnded(5);                                //Call jobended function of monitor object
}



