/*
     ▄▄▄        ██████   ██████  ██▓  ▄████  ███▄    █  ███▄ ▄███▓▓█████  ███▄    █ ▄▄▄█████▓   ▄▄▄█████▓ █     █░ ▒█████  
    ▒████▄    ▒██    ▒ ▒██    ▒ ▓██▒ ██▒ ▀█▒ ██ ▀█   █ ▓██▒▀█▀ ██▒▓█   ▀  ██ ▀█   █ ▓  ██▒ ▓▒   ▓  ██▒ ▓▒▓█░ █ ░█░▒██▒  ██▒
    ▒██  ▀█▄  ░ ▓██▄   ░ ▓██▄   ▒██▒▒██░▄▄▄░▓██  ▀█ ██▒▓██    ▓██░▒███   ▓██  ▀█ ██▒▒ ▓██░ ▒░   ▒ ▓██░ ▒░▒█░ █ ░█ ▒██░  ██▒
    ░██▄▄▄▄██   ▒   ██▒  ▒   ██▒░██░░▓█  ██▓▓██▒  ▐▌██▒▒██    ▒██ ▒▓█  ▄ ▓██▒  ▐▌██▒░ ▓██▓ ░    ░ ▓██▓ ░ ░█░ █ ░█ ▒██   ██░
     ▓█   ▓██▒▒██████▒▒▒██████▒▒░██░░▒▓███▀▒▒██░   ▓██░▒██▒   ░██▒░▒████▒▒██░   ▓██░  ▒██▒ ░      ▒██▒ ░ ░░██▒██▓ ░ ████▓▒░
     ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░▒ ▒▓▒ ▒ ░░▓   ░▒   ▒ ░ ▒░   ▒ ▒ ░ ▒░   ░  ░░░ ▒░ ░░ ▒░   ▒ ▒   ▒ ░░        ▒ ░░   ░ ▓░▒ ▒  ░ ▒░▒░▒░ 
      ▒   ▒▒ ░░ ░▒  ░ ░░ ░▒  ░ ░ ▒ ░  ░   ░ ░ ░░   ░ ▒░░  ░      ░ ░ ░  ░░ ░░   ░ ▒░    ░           ░      ▒ ░ ░    ░ ▒ ▒░ 
      ░   ▒   ░  ░  ░  ░  ░  ░   ▒ ░░ ░   ░    ░   ░ ░ ░      ░      ░      ░   ░ ░   ░           ░        ░   ░  ░ ░ ░ ▒  
         ░  ░      ░        ░   ░        ░          ░        ░      ░  ░         ░                          ░        ░ ░  
                                                                                                                       


      __  _            _   _                   _    __  _       _  _      ___ _   _  
     (_  / \ | |  /\  |_) |_   \    / /\ \  / |_   /__ |_ |\ | |_ |_)  /\  | / \ |_) 
     __) \_X |_| /--\ | \ |_    \/\/ /--\ \/  |_   \_| |_ | \| |_ | \ /--\ | \_/ | \ 
    ---------------------------------------------------------------------------------
    1. Using serial monitor, input either 'A' or 'B' and press enter to select a signal source.
    2. Enter the frequency in Hertz (Hz) of the signal and press enter
    3. The microcontroller will output the desired frequency on the specified channel with a 50% duty cycle                                                                             
*/



/*****************************************************
   DEFINE CONSTANTS
*****************************************************/

#define SIGNAL_A_PIN 32                                         //Signal A output pin
#define SIGNAL_B_PIN 33                                         //Signal B output pin
#define timeout 60000                                           //Set serial timeout

/*****************************************************
   DECLARE GLOBAL VARIABLES
*****************************************************/

int signalAFrequency = 0;                                       //Declare variable for signal A frequency with initial value of 0 (Hz)
int signalBFrequency = 0;                                       //Declare variable for signal B frequency with initial value of 0 (Hz)

/*****************************************************
   INITIALISATION CODE
*****************************************************/

void setup()
{
  
  Serial.begin(9600);                                           //Initialise serial communication
  Serial.setTimeout(timeout);                                   //Set max time to wait for serial input

 
  pinMode(SIGNAL_A_PIN, OUTPUT);                                //Declare signal A pin as output
  pinMode(SIGNAL_B_PIN, OUTPUT);                                //Declare signal A pin as output

  
  ledcSetup(0, 0, 8);                                           //Initialise PWM channel for signal A (channel, frequency, bit_resolution)
  ledcSetup(2, 0, 8);                                           //Initialise PWM channel for signal A (channel, frequency, bit_resolution)
}

/*****************************************************
   MAIN PROGRAM
*****************************************************/

