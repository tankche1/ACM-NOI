# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int main(){
	int n;scanf("%d",&n);
	if(n<=8) puts("0");
		else if(n==9) puts("8");
			else if(n==10) puts("72");
				else{
					printf("72");
					for(int i=11;i<=n;i++) printf("0");
						puts("");
				}
	return 0;
}
