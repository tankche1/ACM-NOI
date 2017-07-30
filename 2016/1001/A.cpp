# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
int a[2][4];
int b[4];

bool equal(){
    for(int j=0;j<4;j++) if(b[j]!=a[1][j]) return false;
    return true;
}

void Rotate(){
    int t=b[0];
    b[0]=b[2];b[2]=b[3];b[3]=b[1];b[1]=t;
}

int main(){
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        for(int i=0;i<2;i++){
            for(int j=0;j<4;j++){
                scanf("%d",&a[i][j]);
                if(i==0) b[j]=a[i][j];
            }
        }

        bool ok=false;
        printf("Case #%d: ",Tcase);
        if(equal()) puts("POSSIBLE");
        else{
            for(int j=0;j<4;j++){
                Rotate();
                if(equal()) ok=true;
            }
            if(ok) puts("POSSIBLE");
            else puts("IMPOSSIBLE");
        }
    }
    return 0;
}
