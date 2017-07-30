#include <stdio.h>
#include <string.h>
#include <math.h>
# include<algorithm>
using namespace std;
const int maxn = 1010;
int dp[maxn][maxn];
int d[maxn][maxn];
struct point
{
    int x, y;
}a[maxn];

int dis(int i, int j)                   //计算两点之间的距离
{
     int p,q;
     if(a[i].y>a[j].y)
          q=(360+a[j].y-a[i].y)%360;
     else
          q=(360+a[i].y-a[j].y)%360;
          p=abs(a[i].y-a[j].y)>q?q:abs(a[i].y-a[j].y);                     //求出小弧的长度
    return (abs(a[i].x-a[j].x)*400+p);                  //距离=两点的轨道差*400+两点的扇区差
}
int main()
{
    int t,n;
    scanf("%d",&t);
    while(t-- )
    {
         scanf("%d", &n);
         a[1].x=0;
         a[1].y=0;                                      //把起点（0，0）加上
        for(int i = 2; i <= n+1; i++)
            scanf("%d %d", &a[i].x, &a[i].y);

        for(int i = 1; i <= n+1; i++)
        {
            for(int j = 1; j <= n+1; j++)
            {
                d[i][j] = dis(i, j);               //d[i][j]为i点到j点的距离
            }
        }
        dp[1][2] = d[1][2];                 
        for(int i = 3; i <= n+1; i++)
        {
            for(int j = 1; j < i-1; j++)
            {
                 dp[j][i] = dp[j][i-1] + d[i-1][i];                /*      dp[j][i]为j点到1点，再从1点到i点的距离，这一步是为下一循环求dp[i][i+1]做准备，其实就是图a      */
            }

            dp[i-1][i] = 999999999;
            for(int j = 1; j < i-1; j++)
            {
                int sum = dp[j][i-1] + d[j][i];
                if(dp[i-1][i] > sum)
                    dp[i-1][i] = sum;                         /*     dp[i-1][i]为i-1点到1点，再从1点到i点的最短距离,这个距离只要加上边d[i-1][i]就是从1点到i点的最短闭合旅程，其实就是图b      */      
            }
        }
        dp[n+1][n+1] = dp[n][n+1] + d[n][n+1];
        printf("%d\n", dp[n+1][n+1]+10*n);        /*   dp[n+1][n+1]就是最终的最短闭合旅程，n+1点到1点，再从1点到n+1点的最短距离 ,10*n为读取点中数据的时间 */
    }
    return 0;
}