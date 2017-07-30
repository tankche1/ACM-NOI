# include<stdio.h>
# include<string.h>
# include<math.h>
# include<set>
# include<algorithm>
using namespace std;
multiset<int> S;
multiset<int>::iterator it;
int n;
int main(){
    int op,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&op);
        if(op==1){
                scanf("%d",&x);
            S.insert(x);
        }
        else if(op==2){
            it=S.begin();
            if(it==S.end()) continue;
            S.erase(it);
        }
        else{
            it=S.end();if(it==S.begin()) {puts("0");continue;}
            it--;
            printf("%d\n",*it);
        }
    }
    return 0;
}
