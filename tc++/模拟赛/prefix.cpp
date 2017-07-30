# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxs=27;
int ans=0;

struct Trie{
	int ch[maxn*maxn][maxs];
	int num[maxn*maxn];
	int sz;
	
	void init(){
		memset(ch[0],0,sizeof(ch[0]));
		memset(num,0,sizeof(num));
		sz=0;
	}
	
	int id(char c) {return c-'a';}
	
	void insert(char *s){
		int n=strlen(s);
		int u=0;
		for(int i=0;i<n;i++){
			int c=id(s[i]);
			if(!ch[u][c]){
				ch[u][c]=++sz;
				memset(ch[sz],0,sizeof(ch[sz]));
			}
			u=ch[u][c];
			num[u]++;
		}
	}
	
	void query(char *s){
		int n=strlen(s);
		int u=0;
		for(int i=0;i<n;i++){
			int c=id(s[i]);
			u=ch[u][c];
			if(num[u]==1) {
				for(int j=0;j<=i;j++) printf("%c",s[j]);printf("\n");
				return;}
		}
	}
};
Trie trie;

int n;
char s[maxn][maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]);
		trie.insert(s[i]);
	}
	for(int i=1;i<=n;i++){
		trie.query(s[i]);
	}
	//printf("%d\n",ans);
	return 0;
}
