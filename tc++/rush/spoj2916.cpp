# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int INF=~0U>>1;
int n,m;
int A[maxn];
int pre[maxn];

struct Node{
	int sum,maxs,maxl,maxr;
	Node() {}
	Node(int sum,int maxs,int maxl,int maxr):sum(sum),maxs(maxs),maxl(maxl),maxr(maxr) {}
};
Node s[maxn<<2];

Node operator + (Node A,Node B){
	return Node(A.sum+B.sum,max(max(A.maxs,B.maxs),A.maxr+B.maxl),max(A.maxl,A.sum+B.maxl),max(B.maxr,B.sum+A.maxr));
}

void build(int o,int L,int R){
	if(L==R){
		s[o]=Node(A[L],A[L],A[L],A[L]);return;
	}
	build(o<<1,L,(L+R)>>1);
	build(o<<1|1,((L+R)>>1)+1,R);
	s[o]=s[o<<1]+s[o<<1|1];
}

int query_R(int o,int L,int R,int qL,int qR){
	if(qL<=L&&qR>=R){
		return s[o].maxr;
	}
	int M=(L+R)>>1;
	if(qR<=M) return query_R(o<<1,L,M,qL,qR);
	else if(qL>M) return query_R(o<<1|1,M+1,R,qL,qR);
		else
			return max(query_R(o<<1|1,M+1,R,M+1,qR),query_R(o<<1,L,M,qL,M)+pre[qR]-pre[M]);
}

int query_L(int o,int L,int R,int qL,int qR){
	//printf("o:%d L:%d R:%d qL:%d qR:%d maxl:%d\n",o,L,R,qL,qR,s[o].maxl);
	if(qL<=L&&qR>=R){
		return s[o].maxl;
	}
	int M=(L+R)>>1;
	if(qR<=M) return query_L(o<<1,L,M,qL,qR);
	else if(qL>M) return query_L(o<<1|1,M+1,R,qL,qR);
		else
			return max(query_L(o<<1,L,M,qL,M),query_L(o<<1|1,M+1,R,M+1,qR)+pre[M]-pre[qL-1]);
}

int query_maxs(int o,int L,int R,int qL,int qR){
	if(qL<=L&&qR>=R){
		return s[o].maxs;
	}
	int M=(L+R)>>1;
	if(qR<=M) return query_maxs(o<<1,L,M,qL,qR);
	else if(qL>M) return query_maxs(o<<1|1,M+1,R,qL,qR);
	else return max(max(query_maxs(o<<1,L,M,qL,M),query_maxs(o<<1|1,M+1,R,M+1,qR)),query_R(o<<1,L,M,qL,M)+query_L(o<<1|1,M+1,R,M+1,qR));
}

int main(){
	int seq1,seq2,seq3;
	int tcase;
	int x1,y1,x2,y2;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		pre[0]=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]),pre[i]=pre[i-1]+A[i];
		build(1,1,n);
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(x2>y1){
				seq1=query_R(1,1,n,x1,y1);
				seq3=query_L(1,1,n,x2,y2);//printf("%d %d\n",seq1,seq3);
				seq2=pre[x2-1]-pre[y1];
				printf("%d\n",seq1+seq2+seq3);
			}
			else{
				int ans=-INF;
				//seq1=query_L(1,1,n,x1,x2-1)+query_sum(1,1,n,x2,y1-1)+query_R(1,1,n,y1,y2);
				//puts("shit");
				seq1=query_R(1,1,n,x1,x2)+query_L(1,1,n,x2,y2)-A[x2];ans=max(ans,seq1);//printf("%d %d\n",query_L(1,1,n,x1,x2),query_R(1,1,n,x2,y2));
				seq2=query_maxs(1,1,n,x2,y1);ans=max(ans,seq2);
				seq3=query_R(1,1,n,x1,y1)+query_L(1,1,n,y1,y2)-A[y1];ans=max(ans,seq3);
				//printf("%d %d %d\n",seq1,seq2,seq3);
				printf("%d\n",ans);
			}
		}
	}
	
	return 0;
}
