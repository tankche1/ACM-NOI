# include<stdio.h>
# include<string.h>
int B[2010];

struct Big{
	int A[2010],Len;
	void get(char *s,int n){
		Len=n;
		for(int i=0;i<n;i++) A[i]=s[i]-'0';
	}
	
	void divide(int a){
		int j=0,t=0,i;
		for(i=0;i<Len;i++){
			t=t*10+A[i];
			if(t>=a) break;
		}
		for(;i<Len;i++){
			B[j++]=t/a;t=t%a;
			t=t*10+A[i+1];
		}
		Len=j;
		for(int i=0;i<Len;i++) A[i]=B[i];
	}
	
	void minus(int a){
		int i,j;
		for(int i=0;i<Len;i++) B[i]=A[i];
		B[Len-1]=B[Len-1]-a;
		for(j=Len-1;j>=0;j--)
			if(B[j]<0) B[j]+=10,B[j-1]--;
			else break;
		for(j=0;j<Len;j++)
			if(B[j]!=0) break;
		for(i=0;j<Len;j++,i++)
			A[i]=B[j];
		Len=i;
	}
	
	void print(){
		for(int i=0;i<Len;i++){
			printf("%d",A[i]);
		}
		puts("");
	}
}N;
char s[2010];
int len;

int main()
{
	freopen("china.in","r",stdin);
	freopen("china.out","w",stdout);
	int end_two=0;
	scanf("%s",s);
	len=strlen(s);
	N.get(s,len);
	//N.print();
	if(N.A[len-1]%2==1){
		N.divide(2);
	}
	else{
		if(len>1) end_two=N.A[len-2]*10;
		end_two+=N.A[len-1];
		if(end_two%4==0){
			N.divide(2);//N.print();
			N.minus(1);
		}
		else{
			N.divide(2);N.minus(2);
		}
	}
	N.print();
	return 0;
}
