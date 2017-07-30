# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
double eps=1e-8;
double pi=acos(-1.0);
double angle;
double R;

int n,m;

struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y) {}
    void read(){
        scanf("%lf%lf",&x,&y);
    }

}stu[maxn];

double Cross(Point A,Point B){
    return A.x*B.y-A.y*B.x;
}

Point Rotate(Point A,double angle){
    return Point(A.x*cos(angle)-A.y*sin(angle),A.x*sin(angle)+A.y*cos(angle));
}

Point operator + (Point A,Point B) {return Point(A.x+B.x,A.y+B.y);}
Point operator - (Point A,Point B) {return Point(A.x-B.x,A.y-B.y);}
Point operator * (Point A,double b) {return Point(A.x*b,A.y*b);}

double Length(Point A) {return sqrt(A.x*A.x+A.y*A.y);}

void Normal(Point &A) {double l=Length(A);A.x=A.x/l;A.y=A.y/l;}

Point st_pos,st_sight,st_dir;
Point now_pos,now_sight,now_dir;

int op[maxn],ti[maxn],alf[maxn];
Point Big;

bool In_rect(Point a,Point b,Point c,Point d){
    //printf("a:%.2lf %.2lf\n",a.x,a.y);
    //printf("b:%.2lf %.2lf\n",b.x,b.y);
    //printf("c:%.2lf %.2lf\n",c.x,c.y);
    //printf("d:%.2lf %.2lf\n",d.x,d.y);
    /*if(Cross(b-a,Big-a)<0) return false;
    if(Cross(c-b,Big-b)<0) return false;
    if(Cross(d-c,Big-c)<0) return false;
    if(Cross(a-d,Big-d)<0) return false;*/
    //printf("%.2lf %.2lf %.2lf %.2lf \n",Cross(b-a,Big-a),Cross(c-b,Big-b),Cross(d-c,Big-c),Cross(a-d,Big-d));
    if(Cross(b-a,Big-a)<eps&&Cross(c-b,Big-b)<eps&&Cross(d-c,Big-c)<eps&&Cross(a-d,Big-d)<eps) return true;
    if(Cross(b-a,Big-a)>-eps&&Cross(c-b,Big-b)>-eps&&Cross(d-c,Big-c)>-eps&&Cross(a-d,Big-d)>-eps) return true;
    //puts("&&&&&&&&&&&7fuck");
    return false;
}

bool Insight(){
    Point tt=Rotate(now_sight,angle);
    //printf("Big.x:%.3lf y:%.3lf now:%.3lf %.3lf len:%.3lf\n",Big.x,Big.y,now_pos.x,now_pos.y,Length(Big-now_pos));
    //printf("sight:%.3lf %.3lf angle:%.3lf %.3lf %.3lf dir:%.3lf %.3lf\n",now_sight.x,now_sight.y,angle,tt.x,tt.y,(Big-now_pos).x,(Big-now_pos).y);
    //printf("%d\n",Cross(now_sight,Big-now_pos)>=-eps&&Cross(Rotate(now_sight,angle),Big-now_pos)<=eps);
    if(Length(Big-now_pos)-R>eps) {return false;}
    if(Cross(now_sight,Big-now_pos)>=-eps&&Cross(Rotate(now_sight,angle),Big-now_pos)<=eps)
        {//puts("hei");
        return true;}
    else return false;
}

bool check(){
    double ang;
    now_pos=st_pos;now_sight=st_sight;now_dir=st_dir;
    if(Insight()) return true;
    //puts("***************");
    //printf("now:%.3lf %.3lf sight:%.3lf %.3lf\n",now_pos.x,now_pos.y,now_sight.x,now_sight.y);

    for(int i=1;i<=m;i++){
        if(ti[i]>ti[i-1]){
            if(In_rect(now_pos,now_pos+(now_sight*R),now_pos+now_dir*(ti[i]-ti[i-1])+(now_sight*R),now_pos+now_dir*(ti[i]-ti[i-1])))
                return true;
            if(In_rect(now_pos,now_pos+(Rotate(now_sight,angle)*R),now_pos+now_dir*(ti[i]-ti[i-1])+(Rotate(now_sight,angle)*R),now_pos+now_dir*(ti[i]-ti[i-1])))
                return true;
            if(Cross(now_sight,Rotate(now_dir,pi/2.0))>-eps&&Cross(Rotate(now_sight,angle),Rotate(now_dir,pi/2.0))<eps){
                if(In_rect(now_pos,now_pos+now_dir*(ti[i]-ti[i-1]),now_pos+now_dir*(ti[i]-ti[i-1])+(Rotate(now_dir,pi/2.0)*R),now_pos+(Rotate(now_dir,pi/2.0)*R)))
                    return true;
            }
            if(Cross(now_sight,Rotate(now_dir,-pi/2.0))>-eps&&Cross(Rotate(now_sight,angle),Rotate(now_dir,-pi/2.0))<eps){
                if(In_rect(now_pos,now_pos+(now_dir*(ti[i]-ti[i-1])),now_pos+(now_dir*(ti[i]-ti[i-1]))+(Rotate(now_dir,-pi/2.0)*R),now_pos+(Rotate(now_dir,-pi/2.0)*R)))
                    return true;
            }
        }
        now_pos=now_pos+now_dir*(ti[i]-ti[i-1]);
        if(Insight()) return true;
        ang=alf[i]/180.0*pi;
        if(op[i]==2){
            now_dir=Rotate(now_dir,-ang);
        }
        else{
            now_sight=Rotate(now_sight,-ang);
            swap(angle,ang);
            if(Insight()) {swap(angle,ang);return true;}
            swap(angle,ang);
        }
         //printf("now:%.3lf %.3lf sight:%.3lf %.3lf\n",now_pos.x,now_pos.y,now_sight.x,now_sight.y);
    }
    return false;
}

int ans[maxn];

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d%lf%lf",&n,&m,&angle,&R);//angle*=2;
        angle=angle/180.0*pi;
        st_pos.read();st_sight.read();st_dir.read();
        st_sight=Rotate(st_sight,-angle/2);
        Normal(st_sight);Normal(st_dir);

        for(int i=1;i<=n;i++) stu[i].read();

        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&op[i],&ti[i],&alf[i]);
        }ti[0]=0;

        for(int i=1;i<=n;i++){
            Big=stu[i];
            ans[i]=check();
        }

        printf("Case #%d: ",Tcase);
        for(int i=1;i<=n;i++){
            if(!ans[i]) printf("1");else printf("0");
        }
        puts("");
    }
    return 0;
}
