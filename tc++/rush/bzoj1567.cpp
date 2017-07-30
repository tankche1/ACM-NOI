# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=55;
typedef long long LL;
typedef unsigned long long ull;
const int seed[2]={1771,17773},size=17771;
int n;
ull Power[2][maxn];
struct Hash{
	struct Node{
		ull key;
		Node *next;
		Node() {}
		Node(ull _key,Node *_next):key(_key),next(_next) {}
	}*h[size];
	
	void clear() {memset(h,0,sizeof(h));}
	
	void insert(ull key){
		int x=key%size;
		h[x]=new Node(key,h[x]);
	}
	
	bool find(ull key){
		int x=key%size;
		for(Node *i=h[x];i;i=i->next) if(i->key==key) return true;
		return false;
	}
};
Hash hash;

struct Mat{
	LL M[maxn][maxn];
	void read(){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%lld",&M[i][j]);
	}
	
	int operator () (int i,int j) const {return M[i][j];}
};
Mat A,B;
ull L[maxn][maxn];

void CalL(Mat &M,int len){
	ull ret;
	for(int i=1;i<=n;i++){
		ret=0;
		for(int j=1;j<=len;j++)
			ret*=seed[0],ret+=M(i,j);
		L[i][1]=ret;
		for(int j=len+1;j<=n;j++)
			ret-=M(i,j-len)*Power[0][len-1],ret*=seed[0],ret+=M(i,j),L[i][j-len+1]=ret;
	}
}

void InsertToHash(int len){
	CalL(A,len);
	hash.clear();
	ull ret;
	for(int j=1;j+len-1<=n;j++){
		ret=0;
		for(int i=1;i<=len;i++)
			ret*=seed[1],ret+=L[i][j];
		hash.insert(ret);
		for(int i=len+1;i<=n;i++)
			ret-=Power[1][len-1]*L[i-len][j],ret*=seed[1],ret+=L[i][j],hash.insert(ret);
	}
}

bool FindHash(int len){
	CalL(B,len);
	ull ret;
	for(int j=1;j+len-1<=n;j++){
		ret=0;
		for(int i=1;i<=len;i++)
			ret*=seed[1],ret+=L[i][j];
		if(hash.find(ret)) return true;
		for(int i=len+1;i<=n;i++){
			ret-=Power[1][len-1]*L[i-len][j],ret*=seed[1],ret+=L[i][j];
			if(hash.find(ret)) return true;
		}
	}
	return false;
}

bool check(int len){
	InsertToHash(len);
	if(FindHash(len)) return true;
	return false;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<=1;i++){
		Power[i][0]=1;
		for(int j=1;j<=n;j++)
			Power[i][j]=Power[i][j-1]*seed[i];
	}
	A.read();B.read();
	int L=0,R=n;
	while(L<=R){
		int M=(L+R)>>1;
		if(check(M))
			L=M+1;
		else R=M-1;
	}
	printf("%d\n",L-1);
	return 0;
}
