#include "glut.h"
#include "glu.h"
#include "gl.h"
#include "GLAUX.H"
#include <math.h>

void myinit(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK display(void);

int x = 0, y = 0, z = 0, xObiect = 0, yObiect = 0, zObiect = 0, bilaX = 0, bilaZ = 0, razaCercExterior = 29, sleep = 20, v = 30, w = -30;
int xSursa = -100, ySursa = 100, zSursa = 0;

GLfloat texturePoints[2][2][2] = { {{0.0, 0.0}, {0.0, 1.0}},  {{1.0, 0.0}, {1.0, 1.0}} }; // punctele de control pentru textura

#pragma region MiscareObiecte

void CALLBACK CresteXSursa()
{
    //xSursa = (xSursa + 5) % 360;
    xSursa += 10;
}
void CALLBACK ScadeXSursa()
{
    //xSursa = (xSursa - 5) % 360;
    xSursa -= 10;
}

void CALLBACK CresteYSursa()
{
    //ySursa = (ySursa + 5) % 360;
    ySursa += 10;
}
void CALLBACK ScadeYSursa()
{
    //ySursa = (ySursa - 5) % 360;
    ySursa -= 10;
}

void CALLBACK CresteZSursa()
{
    //zSursa = (zSursa + 5) % 360;
    zSursa += 10;
}
void CALLBACK ScadeZSursa()
{
    //zSursa = (zSursa - 5) % 360;
    zSursa -= 10;
}

void CALLBACK CresteXObiect()
{
    xObiect += 10;
}
void CALLBACK ScadeXObiect()
{
    xObiect -= 10;
}

void CALLBACK CresteYObiect()
{
    yObiect += 5;
}
void CALLBACK ScadeYObiect()
{
    yObiect -= 5;
}

void CALLBACK CresteZObiect()
{
    zObiect += 5;
}
void CALLBACK ScadeZObiect()
{
    zObiect -= 5;
}

void CALLBACK CresteX()
{
    x = (x + 10) % 360;
}
void CALLBACK ScadeX()
{
    x = (x - 10) % 360;
}

void CALLBACK CresteY()
{
    y = (y + 10) % 360;
}
void CALLBACK ScadeY()
{
    y = (y - 10) % 360;
}

void CALLBACK CresteZ()
{
    z = (z + 10) % 360;
}
void CALLBACK ScadeZ()
{
    z = (z - 10) % 360;
}


void CALLBACK CresteBilaX()//fata
{
    if (bilaX * bilaX + bilaZ * bilaZ < razaCercExterior * razaCercExterior)
        bilaX++;
    else
    {
        //sunet
        while (bilaZ != 0)
        {
            if (bilaZ > 0)
            {
                bilaZ--;
                display();
                Sleep(sleep);
            }
            else if (bilaZ < 0)
            {
                bilaZ++;
                display();
                Sleep(sleep);
            }
        }
        while (bilaX != 0)
        {
            if (bilaX > 0)
            {
                bilaX--;
                display();
                Sleep(sleep);
            }
            else if (bilaX < 0)
            {
                bilaX++;
                display();
                Sleep(sleep);
            }
        }
    }
}
void CALLBACK ScadeBilaX()//spate
{
    if (bilaX * bilaX + bilaZ * bilaZ < razaCercExterior * razaCercExterior)
        bilaX--;
    else
    {
        //sunet
        while (bilaZ != 0)
        {
            if (bilaZ > 0)
            {
                bilaZ--;
                display();
                Sleep(sleep);
            }
            else if (bilaZ < 0)
            {
                bilaZ++;
                display();
                Sleep(sleep);
            }
        }
        while (bilaX != 0)
        {
            if (bilaX > 0)
            {
                bilaX--;
                display();
                Sleep(sleep);
            }
            else if (bilaX < 0)
            {
                bilaX++;
                display();
                Sleep(sleep);
            }
        }
    }
}


void CALLBACK CresteBilaZ()//dreapta
{
    if (bilaX * bilaX + bilaZ * bilaZ < razaCercExterior * razaCercExterior)
        bilaZ++;
    else
    {
        //sunet
        while (bilaZ != 0)
        {
            if (bilaZ > 0)
            {
                bilaZ--;
                display();
                Sleep(sleep);
            }
            else if (bilaZ < 0)
            {
                bilaZ++;
                display();
                Sleep(sleep);
            }
        }
        while (bilaX != 0)
        {
            if (bilaX > 0)
            {
                bilaX--;
                display();
                Sleep(sleep);
            }
            else if (bilaX < 0)
            {
                bilaX++;
                display();
                Sleep(sleep);
            }
        }
    }
}
void CALLBACK ScadeBilaZ()//stanga
{
    if (bilaX * bilaX + bilaZ * bilaZ < razaCercExterior * razaCercExterior)
        bilaZ--;
    else
    {
        //sunet
        while (bilaZ != 0)
        {
            if (bilaZ > 0)
            {
                bilaZ--;
                display();
                Sleep(sleep);
            }
            else if (bilaZ < 0)
            {
                bilaZ++;
                display();
                Sleep(sleep);
            }
        }
        while (bilaX != 0)
        {
            if (bilaX > 0)
            {
                bilaX--;
                display();
                Sleep(sleep);
            }
            else if (bilaX < 0)
            {
                bilaX++;
                display();
                Sleep(sleep);
            }
        }
    }
}

#pragma endregion

GLfloat ctrlpoints[9][9][3] = {
    {{30, 0, 0},                {29.4241, 5.84978, 0},       {27.7187, 11.475, 0},       {24.9491, 16.6597, 0},       {21.2216, 21.2048, 0},       {16.6795, 24.9358, 0},      {11.4971, 27.7095, 0},      {5.87321, 29.4195, 0},    {0.0238898, 30, 0}},
    {{29.4054, -5.94348, 0},    {29.5, 0, 3},                {28.4958, 7.63138, 3},      {25.5517, 14.7432, 3},       {20.868, 20.8513, 3},        {14.7636, 25.5399, 3},      {7.65407, 28.4897, 3},      {0.0234916, 29.5, 3},     {-5.82635, 29.4288, 0}},
    {{27.682, -11.5632, 0},     {28.4714, -7.72211, 3},      {3, 0, 42},                  {2.77187, 1.1475, 42},        {2.12216, 2.12048, 42},       {1.14971, 2.77095, 42},      {0.00238898, 3, 42},         {-7.60869, 28.5019, 3},   {-11.4529, 27.7278, 0}},
    {{24.8959, -16.739, 0},     {25.5046, -14.8245, 3},      {2.7682, -1.15632, 42},      {8, 0, 75},                  {5.65911, 5.6546, 75},      {0.00637061, 8, 75},        {-1.14529, 2.77278, 42},     {-14.7229, 25.5634, 3},   {-16.6398, 24.9623, 0}},
    {{21.154, -21.2722, 0},     {20.8014, -20.9177, 3},      {2.1154, -2.12722, 42},      {5.64107, -5.6726, 75},     {0, 0, 0},                   {-5.65009, 5.66361, 75},     {-2.11878, 2.12385, 42},     {-20.8347, 20.8846, 3},   {-21.1878, 21.2385, 0}},
    {{16.6, -24.9888, 0},       {14.6821, -25.5868, 3},      {1.14087, -2.7746, 42},      {-0.0191118, -7.99998, 75}, {-5.6681, -5.64558, 75},     {-7.99999, 0.0127412, 75},       {-2.77004, 1.15191, 42},     {-25.5282, 14.7839, 3},   {-24.9225, 16.6994, 0}},
    {{11.4087, -27.746, 0},     {7.56328, -28.514, 3},       {-0.00716693, -2.99999, 42}, {-1.15412, -2.76912, 42},     {-2.12554, -2.11709, 42},     {-2.77369, -1.14308, 42},    {-3, 0.00477796, 42},        {-28.4836, 7.67675, 3},   {-27.7004, 11.5191, 0}},
    {{5.77947, -29.438, 0},     {-0.0704749, -29.4999, 3},   {-7.69943, -28.4775, 3},    {-14.8042, -25.5164, 3},     {-20.9011, -20.8181, 3},     {-25.5751, -14.7025, 3},    {-28.5079, -7.58599, 3},    {-29.5, 0.0469833, 3},    {-29.4148, 5.89664, 0}},
    {{-0.0716693, -29.9999, 0}, {-5.92006, -29.4101, 0},     {-11.5412, -27.6912, 0},    {-16.7192, -24.9092, 0},     {-21.2554, -21.1709, 0},     {-24.9756, -16.6199, 0},    {-27.7369, -11.4308, 0},    {-29.4334, -5.80291, 0},  {-30, 0.0477796, 0}},
};

GLuint textureId1;

GLuint incarcaTextura(const char* s)
{
    GLuint textureId = 0;
    AUX_RGBImageRec* pImagineTextura = auxDIBImageLoad(s);

    if (pImagineTextura != NULL)
    {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, pImagineTextura->sizeX, pImagineTextura->sizeY,
            0, GL_RGB, GL_UNSIGNED_BYTE, pImagineTextura->data);
    }
    if (pImagineTextura)
    {
        if (pImagineTextura->data) {
            free(pImagineTextura->data);
        }
        free(pImagineTextura);
    }
    return textureId;
}



