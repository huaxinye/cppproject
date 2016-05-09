#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int main()
{
    struct tm *ptr;
    time_t lt;
    lt =time(NULL);
    //ptr=gmtime(&lt);
    printf(ctime(&lt));
    return 0;
}
