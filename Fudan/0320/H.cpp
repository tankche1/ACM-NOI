# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
int n,S;

struct point{
    double x,y;
    char name[50];
}hey;


bool cmp(point A,point B){
    if(A.x!=B.x)
        return A.x<B.x;
    return A.y<B.y;
}

void dfs(double S,vector<point> &p){
    /*printf("S:%.2lf\n",S);
    for(int i=0;i<(int)p.size();i++){
        printf("%.1lf %.1lf\n",p[i].x,p[i].y);
    }
    if(S<1) {int tt;scanf("%d",&tt);}*/
    if((int)p.size()<=1) return;
    vector<point> b[4];
    double M=S/2.0;
    for(int i=0;i<(int)p.size();i++){
        if(p[i].x<M&&p[i].y<M){
            swap(p[i].x,p[i].y);
            b[0].push_back(p[i]);
        }
        else if(p[i].x<M&&p[i].y>M){
            p[i].y-=M;
            b[1].push_back(p[i]);
        }
        else if(p[i].x>M&&p[i].y>M)
            p[i].x-=M,p[i].y-=M,
            b[2].push_back(p[i]);
        else {
            p[i].x=S-p[i].x;p[i].y=M-p[i].y;
            swap(p[i].x,p[i].y);
            b[3].push_back(p[i]);
        }
    }
    dfs(M,b[0]);
    dfs(M,b[1]);
    dfs(M,b[2]);
    dfs(M,b[3]);
    p.clear();
    for(int j=0;j<4;j++){
        for(int i=0;i<(int)b[j].size();i++){
            p.push_back(b[j][i]);
        }
    }
    return;
}

vector<point> p;
int main(){
    scanf("%d%d",&n,&S);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf",&hey.x,&hey.y);
        scanf("%s",hey.name);
        p.push_back(hey);
    }
    //sort(p+1,p+n+1,cmp);

    dfs((double)S,p);
    for(int i=0;i<(int)p.size();i++)
        printf("%s\n",p[i].name);
    return 0;
}
