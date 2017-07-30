# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=100000000;
const int maxn=110;
char s[maxn],op;
int a,b,c,n;

bool num(char c){
    return (c>='0'&&c<='9')||c=='?';
}

int get(int &t,int x){
    //printf("--  %c%c  --",s[t],s[t+1]);
    if(s[t]=='-'&&((s[t+1]==0)||(s[t+1]=='?'&&x==0))) return -INF;
    if(x==0&&s[t]=='?'&&((s[t+1])=='?'||(s[t+1]>='0'&&s[t+1]<='9'))) return -INF;
    int a=0,type=1;
    if(s[t]=='-') type=-1,t++;
    while(num(s[t])){
        if(s[t]=='?') a=a*10+x;
        else a=a*10+s[t]-'0';
        t++;
    }
    return a*type;
}

int main(){
    int T;
    int t;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%s",s);
        n=strlen(s);s[n]='#';s[n+1]='\0';
        for(int x=0;x<=10;x++){
            if(x==10) {printf("-1\n");break;}

            bool ok=false;
            for(int i=0;i<n;i++){
                if(s[i]>='0'&&s[i]<='9'){
                    if(s[i]-'0'==x) {ok=true;break;}
                }
            }if(ok) continue;
            t=0;//printf("x:%d\n",x);
            a=get(t,x);//printf("a:%d ",a);
            if(a==-INF) continue;
            op=s[t];t++;
            b=get(t,x);//printf("b:%d t:%d ",b,t);
            if(b==-INF) continue;
            t++;
            c=get(t,x);//printf("c:%d \n",c);
            if(c==-INF) continue;

            if(op=='+'&&a+b==c){
                printf("%d\n",x);break;
            }
            else if(op=='-'&&a-b==c){
                printf("%d\n",x);break;
            }
            else if(op=='*'&&(long long)a*b==(long long)c){
                printf("%d\n",x);break;
            }
        }
    }
    return 0;
}
