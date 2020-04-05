#include <iostream>

using namespace std;

void print_vector(const int n, double arr[]) {
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}

void print_result(int n, double* arr) {
	for (int i = 0; i < n; i++) {
		cout << "x" << i + 1 << " = " << arr[i];
		cout << endl;
	}
	cout << endl;
}

void print_matrix_coefs(const int n, double arr[][4]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

double* iterration_method(double arr[][4], double arr_b[], int n) {

	double* temp = new double[n];
	double summ = 0;
	double eps = 0.01;
	double* Xn = new double[n];
	int counter = 0;

	for (int i = 0; i < n; i++) {
		temp[i] = arr_b[i] / arr[i][i];
	}

	do {
		for (int i = 0; i < n; i++) {

			Xn[i] = arr_b[i] / arr[i][i];
			for (int j = 0; j < n; j++) {
				if (i == j) {
					continue;
				}
				else {
					Xn[i] -= arr[i][j] / arr[i][i] * temp[j];
				}
			}
		}
		counter++;

		cout << "Itteration: " << counter << endl;
		print_result(n, temp);

		double* a_X = new double[n];
		for (int i = 0; i < n; i++) {
			a_X[i] = 0;
			for (int k = 0; k < n; k++) {
				a_X[i] += arr[i][k] * temp[k];
			}
		}

		double* r = new double[n];
		for (int i = 0; i < n; i++) {
			r[i] = arr_b[i] - a_X[i];
		}

		cout << "R" << counter << ": " << endl;
		for (int i = 0; i < n; i++) {
			cout << "r" << i + 1 << "=" << r[i] << endl;
		}

		cout << endl;

		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (abs(Xn[i] - temp[i]) > eps) {
				flag = false;
				break;
			}
		}

		for (int i = 0; i < n; i++) {
			temp[i] = Xn[i];
		}

		if (flag)
			break;

	} while (1);

	return temp;
}

int main() {
	double* x;
	const int n = 4;
	const double eps = 0.0001;
	double arr_a[n][n] = {
		{3.81,0.25,1.28, 1.25},
		{2.25, 1.32, 5.08, 0.49},
		{5.31, 6.78, 0.98, 1.04},
		{9.89, 2.45, 3.35, 2.28}
	};

	double arr[n][n] = {
		{1.0, 0.25, 0.34, 0.23},
		{0.0, 1.0, -0.15, -0.034},
		{0.0, 0.0, 1.0, -3.04},
		{0.0, 0.0, 0.0, 1.0}
	};

	double arr_b[n] = { 4.21, 6.97, 2.38, 10.98 };
	double arr_x[n] = { 1.11, -0.64, 4.07, -0.97};

	cout << "Matrix of coeficients: " << endl;
	print_matrix_coefs(n, arr_a);
	cout << "Matrix of a right part: " << endl;
	print_vector(n, arr_b);

	x = iterration_method(arr, arr_x, n);
	cout << "RESULT: " << endl;
	print_result(n, x);

	return 0;

}