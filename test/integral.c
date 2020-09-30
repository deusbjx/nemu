//#include "trap.h"
#include "stdlib.h"
#include "stdio.h"
#include "FLOAT.h"

FLOAT f(FLOAT x) { 
	/* f(x) = 1/(1+25x^2) */
	return F_div_F(int2F(1), int2F(1) + F_mul_int(F_mul_F(x, x), 25));
}

FLOAT f2F(float a) {
	/* You should figure out how to convert `a' into FLOAT without
	 * introducing x87 floating point instructions. Else you can
	 * not run this code in NEMU before implementing x87 floating
	 * point instructions, which is contrary to our expectation.
	 *
	 * Hint: The bit representation of `a' is already on the
	 * stack. How do you retrieve it to another variable without
	 * performing arithmetic operations on it directly?
	 */

	int b = *(int *)&a;
	int flag = b >> 31;
	int exp = (b >> 23) & 0xff;
	FLOAT k = b & 0x7fffff;
	if (exp != 0) k += 1 << 23;
	exp -= 150;
	if (exp < -16) k >>= -16 - exp;
	if (exp > -16) k <<= exp + 16;
	if (flag == 0)return k;
	else return -k;

	//nemu_assert(0);
	//return 0;
}

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	long long ans = (a*1ll*b)>>16;
	return ans;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	/* Dividing two 64-bit integers needs the support of another library
	 * `libgcc', other than newlib. It is a dirty work to port `libgcc'
	 * to NEMU. In fact, it is unnecessary to perform a "64/64" division
	 * here. A "64/32" division is enough.
	 *
	 * To perform a "64/32" division, you can use the x86 instruction
	 * `div' or `idiv' by inline assembly. We provide a template for you
	 * to prevent you from uncessary details.
	 *
	 *     asm volatile ("??? %2" : "=a"(???), "=d"(???) : "r"(???), "a"(???), "d"(???));
	 *
	 * If you want to use the template above, you should fill the "???"
	 * correctly. For more information, please read the i386 manual for
	 * division instructions, and search the Internet about "inline assembly".
	 * It is OK not to use the template above, but you should figure
	 * out another way to perform the division.
	 */

	int flag = 1;
	if (a < 0) {
		flag = -flag;
		a = -a;
	}
	if (b < 0) {
		flag = -flag;
		b = -b;
	}
	int ans = a / b;
	a = a % b;
	//you can't just return (a/b)<<16
	//which will lose last 16 bits
	int i;
	for (i = 0; i < 16; i++) 
	{
		a <<= 1;
		ans <<= 1;
		if (a >= b) {
			a -= b;
			ans++;
		}
	}
	return ans * flag;

	//nemu_assert(0);
	//return 0;
}

FLOAT Fabs(FLOAT a) {
	FLOAT b;
	if (a < 0) b = - a;
	else b = a;
	return b;
	//nemu_assert(0);
	//return 0;
}

FLOAT computeT(int n, FLOAT a, FLOAT b, FLOAT (*fun)(FLOAT)) {
	int k;
	FLOAT s,h;
	h = F_div_int((b - a), n);
	s = F_div_int(fun(a) + fun(b), 2 );
	//s = F_div_int(a + b, 2 );
	for(k = 1; k < n; k ++) {
		//set_bp();
		s += fun(a + F_mul_int(h, k));
		//set_bp();
		//s += a + F_mul_int(h, k);
		//set_bp();
	}
	//set_bp();
	s = F_mul_F(s, h);
	//set_bp();
	return s;
}

int main() { 
	//FLOAT a = 0.666666;
	FLOAT a = computeT(10, f2F(-1.0), f2F(1.0), f);
	//FLOAT ans1 = f2F(0.551222);
	//FLOAT ans2 = f2F(0.666666);
	//FLOAT ans = F_mul_F(f(a),f(ans2));
	//nemu_assert(ans);

	//FLOAT a = computeT(3, ans1, ans2);
	//nemu_assert(1 < 0);
	FLOAT ans = f2F(1.2);
	printf("%x,%x,%d\n",Fabs(a - ans),f2F(1e-4),Fabs(a - ans) > f2F(1e-4));
	//nemu_assert(Fabs(a - ans) > f2F(1e-4));

	return 0;
}
