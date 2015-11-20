typedef complex<double> comp;
const double PI = acos(-1.0);

struct FFT{
	int n;
	comp y[N];

	void init(int _n){
		n = 1;
		while (n < _n){
			n <<= 1;
		}
		for (int i = 0; i < n; ++ i){
			y[i] = 0;
		}
	}

	void change(){
	    int i, j, k;
	    for (i = 1, j = n / 2; i < n - 1; ++ i){
	        if (i < j) swap(y[i], y[j]);
	        k = n / 2;
	        while (j >= k){
	            j -= k;
	            k /= 2;
	        }
	        if (j < k){
	            j += k;
	        }
	    }
	}

	void fft(int on){ // 1 for DFT -1 for IDFT
		change();
	    for (int h = 2; h <= n; h <<= 1){
	        comp wn(cos(-on * 2.0 * PI / h), sin(-on * 2.0 * PI / h));
	        for (int j = 0; j < n; j += h){
	            comp w(1.0, 0.0);
	            for (int k = j; k < j + h / 2; ++ k){
	                comp u = y[k];
	                comp t = w * y[k+h/2];
	                y[k] = u + t;
	     	        y[k+h/2] = u - t;
	                w = w * wn;
	            }
	        }
	    }
	    if (on == -1){
	        for (int i = 0; i < n; ++ i){
	            y[i] /= n;
	        }
	    }
	}

}A, B, C;


// 这个是随手写的
// 传入的na与nb分别是a与b数组的长度，n则是答案应该有的长度，所以所有的init应该用n来初始化
void solve(int na, int a[], int nb, int b[], int c[], int n){
	A.init(n);
	for (int i = 0; i < na; ++ i){
		A.y[i] = a[i];
	}
	B.init(n);
	for (int i = 0; i < nb; ++ i){
		B.y[i] = b[i];
	}
	
	A.fft(1);
	B.fft(1);
	C.init(n);
	for (int i = 0; i < C.n; ++ i){ //另外注意该处需要用C.n这个扩展长度
		C.y[i] = A.y[i] * B.y[i];
	}
	C.fft(-1);

	for (int i = 0; i < C.n; ++ i){
		c[i] = (int)(C.y[i].real() + 0.1);
	}
}
