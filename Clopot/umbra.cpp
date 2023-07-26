/*
 * umbre.c
 * Rodica Baciu - Programarea aplicatiilor grafice 3D cu OpenGL
 *
 *  Programul arat� cum se determina matricea pentru
 *  calcularea umbrelor. Este reprezentat un cub care se roteste
 *  si care arunc� o umbr� pe un plan.
 */
#include "glos.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>
void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4],
	GLfloat mat[4][4]);
void calcCoeficientiPlan(float P[3][3], float coef[4]);
void CALLBACK rot_y(void);
void CALLBACK rot_x(void);
void cub(GLfloat latura);
void plan(void);
void initlights(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK display(void);

static int yRot = 0; //unghiul de rota�ie �n jurul axei y
static int xRot = 0; //unghiul de rota�ie �n jurul axei x
//pozi�ia sursei de lumin�
static GLfloat pozSursa[] = { 60.0, 200.0, -50.0, 1.0 };

void CALLBACK rot_y(void)
{
	yRot = (yRot + 10) % 360;
}
void CALLBACK rot_x(void)
{
	xRot = (xRot + 10) % 360;
}
void calcCoeficientiPlan(float P[3][3], float coef[4])
{
	float v1[3], v2[3];
	float length;
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;
	//calculeaz� doi vectori din trei puncte
	v1[x] = P[0][x] - P[1][x];
	v1[y] = P[0][y] - P[1][y];
	v1[z] = P[0][z] - P[1][z];

	v2[x] = P[1][x] - P[2][x];
	v2[y] = P[1][y] - P[2][y];
	v2[z] = P[1][z] - P[2][z];

	//se cacluleaz� produsul vectorial al celor doi vectori
	// care reprezint� un al treilea vector perpendicular pe plan 
	// ale c�rui componente sunt chiar coeficien�ii A, B, C din ecua�ia planului
	coef[x] = v1[y] * v2[z] - v1[z] * v2[y];
	coef[y] = v1[z] * v2[x] - v1[x] * v2[z];
	coef[z] = v1[x] * v2[y] - v1[y] * v2[x];
	//normalizeaz� vectorul
	length = (float)sqrt((coef[x] * coef[x]) + (coef[y] * coef[y]) + (coef[z] * coef[z]));
	coef[x] /= length;
	coef[y] /= length;
	coef[z] /= length;
}
//creaz� matricea care d� umbra cunosc�ndu-se coeficien�ii planului �i 
//pozi�ia sursei. �n mat se salveaz� matricea.
void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4],
	GLfloat mat[4][4])
{
	GLfloat coefPlan[4];
	GLfloat temp;
	//determin� coeficien�ii planului
	calcCoeficientiPlan(puncte, coefPlan);
	//determin� si pe D
	coefPlan[3] = -(
		(coefPlan[0] * puncte[2][0]) +
		(coefPlan[1] * puncte[2][1]) +
		(coefPlan[2] * puncte[2][2]));
	//temp=A*xL+B*yL+C*zL+D*w
	temp = coefPlan[0] * pozSursa[0] +
		coefPlan[1] * pozSursa[1] +
		coefPlan[2] * pozSursa[2] +
		coefPlan[3] * pozSursa[3];
	//prima coloan�
	mat[0][0] = temp - pozSursa[0] * coefPlan[0];
	mat[1][0] = 0.0f - pozSursa[0] * coefPlan[1];
	mat[2][0] = 0.0f - pozSursa[0] * coefPlan[2];
	mat[3][0] = 0.0f - pozSursa[0] * coefPlan[3];
	//a doua coloana
	mat[0][1] = 0.0f - pozSursa[1] * coefPlan[0];
	mat[1][1] = temp - pozSursa[1] * coefPlan[1];
	mat[2][1] = 0.0f - pozSursa[1] * coefPlan[2];
	mat[3][1] = 0.0f - pozSursa[1] * coefPlan[3];
	//a treia coloana
	mat[0][2] = 0.0f - pozSursa[2] * coefPlan[0];
	mat[1][2] = 0.0f - pozSursa[2] * coefPlan[1];
	mat[2][2] = temp - pozSursa[2] * coefPlan[2];
	mat[3][2] = 0.0f - pozSursa[2] * coefPlan[3];
	//a patra coloana
	mat[0][3] = 0.0f - pozSursa[3] * coefPlan[0];
	mat[1][3] = 0.0f - pozSursa[3] * coefPlan[1];
	mat[2][3] = 0.0f - pozSursa[3] * coefPlan[2];
	mat[3][3] = temp - pozSursa[3] * coefPlan[3];
}
void plan(void)
{
	glBegin(GL_QUADS);
	glVertex3f(500.0f, -165.0f, -500.0f);
	glVertex3f(-500.0f, -165.0f, -500.0f);
	glVertex3f(-500.0f, -165.0f, 500.0f);
	glVertex3f(500.0f, -165.0f, 500.0f);
	glEnd();
}
void cub(GLfloat latura) //func�ia care deseneaz� cubul 
//cu latura de 2Xlatura si centrat �n origine
//ordinea specific�rii v�rfurilor este invers rotitii acelor de ceasornic
{
	glBegin(GL_QUAD_STRIP);
	glNormal3f(-0.33f, 0.33f, 0.33f);
	glVertex3f(-latura, latura, latura);
	glNormal3f(-0.33f, -0.33f, 0.33f);
	glVertex3f(-latura, -latura, latura);
	glNormal3f(0.33f, 0.33f, 0.33f);
	glVertex3f(latura, latura, latura);
	glNormal3f(0.33f, -0.33f, 0.33f);
	glVertex3f(latura, -latura, latura);
	glNormal3f(0.33f, 0.33f, -0.33f);
	glVertex3f(latura, latura, -latura);
	glNormal3f(0.33f, -0.33f, -0.33f);
	glVertex3f(latura, -latura, -latura);
	glNormal3f(-0.33f, 0.33f, -0.33f);
	glVertex3f(-latura, latura, -latura);
	glNormal3f(-0.33f, -0.33f, -0.33f);
	glVertex3f(-latura, -latura, -latura);
	glNormal3f(-0.33f, 0.33f, 0.33f);
	glVertex3f(-latura, latura, latura);
	glNormal3f(-0.33f, -0.33f, 0.33f);
	glVertex3f(-latura, -latura, latura);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-0.33f, 0.33f, 0.33f);
	glVertex3f(-latura, latura, latura);
	glNormal3f(0.33f, 0.33f, 0.33f);
	glVertex3f(latura, latura, latura);
	glNormal3f(0.33f, 0.33f, -0.33f);
	glVertex3f(latura, latura, -latura);
	glNormal3f(-0.33f, 0.33f, -0.33f);
	glVertex3f(-latura, latura, -latura);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-0.33f, -0.33f, 0.33f);
	glVertex3f(-latura, -latura, latura);
	glNormal3f(-0.33f, -0.33f, -0.33f);
	glVertex3f(-latura, -latura, -latura);
	glNormal3f(0.33f, -0.33f, -0.33f);
	glVertex3f(latura, -latura, -latura);
	glNormal3f(0.33f, -0.33f, 0.33f);
	glVertex3f(latura, -latura, latura);
	glEnd();
}
// set�ri pentru iluminarea suprafe�ei, test ad�ncime
void myinit(void)
{
	GLfloat ambient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 128.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	//permite urm�rirea culorilor
	glEnable(GL_COLOR_MATERIAL);
	//seteaz� propriet��ile de material pentru a urma valorile glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//seteaz� sursa		
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);
	//seteaz� materialul	    
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//alb pentru fundal
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);//ascunderea suprafe�elor
}
void CALLBACK display(void)
{
	GLfloat matUmbra[4][4];
	//oricare trei puncte din plan �n sens CCW
	GLfloat puncte[3][3] = { {-50.0f, -164.0f, -50.0f},
							{-50.0, -164.0f, 50.0},
							{50.0f, -164.0f, 50.0f} };
	//sterge ecranul
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//determin� matricea pentru calcularea umbrei	
	MatriceUmbra(puncte, pozSursa, matUmbra);
	//salveaza starea matricei de modelare-vizualizare si reprezint� cubul rotit
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	glColor3f(1.0f, 0.7f, 0.0f);
	cub(30.0);
	glPopMatrix(); //reface matricea initial�

	//deseneaz� umbra
	//mai �nt�i se dezactiveaz� iluminarea si se salveaz� starea matricei de proiectie
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	//apoi se �nmulteste matricea curent� cu matricea de umbrire
	glMultMatrixf((GLfloat*)matUmbra);
	//si cu cea de rota�ie
	glRotatef(xRot, 1.0, 0.0, 0.0);
	glRotatef(yRot, 0.0, 1.0, 0.0);
	//se deseneaz� cubul-umbr� cu gri
	glColor3f(0.4, 0.4, 0.4);
	cub(30.0);
	glPopMatrix(); //reface matricea de proiec�ie la normal

	//deseneaz� sursa de lumin� ca o sfer� mic� galben� �n pozi�ia real�
	glPushMatrix();
	glTranslatef(pozSursa[0], pozSursa[1], pozSursa[2]);
	glColor3f(1.0, 1.0, 0.0);
	auxSolidSphere(5);
	glPopMatrix();

	//deseneaz� planul
	glColor3f(0.0f, 1.0f, 0.3f);
	plan();

	//restaureaz� starea variabilelor de iluminare
	glPopAttrib();

	glFlush();
}
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-200.0, 200.0, -200.0 * (GLfloat)h / (GLfloat)w,
			200.0 * (GLfloat)h / (GLfloat)w, -200.0, 200.0);
	else
		glOrtho(-200.0 * (GLfloat)w / (GLfloat)h,
			200.0 * (GLfloat)w / (GLfloat)h, -200.0, 200.0, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-30, -1.0f, 1.0f, 1.0f); //transformarea de vizualizare
}
int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_DEPTH16 | AUX_RGB);
	auxInitPosition(10, 10, 400, 400);
	auxInitWindow("Reprezentarea umbrelor");
	myinit();
	// inregistreaza functiile callback rot_y, rot_y
	auxKeyFunc(AUX_RIGHT, rot_y);
	auxKeyFunc(AUX_DOWN, rot_x);
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return(0);
}