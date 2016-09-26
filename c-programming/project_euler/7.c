#include<stdio.h>
int main()
{
	int count=1;
	int prime,i;
	for(prime=3;count!=10001;prime++)
		for(i=2;;i++)
		{
			if(prime%i==0)
			{
				break;				
			}
			else if(i==prime-1)
			{				
				count++;
				break;
			}
		}
	printf("%d",prime-1);
}