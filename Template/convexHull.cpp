
typedef long long ll;

struct point{
	ll x, y;
	void input(){
		scanf("%lld%lld", &x, &y);
	}
	point(){}
	point(int _x, int _y){x = _x; y = _y;}
	bool operator <(const point &A)const{
		if (x == A.x){
			return y < A.y;
		}
		return x < A.x;
	}
	point operator -(const point &A){
		return point(x - A.x, y - A.y);
	}
};

inline ll cross(const point &a, const point &b){
	return a.x * b.y - a.y * b.x;
}

int getConvexHull(point *p, int n, point *ch){
	sort(p, p + n);
	int m = 0;
	for (int i = 0; i < n; ++ i){
		while (m > 1 && cross(ch[m-1] - ch[m-2], p[i] - ch[m-1]) <= 0) -- m;
		ch[m++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; -- i){
		while (m > k && cross(ch[m-1] - ch[m-2], p[i] - ch[m-1]) <= 0) -- m;
		ch[m++] = p[i];
	}
	if (n > 1) m --;
	return m;
}