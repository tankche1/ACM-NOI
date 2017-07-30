// by ztx

#include <cstdio>
#define Rep(i,l,r) for(i=(l);i<=(r);i++)
#define rep(i,l,r) for(i=(l);i< (r);i++)
#define Rev(i,r,l) for(i=(r);i>=(l);i--)
#define rev(i,r,l) for(i=(r);i> (l);i--)
typedef long long ll ;
typedef unsigned uint;
typedef double lf ;
int CH , NEG ;
template <typename TP>inline void read(TP& ret) {
    ret = NEG = 0 ; while (CH=getchar() , CH<'!') ;
    if (CH == '-') NEG = true , CH = getchar() ;
    while (ret = ret*10+CH-'0' , CH=getchar() , CH>'!'  &&  CH!='.' && CH!='/') ;/// !!!
    if (NEG) ret = -ret ;
}
template <typename TP>inline void readc(TP& ret) {
    while (ret=getchar() , ret<'!') ;
    while (CH=getchar() , CH>'!') ;
}
template <typename TP>inline void reads(TP *ret) {
    ret[0]=0;while (CH=getchar() , CH<'!') ;
    while (ret[++ret[0]]=CH,CH=getchar(),CH>'!') ;
    ret[ret[0]+1]=0;
}

struct node {
    node*lc,*rc;
    bool flag;
    inline void init();
}nodes[9000010LL],*null,*root;
int tott;
inline void node::init() {
    lc = rc = null; flag=0;
}
inline node* newnode() {
    tott ++ ; return &nodes[tott];
}

int n,a,b,c,d,l;
bool bits[35];
int ans = 0;
uint ansb[30010LL];
int ansl[30010LL];

inline void insert(node*&o,int dep,int len) {
    if (o == null) o = newnode(), o->init();
    if (o->flag) return ;
    if (dep == len) {o->flag = true;return;}
    if (bits[dep+1] == 0) insert(o->lc,dep+1,len);
    else insert(o->rc,dep+1,len);
}

inline void query(node*o,int dep,uint ans) {
    if (o->flag) return;
    if (o == null) {
        ::ans ++;
        ansb[::ans] = ans;
        ansl[::ans] = dep;
        return;
    }
    query(o->lc,dep+1,ans<<1);
    query(o->rc,dep+1,(ans<<1)|1);
}

int aa,bb,cc,dd;
inline void print(uint sta,int len) {
    sta <<= (32-len);
    dd = sta&15;sta >>= 8;
    cc = sta&15;sta >>= 8;
    bb = sta&15;sta >>= 8;
    aa = sta;
    printf("%d.%d.%d.%d/%d\n",aa,bb,cc,dd,len);
}

int main() {
//   #define READ
    #ifdef  READ
        freopen("data.in" ,"r",stdin ) ;
        freopen("me.out","w",stdout) ;
    #endif
    int T,kiss,i,j,ok;
    read(T);
    null = &nodes[0];
    null->init();
    Rep (kiss,1,T) {
        printf("Case #%d:\n",kiss);
        read(n);
        if (!n) {
            puts("0.0.0.0/0");
            continue;
        }
        tott = 0;
        root = null;
        ok = true;
        Rep (j,1,n) {
            read(a),read(b),read(c),read(d),read(l);
            if (!l) ok = false;
            if (ok) {
                Rep (i,1,8) {
                    bits[i] = a&(1<<(8-i));
                    bits[i+8] = b&(1<<(8-i));
                    bits[i+16] = c&(1<<(8-i));
                    bits[i+24] = d&(1<<(8-i));
                }
//Rep (i,1,32)printf("%d",bits[i]);
//puts("");
                insert(root,0,l);
            }
        }
        if (ok) {
            ans = 0;
            query(root,0,0);
            printf("%d\n", ans);
            Rep (i,1,ans) print(ansb[i],ansl[i]);
        } else puts("0");
    }
    #ifdef  READ
        fclose(stdin) ; fclose(stdout) ;
    #else
        getchar() ; getchar() ;
    #endif
    return 0 ;
}
