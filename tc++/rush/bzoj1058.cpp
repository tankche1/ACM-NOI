//http://blog.csdn.net/sdj222555/article/details/8241355
# include<stdio.h>
# include<string.h>
# include<map>
# include<vector>
# include<set>
# include<algorithm>
using namespace std;
const int maxn=500010;
const int INF=~0U>>1;
set<int> all_num,all_mule;
map<int,int> mule_cnt;
vector<int> orign[maxn];
int n,m,a[maxn];
int ans_sort=INF;
char op[20];

void map_add(int x){
	if(!mule_cnt.count(x))
	{mule_cnt[x]=1;all_mule.insert(x);}
	else mule_cnt[x]++;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		orign[i].push_back(a[i]);
		all_num.insert(a[i]);
	}
	orign[n+1].push_back(-INF);
	for(int i=2;i<=n;i++)
	map_add(abs(orign[i][0]-orign[i-1][0]));
	sort(a+1,a+n+1);
	for(int i=2;i<=n;i++) 
		ans_sort=min(ans_sort,a[i]-a[i-1]);
	int pos,val;
	while(m--){
		/*for(set<int>::iterator it=all_num.begin();it!=all_num.end();it++)
			printf("%d ",*it);
		printf("\n");
		for(set<int>::iterator it=all_mule.begin();it!=all_mule.end();it++)
			printf("%d ",*it);
		printf("\n");*/
		scanf("%s",op);
		if(op[0]=='I'){
			scanf("%d%d",&pos,&val);
			if(ans_sort){
				set<int>::iterator it=all_num.lower_bound(val);
				if(it!=all_num.end())
					ans_sort=min(ans_sort,*it-val);
				it--;
				if(it!=all_num.begin())
					ans_sort=min(ans_sort,val-*it);
			}
			all_num.insert(val);
			int mule=abs(orign[pos+1][0]-orign[pos][orign[pos].size()-1]);
			if(--mule_cnt[mule]==0){
				all_mule.erase(mule);
				mule_cnt.erase(mule);
			}
			map_add(abs(orign[pos+1][0]-val));
			map_add(abs(val-orign[pos][orign[pos].size()-1]));
			orign[pos].push_back(val);
		}
		else if(op[4]=='G') printf("%d\n",*all_mule.begin());
		else printf("%d\n",ans_sort);
	}
	return 0;
}
