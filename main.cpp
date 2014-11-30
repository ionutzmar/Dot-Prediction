//#include "stdafx.h"
#include <iostream>
#include <new>
#include <GL/glut.h>
#include <fstream>
#include <string>


using namespace std;

double firstHypothesisCoefficient = 0;
double secondHypothesisCoefficient = 0;
double firstHypothesisCoefficientGL = 0;
double secondHypothesisCoefficientGL = 0;
int numberOfExamples = 1;
double *examplesX;
double *examplesY;
double *examplesXGL;
double *examplesYGL;
int w, h;
int trainingsNumber = 50000;
int trainingsNumberGL = 1000000;
double learningFactor = 0.001;
double learningFactorGL = 0.000001;
double scaleCoef; 
double maxX = 0;
double maxY = 0;

double scale(int d);
double hypothesis(double x, double a, double b);
double sumFunction(double a, double b);
void setPointsGL();
void train(int trainingsNumberGLV);

void display(void)
{
	
	setPointsGL();

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(0, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(0, hypothesis(0, firstHypothesisCoefficientGL, secondHypothesisCoefficientGL));
	glVertex2f(w, hypothesis(w, firstHypothesisCoefficientGL, secondHypothesisCoefficientGL));
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
		glBegin(GL_POINTS);
		glVertex2f(examplesXGL[r], h - examplesY[r] * scaleCoef - 70);
		glVertex2f(examplesXGL[r] - 1, h - examplesY[r] * scaleCoef - 71);
		glVertex2f(examplesXGL[r] - 1, h - examplesY[r] * scaleCoef - 70);
		glVertex2f(examplesXGL[r] - 1, h - examplesY[r] * scaleCoef - 69);
		glVertex2f(examplesXGL[r], h - examplesY[r] * scaleCoef - 69);
		glVertex2f(70 + examplesX[r] * scaleCoef, h - examplesY[r] * scaleCoef - 71);
		glVertex2f(70 + examplesX[r] * scaleCoef + 1, h - examplesY[r] * scaleCoef - 71);
		glVertex2f(70 + examplesX[r] * scaleCoef + 1, h - examplesY[r] * scaleCoef - 70);
		glVertex2f(70 + examplesX[r] * scaleCoef + 1, h - examplesY[r] * scaleCoef - 69);
		glEnd();

		cout << "Coordonates:" << 70 + (examplesX[r] * scaleCoef) << " and " <<h -  examplesY[r] * scaleCoef - 70  << "\n";
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
	train(trainingsNumberGL);
	cout << "\nFirst coef GL: " << firstHypothesisCoefficientGL << " and the second: " << secondHypothesisCoefficientGL << "\n";
	w = width;
	h = height;
}



// void timer(int value)
// {

// 	glutPostRedisplay();
// 	glutTimerFunc(1, timer, value + 1);
// }


int main(int argc, char *argv[])
{
	int cinText = 0;
	cout << "This program is trying to predict values based on examples. Are you going to write the numbers or should I read them form exemple.txt?.\n Press 0 for writing or 1 for reading from exemple.txt!\n";
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
			cout << examplesX[i] << "\n";
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


	for (int q = 0; q < trainingsNumber; q++)
	{
		double derivativeA = 0;
		double derivativeB = 0;

		//cout << firstHypothesisCoefficient << "\n";

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
	train(trainingsNumberGL * 3);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Dot Prediction");
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
		cout << "ExamplesGL: " << examplesXGL[i] << " and " << examplesYGL[i] << "\n";
	}
}

void train(int trainingsNumberGLV)
{
	for (int q = 0; q < trainingsNumberGLV; q++)
	{
		double derivativeAGL = 0;
		double derivativeBGL = 0;
		//cout << "DerivativesGL: " << derivativeAGL << " and " << derivativeBGL << "\n";
		for (int i = 0; i < numberOfExamples; i++)
		{
			derivativeAGL += (hypothesis(examplesXGL[i], firstHypothesisCoefficientGL, secondHypothesisCoefficientGL) - examplesYGL[i]) * examplesXGL[i];
			derivativeBGL += hypothesis(examplesXGL[i], firstHypothesisCoefficientGL, secondHypothesisCoefficientGL) - examplesYGL[i];
			//cout << "Verificari: " << (hypothesis(examplesXGL[i], firstHypothesisCoefficientGL, secondHypothesisCoefficientGL) - examplesYGL[i]) * examplesXGL[i] << "\n";
		}
		derivativeAGL = derivativeAGL / numberOfExamples;
		derivativeBGL = derivativeBGL / numberOfExamples;
		//cout << "DerivativesGL: " << derivativeAGL << " and " << derivativeBGL << "\n";
		firstHypothesisCoefficientGL -= learningFactorGL * derivativeAGL;
		secondHypothesisCoefficientGL -= learningFactorGL * derivativeBGL;
	}
//	cout << "\nFirst coef GL: " << firstHypothesisCoefficientGL << " and the second: " << secondHypothesisCoefficientGL << "\n";
}

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

double sumFunction(double a, double b)
{
	double sum = 0;

	for (int i = 0; i < numberOfExamples; i++)
	{
		sum += (hypothesis(examplesX[i], a, b) - examplesY[i]) * (hypothesis(examplesX[i], a, b) - examplesY[i]);
		//cout << sum << "\n";
	}

	sum = sum / (2 * numberOfExamples);

	return sum;
}

