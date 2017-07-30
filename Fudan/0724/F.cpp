# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
char want[10];
char a[5][5];
bool dfsboy(int cur);

bool win(){
    for(int i=1;i<=4;i++)
        if(a[i][1]!='.'&&a[i][1]==a[i][2]&&a[i][2]==a[i][3]&&a[i][3]==a[i][4]) return true;
    for(int j=1;j<=4;j++)
        if(a[1][j]!='.'&&a[1][j]==a[2][j]&&a[2][j]==a[3][j]&&a[3][j]==a[4][j]) return true;
    if(a[1][1]!='.'&&a[1][1]==a[2][2]&&a[2][2]==a[3][3]&&a[3][3]==a[4][4]) return true;
    if(a[4][1]!='.'&&a[4][1]==a[3][2]&&a[3][2]==a[2][3]&&a[2][3]==a[1][4]) return true;
    return false;
}

bool dfsgirl(int cur){
    if(win()) return want[0]=='W';
    if(cur>16) return want[0]=='T';
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++){
            if(a[i][j]!='.') continue;
            a[i][j]='o';
            if(!dfsboy(cur+1)) {a[i][j]='.';return false;}
            a[i][j]='.';
        }
    return true;
}

bool dfsboy(int cur){
    if(win()) return want[0]=='L';
    if(cur>16) return want[0]=='T';
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(a[i][j]!='.') continue;
            a[i][j]='x';
            if(dfsgirl(cur+1)) {a[i][j]='.';return true;}
            a[i][j]='.';
        }
    }
    return false;
}
int main(){
    char t;
    int tcase;
    bool can;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%s",&want);
        int cur=0,xnum=0,onum=0;
        for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++){
            while((t=getchar())&&t!='.'&&t!='x'&&t!='o');
            a[i][j]=t;
            cur+=(t!='.');
            xnum+=t=='x';onum+=t=='o';
        }
        if(xnum>onum){
            for(int i=1;i<=4;i++)
                for(int j=1;j<=4;j++){
                    if(a[i][j]=='o') a[i][j]='x';
                    else if(a[i][j]=='x') a[i][j]='o';
                }
        }
        can=dfsboy(cur+1);
        if(can) puts("YES");
        else puts("NO");
    }
    return 0;
}
