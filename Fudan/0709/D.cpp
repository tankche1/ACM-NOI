# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10;
int N=100;
char s[10][110];
int posx[130]={0,1,2,2,2,2,3,3,4,4,4,4,5},posy[130]={0,5,2,4,6,8,3,7,2,4,6,8,5};
bool vis[130];

int A[60][60];
bool ok;
int tot=0,pos;
vector<int> C[130];

bool dfs(int cur){
	//printf("cur:%d\n",cur);
	if(cur==13) return true;
	if(s[posx[cur]][posy[cur]]!='x') return dfs(cur+1);
	for(int i=1;i<=12;i++){
		if(!vis[i]){
			s[posx[cur]][posy[cur]]='A'+i-1;vis[i]=1;
			ok=true;
			for(int j=0;j<(int)C[cur].size();j++){
				//printf("C:%d\n",C[cur][j]);
				tot=0;
				for(int k=1;k<=4;k++){
					pos=A[C[cur][j]][k];
					if(s[posx[pos]][posy[pos]]=='x') {tot-=100;break;}
					tot+=s[posx[pos]][posy[pos]]-'A'+1;
				}
				//printf("tot:%d\n",tot);
				if(tot>0&&tot!=26) {ok=false;break;}
			}
			if(ok){
				//printf("i:%d\n",i);
				if(dfs(cur+1)) return true;
			}
			s[posx[cur]][posy[cur]]='x';vis[i]=0;
		}
	}
	return false;
}
int main()
{
	A[1][1]=2;A[1][2]=3;A[1][3]=4;A[1][4]=5;
	A[2][1]=8;A[2][2]=9;A[2][3]=10;A[2][4]=11;
	A[3][1]=1;A[3][2]=3;A[3][3]=6;A[3][4]=8;
	A[4][1]=1;A[4][2]=4;A[4][3]=7;A[4][4]=11;
	A[5][1]=2;A[5][2]=6;A[5][3]=9;A[5][4]=12;
	A[6][1]=5;A[6][2]=7;A[6][3]=10;A[6][4]=12;
	for(int i=1;i<=6;i++)
		for(int j=1;j<=4;j++)
			C[A[i][j]].push_back(i);
	for(int i=1;i<=5;i++)
		scanf("%s",s[i]+1);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=12;i++)
		if(s[posx[i]][posy[i]]!='x') vis[s[posx[i]][posy[i]]-'A'+1]=1;
	
	dfs(1);
	for(int i=1;i<=5;i++){
		for(int j=1;j<=9;j++)
			printf("%c",s[i][j]);
		puts("");
	}
	return 0;
}
