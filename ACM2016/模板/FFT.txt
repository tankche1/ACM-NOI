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
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * len必须去2的幂
 */
void change(complex y[],int len)
{
	int i,j,k;
	for(i = 1, j = len/2;i < len-1; i++)
	{
		if(i < j)swap(y[i],y[j]);
		//交换互为小标反转的元素，i<j保证交换一次
		//i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
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
 * 做FFT
 * len必须为2^k形式，
 * on==1时是DFT，on==-1时是IDFT
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
void getfft(int arg1[], int len1, int arg2[], int len2, int fft_out[])//模板：第一个数组，数组元素数量。 第二个数组，数组元素数量，输出数组
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
