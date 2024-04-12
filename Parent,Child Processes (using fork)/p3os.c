#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	pid_t p;
	p=fork();
	if(p==-1)
	{
		printf("There is an Error while calling fork().\n");
	}
	if(p==0)
	{
		printf("We are in Child Process.\n");
	}
	else
	{
		printf("We are in Parent Process.\n");
	}
	return 0;
}
