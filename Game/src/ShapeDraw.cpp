#include <windows.h>											// Header File For Windows
#include "baseTypes.h"
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <math.h>
//#include <stdlib.h>
#include <stdio.h>

const float DEG2RAD = 3.14159f/180.0f;


void DrawCircle(float_t radius, float_t x, float_t y, char8_t r, char8_t g, char8_t b, bool filled)
{
	
	glEnable(GL_POINT_SMOOTH);
	if(!filled)
	{
		glDisable(GL_TEXTURE_2D);
		glColor4ub(r, g, b,0x20);
		// Set the point size
		glPointSize(1.0);
		glBegin(GL_POINTS);
		float_t radiusMax = radius + 2.0f;
		float_t radiusMin = radius - 2.0f;
		for (int i=0; i < 360; i+=3)
		{
			float degInRad = i*DEG2RAD;
			glVertex2f(x + (cos(degInRad)*radius),y + (sin(degInRad)*radius));
			glVertex2f(x + (cos(degInRad)*radiusMax),y + (sin(degInRad)*radiusMax));
			glVertex2f(x + (cos(degInRad)*radiusMin),y + (sin(degInRad)*radiusMin));
		}
		glEnd();
	}
	else
	{
	    glColor4ub(r, g, b,0xFF);
		glEnable(GL_BLEND); 
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		glPointSize(radius/2.0f);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
	}
}

void DrawLine(float_t startX, float_t startY, float_t endX, float_t endY, char8_t r, char8_t g, char8_t b)
{
	glColor3ub(r, g, b);
	// Draw filtered lines
	glEnable(GL_LINE_SMOOTH);

	glBegin(GL_LINE_STRIP);
		glVertex2f(startX, startY);
		glVertex2f(endX, endY);
	glEnd();

}

void DrawAsteroid(float_t x, float_t y, float_t size, char8_t r, char8_t g, char8_t b, float_t rot)
{
	float_t scaleRaduis = size/10.0f;

	glColor3ub(r, g, b);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(scaleRaduis, scaleRaduis, 1);

	glBegin(GL_LINE_LOOP);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(3.5f, 5.0f);
		glVertex2f(4.5f, 5.0f);
		glVertex2f(6.5f, 0.0f);
		glVertex2f(6.5f, -5.0f);
		glVertex2f(4.0f, -3.0f);
		glVertex2f(4.0f, -9.0f);
		glVertex2f(-2.5f, -9.0f);
		glVertex2f(-5.5f, -5.0f);
		glVertex2f(-4.5f, 0.0f);
		glVertex2f(-5.5f, 2.0f);
		glVertex2f(-3.5f, 5.0f);

	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);			
		glVertex2f(0.0f, 0.0f);
		glVertex2f(3.5f, 5.0f);
		glVertex2f(4.5f, 5.0f);
		glVertex2f(6.5f, 0.0f);
		glVertex2f(6.5f, -5.0f);
		glVertex2f(4.0f, -3.0f);
		glVertex2f(4.0f, -9.0f);
		glVertex2f(-2.5f, -9.0f);
		glVertex2f(-5.5f, -5.0f);
		glVertex2f(-4.5f, 0.0f);
		glVertex2f(-5.5f, 2.0f);
		glVertex2f(-3.5f, 5.0f);

	glEnd();
	glPopMatrix();
}

