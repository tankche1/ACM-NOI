# include<stdio.h>
# include<string.h>
# include<map>
# include<algorithm>
using namespace std;
char s[2000010];
map<unsigned long long, pair<int,int> > key;
int mod=127;
int pos;

int id(char c){
    if(c>='0'&&c<='9') return c-'0'+1;
    if(c>='a'&&c<='z') return 10+c-'a'+1;
    if(c>='A'&&c<='Z') return 36+c-'A'+1;
    if(c=='.') return 63;
    return 64;
}

void solve(unsigned long long hash){
    int L,R;
    unsigned long long tmp=hash;
    while(s[pos]!='}'){
        tmp=hash;
        pos++;
        if(s[pos]=='}') return;
        while(s[pos]!=':') tmp=tmp*mod+id(s[pos]),pos++;
        pos++;L=pos;
        if(s[pos]=='{')
            solve(tmp*mod+id('.'));
        else{
            while(s[pos+1]!=','&&s[pos+1]!='}') pos++;
        }
        key[tmp]=make_pair(L,pos);
        //printf("L:%d R:%d\n",L,pos);
        //for(int i=L;i<=pos;i++) printf("%c",s[i]);puts("");
        pos++;
    }
}

char s2[200010];
int n,m;
int main(){
    unsigned long long hash;
    int T,q,L,R;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        key.clear();
        scanf("%s",s);
        pos=0;solve(0);
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            scanf("%s",s2);
            m=strlen(s2);hash=0;
            for(int j=0;j<m;j++)
                hash=hash*mod+id(s2[j]);
            if(!key.count(hash)) puts("Error!");
            else{
                L=key[hash].first;R=key[hash].second;
                for(int i=L;i<=R;i++) printf("%c",s[i]);puts("");
            }
        }
    }
    return 0;
}
