# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
# define FUCK printf("%d\n",fuck);
using namespace std;
const int maxn=250011;
const int INF=~0U>>1;
const int x=97;
bool first;
char s[maxn][11];

unsigned hash(char *s){
	unsigned ans=0;
	int m=strlen(s);
	unsigned shit=x;
	for(int i=1;i<=m;i++,shit*=x)
		ans+=s[i]*shit;
	return ans;
}

struct Node{
	Node *ch[2],*parent;
	int size,label,val,global_time;
	
	int cmp_size(int s){
		if(s==ch[0]->size+1) return -1;
		return s<=ch[0]->size?0:1;
	}
	
	int cmp_val(int v,int global){
		if(v==val&&global==global_time) return -1;
		return (v<val||(v==val&&global>global_time))?0:1;
	}
	
	Node(){
	}
	
	void maintain(){
		size=1+ch[0]->size+ch[1]->size;
	}
	
};
Node *null;

struct Splay{
	Node seq[maxn];
	Node *root;
	Node *pos;
	int cnt;
	
	void rotate(Node* o,int d){
	Node *p=o->ch[!d];o->ch[!d]=p->ch[d];p->ch[d]->parent=o;
	p->parent=o->parent;o->parent->ch[o->parent->ch[0]==o?0:1]=p;
	p->ch[d]=o;o->parent=p;
	o->maintain();p->maintain();
	if(p->parent==null) root=p;
}

void splay(Node* o,int k){
	int d=o->cmp_size(k);
	if(d==-1) return;
	if(d==1) k-=o->ch[0]->size+1;
	Node *p=o->ch[d];
	int dd=p->cmp_size(k);
	int kk=dd==0?k:k-p->ch[0]->size-1;
	if(dd!=-1){
		splay(p->ch[dd],kk);
		if(dd==d)
		{rotate(o,!d);rotate(o->parent,!d);}
		else {rotate(o->ch[d],!dd);rotate(o,!d);}
	}
	else rotate(o,!d);
}
	
	Node *New(int label,int val,Node *p,int global_time){
		Node *o=&seq[++cnt];
		seq[cnt].label=label;seq[cnt].val=val;
		seq[cnt].ch[0]=seq[cnt].ch[1]=null;
		o->size=1;o->parent=p;o->global_time=global_time;
		return o;
	}
	
	void init(){
		cnt=0;
		root=New(-2,INF,null,0);
	}
	
	int k_th(Node *o){
		int ans=o->ch[0]->size+1;
		while(o->parent!=null) {
			int d=o==o->parent->ch[0]?0:1;
			o=o->parent;
			if(d==1) ans+=o->ch[0]->size+1;
		}
		return ans;
	}
	
	void insert(Node *u,int label,int val,int global_time){
			int d=u->cmp_val(val,global_time);
			if(d==-1) d=1;
			if(u->ch[d]!=null)
				insert(u->ch[d],label,val,global_time);
			else{
				u->ch[d]=New(label,val,u,global_time);
				pos=u->ch[d];
			}
			u->maintain();
	}
	
	Node* insert(int label,int val,int global_time){
		insert(root,label,val,global_time);
		splay(root,k_th(pos));
		return root;
	}
	
	void range(int a,int b){
		splay(root,a);
		splay(root->ch[1],b-a);
	}
	
	Node* &last(){
		return root->ch[1]->ch[0];
	}
	
	void update_rson_lson(){
		root->ch[1]->maintain();
		root->maintain();
	}
	
	void print(Node *o){
		if(o==null) return;
		//printf("size:%d goto left\n",o->size);
		//printf("label:%d left:%d right:%d\n",o->label,o->ch[0]->label,o->ch[1]->label);
		print(o->ch[0]);
		printf("label:%d val:%d size:%d goto right\n",o->label,o->val,o->size);
		
		print(o->ch[1]);
	}
	
	void print(){
		print(root);
	}
	
	void print(Node *o,int x){
		if(o==null) return;
		print(o->ch[1],x);
		if(!first) printf(" "); first=false;
			printf("%s",s[o->label]);
		print(o->ch[0],x);
	}
};
Splay ss;

map<int,Node*> name;
int tot_name=0;

int goal[maxn];
int main(){
	//freopen("input.txt","r",stdin);
	null=new Node();
	null->size=null->val=0;null->label=0;
	int n,score;
	char op[50];
	scanf("%d",&n);
	//ss.insert(0,INF);
	ss.init();
	ss.insert(-1,-INF,0);
	int bh;
	for(int fuck=1;fuck<=n;fuck++){
	//	FUCK
		scanf("%s",op);
		int ll=strlen(op);
		if(op[0]=='+'){
			scanf("%d",&score);
			unsigned name_num=hash(op+1);
			if(!name.count(name_num)) {
				tot_name++;
				name[name_num]=ss.insert(tot_name,score,tot_name);
				for(int i=1;i<ll;i++)
					s[tot_name][i-1]=op[i];
				s[tot_name][ll-1]='\0';
			}
			else{
				bh=name[name_num]->label;int global=name[name_num]->global_time;
				//printf("bh:%d\n",bh);
				int rank=ss.k_th(name[name_num]);//if(op[1]=='B') ss.print();
				ss.range(rank-1,rank+1);//if(op[1]=='B') ss.print();
					//ss.print(ss.last(),1);
				ss.last()=null;
				ss.update_rson_lson();
				//if(op[1]=='B') ss.print();
				name[name_num]=ss.insert(bh,score,global);
			}
			goal[name[name_num]->label]=score;
		}
		else if(op[0]=='?'&&op[1]>='A'&&op[1]<='Z'){
			unsigned name_num=hash(op+1);
			printf("%d\n",ss.root->size-1-ss.k_th(name[name_num])+1);
		}
		else{
			int num=0;int t=1;
			while(op[t]>='0'&&op[t]<='9') {num=num*10+op[t]-'0';t++;}
			int l=max(2,ss.root->size-2-num+1+1-9),r=ss.root->size-2-num+1+1;
			//printf("l:%d r:%d\n",l,r);
			ss.range(l-1,r+1);first=true;
			ss.print(ss.last(),1);printf("\n");
		}
		//ss.print();printf("\n");
	}
	return 0;
}
/*
500
+A 3
+AA 3
+AB 4
?1
*/
