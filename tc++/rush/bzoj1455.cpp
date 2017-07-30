#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
int n,m;
bool dead[maxn];
int p[maxn];
int find(int x){if(x==p[x]) return x;return p[x]=find(p[x]);}

struct Node{
	int key,dist,bh;
	Node *ch[2];
	Node() {}
	void maintain() {dist=ch[1]->dist+1;}
};
Node *null;
Node seq[maxn];int seq_cnt=0;
Node *root[maxn];
Node *New(int key,int bh){
	Node *o=&seq[seq_cnt++];
	o->key=key;o->ch[0]=o->ch[1]=null;o->bh=bh;
	o->dist=0;
	return o;
}

Node *Merge(Node *x,Node *y){
	if(x==null||(y!=null&&y->key<x->key))
		swap(x,y);
	if(y==null) return x;
	x->ch[1]=Merge(x->ch[1],y);
	if(x->ch[0]->dist<x->ch[1]->dist)
		swap(x->ch[0],x->ch[1]);
	x->maintain();
	return x;
}

int main(){
	int a,b,x;
	char op[20];
	null=new Node();null->dist=-1;
	memset(dead,false,sizeof(dead));
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);root[i]=New(x,i);p[i]=i;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%s",op);
		if(op[0]=='M'){
			scanf("%d%d",&a,&b);
			if(dead[a]||dead[b]) continue;
			int px=find(a),py=find(b);
			if(px!=py){
				if(px>py) swap(px,py),swap(a,b);
				p[py]=px;
				root[px]=Merge(root[px],root[py]);
			}
		}
		else{
			scanf("%d",&a);
			if(dead[a]) {puts("0");continue;}
			int px=find(a);
			printf("%d\n",root[px]->key);
			dead[root[px]->bh]=1;
			root[px]=Merge(root[px]->ch[0],root[px]->ch[1]);
		}
	}
	return 0;
}
