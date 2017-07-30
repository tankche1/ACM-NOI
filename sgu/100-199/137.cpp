# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxk=30010;
int n,k;
int s[maxn];
bool vis[maxn];
int main(){
	scanf("%d%d",&n,&k);
	int K=k%n;memset(s,0,sizeof(s));
	for(int r=1;r<=n-1;r++){
	/*	int num=r;memset(vis,0,sizeof(vis));
		int cnt=0;
		while(!vis[num])
		{//if(r==5) printf("num:%d\n",num);
			vis[num]=true,cnt++;if(num==n-1) break;
			num=(num+r)%n;
			}*/
		//printf("r:%d cnt:%d\n",r,cnt);
		if((K*r)%n==n-1){
			int num=r;while(K--) s[num]=1,num=(num+r)%n;//cnt--;
			break;
		}
	}
	for(int i=0;i<n;i++)
		s[i]+=k/n;
	printf("%d",s[0]);
	for(int i=1;i<n;i++) printf(" %d",s[i]);
		puts("");
	return 0;
}
