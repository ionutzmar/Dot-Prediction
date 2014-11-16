#include <iostream>
#include <new>
#include <GL/glut.h>
#include <fstream>
#include <string>

using namespace std;

double firstHypothesisCoefficient = 0;
double secondHypothesisCoefficient = 0;
int numberOfExamples = 1;
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

		examplesX = new double [numberOfExamples];
		examplesY = new double [numberOfExamples];
		
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

		examplesX = new double [numberOfExamples];
		examplesY = new double [numberOfExamples];

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