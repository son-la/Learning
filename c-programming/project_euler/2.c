#include<stdio.h>
#include<conio.h>
int main()
{
	int fib[3],sum;
	fib[0]=1;
	fib[1]=2;
	sum = 0 ;
	for(;;)
	{
		fib[2]=fib[0]+fib[1];
		if(fib[2]>4000000)
			break;
		else if (fib[2]%2==0)
		{
			sum=sum+fib[2];
		}
		fib[0]=fib[1];
		fib[1]=fib[2];
	}
	printf("%d\n",sum+2);
	getch();
}