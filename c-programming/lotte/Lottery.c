#include <stdio.h>
#include <conio.h>
#include <time.h>
/*Variable holding game detail*/

int money = 100;

void greeting();
void rules();
void account();
void join();
void play();
void sorting(int *);


void greeting(){
	printf("\n\n\n\n");
	printf("===============================\n");
	printf(" Welcom to Billion Lottery !!!\n");
	printf("===============================\n")	;
	printf("\n");
	printf("1. Game rules\n");
	printf("2. Join the world !!!\n");
	printf("3. Quit");
	printf("\n\nEnter the number to choose: ");
	return;
}
void rules(){

	printf("\n Here are some important things that players should know:\n");
	printf("- You will have 100 SD as an initial account\n\n");
	printf("- Each lottery ticket costs 10 SD\n\n");
	printf("- You can choose 7 numbers from 0 to 49 (without any repetition) to create your ticket series number\n\n");
	printf("- Here are the awards:\n\n");
	printf("    Match all 7 numbers: +50 SD\n");
	printf("\n\n Press any key to continue ...");
	getch();
	return ;
}
void account(){
	printf("\nYour account: %d SD",money);
	printf("\n\n Press any key to continue ...");
	getch();
	return ;
}
void join(){
	int choose;
	do{
		printf("\n1. Buy ticket\n");
		printf("2. Check your account\n");
		printf("3. Back\n");
		printf("\nEnter the number to choose: ");
		scanf("%d",&choose);
		switch(choose)
		{
			case 1:
				play();
				break;
			case 2: 
				account();
				break;
			case 3:
				break;
			default:
				printf("\nWrong number!!\n");
				break;
		}
	}
	while (choose != 3);
	return;
}
void play(){
	if (money==0){
		printf("You dont have money left :( Sorry .. !");
		return;
	}
	int numboftick = -1;/*maximum 10 = maximum ticket can buy in one time*/
	int c1,c2; //counting variable
	int ticket[10][7],*pticket;
	int result[7],*presult;
	presult=(int *)result;	//Pointer to result
	pticket=(int *)ticket; //Pointer to ticket series
	do
	{
		numboftick++; // Number of ticket +1
		int count2 = 0;/*maximum 7 digits*/
		printf("Enter 7 numbers (from 0 to 49, without repetition):\n");//Enter number
		for(;count2<=6;)
		{
			scanf("%d",&c1);
			if((c1>=0)&&(c1<=49))
			{
				ticket[numboftick][count2]=c1;
				count2++;
				for(c2=0;(c2<count2-1)&&(c2>=0);c2++) //validation the repetition
				{
					if (c1==ticket[numboftick][c2])
					{
						printf("\nRepetition !!!\n");
						count2--;
						break;
					}
				}
			}
			else 
			{
				printf("\nIllegal character !!!\n");
			}
			fflush(stdin);
		}
		money = money - 10; // 10 per ticket
		sorting(pticket + numboftick*count2);
		printf("\nBuy one more ticket (Y/N)?: ");
	}
	while ((numboftick<10)&&(money >=10)&&((c2=getchar())=='Y'));
	
		//ticket that we have
	printf("\nThe ticket(s) that you bought:\n");	
	for(c1=0;c1<=numboftick;c1++)
		{
			printf("\n");
			for(c2=0;c2<7;c2++)
			{
				printf("%d   ",ticket[c1][c2]);	
			}			
		}	
		
		// Take results
		
	srand(time(NULL));
	for(c1=0;c1<7;c1++)
	{
		result[c1] = rand() % 49;
		for(c2=0;c2<c1;c2++)
			if (result[c1]==result[c2])
			{
				c1--;
			}
	}
	sorting(presult);	
	printf("\n\nHere is the result: \n");
	for(c1=0;c1<7;c1++)
		printf("%d   ",*(presult + c1))	;
		
		// Compare result
	
	for(c1=0;c1<numboftick+1;c1++)	
		for(c2=0;c2<7;c2++)
		{
			if (*(presult + c1*7+ c2) != *(pticket + c2) )
				{
					printf("\n\nSorry you lost \n");
					break;
				}
			else if(c2 == 6)
				{
					printf("\n\nCongrat !! + 50 SD \n ");
					money = money +50 ;
				}
			else continue;
			
		}
	return;
}

void sorting(int *ptick){	//From min to max
	int temp;
	int i,j;
	for(i=0;i<7;i++)
		for(j=i;j<7;j++)
		{
			if(*(ptick+i)>*(ptick+j)){
				temp = *(ptick+i);
				*(ptick+i) = *(ptick+j);
				*(ptick+j) = temp;
			}
		}
}

int main(){
	int choose;
	do {
		greeting();
		scanf("%d",&choose);
		switch(choose)
		{
			case 1: 
				rules();
				break;
			case 2:
				join();
				break;
			case 3: 
				break;
			default:
				printf("\nWrong number!!\n");
				break;
		}
	}
	while (choose != 3);
	printf("\n\nBye bye ~ See you\n\n ");
	getch();
}