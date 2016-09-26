#include<stdio.h>

int AmountOfData(FILE*);
int main(void)
{
	FILE *fp;
	
	char *data;
	int amount;
	
	fp = fopen("table.txt","r");
	amount = AmountOfData(fp);
	
	printf("%d", amount);
	fclose(fp);
}

int AmountOfData(FILE *fp)
{

	int c;
	int length = 1;
	
	fscanf(fp,"%d", &c);
	
	while(c != EOF)
	{
		fscanf(fp,"%d", &c);
		length++;
	}
	return length;
}


