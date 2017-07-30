# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=110;
int n;
int type[maxn];
vector<int> love,hate;
int main(){
    int tcase,v;
    scanf("%d",&tcase);
    while(tcase--){
        love.clear();hate.clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            printf("1\n");fflush(stdout);
            printf("%d\n",i);fflush(stdout);
            scanf("%d",&v);if(v==0) hate.push_back(i);else love.push_back(i);
        }
        for(int i=0;i<(int)love.size();i++){
                //printf("love[%d]:%d\n",i,love[i]);
            printf("%d\n",(int)hate.size()+1);fflush(stdout);
            printf("%d",love[i]);
            for(int j=0;j<(int)hate.size();j++){
                printf(" %d",hate[j]);
            }puts("");fflush(stdout);
            scanf("%d",&v);
            if(v!=0) type[love[i]]=1;else type[love[i]]=3;
        }
        for(int i=0;i<(int)hate.size();i++){
            //printf("hate[%d]:%d\n",i,hate[i]);
            printf("%d\n",(int)love.size()+1);fflush(stdout);
            printf("%d",hate[i]);
            for(int j=0;j<(int)love.size();j++)
                printf(" %d",love[j]);
            puts("");fflush(stdout);
            scanf("%d",&v);
            if(v==(int)love.size()+1) type[hate[i]]=3;else type[hate[i]]=2;
        }
        printf("-1\n");fflush(stdout);
        printf("%d",type[1]);
        for(int i=2;i<=n;i++)
            printf(" %d",type[i]);puts("");fflush(stdout);
    }
    return 0;
}
