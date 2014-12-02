//#include "stdafx.h"
#include <iostream>
#include <new>
#include <GL/glut.h>
#include <fstream>
#include <string>


using namespace std;

double firstHypothesisCoefficient = 0;
double secondHypothesisCoefficient = 0;
//double firstHypothesisCoefficientGL = -1;
//double secondHypothesisCoefficientGL = 567;
int numberOfExamples = 1;
double *examplesX;
double *examplesY;
double *examplesXGL;
double *examplesYGL;
int w, h;
//int trainingsNumber = 100000;
//int trainingsNumberGL = 100;
double learningFactor = 0.00001;
//double learningFactorGL = 0.000002;
double scaleCoef;
double maxX = 0;
double maxY = 0;
double oldSumFunction;

double scale(int d);
double hypothesis(double x, double a, double b);
double sumFunction(double a, double b);
void setPointsGL();
//void train();


void display(void)
{

	//glColor3f(1, 1, 1);
	//glRasterPos2f(500, 500);
	//int len;
	//len = (int)strlen("Numere");
	//for (int i = 0; i < len; i++) {
	//glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, "Numere"[i]);
	//}

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//glColor3f(0, 1, 1);
	//glBegin(GL_LINES);
	//glVertex2f(0, hypothesis(0, firstHypothesisCoefficientGL, secondHypothesisCoefficientGL));
	//glVertex2f(w, hypothesis(w, firstHypothesisCoefficientGL, secondHypothesisCoefficientGL));
	//glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(70, h - hypothesis(0, firstHypothesisCoefficient, secondHypothesisCoefficient) * scaleCoef - 70);
	glVertex2f(maxX * scaleCoef + 70, h - hypothesis(maxX, firstHypothesisCoefficient, secondHypothesisCoefficient) * scaleCoef - 70);
	glEnd();

	//drawing the axis
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(70, h - 70);
	glVertex2f(70, 70);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(70, h - 70);
	glVertex2f(w - 70, h - 70);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(70, 70);
	glVertex2f(60, 90);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(70, 70);
	glVertex2f(80, 90);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(w - 70, h - 70);
	glVertex2f(w - 90, h - 80);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(w - 70, h - 70);
	glVertex2f(w - 90, h - 60);
	glEnd();

	glColor3f(1, 0, 0);

	for (int r = 0; r < numberOfExamples; r++)  //drawing the points
	{
		for (int i = -2; i < 3; i++)
		{
			for (int q = -2; q < 3; q++)
			{
				glBegin(GL_POINTS);
				glVertex2f(examplesXGL[r] + i, examplesYGL[r] + q);
				glEnd();
			}
		}
	}

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	gluOrtho2D(0, (GLdouble)width, (GLdouble)height, 0);
	glMatrixMode(GL_MODELVIEW);
	w = width;
	h = height;
	setPointsGL();
	//train();
	//cout << "\nFirst coef GL: " << firstHypothesisCoefficientGL << " and the second: " << secondHypothesisCoefficientGL << "\n";

}

