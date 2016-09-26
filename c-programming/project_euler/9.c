#include <stdio.h>
#include <math.h>
int main()
{
	int check=1;
	int a,b,c;
	for(a=333;(a>0&&check==1);a--)
		for(b=500;b>a;b--)
			{
				c=sqrt(a*a+b*b);
				if((a+b+c==1000)&&(a*a+b*b==c*c))
					{
						check=-1;
						break;
					}
			}
	printf("%d %d %d",(a+1),b,c);
}