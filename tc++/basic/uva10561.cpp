# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=210;
int g[maxn],n;
bool vis[maxn];

void init(){
	g[0]=0;
	g[1]=g[2]=g[3]=1;
	for(int i=4;i<=maxn-5;i++){
		memset(vis,false,sizeof(vis));
		vis[g[i-3]]=vis[g[i-4]]=true;
		if(i>=5) vis[g[i-5]]=true;
		for(int j=1;j+5<i;j++){
			vis[g[j]^g[i-j-5]]=true;
		}
		for(int j=0;;j++){
			if(!vis[j]) {g[i]=j;break;}
		}
	}
}

bool winning(const char *s){
	int n=strlen(s);
	for(int i=0;i<n;i++){
		if(s[i]=='X'&&s[i+1]=='X'&&s[i+2]=='X') return false;
	}
	for(int i=0;i<n;i++){
	//	printf("i:%d\n",i);
		if(s[i]=='X'){
		//	printf("i:%d\n",i);
			if(s[i+1]=='X'&&s[i+2]=='.') return true;
			else if(s[i+1]=='.'&&s[i+2]=='X') return true;
			else if((i>0)&&s[i-1]=='.'&&s[i+1]=='X') return true;
		}
	}
	int start=0,sg=0;
	for(int i=0;i<n;i++){
		if(s[i]=='X'){
			if(i-2>start){
				sg=sg^g[i-2-start];
			}
			start=i+3;
		}
	}
	if(n>start){
		sg=sg^g[n-start];
	}
	return sg!=0;
}

int main(){
	//freopen("in.txt","r",stdin);
	init();
	int T;
	vector<int> ans;
	char s[210];
	scanf("%d",&T);
	while(T--){
		ans.clear();
		scanf("%s",s);
		n=strlen(s);s[n+1]=s[n+2]=s[n+3]='\0';
		if(!winning(s)) {printf("LOSING\n\n");continue;}
		else{
			for(int i=0;i<n;i++)
				if(s[i]=='.'){
					s[i]='X';
					//if(i+1==6) printf("!:%s\n",s);
					if(!winning(s)) {//printf("haha:%s\n",s);
						ans.push_back(i+1);}
					s[i]='.';
				}
		}
		printf("WINNING\n");
		printf("%d",ans[0]);
		for(int i=1;i<ans.size();i++)
			printf(" %d",ans[i]);
		printf("\n");
	}
	return 0;
}
//..XX..XX..