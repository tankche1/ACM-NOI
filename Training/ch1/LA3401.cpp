# include<stdio.h>
# include<map>
# include<iostream>
# include<string.h>
# include<algorithm>
using namespace std;
map<string,int> id;
string s;
int n,col=0;
int cube[4][7];
int num[4][7];
int ans;

void rotate1(int cur){//right
    int t=num[cur][1];
    num[cur][1]=num[cur][5];num[cur][5]=num[cur][6];num[cur][6]=num[cur][2];num[cur][2]=t;
}

void rotate2(int cur){//up
    int t=num[cur][1];
    num[cur][1]=num[cur][4];num[cur][4]=num[cur][6];num[cur][6]=num[cur][3];num[cur][3]=t;
}

void rotate3(int cur){//L
    int t=num[cur][2];
    num[cur][2]=num[cur][4];num[cur][4]=num[cur][5];num[cur][5]=num[cur][3];num[cur][3]=t;
}

int tank=0;
void dfs(int cur){
    if(cur==n){
        int tot=0,same,tmp;
        for(int j=1;j<=6;j++){
            same=30;
            for(int i=0;i<n;i++){
                tmp=0;
                for(int k=0;k<n;k++){
                    if(num[k][j]!=num[i][j]){
                        tmp++;
                    }
                }same=min(same,tmp);
            }
            tot+=same;
        }
        /*printf("tank:%d\n",++tank);
        for(int i=0;i<n;i++){
            for(int j=1;j<=6;j++) printf("%d ",num[i][j]);puts("");
        }puts("################");*/


        ans=min(ans,tot);
        return;
    }

    //3
    for(int i=1;i<=6;i++) num[cur][i]=cube[cur][i];
    for(int p=0;p<4;p++){
        dfs(cur+1);rotate1(cur);
    }

    //1
    for(int i=1;i<=6;i++) num[cur][i]=cube[cur][i];
    rotate2(cur);
    for(int p=0;p<4;p++){
        dfs(cur+1);rotate1(cur);
    }

    //2
    for(int i=1;i<=6;i++) num[cur][i]=cube[cur][i];
    rotate3(cur);
    for(int p=0;p<4;p++){
        dfs(cur+1);rotate1(cur);
    }

    //4
    for(int i=1;i<=6;i++) num[cur][i]=cube[cur][i];
    rotate2(cur);rotate2(cur);
    for(int p=0;p<4;p++){
        dfs(cur+1);rotate1(cur);
    }

    //5
    for(int i=1;i<=6;i++) num[cur][i]=cube[cur][i];
    rotate3(cur);rotate3(cur);rotate3(cur);
    for(int p=0;p<4;p++){
        dfs(cur+1);rotate1(cur);
    }

    //6
    for(int i=1;i<=6;i++) num[cur][i]=cube[cur][i];
    rotate2(cur);rotate2(cur);rotate2(cur);
    for(int p=0;p<4;p++){
        dfs(cur+1);rotate1(cur);
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){
        id.clear();
        if(!n) break;
        for(int i=0;i<n;i++){
            for(int j=1;j<=6;j++){
                cin >> s;
                if(!id.count(s)) id[s]=++col;
                cube[i][j]=id[s];
            }
        }
        if(n==1) {puts("0");continue;}
        ans=1000;
        for(int i=1;i<=6;i++) num[0][i]=cube[0][i];
        dfs(1);
        printf("%d\n",ans);
    }
    return 0;
}
