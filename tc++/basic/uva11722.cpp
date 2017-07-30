# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int t1,t2,s1,s2,wide,height;

double get_area(int w){
	int ly=t1+w,ry=t2+w;
	int ux=s2-w,dx=s1-w;
	bool on_left,on_right,on_up,on_down;
	on_down=on_left=on_right=on_up=false;
	if(ly>=s1&&ly<=s2) on_left=true;
	if(ry>=s1&&ry<=s2) on_right=true;
	if(ux>=t1&&ux<=t2) on_up=true;
	if(dx>=t1&&dx<=t2) on_down=true;
	if(on_left&&on_up) return (s2-ly)*(ux-t1)*0.5;
	if(on_left&&on_right) return (s2-ly+s2-ry)*wide*0.5;
	if(on_down&&on_up) return (dx-t1+ux-t1)*height*0.5;
	if(on_down&&on_right) return (dx-t1)*height+(t2-dx)*(s2-ry+height)*0.5;
	return ly<=s1?wide*height:0;
}

int main(){
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++) {
		int w;
		scanf("%d%d%d%d%d",&t1,&t2,&s1,&s2,&w);
		wide=t2-t1;height=s2-s1;
		double a1=get_area(w);
		double a2=get_area(-w);
		printf("Case #%d: %.6lf\n",kase,(a2-a1)/wide/height);
	}
	return 0;
}
