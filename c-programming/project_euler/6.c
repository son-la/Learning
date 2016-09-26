#include<stdio.h>
int main(){
	FILE *fp;
	fp=fopen("c:\\Users\\Z\\Desktop\\answer.txt","w");//Link to desktop
	int sum1=0,sum2=0,sum;
	for(int i=1; i<=100;i++){
		sum1=sum1+i*i;
		sum2=sum2+i;
	}
	sum=sum1-sum2*sum2;
	fprintf(fp,"Answer: %d",sum);
	fclose(fp);
}