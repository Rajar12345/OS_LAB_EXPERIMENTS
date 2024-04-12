#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	fork();
	printf("Using fork() System Call.\n");
	return 0;
}
