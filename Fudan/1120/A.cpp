# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=500010;
int n;
int a[maxn];
int b[maxn];
int ans=0;

void print(int x,int y,int k){
    for(int i=x;i<=y;i++) b[i]=k;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) b[i]=a[i];
    int pos=1,j,mid;
    for(int i=1;i<n;i++)
        if(a[i]==a[i+1]) pos++;
    for(int i=2;i<n;i++){
        if(a[i]!=a[i-1]){
            for(j=i;a[j]!=a[j+1]&&j<n;j++);
            j--;
            if(i<=j){
                   // printf("i:%d j:%d\n",i,j);
                ans=max(ans,(j-i+1+1)/2);
                if(a[i-1]==a[j+1]) print(i,j,a[i-1]);
                else{
                    mid=(j-i+1)>>1;
                    print(i,i+mid-1,a[i-1]);
                    print(i+mid,j,a[j+1]);
                }
                i=j+1;
            }
        }
    }
    printf("%d\n",ans);
    for(int i=1;i<n;i++) printf("%d ",b[i]);printf("%d\n",b[n]);
    return 0;
}
