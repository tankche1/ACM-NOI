# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

const char* mahjong[] = {
"1T","2T","3T","4T","5T","6T","7T","8T","9T",
"1S","2S","3S","4S","5S","6S","7S","8S","9S",
"1W","2W","3W","4W","5W","6W","7W","8W","9W",
"DONG","NAN","XI","BEI",
"ZHONG","FA","BAI"
};

int val[35];

int code(char *s){
    for(int i=0;i<34;i++)
        if(strcmp(mahjong[i],s)==0) return i;
    return -1;
}

bool dfs(int num,int cur){
    if(num==0){
        return true;
    }
    for(int i=cur;i<34;i++){
        if(val[i]>0){
            if(val[i]>=3){
                val[i]-=3;
                if(dfs(num-3,i)) {val[i]+=3;return true;}
                val[i]+=3;
            }
            if(val[i+1]>0&&val[i+2]>0){
                if((i>=0&&i<=6)||(i>=9&&i<=15)||(i>=18&&i<=24)){
                    val[i]--;val[i+1]--;val[i+2]--;
                    if(dfs(num-3,i)) {val[i]++;val[i+1]++;val[i+2]++;return true;}
                    val[i]++;val[i+1]++;val[i+2]++;
                }
            }
            break;
        }
    }
    return false;
}

bool solve(){
    for(int i=0;i<34;i++){
        if(val[i]>=2){
            val[i]-=2;
            if(dfs(12,0)) {val[i]+=2;return true;}
            val[i]+=2;
        }
    }
    return false;
}

int main(){
    char s[100];
    int t;
    int tcase=0;
    while(1){
        bool ok=true;
        memset(val,0,sizeof(val));
        for(int i=1;i<=13;i++){
            scanf("%s",s);
            t=code(s);if(t==-1) return 0;
            //printf("t:%d\n",t);
            val[t]++;
        }
        printf("Case %d:",++tcase);
        /*for(int i=0;i<34;i++){
            if(val[i]>0) printf("%s %d\n",mahjong[i],val[i]);
        }*/
        for(int i=0;i<34;i++){
            //if(val[i]>0) printf("%s %d\n",mahjong[i],val[i]);
            if(val[i]<4){
                val[i]++;
                if(solve()) printf(" %s",mahjong[i]),ok=false;
                val[i]--;
            }
        }
        if(ok) printf(" Not ready");
        puts("");
    }
    return 0;
}
