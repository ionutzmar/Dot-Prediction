#include <iostream>

using namespace std;

int main()
{
	int *p;
	int a[2];
	p = a;
	*p = 0;
	a[1] = 3;
	
	cout << *(p + 1) << "\n";

	int n;
	cin >> n;
	cout << "\n" << n << "\n";
}