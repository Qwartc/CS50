#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int parseInt(char* chars);
int powInt(int x, int y);

int main(int argc, string argv[])
{
    if(argc == 2)
    {
        
        int number = parseInt(argv[1]);
        string text = get_string("Enter message: ");
        printf("ciphertext: ");
        int n = strlen(text);

        for(int i=0; i<n; i++)
        {
            int t;
            if((text[i]>64 && text[i]<91) || (text[i]>96 && text[i]<123))
            {
                
                t = text[i]+(number)%26;
                if(isupper(text[i]))
                {
                    if(t>'Z')
                    {
                       t = (t-'Z')+'A'-1;  
                    }
                }
                else if (islower(text[i]))
                {
                    if(t>'z')
                    {
                       t = (t-'z')+'a'-1;  
                    }
                }
                
            }
            else
            {
                t = text[i];
            }


            printf("%c", t);
            
        }
        printf("\n");
    }
    else
    {
        printf ("usage : %s + key \n", argv[0]);
        return 1;
    }
}

int parseInt(char* chars)
{
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++)
    {
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}

int powInt(int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        x *= 10;
    }
    return x;
}
