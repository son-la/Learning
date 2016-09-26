#include<stdio.h>
#include<conio.h>
int main()
{
	unsigned long long sum=2;
	int prime,i;
	for(prime=3;prime<=2000000;prime++)
		for(i=2;;i++)
		{
			if(prime%i==0)
			{
				break;				
			}
			else if(i==(int)(prime/2+1))
			{				
				sum=sum+prime;
				break;
			}
		}
	printf("%d",sum);
}