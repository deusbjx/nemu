#include "trap.h"
#include "FLOAT.h"

FLOAT f(FLOAT x) { 
	/* f(x) = 1/(1+25x^2) */
	return F_div_F(int2F(1), int2F(1) + F_mul_int(F_mul_F(x, x), 25));
}

FLOAT computeT(int n, FLOAT a, FLOAT b) {
	int k;
	FLOAT s,h;
	h = F_div_int((b - a), n);
	s = F_div_int(f(a) + f(b), 2 );
	//s = F_div_int(a + b, 2 );
	for(k = 1; k < n; k ++) {
		set_bp();
		s += f(a + F_mul_int(h, k));
		s += a + F_mul_int(h, k);
	}
	s = F_mul_F(s, h);
	return s;
}

int main() { 
	//FLOAT a = 0.666666;
	//FLOAT a = computeT(10, f2F(-1.0), f2F(1.0), f);
	//FLOAT ans1 = f2F(0.551222);
	//FLOAT ans2 = f2F(0.666666);
	//FLOAT ans = F_mul_F(f(a),f(ans2));
	//nemu_assert(ans);

	FLOAT a = computeT(3, f2F(-1.0), f2F(1.0));
	FLOAT ans = f2F(0.551222);

	nemu_assert(Fabs(a - ans) < f2F(1e-4));

	return 0;
}
