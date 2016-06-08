#include <stdio.h>
#include <stdlib.h>

int add_number()
{
  int i = 2;
  int j = 4;
  int k = i+j;
  return k;
}

int show_number()
{
  int i = add_number();
  printf("i is %d\n",i);
  return i;
}

int show_again()
{
  int j = show_number();
  printf("show again: %d\n",j);
  return j;
}

int main()
{
  add_number();
  show_number();
  show_again();
  return 0;
}
