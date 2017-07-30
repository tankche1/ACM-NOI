# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210;
int nei[301],wai[301];
int n,m;
int g[maxn][maxn];

struct H{
    bool v[maxn];
    H(){v[0]=0;}
    H(int val){memset(v,val,sizeof(v));}
}h[110];
int h_cnt=0;

bool operator == (const H &a,const H &b)
{
        for(int i=1;i<=n;++i)
                if(a.v[i]!=b.v[i])
                        return 0;
        return 1;
}

H max(H b){
    static H a;
    for(int i=1;i<=n;i++) a.v[i]=b.v[i];
    for(int i=1;i<=n;i++){
        if(a.v[i]){
            for(int j=1;j<=n;j++)
                if(a.v[j]&&i!=j&&g[i][j])
                    {a.v[i]=0;break;}
        }
    }
    return a;
}

H Conjunction(H a,H b){
    static H c;
    for(int i=1;i<=n;i++)
        c.v[i]=a.v[i]|b.v[i];
    return max(c);
}

H Disjunction(H a,H b){
    static H c;
    int flag;
    for(int i=1;i<=n;i++){
        c.v[i]=0;flag=0;
        for(int j=1;j<=n;j++){
            if(g[i][j]&&a.v[j]) {flag++;break;}
        }
        for(int j=1;j<=n;j++)
             if(g[i][j]&&b.v[j]) {flag++;break;}
        if(flag==2) c.v[i]=1;
    }
    return max(c);
}

H Implication(H a,H b){
    static H c;
    for(int i=1;i<=n;i++){
        c.v[i]=0;
        if(b.v[i]){
            c.v[i]=1;
            for(int j=1;j<=n;j++)
                if(a.v[j]&&g[i][j]) {c.v[i]=0;break;}
        }
    }
    return c;
}

H Equivalence(H a,H b){
    static H c,d;
    c=Implication(a,b);d=Implication(b,a);
    return Conjunction(c,d);
}

H Nott(H a){
    return Implication(a,h[1]);
}

int con[110][110],disj[110][110],imp[110][110],equ[110][110],nott[110];

void dfsh(int x){
    static H B;
    if(x>n) {h[h_cnt++]=B;return;}
    dfsh(x+1);
    for(int i=1;i<x;i++)
        if(B.v[i]&&(g[i][x]||g[x][i]))
            return;
    B.v[x]=1;
    dfsh(x+1);
    B.v[x]=0;
    return;
}

void prepare(){
    dfsh(1);
    swap(h[1],*find(h+1,h+h_cnt,max(H(1))));
    for(int i=0;i<h_cnt;i++){
        for(int j=0;j<h_cnt;j++){
            con[i][j]=find(h,h+h_cnt,Conjunction(h[i],h[j]))-h;
            disj[i][j]=find(h,h+h_cnt,Disjunction(h[i],h[j]))-h;
            imp[i][j]=find(h,h+h_cnt,Implication(h[i],h[j]))-h;
            equ[i][j]=find(h,h+h_cnt,Equivalence(h[i],h[j]))-h;
        }
        nott[i]=find(h,h+h_cnt,Nott(h[i]))-h;
            //printf("i:%d j:%d con:%d disj:%d imp:%d\n",i,j,con[i][j],disj[i][j],imp[i][j]);
            //nott[i][j]=find(h,h+h_cnt,Nott(h[i],h[j]))-h;
    }
}

char s[500];
int numtr[500],num_top,op_top,e[30];
char optr[500];
void init(){num_top=op_top=-1;}

void pop(){
   // printf("%d %c %d ",numtr[num_top-1],optr[op_top],numtr[num_top]);
    int c,res;
    if(optr[op_top]=='~') numtr[num_top]=nott[numtr[num_top]],op_top--;
    else if(optr[op_top]=='='){
        for(c=1;optr[op_top-c]=='=';c++);
        op_top-=c;//printf("c:%d\n",c);
        res=equ[numtr[num_top-c]][numtr[num_top-c+1]];
        for(int i=num_top-c+2;i<=num_top;i++){
            res=con[res][equ[numtr[i-1]][numtr[i]]];
        }
        num_top-=c;numtr[num_top]=res;
    }
    else if(optr[op_top]=='&'){
        numtr[num_top-1]=con[numtr[num_top-1]][numtr[num_top]];op_top--;num_top--;
    }
    else if(optr[op_top]=='|'){
        numtr[num_top-1]=disj[numtr[num_top-1]][numtr[num_top]];op_top--;num_top--;
    }
    else if(optr[op_top]=='>'){
        numtr[num_top-1]=imp[numtr[num_top-1]][numtr[num_top]];op_top--;num_top--;
    }
    //printf(" = %d\n",numtr[num_top]);
}

bool check(){
    init();optr[++op_top]='#';
    //for(int i=0;i<5;i++)
    //    printf("%c : %d\n",i+'A',e[i]);
     //   int ttt;scanf("%d",&ttt);
    int len=strlen(s),pos=0;
    while(pos<len){
        if(s[pos]=='1'||s[pos]=='0'){
            numtr[++num_top]=!(s[pos]-'0');pos++;
        }
        else if(s[pos]>='A'&&s[pos]<='Z'){
            numtr[++num_top]=e[s[pos]-'A'];pos++;
        }
        else{
            if(nei[optr[op_top]]==wai[s[pos]]) op_top--,pos++;
            else if(nei[optr[op_top]]<wai[s[pos]]) optr[++op_top]=s[pos],pos++;
            else{
                pop();
            }
        }
    }
    //printf("result:%d\n",numtr[num_top]);
    return numtr[num_top]==0;
}

bool dfs(int u){
    for(;u<26&&e[u]==-1;u++);
    if(u==26){
        return check();
    }
    for(;e[u]<h_cnt;e[u]++){
        if(!dfs(u+1)) return false;
    }
    e[u]=0;
    return true;
}

int main(){
    nei['#']=-1;wai['#']=-1;
    wai[')']=0;
    nei['(']=0;wai['(']=16;
    nei['~']=9;wai['~']=10;
    nei['&']=8;wai['&']=7;
    nei['|']=6;wai['|']=5;
    nei['>']=3;wai['>']=4;
    nei['=']=1;wai['=']=2;

    int a,b;
    scanf("%d%d\n",&n,&m);
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++) g[i][i]=1;
    for(int i=1;i<=m;i++){
        scanf("%d%d\n",&a,&b);
        g[a][b]=1;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if(g[i][k]&&g[k][j]) g[i][j]=1;
    }

    prepare();
    //printf("h_cnt:%d\n",h_cnt);
    scanf("%d\n",&m);
    int l1,l2;
    for(int i=0;i<m;i++){
        gets(s);
        l1=strlen(s);l2=0;
        memset(e,-1,sizeof(e));
        for(int i=0;i<l1;i++){
            if(s[i]==' ') continue;
            else if(s[i]=='='&&(s[i+1]=='>')) continue;
            else s[l2++]=s[i];
            if(s[i]>='A'&&s[i]<='Z') e[s[i]-'A']=0;
        }
        s[l2++]='#';s[l2]='\0';
        if(!dfs(0)) puts("invalid");
        else puts("valid");
    }
    return 0;
}
