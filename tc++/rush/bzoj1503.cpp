# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=10000000;
int n,_min;
int now=0;
struct Node{
		int val,size;
		Node *ch[2];
		Node() {}
		Node(int val,int size):val(val),size(size){}
		int cmp(int x) {
			if(ch[0]->size>=x) return 0;
			else if(ch[0]->size+1==x) return -1;
			else return 1;
		}
		void maintain() {size=ch[0]->size+ch[1]->size+1;}
};
Node *null;

Node *New(int val){
	Node *o=new Node(val,1);
	o->ch[0]=o->ch[1]=null;
	return o;
}

struct Splay{
	Node *root;
	
	void Rotate(Node* &o,int d){
	//	puts("a");
	Node *p=o->ch[!d];
	o->ch[!d]=p->ch[d];p->ch[d]=o;
	//	puts("a");
	o->maintain();p->maintain();//puts("a");
	if(o==root) root=p;//puts("a");
	o=p;
}

void splay(Node* &o,int k){
	//printf("%d k:%d\n",o->val,k);
	int d=o->cmp(k);//printf("k:%d d:%d %d \n",k,d,o->ch[0]->size);
	if(d==-1) return;//printf("%d\n",o->val);
		Node *p=o->ch[d];
	int kk=d==1?k-o->ch[0]->size-1:k;//printf("k:%d o->ch[0]:%d kk:%d\n",k,o->ch[0]->size,kk);
	int dd=p->cmp(kk);//printf("dd:%d\n",dd);
	//printf("kk:%d dd:%d\n",kk,dd);
//	if(p->ch[dd]==null) puts("fhit");
	if(dd==-1) Rotate(o,!d);
	else{//printf("shit");
	//	printf("kk:%d %d %d %d\n",kk,p->ch[0]->size,dd==1?kk-p->ch[0]->size-1:kk,p->ch[dd]->val);
		splay(p->ch[dd],dd==1?kk-p->ch[0]->size-1:kk);
		if(d==dd){
			Rotate(o,!d);Rotate(o,!d);
		}
		else{
			Rotate(o->ch[d],!dd);Rotate(o,!d);
		}
	}
}

void print(Node *o){
	if(o==null) return;
		print(o->ch[0]);
	printf("%d ",o->val);print(o->ch[1]);
}

void print(){
	print(root);puts("");
}

	
	void init(){
		root=New(INF);
		root->size=2;root->ch[0]=New(-INF);
	}
	
	void insert(int val){
		//printf("val:%d\n",val);
	//	if(root==null) {root=New(val);return;}
		int num=0;
		Node *o=root,*p;
		while(o!=null){
			o->size++;
			p=o;
			if(val<o->val) o=o->ch[0];
				else num+=o->ch[0]->size+1,o=o->ch[1];
		}num++;
		if(val<p->val) p->ch[0]=New(val);
				else p->ch[1]=New(val);
			splay(root,num);
	}
	
	int find_low(int val){//找到比val小的最大编号
		Node *o=root;
		int num=0;
		while(o!=null){
			if(o->val>=val) o=o->ch[0];
				else num+=o->ch[0]->size+1,o=o->ch[1];
		}
		return num;
	}
};
Splay ss;

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int go=0;
	null=new Node(0,0);null->ch[0]=null->ch[1]=NULL;
	int k;
	char op[10];
	scanf("%d%d",&n,&_min);
	ss.init();
	int people=0;
	for(int i=1;i<=n;i++){//ss.print();
		//if(i%10000==0) printf("%d\n",i);
		scanf("%s",op);scanf("%d",&k);
		if(op[0]=='I'){
			if(k<_min) continue;
				people++;
			k-=now;
			ss.insert(k);
		}
		else if(op[0]=='A'){
			now+=k;
		}
		else if(op[0]=='S'){
			now-=k;
			int th=ss.find_low(_min-now);
		//	printf("%d\n",th);
			//ss.print();
			ss.splay(ss.root,th+1);//puts("fuck");ss.print();
			ss.splay(ss.root->ch[0],1);//puts("fuck");
			people-=ss.root->ch[0]->ch[1]->size;go+=ss.root->ch[0]->ch[1]->size;
			ss.root->ch[0]->ch[1]=null;
			ss.root->ch[0]->maintain();
			ss.root->maintain();
		}
		else{
			if(k>people) {puts("-1");continue;}
		//	printf("people:%d k:%d \n",people,k);
			ss.splay(ss.root,people-k+2);//ss.print();
			printf("%d\n",ss.root->val+now);
		}
	}
	printf("%d\n",go);
	return 0;
}