void calcCoeficientiPlan(float P[3][3], float coef[4]) {
    float v1[3], v2[3];
    float length;
    static const int x = 0, y = 1, z = 2;

    // calculeaza 2 vectori din 3 pct
    v1[x] = P[0][x] - P[1][x];
    v1[y] = P[0][y] - P[1][y];
    v1[z] = P[0][z] - P[1][z];
    v2[x] = P[1][x] - P[2][x];
    v2[y] = P[1][y] - P[2][y];
    v2[z] = P[1][z] - P[2][z];

    //se calc produsul vectorial al celor 2 vectori => al3lea vector cu componentele A,B,C chiar coef din ec. planului
    coef[x] = v1[y] * v2[z] - v1[z] * v2[y];
    coef[y] = v1[z] * v2[x] - v1[x] * v2[z];
    coef[z] = v1[x] * v2[y] - v1[y] - v2[x];

    //normalizare vector
    length = (float)sqrt(coef[x] * coef[x] + coef[y] * coef[y] + coef[z] * coef[z]);
    coef[x] /= length;
    coef[y] /= length;
    coef[z] /= length;
}

void MatriceUmbra(GLfloat puncte[3][3], GLfloat pozSursa[4], GLfloat mat[4][4]) {
    // creeaza matricea care da umbra cunoscandu-se coeficientului planului + pozitia sursei
    // IN mat SE SALVEAZA MATRICEA

    GLfloat coefPlan[4], temp;

    //determina coef planului
    calcCoeficientiPlan(puncte, coefPlan);

    // determinam D
    coefPlan[3] = -(coefPlan[0] * puncte[2][0] + coefPlan[1] * puncte[2][1] + coefPlan[2] * puncte[2][2]);

    // temp= AxL + ByL + CzL + Dw
    temp = coefPlan[0] * pozSursa[0] + coefPlan[1] * pozSursa[1] + coefPlan[2] * pozSursa[2] + coefPlan[3] * pozSursa[3];

    //prima coloana
    mat[0][0] = temp - coefPlan[0] * pozSursa[0];
    mat[1][0] = 0.0f - coefPlan[1] * pozSursa[0];
    mat[2][0] = 0.0f - coefPlan[2] * pozSursa[0];
    mat[3][0] = 0.0f - coefPlan[3] * pozSursa[0];
    //a 2a coloana
    mat[0][1] = 0.0f - coefPlan[0] * pozSursa[1];
    mat[1][1] = temp - coefPlan[1] * pozSursa[1];
    mat[2][1] = 0.0f - coefPlan[2] * pozSursa[1];
    mat[3][1] = 0.0f - coefPlan[3] * pozSursa[1];
    //a 3a coloana
    mat[0][2] = 0.0f - coefPlan[0] * pozSursa[2];
    mat[1][2] = 0.0f - coefPlan[1] * pozSursa[2];
    mat[2][2] = temp - coefPlan[2] * pozSursa[2];
    mat[3][2] = 0.0f - coefPlan[3] * pozSursa[2];
    //a4a coloana
    mat[0][3] = 0.0f - coefPlan[0] * pozSursa[3];
    mat[1][3] = 0.0f - coefPlan[1] * pozSursa[3];
    mat[2][3] = 0.0f - coefPlan[2] * pozSursa[3];
    mat[3][3] = temp - coefPlan[3] * pozSursa[3];
}



