#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
int p[maxn];
bool vis[maxn];
int n;
int find(int x){if(x==p[x]) return x;return p[x]=find(p[x]);}
int main(){
	int a,b;
	scanf("%d",&n);
	for(int i=1;i<=10000;i++) p[i]=i;
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a,&b);
		int px=find(a),py=find(b);
		if(px==py)
			vis[px]=1;
		else{
			if(px>py) swap(px,py);
			vis[px]=1;
			p[px]=py;
		}
	}
	for(int i=1;i<=10001;i++)
		if(!vis[i]) {printf("%d\n",i-1);break;}
	return 0;
}
