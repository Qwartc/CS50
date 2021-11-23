#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int check = 0;
    if(argc == 2)
    {
        int strlenght = strlen(argv[1]);
        for(int i=0;i<strlenght; i++)
        {
            if((argv[1][i] >= 'A' && argv[1][i] <= 'Z') || (argv[1][i] >= 'a' && argv[1][i] <= 'z'))
            {
                check++;
            }
        }
        if(check == strlenght)
        {
            string text = get_string("plaintext: ");
            printf("ciphertext: ");
            int textlen = strlen(text);
            int t;
            int j=0;
            for(int i=0; i<textlen;i++)
            {
                int k = (i-(j%strlenght))%strlenght;
                if((text[i]>= 'A' && text[i]<='Z')||(text[i]>= 'a' && text[i]<='z'))
                {
                    if(isupper(argv[1][k]))
                    {
                        t = text[i]+argv[1][k]-'A';
                        if(t>'Z')
                        {
                            t = (t - 'Z')+'A'-1;
                        }
                    }
                    else if(islower(argv[1][k]))
                    {
                        t = text[i] + argv[1][k]-'a';
                        if(t>'z')
                        {
                            t = (t - 'z')+'a'-1;
                        }
                    }
                    else
                    {
                        t = '*';
                        
                    }
                }
                else
                {
                    t = text[i];
                    j++;
                }
                printf("%c", t);
            }
            printf("\n");
        }
        else
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
}
