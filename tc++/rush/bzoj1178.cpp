# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int mi=maxn*5;

struct Two{
	int first,second;
	Two(int f=0,int s=0) :first(f),second(s) {}
	Two u(int f,int s) {first=f;second=s;}
	bool operator <(const Two &rhs)const{
		if(first!=rhs.first) return first<rhs.first;
		return second<rhs.second;
	}
};

int n,maxj;
Two requires[maxn],After[maxn],Line[maxn];
int jump[maxn<<1][23];
int req[maxn<<1],req_cnt=0,Line_cnt;

int Place(int x){
	int L=0,R=req_cnt-1,M;
	while(L<=R){
		M=(L+R)>>1;
		if(req[M]==x) return M;
		else if(req[M]<x) L=M+1;
			else R=M-1;
	}
}

void Get_st(){
	int p=Line_cnt;
	//printf("Line_cnt:%d\n",Line_cnt);
	jump[req_cnt][0]=mi;
	//for(int i=1;i<=p;i++)
	//	printf("%d %d\n",Line[i].first,Line[i].second);
	//jump[req_cnt+1][0]=mi;
	for(int i=req_cnt-1;i>=0;i--){
		int pp=p;
		if(p>=1&&Line[p].first==i){
			jump[i][0]=Line[p].second+1;p--;}
		else jump[i][0]=jump[i+1][0];
			//printf("jump[%d][%d]:%d first:%d second:%d\n",i,0,jump[i][0],Line[pp].first,Line[pp].second);
	}
	bool contin;maxj=0;
	for(int j=1;;j++){
		contin=false;
		for(int i=0;i<=req_cnt;i++){
			if(jump[i][j-1]==mi) jump[i][j]=mi;
				else jump[i][j]=jump[jump[i][j-1]][j-1];
			if(jump[i][j]<mi) contin=true;
				//printf("jump[%d][%d]:%d\n",i,j,jump[i][j]);
		}
		if(!contin) {maxj=j-1;break;}
	}
}

int maxline(int s,int e){
	int ans=0;
	for(int j=maxj;j>=0;j--){
		if(jump[s][j]-1<=e) ans+=1<<j,s=jump[s][j];
	}
	return ans;
}

set<Two> Tree;
typedef set<Two> ::iterator ptr;

bool judge(int bh){
	//printf("%d %dbe\n",Tree.begin()->first,Tree.begin()->second);
	int l=requires[bh].first,r=requires[bh].second;
	//for(ptr tt=Tree.begin();tt!=Tree.end();tt++)
	//	printf("Tree%d %d\n",tt->first,tt->second);
	Two a(l,mi);
	ptr t1;t1=Tree.upper_bound(a);//printf("l:%d r:%d upper:%d %d big:%d \n",l,r,t1->first,t1->second,a<(*t1));
	//ptr t2=Tree.end();t2--;printf("big:%d\n",*t2<
	if(t1==Tree.begin()) return false;
		//printf("fu");
	t1--;
	//printf("tank%d %d\n",t1->first,t1->second);
	if(t1->second<r) return false;
	int ll=t1->first,rr=t1->second;
	//printf("bh:%d ll:%d rr:%d\n",bh,ll,rr);
	if(maxline(ll,l-1)+1+maxline(r+1,rr)==maxline(ll,rr)){
		Tree.erase(t1);
		if(ll<=l-1) {Two a(ll,l-1);Tree.insert(a);}
		if(r+1<=rr) {Two a(r+1,rr);Tree.insert(a);}
		return true;
	}
	else return false;
}

bool cmp(const Two &A,const Two &B){
	if(A.first!=B.first) return A.first<B.first;
		else return A.second>B.second;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&requires[i].first,&requires[i].second);
		req[req_cnt++]=requires[i].first;req[req_cnt++]=requires[i].second;
	}
	int p;
	sort(req,req+req_cnt);
	req_cnt=unique(req,req+req_cnt)-req;
	//printf("%d\n",req_cnt);
	//for(int i=0;i<req_cnt;i++) printf("%d ",req[i]);printf("\n");
	for(int i=1;i<=n;i++){
		requires[i].first=Place(requires[i].first);requires[i].second=Place(requires[i].second);
		After[i].u(requires[i].first,requires[i].second);
		//printf("fuck %d %d\n",After[i].first,After[i].second);
	}
	sort(After+1,After+n+1,cmp);Line_cnt=0;
	for(int i=1;i<=n;i++){
			while(Line_cnt>=1&&Line[Line_cnt].second>=After[i].second) Line_cnt--;
			Line[++Line_cnt]=After[i];p=i;
			//printf("Line:%d %d\n",Line[Line_cnt].first,Line[Line_cnt].second);
		//printf("After:%d %d\n",After[i].first,After[i].second);
	}
	Get_st();
	Two a(0,req_cnt);
	Tree.insert(a);
	printf("%d\n",maxline(0,req_cnt));//printf("%d %dbe\n",Tree.begin()->first,Tree.begin()->second);
	bool isfirst=true;
	for(int i=1;i<=n;i++)
		if(judge(i)) {//if(!isfirst) printf(" ");isfirst=false;
			printf("%d ",i);}
	printf("\n");
	return 0;
}
