/*
splay的题 和维修数列差不多
对于括号序列 去掉（）后变成）））（（（ 维护坐起和右起中）的数目和（的数目 实际处理中用1和-1来搞
然后标记要有翻转标记 改变标记 统一标记 注意统一的时候要覆盖改变 改变的时候把统一换个值
然后不就变成维修数列了。。。
*/
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,m;
int s[maxn];

inline int swa(int &a,int &b){
	int t=a;
	a=-b;b=-t;
}

struct Node{
	Node *ch[2];
	int size,val,lmax,lmin,rmax,rmin,sum;
	int same;
	bool rev,change;
	
	int cmp(int x) {if(x==ch[0]->size+1) return -1;return x<=ch[0]->size?0:1;}
	
	void maintain(){
		size=ch[0]->size+ch[1]->size+1;
		sum=ch[0]->sum+ch[1]->sum+val;
		lmax=max(max(ch[0]->lmax,ch[0]->sum+val),ch[0]->sum+val+ch[1]->lmax);
		lmin=min(min(ch[0]->lmin,ch[0]->sum+val),ch[0]->sum+val+ch[1]->lmin);
		rmin=min(min(ch[1]->rmin,ch[1]->sum+val),ch[1]->sum+val+ch[0]->rmin);
		rmax=max(max(ch[1]->rmax,ch[1]->sum+val),ch[1]->sum+val+ch[0]->rmax);
	}
	
	void pushdown(){
		if(rev){
			ch[0]->rev=!ch[0]->rev;ch[1]->rev=!ch[1]->rev;
			swap(ch[0]->ch[0],ch[0]->ch[1]);swap(ch[1]->ch[0],ch[1]->ch[1]);
			swap(ch[0]->lmax,ch[0]->rmax);swap(ch[0]->lmin,ch[0]->rmin);
			swap(ch[1]->lmax,ch[1]->rmax);swap(ch[1]->lmin,ch[1]->rmin);
			rev=0;
		}
		if(same!=0){
			ch[0]->same=ch[1]->same=same;
			if(ch[0]->size!=0) ch[0]->val=same;if(ch[1]->size!=0) ch[1]->val=same;
			ch[0]->change=ch[1]->change=0;
			ch[0]->sum=ch[0]->size*same;ch[1]->sum=ch[1]->size*same;
			ch[0]->lmin=ch[0]->rmin=min(0,ch[0]->sum);ch[0]->lmax=ch[0]->rmax=max(0,ch[0]->sum);
			ch[1]->lmin=ch[1]->rmin=min(0,ch[1]->sum);ch[1]->lmax=ch[1]->rmax=max(0,ch[1]->sum);
			same=0;
		}
		if(change){
			change=0;
			ch[0]->same=-ch[0]->same;ch[1]->same=-ch[1]->same;
			ch[0]->val=-ch[0]->val;ch[1]->val=-ch[1]->val;
			if(!ch[0]->same) ch[0]->change^=1; else ch[0]->change=0;
			if(!ch[1]->same) ch[1]->change^=1;else ch[1]->change=0;
			ch[0]->sum=-ch[0]->sum;ch[1]->sum=-ch[1]->sum;
			swa(ch[0]->lmin,ch[0]->lmax);swa(ch[0]->rmin,ch[0]->rmax);
			swa(ch[1]->lmin,ch[1]->lmax);swa(ch[1]->rmin,ch[1]->rmax);
		}
	}
	
};
Node *null;

Node* New(int x){
	Node *o=new Node();
	o->sum=o->val=x;o->lmax=o->rmax=max(0,x);o->lmin=o->rmin=min(0,x);
	o->same=o->rev=o->change=0;
	o->size=1;
	o->ch[0]=o->ch[1]=null;
	return o;
}

struct Splay{
	Node *root;
	
	Node *Build(int L,int R){
		int M=(L+R)>>1;
		Node *o=New(s[M]);
		if(L<M) o->ch[0]=Build(L,M-1);
		if(M<R) o->ch[1]=Build(M+1,R);
		o->maintain();
		return o;
	}
	
	void init(int n){
		root=Build(0,n);
	}
	
	void Rotate(Node* &o,int d){
		//o->pushdown();
		Node *p=o->ch[!d];//p->pushdown();
		o->ch[!d]=p->ch[d];p->ch[d]=o;
		o->maintain();p->maintain();
		if(root==o) root=p;
		//o->maintain();p->maintain();
		o=p;
	}
	
