#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

typedef long long ll;

#define _abs(x) ((x)>0?(x):-(x))

ll gcd(ll x, ll y){
    return x ? gcd(y%x, x) : y;
}

int N;
int a[2010],b[2010],c[2010];
vector <pair <ll, ll> > v;

ll func(void){
    int i,j;
    int ans = 0;

    i = 0;
    while(i < v.size()){
        for(j=i;j<v.size();j++) if(v[j] != v[i]) break;
        int d = j - i;
        ans += d * (d - 1) / 2;
        i = j;
    }

    return ans;
}

int main(void){
    int i,j;

    cin >> N;
    REP(i,N) scanf("%d%d%d", &a[i], &b[i], &c[i]);

    ll ans = 0;

    int zero = 0;
    REP(i,N) if(c[i] == 0) zero++;
    if(zero == 2) ans += N - 2;

    REP(i,N) if(c[i] != 0){
        v.clear();
        ll px = a[i] * a[i] + b[i] * b[i];
        ll qx = a[i] * c[i];
        ll py = a[i] * a[i] + b[i] * b[i];
        ll qy = b[i] * c[i];

        // cout << qx << "/" << px << ' ' << qy << "/" << py << endl;

        REP(j,i) if(c[j] != 0){
            ll px2 = a[j] * a[j] + b[j] * b[j];
            ll qx2 = a[j] * c[j];
            ll py2 = a[j] * a[j] + b[j] * b[j];
            ll qy2 = b[j] * c[j];

            ll rx = px * px2;
            ll sx = qx * px2 - px * qx2;

            ll ry = py * py2;
            ll sy = qy * py2 - py * qy2;

            ll g = gcd(_abs(sx), _abs(sy));
            sx /= g; sy /= g;
            if(sx < 0 || (sx == 0 && sy < 0)){
                sx = -sx;
                sy = -sy;
            }

            // cout << i << ' ' << j << ' ' << sx << "/" << rx << ' ' << sy << "/" << ry << endl;

            v.push_back(make_pair(sx, sy));
        }

        sort(v.begin(),v.end());

        ll tmp = func();
        ans += tmp;
    }

    cout << ans << endl;

    return 0;
}
