# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2510;
typedef pair<int,int> pi;
pi cow[maxn],bottle[maxn];
int n,m;
bool used[maxn];

bool cmp1(pi a,pi b){
	return a.second<b.second;
}

bool cmp2(pi a,pi b){
	return a.first<b.first;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&cow[i].first,&cow[i].second);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&bottle[i].first,&bottle[i].second);
	sort(cow+1,cow+n+1,cmp1);
	sort(bottle+1,bottle+m+1,cmp2);
	memset(used,false,sizeof(used));
	int ans=0;
	//for(int i=1;i<=n;i++) printf("%d %d\n",cow[i].first,cow[i].second);
	//	for(int i=1;i<=m;i++) 	printf("%d %d\n",bottle[i].first,bottle[i].second);
	for(int i=1;i<=m;i++){
	//	printf("%d %d\n",bottle[i].first,bottle[i].second);
		for(int j=1;j<=n;j++){
			//printf("%d %d\n",cow[i].first,cow[i].second);
			//printf("i:%d j:%d %d %d %d\n",i,j,cow[j].first,cow[j].second,bottle[i].first);
			if((!used[j])&&cow[j].first<=bottle[i].first&&cow[j].second>=bottle[i].first){
				used[j]=1;ans++;
				//printf("i:%d j:%d\n",i,j);
				if(--bottle[i].second==0) break;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
