/*
状态如何保存呢，不懂
因为题目已经说了，最多的可以走的位置不会大于32，这是不是暗示着什么呢，有点意思
在仔细看一下这个地图上面的东西，会有“.(0)”、“S(1)”、“M(2)”、“P(3)”
那么就是四个状态，也就是4进制，32位来表示
一个四进制的3210表示十进制为3*4^3+2*4^2+1*4^1+0*4^0=228
那就是4^3 = 2^6，我们记录了相对位置之后，就可以在对应位置放123了
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
typedef unsigned long long ull;
const int maxn = 10;
using namespace std;
const int n = 6, m = 8;
int fx[] = {-1,1,0,0};
int fy[] = {0,0,-1,1};
struct point//在森林中的动物
{
    int x,y,ani,flag;//1-s,2-m,3-p//是否还在标记中
};
struct node
{
    int size;   //动物总数
    point animals[maxn];
    char mp[maxn][maxn];
    int flag;//早到的标志
    void operator=(node a)
    {
        memcpy(animals, a.animals, sizeof(animals));
        memcpy(mp, a.mp, sizeof(mp));
        size =a.size;
        flag = a.flag;
    }
    void Init()
    {
        size = 0;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                if(mp[i][j] == 'S')
                {
                    animals[size].x = i;
                    animals[size].y = j;
                    animals[size].flag = 0;
                    animals[size++].ani = 1;
                }
                if(mp[i][j] == 'M')
                {
                    animals[size].x = i;
                    animals[size].y = j;
                    animals[size].flag = 0;
                    animals[size++].ani = 2;
                }
                if(mp[i][j] == 'P')
                {
                    animals[size].x = i;
                    animals[size].y = j;
                    animals[size].flag = 0;
                    animals[size++].ani = 3;
                }
            }
        }
    }
};
char mp[maxn][maxn];//初始地图
int bp[maxn][maxn]; //记录空位的编码
int tot;            //状态映射
ull bit[70];        //进制转换
map<ull, int>vis;
queue<node>que;
bool chare(int x,int y)//判断是否越界
{
    if(x<1||y<1||x>n||y>m)return false;
    return true;
}
void Init()//记录空格对应位
{
    int tt = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(mp[i][j] == '#' || mp[i][j] == 'N')
                continue;
            bp[i][j] = tt++;
        }
    }
}
ull Getnum(char mp[maxn][maxn])//对应状态
{
    ull ret = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(mp[i][j] == 'S')
            {
                ret += 1*bit[bp[i][j]<<1];
            }
            else if(mp[i][j] == 'M')
            {
                ret += 2*bit[bp[i][j]<<1];
            }
            else if(mp[i][j] == 'P')
            {
                ret += 3*bit[bp[i][j]<<1];
            }
        }
    }
    return ret;
}
void move(int f,int ani,node &he)
{
    int xi = he.animals[ani].x;
    int yi = he.animals[ani].y;
    he.mp[xi][yi]='.';
    if(he.animals[ani].ani == 1)//人在走
    {
        xi += fx[f];
        yi += fy[f];//走了一步，人的那一步，只要不是树，和老鼠就可以走，因为碰见猪就被吃了，碰见海螺就结束游戏了，所以不会跟他们同格
        while(chare(xi,yi)&&he.mp[xi][yi]!='#'&&he.mp[xi][yi]!='M'&&he.mp[xi][yi]!='S')//这一步是有效的
        {
            //先检查是否有猪
            if(he.mp[xi+1][yi]=='P'||he.mp[xi-1][yi]=='P'||he.mp[xi][yi+1]=='P'||he.mp[xi][yi-1]=='P')
                return;
            //检查是有嗨喽
            if(he.mp[xi+1][yi]=='N'||he.mp[xi-1][yi]=='N'||he.mp[xi][yi+1]=='N'||he.mp[xi][yi-1]=='N')
            {
                he.flag = 1;
                return;
            }
            xi += fx[f];
            yi += fy[f];
        }
        xi -= fx[f];
        yi -= fy[f];
        he.mp[xi][yi] = 'S';
        he.animals[ani].x=xi;
        he.animals[ani].y=yi;
        ull stt = Getnum(he.mp);
        if(vis.find(stt) == vis.end())
        {
            vis[stt] = 1;
            que.push(he);
        }
    }
    if(he.animals[ani].ani==2)//老鼠在走
    {
        xi += fx[f];
        yi += fy[f];//走了一步，人的那一步，只要不是树，和老鼠就可以走，因为碰见猪就被吃了，碰见海螺就结束游戏了，所以不会跟他们同格
        while(chare(xi,yi)&&he.mp[xi][yi]!='#'&&he.mp[xi][yi]!='S'&&he.mp[xi][yi]!='M')//这一步是有效的
        {
            //先检查是否有猪
            if(he.mp[xi+1][yi]=='P'||he.mp[xi-1][yi]=='P'||he.mp[xi][yi+1]=='P'||he.mp[xi][yi-1]=='P')
            {
                he.animals[ani].flag = 1;//被吃掉了
                ull stt = Getnum(he.mp);
                if(vis.find(stt) == vis.end())
                {
                    vis[stt] = 1;
                    que.push(he);
                }
                return;
            }
            //检查是有嗨喽
            if(he.mp[xi+1][yi]=='N'||he.mp[xi-1][yi]=='N'||he.mp[xi][yi+1]=='N'||he.mp[xi][yi-1]=='N')
            {
                return;
            }
            xi += fx[f];
            yi += fy[f];
        }
        xi -= fx[f];
        yi -= fy[f];
        he.mp[xi][yi] = 'M';
        he.animals[ani].x=xi;
        he.animals[ani].y=yi;
        ull stt = Getnum(he.mp);
        if(vis.find(stt) == vis.end())
        {
            vis[stt] = 1;
            que.push(he);
        }
    }
    if(he.animals[ani].ani==3)//猪就比较有搞头了，
    {
        int eat = 0;
        xi += fx[f];
        yi += fy[f];
        while(chare(xi,yi)&&he.mp[xi][yi]!='#'&&he.mp[xi][yi]!='P')
        {
            for(int j = 0; j < 4; j++)//扫描当前点的四周
            {
                if(he.mp[xi+fx[j]][yi+fy[j]] =='S'||he.mp[xi+fx[j]][yi+fy[j]]=='M')//有人、老鼠
                {
                    eat = 1;
                    he.mp[xi+fx[j]][yi+fy[j]] = '.';
                    for(int i = 0; i < he.size; i++)
                    {
                        if(he.animals[i].x == xi+fx[j] && he.animals[i].y == yi+fy[j])
                        {
                            he.animals[i].flag = 1;
                            break;
                        }
                    }
                }
                if(he.mp[xi+fx[j]][yi+fy[j]] =='N')return;
            }
            if(eat)
            {
                he.mp[xi][yi] = 'P';
                he.animals[ani].x=xi;
                he.animals[ani].y=yi;
                ull stt = Getnum(he.mp);
                if(vis.find(stt) == vis.end())
                {
                    vis[stt] = 1;
                    que.push(he);
                }
                return;
            }
            xi += fx[f];
            yi += fy[f];
        }
        xi -= fx[f];
        yi -= fy[f];
        he.mp[xi][yi] = 'P';
        he.animals[ani].x=xi;
        he.animals[ani].y=yi;
        ull stt = Getnum(he.mp);
        if(vis.find(stt) == vis.end())
        {
            vis[stt] = 1;
            que.push(he);
        }
    }
}
int bfs()
{
    ull p1,q1;
    node p,q;
    memcpy(p.mp, mp,sizeof(p.mp));
    p.Init();
    p.flag=0;
    p1 = Getnum(p.mp);
    vis.clear();
    vis.insert(pair<ull,int>(p1,1));
    while (!que.empty())que.pop();
    que.push(p);
    int stap = 0;
    while(!que.empty())
    {
        stap++;
        int size = que.size();
        while(size--)
        {
            p = que.front();
            que.pop();
            for(int i = 0; i < p.size; i++)//对里面的动物进行移动
            {
                if(p.animals[i].flag)continue;
                for(int j = 0; j < 4; j++)
                {
                    q = p;
                    move(j,i,q);//i去跑
                    if(q.flag)return stap;
                }
            }
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    bit[0] = 1;
    for(int i = 1; i <= 64; i++)
        bit[i] = bit[i-1]*2;
    while(scanf("%s",mp[1]+1)!=EOF)
    {
        for(int i = 2; i <= n; i++)
            scanf("%s",mp[i]+1);
        Init();
        printf("%d\n",bfs());
    }
    return 0;
}
