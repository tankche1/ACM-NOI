#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxnode=300010;
vector<int> p[maxn];

int n;
char s[maxn][300];

struct Trie{
	int word[maxn];
	int ch[maxnode][26];
	int sz;
	void init(){
		sz=0;
		memset(ch[0],0,sizeof(ch[0]));memset(word,0,sizeof(word));
	}
	
	void insert(char *s,int bh){
		int n=strlen(s);
		int u=0;
		for(int i=n-1;i>=0;i--){
			int c=s[i]-'a';
			if(!ch[u][c]){
				ch[u][c]=++sz;memset(ch[sz],0,sizeof(ch[sz]));
			}
			u=ch[u][c];
		}
		word[u]=bh;
	}
	
	void get_p(char *s,int bh){
		int n=strlen(s);
		int u=0;
		for(int i=n-1;i>=0;i--){
			int c=s[i]-'a';
			u=ch[u][c];
			if(word[u])
				p[word[u]].push_back(bh);
		}
	}
}trie;

int main(){
	int k;
	scanf("%d",&n);
	trie.init();
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]),trie.insert(s[i],i);
	for(int i=1;i<=n;i++)
		trie.get_p(s[i],i);
	for(int i=1;i<=n;i++){
		scanf("%d",&k);
		if(k>p[i].size()) puts("-1");
			else printf("%d\n",p[i][k-1]);
	}
	return 0;
}
