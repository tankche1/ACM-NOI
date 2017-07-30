# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
# define mp(a,b) make_pair(a,b)
using namespace std;
const int maxm=200010;
typedef pair<int,int> pi;
map< pi,int> id;
int m;
int cnt=0;
int p[maxm<<1];
int find(int x){
    static int t,root;
    root=x;
    while(p[root]!=root){
        root=p[root];
    }
    while(x!=root){
        t=p[x];p[x]=root;x=t;
    }
    return root;
}
int main(){
    int x1,y1,x2,y2,a,b,pa,pb;
    scanf("%d",&m);
    //for(int i=1;i<=2*m;i++) p[i]=i;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x1,&y1);scanf("%d%d",&x2,&y2);
        if(!id.count(mp(x1,y1))) {id[mp(x1,y1)]=++cnt;p[cnt]=cnt;}
        if(!id.count(mp(x2,y2))) {id[mp(x2,y2)]=++cnt;p[cnt]=cnt;}
        a=id[mp(x1,y1)];b=id[mp(x2,y2)];
        pa=find(a);pb=find(b);
        //printf("a:%d b:%d pa:%d pb:%d\n",a,b,pa,pb);
        if(pa==pb) {printf("%d\n",i);return 0;}
        p[pa]=pb;
    }
    puts("0");
    return 0;
}
