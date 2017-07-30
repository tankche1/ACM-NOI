#include<stdio.h>
# include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
typedef pair<int,int> pi;
const int maxn=100010;
//map<string,int> ms;
int fa[maxn];
char s[maxn],word[maxn];
int node[maxn];
int slen,pos;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int l[maxn],r[maxn];

void add_edge(int a,int b){
//	printf("a:%d b:%d\n",a,b);
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

inline int lowbit(int x){return (x&(-x));}

struct FenwickTree{
	int C[maxn],n;
	void init(int nn){
		n=nn;memset(C,0,sizeof(C));
	}
	
	void add(int x,int val){
		while(x<=n){
			C[x]+=val;
			x+=lowbit(x);
		}
	}
	
	int sum(int x){
		int res=0;
		while(x>0){
			res+=C[x];
			x-=lowbit(x);
		}
		return res;
	}
}fwt;

struct ACmachine{
	int ch[maxn][26],sz;
	//int val[maxn];
	int fail[maxn];
	
	void init(){
		memset(first,-1,sizeof(first));edge=0;
		sz=0;memset(ch[0],0,sizeof(ch[0]));
	}
	
	void insert(char *s,int bh){
		int n=strlen(s),u=0;
		for(int i=0;i<n;i++){
			int c=s[i]-'a';
			if(!ch[u][c])
				ch[u][c]=++sz,memset(ch[sz],0,sizeof(ch[sz])),fa[sz]=u;//,val[sz]=0;
			u=ch[u][c];
		}
		//val[u]=bh//;ms[string(s)]=bh;node[bh]=u;
		node[bh]=u;
	}
	
	void getFail(){
		queue<int> Q;
		int u=0;
		fail[0]=0;
		for(int c=0;c<26;c++)
			if(ch[u][c])
				Q.push(ch[u][c]),fail[ch[u][c]]=0,add_edge(0,ch[u][c]);
		while(!Q.empty()){
			int u=Q.front();Q.pop();
			for(int c=0;c<26;c++){
				if(ch[u][c]==0) {ch[u][c]=ch[fail[u]][c];continue;}
				int f=fail[u];
				//while(f&&(!ch[f][c])) f=fail[f];
				fail[ch[u][c]]=ch[f][c];
				add_edge(ch[f][c],ch[u][c]);
				Q.push(ch[u][c]);
			}
		}
	}
}ac;

int dfs_clock=0;
void dfs(int x,int fa){
	l[x]=++dfs_clock;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa) continue;
		dfs(v[e],x);
	}
	r[x]=dfs_clock;
}

int m;
int ans[maxn];

struct Duty{
	int first,second,bh;
	bool operator <(const Duty &rhs)const{
		if(first==rhs.first) return second<rhs.second;
		return first<rhs.first;
	}
};
Duty duty[maxn];

int main(){
	int u=0;
	//freopen("type.in","r",stdin);
	//freopen("type.ans","w",stdout);
	scanf("%s",s);slen=strlen(s);pos=0;
	ac.init();
	int bh=0;fa[0]=0; 
	for(int i=0;i<slen;i++){
		if(s[i]>='a'&&s[i]<='z'){
			int c=s[i]-'a';
			if(!ac.ch[u][c]){
				ac.ch[u][c]=++ac.sz;memset(ac.ch[ac.sz],0,sizeof(ac.ch[ac.sz]));
				fa[ac.sz]=u;
			}
			u=ac.ch[u][s[i]-'a'];
		}
		else if(s[i]=='B')
			u=fa[u];
		else{
			bh++;
			node[bh]=u;
		}
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d %d",&duty[i].second,&duty[i].first),duty[i].bh=i;
	sort(duty+1,duty+m+1);
	ac.getFail();
	dfs(0,0);
	fwt.init(slen);
	pos=1;int now=0;u=0;
	for(int i=0;i<slen;i++){
		if(s[i]>='a'&&s[i]<='z'){
			u=ac.ch[u][s[i]-'a'];
			fwt.add(l[u],1);
		}
		else if(s[i]=='B'){
			fwt.add(l[u],-1),
			u=fa[u];
		}
		else{
			now++;
			while(now==duty[pos].first){
				ans[duty[pos].bh]=fwt.sum(r[node[duty[pos].second]])-fwt.sum(l[node[duty[pos].second]]-1);
				if(++pos>m) break;
			}
			if(pos>m) break;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
