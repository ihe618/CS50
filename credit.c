#include <cs50.h>
#include <stdio.h>
#include <math.h>

long ten(int p);
int digit(long x, int y);


int main(void)
{ 
long n = get_long("Number: ");                      //Define number

//Eliminate negative and <13 or > 16 digit no.s      
    if (n < 100000000000 || n > 9999999999999999)
    {
        printf("INVALID\n");                                   
    }
    else
    {
//Application of Luhn's algorithm
    //Two times even digit (from second to last digit)- and sum of the product's digits
    int sume = 0;                           
    for(int i=2; i<17; i = i+2)                        //Repeat for even digits from second to last 
    {
    int twotimes = 2*(digit(n, i));                     //multiple digit by 2
    int d = twotimes % 10;                              //determine single digit for the product
    int t = (twotimes - d)/10;                          //determine tenth digit for the product    
    sume = sume + d + t;                                //add single and tenth digits of product   
    }
    //Sum of Odd digits (counting from last digit)
    int sumo= 0;
    for(int i=1; i < 16; i = i+2)
    {
    sumo = sumo + digit(n, i);  
    }
    int final = sume + sumo;
//If fail Luhn's algorithm
        if(final % 10)                                
        {
        printf("INVALID\n"); 
        }
//If pass Luhn's algorithm       
        else if(final % 10 == 0)
        {
            //American Express
            long Am = (n - n % ten(13))/ten(13);
            if ((Am == 34) || (Am == 37))
                {
                printf("AMEX\n");
                }
            //Mastercard
            long MC = (n - n%ten(14))/ten(14);
            if ( (50 < MC) && (MC < 56))
                {
                printf("MASTERCARD\n");
                }
            //Visa
            long Vi = (n - n % ten(12))/ten(12);
            long Vis = (n - n % ten(15))/ten(15);
            if((Vi == 4) || (Vis == 4))
                {
                printf("VISA\n");
                }
        }
        else
        {
        printf("INVALID\n");
        }
        
    }
    
}


//Create function for powers of 10
long ten(int p)                                    
{  
    long result = 1;
    for(int i=0; i<p; i++)
    {
    result = 10 * result;
    }
return result;
} 

//Create function to spit out digit
int digit(long x, int y)                            
{
    int answer;
    answer = ( x % ten(y) - x % ten(y-1) )/ten(y-1);
    return answer;
}
