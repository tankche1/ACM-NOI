# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
char s[1000010];
bool content;
int n;

void space(int num){
    for(int i=1;i<=num;i++) printf(" ");
}
void jump(int &pos){
    while(pos<n&&(s[pos]==32||s[pos]==9||s[pos]==10)) pos++;
}

int main(){
    //freopen("in.txt","r",stdin);
    int Case,pos;
    scanf("%d\n",&Case);
    pos=n=0;
    for(int Tcase=1;Tcase<=Case;Tcase++){
        int in=0;content=false;
        printf("Case #%d:\n",Tcase);
        while(1){
            //printf("pos:%d\n",pos);
            if(pos>=n) {gets(s);n=strlen(s);pos=0;}
            while(pos<n&&((s[pos]!='<')||(s[pos+1]!='h')||(s[pos+2]!='t')||(s[pos+3]!='m')||(s[pos+4]!='l')||(s[pos+5]!='>'))) {

                /*if(pos==5) {
                    printf("%s\n",s+pos);
                    printf("%d\n",((s[pos]!='<')||(s[pos+1]!='h')||(s[pos+2]!='t')||(s[pos+3]!='m')||(s[pos+4]!='l')||(s[pos+5]!='>')));
                    printf("%d %d %d %d %d %d\n",s[pos]!='<',s[pos+1]!='h',s[pos+2]!='t',s[pos+3]!='m',s[pos+4]!='l',s[pos+5]!='>');
                }*/
                pos++;
            }
            if(pos>=n) continue;
            else break;
        }

        while(1){
            if(pos>=n) {gets(s);n=strlen(s);pos=0;}

            jump(pos);if(pos>=n) continue;
            if(s[pos]=='<'){
                //<br/>
                pos++;//jump(pos);//if(pos>=n) continue;
                if(s[pos]=='b'&&s[pos+1]=='r'&&s[pos+2]=='/'){
                    if(content) {puts("");content=false;}
                    space(in);
                    puts("<br/>");
                    pos+=4;
                }
                else if(s[pos]=='/'){
                    if(content) {puts("");content=false;}
                    in--;
                    space(in);
                    printf("<");
                    while(s[pos]!='>') printf("%c",s[pos]),pos++;
                    printf("%c\n",s[pos]);pos++;
                }
                else{//if(s[pos]!='/'){
                    if(content) {puts("");content=false;}
                    space(in);
                    in++;
                    printf("<");
                    while(s[pos]!='>') printf("%c",s[pos]),pos++;
                    printf("%c\n",s[pos]);
                    if(s[pos-1]=='/') in--;
                    pos++;
                }

            }
            else{
                if(content){
                    printf(" ");
                    while(pos<n&&s[pos]!='<'&&s[pos]!=32&&s[pos]!=9&&s[pos]!=10){
                        printf("%c",s[pos]);pos++;
                    }
                }
                else{
                    content=true;
                    space(in);
                    while(pos<n&&s[pos]!='<'&&s[pos]!=32&&s[pos]!=9&&s[pos]!=10){
                        printf("%c",s[pos]);pos++;
                    }
                }
            }
            if(in==0) {
                //while(pos<=n&&(s[pos]!='<'||s[pos+1]!='h'||s[pos+2]!='t'||s[pos+3]!='m'||s[pos+4]=='l'||s[pos+5]!='>')) pos++;
                break;
            }

        }
    }
    return 0;
}
