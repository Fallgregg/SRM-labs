#include <iomanip>
#include <iostream>

using namespace std;

double arr[4][4] = {
{ 6.92, 1.16, 0.91, 1.15 },
{ 1.16, 3.50, 1.30, 0.16 },
{ 0.91, 1.30, 6.10, 2.10 },
{ 1.15, 0.16, 2.10, 5.44 },
};

int main() { 

	cout << "MATRIX: " << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << setw(4) << " " << arr[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	double m1[4][4];

	for (int i = 0; i < 3; i++) {
		double  s1[4][4] = { { 1,	0,	0,	0 },{ 0,	1,	0,	0 },{ 0,	0,	1,	0 },{ 0,	0,	0,	1 } };
		double  s2[4][4] = { { 1,	0,	0,	0 },{ 0,	1,	0,	0 },{ 0,	0,	1,	0 },{ 0,	0,	0,	1 } };

		for (int j = 0; j < 4; j++) {
			if (j != 2 - i) {
				s1[2 - i][j] = -(arr[2 - i + 1][j]) / arr[2 - i + 1][2 - i];
			}
			else {
				s1[2 - i][j] = 1 / arr[2 - i + 1][2 - i];
			}
			s2[2 - i][j] = arr[3 - i][j];
		}

		cout << "Matrix M1 on iteration num" << i << ":" << endl;
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				cout << setw(4) << " " << s1[k][j] << "  ";
			}
			cout << endl;
		}
		cout << endl;

		cout << "Matrix M2 on iteration num." << i << ":" << endl;
		for (int k = 0; k < 4; k++) {
			for (int j = 0; j < 4; j++) {
				cout << setw(4) << " " << s2[k][j] << "  ";
			}
			cout << endl;
		}
		cout << endl;

		double d[4][4] = { { 0,	0,	0,	0 },{ 0,	0,	0,	0 },{ 0,	0,	0,	0 },{ 0,	0,	0,	0 } };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int l = 0; l < 4; l++) {
					d[i][j] += s2[i][l] * arr[l][j];
				}
			}
		}

		double d2[4][4] = { { 0,	0,	0,	0 },{ 0,	0,	0,	0 },{ 0,	0,	0,	0 },{ 0,	0,	0,	0 } };
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int l = 0; l < 4; l++) {
					d2[i][j] += d[i][l] * s1[l][j];
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				arr[i][j] = d2[i][j];
			}
		}

		cout << "Matrix P after iteration num." << i + 1 << ":" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << setw(4) << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}


	cout << "Characteristic equation: " << endl << "X^4 - ";
	int ind = 3;
	for (int i = 0; i < 4; i++) {
		if (i != 3) {
			cout << "(" << arr[0][i] << ") " << " * X^" << ind << " - ";
		}
		else {
			cout << arr[0][3] << ";" << endl;
		}
		ind--;
	}
}



