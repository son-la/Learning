#include <stdio.h>
#include <inttypes.h>
int prime(unsigned long long int);
int main(){
	unsigned long long int a = 600851475143ULL,i;
	for(i=2;i<a/2;i++){
		if(prime(i)==1){
			while(a%i==0)
			{	
				a=a/i;
			}
		}
	}
	printf("%llu",a);
}
int prime(unsigned long long int a){
	unsigned long long int j;
	if(a=2)
		return 1;
	else {
		for(j=2;j<=a/2;j++){
			if(a%j==0)
				return 0;
			else if(j=a/2)
				return 1;
		}
	}
}