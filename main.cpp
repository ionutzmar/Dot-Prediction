#include <iostream>
#include <new>
#include <GL/glut.h>

#include <time.h>
#include <stdlib.h>

using namespace std;

float firstHypothesisCoefficient = 0;
float secondHypothesisCoefficient = 0;
int numberOfExamples;
float *examplesX;
float *examplesY;
int w, h;
int trainingsNumber = 5000;
float learningFactor = 0.01;

float hypothesis(float x, float a = firstHypothesisCoefficient, float b = secondHypothesisCoefficient);
float sumFunction(float a, float b);


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1, 0, 0);

	for (int r = 0; r < numberOfExamples; r++)
	{
		glBegin(GL_POINTS);
		glVertex2f(examplesX[r], examplesY[r]);
		glEnd();
	}



	glColor3f(0, 1, 0);
	// glBegin(GL_LINES);
	// 	glVertex2f(0, -p.f(-w / 2) + h / 2);
	// 	glVertex2f(w, -p.f(w / 2) + h / 2);
	// glEnd();

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
	gluOrtho2D(0, (GLdouble) width, (GLdouble) height, 0);
	glMatrixMode(GL_MODELVIEW);

	w = width;
	h = height;
}

void initialize(void)
{
	glClearColor(0, 0, 0, 1);

	srand (time(NULL));
}

// void timer(int value)
// {
	
// 	glutPostRedisplay();
// 	glutTimerFunc(1, timer, value + 1);
// }


int main(int argc, char *argv[])
{
	
	cout << "This program is trying to predict values based on examples. Now give me the number of examples: \n";
	cin >> numberOfExamples;
	cout << "\n";

	examplesX = new float [numberOfExamples];
	examplesY = new float [numberOfExamples];

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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Dot Prediction");

	initialize();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//glutTimerFunc(1, timer, 0);

	glutMainLoop();

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
