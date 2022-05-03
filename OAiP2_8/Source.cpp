#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

const double A = 1.;
const double B = 4.;
const double DEFAULT_EPS = 0.000001;

double calculateByNumOfPartitions(double a, double b, int n);
double calculateByEPS(double a, double b, double eps);
double calculateFirstFunction(double a, double b);
double function(double x);
double firstFunction(double x);
int numOfSymAfterComma(double num, int k);
int correctInputInt();
int enterNumberInRange(int min, int max);
double correctInputDouble();

int main()
{
	char code;
	double a, b, eps, result;
	int number, n, k;
	k = numOfSymAfterComma(DEFAULT_EPS, 0);
	cout << "Function: x - 5(sinx)^2" << endl;
	cout << "------------------------------------------" << endl;
	do
	{
		cout << "Do you want to use default values(a = " << A << ", b = " << B << ")? (Y/N)" << endl;
		code = (char)_getch();
		if (code == 'Y' || code == 'y')
		{
			a = A;
			b = B;
		}
		else
		{
			cout << "Enter a: ";
			a = correctInputDouble();
			cout << "Enter b: ";
			b = correctInputDouble();
			if (b < a)
			{
				cout << "b < a, swap them!" << endl;
				double temp = a;
				a = b;
				b = temp;
			}
		}
		cout << "Calculate by:\n1) Number of partitions\n2) EPS" << endl;
		number = enterNumberInRange(1, 2);
		switch (number)
		{
		case 1:
			do
			{
				cout << "Enter number of partitions (n > 0): ";
				n = correctInputInt();
			} while (n < 0);
			result = calculateByNumOfPartitions(a, b, n);
			break;
		case 2:
			do
			{
				cout << "Enter EPS (EPS > 0): ";
				eps = correctInputDouble();
			} while (eps <= 0.);
			k = numOfSymAfterComma(eps, 0);
			result = calculateByEPS(a, b, eps);
			break;
		}
		cout << "Result: " << setprecision(k) << result << "\nOriginal: " << calculateFirstFunction(a, b) << endl;
		cout << "\nDo you want to continue?(Y/N)" << endl;
		code = (char)_getch();
	} while (code == 'Y' || code == 'y');
	system("pause");
	return 0;
}

double calculateByNumOfPartitions(double a, double b, int n)
{
	double h, delta, res = 0.;
	h = (b - a) / n;
	cout << "Number of partitions: " << n << "\nStep: " << h << endl;
	delta = h / 2.;
	for (double x = a; x <= b - h / 4.; x += h)
	{
		res += function(x + delta);
	}
	res *= h;
	cout << "Result: " << res << endl;
	cout << endl;
	return res;
}

double calculateByEPS(double a, double b, double eps)
{
	int n = 2;
	double result_prev, result1, result2, delta;
	result1 = calculateByNumOfPartitions(a, b, n);
	do
	{
		n *= 2;
		result2 = calculateByNumOfPartitions(a, b, n);
		delta = fabs(result2 - result1);
		result_prev = result1;
		result1 = result2;
	} while (delta > eps);
	cout << "The accuracy achieved in " << n / 2 << " number of partitions" << endl;
	return result_prev;
}

double calculateFirstFunction(double a, double b)
{
	return firstFunction(b) - firstFunction(a);
}

double firstFunction(double x)
{
	return 0.5 * (x * x - 5. * x + 2.5 * sin(2. * x));
}

double function(double x)
{
	return x - 5 * sin(x) * sin(x);
}

int numOfSymAfterComma(double num, int k)
{
	if (num >= 1. || num <= -1.)
	{
		return k;
	}
	return numOfSymAfterComma(num * 10, k + 1);
}

double correctInputDouble()
{
	double a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, please write numbers!\n" << "Try again!" << endl;
		}
	}
	return a;
}

int correctInputInt()
{
	int a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, please write numbers!\n" << "Try again!" << endl;
		}
	}
	return a;
}

int enterNumberInRange(int min, int max)
{
	int number;
	while (true)
	{
		number = correctInputInt();
		if (number >= min && number <= max)
		{
			break;
		}
		else
		{
			cout << "Enter number in range!" << endl;
		}
	}
	return number;
}