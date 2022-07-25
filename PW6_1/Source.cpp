#include<Windows.h>
#include <GL/glut.h> 
#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

struct Point
{
	float x, y, z;
};

vector<Point> v;
vector<vector<int>> faces;
int point_count, face_count;

void reshape(int w, int h);
void display();
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void readfromfile()
{
	float x, y, z;
	Point p;
	ifstream f("object_data.txt", ios::in);
	f >> point_count >> face_count;
	for (int i = 0; i < point_count; i++)
	{
		f >> p.x >> p.y >> p.z;
		v.push_back(p);
	}
	faces.resize(face_count);
	for (int i = 0; i < face_count; i++)
	{
		int n;
		f >> n;
		for (int j = 0; j < n; j++)
		{
			int p;
			f >> p;
			faces[i].push_back(p);
		}
	}
	f.close();
}

int main(int argc, char * argv[])
{
	readfromfile();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("PW6_1");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	glutMainLoop();

	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 10, 0, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	for (int i = 0; i < face_count; i++)
	{
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < faces[i].size(); j++)
		{
			glVertex3f(v[faces[i][j]].x, v[faces[i][j]].y, v[faces[i][j]].z);
		}


		glEnd();
	}
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == 65)
	{
		glMatrixMode(GL_MODELVIEW);
		glTranslated(2, 2, 0);
		display();
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		glMatrixMode(GL_MODELVIEW);
		glTranslated(0, 2, 0);
		display();
		break;
	case GLUT_KEY_DOWN:
		glMatrixMode(GL_MODELVIEW);
		glRotated(5, 1, 1, 1);
		display();
		break;
	}
}
