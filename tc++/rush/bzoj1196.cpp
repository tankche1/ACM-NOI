# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=20010;
struct Edge{
	int a,b,c;
	Edge() {}
	Edge(int a,int b,int c):a(a),b(b),c(c) {}
	bool operator < (const Edge &rhs)const{
		return c<rhs.c;
	}
};
Edge edges1[maxm],edges2[maxm];
int n,k,m;
int p[maxn];

int find(int x){
	if(x==p[x]) return x;
		return p[x]=find(p[x]);
}

bool check(int Ti){
	int ans=0,kuai=n;
	for(int i=1;i<=n;i++) p[i]=i;
	for(int i=1;i<m;i++){
		if(edges1[i].c>Ti) break;
		int px=find(edges1[i].a),py=find(edges1[i].b);
		if(px==py) continue;
		p[py]=px;ans++;kuai--;
	}
	if(ans<k) return false;
	for(int i=1;i<m;i++){
		if(edges2[i].c>Ti) break;
		int px=find(edges2[i].a),py=find(edges2[i].b);
		if(px==py) continue;
		p[py]=px;
		if(--kuai==1) break;
	}
	//printf("Ti:%d ans:%d kuai:%d\n",Ti,ans,kuai);
	return ans>=k&&kuai==1;
}

int main(){
	int _max;
	int a,b,c1,c2;
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<m;i++)
		scanf("%d%d%d%d",&a,&b,&c1,&c2),_max=max(_max,c1),edges1[i]=Edge(a,b,c1),edges2[i]=Edge(a,b,c2);
	sort(edges1+1,edges1+m+1);
	sort(edges2+1,edges2+m+1);
	//sort(edges+1,edges+m+1);
	int L=1,R=_max;
	while(L<=R){
		int M=(L+R)>>1;
		//printf("L:%d R:%d 
		if(check(M)) R=M-1;
			else L=M+1;
	}
	printf("%d\n",R+1);
	return 0;
}