void DrawSaucer(float_t x, float_t y, float_t width, float_t height, char8_t r, char8_t g, char8_t b)
{
	float_t scaleWidth = width / 8.0f;
	float_t scaleHeight = height / 8.0f;

	glColor3ub(r, g, b);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(scaleWidth, scaleHeight, 1);

	glBegin(GL_LINE_LOOP);
		glVertex2f(3.0f, 10.0f);
		glVertex2f(5.0f, 5.0f);
		glVertex2f(10.0f, 0.0f);
		glVertex2f(5.0f, -5.0f);
		glVertex2f(-5.0f, -5.0f);
		glVertex2f(-10.0f, 0.0f);
		glVertex2f(-5.0f, 5.0f);
		glVertex2f(-3.0f, 10.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex2f(-5.0f, 5.0f);
		glVertex2f(5.0f, 5.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex2f(-10.0f, 0.0f);
		glVertex2f(10.0f, 0.0f);
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2f(3.0f, 10.0f);
		glVertex2f(5.0f, 5.0f);
		glVertex2f(10.0f, 0.0f);
		glVertex2f(5.0f, -5.0f);
		glVertex2f(-5.0f, -5.0f);
		glVertex2f(-10.0f, 0.0f);
		glVertex2f(-5.0f, 5.0f);
		glVertex2f(-3.0f, 10.0f);
	glEnd();
	glPopMatrix();
}

void DrawDeathStar(float_t x, float_t y, float_t width, float_t height, 
	char8_t r, char8_t g, char8_t b, float_t rot, int type)
{
	float_t scaleWidth = width / 8.0f;
	float_t scaleHeight = height / 8.0f;

	glColor3ub(r, g, b);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(scaleWidth, scaleHeight, 1);

	if (type == 0) // hexagon
	{
		glBegin(GL_LINE_LOOP);
			glVertex2f(0.f, 6.0f);
			glVertex2f(4.0f, 3.0f);
			glVertex2f(4.0f, -3.0f);
			glVertex2f(0.f, -6.0f);
			glVertex2f(-4.0f, -3.0f);
			glVertex2f(-4.0f, 3.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex2f(0.f, 6.0f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.0f, -3.0f);
			glVertex2f(0.f, -6.0f);
			glVertex2f(-1.0f, -3.0f);
			glVertex2f(0.0f, 0.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex2f(4.0f, -3.0f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(1.5f, 2.5f);
			glVertex2f(4.0f, 3.0f);
			glVertex2f(2.5f, 0.5f);
			glVertex2f(0.0f, 0.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex2f(-4.0f, -3.0f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(-1.5f, 2.5f);
			glVertex2f(-4.0f, 3.0f);
			glVertex2f(-2.5f, 0.5f);
			glVertex2f(0.0f, 0.0f);
			
		glEnd();

		glPointSize(2);
		glBegin(GL_POINTS);
			glVertex2f(0.f, 6.0f);
			glVertex2f(4.0f, 3.0f);
			glVertex2f(4.0f, -3.0f);
			glVertex2f(0.f, -6.0f);
			glVertex2f(-4.0f, -3.0f);
			glVertex2f(-4.0f, 3.0f);
		glEnd();
	}
	else if (type == 1) // diamond
	{
		glBegin(GL_LINE_LOOP);
			glVertex2f(0.f, 10.0f);
			glVertex2f(5.0f, 0.0f);
			glVertex2f(0.f, -10.0f);
			glVertex2f(-5.0f, 0.0f);
			glVertex2f(0.0f, -3.0f);
			glVertex2f(5.0f, 0.0f);
			glVertex2f(0.0f, 3.0f);
			glVertex2f(-5.0f, 0.0f);
			glVertex2f(0.f, 10.0f);
		glEnd();

		glPointSize(2);
		glBegin(GL_POINTS);
			glVertex2f(0.f, 10.0f);
			glVertex2f(5.0f, 0.0f);
			glVertex2f(0.f, -10.0f);
			glVertex2f(-5.0f, 0.0f);
			glVertex2f(0.0f, -3.0f);
			glVertex2f(5.0f, 0.0f);
			glVertex2f(0.0f, 3.0f);
			glVertex2f(-5.0f, 0.0f);
			glVertex2f(0.f, 10.0f);
		glEnd();
	}
	else if (type == 2) //triangle
	{
		glBegin(GL_LINE_LOOP);
			glVertex2f(0.f, 5.0f);
			glVertex2f(5.0f, -5.0f);
			glVertex2f(0.0f, -2.0f);
			glVertex2f(-5.0f, -5.0f);
		glEnd();

		glPointSize(2);
		glBegin(GL_POINTS);
			glVertex2f(0.f, 5.0f);
			glVertex2f(5.0f, -5.0f);
			glVertex2f(0.0f, -2.0f);
			glVertex2f(-5.0f, -5.0f);
		glEnd();
	}
	
	glPopMatrix();
}

void DrawSpaceShip(float_t x, float_t y, float_t width, float_t height, char8_t r, char8_t g, char8_t b, float_t rot)
{
	float_t scaleWidth = width/8.0f;
	float_t scaleHeight = height/8.0f;

	glColor3ub(r, g, b);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(scaleWidth, scaleHeight, 1);

	glBegin(GL_LINE_LOOP);
		glVertex2f(0.f, 10.0f);
		glVertex2f(3.5f, -5.0f);
		glVertex2f(2.0f, -4.0f);
		glVertex2f(-2.0f, -4.0f);
		glVertex2f(-3.5f, -5.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
		glVertex2f(0.f, 3.0f);
		glVertex2f(6.0f, -1.5f);
		glVertex2f(4.0f, -4.0f);
		glVertex2f(-4.0f, -4.0f);
		glVertex2f(-6.0f, -1.5f);
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);			
		glVertex2f(0.f, 10.0f);
		glVertex2f(3.5f, -5.0f);
		glVertex2f(2.0f, -4.0f);
		glVertex2f(-2.0f, -4.0f);
		glVertex2f(-3.5f, -5.0f);
	glEnd();
	glPopMatrix();
}

void DrawShield(float_t x, float_t y, float_t width, float_t height, char8_t r, char8_t g, char8_t b) 
{
	float_t scaleWidth = width / 8.0f;
	float_t scaleHeight = height / 8.0f;

	glColor3ub(r, g, b);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(scaleWidth, scaleHeight, 1);

	glBegin(GL_LINE_LOOP);
		glVertex2f(0.f, 6.0f);
		glVertex2f(4.0f, 3.0f);
		glVertex2f(4.0f, -3.0f);
		glVertex2f(0.f, -6.0f);
		glVertex2f(-4.0f, -3.0f);
		glVertex2f(-4.0f, 3.0f);
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
		glVertex2f(0.f, 6.0f);
		glVertex2f(4.0f, 3.0f);
		glVertex2f(4.0f, -3.0f);
		glVertex2f(0.f, -6.0f);
		glVertex2f(-4.0f, -3.0f);
		glVertex2f(-4.0f, 3.0f);
	glEnd();
	glPopMatrix();
}

void DrawLetter(float_t x, float_t y, char8_t r, char8_t g, char8_t b, char8_t letter, float_t size)
{
	glColor3ub(r, g, b);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	glBegin(GL_LINES);	
	switch (letter) 
	{
		case 'A':
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 0.5);

			glVertex2f(0.0, 0.5);
			glVertex2f(0.5, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, -1.0);
		
			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, 0.5);

			glVertex2f(1.0, 0.5);
			glVertex2f(0.5, 1.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);
			break;
		case 'B':
			//upper half
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(0.8, 1.0);

			glVertex2f(0.8, 1.0);
			glVertex2f(1.0, 0.8);

			glVertex2f(1.0, 0.8);
			glVertex2f(1.0, 0.2);

			glVertex2f(1.0, 0.2);
			glVertex2f(0.8, 0.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.8, 0.0);

			//lower half
			glVertex2f(0.0, 0.0);
			glVertex2f(0.8, 0.0);

			glVertex2f(0.8, 0.0);
			glVertex2f(1.0, -0.2);

			glVertex2f(1.0, -0.2);
			glVertex2f(1.0, -0.8);

			glVertex2f(1.0, -0.8);
			glVertex2f(0.8, -1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(0.8, -1.0);

			break;
		case 'C':
			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);
			break;
		case 'D':
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(0.5, 1.0);

			glVertex2f(0.5, 1.0);
			glVertex2f(1.0, 0.5);

			glVertex2f(1.0, 0.5);
			glVertex2f(1.0, -0.5);

			glVertex2f(0.0, -1.0);
			glVertex2f(0.5, -1.0);

			glVertex2f(0.5, -1.0);
			glVertex2f(1.0, -0.5);
			break;
		case 'E':
			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, -1.0);
			break;
		case 'F':
			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, -1.0);
			break;
		case 'G':
			glVertex2f(0.5, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);
			break;
		case 'H':
			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);
			break;
		case 'I':
			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.5, 1.0);
			glVertex2f(0.5, -1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, -1.0);
			break;
		case 'J':
			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.5, 1.0);
			glVertex2f(0.5, -1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(0.5, -1.0);
			break;
		case 'K':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, -1.0);
			break;
		case 'L':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, -1.0);
			break;
		case 'M':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(0.5, -0.5);

			glVertex2f(0.5, -0.5);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);
			break;
		case 'N':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(1.0, 1.0);
			break;
		case 'O':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);
			break;
		case 'P':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(0.0, 0.0);
			break;
		case 'Q':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(0.5, -1.5);
			glVertex2f(1.0, -1.0);
			break;
		case 'R':
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(0.0, 0.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, -1.0);
			break;
		case 'S':
			glVertex2f(1.0, 1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(0.0, 0.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);
			break;

		case 'T':
			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.5, 1.0);
			glVertex2f(0.5, -1.0);
			break;
		case 'U':
			glVertex2f(0.0, 1.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(1.0, 1.0);
			break;
		case 'V':
			glVertex2f(0.0, 1.0);
			glVertex2f(0.5, -1.0);

			glVertex2f(0.5, -1.0);
			glVertex2f(1.0, 1.0);
			break;
		case 'W':
			glVertex2f(0.0, 1.0);
			glVertex2f(0.25, -1.0);

			glVertex2f(0.25, -1.0);
			glVertex2f(0.5, 1.0);

			glVertex2f(0.5, 1.0);
			glVertex2f(0.75, -1.0);

			glVertex2f(0.75, -1.0);
			glVertex2f(1.0, 1.0);
			break;
		case 'X':
			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, -1.0);
			break;
		case 'Y':
			glVertex2f(0.0, 1.0);
			glVertex2f(0.5, 0.0);

			glVertex2f(0.5, 0.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.5, 0.0);
			glVertex2f(0.5, -1.0);
			break;
		case 'Z':
			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(0.0, -1.0);
			break;
		default:
			break;
	}

	glEnd();
	glPopMatrix();
}

