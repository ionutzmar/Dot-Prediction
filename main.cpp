#include <iostream>
#include <new>
#include <GL/glut.h>
#include <fstream>

using namespace std;

double firstHypothesisCoefficient = 0;
double secondHypothesisCoefficient = 0;
int numberOfExamples;
double *examplesX;
double *examplesY;
int w, h;
int trainingsNumber = 50000;
double learningFactor = 0.00001;

double hypothesis(double x, double a = firstHypothesisCoefficient, double b = secondHypothesisCoefficient);
double sumFunction(double a, double b);

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		//glVertex2f(0, -f(-w / 2) + h / 2);
		//glVertex2f(w, -f(w / 2) + h / 2);
		glVertex2f(0, h - hypothesis(0, firstHypothesisCoefficient, secondHypothesisCoefficient));
		glVertex2f(w, h - hypothesis(w, firstHypothesisCoefficient, secondHypothesisCoefficient));
	glEnd();

	glColor3f(1, 0, 0);

	for (int r = 0; r < numberOfExamples; r++)
	{
		glBegin(GL_POINTS);
		glVertex2f(examplesX[r], h - examplesY[r]);
		glVertex2f(examplesX[r] - 1, h - examplesY[r] - 1);
		glVertex2f(examplesX[r] - 1, h - examplesY[r]);
		glVertex2f(examplesX[r] - 1, h - examplesY[r] + 1);
		glVertex2f(examplesX[r], h - examplesY[r] + 1);
		glVertex2f(examplesX[r], h - examplesY[r] - 1);
		glVertex2f(examplesX[r] + 1, h - examplesY[r] - 1);
		glVertex2f(examplesX[r] + 1, h - examplesY[r]);
		glVertex2f(examplesX[r] + 1, h - examplesY[r] + 1);
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
	//cin >> numberOfExamples; //////////////////////////////////////////////////////////////////////////////////////////// Se decomenteaza AICI
	
	numberOfExamples = 4;

	examplesX = new double [numberOfExamples];
	examplesY = new double [numberOfExamples];
	
	int times = 0;
	double n;
	int counter = 0;
	ifstream f("exemple.txt");
	while (f >> n)
	{
		cout << n << "\n";
		if (counter == 0)
		{
			examplesX[times / 2] = n;
			counter = 1;
		}
		else
		{
			examplesY[(times - 1) / 2] = n;
			counter = 0;
		}
		times++;
	}
	f.close();

	cout << "\n";



	cout << "Now give me the examples:";
	cout << "\n";

	// for (int i = 0; i < numberOfExamples; i++) //////////////////////////////////////////////// Se decomenteaza AICI
	// {
	// 	double x;
	// 	double y;
	// 	cout << "x: ";
	// 	cin >> x;
	// 	examplesX[i] = x;
	// 	cout << "\n";
	// 	cout << "y: ";
	// 	cin >> y;
	// 	examplesY[i] = y;
	// 	cout << "\n";
	// }

	// for (int i = 0; i < numberOfExamples; i++)
	// {
	// 	cout << examplesX[i] << "\n";
	// 	cout << examplesY[i] << "\n";
	// }



	for (int q = 0; q < trainingsNumber; q++)
	{
		double derivativeA = 0;
		double derivativeB = 0;

		//cout << firstHypothesisCoefficient << "\n";

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

	sum = sum / ( 2 * numberOfExamples);

	return sum;
}
