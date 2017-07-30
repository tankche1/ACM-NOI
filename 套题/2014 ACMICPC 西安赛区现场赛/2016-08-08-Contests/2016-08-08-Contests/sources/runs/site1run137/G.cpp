#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define clr(a) memset((a),0,sizeof(a))
#define intl long long
#define maxn 401000
using namespace std;

const intl Mo = 1000000007LL;
const intl base = 37LL;

map<intl,int> mp;

typedef int arr32[maxn];

intl ans,Has[maxn],ni[maxn],po[maxn];
arr32 H,wp,SA_,pas,rank,rank_,SA,pw,sumA,sumB,l;
char A[maxn],B[maxn],s[maxn],ss[maxn];
int n,m,len,top,T,t_;
int st[maxn][21];

intl fpm(intl a,intl b) {
    if (!a) return 0LL;
    intl ans = 1LL;
    for (; b; b >>= 1) {
	if (b & 1LL) ans *= a, ans %= Mo;
	a *= a; a %= Mo;
    }
    return ans;
}

bool judge(int *k,int a,int b,int c) {
    return (k[a] == k[b] && (k[a + c] == k[b + c]));
}

void get_suffix() {
    int i,j;
    for (i = 1; i <= max(len, 30); i++) rank[i] = rank_[i] = SA[i] = SA_[i] = wp[i] = 0;
    for (i = 1; i <= len; i++) rank[i] = s[i] - 'a' + 1;
    for (i = 1; i <= len; i++) wp[rank[i]]++;
    for (i = 1; i <= 30; i++) wp[i] += wp[i - 1];
    for (i = len; i; i--) SA[wp[rank[i]]--] = i;
    int u,q;
    for (q = 1; q < len; q <<= 1) {
	//memset(wp,0,sizeof(wp));
	for (i = 0; i <= max(len,30); i++) wp[i] = 0;
	for (i = 0; i <= len; i++) SA_[i] = SA[i];
	//memcpy(SA_,SA,sizeof(SA));
	for (i = 1; i <= len; i++) wp[rank[i]]++;
	for (i = 1; i <= max(len,30); i++) wp[i] += wp[i - 1];
	for (i = len; i; i--)
	    if (SA_[i] > q) SA[wp[rank[SA_[i] - q]]--] = SA_[i] - q;
	for (i = len - q + 1; i <= len; i++) SA[wp[rank[i]]--] = i;
	//memcpy(rank_,rank,sizeof(rank));
	for (i = 0; i <= len; i++) rank_[i] = rank[i];
	rank[SA[1]] = u = 1;
	for (i = 2; i <= len; i++) {
	    if (judge(rank_,SA[i],SA[i - 1],q)) rank[SA[i]] = u;
	    else rank[SA[i]] = ++u;
	}
    }
    
    for (i = 1; i <= max(len, 30); i++) rank_[i] = SA_[i] = wp[i] = 0; 
    for (i = 1; i <= max(len, 30); i++) sumA[i] = sumB[i] = 0;
}

void get_height() {
    for (int i = 1; i <= len; i++) H[i] = 0;
    for (int i = 1; i <= len; i++) {
	if (rank[i] == 1) { H[rank[i]] = 0; continue; }
	H[rank[i]] = max(H[rank[i - 1]] - 1, 0);
	while (s[i + H[rank[i]]] == s[SA[rank[i] - 1] + H[rank[i]]]) H[rank[i]]++;
    }
}

int get_(int L,int R) {
    if (L == R) return (len - SA[L] + 1);
    int k = pw[R - L];
    return min(st[R][k], st[L + (1 << k)][k]);
}

intl get_hash(int L,int R) {
    return ((Has[R] - Has[L - 1]) * ni[L] % Mo + Mo) % Mo;
}

