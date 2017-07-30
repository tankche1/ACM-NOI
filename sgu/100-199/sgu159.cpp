# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int b,n;
int s[2010];
int cnt=0;


void dfs(int cur,int yu,bool flag){
    //printf("cur:%d s[%d]:%d\n",cur,cur-1,s[cur-1]);
    if(cur==n){
        if(s[cur-1]==0&&n!=1) return;
        if(flag==1){
             for(int i=n-1;i>=0;i--){
                 if(s[i]<=9) printf("%d",s[i]);
                 else printf("%c",'A'+s[i]-10);
             }
             puts("");
        }
        else cnt++;
        return;
    }
    for(int i=cur-1;i>0;i--){
        yu+=s[i]*s[cur-i];
    }
   /* for(int i=cur-1;i>=0;i--){
            if(s[i]<=9) printf("%d",s[i]);
            else printf("%c",'A'+s[i]-10);
        }
        puts("");
    printf("yu:%d\n",yu);*/
    for(int i=0;i<b;i++){
        if((i*s[0]*2+yu)%b==i){
            s[cur]=i;
            dfs(cur+1,(i*s[0]*2+yu)/b,flag);
        }
    }
    return;
}
int main(){
    scanf("%d%d",&b,&n);
    for(int i=0;i<b;i++){
        if(((i*i)%b)==i){
            s[0]=i;
            dfs(1,i*i/b,0);
        }
    }
    printf("%d\n",cnt);
     for(int i=0;i<b;i++){
        if(((i*i)%b)==i){
            s[0]=i;
            dfs(1,i*i/b,1);
        }
    }
    return 0;
}