void plan(void)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    //podea
    glColor3f(0.0f, 1.0f, 0.3f);
    glVertex3f(500.0f, -165.0f, -700.0f);
    glVertex3f(-500.0f, -165.0f, -700.0f);
    glVertex3f(-500.0f, -165.0f, 700.0f);
    glVertex3f(500.0f, -165.0f, 700.0f);

    //spate
    glColor3f(1, 0.31764705882, 0);
    glRotatef(90, 1, 0, 0);

    glVertex3f(500.0f, -195.0f, -500.0f);
    glVertex3f(-500.0f, -195.0f, -500.0f);
    glVertex3f(-500.0f, 195.0f, -500.0f);
    glVertex3f(500.0f, 195.0f, -500.0f);
    
    glPopMatrix();
    glEnd();
}

void cruce(boolean umbra)
{
    glPushMatrix();
    if (umbra)
    glColor3f(0.8510, 0.6039, 0.0353);

    glPushMatrix();
    glRotatef(-30, 1, 0, 0);
    glTranslatef(0, 2, 8);
    auxSolidCylinder(0.5, 5);
    glPopMatrix();


    glPushMatrix();
    glRotatef(90, 0, 0, 1);
    glTranslatef(5, 0.6, 6.3);
    auxSolidCylinder(0.5, 3);
    glPopMatrix();

    glPopMatrix();


    glPushMatrix();
    if (umbra)
    glColor3f(0.5608, 0.1882, 0.0392);

    glPushMatrix();
    glTranslatef(2, 5.05, 6.3);
    auxSolidSphere(0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2, 5.05, 6.3);
    auxSolidSphere(0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 6.9, 5.5);
    auxSolidSphere(0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.5, 7.7);
    auxSolidSphere(0.7);
    glPopMatrix();

    glPopMatrix();
}

