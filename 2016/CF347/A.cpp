# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=110;

char s[1010];
int op[maxn];
int now=1;
int num[maxn];
int n,m;

int main(){
    gets(s);
    int pos=1;
    op[1]=1;
    while(s[pos]!='='){
        if(s[pos]=='+'||s[pos]=='-') op[++now]=s[pos]=='+' ? 1 :-1;
        pos++;
    }

    n=0;
    while(s[pos]<'0'||s[pos]>'9') pos++;
    while(s[pos]>='0'&&s[pos]<='9') n=n*10+s[pos]-'0',pos++;
    m=now;

    //puts("fuck");

    int sum=0,t;
    for(int i=1;i<=m;i++) num[i]=1,sum+=op[i];

    if(sum<n){

        for(int i=1;i<=m;i++) if(op[i]==1) t=min(n-sum,n-num[i]),num[i]+=t,sum+=t;
    }

    if(sum>n){
        for(int i=1;i<=m;i++) if(op[i]==-1) t=min(sum-n,n-num[i]),num[i]+=t,sum-=t;
    }

    if(sum!=n) puts("Impossible");
    else{
        printf("Possible\n");
        printf("%d",num[1]);
        for(int i=2;i<=m;i++){
            printf(" %c %d",op[i]==1?'+':'-',num[i]);
        }
        printf(" = %d\n",n);
    }

    return 0;
}
