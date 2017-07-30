# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
typedef long long LL;
struct Animal{
    int x,y;
    bool dead;
    char type;
    Animal() {}
    Animal(int _x,int _y,bool _dead,char _type):x(_x),y(_y),dead(_dead),type(_type){}
};
Animal an[6],ann[6];
int acnt=0;
int nutx,nuty;
int code[7][10],space;

char s[7][10];

bool check(int x,int y) {return x>=0&&x<6&&y>=0&&y<8&&s[x][y]!='#';}
bool caneat(char t) {return t=='N'||t=='S'||t=='M';}
bool have(int x,int y,char c){
    for(int i=0;i<acnt;i++) if(an[i].type==c&&an[i].x==x&&an[i].y==y&&an[i].dead==0) return true;
    return false;
}

inline void add(int &x) {x++;if(x==100000) x=0;}

int step[1000000];
Animal que[100000][6];

LL getcode(){
    static LL tmp;tmp=0;
    for(int i=acnt-1;i>=0;i--){
        if(an[i].dead==1) tmp=tmp*33;
        else tmp=tmp*33+code[an[i].x][an[i].y];
    }
    return tmp;
}
LL val[1000000];
const LL MO = 233333;
int first[240000],nex[1000000],top;

bool find(int mo,LL hash) {
    for (int i = first[mo]; i; i = nex[i])
        if (val[i] == hash) return true;
    return false;
}

void build(LL hash) {
    int mo = hash % MO;
    nex[++top] = first[mo]; first[mo] = top;
    val[top] = hash;
}

bool judge(LL hash) {
    LL h = hash % MO;
    return find(h,hash);
}

void Copy(){for(int i=0;i<acnt;i++) an[i]=ann[i];}

int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
void BFS(){
    int front=0,rear=1,nx,ny;
    LL tc;
    for(int i=0;i<acnt;i++) que[0][i]=an[i];
    step[0]=0;
    top = 0; memset(first,0,sizeof(first));

    tc=getcode();build(tc);
    int stop,stepp,squ;
    while(front!=rear){
        for(int i=0;i<acnt;i++) ann[i]=an[i]=que[front][i];stepp=step[front];add(front);

        squ=0;for(int i=0;i<acnt;i++) if(an[i].type=='S'&&an[i].dead==0) squ++;
        if(!squ) continue;
        //for(int i=0;i<acnt;i++)
            //printf("%c x:%d y:%d dead:%d\n",an[i].type,an[i].x,an[i].y,an[i].dead);
        for(int i=0;i<acnt;i++){//pig
            if(ann[i].type!='P'||ann[i].dead==1) continue;
            for(int d=0;d<4;d++){
                Copy();
                stop=false;
                while(1){
                    if(stop!=0) break;
                    nx=an[i].x+dx[d];ny=an[i].y+dy[d];
                    if((!check(nx,ny))||have(nx,ny,'P')) break;
                    an[i].x=nx;an[i].y=ny;
                    for(int j=0;j<acnt;j++){
                        if((an[j].type=='S'||an[j].type=='M')&&an[j].dead==0){
                            if(abs(an[j].x-nx)+abs(an[j].y-ny)==1){
                                stop=true;an[j].dead=1;
                            }
                        }
                    }
                    if(abs(nutx-an[i].x)+abs(nuty-an[i].y)==1) stop=-1;
                }
                if(stop==-1) continue;
                tc=getcode();
                if(!judge(tc)) {build(tc); for(int j=0;j<acnt;j++) que[rear][j]=an[j];step[rear]=stepp+1;add(rear);}
            }
        }

        for(int i=0;i<acnt;i++){//mat
            if(ann[i].type!='M'||ann[i].dead==1) continue;
            for(int d=0;d<4;d++){
                 Copy();stop=0;
                 while(1){
                    nx=an[i].x+dx[d];ny=an[i].y+dy[d];
                    if((!check(nx,ny))||have(nx,ny,'M')||have(nx,ny,'S')) break;
                    an[i].x=nx;an[i].y=ny;
                    for(int j=0;j<acnt;j++){
                        if(an[j].type=='P'&&an[j].dead==0){
                            if(abs(an[j].x-nx)+abs(an[j].y-ny)==1){
                                an[i].dead=1;break;
                            }
                        }
                    }
                    if(an[i].dead) break;
                    if(abs(nutx-an[i].x)+abs(nuty-an[i].y)==1) {stop=-1;break;}
                }
                if(stop==-1) continue;
                tc=getcode();
                if(!judge(tc)) {build(tc); for(int j=0;j<acnt;j++) que[rear][j]=an[j];step[rear]=stepp+1;add(rear);}
            }
        }

        for(int i=0;i<acnt;i++){//squirrel
            if(ann[i].type!='S'||ann[i].dead==1) continue;
            for(int d=0;d<4;d++){
                 Copy();
                 stop=0;
                 while(1){
                    nx=an[i].x+dx[d];ny=an[i].y+dy[d];
                    //printf("nx:%d ny:%d nutx:%d nuty:%d\n",nx,ny,nutx,nuty);
                    if((!check(nx,ny))||have(nx,ny,'M')||have(nx,ny,'S')) break;
                    an[i].x=nx;an[i].y=ny;
                    for(int j=0;j<acnt;j++){
                        if(an[j].type=='P'&&an[j].dead==0){
                            if(abs(an[j].x-nx)+abs(an[j].y-ny)==1){
                                an[i].dead=1;break;
                            }
                        }
                    }
                    if(an[i].dead) break;
                    if(abs(nutx-an[i].x)+abs(nuty-an[i].y)==1) {stop=-1;break;}
                }
                if(stop==-1) {printf("%d\n",stepp+1);return;}
                tc=getcode();
                if(!judge(tc)) {build(tc); for(int j=0;j<acnt;j++) que[rear][j]=an[j];step[rear]=stepp+1;add(rear);}
            }
        }

    }
}
int main(){
    //freopen("input.txt","r",stdin);
    while(scanf("%s",s[0])!=EOF){
        for(int i=1;i<6;i++) scanf("%s",s[i]);
        acnt=0;space=0;

        for(int i=0;i<6;i++){
            for(int j=0;j<8;j++){
                if(s[i][j]=='N') {nutx=i,nuty=j;}
                if(s[i][j]=='P'){
                    for(int d=0;d<4;d++){
                        if(check(i+dx[d],j+dy[d])&&caneat(s[i+dx[d]][j+dy[d]])){
                            s[i+dx[d]][j+dy[d]]='.';
                        }
                    }
                }
            }
        }

        for(int i=0;i<6;i++){
            for(int j=0;j<8;j++){
                if(s[i][j]=='M'||s[i][j]=='S'||s[i][j]=='P') an[acnt++]=Animal(i,j,0,s[i][j]);
                if(s[i][j]!='#') s[i][j]='.',code[i][j]=++space;
            }
        }
        BFS();
    }
    return 0;
}
