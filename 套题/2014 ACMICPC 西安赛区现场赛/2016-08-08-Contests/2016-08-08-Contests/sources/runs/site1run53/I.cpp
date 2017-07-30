#include <bits/stdc++.h>
using namespace std;
#define LL long long

bool stt;

int Test,N,tot,len;
char s[110];
int a[32],now[32];
int res[1000010][32];
int reslen[1000010];

class rec{
	public:
	int go[2];
	int acd;
	void clr(){
		memset(go,0,sizeof(go));
		acd=0;
	}
}Trie[1000010];

bool enn;

int Init(int x,int s){
	if (!Trie[x].go[s]){
		Trie[x].go[s]=++tot;
		Trie[tot].clr();
	}
	return Trie[x].go[s];
}

void dfs(int x,int dep){
	if (dep==32)return;
	if (Trie[x].acd)return; 
	if (Trie[x].go[0]){
		now[dep]=0;
		dfs(Trie[x].go[0],dep+1);
	}else{
		++len;
		memcpy(res[len],now,sizeof(now));
		res[len][dep]=0;
		reslen[len]=dep+1;
	}
	if (Trie[x].go[1]){
		now[dep]=1;
		dfs(Trie[x].go[1],dep+1);
	}else{
		++len;
		memcpy(res[len],now,sizeof(now));
		res[len][dep]=1;
		reslen[len]=dep+1;
	}
	now[dep]=0;
}

int main() {
//	freopen("I.in","r",stdin);
//	freopen("I.out","w",stdout);
	scanf("%d",&Test);
	for (int tt=1;tt<=Test;tt++){
		scanf("%d",&N);
		printf("Case #%d:\n",tt);
		if (!N){
			printf("1\n");
			printf("0.0.0.0/0\n");
			continue;
		}
		tot=1;
		Trie[1].clr();
		for (int i=1;i<=N;i++){
			scanf("%s",s);
			int ll=0;
			int x;
			for (int j=0;j<4;j++){
				x=0;
				while (s[ll]>='0'&&s[ll]<='9')x=x*10+s[ll]-'0',ll++;
				ll++;
				for (int k=7;k>=0;k--)
					a[j*8+7-k]=(x>>k)&1;
			}
			len=0;
			while (s[ll]>='0'&&s[ll]<='9')len=len*10+s[ll]-'0',ll++;
			x=1;
			for (int j=0;j<len;j++)
				x=Init(x,a[j]);
			Trie[x].acd=1;
		}
		len=0;
		memset(now,0,sizeof(now));
		dfs(1,0);
		printf("%d\n",len);
		for (int i=1;i<=len;i++){
			int x=0;
			for (int j=0;j<4;j++){
				x=0;
				for (int k=7;k>=0;k--)
					x^=res[i][j*8+7-k]<<k;
				if (j)printf(".");
				printf("%d",x);
			}
			printf("/");
			printf("%d\n",reslen[i]);
		}
	}
	return 0;
}
