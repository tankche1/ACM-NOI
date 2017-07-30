#pragma comment( linker, "/STACK:1024000000,1024000000")
# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxm=500010;

//AC×Ô¶¯»ú
queue<int> Q;
struct ACmachine{
	int ch[maxm][2];
	int val[maxm];
	int num[maxm];
	int go[maxm][2];
	int sz;
	int f[maxm],last[maxm];

	void init() {val[0]=0;memset(ch[0],0,sizeof(ch[0]));memset(go[0],0,sizeof(go[0]));num[0]=0;sz=0;}

	bool search(char *s){
	    int n=strlen(s),u=0;
	    for(int i=0;i<n;i++){
			int c=s[i]-'0';
			if(!ch[u][c]) return false;
			u=ch[u][c];
		}
		return val[u]==1;
	}

	void insert(char *s){
		int n=strlen(s),u=0;
		for(int i=0;i<n;i++){
			int c=s[i]-'0';
			if(!ch[u][c]){
				ch[u][c]=++sz;memset(ch[sz],0,sizeof(ch[sz]));val[sz]=0;num[sz]=0;memset(go[sz],0,sizeof(go[sz]));
			}
			u=ch[u][c];
		}
		//printf("u:%d\n",u);
		val[u]=1;
	}

	long long find(char *s){
	    int n=strlen(s),u=0;
	    long long res=0;
	    for(int i=0;i<n;i++){
            int c=s[i]-'0';
            u=go[u][c];
            res+=num[u];
	    }
	    return res;
	}

	void get_Fail(){

	    for(int i=0;i<=sz;i++) go[i][0]=ch[i][0],go[i][1]=ch[i][1],num[i]=val[i];
	    f[0]=0;
		for(int c=0;c<2;c++)
			if(go[0][c]){
				f[go[0][c]]=0;Q.push(go[0][c]);
			}
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int c=0;c<2;c++){
				int u=go[x][c];
				if(!u) {go[x][c]=go[f[x]][c];continue;}
				Q.push(u);
				int r=f[x];
				//while(r&&!go[r][c]) r=f[r];
				f[u]=go[r][c];
				num[u]=num[u]+num[f[u]];
				//printf("f[%d]:%d num:%d val:%d\n",u,f[u],num[u],val[u]);
			}
		}
	}
}big,small;

int block=2000;
char s1[maxm*10],s[maxm*10];

void dfs(int a,int b){
    big.val[a]|=small.val[b];
    for(int c=0;c<2;c++){
        if(small.ch[b][c]==0) continue;
        if(!big.ch[a][c]){
            big.ch[a][c]=++big.sz;memset(big.ch[big.sz],0,sizeof(big.ch[big.sz]));big.val[big.sz]=0;
        }
        dfs(big.ch[a][c],small.ch[b][c]);
    }
}

void Union(){
    dfs(0,0);small.init();big.get_Fail();
}

int main(){
    int Case,n;
    long long k;
    int len;
    char op;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        big.init();small.init();
        printf("Case #%d:\n",Tcase);
        k=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            while((op=getchar())&&op!='?'&&op!='+');
            scanf("%s",s1);len=strlen(s1);
            for(int i=0;i<len;i++) s[i]=s1[(i+(k%len))%len];s[len]='\0';
            //printf("s:");puts(s);
            if(op=='+'){
                if(small.search(s)||big.search(s)) continue;
                small.insert(s);small.get_Fail();
                if(small.sz>block){
                    Union();
                }
            }
            else{
                k=small.find(s)+big.find(s);
                printf("%I64d\n",k);//k%=len;
            }
        }
    }
    return 0;
}
