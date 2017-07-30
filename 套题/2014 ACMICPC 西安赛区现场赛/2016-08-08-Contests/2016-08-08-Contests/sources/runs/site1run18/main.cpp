// by ztx

#include <cstdio>
#define Rep(i,l,r) for(i=(l);i<=(r);i++)
#define rep(i,l,r) for(i=(l);i< (r);i++)
#define Rev(i,r,l) for(i=(r);i>=(l);i--)
#define rev(i,r,l) for(i=(r);i> (l);i--)
typedef long long ll ;
typedef double lf ;
int CH , NEG ;
template <typename TP>inline void read(TP& ret) {
    ret = NEG = 0 ; while (CH=getchar() , CH<'!') ;
    if (CH == '-') NEG = true , CH = getchar() ;
    while (ret = ret*10+CH-'0' , CH=getchar() , CH>'!') ;
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

#define  maxn  110LL

int n;

int main() {
//   #define READ
    #ifdef  READ
        freopen("data.in" ,"r",stdin ) ;
        freopen("me.out","w",stdout) ;
    #endif
    int T,kiss,a,ok,i;
    read(T);
    Rep (kiss,1,T) {
        read(n);
        ok = true ;
        Rep (i,1,n) {
            read(a);
            if (a%3!=0) ok = false ;
        }
        printf("Case #%d: %s\n",kiss,ok?"Yes":"No");
    }
    #ifdef  READ
        fclose(stdin) ; fclose(stdout) ;
    #else
        getchar() ; getchar() ;
    #endif
    return 0 ;
}
