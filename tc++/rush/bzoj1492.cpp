#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const double INF=1e100;
typedef pair<double,double> pi;

double dp[maxn];
double A[maxn],B[maxn],rate[maxn];
int n,s;

struct Node{
	pi data;
	Node *ch[2],*f;
	double k[2];
		
	Node(){}
};
Node seq[maxn];int seq_cnt=0;Node *null;
Node* New(pi data){
	Node *o=&seq[seq_cnt++];
	o->data=data;
	o->ch[0]=o->ch[1]=o->f=null;
	return o;
}

double Cal_k(Node *x,Node *y){
	if(y->data.first==x->data.first) return -INF;
	return (y->data.second-x->data.second)/(y->data.first-x->data.first);
}

struct SplayTree{
	Node *root;
	
	void Rotate(Node* &o,int d){
		Node *p=o->ch[!d];
		o->ch[!d]=p->ch[d];
		if(p->ch[d]!=null) p->ch[d]->f=o;
		p->ch[d]=o;
		p->f=o->f;
		if(o->f!=null) o->f->ch[o->f->ch[1]==o]=p;
		o->f=p;
		if(root==o) root=p;
		o=p;
	}
	
	void Splay(Node *t,Node *fa){
		while(t->f!=fa){
			Node *o=t->f;
			if(t->f->f==fa){
				Rotate(o,o->ch[0]==t);
			}
			else{
				Node *p=o;
				o=o->f;
				int d=o->ch[1]==t->f;int dd=o->ch[d]->ch[1]==t;
				if(d==dd)
					Rotate(o,!d),Rotate(o,!d);
				else 
					Rotate(p,!dd),Rotate(o,!d);
			}
		}
	}
	
	Node *get_neighbour(Node *now,int t){
		if(now->ch[t]==null) return null;
		for(now=now->ch[t];now->ch[!t]!=null;now=now->ch[!t]);
			return now;
	}
	
	Node *find_near(double k){
		Node *now=root;
		for(;;now=now->ch[now->k[1]>k])
			if(now->k[0]>=k&&now->k[1]<=k)
				return now;
	}
	
	void Check(Node *t,int c){
		for(Node *now=get_neighbour(t,c);;now=get_neighbour(t,c)){
			if(now==null) return;
			Splay(now,t);
			if((c==0&&now->k[0]<=Cal_k(now,t))||(c==1&&now->k[1]>=Cal_k(now,t))){
				t->ch[c]=now->ch[c];
				if(now->ch[c]!=null) now->ch[c]->f=t;
			}
			else return;
		}
	}
	
	void Fix(Node *t){
		Splay(t,null);
		Node *pred=get_neighbour(t,0),*succ=get_neighbour(t,1);
		t->k[0]=pred==null?0:Cal_k(pred,t);
		t->k[1]=succ==null?-INF:Cal_k(succ,t);
		if(t->k[0]<=t->k[1]){
			Node *x=pred==null?succ:pred;
			int d=x==pred?0:1;
			Splay(x,t);x->f=null;
			x->ch[!d]=t->ch[!d];
			if(t->ch[!d]!=null) x->ch[!d]->f=x;
			root=x;
		}
		else{
			Check(t,0);Check(t,1);
			pred=get_neighbour(t,0),succ=get_neighbour(t,1);
			t->k[0]=pred==null?0:pred->k[1]=Cal_k(pred,t);
			t->k[1]=succ==null?-INF:succ->k[0]=Cal_k(succ,t);
		}
	}
	
	void Insert(Node *newnode){
		Node *now=root,*last=null;
		for(;now!=null;last=now,now=now->ch[newnode->data>now->data])
			if(now==newnode) return;
		if (last == null)
			root = newnode;
		else
			last->ch[newnode->data>last->data]=newnode;
		newnode->f=last;
		Fix(newnode);
	}
}ss;

int main(){
	//freopen("input.txt","r",stdin);
	null=new Node();
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf",&A[i],&B[i],&rate[i]);
	dp[1]=(double)s;
	ss.root=New(pi(dp[1]/(rate[1]*A[1]+B[1])*rate[1],dp[1]/(rate[1]*A[1]+B[1])));
	ss.root->k[0]=0;ss.root->k[1]=-INF;
	for(int i=2;i<=n;i++){
		Node *p=ss.find_near(-A[i]/B[i]);
		dp[i]=max(dp[i-1],(p->data.second+A[i]/B[i]*p->data.first)*B[i]);
		ss.Insert(New(pi(dp[i]/(rate[i]*A[i]+B[i])*rate[i],dp[i]/(rate[i]*A[i]+B[i]))));
	}
	printf("%.3lf\n",dp[n]);
	return 0;
}
