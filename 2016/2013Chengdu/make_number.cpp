# include<stdio.h>
# include<string.h>
# include<vector>
# include<time.h>
# include<algorithm>
using namespace std;
char s[3][20];

int get(){
    int a=rand()%10+1;
    if(a==0) return 0;
    if(a>7) return 2;
    return 1;
}

int main(){
    srand(time(NULL));
    s[0][0]='Y';s[0][1]='E';s[0][2]='S';s[0][3]='\0';
    s[1][0]='N';s[1][1]='O';s[1][2]='\0';
    s[2][0]='E';s[2][1]='R';s[2][2]='R';s[2][3]='O';s[2][4]='R';s[2][3]='\0';
    //s[2]="ERROR";
    int Tcase=5;
    printf("%d\n",Tcase);
    for(int i=1;i<=Tcase;i++){
        int n=1000,m=5,cnt=50;
        printf("%d %d %d %d\n",n,m,200,300);
        for(int i=1;i<=n;i++){
            printf("%c %c %d %s\n",'A'+rand()%cnt,'A'+rand()%m,rand()%300,s[get()]);
        }
    }
    return 0;
}