void clopot(boolean umbra)
{

#pragma region RotireObiectComplet
    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);
    glRotatef(z, 0, 0, 1);
    
    glTranslatef(xObiect, 0, 0);
    glTranslatef(0, yObiect, 0);
    glTranslatef(0, 0, zObiect);
#pragma endregion

#pragma region Clopot

    glMap2f(GL_MAP2_VERTEX_3,   // Target: The type of data to generate from control points
        0.0, 1.0,           // U Range: The range of the u parameter (horizontal)
        3,                  // U Stride: The number of floats between control points in the u direction
        9,                  // U Order: The order of the polynomial in the u direction (u order = number of control points in the u direction)
        0.0, 1.0,           // V Range: The range of the v parameter (vertical)
        27,                 // V Stride: The number of floats between control points in the v direction
        9,                  // V Order: The order of the polynomial in the v direction (v order = number of control points in the v direction)
        &ctrlpoints[0][0][0]// Pointer to the control points array
    );
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texturePoints[0][0][0]); // pt textura

    glEnable(GL_MAP2_VERTEX_3); // validarea tipului de evaluare GL_MAP2_VERTEX_3
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0); // intervalele de esantionare 
    // a suprafetei pentru parametrii u si v


    glPushMatrix();
    glScalef(0.5, 0.45, 0.5);

    if(umbra)
        glColor3f(0.7882, 0.6471, 0.2118);

    glTranslatef(0, -20, 0);
    glRotatef(-90.0, 1, 0, 0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20); // specifica modul
    // de redare al poligoanelor (GL_FILL, GL_POINT, GL_LINE, 
    // si intervalele de esantionare a suprafetei pentru u si v

    glPopMatrix();
