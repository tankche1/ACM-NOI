# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;

int op;
int hour,minute;
char s[10];

int main(){
    scanf("%d",&op);
    scanf("%s",s);
    hour=(s[0]-'0')*10+s[1]-'0';
    minute=(s[3]-'0')*10+s[4]-'0';
    //printf("hour:%d minute:%d\n",hour,minute);
    int ans=0;
    if(op==24&&hour>=op) hour=s[1]-'0';
    else if(op==12){
        if(hour==0) hour=1;
        else if(hour>12){
            if(hour%10==0) hour=10;
            else hour=s[1]-'0';
        }
    }
    if(minute>=60) minute=s[4]-'0';
    if(hour<10) printf("0");printf("%d:",hour);
    if(minute<10) printf("0");printf("%d\n",minute);
    return 0;
}
