#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
int appear[maxn];
int num[maxn],n,m;
int x[maxn],y[maxn],cup[maxn];
int belong[maxn];
int cnt,rangeL[maxn],rangeR[maxn],val[maxn];
bool ok=true;
int bh[maxn],next[maxn];

bool cmp(int a,int b){
	return rangeL[a]<rangeL[b];
}
inline int lowbit(int x) {return x&(-x);}

struct SegmenTree{
	int space[maxn<<2];
	void build(int o,int L,int R){
		if(L==R) {space[o]=1;return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);build(o<<1|1,M+1,R);
		space[o]=space[o<<1]+space[o<<1|1];
	}
	
	void add(int o,int L,int R,int pos){
		//printf("o:%d L:%d R:%d pos:%d\n",o,L,R,pos);
		if(L==R) {space[o]--;return;}
		int M=(L+R)>>1;
		if(pos<=M) add(o<<1,L,M,pos);
		else add(o<<1|1,M+1,R,pos);
		space[o]=space[o<<1]+space[o<<1|1];
	}
	
	int query(int o,int L,int R,int size){
		if(space[o]<size||size==0) return -1;
		if(L==R) return L;
		int M=(L+R)>>1;
		if(size>space[o<<1]){
			size-=space[o<<1];return query(o<<1|1,M+1,R,size);
		}
		else return query(o<<1,L,M,size);
	}
}seg;

struct FenwickTree{
	int C[maxn],n;
	void init(int nn) {n=nn;memset(C,0,sizeof(C));}
	
	void add(int x,int val) {while(x<=n) C[x]+=val,x+=lowbit(x);}
	int sum(int x) {int res=0;while(x) res+=C[x],x-=lowbit(x);return res;}
}fwt;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&x[i],&y[i]);
	int k=0;
	bool ok=true;
	seg.build(1,1,n);
	for(int i=1;i<=m;i++){
		if(!appear[x[i]]){
			belong[x[i]]=seg.query(1,1,n,y[i]-k);cup[belong[x[i]]]=x[i];//printf("%d\n",belong[x[i]]);
			if(belong[x[i]]==-1) {ok=false;break;}
			seg.add(1,1,n,belong[x[i]]);
			k++;
		}
		else{
			cnt++;
			rangeL[cnt]=appear[x[i]],rangeR[cnt]=i,val[cnt]=y[i];
		}
		appear[x[i]]=i;
	}
	for(int i=1;i<=cnt;i++)
		bh[i]=i;
	for(int i=1;i<=n;i++) num[i]=m+1;
	for(int i=m;i>=1;i--) 
		next[i]=num[x[i]],num[x[i]]=i;
	memset(num,0,sizeof(num));
	fwt.init(m+1);
	for(int i=1;i<=m;i++)
		if(!num[x[i]]) num[x[i]]=1,fwt.add(i,1);
	sort(bh+1,bh+cnt+1,cmp);
	bh[0]=0;rangeL[0]=rangeL[bh[1]];
	for(int i=1;i<=cnt;i++){
		//printf("i:%d\n",i);
		for(int j=rangeL[bh[i-1]];j<rangeL[bh[i]];j++) fwt.add(j,-1),fwt.add(next[j],1);
		if(val[bh[i]]!=fwt.sum(rangeR[bh[i]])) ok=false;
	}
	int pos=1;
	if(!ok) puts("-1");
	else{
		for(int i=1;i<=n;i++){
			if(!cup[i]){
				while(belong[pos]) pos++;
				cup[i]=pos;belong[pos]=i;
			}
			printf("%d ",cup[i]);
		}
		puts("");
	}
	return 0;
}
