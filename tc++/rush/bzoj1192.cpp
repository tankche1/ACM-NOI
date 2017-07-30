# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int m,p;
int main(){
	p=0;
	int now=1;
	scanf("%d",&m);
	while(m>0){
		m-=now;p++;
		now<<=1;
	}
	printf("%d\n",p);
	return 0;
}
