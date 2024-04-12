#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	int pid=fork();
	if(pid>0)
	{
		sleep(60);
	}
	else if(pid==0)
	{
		printf("Zombie Process Created Successfully\n");
		exit(0);
	}
	else
	{
		printf("Sorry Child Process Cannot be Created\n");
	}
	return 0;
}
