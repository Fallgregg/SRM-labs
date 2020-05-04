#include<iostream>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include <math.h>
#include <windows.h>

using namespace std;

float er = 0;
float* runningMethod(float** A, float* b, int n) {
	float* K = new float[n];
	int n1 = n - 1;
	float y = A[0][0];
	float* a = new float[n];
	float* b1 = new float[n];
	a[0] = -A[0][1] / y;
	b1[0] = b[0] / y;
	for (int i = 1; i < n1; i++) {
		y = A[i][i] + A[i][i - 1] * a[i - 1];
		a[i] = -A[i][i + 1] / y;
		b1[i] = (b[i] - A[i][i - 1] * b1[i - 1]) / y;
	}
	K[n1] = (b[n1] - A[n1][n1 - 1] * b1[n1 - 1]) / (A[n1][n1] + A[n1][n1 - 1] * a[n1 - 1]);
	for (int i = n1 - 1; i >= 0; i--) {
		K[i] = a[i] * K[i + 1] + b1[i];
	}
	return K;
}

float splineMethod(float* X, float* Y, int n, float x0) {
	float* a = new float[n - 1];
	float* b = new float[n - 1];
	float* c = new float[n - 1];
	float* d = new float[n - 1];
	float** A = new float* [n - 1];
	float* h = new float[n - 1];
	float* by = new float[n];
	for (int i = 0; i < n; i++) {
		A[i] = new float[n];
	}
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			A[i][j] = 0;
		}
		by[i] = 0;
		a[i] = Y[i];
		h[i] = X[i + 1] - X[i];
	}

	A[0][0] = 1;
	A[n - 2][n - 2] = 1;
	for (int i = 1; i < n - 2; i++) {
		A[i][i - 1] = h[i - 1];
		A[i][i] = 2 * (h[i - 1] + h[i]);
		A[i][i + 1] = h[i];
		by[i] = 3 * (((Y[i + 1] - Y[i]) / h[i]) - ((Y[i] - Y[i - 1]) / h[i - 1]));
	}
	c = runningMethod(A, by, n - 1);
	for (int i = 0; i < n - 1; i++) {
		d[i] = (c[i + 1] - c[i]) / (3 * h[i]);
		b[i] = ((Y[i + 1] - Y[i]) / h[i]) - h[i] * (c[i + 1] + 2 * c[i]) / 3;
	}
	d[n - 2] = -c[n - 2] / (3 * h[n - 2]);
	b[n - 2] = ((Y[n - 1] - Y[n - 2]) / h[n - 2]) - 2 * h[n - 2] * c[n - 2] / 3;
	int m;
	for (int i = 0; i < n; i++) {
		if (x0 >= X[i] && x0 <= X[i + 1]) {
			m = i;
		}
	}

	float x = x0 - X[m];
	float y = a[m] + b[m] * x + c[m] * x * x + d[m] * x * x * x;

	if (er == 0) {
		cout << "Spline coeficients: " << y << " :" << endl << endl;
		cout << setw(10) << a[m] << endl;
		cout << setw(10) << b[m] << endl;
		cout << setw(10) << c[m] << endl;
		cout << setw(10) << d[m] << endl;
	}

	return y;
	 
}


void printPolynom(float* X, float* Y) {
	int n = 5;
	float Y1[5];
	for (int count = 0; count < 5; count++) Y1[count] = Y[count];
	float k[5];
	k[0] = Y1[0];
	for (int j = 1; j < n; j++) {
		for (int i = 0; i < n - j; i++) {
			Y1[i] = (Y1[i + 1] - Y1[i]) / (X[i + j] - X[i]);
			k[j] = Y1[0];
		}
	}
	cout << "N(x) = ";
	for (int i = 0; i < n; i++) {
		if (i != 3 && i != 0) cout << " + " << k[i] << "*X^" << n - i - 1;
		else if (i != 0) cout << " + " << abs(k[i]) << "*X^" << n - i - 1;
		else cout << k[i] << "*X^" << n - i - 1;
	}
}

float newtonMethod(float* X, float* Y, int n, float x) {
	float* Xn = new float[n];
	for (int i = 0; i < n; i++) {
		Xn[i] = Y[i];
	}
	float* delta = new float[n];
	delta[0] = Xn[0];
	float Sum = delta[0];
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i; j++) {
			Xn[j] = Xn[j + 1] - Xn[j];
		}
		delta[i + 1] = Xn[0];
	}
	float h = X[1] - X[0];
	float q = (x - X[0]) / h;
	int fact = 1;
	float d = 1;
	for (int i = 1; i < n; i++) {
		fact *= i;
		d *= q - i + 1;
		Sum += (delta[i] * d) / fact;
	}
	return Sum;
}

float findError(float x0, float x)
{
	return abs(x - x0);
}

int main() {
	int n = 5;
	float X[5] = { 0, 2, 4, 6, 8 };
	float* Y;
	float error;
	Y = new float[n];

	for (int i = 0; i < n; i++) {
		Y[i] = pow(3 * X[i], 1 / 3) + (float)sin((3 * X[i]) / 2);
	}
	error = Y[0];

	cout << "X: ";
	for (int i = 0; i < n; i++) {
		cout << X[i] << " ";
	}

	cout << endl << "Y: ";
	for (int i = 0; i < n; i++) {
		cout << Y[i] << " ";
	}

	cout << endl << "Newton method: " << endl << endl;
	for (int i = 0; i < n; i++) {
		cout << setw(10) << newtonMethod(X, Y, n, X[i]) << endl;
	}
	cout << endl << "Polynom:\n";
	printPolynom(X, Y);
	cout << endl;

	cout << "\nSpline method: " << endl << endl;
	for (int i = 0; i < n; i++) {
		splineMethod(X, Y, n, X[i]);
		cout << endl << endl;
	}

	cout << "Checking for errors: " << endl << endl;
	cout << "Enter X of the point: ";
	cin >> er;

	bool check = false;
	for (int i = 0; i < 5; i++) {
		if (er == X[i]) check = true;
	}

	if (check == false) {
		cout << "Error between N(x) & F(x) results is: " << endl << findError(pow(er, 1 / 3) + (float)sin(0.5 * er), newtonMethod(X, Y, n, er)) << endl;
	} else {
		cout << "Error between N(x) & F(x) results is: 0";
	}

	return 0;
}