	void splay(Node* &o,int k){
		o->pushdown();
		int d=o->cmp(k);
		//printf("o->val:%d k:%d num:%d size:%d d:%d\n",o->val,k,o->ch[0]->size+1,o->size,d);
		if(d!=-1){
			if(d==1) k-=o->ch[0]->size+1;
			o->ch[d]->pushdown();
			int dd=o->ch[d]->cmp(k);
		//	printf("d:%d kk:%d\n",d,k);
			if(dd==-1) Rotate(o,!d);
			else{//puts("fuck");
				Node *p=o->ch[d];
				if(dd==1) k-=p->ch[0]->size+1;
				//printf("k:%d %d %d\n",k,o->ch[d]->val,o->ch[d]->ch[dd]->val);
				splay(o->ch[d]->ch[dd],k);
				if(dd==d){
					Rotate(o,!d);Rotate(o,!d);
				}
				else {
					Rotate(o->ch[d],!dd);Rotate(o,!d);
				}
			}
		}
	}
		
	void make_same(int a,int b,int c){
	//	printf("num:%d\n",root->ch[0]->size+1);
		splay(root,a);
		splay(root->ch[1],b-a+2);
		//printf("num:%d\n",root->ch[0]->size+1);
		Node *p=root->ch[1]->ch[0];
		p->val=c;
		p->same=c;
		p->change=0;
		p->sum=p->size*c;
		p->lmin=p->rmin=min(0,p->sum);p->lmax=p->rmax=max(0,p->sum);
		root->ch[1]->maintain();root->maintain();
		//printf("num:%d\n",root->ch[0]->size+1);
	}
		
	void change(int a,int b){
	//	print();printf("num:%d\n",root->ch[0]->size+1);
		splay(root,a);//print();
		splay(root->ch[1],b-a+2);
		//print();
		Node *p=root->ch[1]->ch[0];
		p->val=-p->val;
		p->change=!p->change;
		p->same=-p->same;
		if(p->same!=0) p->change=0;
		p->sum=-p->sum;
		swa(p->lmin,p->lmax);swa(p->rmin,p->rmax);
		root->ch[1]->maintain();root->maintain();
	}
	
	void reverse(int a,int b){
	//	print();//printf("num:%d\n",root->ch[0]->size+1);
		splay(root,a);//printf("num:%d a:%d \n",root->ch[0]->size+1,a);
	//	print();
		splay(root->ch[1],b-a+2);//print();
		Node *p=root->ch[1]->ch[0];//printf("num:%d\n",root->ch[0]->size+1);
		//print(p);puts("");
		p->rev^=1;
		swap(p->ch[0],p->ch[1]);
		//print(p);puts("");
		swap(p->lmax,p->rmax);swap(p->lmin,p->rmin);
		root->ch[1]->maintain();root->maintain();
		//printf("num:%d\n",root->ch[0]->size+1);
	}
	
	void query(int a,int b){
		splay(root,a);
		splay(root->ch[1],b-a+2);
		Node *p=root->ch[1]->ch[0];
		//print(p);printf("lmin:%d lmax:%d rmin:%d rmax:%d sum:%d \n",p->lmin,p->lmax,p->rmin,p->rmax,p->sum);
		printf("%d\n",(-p->lmin+1)/2+(p->rmax+1)/2);
	}
	
	void print(Node *o){
		if(o==null) return;
			o->pushdown();
			print(o->ch[0]);
		if(o->val==1||o->val==-1)
			printf("%c",o->val==1?'(':')');
		else printf("%c",'&');
		print(o->ch[1]);
	}
	
	void print(){
		print(root);puts("");
	}
	
};
Splay ss;

int main(){
	int a,b,c;
	null=new Node();
	null->sum=null->val=null->lmax=null->lmin=null->rmin=null->rmax=null->same=null->rev=null->change=null->size=0;
	null->ch[0]=null->ch[1]=NULL;
	char t,op[20];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		while((t=getchar())&&t!='('&&t!=')');
		s[i]=t=='('?1:-1;
	}
	s[0]=s[n+1]=0;
	ss.init(n+1);
	for(int i=1;i<=m;i++){
		//ss.print();
		scanf("%s",op);
		if(op[0]=='R'){
			scanf("%d%d",&a,&b);while((t=getchar())&&t!='('&&t!=')');c=t=='('?1:-1;
			ss.make_same(a,b,c);
		}
		else if(op[0]=='S'){
			scanf("%d%d",&a,&b);
			ss.reverse(a,b);
		}
		else if(op[0]=='I'){
			scanf("%d%d",&a,&b);
			ss.change(a,b);
		}
		else{
			scanf("%d%d",&a,&b);
			ss.query(a,b);
		}
	}
	return 0;
}
/*
8 10
((((((((
S 1 4
Q 1 2
R 1 4 )
Q 1 2
I 1 2
Q 1 2
Q 1 4
Q 1 2
Q 3 4
Q 1 2
*/
