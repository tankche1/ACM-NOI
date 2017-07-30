# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=300010;
int cnt[maxn],num[maxn];
int first;
int n,q;
int unread=0;
int que[maxn],bh[maxn],tot=0;

int main(){
    int type,x;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&type,&x);
        if(type==1){
            que[++tot]=x;bh[tot]=++cnt[x];unread++;
        }
        else if(type==2){
            unread-=cnt[x]-num[x];num[x]=cnt[x];
        }
        else{
            for(int i=first+1;i<=x;i++){
                if(bh[i]>num[que[i]]) {num[que[i]]++;unread--;}
            }
            first=max(first,x);
        }

        printf("%d\n",unread);
    }


    return 0;
}
