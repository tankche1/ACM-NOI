# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;

char s[5][5];
bool row[5][5],line[5][5],block[5][5];
int a[5][5];

inline int belong(int x,int y){
    if(x<=2&&y<=2) return 1;
    else if(x<=2) return 2;
    else if(y<=2) return 3;
    else return 4;
}

bool dfs(int x,int y){
    if(y>4) x++,y=1;
    if(x>4){
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++) printf("%d",a[i][j]);puts("");
        }
        return true;
    }
    if(s[x][y]!='*')  return dfs(x,y+1);

    for(int k=1;k<=4;k++){
        if(row[x][k]||line[y][k]||block[belong(x,y)][k]) continue;
        a[x][y]=k;
        row[x][k]=1;line[y][k]=1;block[belong(x,y)][k]=1;
        if(dfs(x,y+1)) return true;
        row[x][k]=0;line[y][k]=0;block[belong(x,y)][k]=0;
    }

    return false;
}

int main(){
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        for(int i=1;i<=4;i++) scanf("%s",s[i]+1);
        memset(row,0,sizeof(row));
        memset(line,0,sizeof(line));
        memset(block,0,sizeof(block));
        printf("Case #%d:\n",Tcase);
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                if(s[i][j]!='*'){
                    row[i][s[i][j]-'0']=1;
                    line[j][s[i][j]-'0']=1;
                    block[belong(i,j)][s[i][j]-'0']=1;
                    a[i][j]=s[i][j]-'0';
                }
            }
        }

        dfs(1,1);
    }
    return 0;
}
