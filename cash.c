#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
  float number;                           //define number
  do
  {
  number = get_float("Change owed: $"); 
  }
  while (number<0);                                 //get positive number
 int cents = round(number*100);                     //define and convert to cents

 int counter = 0;                                   //define counter

//add number of quarters
counter = counter + cents/25;                       //add quotient to counter (works even if smaller than 25)
   
    //if there is remainder (if no remainder- done)
    if(cents%25)                                   
    {
        int x = cents%25;                           //define x as remainder after division by 25  
        if(x/10 >= 1)                                //if x bigger than 10
        {
            counter = counter + x/10;                //add quotient after division by 10   
            int y = x%10;                            //define y as remainder after division by 10
            counter = counter + y/5 + y%5;           //then add quotient from division by 5 and remainder (pennies)
        }
        else if (x/10 < 1)                           //if remainder x less than 10
        {                    
            counter = counter + x/5 + x%5;           //then add quotient from division of x by 5 and remainder 
        }
    }

printf("Min coins: %i\n", counter);
}
