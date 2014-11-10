#include <iostream>

using namespace std;

float firstHypothesisCoefficient = 0;
float secondHypothesisCoefficient = 0;

class Example
{

private:

	int _examplesNumber;
	float *pDataX;
	float *pDataY;
	//int dim_1;
	//int dim_2;
public:

	Example(int cinExamplesNumber)
	{

		_examplesNumber = cinExamplesNumber;
		float dataX[_examplesNumber];
		float dataY[_examplesNumber];
		pDataX = dataX;
		pDataY = dataY;

	//float myArray [][]=new float [dim_1][dim_2];

		
	};

	~Example()
	{
		//
	};

	int getExamplesNumber()
	{
		return _examplesNumber;
	};

	void setX(int i, float x)
	{
		*(pDataX + i) = x;
		cout << *(pDataX + i) << "\n";
	};

	void setY(int i, float y)
	{
		*(pDataY + i) = y;
		cout << *(pDataY + i) << "\n";
		cout << *(pDataX + i) << "\n";
	};

	float getExample(int axis, int i)
	{
		if (axis == 0)
			return *(pDataX + i);
		else
			return *(pDataY + i);
	}

	// float getData()
	// {
	// 	return *dataNumbers[2][2];
	// };




};

int main(void)
{

	int numberOfExamples;
	cout << "This program is trying to predict values based on examples. Now give me the number of examples: \n";
	cin >> numberOfExamples;
	cout << "\n";

	Example examples(numberOfExamples);

	cout << "Now give me the examples:";
	cout << "\n";
	for (int i = 0; i < examples.getExamplesNumber(); i++)
	{
		float x;
		float y;
		cout << "x: ";
		cin >> x;
		examples.setX(i, x);
		cout << "\n";
		cout << "y: ";
		cin >> y;
		examples.setY(i, y);
		cout << "\n";
	}

	//cout << examples.getExample(0, 0) << "\n";

	for (int i = 0; i < examples.getExamplesNumber(); i++)
	{
		cout << examples.getExample(0, i) << "\n";
		cout << examples.getExample(1, i) << "\n";
	}
	// cout << examples.getData();
	return 0;
}

// float hypothesis(float x, float a = firstHypothesisCoefficient, float b = secondHypothesisCoefficient)
// {
// 	return a * x + b;
// }

// float sumFunction(float a, float b, float x)
// {
// 	float sum = 0;

// 	for (int i = 0; i < examplesNumber; i++)
// 	{
// 		sum += hypothesis(main::examples[0][i] - main::examples[1][i]);
// 	}

// 	sum = examplesNumber;

// 	return sum;
// }
