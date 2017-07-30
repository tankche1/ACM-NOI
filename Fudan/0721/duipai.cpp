/***********************************************
 * Author: fisty
 * Created Time: 2015/6/14 16:37:52
 * File Name   : hdu3709.cpp
 *********************************************** */
#include <iostream>
#include <cstring>
#include <deque>
#include <cmath>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>
#include <algorithm>
using namespace std;
#define Debug(x) cout << #x << " " << x <<endl
#define Memset(x, a) memset(x, a, sizeof(x))
const int INF = 0x3f3f3f3f;
typedef long long LL;
typedef pair<int, int> P;
#define FOR(i, a, b) for(int i = a;i < b; i++)
#define MAX_N 20
int t;
LL n, m;
int digit[MAX_N];
LL dp[MAX_N][MAX_N][2005];
//dp[i][j][k] 代表i位数字，支点为j， 力矩为k
LL dfs(int len, int o, int s, int e){
    if(len <= 0) return s == 0;
    if(s < 0) return 0;
    if(!e && dp[len][o][s] != -1) return dp[len][o][s];
        
    LL res = 0;
    int u = e ? digit[len] : 9;
    for(int d = 0;d <= u; d++){
        int next = s + d * (len - o);
        res += dfs(len-1, o, next, e && (d == u));
    }
    if(!e)
        dp[len][o][s] = res;
    return  res;
}
LL solve(LL x){
    int len = 0;
    while(x){
        digit[++len] = x % 10;
        x /= 10;
    }
    LL ans = 0;
    for(int i = 1;i <= len; i++){
        ans += dfs(len, i, 0, 1);
    }
    return ans - (len-1); //减去 00 , 000 , 0000的情况
}
int main() {
    //freopen("in.cpp", "r", stdin);
    //cin.tie(0);
    //ios::sync_with_stdio(false);
    scanf("%d", &t);
    while(t--){
        Memset(dp, -1);
        scanf("%I64d%I64d", &n, &m);
        LL ans = solve(m) - solve(n-1);
        printf("%I64d\n", ans);
    }
    return 0;
}