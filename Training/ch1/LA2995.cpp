# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=12;
char view[6][maxn][maxn];
int n;
char block[maxn][maxn][maxn];

void get(int k,int i,int j,int len,int &x,int &y,int &z){
    if(k==0) z=i,y=j,x=n-1-len;
    if(k==1) z=i,x=j,y=len;
    if(k==2) z=i,y=n-1-j,x=len;
    if(k==3) z=i,x=n-1-j,y=n-1-len;
    if(k==4) x=i,y=j,z=len;
    if(k==5) x=n-1-i,y=j,z=n-1-len;
}

int main(){
    char t;
    int x,y,z;
while(scanf("%d",&n)!=EOF){
    if(!n) break;
    for(int i=0;i<n;i++){
        for(int k=0;k<6;k++){
            for(int j=0;j<n;j++){
                while((t=getchar())&&t!='.'&&(t<'A'||t>'Z'));
                view[k][i][j]=t;
            }
        }
    }
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) block[i][j][k]='#';

    for(int k=0;k<6;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(view[k][i][j]=='.'){
                    for(int p=0;p<n;p++){
                        get(k,i,j,p,x,y,z);
                        block[x][y][z]='.';
                    }
                }
            }
        }
    }

    while(1){
        Loop:
        for(int k=0;k<6;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    for(int p=0;p<n;p++){
                        get(k,i,j,p,x,y,z);
                        if(block[x][y][z]=='.') continue;
                        if(block[x][y][z]=='#'){
                            block[x][y][z]=view[k][i][j];
                            break;
                        }
                        if(block[x][y][z]!=view[k][i][j]){
                            block[x][y][z]='.';goto Loop;
                        }
                        break;
                    }
                }
            }
        }
        break;
    }
    int ans=0;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) for(int k=0;k<n;k++) if(block[i][j][k]!='.') ans++;
    printf("Maximum weight: %d gram(s)\n",ans);
}
    return 0;
}
