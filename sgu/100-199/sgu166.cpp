# include<stdio.h>
# include<string.h>
# include<iostream>
# include<string>
# include<algorithm>
using namespace std;
struct Line{
    string s;
    Line *pre,*suc;
    Line(const string &_s,Line *_pre,Line *_suc):s(_s),pre(_pre),suc(_suc) {}
};
int main(){
    //freopen("input.txt","r",stdin);
    int p=0;
    Line *now=new Line(string(),0,0);
    Line *tmp;
    char t;
    while((t=getchar())&&t!='Q'){
           // putchar(t);
        if(t=='L'){
            if(p) p--;
        }
        else if(t=='R'){
            p++;
        }
        else if(t=='U'){
            if(now->pre) now=now->pre;
        }
        else if(t=='D'){
            if(now->suc) now=now->suc;
        }
        else if(t=='N'){
            if(p<now->s.length()){
                tmp=new Line(now->s.substr(p),now,now->suc);
                now->s.resize(p);
            }
            else tmp=new Line(string(),now,now->suc);
            if(tmp->suc) tmp->suc->pre=tmp;
            now->suc=tmp;now=tmp;
            p=0;
        }
        else if(t=='E'){
            p=now->s.length();
        }
        else if(t=='H'){
            p=0;
        }
        else if(t=='X'){
            if(p<now->s.length()){
                now->s.erase(p,1);
            }
            else if(tmp=now->suc){
                now->s.resize(p,' ');now->s+=tmp->s;now->suc=tmp->suc;
                if(tmp->suc) tmp->suc->pre=now;
                delete tmp;
            }
        }
        else if(t=='B'){
            if(p==0){
                if(tmp=now->pre){
                    p=tmp->s.length();
                    tmp->s+=now->s;
                    if(tmp->suc=now->suc) tmp->suc->pre=tmp;
                    delete now;
                now=tmp;
                }
            }
            else if(--p<now->s.length()){
                now->s.erase(p,1);
            }
        }
        else if(islower(t)||t==' '){
                //printf("hei");
            if(p>now->s.length()){
                now->s.resize(p,' ');
            }
                now->s.insert(now->s.begin()+p,t);
                p++;
        }
    }
    //cout << now->s;
    //puts("fuck");
    for(;now->pre;now=now->pre){
        //cout << now->s << '\n' ;
        //int aa;scanf("%d",&aa);
    }
    //puts("shit");
    for(;now;now=tmp)
        {
                cout << now->s;
                tmp=now->suc;
                delete now;
                if(tmp)
                        cout << '\n';
        }
    return 0;
}
