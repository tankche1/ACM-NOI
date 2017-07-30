# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxm=1010;

int encode(char c){
    if(c=='A') return 0;
    else if(c=='C') return 1;
    else if(c=='G') return 2;
    return 3;
}

//AC×Ô¶¯»ú
struct ACmachine{
	int ch[maxm][4];
	int val[maxm];
	int sz;
	int f[maxm],last[maxm];
	queue<int> Q;

	void init() {val[0]=0;memset(ch[0],0,sizeof(ch[0]));sz=0;}
	void insert(char *s){
		int n=strlen(s),u=0;
		for(int i=0;i<n;i++){
			int c=encode(s[i]);
			if(!ch[u][c]){
				ch[u][c]=++sz;memset(ch[sz],0,sizeof(ch[sz]));val[sz]=0;
			}
			u=ch[u][c];
		}
		//printf("u:%d\n",u);
		val[u]=1;
	}

	void get_Fail(){f[0]=0;
		for(int c=0;c<4;c++)
			if(ch[0][c]){
				f[ch[0][c]]=0;Q.push(ch[0][c]);
			}
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int c=0;c<4;c++){
				int u=ch[x][c];
				if(!u) {ch[x][c]=ch[f[x]][c];continue;}
				Q.push(u);
				int r=f[x];
				while(r&&!ch[r][c]) r=f[r];
				f[u]=ch[r][c];
				val[u]=val[u]|val[f[u]];
				//printf("f[%d]:%d\n",u,f[u]);
			}
		}
	}
}ac;

int n;
char s[50];
char p[1010];
int f[1010][1010];

int main(){
    int Tcase=0;
    while(scanf("%d",&n)!=EOF){
        Tcase++;
        if(!n) break;
        ac.init();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            ac.insert(s);
        }
        ac.get_Fail();

        scanf("%s",p);
        int m=strlen(p);
        memset(f,-1,sizeof(f));
        f[0][0]=0;

        for(int i=0;i<=m;i++){
            for(int j=0;j<=ac.sz;j++){
                if(f[i][j]!=-1){
                    //printf("f[%d][%d]:%d\n",i,j,f[i][j]);
                    if(i==m) continue;
                    for(int k=0;k<4;k++){
                        if(ac.val[ac.ch[j][k]]) continue;
                        if(f[i+1][ac.ch[j][k]]==-1) f[i+1][ac.ch[j][k]]=f[i][j]+(encode(p[i])!=k);
                        else f[i+1][ac.ch[j][k]]=min(f[i+1][ac.ch[j][k]],f[i][j]+(encode(p[i])!=k));
                    }
                }
            }
        }

        int ans=10000;
        for(int j=0;j<=ac.sz;j++)
            if(f[m][j]!=-1) ans=min(ans,f[m][j]);
        printf("Case %d: ",Tcase);
        if(ans==10000) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
