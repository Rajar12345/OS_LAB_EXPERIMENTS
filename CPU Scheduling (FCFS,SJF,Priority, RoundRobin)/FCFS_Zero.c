#include<stdio.h>
void Waiting(int pr[],int n,int bt[],int wt[])
{
	wt[0]=0;
	for(int i=1;i < n;i++)
	{
		wt[i]=bt[i-1]+wt[i-1];
	}
}
void TurnAround(int pr[],int n,int bt[],int wt[],int tat[])
{
	for(int i=0;i<n;i++)
		tat[i]=bt[i]+wt[i];
}
void Average(int pr[],int n,int bt[])
{
	int wt[n],tat[n],total_wt = 0,total_tat = 0;
	Waiting(pr,n,bt,wt);
	TurnAround(pr,n,bt,wt,tat);
	printf("Processes\tBurst-Time\tWaiting-Time\tTurn-AroundTime\n");
	for(int i=0;i<n;i++)
	{
		total_wt=total_wt+wt[i];
		total_tat=total_tat+tat[i];
		printf("  %d ",(i+1));
		printf("\t\t%d ",bt[i]);
		printf("\t\t%d",wt[i]);
		printf("\t\t%d\n",tat[i]);
	}
	float s=(float)total_wt/(float)n;
	float t=(float)total_tat/(float)n;
	printf("Average Waiting Time = %f\n",s);
	printf("Average Turn-Around-Time = %f\n",t);
}
int main()
{
	int pr[]={1,2,3};
	int n=sizeof pr/sizeof pr[0];
	int burst[]={10,5,8};
	Average(pr,n,burst);
	return 0;
}
