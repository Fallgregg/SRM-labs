#include <iostream>
#include <iomanip>
#define n 400
using namespace std;

double x[n], y[n], eps;

double derivative(double x, double y) {
    return exp((-1.4*x) * (pow(y,2) + 1.4 ));
}

void RungeKutte_method(int j, double h) {
    cout << "\nRunge_Kutte method\n";
    double k1, k2, k3, k4, ch;
    int i = 0;
    cout << 0 << " X: " << x[i] << setw(20) << "Y: " << y[i] << setw(20) << "Eps:" << 0 << endl;
    do {
        if (j == 1 && i == 3) break;
        do {
            x[i + 1] = x[i] + h;
            k1 = derivative(x[i], y[i]);
            k2 = derivative(x[i] + h / 2, y[i] + h * k1 / 2);
            k3 = derivative(x[i] + h / 2, y[i] + h * k2 / 2);
            k4 = derivative(x[i] + h, y[i] + h * k3);
            ch = abs((k2 - k3) / (k1 - k2));
            if (ch > 0.09) {
                h /= 2;
                cout << "h: " << h << endl;
            }
        } while (ch > 0.09);
        y[i + 1] = y[i] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
        eps = abs(y[i + 1] - y[i]) / (pow(2, 4) - 1);
        cout << i + 1 << " X: " << x[i + 1] << setw(10) << "Y: " << y[i + 1] << setw(10) << "ESP: " << eps << endl;
        i++;
    } while (x[i] < 4);
}

void Adams_method(double h) {
    RungeKutte_method(1, 0.1);
    cout << "\nAdams method: \n";
    int i = 3;
    double ch, Y;
    do {
        do {
            x[i + 1] = x[i] + h;
            y[i + 1] = y[i] + h / 24 * (55 * derivative(x[i], y[i]) - 59 * derivative(x[i - 1], y[i - 1]) + 37 * derivative(x[i - 2], y[i - 2]) - 9 * derivative(x[i - 3], y[i - 3]));
            Y = y[i] + h / 24 * (9 * derivative(x[i + 1], y[i + 1]) + 19 * derivative(x[i], y[i]) - 5 * derivative(x[i - 1], y[i - 1]) + derivative(x[i - 2], y[i - 2]));
            ch = abs(Y - y[i + 1]);
            if (ch > 0.09) {
                h /= 2;
                cout << "h: " << h << endl;
            }
        } while (ch > 0.09);
        eps = eps = abs(y[i + 1] - y[i]) / (pow(2, 4) - 1);
        cout << i - 3 << " X: " << x[i + 1] << setw(10) << "Y: " << y[i + 1] << setw(10) << "ESP: " << eps << endl;
        i++;
    } while (x[i] < 4);
}

int main() {
    cout << "y' = f(x,y)\nf(x,y) = e^(-1.4*x)*(y+1.4)\ninterval: [0, 4]\ny(0) = 0\n";
    x[0] = 0;
    y[0] = 0;
    RungeKutte_method(0, 0.1);
    cout << endl << endl;
    Adams_method(0.1);
    system("pause");
    return 0;
}
