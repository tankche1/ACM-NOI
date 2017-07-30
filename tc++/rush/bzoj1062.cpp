#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int X=3010,Y=4010;
struct Cloud{
	int t,l;
};
Cloud c[1000010];
int n,len,m,q,op;
int a[2][X][Y];

inline int lowbit(int x) {return x&(-x);}

void Add(int k,int t,int l,int val){
	if(k) l=l-t+m,t-=len;else l=l+t;
	//	printf("l:%d t:%d\n",l,t);
	for(int i=t+1;i<X;i+=lowbit(i))
		for(int j=l+1;j<Y;j+=lowbit(j)){
			a[k][i][j]+=val;//printf("i:%d j:%d\n",i,j);
		}
}

int sum(int k,int t,int l){
	int ans=0;
	for(int i=t+1;i;i-=lowbit(i))
		for(int j=l+1;j;j-=lowbit(j))
			ans+=a[k][i][j];
	return ans;
}

int Area(int k,int x0,int y0,int x1,int y1){
	if(k) y0=y0-x0+m,x0-=len;else y0=x0+y0;
	if(k) y1=y1-x1+m,x1-=len;else y1=x1+y1;
	return sum(k,x1,y1)-sum(k,x0-1,y1)-sum(k,x1,y0-1)+sum(k,x0-1,y0-1);
}

void insert(int col,int val){
	Add(0,c[col].t,c[col].l,val);if(c[col].t<=len) Add(0,c[col].t+n,c[col].l,val);
	Add(1,c[col].t+n,c[col].l,val);if(c[col].t>=len) Add(1,c[col].t,c[col].l,val);
}

int query(int t,int L,int R){
	int d=R==len,ans=0;
	ans+=Area(0,t,L,t+R,len);
	if(R) ans+=Area(1,n-R+t+d,L-R+d,n+t-1,len+R-1);
	return ans;
}

int main(){
	int t,col,l,r,d;
	scanf("%d%d",&q,&len);n=len<<1;m=n<<1;
	while(q--){
		scanf("%d%d",&op,&t);t%=n;
		if(op==1){
			scanf("%d%d%d%d",&col,&l,&r,&d);
			c[col].t=(t-l*d+n)%n;
			c[col].l=r-l;
			insert(col,1);
		}
		else if(op==2){
			scanf("%d%d",&l,&r);
			printf("%d\n",query(t,l,r));
		}
		else {
			scanf("%d",&col);
			insert(col,-1);
		}
	}
	return 0;
}
