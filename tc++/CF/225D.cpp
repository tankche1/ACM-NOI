#include<stdio.h>
#include<string.h>
# include<map>
#include<algorithm>
using namespace std;
const int maxm=200010;
int n,m;
struct Date{
	int x,y;
	bool operator == (const Date &rhs)const{
		return x==rhs.x&&y==rhs.y;
	}
};
Date block[maxm];
Date now[maxm];
Date next[maxm];
int next_cnt=0;
int cnt=0;
bool cmp(Date A,Date B){
	if(A.x!=B.x)
	return A.x<B.x;
	return A.y<B.y;
}
int main(){
	scanf("%d%d",&n,&m);
	int tt=0;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&block[i].x,&block[i].y),block[m+(++tt)].x=block[i].x,block[m+tt].y=n+1;
	m+=tt;
	block[0].x=0;
	++m;block[m].x=n;block[m].y=n+1;
	sort(block+1,block+m+1,cmp);
	m=unique(block+1,block+m+1)-(block+1);
	next_cnt=1;next[next_cnt].x=1;next[next_cnt].y=1;
	for(int i=1;i<=m;i++){
		cnt=next_cnt;for(int j=1;j<=cnt;j++) now[j]=next[j];
		if(cnt==0) break;
		if(block[i-1].x<block[i].x-1) now[cnt=1].y=n;
		int last=now[1].x,j,pos=1;next_cnt=0;
		//printf("x:%d \n",block[i].x);
		//for(int j=1;j<=cnt;j++) printf("[%d,%d] ",now[j].x,now[j].y);puts("");
		for(j=i;block[j].x==block[i].x;j++){
			if(last==-1) continue;
			if(last>block[j].y) continue;
			if(block[j].y-1>=last) {next_cnt++;next[next_cnt].x=last;next[next_cnt].y=block[j].y-1;}
			while(pos<=cnt&&now[pos].y<block[j].y+1) pos++;
			if(pos>cnt) {last=-1;continue;}
			if(now[pos].x>block[j].y+1) last=now[pos].x;else last=block[j].y+1;
		}
		i=j-1;
	}
	next[0].y=-1;//printf("%d\n",next_cnt);
	if(next[next_cnt].y==n) printf("%d\n",2*n-2);
	else puts("-1");
	return 0;
}
