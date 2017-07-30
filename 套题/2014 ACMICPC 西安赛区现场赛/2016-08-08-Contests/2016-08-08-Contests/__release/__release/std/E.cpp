#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;

int dcmp(double x) {
	return x < -eps ? -1 : x > eps;
}

struct Point {
	double x, y;
//	Point(){}
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	Point operator + (const Point &b) { return Point(x+b.x, y+b.y); }
	Point operator - (const Point &b) { return Point(x-b.x, y-b.y); }
	Point operator * (const double &b) { return Point(x * b, y * b); }
	Point operator / (const double &b) { return Point(x / b, y / b); }
	double operator * (const Point &b) { return x * b.y - y * b.x; }
	double operator % (const Point &b) { return x * b.x + y * b.y; }
	Point rot(double ang) {
		double tx = x * cos(ang) - y * sin(ang);
		double ty = x * sin(ang) + y * cos(ang);
		return Point(tx, ty);
	}
	double len2() const {
		return x*x + y*y;
	}
	double len() const {
		return sqrt(x*x + y*y); 
	}
	void init() { 
		assert(scanf("%lf %lf", &x, &y) == 2);
		assert(-2000 <= x && x <= 2000);
		assert(-2000 <= y && y <= 2000);
	}
} point[2222];
bool is_seen[2222];
bool is_point_in_sector(Point p, Point pos, Point v1, Point v2) {
	// theta < pi
	if (dcmp((p-pos).len2() - (v2-pos).len2()) > 0) return false;
	return dcmp((v1-pos)*(p-pos)) >= 0 && dcmp((v2-pos)*(p-pos)) <= 0;
}
bool is_segment_intersect(Point A, Point B, Point C,Point D) {
	if(max(C.x,D.x) < min(A.x,B.x) || max(C.y,D.y) < min(A.y,B.y)) return false;
	if(max(A.x,B.x) < min(C.x,D.x) || max(A.y,B.y) < min(C.y,D.y)) return false;
	if(dcmp((B-A)*(C-A))*dcmp((B-A)*(D-A)) > 0) return false;
	if(dcmp((D-C)*(A-C))*dcmp((D-C)*(B-C)) > 0) return false;
	return true;
}
vector<Point> getCL(Point c, double r, Point p1, Point p2) { 
	vector<Point> res;
	double x = (p1 - c) % (p2 - p1);
	double y = (p2 - p1).len2();
	double d = x * x - y * ((p1 - c).len2() - r * r);
	if (d < -eps) return res;
	if (d < 0) d = 0;
	Point q1 = p1 - ((p2 - p1) * (x / y));
	Point q2 = (p2 - p1) * (sqrt(d) / y);
	res.push_back(q1 - q2);
	res.push_back(q1 + q2);
	return res;
}
bool is_point_on_segment(Point P, Point p1,Point p2)
{
	if(! (min(p1.x,p2.x) <= P.x && P.x <= max(p1.x,p2.x) &&
		  min(p1.y,p2.y) <= P.y && P.y <= max(p1.y,p2.y)) )
		return false;
	if(dcmp((P-p1)*(p2-p1)) == 0) return true;
	return false;
}
bool is_point_on_arc(Point P, Point pos, Point v1, Point v2) {
	if (dcmp((P-pos).len2() - (v1-pos).len2()) != 0) return false;
	return is_point_in_sector(P, pos, v1, v2);
}
bool is_segment_with_tri(Point p1, Point p2, Point pos, Point v1, Point v2) {
		// trick with overlap -=====================-
	
	if (is_segment_intersect(p1, p2, pos, v1)) return true;
	if (is_segment_intersect(p1, p2, pos, v2)) return true;
	if (is_segment_intersect(p1, p2, v1, v2)) return true;
	return false;
}
bool is_segment_with_arc(Point p1, Point p2, Point pos, Point v1, Point v2) {
	vector<Point> res = getCL(pos, (v1-pos).len(), p1, p2);
	for (auto &v : res) if (is_point_on_segment(v, p1, p2) && is_point_on_arc(v, pos, v1, v2)) return true;
	return false;
}
void check_movement(Point pos, Point sight, Point go, double theta, double pre, double cur, const int &n) {		

	Point v1 = pos + sight.rot(-theta/2);
	Point v2 = pos + sight.rot(theta/2);
	
	for (int i = 0; i < n; ++i) {
		if (is_seen[i]) continue;
		Point p1 = point[i];
		Point p2 = point[i] + go * (pre - cur);
		
		if (is_point_in_sector(p1, pos, v1, v2)) { is_seen[i] = true; continue; }
		if (is_point_in_sector(p2, pos, v1, v2)) { is_seen[i] = true; continue; }
		
		if (dcmp(pre-cur) == 0) continue; // trick?
		
		if (is_segment_with_tri(p1, p2, pos, v1, v2)) { is_seen[i] = true; continue; }
		if (is_segment_with_arc(p1, p2, pos, v1, v2)) { is_seen[i] = true; continue; }
	}
}
void check_rotation(Point pos, Point sight, double theta, double alpha, const int &n) {

	Point v1 = pos + sight.rot(-theta/2);
	Point v2 = pos + sight.rot(theta/2);
	Point v3 = pos + sight.rot(-theta/2-alpha);
	Point v4 = pos + sight.rot(theta/2-alpha);

	for (int i = 0; i < n; ++i) {
		if (is_seen[i]) continue;
		if (is_point_in_sector(point[i], pos, v1, v2)) { is_seen[i] = true; continue; }
		if (is_point_in_sector(point[i], pos, v3, v4)) { is_seen[i] = true; continue; }
		
		if (dcmp(alpha - theta) > 0) {
			if (is_point_in_sector(point[i], pos, v4, v1)) { is_seen[i] = true; continue; }
		}
	}
}
int main() {

//	freopen("Ein","r",stdin);

	int cases; scanf("%d", &cases);
	int cas = 0;
	while (cases--) {
		printf("Case #%d: ", ++cas);
		
		int n, m;
		double R, theta;
		assert(scanf("%d %d %lf %lf", &n, &m, &theta, &R) == 4);
		assert(1 <= n && n <= 2000);
		assert(1 <= m && m <= 2000);
		assert(0 < theta && theta < 180);
		assert(1 <= R && R <= 2000);
		theta = theta / 180. * pi;
		
		Point pos; pos.init();
		Point sight; sight.init();
		Point go; go.init();
		
		sight = sight / sight.len() * R;
		go = go / go.len();
		
		for (int i = 0; i < n; ++i) {
			point[i].init();
			is_seen[i] = false;
		}
		
		double pre_time = 0;
		
		for (int TT = 0; TT < m+1; ++TT) {
		
			double alpha = 0;
			double Time = 0;
			int op = 1;
			if (TT > 0) {
				assert(scanf("%d %lf %lf", &op, &Time, &alpha) == 3);
				assert(op == 1 || op == 2);
				assert(Time >= 0 && Time <= 2000);
				assert(alpha >= 0 && alpha <= 180);
			}
			alpha = alpha / 180. * pi;
			
			check_movement(pos, sight, go, theta, pre_time, Time, n);
			pos = pos + go * (Time - pre_time);			
			if (op == 1) {
				check_rotation(pos, sight, theta, alpha, n);
				sight = sight.rot(-alpha);
			} else {
				go = go.rot(-alpha);
			}
			pre_time = Time;
		}
		for (int i = 0; i < n; ++i) if (is_seen[i]) printf("0"); else printf("1");
		puts("");
	}

	return 0;
}
