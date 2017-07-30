# include<stdio.h>
# include<string.h>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=4010;
int n,k;

struct bell{
	int mass,cost;
}b[maxn];

struct tank{
	int mass,num;
	tank() {}
	tank(int mass,int num):mass(mass),num(num) {}
}t[maxn];int t_cnt=0;
bool operator < (const tank a,const tank b){
	return a.num>b.num;
}
int num[maxn];
int c[maxn];
multiset<int> s[maxn];
int d[maxn],d_cnt=0;
multiset<int>::iterator it;

int main(){
	scanf("%d%d",&n,&k);

	memset(num,0,sizeof(num));
	memset(c,0,sizeof(c));
	for(int i=1;i<=4000;i++) s[i].clear();
	for(int i=1;i<=n;i++){
		scanf("%d%d",&b[i].mass,&b[i].cost);
		num[b[i].mass]++;
	}
	int col=0;
	for(int i=4000;i>=1;i--)
		if(num[i]) t[++t_cnt]=tank(i,num[i]),col++;
	if(col<k) {printf("0 0\n");return 0;}
	
	sort(t+1,t+t_cnt+1);//从大到小排序
	int maxnum=t[k].num,ed;
	for(ed=k+1;ed<=t_cnt;ed++)
		if(t[ed].num!=maxnum) break;
	ed--;
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++){
		s[b[i].mass].insert(b[i].cost);
		c[b[i].mass]+=b[i].cost;num[b[i].mass]++;
		if(num[b[i].mass]>maxnum) {
			c[b[i].mass]-=*s[b[i].mass].begin();
			s[b[i].mass].erase(s[b[i].mass].begin());
		}
	}
	
	for(int i=1;i<=ed;i++){
		d[++d_cnt]=c[t[i].mass];
		//printf("t:%d c:%d\n",t[i].mass,c[t[i].mass]);
	}
	sort(d+1,d+d_cnt+1);
	int ans=0;
	for(int i=d_cnt;i>=d_cnt-k+1;i--)
		ans+=d[i];
	printf("%d %d\n",maxnum,ans);
	return 0;
}
