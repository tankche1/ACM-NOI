# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
# include<vector>
using namespace std;
int lenA,lenB;
int A[50],B[50];
vector<int> ansB;

bool cmp(int a,int b){
    if((a%10)!=(b%10)) return (a%10)<(b%10);
    return a<b;
}
int main(){
   // freopen("in.txt","r",stdin);
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
            scanf("%d%d",&lenA,&lenB);
            for(int i=0;i<lenA;i++) scanf("%d",&A[i]);
            for(int i=0;i<lenB;i++) scanf("%d",&B[i]);
            sort(A,A+lenA);sort(B,B+lenB);
            sort(A,A+lenA);sort(B,B+lenB);
            lenA=unique(A,A+lenA)-A;
            lenB=unique(B,B+lenB)-B;
            int tpa=lenA-1,tpb=lenB-1,ans=0,tot,pos1,pos2;
            ansB.clear();
            while(tpa>=0&&tpb>=0){
                while(1){
                    if(tpa>=0&&A[tpa]>B[tpb]) tpa--;
                   if(tpb>=0&&A[tpa]<B[tpb]) tpb--;
                   if(tpa<0||tpb<0) break;
                    if(A[tpa]==B[tpb]) break;
                }
               tot=0;
               while(tpa>=0&&tpb>=0&&A[tpa]==B[tpb]) tot++,tpa--,tpb--;
               if(tot>ans) ans=tot,pos1=tpa+1,pos2=tpb+1;
            }
            if(ans==0) {puts("NONE");continue;}
            else{
                printf("%d",A[pos1+ans-1]);
                for(int i=pos1+ans-2;i>=pos1;i--) printf(" %d",A[i]);puts("");
                ansB.push_back(B[pos2]);
                for(int i=1;i<ans;i++) ansB.push_back(B[++pos2]);
            }
            sort(ansB.begin(),ansB.end(),cmp);
            printf("%d",ansB[0]);
            for(int i=1;i<ansB.size();i++) printf(" %d",ansB[i]);puts("");
    }
    return 0;
}
