# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int n;
char a[10][10];
int ans[10][10];

int row[6][6],line[6][6];

bool check(int x,int y){
    if(a[x][0]>='0'&&a[x][0]<='9'){
        int cnt=0,_max=0;
        for(int j=1;j<=y;j++){
            if(ans[x][j]>_max) _max=ans[x][j],cnt++;
        }
        if(y==n&&cnt!=a[x][0]-'0') return false;
        if(y<n&&cnt>a[x][0]-'0') return false;
    }

    if(a[x][n+1]>='0'&&a[x][n+1]<='9'&&y==n){
        int cnt=0,_max=0;
        for(int j=y;j>=1;j--){
            if(ans[x][j]>_max) _max=ans[x][j],cnt++;
        }
        if(y==n&&cnt!=a[x][n+1]-'0') return false;
    }

    if(a[0][y]>='0'&&a[0][y]<='9'){
        int cnt=0,_max=0;
        for(int i=1;i<=x;i++){
            if(ans[i][y]>_max) _max=ans[i][y],cnt++;
        }
        if(x==n&&cnt!=a[0][y]-'0') return false;
        if(x<n&&cnt>a[0][y]-'0') return false;
    }

    if(a[n+1][y]>='0'&&a[n+1][y]<='9'&&x==n){
        int cnt=0,_max=0;
        for(int i=x;i>=1;i--){
            if(ans[i][y]>_max) _max=ans[i][y],cnt++;
        }
        if(x==n&&cnt!=a[n+1][y]-'0') return false;
    }

    return true;
}

bool dfs(int x,int y){
    if(y>n) x++,y=1;

    if(x>n){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                printf("%d",ans[i][j]);
            }puts("");
        }
        return true;
    }

    if(a[x][y]>='0'&&a[x][y]<='9'){
        ans[x][y]=a[x][y]-'0';//row[x][ans[x][y]]=1;line[y][ans[x][y]]=1;
        if(!check(x,y)) return false;
        if(dfs(x,y+1)) return true;
        //row[x][ans[x][y]]=0;line[y][ans[x][y]]=0;
        return false;
    }
    else{
        for(int i=1;i<=n;i++){
            if(row[x][i]==0&&line[y][i]==0){
                ans[x][y]=i;
                row[x][ans[x][y]]=1;line[y][ans[x][y]]=1;
                if(check(x,y)){
                    if(dfs(x,y+1)) return true;
                }
                row[x][ans[x][y]]=0;line[y][ans[x][y]]=0;
            }
        }
    }
    return false;
}

int main(){
    int T;
    char t;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=0;i<=n+1;i++){
            for(int j=0;j<=n+1;j++){
                while((t=getchar())&&t!='-'&&(t>'9'||t<'0'));
                a[i][j]=t;
            }
        }

        memset(row,0,sizeof(row));memset(line,0,sizeof(line));

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(a[i][j]>='0'&&a[i][j]<='9'){
                    row[i][a[i][j]-'0']=1;line[j][a[i][j]-'0']=1;
                }
            }
        }
       if(!dfs(1,1)) puts("no");
       puts("");
    }
    return 0;
}
