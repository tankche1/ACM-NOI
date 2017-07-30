# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=55;
const int INF=~0U>>1;
int n,m;
int c[maxn];
typedef long long LL;

bool check(int set){
	LL res=0;
	for(int i=1;i<=n;i++)
		if(c[i]<set) res+=set-c[i];
	return (res<=m)&&(res<=set);
}

int main(){
	scanf("%d%d",&n,&m);
	int _min=INF;
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]),_min=min(_min,c[i]);
	int L=1,R=_min+m;
	while(L<=R){
		int M=(L+R)>>1;
		if(check(M)) L=M+1;
			else R=M-1;
	}
	printf("%d\n",L-1);
	return 0;
}
