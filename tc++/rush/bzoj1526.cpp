# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10000;
int n,t;
int first[10],next[maxn],A[maxn];
vector<int> pos[maxn];
int Count[maxn];

void cal(){
	char op;
	scanf("%d ",&t);
	memset(first,-1,sizeof(first));
	for(int i=0;i<t;i++)
		A[i]=(op=getchar())-'0',pos[i].clear();
	for(int i=t-1;i>=0;i--){
		next[i]=first[A[i]];
		first[A[i]]=i;
	}
	for(int i=0;i<10;i++)
		pos[first[i]].push_back(10+i);
	for(int i=0;i<t;i++){
		for(int j=0;j<pos[i].size();j++){
			int x=pos[i][j];
			if(x<maxn){
				for(int k=0;k<10;k++)
					if(first[k]!=-1)
						pos[first[k]].push_back(x*10+k);
			}
			else
				x-=maxn,Count[x]++;
		}
		first[A[i]]=next[i];
	}
}

int main(){
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++) cal();
	int ans=0;
	for(int i=0;i<maxn;i++)
		if(Count[i]==n) ans++;
	printf("%d\n",ans);
	return 0;
}
