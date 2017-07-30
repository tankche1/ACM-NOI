# include<stdio.h>
# include<string.h>
# include<queue>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=500010;
const int INF=~0U>>1;
int n,m;
int bh[maxn],val[maxn],sum[maxn];
int zero[maxn];

struct HeapNode{
	int num;
	HeapNode(){}
	HeapNode(int num):num(num) {}
	bool operator < (const HeapNode &rhs)const{
		return bh[num]>bh[rhs.num];
	}
};

priority_queue<HeapNode> qu[maxn];
priority_queue<HeapNode> q[maxn];


int getans(int pos,int m){
	if(sum[pos]!=0)
		return ceil(sum[pos]/(n-pos+1));
	return zero[pos]>=m?0:1;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&bh[i],&val[i]);if(val[i]==0) val[i]=-1;
	}
	sum[n+1]=0;zero[n+1]=0;
	for(int i=n;i>=1;i--){
		sum[i]=sum[i+1]+val[i];zero[i]=zero[i+1];if(sum[i]==0) zero[i]++;
	}
	int ans=getans(1,m);
	int last=0;bh[n+1]=n+1;
	for(int i=2;i<=n;i++) qu[sum[i]].push(HeapNode(i-1));
		//printf("ans:%d\n",ans);
	for(int i=1;i<m;i++){
		int now=n+1;printf("i:%d\n",i);
		for(int j=sum[last+1]-ans;j<=sum[last+1]+ans;j++){
			if(ceil(j/(m-i))>ans) continue;printf("j:%d\n",j);
			for(;!qu[j].empty()&&n-qu[j].top().num>=m-i;qu[j].pop())
			if(qu[j].top().num>last) q[j].push(qu[j].top()),printf("qu[j].top():%d\n",qu[j].top().num);
				else printf("whyqu[j].top():%d\n",qu[j].top().num);
			if(!qu[j].empty()) printf("fuckqu[j].top():%d\n",qu[j].top().num);
			for(;(!q[j].empty())&&q[j].top().num<=last;q[j].pop());// printf("q:%d last:%d\n",q[j].top().num,last);
			//	if(!q[j].empty()) printf("fuck %d\n",q[j].top().num);
			if(!q[j].empty()&&bh[q[j].top().num]<bh[now]) now=q[j].top().num;//,printf("j:%d num:%d\n",j,q[j].top().num);
		}
		printf("%d ",bh[now]);last=now;
	}
	printf("%d\n",bh[n]);
	return 0;
}
