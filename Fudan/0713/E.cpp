# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210;
int n,want[3];
int now[3];
char s[maxn];
int main(){
	scanf("%d%d%d",&n,&want[0],&want[1]);want[2]=n-want[0]-want[1];
	if(want[2]<0) {puts("-1");return 0;}
	scanf("%s",s);
	memset(now,0,sizeof(now));
	for(int i=0;i<n;i++){
		now[s[i]-'0']++;
	}
	int t,change=0;
	for(int i=0;i<n;i++){
		t=s[i]-'0';
		if(now[t]<=want[t]) continue;
		for(int j=0;j<=2;j++){
			if(j==t) continue;
			if(now[j]<want[j]){
				s[i]='0'+j;now[j]++;now[t]--;change++;
				break;
			}
		}
	}
	printf("%d\n",change);
	puts(s);
	return 0;
}
