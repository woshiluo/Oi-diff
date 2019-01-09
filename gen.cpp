#include <cstdio>
#include <cstdlib>
#include <ctime>

int n;

int main(){
	srand(time(0));
	n=rand()%10+2;
	printf("%d\n",n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%d ", rand()%1000 );
		}
		printf("\n");
	}
}
