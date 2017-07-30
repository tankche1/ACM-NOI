/*# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
typedef long long LL;
int s[15];
map<LL,bool> id;

LL get(){
    LL res=0;LL now=1;
    for(int i=1;i<=14;i++){
        res=res+s[i]*now;
        now*=i;
    }
    return res;
}

LL ans;
int n;

void dfs(){
    //for(int i=1;i<=14;i++)
    //    printf("%d ",s[i]);puts("");
    LL a=get();
    int pos;
    if(id.count(a)){
    //puts("fuck");
        return;
    }
    for(int i=1;i<=14;i++)
        if(s[i]==14) pos=i;

   // id[a]=1;
    for(int i=2;i<=14;i++){
        //    printf("i:%d\n",i);
        if(i<=13-n) continue;
        //printf("shiti:%d\n",i);
        if(s[i-1]+1==s[i]&&i!=pos){
                //printf("i:%d\n",i);
            swap(s[i],s[pos]);
            dfs();
            swap(s[i],s[pos]);
        }
    }

    ans++;
   // printf("pos:%d\n",pos);
    return;
}

int main(){
    for(n=1;n<=13;n++){
            n--;
    for(int i=1;i<=14;i++) s[i]=i;
   // s[14]=0;
   ans=0;id.clear();
    dfs();
    printf("%I64d\n",ans);
    n++;
    }
    return 0;
}*/
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int ans[14]={0,1,2,5,14,47,189,891,4815,29547,203173,1548222,12966093,118515434};
int n;
int main(){
    scanf("%d",&n);
    printf("%d\n",ans[n]);
    return 0;
}

