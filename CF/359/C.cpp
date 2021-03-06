# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL INF=3*(1e+18)+6;

int n;

LL px[maxn],py[maxn],pz[maxn];
LL ansA,ansB,ansC;

bool check(LL r){
    LL A,B,C;
    LL lA=-INF,rA=INF,lB=-INF,rB=INF,lC=-INF,rC=INF,lS=-INF,rS=INF;
    LL _lA=-INF,_rA=INF,_lB=-INF,_rB=INF,_lC=-INF,_rC=INF,_lS=-INF,_rS=INF;

    for(int i=1;i<=n;i++){
        lA=max(lA,-px[i]+py[i]+pz[i]-r);
        rA=min(rA,-px[i]+py[i]+pz[i]+r);
        lB=max(lB,px[i]-py[i]+pz[i]-r);
        rB=min(rB,px[i]-py[i]+pz[i]+r);
        lC=max(lC,px[i]+py[i]-pz[i]-r);
        rC=min(rC,px[i]+py[i]-pz[i]+r);
        lS=max(lS,px[i]+py[i]+pz[i]-r);
        rS=min(rS,px[i]+py[i]+pz[i]+r);
    }

    lS=max(lS,lA+lB+lC);
    rS=min(rS,rA+rB+rC);

    /*if(r==0){
        printf("lA:%lld rA:%lld lB:%lld rB:%lld lC:%lld rC:%lld lS:%lld rS:%lld\n",lA,rA,lB,rB,lC,rC,lS,rS);
    }*/

    if(lA>rA) return false;
    if(lB>rB) return false;
    if(lC>rC) return false;
    if(lS>rS) return false;

    for(int c=0;c<2;c++){
        if(lA-c>=0) _lA=(lA-c+1)/2;else _lA=(lA-c)/2;
        if(rA-c<0) _rA=(rA-c-1)/2;else _rA=(rA-c)/2;
        if(lB-c>=0) _lB=(lB-c+1)/2;else _lB=(lB-c)/2;
        if(rB-c<0) _rB=(rB-c-1)/2;else _rB=(rB-c)/2;
        if(lC-c>=0) _lC=(lC-c+1)/2;else _lC=(lC-c)/2;
        if(rC-c<0) _rC=(rC-c-1)/2;else _rC=(rC-c)/2;
        if(lS-3*c>=0) _lS=(lS-3*c+1)/2;else _lS=(lS-3*c)/2;
        if(rS-3*c<0) _rS=(rS-3*c-1)/2;else _rS=(rS-3*c)/2;

        /*if(r==1077719544343832544){
            printf("fucklA:%lld rA:%lld lB:%lld rB:%lld lC:%lld rC:%lld lS:%lld rS:%lld\n",_lA,_rA,_lB,_rB,_lC,_rC,_lS,_rS);
        }*/

        if(_lA>_rA) continue;
        if(_lB>_rB) continue;
        if(_lC>_rC) continue;
        if(_lS>_rS) continue;

        A=_lA;B=_lB;C=_lC;
        if(A+B+C>_rS) continue;
        if(A+B+C<_lS){
            A+=min(_rA-A,_lS-(A+B+C));
        }
        if(A+B+C<_lS){
            B+=min(_rB-B,_lS-(A+B+C));
        }
        if(A+B+C<_lS){
            C+=min(_rC-C,_lS-(A+B+C));
        }

        //if(r==1077719544343832544) printf("A+B+C-_lS:%lld\n",A+B+C-_lS);
        if(A+B+C<_lS) continue;
        A=2*A+c;B=2*B+c;C=2*C+c;
        ansA=(B+C)/2;
        ansB=(A+C)/2;
        ansC=(A+B)/2;
        return true;

    }
    return false;

}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%lld%lld%lld",&px[i],&py[i],&pz[i]);

        LL L=0,R=INF,M;
        while(L<=R){
            M=(L+R)>>1;
            if(check(M)) R=M-1;
            else L=M+1;
        }

        check(R+1);
        //rintf("R:%lld\n",R+1);
        printf("%lld %lld %lld\n",ansA,ansB,ansC);
    }
    return 0;
}
