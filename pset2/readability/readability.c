#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'A' || text[i] >= 'a')
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    words++;
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    float index_raw = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(index_raw);
    //printf("%d\n", index);

    if (index < 16 && index >= 0)
    {
        printf("Grade %d\n", index);
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }

    printf("%d, %d, %d, %d", letters, words, sentences, index);

}