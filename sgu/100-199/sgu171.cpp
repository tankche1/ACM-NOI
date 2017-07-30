# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=16000+10;
const int maxm=100+10;
struct tank{
    int val,bh,num;
    tank(){}
    bool operator < (const tank &rhs)const{
        return val<rhs.val;
    }
};
tank pupil[maxn],zone[maxm];
int k,n;
int ans[maxn];

bool cmp1(tank a,tank b){
    return a.val<b.val;
}

bool cmp2(tank a,tank b){
    return a.num>b.num;
}

int main(){
    scanf("%d",&k);
    n=0;
    for(int i=1;i<=k;i++){
        zone[i].bh=i;
        scanf("%d",&zone[i].num);
        n+=zone[i].num;
    }
    for(int i=1;i<=k;i++){
        scanf("%d",&zone[i].val);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&pupil[i].val);pupil[i].bh=i;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&pupil[i].num);
    }

    int t,small=1,big=k;
    sort(zone+1,zone+k+1);
    sort(pupil+1,pupil+n+1,cmp2);
    for(int i=1;i<=n;i++){
        t=lower_bound(zone+1,zone+k+1,pupil[i])-zone;t--;
        while(t>0&&zone[t].num==0) t--;
        if(t<small){
            ans[pupil[i].bh]=zone[big].bh;zone[big].num--;
        }
        else{
            ans[pupil[i].bh]=zone[t].bh;zone[t].num--;
        }
        while(zone[big].num==0&&big>0) big--;
        while(zone[small].num==0&&small<=n) small++;
    }
    for(int i=1;i<=n;i++){
        printf("%d",ans[i]);
        if(i<n) printf(" ");
    }
    puts("");
    return 0;
}
