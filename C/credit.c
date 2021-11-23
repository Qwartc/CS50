#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number;
    long number2;
    long number3;
    int i=0;
    int c=0;
    int sum = 0;
    int j=1;
    int amountdigits;
    number = get_long("Number: ");
    number2 = number;
    while(number2!=0)
    {
        number2/=10;
        i++;
    }
    if(i == 15 || i == 13 || i == 16)
    {
       amountdigits = i;
        number2 = number;
        while(number != 0)
        {
            number2 = number;
            number2= number2 % 10;
            if(j%2 == 0)
            {
                if(number2*2>=10)
                {
                    c+=number2*2%10;
                    c+=number2*2/10;
                }
                else
                {
                c = c + number2*2; 
                }
            }
            else
            {
                sum+=number2;
            }
            if(j==amountdigits-1)
            {
                number3 = number;
            }
            number/=10;
            j++;
        }
        
        if((c+sum)%10 == 0)
        {
            if(number3 == 34 || number3 == 37)
            {
                printf("AMEX\n");
            }
            else if(number2 == 4)
            {
                printf("VISA\n");
            }
            else if(number3 >= 51 && number3<=55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");  
        }

    }
    else 
    {
        printf("INVALID\n");  
    }
}
