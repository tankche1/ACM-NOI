#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
char s,t;
int hour,minite;
int lhour,lminite;
int main(){
	//scanf("%s%s",s,t);
	int num=0;hour=0;
	while((t=getchar())&&(t<'0'||t>'9'));hour=t-'0';
		while((t=getchar())&&(t<'0'||t>'9'));hour=hour*10+t-'0';
			
	while((t=getchar())&&(t<'0'||t>'9'));minite=t-'0';
		while((t=getchar())&&(t<'0'||t>'9'));minite=minite*10+t-'0';
			
		
			while((t=getchar())&&(t<'0'||t>'9'));lhour=t-'0';
		while((t=getchar())&&(t<'0'||t>'9'));lhour=lhour*10+t-'0';
			
	while((t=getchar())&&(t<'0'||t>'9'));lminite=t-'0';
		while((t=getchar())&&(t<'0'||t>'9'));lminite=lminite*10+t-'0';
	int t=hour*60+minite-lhour*60-lminite;
		t=(t+1440)%1440;
		printf("%02d:%02d\n",t/60,t%60);
	return 0;
}
