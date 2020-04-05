#include <iostream>

using namespace std;

int main() {
	int n = 4;
	double temp = 0;
	double temp2 = 0;
	double* rArr = new double[n];
	double* x = new double[n];
	double** arr = new double* [n];
	for (int i = 0; i <= n; i++) {
		arr[i] = new double[n];
	}

	cout << "Coefficients of the matrix: " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << "a[" << i << "," << j << "]= ";
			cin >> arr[i][j];
		}
	}

	cout << endl << "Coefficients of right part: " << endl;
	for (int i = 1; i <= n; i++) {
		cout << "b[" << i << "]= ";
		cin >> rArr[i];
	}

	for (int k = 1; k <= n; k++) {
		for (int j = k + 1; j <= n; j++) {
			temp = arr[j][k] / arr[k][k];
			for (int i = k; i <= n; i++) {
				arr[j][i] = arr[j][i] - temp * arr[k][i];
			}
			rArr[j] = rArr[j] - temp * rArr[k];
		}
	}

	print_matrix

	for (int k = n; k >= 1; k--) {
		temp = 0;
		for (int j = k + 1; j <= n; j++) {
			temp2 = arr[k][j] * x[j];
			temp += temp2;
		}
		x[k] = (rArr[k] - temp) / arr[k][k];
	}
	cout << endl << "Results: " << endl;
	for (int i = 1; i <= n; i++) {
		cout << "x[" << i << "]=" << x[i] << " " << endl;
	}
	return 0;
}

