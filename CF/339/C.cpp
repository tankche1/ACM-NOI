# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=30;
const int maxm=100010;
int n,a[maxn];
char A[maxm],B[maxm];

inline int gcd(int a,int b){
    if(a==0) return b;
    return gcd(b%a,a);
}

int main(){
    scanf("%d",&n);
    int odd=0,pos=0,tot=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);tot+=a[i];
        if(a[i]&1) pos=i,odd++;
    }
    if(n==1){
        printf("%d\n",a[1]);for(int i=1;i<=n;i++) for(int j=0;j<a[i];j++) printf("%c",'a'+i-1);puts("");
        return 0;
    }
    if(odd>1){
        printf("0\n");
        for(int i=1;i<=n;i++) for(int j=0;j<a[i];j++) printf("%c",'a'+i-1);puts("");
        return 0;
    }
    int t=a[1];
    for(int i=2;i<=n;i++) t=gcd(t,a[i]);
   // printf("t:%d odd:%d\n",t,odd);
    if(odd==0){
        printf("%d\n",t);
        int len=(tot)/t,k=1;int kk=len;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=a[i]/t;j++)
                A[k++]='a'+i-1,B[kk--]='a'+i-1;
        }
        for(int i=1;i<=t/2;i++){
            for(int j=1;j<=len;j++) printf("%c",A[j]);
            for(int j=1;j<=len;j++) printf("%c",B[j]);
        }
        puts("");
        return 0;
    }
    if(odd==1){
           // puts("fuck");
        printf("%d\n",t);
        int len=tot/t,k=1;int kk=len;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=a[i]/t/2;j++){
                A[k++]='a'+i-1;A[kk--]='a'+i-1;
            }
        }
        A[len/2+1]='a'+pos-1;
        for(int i=1;i<=t;i++){
            for(int j=1;j<=len;j++) printf("%c",A[j]);
        }puts("");
    }

    return 0;
}
