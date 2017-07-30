#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef unsigned int ui;
const int maxn=100010;
const int mod=107;
char s[maxn],word[maxn];
struct block{
	int l,r;ui hash;
	block() {}
};
block b[maxn];
int pow[maxn];
int cnt=0;
int n,tcase,len;
ui h[maxn];

bool dfs(int pos1,int pos2){
	if(pos1>n&&pos2>len) return true;
	if(pos1>n||pos2>len) return false;
		
	if(s[pos1]=='?'){
		return dfs(pos1+1,pos2+1);
	}
	else if(s[pos1]=='*'){
		for(int k=pos2;k<=len+1;k++)
			if(dfs(pos1+1,k)) return true;
	}
	else if(s[pos1]==word[pos2]){
		for(int i=1;i<=cnt;i++)
			if(b[i].l==pos1){
				if(b[i].hash==h[pos2+b[i].r-b[i].l]-h[pos2-1]*pow[b[i].r-b[i].l+1])
					return dfs(b[i].r+1,pos2+b[i].r-b[i].l+1);
			}
	}
	return false;
}

int main(){
	scanf("%s",s+1);n=strlen(s+1);
	pow[0]=1;
	for(int i=1;i<=maxn-10;i++) pow[i]=pow[i-1]*mod;
	for(int i=1;i<=n;i++){
		if(s[i]>='a'&&s[i]<='z'){
			int j=i;while(s[j+1]>='a'&&s[j+1]<='z') j++;
			cnt++;b[cnt].l=i;b[cnt].r=j;ui now=0;
			for(int k=i;k<=j;k++) now=now*mod+s[k];
			b[cnt].hash=now;
			i=j;
		}
	}
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%s",word+1);len=strlen(word+1);
		h[0]=0;for(int i=1;i<=len;i++) h[i]=h[i-1]*mod+word[i];
		bool ok=dfs(1,1);
		if(ok) puts("YES");
		else puts("NO");
	}
	return 0;
}
