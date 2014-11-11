#include <iostream>
#include <new>

using namespace std;

float firstHypothesisCoefficient = 0;
float secondHypothesisCoefficient = 0;
int numberOfExamples;
float *examplesX;
float *examplesY;
int trainingsNumber = 50;
float learningFactor = 0.01;

float hypothesis(float x, float a = firstHypothesisCoefficient, float b = secondHypothesisCoefficient);
float sumFunction(float a, float b);

int main(void)
{
	
	cout << "This program is trying to predict values based on examples. Now give me the number of examples: \n";
	cin >> numberOfExamples;
	cout << "\n";

	examplesX = new (nothrow) float [numberOfExamples];
	examplesY = new (nothrow) float [numberOfExamples];

	cout << "Now give me the examples:";
	cout << "\n";
	for (int i = 0; i < numberOfExamples; i++)
	{
		float x;
		float y;
		cout << "x: ";
		cin >> x;
		examplesX[i] = x;
		cout << "\n";
		cout << "y: ";
		cin >> y;
		examplesY[i] = y;
		cout << "\n";
	}

	// for (int i = 0; i < numberOfExamples; i++)
	// {
	// 	cout << examplesX[i] << "\n";
	// 	cout << examplesY[i] << "\n";
	// }

	for (int q = 0; q < trainingsNumber; q++)
	{
		float derivativeA = 0;
		float derivativeB = 0;
		for (int i = 0; i < numberOfExamples; i++)
		{
			derivativeA += ( hypothesis(examplesX[i], firstHypothesisCoefficient, secondHypothesisCoefficient) - examplesY[i] ) * examplesX[i];
			derivativeB += hypothesis(examplesX[i], firstHypothesisCoefficient, secondHypothesisCoefficient) - examplesY[i];
		}
		derivativeA = derivativeA / numberOfExamples;
		derivativeB = derivativeB / numberOfExamples;
		firstHypothesisCoefficient -= learningFactor * derivativeA;
		secondHypothesisCoefficient -= learningFactor * derivativeB;
	}

	cout << "\n" << "First coefficient: " << firstHypothesisCoefficient << "\n" << "Second coefficinet: " << secondHypothesisCoefficient << "\n" << "SumFunction: " << sumFunction(firstHypothesisCoefficient, secondHypothesisCoefficient) << "\n";
	return 0;


}

float hypothesis(float x, float a, float b)
{
	return a * x + b;
}

float sumFunction(float a, float b)
{
	float sum = 0;

	for (int i = 0; i < numberOfExamples; i++)
	{
		sum += (hypothesis(examplesX[i], a, b) - examplesY[i]) * (hypothesis(examplesX[i], a, b) - examplesY[i]);
		//cout << sum << "\n";
	}

	sum = sum / ( 2 * numberOfExamples);

	return sum;
}
