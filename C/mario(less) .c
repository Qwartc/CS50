#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        h = get_int("Enter heigth of pyramide: ");
    }
    while(h<1 || h>8);

     int i=1;
     int j=1;
    while(i <= h)
    { 
         j=1;
        while(j<=h)
        {
             if(j<=h-i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
            
            j++;
        }
        printf("\n");
        i++;  
    }
}

}
