# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<string>
# include<map>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n;
char s[maxn];
map<string,int> id;
string str;
int dp[maxn];
bool can[maxn][2];

int main(){
    scanf("%s",s);
    n=strlen(s);
    dp[n]=1;can[n][0]=can[n][1]=0;
    for(int i=n-2;i>=5;i--){
        if(dp[i+2]&&(s[i]!=s[i+2]||s[i+1]!=s[i+3]||can[i+2][1])){
            dp[i]=1;
            can[i][0]=1;
        }
        if(dp[i+3]&&(s[i]!=s[i+3]||s[i+1]!=s[i+4]||s[i+2]!=s[i+5]||can[i+3][0])){
            dp[i]=1;
            can[i][1]=1;
        }
        if(can[i][0]){
            str="";str+=s[i];str+=s[i+1];id[str]=1;
        }
        if(can[i][1]){
            str="";str+=s[i];str+=s[i+1];str+=s[i+2];id[str]=1;
        }
    }
    printf("%d\n",id.size());
    map<string,int> ::iterator it;
    for(it=id.begin();it!=id.end();it++){
        printf("%s\n",it->first.c_str());
    }
    return 0;
}
