# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
char name[maxn][maxn];
char t[20];
int a[maxn][500];
int val[maxn][10];
int n;
int len,tt;
int bh[maxn];
int tmp=0;
int type(char c){
    if(c=='u') return 2;
    else if(c=='m') return 1;
    else return 0;
}

bool cmp(int a,int b){
    for(int i=0;i<10;i++){
        if(val[a][i]<val[b][i]) return 1;
        else if(val[a][i]>val[b][i]) return 0;
    }
    return strcmp(name[a],name[b])>0;
}

int main(){
    scanf("%d\n",&n);
    len=0;
    for(int i=1;i<=n;i++){
        scanf("%s",name[i]);
        tt=strlen(name[i]);name[i][tt-1]='\0';
        scanf("%s",t);
        while(t[0]!='c'){
            a[i][++a[i][0]]=type(t[0]);
            //printf("i:%d j:%d %d\n",i,a[i][0],a[i][a[i][0]]);
            scanf("%s",t);
        }
        if(a[i][0]>len) len=a[i][0];
    }
    memset(val,0,sizeof(val));
    int now,tmp;

    for(int i=1;i<=n;i++){
        for(int j=1;j<a[i][0]+1-j;j++){
            swap(a[i][j],a[i][a[i][0]+1-j]);
        }
        for(int j=a[i][0]+1;j<=len;j++){
            a[i][j]=1;
        }tmp=0;
        /*printf("i:%d \n",i);
        for(int j=1;j<=len;j++)
            printf("j:%d %d\n",j,a[i][j]);*/
        now=9;
        for(int j=len;j>=1;j--,now--){
            tmp=0;
            for(int k=max(j-9,1);k<=j;k++){
                tmp=tmp*3+a[i][k];
            }
            j=j-9;
            //printf("i:%d tmp:%d\n",i,tmp);
            val[i][now]=tmp;
        }
    }

    for(int i=1;i<=n;i++) bh[i]=i;
    sort(bh+1,bh+n+1,cmp);
    for(int i=n;i>=1;i--){
        puts(name[bh[i]]);
    }
    return 0;
}
