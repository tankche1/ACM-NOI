# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int INF=~0U>>2;

int n,m;
int A[maxn];
int Min,Max;
int Minscc;

struct Node{
	int val,size;
	Node *ch[2];
	
	void maintain(){
		size=ch[0]->size+ch[1]->size+1;
	}
	
	int cmp(int k){
		if(k<=ch[0]->size) return 0;
			else if(k==ch[0]->size+1) return -1;
				return 1;
	}
};
Node *null;
Node seq[1000010];int seq_cnt=0;

Node* New(int x){
	Node *o=&seq[seq_cnt++];
	o->ch[0]=o->ch[1]=null;
	o->size=1;
	o->val=x;
	return o;
}

struct Splay{
	Node *root;
	
	void init(){
		root=null;
		insert(INF);
		insert(-INF);
		insert(-INF-1);
	}
	
	void Rotate(Node* &o,int d){
		Node *p=o->ch[!d];
		o->ch[!d]=p->ch[d];p->ch[d]=o;
		o->maintain();p->maintain();
		if(root==o) root=p;
		o=p;
	}
	
	void splay(Node* &o,int k){
		int d=o->cmp(k);
		if(d!=-1){
			if(d==1) k-=o->ch[0]->size+1;
			int dd=o->ch[d]->cmp(k);
			if(dd==-1) Rotate(o,!d);
			else{
				if(dd==1) k-=o->ch[d]->ch[0]->size+1;
				splay(o->ch[d]->ch[dd],k);
				if(d==dd){
					Rotate(o,!d);Rotate(o,!d);
				}
				else{
					Rotate(o->ch[d],!dd);Rotate(o,!d);
				}
			}
		}
	}
	
	void insert(int x){
		Node *o=root,*p;
		int num=0;
		if(root==null) {root=New(x);return;}
		while(1){
			if(o==null) break;
			p=o;
			o->size++;
			if(x<=o->val) o=o->ch[0];
				else o=o->ch[1],num+=p->ch[0]->size+1;
		}
		if(x<=p->val) p->ch[0]=New(x);
			else p->ch[1]=New(x);
		num++;
		splay(root,num);
	}
	
	int find_min(int x){//找到x的最小位置
		Node *o=root;
		int num=0,ans;
		while(1){
			if(o==null) break;
			if(o->val==x) ans=num+o->ch[0]->size+1;
			if(o->val>=x) o=o->ch[0];
				else {num+=o->ch[0]->size+1;o=o->ch[1];}
		}
		//printf("ans:%d\n",ans);
		return ans;
	}
	
	void erase(int x){
		int num=find_min(x);
		splay(root,num-1);
		splay(root->ch[1],2);
		root->ch[1]->ch[0]=null;
		root->ch[1]->maintain();
		root->maintain();
	}
	
	void lower_find(int x){//找到小于x的最大值的bh并旋转到根
		Node *o=root;int num=0;
		while(1){
			if(o==null) break;
				//printf("val:%d\n",o->val);
			if(o->val>=x) o=o->ch[0];
				else {num+=o->ch[0]->size+1;o=o->ch[1];}
		}
		splay(root,num);
		//printf("lower_find :%d\n",root->val);
	}
	
	void upper_find(int x) {//找到大于x的最小值得bh并旋转到根
		Node *o=root;int num=0;
		while(1){
			if(o==null) break;
			//	printf("o->val:%d\n",o->val);
			if(o->val>x) o=o->ch[0];
				else {num+=o->ch[0]->size+1;o=o->ch[1];}
		}
		num++;
		splay(root,num);
		//printf("upper_find:%d\n",root->val);
	}
	
	void print(Node *o){
		if(o==null) return;
			print(o->ch[0]);
		printf("%d ",o->val);
		print(o->ch[1]);
	}
	
	void print(){
		printf("size:%d ",root->size);
		print(root);puts("");
	}
};

vector<int> T;

struct SegmentLineTree{
	Splay s[maxn<<2];
	
	void build(int o,int L,int R){
		s[o].init();
		for(int i=L;i<=R;i++)
			s[o].insert(A[i]);
	//	s[o].print();
		if(L==R) return;
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
	}
	
	void change(int o,int L,int R,int pos,int val){
	//	printf("o:%d L:%d R:%d\n",o,L,R);
		//s[o].print();
		s[o].erase(A[pos]);
		s[o].insert(val);
		//s[o].print();
	//	printf("o:%d L:%d R:%d\n",o,L,R);
		if(L==R) return;
		int M=(L+R)>>1;
		if(pos<=M) change(o<<1,L,M,pos,val);
			else change(o<<1|1,M+1,R,pos,val);
	}
	
	void query(int o,int L,int R,int ql,int qr){
		if(ql<=L&&qr>=R) {
			T.push_back(o);return;
		}
		int M=(L+R)>>1;
		if(ql<=M) query(o<<1,L,M,ql,qr);
		if(qr>M) query(o<<1|1,M+1,R,ql,qr);
	}
	
	int solve(int ql,int qr,int k){
		T.clear();
		query(1,1,n,ql,qr);
		Min=INF+2;Max=-INF-3;
		//printf("%d\n",T.size());
		for(int i=0;i<T.size();i++){
			//s[T[i]].print();
			s[T[i]].splay(s[T[i]].root,3);
			Min=min(Min,s[T[i]].root->val);
			s[T[i]].splay(s[T[i]].root,s[T[i]].root->size-1);
			Max=max(Max,s[T[i]].root->val);
		}
		//printf("%d %d\n",Min,Max);
		int L=Min+1,R=Max+1,M,rangeL,rangeR;
		while(L<=R){
			M=(L+R)>>1;Minscc=-INF-3;rangeL=1;
			for(int i=0;i<T.size();i++){
				s[T[i]].lower_find(M);
				if(s[T[i]].root->val>Minscc) Minscc=s[T[i]].root->val;
			}
			//printf("M:%d Minscc:%d\n",M,Minscc);
			for(int i=0;i<T.size();i++){
				s[T[i]].lower_find(Minscc);
				rangeL+=s[T[i]].root->ch[0]->size+1-2;
			}
			rangeR=0;
			for(int i=0;i<T.size();i++){
				s[T[i]].upper_find(Minscc);
				rangeR+=s[T[i]].root->ch[0]->size-2;
			}
			//printf("%d %d\n",rangeL,rangeR);
			if(k>=rangeL&&k<=rangeR){
				return Minscc;
			}
			else if(k<rangeL) R=M-1;
			else L=M+1;
		}
	}
	
};
SegmentLineTree st;

int main(){
	char op[20];
	int pos,val,ql,qr,k;
	null=&seq[seq_cnt++];
	null->ch[0]=null->ch[1]=NULL;null->size=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	st.build(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%s",op);
		if(op[0]=='C') {
			scanf("%d%d",&pos,&val);
			st.change(1,1,n,pos,val);
			A[pos]=val;
		}
		else{
			scanf("%d%d%d",&ql,&qr,&k);
			printf("%d\n",st.solve(ql,qr,k));
		}
	}
	return 0;
}
