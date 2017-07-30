# include<stdio.h>
# include<math.h>
# include<string.h>
# include<algorithm>
using namespace std;

const double PI = acos(-1.0);
const int maxn = 100010 *4;
const int mod=313;
struct complex
{
	double r,i;
	complex(double _r = 0.0,double _i = 0.0)
	{
		r = _r; i = _i;
	}
	complex operator +(const complex &b)
	{
		return complex(r+b.r,i+b.i);
	}
	complex operator -(const complex &b)
	{
		return complex(r-b.r,i-b.i);
	}
	complex operator *(const complex &b)
	{
		return complex(r*b.r-i*b.i,r*b.i+i*b.r);
	}
};
/*
 * ����FFT��IFFTǰ�ķ�ת�任��
 * λ��i�� ��i�����Ʒ�ת��λ�ã�����
 * len����ȥ2����
 */
void change(complex y[],int len)
{
	int i,j,k;
	for(i = 1, j = len/2;i < len-1; i++)
	{
		if(i < j)swap(y[i],y[j]);
		//������ΪС�귴ת��Ԫ�أ�i<j��֤����һ��
		//i��������+1��j��ת���͵�+1,ʼ�ձ���i��j�Ƿ�ת��
		k = len/2;
		while( j >= k)
		{
			j -= k;
			k /= 2;
		}
		if(j < k) j += k;
	}
}
/*
 * ��FFT
 * len����Ϊ2^k��ʽ��
 * on==1ʱ��DFT��on==-1ʱ��IDFT
 */
void fft(complex y[],int len,int on)
{
	change(y,len);
	for(int h = 2; h <= len; h <<= 1)
	{
		complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
		for(int j = 0;j < len;j+=h)
		{
			complex w(1,0);
			for(int k = j;k < j+h/2;k++)
			{
				complex u = y[k];
				complex t = w*y[k+h/2];
				y[k] = u+t;
				y[k+h/2] = u-t;
				w = w*wn;
			}
		}
	}
	if(on == -1)
		for(int i = 0;i < len;i++)
			y[i].r /= len;
}

complex x1[maxn], x2[maxn];
void getfft(int arg1[], int len1, int arg2[], int len2, int fft_out[])//ģ�壺��һ�����飬����Ԫ�������� �ڶ������飬����Ԫ���������������
{
	int len = 1;
	while(len < len1*2 || len < len2*2)len<<=1;
	for(int i = 0;i < len1;i++)
		x1[i] = complex(arg1[i] , 0);
	for(int i = len1;i < len;i++)
		x1[i] = complex(0 , 0);
	for(int i = 0;i < len2;i++)
		x2[i] = complex(arg2[i] , 0);
	for(int i = len2;i < len;i++)
		x2[i] = complex(0, 0);
	fft(x1,len,1);
	fft(x2,len,1);
	for(int i = 0;i < len;i++)
		x1[i] = x1[i]*x2[i];
	fft(x1,len,-1);
	for(int i = 0;i < len;i++)
		fft_out[i] = ((int)(x1[i].r+0.5));
}

int n;
int a[maxn];
int f[maxn];

int fft_a[maxn],fft_b[maxn],fft_c[maxn];

void solve(int l,int r){
    if(l==r){
        f[l]=(f[l]+a[l])%mod;
        return;
    }

    int mid=(l+r)>>1;
    solve(l,mid);
    int l1=mid-l+1,l2=r-l;
    //for(int i=0;i<mid-l+1;i++) fft_a[i]=f[i+mid+1];
    //for(int i=0;i<l2;i++) fft_b[i]=a[i+1];

    getfft(&f[l],l1,&a[1],l2,fft_c);

    for(int i=mid+1;i<=r;i++){
        f[i]=(f[i]+fft_c[mid-l+i-(mid+1)])%mod;
    }
    solve(mid+1,r);
}

int main(){
    //printf("%.1lf\n",1.56);
    while(scanf("%d",&n)!=EOF){
        if(n==0) break;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),a[i]%=mod;
        for(int i=1;i<=n;i++) f[i]=0;
        solve(1,n);
        printf("%d\n",f[n]);
    }
    return 0;
}
