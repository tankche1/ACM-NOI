# include<stdio.h>
# include<string.h>
# include<iostream>
# include<math.h>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const double PI = acos(-1.0);
const int maxn = 1200*1200;
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
void getfft(double arg1[], int len1, double arg2[], int len2, double fft_out[])//ģ�壺��һ�����飬����Ԫ�������� �ڶ������飬����Ԫ���������������
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
		fft_out[i] = ((x1[i].r));
}

double fft_a[maxn],fft_b[maxn],fft_c[maxn];


int n,m,r,N,M,S;
double R;
int p[510][510];

int main(){
    double dis;
    while(scanf("%d%d%lf",&n,&m,&R)!=EOF){
        r=0;
        while(r<R) r++;
        N=n+2*r;M=m+2*r;S=M;
        for(int i=0;i<(n-1)*S+m;i++) fft_a[i]=0;
        for(int i=0;i<2*r*S+r+r+1;i++) fft_b[i]=0;

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                scanf("%d",&p[i][j]);
            }
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                fft_a[i*S+j]=p[i][j];
            }
        }

        for(int i=-r;i<=r;i++){
            for(int j=-r;j<=r;j++){
                if(i*i+j*j<R*R){
                    dis=sqrt(i*i+j*j);
                    fft_b[(i+r)*S+(j+r)]=(double)1/(dis+1);
                }
            }
        }

        getfft(fft_a,(n-1)*S+m,fft_b,2*r*S+r+r+1,fft_c);

        double ans=0,result;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                result=fft_c[(i+r)*S+j+r];
                ans=max(ans,result);
            }
        }
        printf("%.3lf\n",ans);
    }
    return 0;
}
