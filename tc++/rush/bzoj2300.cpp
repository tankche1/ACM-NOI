#include<stdio.h>
#include<string.h>
# include<math.h>
# include<set>
#include<algorithm>
using namespace std;
const int maxm=100010;
int n,m,q;
int x[maxm],y[maxm];
bool del[maxm];
int op[maxm<<1],p[maxm<<1];

typedef pair<int,int> Point;

set<Point> s;
set<Point>::iterator next,last,pos;
double len;
	
double Length(Point A,Point B){
	return sqrt((B.first-A.first)*(B.first-A.first)+(B.second-A.second)*(B.second-A.second));
}

bool Slope(Point A,Point B,Point C){
	//k(AB)>k(BC)
	if((B.second-A.second)*(C.first-B.first)>(C.second-B.second)*(B.first-A.first)) return true;
	return false;
}

void Insert(Point P){
	next=s.lower_bound(P);
	last=--next;++next;
	if((P.second-last->second)*(next->first-last->first)>(next->second-last->second)*(P.first-last->first)){
		pos=last;
		len-=Length(*last,*next);
		++next;++last;
		while(next!=s.end()&&(!Slope(P,*last,*next))) {len-=Length(*last,*next);s.erase(*last);last=next;++next;}
		next=pos;pos=last;last=next;last--;
		while(next!=s.begin()&&(!Slope(*last,*next,P))) {
			len-=Length(*last,*next);s.erase(*next);next=last;--last;
		}
		s.insert(P);len+=Length(P,*next);len+=Length(P,*pos);
	}
}
double ans[maxm<<1];

int main(){
	scanf("%d%d%d",&n,&x[0],&y[0]);
	memset(del,false,sizeof(del));
	scanf("%d",&m);m++;
	for(int i=1;i<m;i++)
		scanf("%d%d",&x[i],&y[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d",&op[i]);
		if(op[i]==1) scanf("%d",&p[i]),del[p[i]]=1;
	}
	s.insert(Point(0,0));s.insert(Point(n,0));len=n;
	for(int i=0;i<m;i++)
		if(!del[i]) Insert(Point(x[i],y[i]));
	for(int i=q;i>=1;i--){
		if(op[i]==2) ans[i]=len;
		else Insert(Point(x[p[i]],y[p[i]]));
	}
	for(int i=1;i<=q;i++)
		if(op[i]==2) printf("%.2lf\n",ans[i]);
	return 0;
}
