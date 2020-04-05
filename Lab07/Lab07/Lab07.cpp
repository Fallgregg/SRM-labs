#include <iostream>
#include <math.h>

using namespace std;

double function(double x) {
	return cos(x) / (x + 1);
}

void trapeze_equation(double a, double b, int n, double eps) {
	double h = 0.0;
	double res = 0.0;
	double temp_res = 0.0;

	do {
		h = (b - a) / n;
		temp_res = res;
		res = 0.0;
		for (double x = a; x < b; x += h) {
			res += (function(x + h) + function(x)) / 2 * h;
		}
	} while ((abs(temp_res - res) > eps) && (n *= 2));

	cout << "Integral = " << res << endl;
}

double  gaussian_elimination(double a, double b, int k) {
	const int n = 3;
	double X[n] = { -0.7745967, 0, 0.7745967 };  
	double C[n] = { 0.5555556, 0.8888889, 0.5555556 };
	double dif = (b - a) / 2;
	double sum = (a + b) / 2;
	double x, Sum_Ai = 0.0;
	for (int i = 0;i < n; i++)
	{
		x = sum + dif * X[i];
		Sum_Ai += C[i] * function(x);
	}
	return dif * Sum_Ai;
}

		
int main() {
	double a = 0.5;
	double b = 1.4;
	double eps = 0.0001;
	int n = 2;
	double res = 0.0;

	cout << "Trapeze method: \n";
	trapeze_equation(a, b, n, eps);

	cout << "\nMethod of Gauss: \n";
	for (int i = 0; i < 100; ++i) {
		res += gaussian_elimination(a + i * (b - a) / 100, a + (i + 1) * (b - a) / 100, 100);
	}
	cout << "Integral = " << res << endl;

	return 0;
}