void loop()
{

  
  Serial.println("Enter signal (A or B): ");                    //Print to serial monitor on new line
  
  
  while (!Serial.available())                                   //While no bytes available in serial buffer carry out loop
  {
                                                                //Wait for user input
  }


  char signal_selection = Serial.read();                        //Read user input from serial buffer and store it in signal_selection

 
  switch (signal_selection)                                     //Switch expression dependent on user input
  {
    case 'A':                                                   //Input A
      
      Serial.println("Enter frequency for Signal A: ");         //Print to serial monitor on new line
      while (!Serial.available())                               //While no bytes available in serial buffer carry out loop
      {
                                                                //Wait for user input
      }

      signalAFrequency = Serial.parseInt();                     //Look for the next valid integer in the incoming serial (until serial timeout elapses)
      
      ledcWrite(0, 0);                                          //Write to PWM channel 0 (channel, duty_cycle) [Duty cycle 0 = 0%]
      ledcSetup(0, signalAFrequency, 8);                        //Write to PWM channel for signal A (channel, frequency, bit_resolution)
      ledcAttachPin(SIGNAL_A_PIN, 0);                           //Attach pin to PWM channel (pin, channel)
      ledcWrite(0, 127);                                        //Write to PWM channel 0 (channel, duty_cycle) [Duty cycle 127 = 50%]
      
      Serial.println("\n---------------------------------------");
      Serial.print("Signal A frequency set: " );
      Serial.print(signalAFrequency);
      Serial.println("Hz");
      Serial.println("--------------------------------------- \n");

      break;                                                    //End case A statement

    case 'B':                                                   //Input B
      
      Serial.println("Enter frequency for Signal B: ");         //Print to serial monitor on new line
      while (!Serial.available())                               //While no bytes available in serial buffer carry out loop
      {
                                                                //Wait for user input
      }

      signalBFrequency = Serial.parseInt();                     //Look for the next valid integer in the incoming serial (until serial timeout elapses)

      ledcWrite(2, 0);                                          //Write to PWM channel 2 (channel, duty_cycle) [Duty cycle 0 = 0%]
      ledcSetup(2, signalBFrequency, 8);                        //Write to PWM channel for signal B (channel, frequency, bit_resolution)
      ledcAttachPin(SIGNAL_B_PIN, 2);                           //Attach pin to PWM channel (pin, channel)
      ledcWrite(2, 127);                                        //Write to PWM channel 2 (channel, duty_cycle) [Duty cycle 127 = 50%]
      
      Serial.println("\n---------------------------------------");
      Serial.print("Signal B frequency set: " );
      Serial.print(signalBFrequency);
      Serial.println("Hz");
      Serial.println("--------------------------------------- \n");
      
      break;                                                    //End case A statement

    default:                                                    //Default case statement if no case match found
      Serial.println("Invalid signal. Please enter A or B.");   //Print to serial monitor on new line
      break;                                                    //End case A statement
  }

}


/*
     ██▓███   ██▀███   ▒█████    ▄████  ██▀███   ▄▄▄       ███▄ ▄███▓   ▓█████  ███▄    █ ▓█████▄ 
    ▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒ ██▒ ▀█▒▓██ ▒ ██▒▒████▄    ▓██▒▀█▀ ██▒   ▓█   ▀  ██ ▀█   █ ▒██▀ ██▌
    ▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▒██░▄▄▄░▓██ ░▄█ ▒▒██  ▀█▄  ▓██    ▓██░   ▒███   ▓██  ▀█ ██▒░██   █▌
    ▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░░▓█  ██▓▒██▀▀█▄  ░██▄▄▄▄██ ▒██    ▒██    ▒▓█  ▄ ▓██▒  ▐▌██▒░▓█▄   ▌
    ▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░░▒▓███▀▒░██▓ ▒██▒ ▓█   ▓██▒▒██▒   ░██▒   ░▒████▒▒██░   ▓██░░▒████▓ 
    ▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░  ░▒   ▒ ░ ▒▓ ░▒▓░ ▒▒   ▓▒█░░ ▒░   ░  ░   ░░ ▒░ ░░ ▒░   ▒ ▒  ▒▒▓  ▒ 
    ░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░   ░   ░   ░▒ ░ ▒░  ▒   ▒▒ ░░  ░      ░    ░ ░  ░░ ░░   ░ ▒░ ░ ▒  ▒ 
    ░░         ░░   ░ ░ ░ ░ ▒  ░ ░   ░   ░░   ░   ░   ▒   ░      ░         ░      ░   ░ ░  ░ ░  ░ 
                ░         ░ ░        ░    ░           ░  ░       ░         ░  ░         ░    ░    
                                                                                       ░      
*/