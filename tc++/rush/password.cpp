# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxlen=300010;
const int maxnode=maxlen*19;
int n;
int node[maxn];
int first[maxlen],next[maxlen],v[maxlen],edge;
vector<int> to[maxlen];

void add_edge(int a,int b){
	//printf("a:%d b:%d\n",a,b);
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

struct ACmachine{
	int ch[maxlen][26];
	int fail[maxlen];
	bool val[maxlen];
	int sz;
	
	void init(){
		memset(first,-1,sizeof(first));edge=0;
		memset(ch[0],0,sizeof(ch[0]));sz=1;
	}
	
	void insert(char *s,int bh){
		int n=strlen(s),u=0;
		for(int i=0;i<n;i++){
			int c=s[i]-'a';
			if(!ch[u][c]){
				memset(ch[sz],0,sizeof(ch[sz]));ch[u][c]=sz;val[sz]=0;sz++;
			}
			u=ch[u][c];
		}
		val[u]=1;
		to[u].push_back(bh);
		node[bh]=u;
	}
	
	void getFail(){
		queue<int> Q;fail[0]=0;
		for(int c=0;c<26;c++){
			if(ch[0][c]) Q.push(ch[0][c]),fail[ch[0][c]]=0,add_edge(0,ch[0][c]);
		}
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int c=0;c<26;c++){
				int u=ch[x][c];
				if(!u) {ch[x][c]=ch[fail[x]][c];continue;}
				Q.push(u);
				int f=fail[x];
				while(f&&(!ch[f][c])) f=fail[f];
				fail[u]=ch[f][c];
				add_edge(ch[f][c],u);
			}
		}
	}
}ac;
int rangeL[maxlen],rangeR[maxlen],dfs_clock=0,dfn[maxlen];

void dfs(int x){
	rangeL[x]=++dfs_clock;dfn[dfs_clock]=x;
	for(int e=first[x];e!=-1;e=next[e])
		dfs(v[e]);
	rangeR[x]=dfs_clock;
}

struct Node{
	Node *ch[2];
	int size;
	Node() {}
};
Node *root[maxlen],seq[maxnode];Node *null;int seq_cnt=0;

Node *New(){
	Node *o=&seq[seq_cnt++];
	o->size=0;o->ch[0]=o->ch[1]=null;
	return o;
}

void Insert(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size+1;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=M){
		if(x->ch[0]==null) x->ch[0]=New();
		x->ch[1]=y->ch[1];
		Insert(x->ch[0],y->ch[0],L,M,val);
	}
	else{
		if(x->ch[1]==null) x->ch[1]=New();
		x->ch[0]=y->ch[0];
		Insert(x->ch[1],y->ch[1],M+1,R,val);
	}
}

int Ask(Node *x,Node *y,int k){
	int L=1,R=n;
	if(x->size-y->size<k) return -1;
	for(;;){
		if(L==R) return L;
		int M=(L+R)>>1;
		int tot=x->ch[0]->size-y->ch[0]->size;
		if(k<=tot)
			x=x->ch[0],y=y->ch[0],R=M;
		else k-=tot,x=x->ch[1],y=y->ch[1],L=M+1;
	}
}

char s[maxlen];
int main(){
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;
	scanf("%d",&n);
	ac.init();
	for(int i=1;i<=n;i++)
		scanf("%s",s),ac.insert(s,i);
	ac.getFail();
	dfs(0);
	root[0]=New();
	for(int i=1;i<=ac.sz;i++){
		root[i]=root[i-1];
		//printf("i:%d\n",i);
		for(int j=0;j<to[dfn[i]].size();j++){
			Node *u=New();
			Insert(u,root[i],1,n,to[dfn[i]][j]);
			root[i]=u;
		}
		//printf("root[%d]sz:%d\n",i,root[i]->size);
	}
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
		//printf("%d %d\n",rangeL[node[i]],rangeR[node[i]]);
		printf("%d\n",Ask(root[rangeR[node[i]]],root[rangeL[node[i]]-1],x));
	}
	return 0;
}
/*
5
a
aa
aaa
aaaa
aaaaa
3
3
*/
