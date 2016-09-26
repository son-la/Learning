#include <stdio.h>
#include <stdlib.h>
int main()
{
	char input[1000];
	int input1[1000];
	int count;
	int i=0;
	int temp1=0;
	int temp2;
	FILE *fp;
	fp = fopen("C:\\Users\\Z\\Desktop\\text.txt", "r");
	fscanf(fp, "%s", input);
	fclose(fp);
	for(i=0; i<1000;i++)
	{
		input1[i]=input[i]-'0';
	}
	for(i=0; i<996;i++)
	{
		temp2 = input1[i]*input1[i+1]*input1[i+2]*input1[i+3]*input1[i+4];
		if(temp2>temp1)
			temp1=temp2;
	}
	printf("%d",temp1);
}