#pragma endregion  

#pragma region Torus
    glPushMatrix();

    glRotatef(90, 1, 0, 0);
    auxSolidTorus(0.5, 9.75);

    glPopMatrix();
#pragma endregion

    glPushMatrix();

#pragma region RotireInterior
    glTranslatef(0, 11.35, 0);
    glRotatef(bilaX, 1, 0, 0);
    glRotatef(bilaZ, 0, 0, 1);
    glTranslatef(0, -11.35, 0);
#pragma endregion


#pragma region InteriorClopot
    //suport bila
    glPushMatrix();
    if (umbra)
    glColor3f(0.4118, 0.2235, 0.0627);

    glTranslatef(0, 11.35, 0);
    auxSolidCylinder(0.5, 20);
    glPopMatrix();

    //bila
    glPushMatrix();
    if (umbra)
    glColor3f(0.7882, 0.6471, 0.2118);

    glTranslatef(0, -9, 0);
    auxSolidSphere(2);
    glPopMatrix();
#pragma endregion

    glPopMatrix();

#pragma region Maner
    //suport maner
    glPushMatrix();
    if (umbra)
    glColor3f(0.4, 0.2392, 0.102);
    glTranslatef(0, 21.3, 0);
    auxSolidCylinder(1, 10);
    glPopMatrix();

    //maner
    glPushMatrix();
    if (umbra)
    glColor3f(0.4706, 0.4706, 0.4706);
    glTranslatef(0, 24.5, 0);
    auxSolidTorus(0.8, 3);
    glPopMatrix();
#pragma endregion  

#pragma region Cruci
    glPushMatrix();

    glPushMatrix(); // cruce1
    cruce(umbra);
    glPopMatrix();


    glPushMatrix(); //cruce2
    glRotatef(180, 0, 1, 0);
    cruce(umbra);
    glPopMatrix();


    glPushMatrix(); //cruce3
    glRotatef(90, 0, 1, 0);
    cruce(umbra);
    glPopMatrix();


    glPushMatrix(); //cruce4
    glRotatef(-90, 0, 1, 0);
    cruce(umbra);
    glPopMatrix();

    glPopMatrix();
#pragma endregion

}



void CALLBACK IdleFunction()
{
    for (bilaZ = v; bilaZ > w; bilaZ--)
    {
        display();
        Sleep(sleep);
    }

    for (bilaZ = w; bilaZ < v; bilaZ++)
    {
        display();
        Sleep(sleep);
    }

    if (w && v)
    {
        w += 2;
        v -= 2;
    }
    else
    {
        auxIdleFunc(NULL);
    }
    /*while (bilaZ < 29)
    {
        bilaZ++;
        display();
        Sleep(sleep);
    }

    while (bilaZ > -29)
    {
        bilaZ--;
        display();
        Sleep(sleep);
    }*/

}

