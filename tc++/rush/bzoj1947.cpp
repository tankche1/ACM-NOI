# include<stdio.h>
# include<string.h>
# include<algorithm>
# include<map>
# define pre(x) (Pre.count(x)?Pre[x]:x-1)
# define next(x) (Next.count(x)?Next[x]:x+1)
using namespace std;
const int maxn=50010;
const int INF=2*(1e+9)+11;
map<int,int> Pre,Next;
typedef pair<int,int> pi;
pi P[maxn],L[maxn];
int n,m;
int p_cnt=0,l_cnt=0;
int ans[maxn];
int main(){
	int a,b;
	char op[20];
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);swap(a,b);
		Next[pre(b)]=next(b);
		Pre[next(b)]=pre(b);
		Next[pre(a)]=b;
		Pre[b]=pre(a);
		Next[b]=a;
		Pre[a]=b;
	}scanf("%d",&m);
	for(int i=0;i<m;i++){
		scanf("%s%d",op,&a);
		if(op[0]=='P') P[p_cnt++]=pi(a,i);
			else L[l_cnt++]=pi(a,i);
	}
	Next[INF]=INF+1;
	P[p_cnt++]=pi(INF,m);P[p_cnt++]=pi(INF+10,m);
	L[l_cnt++]=pi(INF,m);L[l_cnt++]=pi(INF+10,m);
	sort(P,P+p_cnt);sort(L,L+l_cnt);
	int now=0,pos=0;
	while(now<INF){
		//int fuck;scanf("%d",&fuck);
		int a=Next.lower_bound(now)->first-now;
		int b=lower_bound(P,P+p_cnt,pi(now,0))->first-now;
		int c=lower_bound(L,L+l_cnt,pi(pos,0))->first-pos;
		int Min=min(a,min(b,c));
		pos+=Min;now+=Min;//printf("pos:%d now:%d a:%d b:%d c:%d\n",pos,now,a,b,c);
		if(Min==b){
			pi *l=lower_bound(P,P+p_cnt,pi(now,0)),*r=lower_bound(P,P+p_cnt,pi(now+1,0));
			while(l!=r) ans[l->second]=pos/*,printf("b:%d\n",l->second)*/,++l;
		}
		if(Min==c){
			pi *l=lower_bound(L,L+p_cnt,pi(pos,0)),*r=lower_bound(L,L+p_cnt,pi(pos+1,0));
			while(l!=r) ans[l->second]=now,/*printf("c:%d %d\n",l->first,l->second),*/++l;
		}
		now=next(now);pos++;
	}
	for(int i=0;i<m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
