#include <cstdio>
#include <cstdlib>

int n;

int main(){
	while(1){
		n++;
		system("./gen.run >t.in");
		system("./mine.run <t.in >mine.out");
		system("./dalao.run <t.in >dalao.out");
		if(system("diff dalao.out mine.out")!=0){
			printf("\033[7m%6d\033[0m \033[1;31m✘ Wrong Answer\033[0m\n",n);
			return 0;
		}
		else 
			printf("\033[7m%6d\033[0m \033[1;32m✔ Acceppted\033[0m\n",n);
	}
}