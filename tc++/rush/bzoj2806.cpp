#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxn=1200010;
int n,m;
int cnt=0;
char s[maxn];
char T[maxn];
int v[maxn];
int dp[maxn],q[maxn],head,tail;

struct Node{
	Node *par,*go[3];
	int val;
	Node(){memset(go,0,sizeof(go));par=0;}
};
Node sam[maxn<<1];int sam_cnt=0;
Node *root,*last;

void insert(int w){
	Node *p=last;
	Node *np=&sam[sam_cnt++];np->val=p->val+1;
	while(p&&p->go[w]==0)
		p->go[w]=np,p=p->par;
	if(p==0)
		np->par=root;
	else{
		Node *q=p->go[w];
		if(p->val+1==q->val)
			np->par=q;
		else{
			Node *nq=&sam[sam_cnt++];nq->val=p->val+1;
			memcpy(nq->go,q->go,sizeof(q->go));
			nq->par=q->par;
			q->par=nq;
			np->par=nq;
			while(p&&p->go[w]==q)
				p->go[w]=nq,p=p->par;
		}
	}
	last=np;
}


void match(char *s,int len){
	Node *p=root;
	int cnt=0;
	for(int i=1;i<=len;i++){
		int w=s[i]-'0';
		if(p->go[w]) cnt++,p=p->go[w];
		else{
			while(p&&p->go[w]==0) p=p->par;
			if(p==0) cnt=0,p=root;
			else cnt=p->val+1,p=p->go[w];
		}
		v[i]=cnt;
	}
}

bool check(int L,int n){
	for(int i=0;i<L;i++) dp[i]=0;
	head=0;tail=-1;
	for(int i=L;i<=n;i++){
		dp[i]=dp[i-1];
		while(tail>=head&&dp[i-L]-(i-L)>=dp[q[tail]]-q[tail]) tail--;
		q[++tail]=i-L;
		while(head<=tail&&q[head]<i-v[i]) head++;
		if(head<=tail) dp[i]=max(dp[i],dp[q[head]]+i-q[head]);
	}
	return 10*dp[n]>=9*n;
}

int main(){
	root=&sam[sam_cnt++];last=root;root->val=0;
	scanf("%d %d\n",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%s",T);int len=strlen(T);
		for(int j=0;j<len;j++)
			insert(T[j]-'0');
		insert(2);
	}
	for(int i=1;i<=n;i++){
		T[0]='a';
		scanf("%s",T+1);
		int len=strlen(T)-1;
		match(T,len);
		int L=1,R=len;
		while(L<=R){
			int M=(L+R)>>1;
			if(check(M,len)) L=M+1;
			else R=M-1;
		}
		printf("%d\n",L-1);
	}
	return 0;
}
