# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL a[maxn],n;
struct HeapNode{
    LL val;
    HeapNode(){}
    HeapNode(LL val):val(val) {}
    bool operator < (const HeapNode &rhs)const{
        return rhs.val<val;
    }
};
priority_queue<HeapNode> q;
int main(){
    int tcase;
    LL v,ans;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d",&n);
        ans=0;
        for(int i=1;i<=n;i++)
            scanf("%I64d",&a[i]),ans+=a[i],q.push(HeapNode(a[i]));
        while(!q.empty()){
            v=q.top().val;q.pop();
            if(q.empty()) break;
            v=v+q.top().val;q.pop();
            q.push(HeapNode(v));ans+=v;
        }ans-=v;
        printf("%I64d\n",ans);
    }
    return 0;
}
