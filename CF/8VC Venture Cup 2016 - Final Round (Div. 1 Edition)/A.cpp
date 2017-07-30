# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
int n;
int a[maxn],b[maxn];

void inc(int &x){
    x++;if(x>n) x=1;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    int pos1,pos2;
    for(pos2=1;b[pos2]==0;pos2++);
    for(pos1=1;a[pos1]!=b[pos2];pos1++);

    bool ok=true;
    for(int i=1;i<=n-2;i++){
        inc(pos1);inc(pos2);
        if(a[pos1]==0) inc(pos1);
        if(b[pos2]==0) inc(pos2);
        if(a[pos1]!=b[pos2]) ok=false;
    }
    if(ok) puts("YES");
    else puts("NO");
    return 0;
}
