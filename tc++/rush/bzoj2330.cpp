/*
定了原点加限制
通过最短路径算法求出来的一组解当中，所有未知数都达到最大值
假设X0是定死的；X1到Xn在满足所有约束的情况下可以取到的最大值分别为M1、M2、……、Mn（当然我们不知道它们的值是多少）；解出的源点到每个点的最短路径长度为D1、D2、……、Dn。 
基本的Bellman-Ford算法是一开始初始化D1到Dn都是无穷大。然后检查所有的边对应的三角形不等式，一但发现有不满足三角形不等式的情况，则更新对应的D值。最后求出来的D1到Dn就是源点到每个点的最短路径长度。 
如果我们一开始初始化D1、D2、……、Dn的值分别为M1、M2、……、Mn，则由于它们全都满足三角形不等式（我们刚才已经假设M1到Mn是一组合法的解），则Bellman-Ford算法不会再更新任合D值，则最后得出的解就是M1、M2、……、Mn。 
好了，现在知道了，初始值无穷大时，算出来的是D1、D2、……、Dn；初始值比较小的时候算出来的则是M1、M2、……、Mn。大家用的是同样的算法，同样的计算过程，总不可能初始值大的算出来的结果反而小吧。所以D1、D2、……、Dn就是M1、M2、……、Mn。 
*/
# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
# define Add(a,b,c) Bell.add_edge(a,b,c)
int n,m;
const int maxn=100010,maxm=2000010;

struct BellmanFord{
	int first[maxn],next[maxm],v[maxm],dist[maxm];
	int n,edge,cnt[maxn];
	int d[maxn];
	bool inq[maxn];
	
	void init(int nn){
		n=nn;memset(first,-1,sizeof(first));edge=0;
	}
	
	void add_edge(int a,int b,int c){
		next[edge]=first[a];
		v[edge]=b;
		dist[edge]=c;
		first[a]=edge++;
	}
	
	bool negativeCycle(){
		queue<int> q;
		for(int i=1;i<=n;i++) d[i]=0,inq[i]=true,q.push(i),cnt[i]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]<d[x]+dist[e]){
					d[v[e]]=d[x]+dist[e];
					if(!inq[v[e]]){
						inq[v[e]]=true;q.push(v[e]);
						if(++cnt[v[e]]>=n) return true;
					}
				}
			}
		}
		return false;
	}
};
BellmanFord Bell;

int main(){
	int op,a,b;
	scanf("%d%d",&n,&m);
	Bell.init(n);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&op,&a,&b);
		if(op==1) {
			Bell.add_edge(a,b,0);Bell.add_edge(b,a,0);
		}
		else if(op==2){
			Bell.add_edge(a,b,1);
		}
		else if(op==3) Add(b,a,0);
		else if(op==4) Add(b,a,1);
		else if(op==5) Add(a,b,0);
	}
	if(Bell.negativeCycle()) printf("-1\n");
	else{
		int ans=0,sum=0;
		for(int i=1;i<=n;i++) sum+=Bell.d[i];
		sum+=n;
		//for(int i=1;i<=n;i++) printf("%d ",Bell.d[i]);
		printf("%d\n",sum);
	}
	return 0;
}
