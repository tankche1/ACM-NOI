# include<stdio.h>
# include<map>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int mod=227;
unsigned long long hash[maxn],p[maxn];
char s[maxn];
map<unsigned long long,bool> id;
char ans[maxn];
int n,m,k;

bool dfs(int cur,unsigned long long sign){
	if(cur==m){
		sign=sign*p[10001-(m-1)];
		if(!id.count(sign)) return true;
		return false;
	}
	for(int i=0;i<k;i++){
		ans[cur]='a'+i;
		if(dfs(cur+1,sign+p[cur]*ans[cur])) return true;
	}
	return false;
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int Tcase;
	scanf("%d",&Tcase);
	p[0]=1;
	for(int i=1;i<=10005;i++)
		p[i]=p[i-1]*mod;
	while(Tcase--){
		scanf("%d%d%d\n",&n,&m,&k);
		gets(s);
		hash[0]=s[0];
		for(int i=1;i<n;i++) hash[i]=hash[i-1]+s[i]*p[i];
		id.clear();
		id[hash[m-1]*p[(10001-(m-1))]]=1;
		for(int i=1;i+m<=n;i++)
			id[(hash[i+m-1]-hash[i-1])*p[10001-(i+m-1)]]=true;
		dfs(0,0);
		ans[m]='\0';
		puts(ans);
	}
	return 0;
}
