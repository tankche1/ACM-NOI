# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=110;

struct Bit{
    int a[maxn],len;
    void init() {len=1;memset(a,0,sizeof(a));}

    void print(){
        for(int i=len;i>=1;i--) printf("%d",a[i]);puts("");
    }
};

vector<Bit> G[2];
//vector<Bit> P;

void divide(Bit A,Bit B){
    int tmp=0;
    //printf("A:");A.print();
    for(int i=A.len;i>=1;i--){
        B.a[i]=(A.a[i]+tmp)/2;
        tmp=(A.a[i]+tmp)&1;
        tmp=tmp*10;
    }
    B.len=A.len;
    while(B.len>1&&B.a[B.len]==0) B.len--;
    //printf("B:");B.print();
}

void copy(Bit A,Bit B){
    A.len=B.len;
    for(int i=1;i<=100;i++) A.a[i]=B.a[i];
}

int n;

int main(){
    scanf("%d",&n);n++;
    Bit zero,one,tmp,res,tank,haha;
    zero.init();one.init();one.a[1]=1;
    G[1].push_back(zero);G[1].push_back(one);

    int f[110];f[1]=2;
    for(int i=2;i<=5;i++){
        int now=i&1;int last=now^1;
        for(int j=0;j<(int)G[last].size();j++){
            tmp=G[last][j];haha=tmp;
            //tmp.print();
            res.init();
            for(int k=1;;k++){
                res.a[k]=tmp.a[1]&1;
                divide(tmp,tank);
                copy(tmp,tank);
                if(tmp.len==1&&tmp.a[1]==0){
                    res.len=k;break;
                }
                if(k==i) break;
            }

            bool ok=true;
            for(int k=1;k<=i;k++) if(res.a[k]!=haha.a[k]) {ok=false;break;}
            if(ok) G[now].push_back(haha);
        }

        for(int j=0;j<(int)G[last].size();j++){
            tmp=G[last][j];
            tmp.a[++tmp.len]=1;
            //tmp.print();
            copy(haha,tmp);
            res.init();

            for(int k=1;;k++){
                res.a[k]=tmp.a[1]&1;
                divide(tmp,tank);
                //puts("fuck");
                copy(tmp,tank);//puts("shit");
                //printf("tmp:");tmp.print();
                if(tmp.len==1&&tmp.a[1]==0){
                    res.len=k;break;
                }
                if(k==i) break;
            }

            bool ok=true;
            for(int k=1;k<=i;k++) if(res.a[k]!=haha.a[k]) {ok=false;break;}
            if(ok) G[now].push_back(haha);
        }

        f[i]=(int)G[now].size();
        printf("f[%d]:%d\n",i,f[i]);
        for(int k=0;k<f[i];k++){
            if(G[now][k].len<i) G[now][k].len++;
            G[now][k].print();
        }
    }

    return 0;
}