void add_ans(int L,int R) {
    if (ss[L] == '#') return;
    L /= 2; R /= 2;
    int k = rank[L], len_ = R - L + 1;
    int l = 1, r = k;
    intl js = get_hash(L,R);
    if (mp[js]) return;
    mp[js] = 1;
    while (l < r) {
	int mid = (l + r) >> 1;
	if (get_(mid, k) >= len_) r = mid;
	else l = mid + 1;
    }
    int L_ = l;

    l = k, r = len;
    while (l < r) {
	int mid = (l + r + 1) >> 1;
	if (get_(k, mid) >= len_) l = mid;
	else r = mid - 1;
    }
    
    int R_ = l;

    ans += (intl) (sumA[R_] - sumA[L_ - 1]) * (intl) (sumB[R_] - sumB[L_ - 1]); 
}

void manacher() {
    for (int i = 1; i <= top; i++) l[i] = 0;
    l[1] = 1; int k = 1, r = 1;
    for (int i = 2; i <= top; i++) {
	l[i] = min(l[k * 2 - i], r - i + 1);
	while (ss[i + l[i]] == ss[i - l[i]] && (i - l[i] > 0)) {
	    l[i]++;
	    add_ans(i - l[i] + 1, i + l[i] - 1);
	}
	if (l[i] + i - 1 > r) {
	    r = l[i] + i - 1;
	    k = i;
	}
    }
}

void prepare() {
    for (int i = 1; i <= len; i++) st[i][0] = H[i];
    for (int i = 1; i <= len; i++)
	for (int j = 1; j <= 20; j++)
	    st[i][j] = 0;
    for (int j = 1; j <= 20; j++)
	for (int i = (1 << j); i <= len; i++)
	    st[i][j] = min(st[i][j - 1], st[i - (1 << (j - 1))][j - 1]);

    for (int i = 1; i <= len + 1; i++) sumA[i] = sumB[i] = 0;

    for (int i = 1; i <= n; i++) {
	sumA[rank[i]]++;
    }

    for (int i = n + 2; i <= len; i++)
	sumB[rank[i]]++;

    for (int i = 1; i <= len; i++)
	sumA[i] += sumA[i - 1], sumB[i] += sumB[i - 1];

    for (int i = 1; i <= n; i++) Has[i] = (Has[i - 1] + (intl) (A[i] - 'a' + 1) * po[i]) % Mo;
}

void init() {
    mp.clear();
    memset(H,0,sizeof(H));
    //clr(s); clr(ss); clr(l); clr(rank); clr(rank_); clr(SA); clr(SA_);
    //clr(st); clr(wp);

    top = n = m = len = ans = 0;
}

int main() {
    //freopen("G.in","r",stdin);
    //freopen("G.out","w",stdout);

    po[0] = 1LL;
    
    for (int i = 1; i <= 200000; i++)
	po[i] = (po[i - 1] * base) % Mo;

    for (int i = 0; (1 << i) <= 400000; i++) pw[1 << i] = i;

    for (int i = 1; i <= 400000; i++)
	pw[i] = pw[i] ? pw[i] : pw[i - 1];
    
    ni[200000] = fpm(po[200000],Mo - 2LL);

    for (int i = 200000 - 1; i >= 0; i--)
	ni[i] = (ni[i + 1] * base) % Mo;
    
    for (scanf("%d",&T); T; T--) {
	init();
	scanf("%s\n%s",A + 1,B + 1);
	n = strlen(A + 1); m = strlen(B + 1);
	for (int i = 1; i <= n; i++) s[i] = A[i];
	len = n;
	s[++len] = 'z' + 1;
	for (int i = 1; i <= m; i++) s[++len] = B[i];
	s[len + 1] = 0;
	get_suffix();
	get_height();
	//return 0;
	top = 0;
	for (int i = 1; i <= n; i++) {
	    ss[++top] = '#';
	    ss[++top] = A[i];
	}
	ss[++top] = '#';
	ss[top + 1] = 0;
	prepare();
	manacher();
	printf("Case #%d: %lld\n",++t_,ans);
    }
    return 0;  
}
