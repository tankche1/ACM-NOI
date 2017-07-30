# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
char s[30];
int cnt[30];
bool vis[30];
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		memset(cnt,0,sizeof(cnt));
		memset(vis,false,sizeof(vis));
		for(int i=0;i<26;i++){
			if(!vis[i]){
				int j=i,n=0;
				do{
					vis[j]=true;
					j=s[j]-'A';
					n++;
				}while(j!=i);
				cnt[n]++;
			}
		}
		bool ok=true;
		for(int i=2;i<=26;i+=2){
			if(cnt[i]%2){ok=false;break;
			}
		}
		if(ok) printf("Yes\n");
			else printf("No\n");
	}
	return 0;
}
