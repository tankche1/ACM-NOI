# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
char s1[110],s2[110];

int id(char *s){
    int n=strlen(s);
    if(strcmp(s,"monday")==0) return 1;
    else if(strcmp(s,"tuesday")==0) return 2;
    else if(strcmp(s,"wednesday")==0) return 3;
    else if(strcmp(s,"thursday")==0) return 4;
    else if(strcmp(s,"friday")==0) return 5;
    else if(strcmp(s,"saturday")==0) return 6;
    else if(strcmp(s,"sunday")==0) return 7;
}

int main(){
    scanf("%s",s1);
    scanf("%s",s2);
    int a=id(s1),b=id(s2);
    //printf("%d %d\n",a,b);
    int c=(b-a+7)%7;
    if(c==0||c==2||c==3) puts("YES");
    else puts("NO");
    return 0;
}
