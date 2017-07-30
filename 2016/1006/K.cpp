# include<stdio.h>
# include<string.h>
# include<iostream>
# include<math.h>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=510;
double pi=acos(-1.0);
double tpi=2*pi;
double eps=1e-8;
int n,nn,ans=0;

struct point{
    int x,y;
    double ang;

    point() {}
    point(int x,int y):x(x),y(y) {}
}pp[maxn],p[maxn],p3[maxn];

int dcmp(double a){
    if(fabs(a)<eps) return 0;
    return a<0?-1:1;
}

int nex(int a){return a==nn?1:a+1;}

double Len(point A){return sqrt(A.x*A.x+A.y*A.y);}

bool cmp(point A,point B){
    if(dcmp(A.ang-B.ang)!=0) return A.ang<B.ang;
    return dcmp(Len(A)-Len(B))<0;
}

double get_ang(point A){
    double t=acos((double)A.x/Len(A));
    return A.y>=0?t:tpi-t;
}

point operator - (point A,point B) {return point(A.x-B.x,A.y-B.y);}

int Cross(point A,point B){
    return A.x*B.y-A.y*B.x;
}

bool tank(point A,point B){
    if((Cross(A,B)==0)&&(dcmp(A.ang-B.ang)!=0)) return true;
    return false;
}

void solve(int ori){
   // printf("ori:%d %d\n",pp[ori].x,pp[ori].y);
    int cnt=0;
    for(int i=1;i<=n;i++) if(i!=ori) p3[++cnt]=pp[i]-pp[ori],p3[cnt].ang=get_ang(p3[cnt]);

    sort(p3+1,p3+cnt+1,cmp);
    //for(int i=1;i<=cnt;i++) printf("x:%d y:%d ang:%.2lf\n",p3[i].x,p3[i].y,p3[i].ang);
    p[1]=p3[1];
    nn=1;
    for(int i=2;i<=cnt;i++){
        if(dcmp(p3[i].ang-p3[i-1].ang)!=0) p[++nn]=p3[i];
    }

   // for(int i=1;i<=nn;i++) printf("i:%d %d\n",p[i].x,p[i].y);

    int a,b,na,nb,besta,bestb;
    //printf("nn:%d\n",nn);
    for(int i=1;i<=nn;i++){
        a=i;b=-1;
        for(int j=nex(i);j!=i;j=nex(j)){
            if(tank(p[i],p[j])) {b=j;break;}
            if(Cross(p[i],p[j])<0) {break;}
        }
        //printf("i:%d b:%d\n",i,b);
        if(b==-1) continue;
        int j=b;
        //printf("i - j :%d %d %d %d\n",p[i].x,p[i].y,p[j].x,p[j].y);
        //printf("i:%d j:%d\n",i,j);

        na=nex(a);nb=nex(b);besta=na;bestb=nb;
        if(na!=j&&nb!=i&&tank(p[na],p[nb])) ans++;
        a=na;b=nb;
        na=nex(a);nb=nex(b);
        if(a==j||b==i) continue;
        if(na==j&&nb==i) continue;
        while(1){
            //printf("a - b: %d %d %d %d\n",p[a].x,p[a].y,p[b].x,p[b].y);
            //printf("a:%d b:%d\n",a,b);

            if((na!=j)||(nb==i&&Cross(p[a],p[nb])<0)) a=na;
            //else b=nb;
            else if((nb!=i)||(na==j&&Cross(p[na],p[b])>0)) b=nb;
            else puts("fuck");

            if(tank(p[a],p[b])&&Cross(p[besta]-p[i],p[a]-p[i])>0&&Cross(p[bestb]-p[j],p[b]-p[j])>0) ans++;
            if(a==na&&Cross(p[besta]-p[i],p[a]-p[i])>0) besta=a;
            if(b==nb&&Cross(p[bestb]-p[j],p[b]-p[j])>0) bestb=b;
           // printf("a:%d b:%d\n",a,b);


            na=nex(a);nb=nex(b);//printf("na:%d nb:%d\n",na,nb); //int tt;scanf("%d",&tt);
            //printf("na:%d nb:%d i:%d j:%d\n",na,nb,i,j);
            if(na==j&&nb==i) break;
        }//printf("ans:%d\n",ans);
    }
    //printf("ans:%d\n",ans);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&pp[i].x,&pp[i].y);

    /*for(int a=1;a<=n;a++){
        for(int b=1;b<=n;b++){
            if(a==b) continue;
            for(int c=1;c<=n;c++){
                if(a==c||b==c) continue;
                for(int d=1;d<=n;d++){
                    if(a==d||b==d||c==d) continue;
                    for(int e=1;e<=n;e++){
                        if(a==e||b==e||c==e||d==e) continue;
                       // printf("%d %d %d %d %d\n",a,b,c,d,e);
                        if(Cross(pp[b]-pp[a],pp[c]-pp[a])==0&&Cross(pp[d]-pp[a],pp[e]-pp[a])==0){
                            //printf("%d %d %d %d %d %d %d %d %d %d\n",pp[a].x,pp[a].y,pp[b].x,pp[b].y,pp[c].x,pp[c].y,pp[d].x,pp[d].y,pp[e].x,pp[e].y);
                        }
                    }
                }
            }
        }
    }*/

    for(int i=1;i<=n;i++) solve(i);
        printf("%d\n",ans/2);
    return 0;
}
