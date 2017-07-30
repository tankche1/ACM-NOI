# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
int k;
bool can[20];
int main(){
    scanf("%d",&k);
    if(k==1) {printf("%d\n",8);return 0;}
    if(k==2) {printf("%d\n",1);return 0;}
    int ans=0;
    memset(can,false,sizeof(can));
    can[1]=1;
    can[2]=1;
    if((k-1+3)%3==0) can[3]=1;
    can[4]=0;
    can[5]=1;
    can[6]=can[3];
    can[7]=((k-1)%6==0);
    can[8]=0;
    can[9]=((k-1+9)%9==0);
    for(int i=1;i<=8;i++){
        if(can[i]&&can[i+1]) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
