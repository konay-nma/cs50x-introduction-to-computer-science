#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

char substitution(char key[]);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int key_len = strlen(key);

        //checking key length
        if (key_len != 26)
        {
            printf("Key must contain 26 charaters.\n");
            return 1;
        }

        //checking duplicate ann alpah key
        for (int i = 0; i < key_len; i++)
        {
            for (int j = i + 1; j < key_len; j++)
            {
                if (key[i] == key[j])
                {
                    printf("duplicate characters in key\n");
                    return 1;
                }
            }

            if (!isalpha(key[i]))
            {
                printf("Key must be 26 alphabetic charaters.\n");
                return 1;
            }
        }
        printf("%c", substitution(key)); // method call to generete ciphertext
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

//creatting method for ciper text algorithm
char substitution(char key[])
{
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            int index = (int)(plaintext[i] % 'A');
            printf("%c", toupper(key[index]));
        }
        else if (islower(plaintext[i]))
        {
            int index = (int)(plaintext[i] % 'a');
            printf("%c", tolower(key[index]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
