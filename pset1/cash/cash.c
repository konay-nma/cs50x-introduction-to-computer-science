#include<cs50.h>
#include<stdio.h>
#include<math.h>

void numOfCoin(int cent_owed);

int main(void)
{
    int cent_owed = 0;

    do
    {
        float dollar_owed = get_float("Change owed: ");
        cent_owed = round(dollar_owed * 100);
    }
    while (cent_owed <= 0);

    numOfCoin(cent_owed); // function call
}

void numOfCoin(int cent_owed)
{
    int a = cent_owed / 25;
    int b = (cent_owed % 25) / 10;
    int c = ((cent_owed % 25) % 10) / 5;
    int d = ((cent_owed % 25) % 10) % 5;

    printf("%d\n", a + b + c + d);
}
