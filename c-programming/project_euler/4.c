//<5 digits
#include <stdio.h>
int validation(int ,int );
int gen(int);

int gen(int numofdigits){
	int i,j,k=0;
	int validate;
	int numb;
	int lim=0;
	int result=0;
	for(j=0;j<numofdigits;j++)
		lim=lim*10+1;
	for(i=9*lim;i>=lim;i--)
		for(j=9*lim;j>=lim;j--){
			numb=i*j;
			validate = validation(numb,numofdigits);
			if (validate==1)
			{
				if (result < numb)
					result = numb;
			}
			else if (validate == -2)
				return result;			
		}
}

int validation(int a,int i){
	int j;
	int b[i*2];
	i=i*2-1;//index of the last element
	
	for(j=i;j>=0;j--){
		b[j]=a-a/10*10;
		a=a/10;
	}
	if(b[0]==0)
		return -2; //check the symmetry of number
		
	for(j=0;j<(i+1)/2;j++){	
		if (b[j]!=b[i-j])
			return -1;	// not palindromic  number
	}
	return 1;

}
int main(){
	int result;
	int numb, numofdigits;
	printf("Enter the number of digit: \n");
	scanf("%d",&numofdigits);
	result=gen(numofdigits);
	if (result == 0)
		printf("\nNo palindromic number !!\n");
	else printf("\nResult: %d\n",result);
	return;
}