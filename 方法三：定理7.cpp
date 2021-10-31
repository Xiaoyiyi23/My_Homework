#include<stdio.h>

//利用书47页定理6求欧拉函数 

int main()
{
	int m,m1=0,i=2,j=0,k=0,factor[20],a[20];
	float b[20],sum=1;
	printf("请输入一个正整数\n"); 
	scanf("%d",&m);
	m1=m;
	while(m>1)            //求质因数，并将其储存到factor数组中 
	{
		if(m%i==0)
		{
			factor[j]=i;
			j++;
			m=m/i;
		}
		else i++;
	}
	
	for(i=0;i<j;i++) 
	{
		if(a[k-1]==factor[i])
		{
			continue;
		}
		else
		{
			a[k]=factor[i];
			k++;
		}
	}
	
	for(i=0;i<k;i++)
	{
		b[i]=1-(1/float(a[i]));
	}
	
	for(i=0;i<k;i++)
	{
		sum=sum*b[i];
	}
	sum=sum*float(m1);
	printf("该整数的欧拉函数：%.0f",sum);
} 
