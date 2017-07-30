/*
找到第一个i使得m+1<fib[i]
答案就是m-fib[i-2]
*/
# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int bit=100000;
const int bit_num=5;
typedef long long LL;

struct Big{
	LL a[250];
	int len;
	void init() {len=1;memset(a,0,sizeof(a));}
	void get(char *s){
		len=0;
		int n=strlen(s),tmp;
		for(int i=n-1;i>=0;i-=bit_num){
			tmp=0;
			for(int j=max(0,i-bit_num+1);j<=i;j++)
				tmp=tmp*10+s[j]-'0';
			a[len++]=tmp;
		}
	}

	void print(){
		printf("%lld",a[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%05lld",a[i]);puts("");
	}
};

Big C;
Big operator + (Big A, Big B){
	int n=max(A.len,B.len);
	C.init();
	for(int i=0;i<n;i++)
		C.a[i]=A.a[i]+B.a[i];
	for(int i=0;i<n;i++)
		if(C.a[i]>=bit) C.a[i]-=bit,C.a[i+1]++;
	C.len=n;
	if(C.a[C.len]) C.len++;
	return C;
}

Big operator - (Big A,Big B){
	C.init();
	C.len=A.len;
	for(int i=0;i<C.len;i++)
        C.a[i]=A.a[i]-B.a[i];
    for(int i=0;i<C.len;i++){
        if(C.a[i]<0) C.a[i]+=bit,C.a[i+1]--;
    }
    while(C.len>1&&C.a[C.len-1]==0) C.len--;
    return C;
}

bool operator < (Big A,Big B){
	if(B.len>A.len) return true;
	if(A.len>B.len) return false;
	for(int i=A.len-1;i>=0;i--){
		if(A.a[i]>B.a[i]) return false;
		else if(A.a[i]<B.a[i]) return true;
	}
	return false;
}
Big feb[1010];
Big m,one,ans;
char s[1010];
int n;

int main(){
   // freopen("1009.in","r",stdin);
    one.init();one.a[0]=1;
    feb[1].init();feb[2].init();
    feb[1].a[0]=1;feb[2].a[0]=1;
    for(int i=3;i<=1005;i++){
        feb[i]=feb[i-1]+feb[i-2];

            //printf("i:%d\n",i);
           // feb[i].print();

    }
    int tcase,pos;
    scanf("%d\n",&tcase);
    while(tcase--){
        m.init();ans.init();
        scanf("%d ",&n);
        scanf("%s",s);
        m.get(s);
        m=m+one;
        //m.print();
        for(int i=1;i<=1005;i++)
            if((m<feb[i])) {pos=i;break;}
        //printf("pos:%d\n",pos);
        m=m-one;
        ans=m-feb[pos-2];
        //ans.print();
        LL print=0;
        for(int i=ans.len-1;i>=0;i--){
            print=print*bit+ans.a[i];print%=258280327;
        }
        printf("%I64d\n",print);
    }
    return 0;
}
