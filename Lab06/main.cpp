#include <iostream>

using namespace std;

double function(double x){
    return 2*pow(x,1) - 4*pow(x,2) - x + 3;
}

double bisection_roots(double (*f)(double),double a,double b,double eps){
    double c;
    double n = 0;
    while((b - a) / 2 > eps) {
        c = (a + b) / 2;
        if ((f(a) * f(c)) > 0) {
            a = c;
        } else {
            b = c;
        }
        n += 1;
    }

    cout << "N = " << n << endl;
    return c;
}

double chord_roots(double a, double b, double epsilon) {
    double n = 0;
    while(fabs(b - a) > epsilon) {
        a = b - (b - a) * function(b) / (function(b) - function(a));
        b = a + (a - b) * function(a) / (function(a) - function(b));
        n += 1;
    }
    cout << " N = " << n << endl;
    return b;
}

double newton_roots(double (*f)(double),double x0,int k){
    double x = x0, df, h=0.00001;
    double n = 0;
    df=(f(x+h) - f(x)) / h;
    for(int i = 1;i <= k;i++) {
        x = x - f(x) / df;
        n += 1;
    }
    cout << " N = " << n << endl;
    return x;
}

int main() {
    double a,b,a1,b1,eps,x1, x2,x3,x0;
    cout << " Enter first interval: ";
    cin >> a >> b;
    cout << "Enter second interval: ";
    cin >> a1 >> b1;
    cout << "Enter starter (for Newton method): ";
    cin >> x0;
    cout << "Enter epsilon: ";
    cin >> eps;

    x1 = bisection_roots(function, a, b, eps);
    cout << " X(1) = " << x1 << endl;
    x2 = newton_roots(function, x0, 2);
    cout << " X(2) = " << x2 << endl;
    x3 = chord_roots(a1, b1, eps);
    cout << " X(3) = " << x3 << endl;

    return 0;
}
