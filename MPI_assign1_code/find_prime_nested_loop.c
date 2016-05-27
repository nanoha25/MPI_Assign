#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int main()
{
  int i; //This variable will be used to display prime number.
  int j; //This variable will be used to test if a number is a prime number.
  int max; //This variable will be used as user input to determine the range to find prime number.

  printf("Please enter the number you would like to find the prime number. ");
  scanf("%d", &max);

  for (i=2; i<=max; i++)  //This for loop will go through all numbers between 2 and max number defined by user.
  {
    for (j=2; j<=i; j++)  //This for loop will determine if current number has more than 2 factors (1 and itself).
    {
      if (i%j==0)  //This line is the determine condition. It uses module division.
      {
        break;  //If condition is true then program jumps out of INNER for loop. Not the ENTIRE for loop.
      }
    }
    if (i==j)  //This condition is to include the number itself, because in previous "if" condition, say we are at number 7, and "7%7==0" is true. This defeats the purpose of finding prime number.
    {
      printf("%d is a prime number.\n",i);
    }
  }
}
