#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>
#include<string>
#define maxn 150
using namespace std;
map<string,bool>M;
string s[maxn];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        char c=getchar();
        int cnt=0;
        c=getchar();
        while(c!='\n')
        {
            if(c==' ') cnt++;
            else s[cnt]+=c;
            c=getchar();
        }
        string str="";
        while(c!='?')
        {
            c=getchar();
            if(c==' ') str="";
            else if(c=='\n') {M[str]=true;str="";}
            else str+=c;
        }
        int i=0;
        while(M.count(s[i])&&i<=cnt) i++;
        cout<<s[i];
        for(++i;i<=cnt;++i)
            if(!M.count(s[i])) cout<<' '<<s[i];
        cout<<endl;
        for(int i=0;i<=cnt;++i) s[i]="";
        M.clear();
    }
}
