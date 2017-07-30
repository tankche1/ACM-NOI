# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int A,alpha,beta,gamma,M,k;
int pos[maxn],f[maxn];
int main(){
    scanf("%d%d%d%d%d%d",&A,&alpha,&beta,&gamma,&M,&k);
    if(k==0) {printf("%d\n",A);return 0;}
    A%=M;
    memset(pos,-1,sizeof(pos));
    f[0]=A;pos[A]=0;
    int st,ed;
    for(int i=1;;i++){
        f[i]=(alpha*f[i-1]*f[i-1]+beta*f[i-1]+gamma)%M;
        if(pos[f[i]]!=-1) {
            st=pos[f[i]];ed=i-1;break;
        }
        pos[f[i]]=i;
    }
    if(k<=ed+1) {printf("%d\n",f[k]);return 0;}
    k-=st-1;
    k%=(ed-st+1);
    if(k==0) printf("%d\n",f[ed]);
    else printf("%d\n",f[st+k-1]);
    return 0;
}
