#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1000010;
int n,A[maxn];
int p[maxn];

struct Node{
	int key,dist;
	Node *ch[2];
	Node(){}
};
Node *null;
Node seq[maxn];int seq_cnt=0;
Node *New(int key){
	Node *o=&seq[seq_cnt++];
	o->key=key;o->ch[0]=o->ch[1]=null;
	o->dist=0;
	return o;
}
Node *root[maxn];

Node *Merge(Node *x,Node *y){
	if(x==null||(y!=null&&y->key>x->key)){
		swap(x,y);
	}
	if(y==null) return x;
	x->ch[1]=Merge(x->ch[1],y);
	if(x->ch[0]->dist<x->ch[1]->dist)
		swap(x->ch[0],x->ch[1]);
	x->dist=x->ch[1]->dist+1;
	return x;
}

int tot=0;
int main(){
	null=new Node();null->dist=-1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),A[i]-=i;
	p[0]=0;
	for(int i=1;i<=n;i++){
		root[++tot]=New(A[i]);
		p[tot]=i;
		while(tot>1&&root[tot]->key<=root[tot-1]->key){
			tot--;root[tot]=Merge(root[tot],root[tot+1]);
			if(((p[tot+1]-p[tot])&1)&&((p[tot]-p[tot-1])&1)){
				root[tot]=Merge(root[tot]->ch[0],root[tot]->ch[1]);
			}
			p[tot]=p[tot+1];
		}
	}
	long long ans=0;
	for(int i=1;i<=tot;i++){
		for(int j=p[i-1]+1;j<=p[i];j++)
			ans+=abs(A[j]-root[i]->key);
	}
	printf("%lld\n",ans);
	return 0;
}
