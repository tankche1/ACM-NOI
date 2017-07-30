# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxm=55;
const int maxn=1005;

int m,n;
int wood[maxm],need[maxn],len[maxn];
int wood_len,tot_len;

bool dfs(int bh,int last,int waste){
	//printf("bh:%d last:%d waste:%d num:%d\n",bh,last,waste,num);
	if(!bh) return true;
	if(wood_len-waste<tot_len) return false;
	for(int i=last;i<=m;i++){
		if(len[i]>=need[bh]){
			int ww=waste;
			len[i]-=need[bh];
			if(len[i]<need[1]) ww+=len[i];
			if(dfs(bh-1,need[bh]==need[bh-1]?i:1,ww)) return true;
			len[i]+=need[bh];
		}
	}
	return false;
}

bool can_solve(int num){
	memcpy(len,wood,sizeof(wood));
	tot_len=0;need[0]=-2;
	for(int i=1;i<=num;i++)
		tot_len+=need[i];
	//printf("M:%d\n",num);
	if(dfs(num,1,0)) return true;
	else return false;
}

int main(){
	wood_len=0;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&wood[i]);wood_len+=wood[i];
	}
	sort(wood,wood+m+1);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&need[i]);
	sort(need+1,need+n+1);
	int L=1,R=n,M;
	while(L<=R){
		M=(L+R)>>1;
		if(can_solve(M)) L=M+1;
			else R=M-1;
	}
	printf("%d\n",L-1);
	return 0;
}
