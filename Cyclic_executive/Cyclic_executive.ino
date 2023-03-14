#include <B31DGMonitor.h>
#include "Ticker.h"

Ticker cyclic_ticker;                     //Ticker object init

int count_executions = 0;                      //Global executions counter
int max_count_executions = 5;                   //Global maximum executions allowed


void task_one(int max_count_executions)                           //Task 1 func
{
  Serial.print("Executing: Task 1");
  Serial.print("\t");
  Serial.print("Execution count: ");
  Serial.println(count_executions + 1);
  Serial.println("-------------------------------------");

  count_executions++;

  if (count_executions >= max_count_executions)
  {
    cyclic_ticker.detach();
  }
}

void stask_two()                           //Task 2 func
{
  Serial.println("Task two");
}

void stask_three()                           //Task 3 func
{
  Serial.println("Task three");
}

void stask_four()                           //Task 4 func
{
  Serial.println("Task four");
}

void setup()
{
    Serial.begin(9600);                           //Serial init

    cyclic_ticker.attach_ms(4000, task_one, max_count_executions);
    
}

void loop()
{
  
}
