# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=20010;
char s[maxn];

void Manacher(int n){
	int mx=0,id=0;//memset(p,0,sizeof(p));
	p[0]=1;
	for(int i=1;i<n;i++){
		if(mx>i)
		p[i]=min(p[id*2-i],mx-i);
		else p[i]=1;
		while(i+p[i]<n&&i-p[i]>=0&&s[i+p[i]]==s[i-p[i]]) p[i]++;
		if(i+p[i]-1>mx) mx=i+p[i]-1,id=i;
	}
}


int main(){
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){

    }
    return 0;
}
