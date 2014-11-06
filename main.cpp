#include <iostream>

using namespace std;

float a = 0;
float b = 0;
int examplesNumber;
float sum = 0;
float x;
float y;

float hypothesis(float);
float sumFunction(float, float, float);


int main(void)
{
	cout << "This program is trying to predict values based on examples. Now give me the number of examples: \n";
	cin >> examplesNumber;
	cout << "\n";
	float examples[2][examplesNumber];
	cout << "Now give me the examples:";
	cout << "\n";
	for (int i = 0; i < examplesNumber; i++)
	{
		cout << "x: ";
		cin >> x;
		cout << "\n";
		cout << "y: ";
		cin >> y;
		examples[0][i] = x;
		examples[1][i] = y;
		cout << "\n";
	}
	return 0;
}

float hypothesis(float x)
{
	return a * x + b;
}

float sumFunction(float a, float b, float x)
{
	sum = 0;
	for(int i = 0; i< examplesNumber; i++)
	{
		sum += (a * x + b - hypothesis(x)) * (a * x + b - hypothesis(x));
	}
	return (1 / (2 * examplesNumber)) * sum;
}
