# include<stdio.h>
# include<string.h>
# include<algorithm>
# include<vector>
using namespace std;

int n,a,b;
struct computer
{
  int bh,w,soc;
}com[4][10010];
int num[4];

bool cmp(computer a,computer b){
return a.w<b.w;
}
vector<int> ans1,ans2;
int main()
{
//freopen("in.txt","r",stdin);
int t,ww;int aaa,bbb;
int aaaa;
    scanf("%d%d%d",&n,&a,&b);aaa=a;bbb=b;aaaa=a;
    num[0]=num[1]=num[2]=num[3]=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&t,&ww);
        com[t][++num[t]].w=ww;com[t][num[t]].bh=i;
    }
    int ans=0,totw=0;
    int aa=a,bb=b;
    ans+=min(aa,num[1]);aa-=min(aa,num[1]);
    ans+=min(bb,num[2]);bb-=min(bb,num[2]);
    ans+=min(aa+bb,num[3]);
    sort(com[1]+1,com[1]+num[1]+1,cmp);
    sort(com[2]+1,com[2]+num[2]+1,cmp);
    sort(com[3]+1,com[3]+num[3]+1,cmp);
    int pos1=0,pos2=0,pos3=0;
    while(a>0&&pos1<num[1]){
    pos1++;totw+=com[1][pos1].w;a--;
    }
    while(b>0&&pos2<num[2]){
    pos2++;totw+=com[2][pos2].w;b--;
    }
    while(a>0&&pos3<num[3]){
    a--;pos3++;totw+=com[3][pos3].w;com[3][pos3].soc=1;
    }
    while(b>0&&pos3<num[3]){
    b--;pos3++;totw+=com[3][pos3].w;com[3][pos3].soc=2;
    }
   // printf("pos1:%d pos2:%d pos3:%d\n",pos1,pos2,pos3);
  //   printf("ans1size:%d ans2size:%d\n",(int)ans1.size(),(int)ans2.size());
    while(pos3<num[3]){
        if(pos1>0&&(pos2==0||(pos1>0&&com[1][pos1].w>=com[2][pos2].w))&&com[3][pos3+1].w<=com[1][pos1].w){
            //printf("change 1 to 3\n");
            pos3++;totw+=com[3][pos3].w;totw-=com[1][pos1].w;pos1--;com[3][pos3].soc=1;
        }
        else if(pos2>0&&(pos1==0||(pos2>0&&com[2][pos2].w>=com[1][pos1].w))&&com[3][pos3+1].w<=com[2][pos2].w){
         //printf("change 2 to 3\n");
        pos3++;totw+=com[3][pos3].w;totw-=com[2][pos2].w;pos2--;com[3][pos3].soc=2;
        }
        else break;
    }
    //printf("pos1:%d pos2:%d pos3:%d\n",pos1,pos2,pos3);
    printf("%d %d\n",ans,totw);
    for(int i=1;i<=pos1;i++){
    ans1.push_back(com[1][i].bh);
   // printf("1\n");
    }
    for(int i=1;i<=pos2;i++)
    ans2.push_back(com[2][i].bh);
    for(int i=1;i<=pos3;i++){
    t=com[3][i].soc;
    if(t==1) ans1.push_back(com[3][i].bh);//,printf("3 to 1\n");
    else ans2.push_back(com[3][i].bh);
    }
    //printf("ans1size:%d ans2size:%d\n",(int)ans1.size(),(int)ans2.size());
    for(int i=0;i<(int)ans1.size();i++)
    printf("%d %d\n",ans1[i],i+1);
    for(int i=0;i<(int)ans2.size();i++){
            //printf("i:%d\n",i);
    printf("%d %d\n",ans2[i],i+aaaa+1);
    }
    return 0;
}
