/*
״̬��α����أ�����
��Ϊ��Ŀ�Ѿ�˵�ˣ����Ŀ����ߵ�λ�ò������32�����ǲ��ǰ�ʾ��ʲô�أ��е���˼
����ϸ��һ�������ͼ����Ķ��������С�.(0)������S(1)������M(2)������P(3)��
��ô�����ĸ�״̬��Ҳ����4���ƣ�32λ����ʾ
һ���Ľ��Ƶ�3210��ʾʮ����Ϊ3*4^3+2*4^2+1*4^1+0*4^0=228
�Ǿ���4^3 = 2^6�����Ǽ�¼�����λ��֮�󣬾Ϳ����ڶ�Ӧλ�÷�123��
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
struct point//��ɭ���еĶ���
{
    int x,y,ani,flag;//1-s,2-m,3-p//�Ƿ��ڱ����
};
struct node
{
    int size;   //��������
    point animals[maxn];
    char mp[maxn][maxn];
    int flag;//�絽�ı�־
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
char mp[maxn][maxn];//��ʼ��ͼ
int bp[maxn][maxn]; //��¼��λ�ı���
int tot;            //״̬ӳ��
ull bit[70];        //����ת��
map<ull, int>vis;
queue<node>que;
bool chare(int x,int y)//�ж��Ƿ�Խ��
{
    if(x<1||y<1||x>n||y>m)return false;
    return true;
}
void Init()//��¼�ո��Ӧλ
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
ull Getnum(char mp[maxn][maxn])//��Ӧ״̬
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
    if(he.animals[ani].ani == 1)//������
    {
        xi += fx[f];
        yi += fy[f];//����һ�����˵���һ����ֻҪ��������������Ϳ����ߣ���Ϊ������ͱ����ˣ��������ݾͽ�����Ϸ�ˣ����Բ��������ͬ��
        while(chare(xi,yi)&&he.mp[xi][yi]!='#'&&he.mp[xi][yi]!='M'&&he.mp[xi][yi]!='S')//��һ������Ч��
        {
            //�ȼ���Ƿ�����
            if(he.mp[xi+1][yi]=='P'||he.mp[xi-1][yi]=='P'||he.mp[xi][yi+1]=='P'||he.mp[xi][yi-1]=='P')
                return;
            //����������
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
    if(he.animals[ani].ani==2)//��������
    {
        xi += fx[f];
        yi += fy[f];//����һ�����˵���һ����ֻҪ��������������Ϳ����ߣ���Ϊ������ͱ����ˣ��������ݾͽ�����Ϸ�ˣ����Բ��������ͬ��
        while(chare(xi,yi)&&he.mp[xi][yi]!='#'&&he.mp[xi][yi]!='S'&&he.mp[xi][yi]!='M')//��һ������Ч��
        {
            //�ȼ���Ƿ�����
            if(he.mp[xi+1][yi]=='P'||he.mp[xi-1][yi]=='P'||he.mp[xi][yi+1]=='P'||he.mp[xi][yi-1]=='P')
            {
                he.animals[ani].flag = 1;//���Ե���
                ull stt = Getnum(he.mp);
                if(vis.find(stt) == vis.end())
                {
                    vis[stt] = 1;
                    que.push(he);
                }
                return;
            }
            //����������
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
    if(he.animals[ani].ani==3)//��ͱȽ��и�ͷ�ˣ�
    {
        int eat = 0;
        xi += fx[f];
        yi += fy[f];
        while(chare(xi,yi)&&he.mp[xi][yi]!='#'&&he.mp[xi][yi]!='P')
        {
            for(int j = 0; j < 4; j++)//ɨ�赱ǰ�������
            {
                if(he.mp[xi+fx[j]][yi+fy[j]] =='S'||he.mp[xi+fx[j]][yi+fy[j]]=='M')//���ˡ�����
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
            for(int i = 0; i < p.size; i++)//������Ķ�������ƶ�
            {
                if(p.animals[i].flag)continue;
                for(int j = 0; j < 4; j++)
                {
                    q = p;
                    move(j,i,q);//iȥ��
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
