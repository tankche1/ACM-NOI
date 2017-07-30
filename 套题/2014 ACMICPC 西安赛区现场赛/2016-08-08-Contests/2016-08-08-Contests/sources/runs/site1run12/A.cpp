#include <bits/stdc++.h>
using namespace std;

int main() {
    int casen;
    cin>>casen;
    for (int pp=1;pp<=casen;pp++) {
        int n;bool flag=true;
        cin>>n;
        for (int i=0,x;i<n;i++) {
            scanf("%d",&x);
            if (x%3) flag=false;
        }
        printf("Case #%d: %s\n",pp,flag?"Yes":"No");
    }

}
