# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
double x;
struct people{
    double h;int bh;
}p[6010];
bool cmp(people a,people b){
    return a.h<b.h;
}
int n;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf",&x);
        //printf("%.7lf\n",x);
        p[i].h=(x*1000);
        //printf("%.2lf %d\n",p[i].h);
        p[i].h-=2000;
        p[i].bh=i;
    }
    sort(p+1,p+n+1,cmp);
    //for(int i=1;i<=n;i++)
       // printf("%d\n",p[i].h);
    puts("yes");
    double sum=0;int l=1,r=n;
    while(l<=r){
        if(sum>0){
            sum+=p[l].h;
            if(l>1||r<n) printf(" ");
            printf("%d",p[l].bh);;
            l++;
        }
        else{
            sum+=p[r].h;
            if(l>1||r<n) printf(" ");
            printf("%d",p[r].bh);
            r--;
        }
    }

    puts("");
    return 0;
}
