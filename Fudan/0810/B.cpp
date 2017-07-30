# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int len[13]={0,4,3,3,2,2,2,1,1,1,1};
int a[15][15];
char s[15][15];

bool check(int x,int y){
    if(s[x][y]=='#')  return 0;
    if(x>1&&s[x-1][y]=='#') return 0;
    if(x<10&&s[x+1][y]=='#') return 0;
    if(y>1&&s[x][y-1]=='#') return 0;
    if(y<10&&s[x][y+1]=='#') return 0;
    return 1;
}

void place(int l){
    //printf("l:%d\n",l);
    bool ok;
    for(int i=1;i<=10;i++)
    for(int j=1;j+l-1<=10;j++){
        ok=true;
        for(int k=j;k<=j+l-1;k++){
            if(!check(i,k)) ok=false;
        }
        if(ok){
            for(int k=j;k<=j+l-1;k++){
            s[i][k]='#';
            }
            return;
        }
    }
    return;
}

int main(){
    freopen("battleship.in","r",stdin);
    freopen("battleship.out","w",stdout);
    int x,y;
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++){
                s[i][j]='.';
            scanf("%d",&a[i][j]);
            if(a[i][j]==100) x=i,y=j;
        }
    s[x][y]='#';
    for(int i=1;i<=9;i++)
        place(len[i]);
    for(int i=1;i<=10;i++){
    for(int j=1;j<=10;j++){
        printf("%c",s[i][j]);
    }puts("");
    }
    return 0;
}
