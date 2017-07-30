# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxl=52;
int nei[310],wai[310];
char optr[maxl];
LL numtr[maxl];
int num_top,op_top;

void init(){
    num_top=op_top=-1;
}

bool get(){
    if(num_top<1) return 0;
    char op=optr[op_top--];
    LL b=numtr[num_top--];LL a=numtr[num_top--];
    //printf("%I64d %c %I64d ",a,op,b);
    if(op=='+') numtr[++num_top]=a+b;
    else if(op=='-') numtr[++num_top]=a-b;
    else if(op=='*') numtr[++num_top]=a*b;
    else{
        LL tmp=1;
        while(b--)
            tmp*=a;
        numtr[++num_top]=tmp;
    }
    //printf("= %I64d\n",numtr[num_top]);
    return 1;
}

LL calc(char *s,int x){
    int n=strlen(s),pos=0;
    LL num;
    while(pos<n){
        //printf("pos:%d c:%c n:%d\n",pos,s[pos],n);
        if(s[pos]>='0'&&s[pos]<='9'){
            num=0;
            while(s[pos]>='0'&&s[pos]<='9'){
                num=num*10+s[pos]-'0';pos++;
            }
            numtr[++num_top]=num;
        }
        else if(s[pos]=='a'){
            numtr[++num_top]=x;
            pos++;
        }
        else{
            if(nei[optr[op_top]]==wai[s[pos]]) op_top--,pos++;
            else if(nei[optr[op_top]]<wai[s[pos]]) optr[++op_top]=s[pos++];
            else{
                if(!get()) return -1;
            }
        }
    }
    return numtr[num_top];
}

char origin[maxl];
char s[maxl];
int m;
int tri[10]={5,7,10,17,19,23,41,55,33,36};
int main(){
    nei['+']=2;wai['+']=1;
    nei['-']=2;wai['-']=1;
    nei['*']=4;wai['*']=3;
    nei['/']=4;wai['/']=3;
    nei['^']=6;wai['^']=5;
    //wai[')']=8;
    wai[')']=0;
    nei['(']=0;wai['(']=8;
    nei['#']=-1;wai['#']=-1;

    gets(origin);
    int nn=strlen(origin),n=0;
    origin[nn]='#';origin[++nn]='\0';
    for(int i=0;i<nn;i++) {if(origin[i]!=' ') origin[n++]=origin[i];}
    origin[n]='\0';

    scanf("%d\n",&m);
    bool ok;
    LL t1,t2;
    for(int i=0;i<m;i++){
        gets(s);
        nn=strlen(s),n=0;
        s[nn]='#';s[++nn]='\0';
        for(int i=0;i<nn;i++) if(s[i]!=' ') s[n++]=s[i];s[n]='\0';
        ok=true;
        for(int j=0;j<10;j++){
            init();
            optr[++op_top]='#';
            t1=calc(origin,tri[j]);//printf("t1:%I64d\n",t1);
            init();
            optr[++op_top]='#';
            t2=calc(s,tri[j]);//printf("t2:%I64d\n",t2);
            if(t1!=t2) {ok=false;break;}
        }
        if(ok) printf("%c",'A'+i);
    }
    puts("");
    return 0;
}
