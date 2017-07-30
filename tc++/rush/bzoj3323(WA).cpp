#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int mod=20130426;
const int RR=100001;
typedef long long LL;
int n;
int ans;
int pow[maxn<<1];

struct SegmenTree{
	int sum[maxn<<2],add[maxn<<2],mul[maxn<<2],mulx[maxn<<2];
	
	void build(){
		memset(sum,0,sizeof(sum));memset(add,0,sizeof(add));memset(mul,1,sizeof(mul));memset(mulx,0,sizeof(mulx));
	}
	
	void pushdown(int o,int L,int R){
		if(mul[o]!=1){
			mul[o<<1]=(LL)mul[o]*mul[o<<1]%mod;
			mul[o<<1|1]=(LL)mul[o]*mul[o<<1|1]%mod;
			sum[o<<1]=(LL)sum[o<<1]*mul[o]%mod;
			sum[o<<1|1]=(LL)sum[o<<1|1]*mul[o]%mod;
			add[o<<1]=((LL)add[o<<1]*mul[o])%mod;
			add[o<<1|1]=((LL)add[o<<1|1]*mul[o])%mod;
			mul[o]=1;
		}
		if(add[o]!=0){
			int M=(L+R)>>1;
			add[o<<1]=(add[o<<1]+add[o])%mod;
			add[o<<1|1]=(add[o<<1|1]+add[o])%mod;
			sum[o<<1]=((LL)(M-L+1)*add[o]+sum[o<<1])%mod;
			sum[o<<1|1]=((LL)(R-M)*add[o]+sum[o<<1|1])%mod;
			add[o]=0;
		}
		if(mulx[o]){
			mulx[o<<1]+=mulx[o];
			mulx[o<<1|1]+=mulx[o];
			mulx[o]=0;
		}
	}
	
	void update(int o,int L,int R,int qL,int qR,int val,int op){
		//printf("L:%d R:%d qL:%d qR:%d val:%d op:%d\n",L,R,qL,qR,val,op);
		if(qL<=L&&qR>=R){
			if(op==2) add[o]=(add[o]+val)%mod,sum[o]=((LL)(R-L+1)*val+sum[o])%mod;
			else if(op==1) mul[o]=(LL)mul[o]*val%mod,sum[o]=(LL)sum[o]*val%mod,add[o]=(LL)add[o]*val%mod;
			else if(op==3) mulx[o]++;
			return;
		}
		pushdown(o,L,R);
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val,op);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val,op);
		sum[o]=sum[o<<1]+sum[o<<1|1];
	}
	
	void query(int o,int L,int R,int node,int v){
		//if(node<=7)
		//printf("L:%d R:%d sum:%d\n",L,R,sum[o]);
		if(L==R){
			int res=sum[o];
			res=(LL)res*pow[node-1+mulx[o]]%mod;
			//printf("sum:%d res:%d\n",sum[o],res);
			ans=(ans+res)%mod;
			return;
		}
		pushdown(o,L,R);
		if(node<=((L+R)>>1)) query(o<<1,L,(L+R)>>1,node,v);
		else query(o<<1|1,((L+R)>>1)+1,R,node,v);
	}
	
}seg;

int main(){
	char op[20];
	int L,R,v;
	scanf("%d",&n);
	seg.build();
	for(int i=1;i<=n;i++){
		scanf("%s",op);
		if(op[0]=='m'&&op[3]=='x'){
			scanf("%d%d",&L,&R);L++;R++;
			seg.update(1,1,RR,L,R,1,3);
		}
		else if(op[0]=='m'){
			scanf("%d%d%d",&L,&R,&v);L++;R++;
			seg.update(1,1,RR,L,R,v,1);
		}
		else if(op[0]=='a'){
			scanf("%d%d%d",&L,&R,&v);L++;R++;
			seg.update(1,1,RR,L,R,v,2);
		}
		else{
			scanf("%d",&v);
			ans=0;
			pow[0]=1;
			for(int i=1;i<=RR+RR;i++)
				pow[i]=(LL)pow[i-1]*v%mod;
			for(int i=1;i<=RR;i++)
				seg.query(1,1,RR,i,v);
			printf("%d\n",ans);
		}
	}
	return 0;
}