int main(int argc, char *argv[])
{
	int cinText = 0;
	cout << "Give me the POINTS! I will tell you the equation and I will draw them. Are you going to write the numbers or should I read them from exemple.txt?.\n Press 0 for writing or 1 for reading from exemple.txt!\n";
	cin >> cinText;
	if (cinText == 1)
	{
		ifstream fs("exemple.txt");
		char c;
		while (fs.get(c))
		{
			if (c == '\n')
				++numberOfExamples;
		}
		fs.close();

		ifstream f("exemple.txt");
		cout << "Number of Exampels: " << numberOfExamples << "\n";

		examplesX = new double[numberOfExamples];
		examplesY = new double[numberOfExamples];
		examplesXGL = new double[numberOfExamples];
		examplesYGL = new double[numberOfExamples];

		int times = 0;
		string n;

		while (getline(f, n))
		{
			int placeSubstring = n.find(", ") + 2;
			//cout << "\n" << placeSubstring << "\n";
			examplesX[times] = atof(n.substr(0, placeSubstring - 2).c_str());
			examplesY[times] = atof(n.substr(placeSubstring).c_str());
			times++;
			// cout << "\nX = " << n.substr(0, placeSubstring - 2);
			// cout << "\nY = " << n.substr(placeSubstring);
		}
		f.close();

		cout << "These are the examples:\n";
		for (int i = 0; i < numberOfExamples; i++)
		{
			cout << examplesX[i] << " ";
			cout << examplesY[i] << "\n";
		}

	}
	else
	{
		cout << "So far so good. Now give me the number of examples: \n";
		cin >> numberOfExamples;
		cout << "\nNow give me the examples:\n";

		examplesX = new double[numberOfExamples];
		examplesY = new double[numberOfExamples];
		examplesXGL = new double[numberOfExamples];
		examplesYGL = new double[numberOfExamples];

		for (int i = 0; i < numberOfExamples; i++)
		{
			double x;
			double y;
			cout << "x: ";
			cin >> x;
			examplesX[i] = x;
			cout << "\n";
			cout << "y: ";
			cin >> y;
			examplesY[i] = y;
			cout << "\n";
		}
	}

	oldSumFunction = sumFunction(firstHypothesisCoefficient, secondHypothesisCoefficient) + 1;
	while (oldSumFunction - sumFunction(firstHypothesisCoefficient, secondHypothesisCoefficient) > 0.0000000001)
	{
		oldSumFunction = sumFunction(firstHypothesisCoefficient, secondHypothesisCoefficient);
		double derivativeA = 0;
		double derivativeB = 0;

		for (int i = 0; i < numberOfExamples; i++)
		{
			derivativeA += (hypothesis(examplesX[i], firstHypothesisCoefficient, secondHypothesisCoefficient) - examplesY[i]) * examplesX[i];
			derivativeB += hypothesis(examplesX[i], firstHypothesisCoefficient, secondHypothesisCoefficient) - examplesY[i];
		}
		derivativeA = derivativeA / numberOfExamples;
		derivativeB = derivativeB / numberOfExamples;
		firstHypothesisCoefficient -= learningFactor * derivativeA;
		secondHypothesisCoefficient -= learningFactor * derivativeB;
	}
	cout << "\n" << "First coefficient: " << firstHypothesisCoefficient << "\n" << "Second coefficinet: " << secondHypothesisCoefficient << "\n" << "SumFunction: " << sumFunction(firstHypothesisCoefficient, secondHypothesisCoefficient) << "\n";
	w = 800;
	h = 600;
	setPointsGL();
	//train();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Dot Prediction");
	//glClearColor(0.8, 0.8, 0.8, 1);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void setPointsGL()
{
	if (w > h)
		scaleCoef = scale(h - 80);
	else
		scaleCoef = scale(w - 80);
	cout << "Scale: " << scaleCoef << "\n";

	for (int i = 0; i < numberOfExamples; i++)
	{
		examplesXGL[i] = 70 + examplesX[i] * scaleCoef;
		examplesYGL[i] = h - examplesY[i] * scaleCoef - 70;
		//cout << "ExamplesGL: " << examplesXGL[i] << " and " << examplesYGL[i] << "\n";
	}

}

//void train()
//{
//	double prevSum = sumFunction(firstHypothesisCoefficientGL, secondHypothesisCoefficientGL, 1) + 1;
//	while (prevSum - sumFunction(firstHypothesisCoefficientGL, secondHypothesisCoefficientGL, 1) > 0.00001)
//	{
//		prevSum = sumFunction(firstHypothesisCoefficientGL, secondHypothesisCoefficientGL, 1);
//		double derivativeAGL = 0;
//		double derivativeBGL = 0;
//		//cout << "DerivativesGL: " << derivativeAGL << " and " << derivativeBGL << "\n";
//		for (int i = 0; i < numberOfExamples; i++)
//		{
//			derivativeAGL += (hypothesis(examplesXGL[i], firstHypothesisCoefficientGL, secondHypothesisCoefficientGL) - examplesYGL[i]) * examplesXGL[i];
//			derivativeBGL += hypothesis(examplesXGL[i], firstHypothesisCoefficientGL, secondHypothesisCoefficientGL) - examplesYGL[i];
//			//cout << "Verificari: " << (hypothesis(examplesXGL[i], firstHypothesisCoefficientGL, secondHypothesisCoefficientGL) - examplesYGL[i]) * examplesXGL[i] << "\n";
//		}
//		derivativeAGL = derivativeAGL / numberOfExamples;
//		derivativeBGL = derivativeBGL / numberOfExamples;
//		//cout << "DerivativesGL: " << derivativeAGL << " and " << derivativeBGL << "\n";
//		firstHypothesisCoefficientGL -= learningFactorGL * derivativeAGL;
//		secondHypothesisCoefficientGL -= learningFactorGL * derivativeBGL;
//	}
//	//	cout << "\nFirst coef GL: " << firstHypothesisCoefficientGL << " and the second: " << secondHypothesisCoefficientGL << "\n";
//}

double scale(int d)
{
	maxX = 0;
	maxY = 0;
	for (int i = 0; i < numberOfExamples; i++)
	{
		if (maxX < examplesX[i])
			maxX = examplesX[i];
		if (maxY < examplesY[i])
			maxY = examplesY[i];
	}
	if (maxX > 0 && maxY > 0)
	{
		if (maxX > maxY)
			return d / maxX;
		else
			return d / maxY;
	}
	else
		return 1;
}



double hypothesis(double x, double a, double b)
{
	return a * x + b;
}

double sumFunction(double a, double b)//, int GL)
{
	double sum = 0;

	//if (GL == 0)
	//{
	for (int i = 0; i < numberOfExamples; i++)
	{
		sum += (hypothesis(examplesX[i], a, b) - examplesY[i]) * (hypothesis(examplesX[i], a, b) - examplesY[i]);
	}
	//}
	//else
	//{
	//	for (int i = 0; i < numberOfExamples; i++)
	//	{
	//		sum += (hypothesis(examplesXGL[i], a, b) - examplesYGL[i]) * (hypothesis(examplesXGL[i], a, b) - examplesYGL[i]);
	//	}
	//}

	sum = sum / (2 * numberOfExamples);

	return sum;
}