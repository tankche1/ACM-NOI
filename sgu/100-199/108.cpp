# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxk=5010;
int n,K;
struct state{
	int val,bh;
	state() {}
	state(int val,int bh):val(val),bh(bh) {}
	bool operator< (const state &rhs)const{
		return val<rhs.val;
	}
};

state s[maxk];
bool noself[maxn];
int ans[maxk];
inline void add(int &x){
	if(++x==maxn) x=0;
}
int main(){
	memset(noself,0,sizeof(noself));
	scanf("%d",&n);
	scanf("%d",&K);
	for(int i=1;i<=K;i++)
		scanf("%d",&s[i].val),s[i].bh=i;
	sort(s+1,s+K+1);
	int now=0,nowk=1,num=0;
	for(int i=1;i<=n;i++){
		if(!noself[now]){
			num++;
			while(nowk<=K&&s[nowk].val==num) ans[s[nowk++].bh]=i;
		}
		int next=now,w=i;
		while(w>0) next+=w%10,w/=10;
		if(next>=maxn)
		noself[(next)-maxn]=1;
		else noself[next]=1;
		noself[now]=0;
		add(now);
	}
	printf("%d\n%d",num,ans[1]);
	for(int i=2;i<=K;i++)
		printf(" %d",ans[i]);puts("");
	return 0;
}
