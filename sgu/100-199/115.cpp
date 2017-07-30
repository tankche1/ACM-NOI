# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int main(){
	int ans=0;
	int mon,day;
	scanf("%d%d",&day,&mon);
	if(mon>13||mon<1||day<1||day>month[mon]) puts("Impossible");
	for(int i=1;i<mon;i++){
		ans+=month[i];
	}
	ans+=day;
	if(ans%7==0) printf("7\n");
	else printf("%d\n",(ans%7));
	return 0;
}
