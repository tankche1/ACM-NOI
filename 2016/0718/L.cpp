# include<stdio.h>
# include<iostream>
# include<map>
# include<math.h>
# include<string.h>
# include<string>
# include<algorithm>
using namespace std;
const int maxn=70;
int n,m;
int a,b;
string name1,name2;
string s[70];
map<string,int> id;

long long px[maxn],py[maxn],pz[maxn];
double dist[maxn][maxn];

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        id.clear();
        for(int i=1;i<=n;i++){
            cin >> s[i];dist[i][i]=0;
            id[s[i]]=i;
            scanf("%I64d%I64d%I64d",&px[i],&py[i],&pz[i]);
        }

        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                dist[i][j]=dist[j][i]=sqrt((px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j])+(pz[i]-pz[j])*(pz[i]-pz[j]));
            }
        }

        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            cin >> name1;cin >> name2;
            a=id[name1],b=id[name2];
            dist[a][b]=0;
        }

        for(int k=1;k<=n;k++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(dist[i][j]-dist[i][k]>dist[k][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];
                    }
                }
            }
        }

        printf("Case %d:\n",Tcase);
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            cin >> name1;cin >> name2;
            a=id[name1],b=id[name2];
            printf("The distance from ");
            cout << name1 ;
            printf(" to ");cout << name2;
            //printf("a:%d b:%d ",a,b);
            printf(" is %d parsecs.\n",(int)(dist[a][b]+0.5));
        }
    }
    return 0;
}
