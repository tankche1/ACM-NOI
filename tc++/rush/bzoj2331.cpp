# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
const int mod=20110520;
const int power=81*81*27;
const int hmod=10233071;
char s[110];
int m,n;
inline int pos(int x,int y) {return x*n+y;}

struct Node{
	int key;
	int num;
	Node *next;
	Node() {}
};
Node *h[hmod];

Node *New(int k){
	Node *o=new Node();o->key=k;o->num=-1;o->next=NULL;return o;
}

Node *get(int key){
	if(h[key%hmod]==NULL) return h[key%hmod]=New(key);
	Node *e;
	for(e=h[key%hmod];e->next!=NULL;e=e->next){
		if(e->key==key) return e;
	}
	if(e->key==key) return e;
	else return e->next=New(key);
}

struct State{
	int left,up[11];
	
	void init(){
		left=0;memset(up,0,sizeof(up));
	}
	
	int getcode(){
		int key=left;
		for(int i=0;i<n;i++)
			key=key*3+up[i];
		return key;
	}
	
	bool next(int row,int col,int U,int D,int L,int R,State &T){
		if(U!=up[col]) return false;
		if(L!=left) return false;
		if(D&&row==m-1) return false;
		if(L&&col==0) return false;
		if(U&&row==0) return false;
		if(R&&col==n-1) return false;
		for(int i=0;i<n;i++) T.up[i]=up[i];
		T.left=R;T.up[col]=D;
		return true;
	}
};
State T;

int rec(int row,int col,State S){
	if(col==n) row++,col=0;
	if(row==m) return 1;
	Node *hkey=get(pos(row,col)*power+S.getcode());
	if(hkey->num!=-1) return hkey->num;
	int &res=hkey->num;res=0;
	/*printf("row:%d col:%d \n",row,col);
	for(int i=0;i<n;i++) printf("up[%d]:%d ",i,S.up[i]);printf("left:%d\n",S.left);*/
	
	if(s[pos(row,col)]=='*'){
		if(S.next(row,col,0,0,0,0,T)) res+=rec(row,col+1,T);
	}
	else{//1表示向内 2表示向外
		if(S.next(row,col,2,2,0,0,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,0,0,2,2,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,2,0,0,0,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,0,0,2,0,T)) res+=rec(row,col+1,T);
		
		if(S.next(row,col,0,1,0,0,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,0,0,0,1,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,1,1,0,0,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,0,0,1,1,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,1,0,1,0,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,1,0,0,2,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,0,2,1,0,T)) res+=rec(row,col+1,T);
		if(S.next(row,col,0,2,0,2,T)) res+=rec(row,col+1,T);
	}
	res%=mod;
	/*printf("row:%d col:%d \n",row,col);
	for(int i=0;i<n;i++) printf("up[%d]:%d ",i,S.up[i]);printf("left:%d res:%d\n",S.left,res);
	*/
	return res;
}

char news[110];

int main(){
	//freopen("floor.in","r",stdin);
	//freopen("floor.out","w",stdout);
	char t;
	for(int i=0;i<hmod;i++) h[i]=NULL;
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			while((t=getchar())&&t!='*'&&t!='_');
			s[i*n+j]=t;
	}
	if(n>m){
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				news[(n-1-j)*m+i]=s[i*n+j];
		swap(m,n);
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				s[i*n+j]=news[i*n+j];
	}
	State S;
	S.init();
	int ans=rec(0,0,S);
	printf("%d\n",ans);
	return 0;
}
/*
3 2
__
__
__
*/