void CALLBACK display(void)
{
    GLfloat pozSursa[] = { xSursa, ySursa, zSursa, 1.0 };

    GLfloat matUmbra[4][4];

    GLfloat puncte[3][3] = { 
        {-200.0f, -164.0f, -200.0f},
        {-200.0, -164.0f, 200.0},
        {200.0f, -164.0f, 200.0f} 
    };

    MatriceUmbra(puncte, pozSursa, matUmbra);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#pragma region Clopot
    glPushMatrix();

    glRotatef(-20, 1, 0, 0);
    glScalef(3, 3, 3);
    glTranslatef(0, -20, 0);
    clopot(1);

    glPopMatrix();
#pragma endregion

#pragma region Umbra
    
    glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glMultMatrixf((GLfloat*)matUmbra);// se inmulteste matricea curenta cu matricea de umbrire
    glColor3f(0.4, 0.4, 0.4);
    clopot(0);
    glEnable(GL_TEXTURE_2D);
    glPopAttrib();
    glPopMatrix();

    glPopMatrix();
#pragma endregion

#pragma region Sursa
    glPushMatrix();

    //glRotated((GLdouble)xSursa, 1.0, 0.0, 0.0);//rotatia sursei
    //glRotated((GLdouble)ySursa, 0.0, 1.0, 0.0);//rotatia sursei
    //glRotated((GLdouble)zSursa, 0.0, 0.0, 1.0);//rotatia sursei

    glTranslatef(xSursa, 0, 0);
    glTranslatef(0, ySursa, 0);
    glTranslatef(0, 0, zSursa);

    glLightfv(GL_LIGHT0, GL_POSITION, pozSursa);

    glDisable(GL_LIGHTING);
    glColor3f(1.0, 0.9, 0);
    auxSolidSphere(15);
    glEnable(GL_LIGHTING);

    glPopMatrix();
#pragma endregion


#pragma region Plan
    plan();
#pragma endregion

    /*glPopAttrib();*/
    glFlush();
}

void myinit(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };

    GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    glEnable(GL_DEPTH_TEST); // se activeaza ascunderea suprafetelor
    glDepthFunc(GL_LESS);//modelul de comparatie in testul de adancime

#pragma region Textura
    glEnable(GL_MAP2_TEXTURE_COORD_2);

    textureId1 = incarcaTextura("texturaClopot.bmp");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    GLfloat sGenParams[] = { 1.0, 1.0, 1.0, 0.0 };
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sGenParams);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureId1);
#pragma endregion

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE); // pentru iluminare


    glEnable(GL_COLOR_MATERIAL);//permite urmarirea culorilor
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//seteaza proprietatile de material pt a urma valorile glColor


    //SETEAZA SURSA 
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    //SETEAZA MATERIALUL
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-200.0, 200.0, -200.0 * (GLfloat)h / (GLfloat)w,
            200.0 * (GLfloat)h / (GLfloat)w, -600.0, 600.0);
    else
        glOrtho(-200.0 * (GLfloat)w / (GLfloat)h,
            200.0 * (GLfloat)w / (GLfloat)h, -200.0, 200.0, -600.0, 600.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(-10, -1.0f, 1.0f, 1.0f); //transformarea de vizualizare
}

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
    auxInitPosition(0, 0, 500, 500);
    auxInitWindow("Clopot");
    myinit();

    auxKeyFunc(AUX_UP, ScadeX);
    auxKeyFunc(AUX_DOWN, CresteX);

    auxKeyFunc(AUX_RIGHT, CresteY);
    auxKeyFunc(AUX_LEFT, ScadeY);

    auxKeyFunc(AUX_n, CresteZ);
    auxKeyFunc(AUX_m, ScadeZ);


    auxKeyFunc(AUX_w, ScadeBilaX);
    auxKeyFunc(AUX_s, CresteBilaX);

    auxKeyFunc(AUX_d, CresteBilaZ);
    auxKeyFunc(AUX_a, ScadeBilaZ);

    auxKeyFunc(AUX_i, CresteYSursa);
    auxKeyFunc(AUX_k, ScadeYSursa);

    auxKeyFunc(AUX_l, CresteXSursa);
    auxKeyFunc(AUX_j, ScadeXSursa);

    auxKeyFunc(AUX_o, CresteZSursa);
    auxKeyFunc(AUX_p, ScadeZSursa);
    
    auxKeyFunc(AUX_t, CresteYObiect);
    auxKeyFunc(AUX_g, ScadeYObiect);

    auxKeyFunc(AUX_h, CresteXObiect);
    auxKeyFunc(AUX_f, ScadeXObiect);

    auxKeyFunc(AUX_y, CresteZObiect);
    auxKeyFunc(AUX_u, ScadeZObiect);

    auxReshapeFunc(myReshape);
    //auxIdleFunc(IdleFunction);
    auxMainLoop(display);
    return(0);
}
