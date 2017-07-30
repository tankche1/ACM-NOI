# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
int ans[maxn*maxn][2];
struct state{
	int num,bh;
	bool operator < (const state &rhs)const{
		return num>rhs.num;
	}
};
state s[maxn];
int n;
int main(){
	memset(ans,0,sizeof(ans));
	scanf("%d",&n);int N=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i].num),s[i].bh=i,N+=s[i].num;n=N/2;
	sort(s+1,s+n+1);
	int pos=1,now=1;
	while(pos+s[now].num-1<n){
		for(int i=pos;i<pos+s[now].num-1;i++) ans[i][0]=s[now].bh;
		ans[pos+s[now].num-1][1]=s[now].bh;pos=pos+s[now].num-1;s[now].num=0;now++;
		//printf("now:%d pos:%d\n",now,pos);
	}
	for(int i=pos;i<=n;i++)
		ans[i][0]=s[now].bh,s[now].num--;
	if(!s[now].num) now++;
		pos=1;
	while(pos<=n){
		if(ans[pos][1]==0){
			ans[pos][1]=s[now].bh;if(!(--s[now].num)) now++;
		}
		pos++;
	}printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",ans[i][0],ans[i][1]);
	return 0;
}
