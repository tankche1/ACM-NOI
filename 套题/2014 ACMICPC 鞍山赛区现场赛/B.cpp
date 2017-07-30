# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int n;

struct QQ{
    int len,top;

    struct MM{
        int u;
        LL words;
        MM(int u=0,LL words=0):u(u),words(words) {}
    };
    MM mm[5010];

    void init() {
        len=0;top=0;
    }

    void Add(int u){
        for(int i=1;i<=len;i++){
            if(mm[i].u==u){
                puts("same priority.");return;
            }
        }
        puts("success.");
        mm[++len]=MM(u,0);
        return;
    }

    void Close(int u){
        for(int i=1;i<=len;i++){
            if(mm[i].u==u){
                printf("close %d with %I64d.\n",u,mm[i].words);
                for(int j=i;j<len;j++) mm[j]=mm[j+1];
                len--;return;
            }
        }
        puts("invalid priority.");
        return;
    }

    void Chat(int w){
        if(!len) {puts("empty.");return;}
        puts("success.");
        int d=1;
        for(int i=1;i<=len;i++){
            if(mm[i].u==top){
                d=i;break;
            }
        }
        mm[d].words+=w;
        return;
    }

    void Rotate(int x){
        if(len<x||x<1) {puts("out of range.");return;}
        mm[0]=mm[x];
        for(int i=x;i>=1;i--)
            mm[i]=mm[i-1];
        puts("success.");
        return;
    }

    void Prior(){
        if(!len) {puts("empty.");return;}
        int d=1;
        for(int i=2;i<=len;i++){
            if(mm[i].u>mm[d].u) d=i;
        }
        mm[0]=mm[d];
        for(int i=d;i>=1;i--)
            mm[i]=mm[i-1];
        puts("success.");
        return;
    }

    void Choose(int u){
        int d=-1;
        for(int i=1;i<=len;i++){
            if(mm[i].u==u) {d=i;break;}
        }
        if(d==-1) {puts("invalid priority.");return;}
        mm[0]=mm[d];
        for(int i=d;i>=1;i--)
            mm[i]=mm[i-1];
        puts("success.");
        return;
    }

    void Top(int u){
        int d=-1;
        for(int i=1;i<=len;i++){
            if(mm[i].u==u) {d=i;break;}
        }
        if(d==-1) {puts("invalid priority.");return;}
        top=u;
        puts("success.");
        return;
    }

    void Untop(){
        int d=-1;
        for(int i=1;i<=len;i++){
            if(mm[i].u==top) {d=i;break;}
        }
        if(d==-1) {puts("no such person.");return;}
        top=0;
        puts("success.");
        return;
    }

    void Bye(){
        for(int i=1;i<=len;i++){
            if(mm[i].u==top&&mm[i].words>0){
                printf("Bye %d: %I64d\n",mm[i].u,mm[i].words);break;
            }
        }
        for(int i=1;i<=len;i++){
            if(mm[i].words>0&&mm[i].u!=top){
                printf("Bye %d: %I64d\n",mm[i].u,mm[i].words);
            }
        }
        return;
    }

}qq;
int main(){
    //freopen("output.txt","w",stdout);
    char op[300];
    int T,u;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        qq.init();
        for(int i=1;i<=n;i++){
            scanf("%s",op);
            printf("Operation #%d: ", i);
            if(strcmp(op,"Add") == 0){
                scanf("%d",&u);
                qq.Add(u);
            }
            else if(strcmp(op,"Close")==0){
                scanf("%d",&u);
                qq.Close(u);
            }
            else if(strcmp(op,"Chat")==0){
                scanf("%d",&u);
                qq.Chat(u);
            }
            else if(strcmp(op,"Rotate")==0){
                scanf("%d",&u);
                qq.Rotate(u);
            }
            else if(strcmp(op,"Prior")==0){
                qq.Prior();
            }
            else if(strcmp(op,"Choose")==0){
                scanf("%d",&u);
                qq.Choose(u);
            }
            else if(strcmp(op,"Top")==0){
                scanf("%d",&u);
                qq.Top(u);
            }
            else if(strcmp(op,"Untop")==0){
                //scanf("%d",&u);
                qq.Untop();
            }
        }qq.Bye();
    }
    return 0;
}