void DrawLetters(float_t x, float_t y, char8_t r, char8_t g, char8_t b, char8_t* letters, int arrayCount, float_t size)
{
	float_t offset = 0.0f;

	for (int i = 0; i < arrayCount; i++)
	{
		offset += size + size / 2;
		DrawLetter(x+ offset, y, r, g, b, letters[i], size);
	}
}

void DrawNumber(float_t x, float_t y, char8_t r, char8_t g, char8_t b, int number, float_t size)
{
	glColor3ub(r, g, b);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	glBegin(GL_LINES);
	switch (number) 
	{
		case 0:
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);
			break;
		case 1:
			glVertex2f(0.5, -1.0);
			glVertex2f(0.5, 1.0);
			break;
		case 2:
			glVertex2f(1.0, 1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);
			break;
		case 3:
			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, -1.0);
			break;
		case 4:
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);
			break;
		case 5:
			glVertex2f(1.0, 1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(0.0, 0.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);
			break;
		case 6:
			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 0.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);

			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);
			break;
		case 7:
			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);
			break;
		case 8:
			glVertex2f(0.0, -1.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(1.0, -1.0);
			glVertex2f(0.0, -1.0);
			break;
		case 9:
			glVertex2f(0.0, 1.0);
			glVertex2f(1.0, 1.0);

			glVertex2f(1.0, 1.0);
			glVertex2f(1.0, -1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 1.0);

			glVertex2f(0.0, 0.0);
			glVertex2f(1.0, 0.0);
			break;
		default:
			break;
	}

	glEnd();
	glPopMatrix();
}

void DrawNumbers(float_t x, float_t y, char8_t r, char8_t g, char8_t b, int* numbers, int arrayCount, float_t size)
{
	float_t offset = 0.0f;

	for (int i = 0; i < arrayCount; i++)
	{
		offset += size + size/2;
		DrawNumber(x + offset, y, r, g, b, numbers[i], size);
	}
}
