#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "TextureLoader.h"
#include "Camara.h"
#include "Ilumination.h"
#include "Line.h"
#include "Escena.h"
#include "SpotLight.h"
#include "Lamp.h"
#include "Texture.h"

#include <iostream>

using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
GLdouble xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;
GLdouble xRightIni = 10, xLeftIni = -xRightIni, yTopIni = 10, yBotIni = -yTop, NIni = 1, FIni = 1000;

// Camera parameters
GLdouble eyeX= 25.0, eyeY=25.0, eyeZ= 25.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;

/*Variables globales para control por teclado.*/
GLfloat girox = 0.0;
GLfloat giroy = 0.0;
GLfloat giroz = 0.0;
GLfloat gradoGiro = 2.0f;

GLfloat openDoor = false;

GLfloat cocheMueve = 0.0;
GLfloat avanceCoche = 0.05f;

GLdouble incDesp = 0.25;

GLdouble factorMas = 1.2;
GLdouble factorMenos = 0.8;

GLboolean muestraNormal = false;
GLboolean baldosas = false;
GLboolean dibujaMon = true, dibujaCoche = false;
GLboolean inCar = false;

Camara* camara;
Escena* escena;
Ilumination *ilumination;
Texture* texture;

/*Llamamos a la constructoras de los objetos.*/
void buildSceneObjects() {
	SpotLight** spots = new SpotLight*[3];
	spots[0] = ilumination->addSpot();
	spots[1] = ilumination->addSpot();
	Lamp **lamps = new Lamp*[1];
	lamps[0] = ilumination->addLamp();

	texture = new Texture();
	escena = new Escena(spots, lamps, texture->getTexture(0));
}

//Dibuja los ejes de coordenadas.
void drawAxes() {
// Drawing axes
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 0, 0);
		glVertex3f(20, 0, 0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 20);
	glEnd();
}

void drawNet() {
	PV3D* begin,* end;
	Line *line;
	begin = new PV3D(-1000, 0.0, -1000, 1.0);
	end = new PV3D(-1000, 0.0, 1000, 1.0);
	line = new Line(begin, end, new Color("black"));
	
	for (int i = -1000; i < 1000; i+=10) {
		line = new Line(begin, end, new Color("black"));
		line->dibuja();
		begin->setX((GLfloat)i);
		end->setX((GLfloat)i);
	}

	begin = new PV3D(-1000, 0.0, -1000, 1.0);
	end = new PV3D(+1000, 0.0, -1000, 1.0);
	for (int i = -1000; i < 1000; i += 20) {
		line = new Line(begin, end, new Color("black"));
		line->dibuja();
		begin->setZ(i);
		end->setZ(i);
	}
}

//Método que dibuja los elementos de la escena.
void drawScene() {
	//Dibuja los ejes de la escena.
	drawAxes();
	drawNet();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(girox, 1.0, 0.0, 0.0);
	glRotatef(giroy, 0.0, 1.0, 0.0);
	glRotatef(giroz, 0.0, 0.0, 1.0);

	escena->dibuja();
	glPopMatrix();

}

//Metodo que gira los elementos de la vista de 4 perspectivas.
void gira(GLint i) {
	if (i == 0) {
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glRotatef(0 , 1.0, 0.0, 0.0);
			glRotatef(-45, 0.0, 1.0, 0.0);
			glRotatef(35, 0.0, 0.0, 1.0);
	}
	else if (i == 1) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glRotatef(-45, 1.0, 0.0, 0.0);
			glRotatef(35, 0.0, 1.0, 0.0);
			glRotatef(30, 0.0, 0.0, 1.0);

	}
	else if (i == 3) {
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glRotatef(180, 1.0, 0.0, 0.0);
			glRotatef(45, 0.0, 1.0, 0.0);
			glRotatef(235, 0.0, 0.0, 1.0);
	}
	else {
		glPushMatrix();
	}
	drawScene(); //Dibuja la escena
	glPopMatrix();
}

//Embaldosa la escena mostrando las vistas frontal, lateral, cenital y esquina.
void embaldosarCuatroVistas() {
	GLint nCol = 2;
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	GLint cont = 0;
	for (GLint c = 0; c < nCol; c++) {
		GLdouble currentH = 0;
		while ((currentH) <= HEIGHT) {
			glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
			gira(cont);
			currentH += h;
			cont++;
		}
	}
}

//Metodo que gira los elementos de la vista de 4 perspectivas.
void estereoscopica(GLint i) {
	if (i == 0) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
	}
	else if (i == 1) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.25);
	}
	drawScene(); //Dibuja la escena
	glPopMatrix();
}

//Embaldosa la escena mostrando las vistas frontal, lateral, cenital y esquina.
void embaldosarDosVistas() {
	GLint nCol = 2;
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	GLint cont = 0;
	for (GLint c = 0; c < nCol; c++) {
		glViewport((GLint)(c*w), (GLint)yTop - yBot, (GLint)w, (GLint)HEIGHT);
		estereoscopica(cont);
		cont++;
	}
}


//Desembaldosa la escena.
void desembaldosar() {
	glViewport(0, 0, WIDTH, HEIGHT);
	drawScene();
}


void initializeLight(){
	ilumination = new Ilumination();
	ilumination->enableAllLights();
}

void initGL() {	 	 

	//Light set up
	initializeLight();

	buildSceneObjects();	

	// Camera set up
	PV3D* eye = new PV3D(eyeX, eyeY, eyeZ, 1);
	PV3D* look = new PV3D(lookX, lookY, lookZ, 0);
	PV3D* up = new PV3D(upX, upY, upZ, 0);

	camara = new Camara(eye, look, up, xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);  

	glDisable(GL_CULL_FACE);
	ilumination->reponeAllLights();
 }

/*Método display.*/
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	
	/*Espacio de trabajo.*/
	
	if (baldosas) embaldosarCuatroVistas();
	else desembaldosar();

	/*Fin de espacio de trabajo.*/

	glFlush();
	glutSwapBuffers();
}

/*Zoom progresivo.*/
void zoomProgresivo(GLint nIter, GLfloat f) {
	/*Calculamos los puntos medios de cada eje.*/
	GLdouble yMiddle = (yBot + yTop) / 2.0;
	GLdouble xMiddle = (xLeft + xRight) / 2.0;
	/*Calculamos el incremento de cada iteración.*/
	GLdouble fIncr = (f - 1) / (GLdouble)nIter;
	/*Calculamos altura y anchura del puerto de vista.*/
	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	/*Calculamos el zoom gradualmente.*/
	for (int i = 0; i <= nIter; i++) {
		GLdouble fAux = 1 + fIncr*i;
		GLdouble newWidth = SVAWidth / fAux;
		GLdouble newHeight = SVAHeight / fAux;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(!camara->isPerspectiva())
			glOrtho(xMiddle - newWidth / 2.0, xMiddle + newWidth / 2.0, yMiddle - newHeight / 2.0, yMiddle + newHeight / 2.0, N, F);
		else
			glFrustum(xMiddle - newWidth / 2.0, xMiddle + newWidth / 2.0, yMiddle - newHeight / 2.0, yMiddle + newHeight / 2.0, N, F);
		display(); //glutPostRedisplay(); no funciona!
		/*Solo dormimos al final, para que no pare al mantener el botón pulsado.*/
		if(nIter != i) Sleep(50);
	}
}

/*Zoom normal.*/
void zoom(GLfloat f) {
	/*Calculamos los puntos medios de cada eje.*/
	GLdouble yMiddle = (yBot + yTop) / 2.0;
	GLdouble xMiddle = (xLeft + xRight) / 2.0;
	/*Calculamos altura y anchura del puerto de vista.*/
	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	/*Calculamos el zoom gradualmente.*/
	GLdouble newWidth = SVAWidth / f;
	GLdouble newHeight = SVAHeight / f;
	yTop = yMiddle + newHeight / 2.0;
	yBot = yMiddle - newHeight / 2.0;
	xRight = xMiddle + newWidth / 2.0;
	xLeft = xMiddle - newWidth / 2.0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!camara->isPerspectiva())
		glOrtho(xMiddle - newWidth / 2.0, xMiddle + newWidth / 2.0, yMiddle - newHeight / 2.0, yMiddle + newHeight / 2.0, N, F);
	else
		glFrustum(xMiddle - newWidth / 2.0, xMiddle + newWidth / 2.0, yMiddle - newHeight / 2.0, yMiddle + newHeight / 2.0, N, F);
	display(); //glutPostRedisplay(); no funciona!
}

void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	if (!camara->isPerspectiva())
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else
		glFrustum(xLeft, xRight, yBot, yTop, N, F);
}


void resetFrustumValues() {
	yTop = yTopIni;
	yBot = yBotIni;
	xLeft = xLeftIni;
	xRight = xRightIni;
}

/*Método key para teclas normales.*/ 
void key(unsigned char key, int x, int y) {
	bool need_redisplay = true;
	switch (key) {
	case 27:  /* Escape key */
			  //continue_in_main_loop = false; // (**)
			  //Freeglut's sentence for stopping glut's main loop (*)
		glutLeaveMainLoop();
		break;

	case 'a':
		girox += gradoGiro;
		break;
	case 'z':
		girox -= gradoGiro;
		break;
	case 's':
		giroy += gradoGiro;
		break;
	case 'x':
		giroy -= gradoGiro;
		break;
	case 'd':
		giroz += gradoGiro;
		break;
	case 'c':
		giroz -= gradoGiro;
		break;
	case 'l':
		resetFrustumValues();
		camara->updateFrustumValues(xLeft, xRight, yBot, yTop, N, F);
		camara->cambioProyeccion();
		if (camara->isPerspectiva()){
			zoom(factorMas*24);
		}
		ilumination->reponeAllLights();
		break;
	case 'u':
		if (!baldosas) {
			camara->roll("neg");
			ilumination->reponeAllLights();
		}
		break;
	case 'i':
		if (!baldosas) {
			camara->roll("pos");
			ilumination->reponeAllLights();
		}
		break;
	case 'j':
		if (!baldosas) {
			camara->yaw("neg");
			ilumination->reponeAllLights();
		}
		break;
	case 'k':
		if (!baldosas) {
			camara->yaw("pos");
			ilumination->reponeAllLights();
		}
		break;
	case 'n':
		if (!baldosas) {
			camara->pitch("neg");
			ilumination->reponeAllLights();
		}
		break;
	case 'm':
		if (!baldosas) {
			camara->pitch("pos");
			ilumination->reponeAllLights();
		}
		break;
	case 'o':
		baldosas = false;
		break;
	case 'p':
		baldosas = true;
		camara->vistaEsquina();
		ilumination->reponeAllLights();
		break;
	case 't':
		zoomProgresivo(3, factorMenos);
		camara->updateFrustumValues(xLeft, xRight, yBot, yTop, N, F);
		break;
	case 'y':
		zoomProgresivo(3, factorMas);
		camara->updateFrustumValues(xLeft, xRight, yBot, yTop, N, F);
		break;
	case 'e':
		if (!baldosas) {
			camara->translateX("neg");
			ilumination->reponeAllLights();
		}
		break;
	case 'r':
		if (!baldosas) {
			camara->translateX("pos");
			ilumination->reponeAllLights();
		}
		break;
	case 'f':
		if (!baldosas) {
			camara->translateY("neg");
			ilumination->reponeAllLights();
		}
		break;
	case 'g':
		if (!baldosas) {
			camara->translateY("pos");
			ilumination->reponeAllLights();
		}
		break;
	case 'v':
		if (!baldosas) {
			camara->translateZ("neg");
			ilumination->reponeAllLights();
		}
		break;
	case 'b':
		if (!baldosas) {
			camara->translateZ("pos");
			ilumination->reponeAllLights();
		}
		break;
	case 'Q':
		ilumination->disableAmbientLight();
		break;
	case 'W':
		ilumination->enableAmbientLight();
		break;
	case 'A':
		escena->apagaCoche();
		break;
	case 'S':
		escena->enciendeCoche();
		break;
	case 'Z':
		escena->apagaFarola();
		break;
	case 'X':
		escena->enciendeFarola();
		break;
	case 'E':
		ilumination->apagaRemota();
		break;
	case 'R':
		ilumination->enciendeRemota();
		break;
	case 'O':
		for(int i = 0; i < 2; i++) {
			escena->abrePuertaCoche(openDoor);
			Sleep(50);
			display();
		}
		escena->abrePuertaCoche(openDoor);
		openDoor = !openDoor;
		break;
	case 'Y':
		escena->noGiro();
		if (camara->isPerspectiva()) {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getLook()->getX() - 20, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
			camara->setUpCamera();
		}
		else {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getEye()->getX() + 10, escena->getEye()->getY() + 10, escena->getEye()->getZ() + 10, 1.0));
			camara->setUpCamera();
		}
		ilumination->reponeAllLights();
		break;


	case'H':
		escena->noGiro();
		if (camara->isPerspectiva()) {
			escena->mueveCoche(true);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getLook()->getX() + 15, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
			camara->setUpCamera();
		}
		else {
			escena->mueveCoche(true);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getLook()->getX() + 10, escena->getLook()->getY() + 10, escena->getLook()->getZ() + 10, 1.0));
			camara->setUpCamera();
		}
		ilumination->reponeAllLights();

		break;
	case 'G':
		escena->giraCoche(-12);		
		if (camara->isPerspectiva()) {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getLook()->getX() - 20, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
			camara->setUpCamera();
		}
		else {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getEye()->getX() + 10, escena->getEye()->getY() + 10, escena->getEye()->getZ() + 10, 1.0));
			camara->setUpCamera();
		}
		ilumination->reponeAllLights();
		break;
		break;
	case 'J':
		escena->giraCoche(12);
		if (camara->isPerspectiva()) {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getLook()->getX() - 20, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
			camara->setUpCamera();
		}
		else {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getEye()->getX() + 10, escena->getEye()->getY() + 10, escena->getEye()->getZ() + 10, 1.0));
			camara->setUpCamera();
		}
		ilumination->reponeAllLights();
		break;
		break;
	case 'I':		
		escena->noGiro();
		if (camara->isPerspectiva()) {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getLook()->getX() - 20, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
			camara->setUpCamera();
		}
		else {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getEye()->getX() + 10, escena->getEye()->getY() + 10, escena->getEye()->getZ() + 10, 1.0));
			camara->setUpCamera();
		}
		escena->vuela(true);
		camara->setLook(escena->getLook());
		camara->setEye(new PV3D(escena->getLook()->getX() - 20, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
		camara->setUpCamera();
		ilumination->reponeAllLights();
		break;
	case 'U':
		escena->noGiro();
		if (camara->isPerspectiva()) {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getLook()->getX() - 20, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
			camara->setUpCamera();
		}
		else {
			escena->mueveCoche(false);
			camara->setLook(escena->getLook());
			camara->setEye(new PV3D(escena->getEye()->getX() + 10, escena->getEye()->getY() + 10, escena->getEye()->getZ() + 10, 1.0));
			camara->setUpCamera();
		}
		escena->vuela(false);
		camara->setLook(escena->getLook());
		camara->setEye(new PV3D(escena->getLook()->getX() - 20, escena->getLook()->getY() + 2, escena->getLook()->getZ(), 1.0));
		camara->setUpCamera();
		ilumination->reponeAllLights();
		break;
	case '1':
		if (!baldosas) {
			camara->giraX("pos");
			ilumination->reponeAllLights();
		}
		break;
	case '2':
		if (!baldosas) {
			camara->giraY("pos");
			ilumination->reponeAllLights();
		}
		break;
	case '3':
		if (!baldosas) {
			camara->giraZ("pos");
			ilumination->reponeAllLights();
		}
		break;

	case '4':
		if (!baldosas) {
			camara->vistaLateral();
			ilumination->reponeAllLights();
		}
		break;
	case '5':
		if (!baldosas) {
			camara->vistaFrontal();
			ilumination->reponeAllLights();
		}
		break;
	case '6':
		if (!baldosas) {
			camara->vistaCenital();
			ilumination->reponeAllLights();
		}
		break;
	case '7':
		if (!baldosas) {
			camara->vistaEsquina();
			ilumination->reponeAllLights();
		}
		break;
	default:
		need_redisplay = false;
		break;
	}
	if (need_redisplay)
		glutPostRedisplay();
}

/*Metodo key para teclas especiales.*/
void key(int key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;
		case GLUT_KEY_UP:
			yTop -= incDesp;
			yBot -= incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		case GLUT_KEY_DOWN:
			yTop += incDesp;
			yBot += incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		case GLUT_KEY_LEFT:
			xLeft += incDesp;
			xRight += incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		case GLUT_KEY_RIGHT:
			xLeft -= incDesp;
			xRight -= incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutSpecialFunc(key);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 

	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}
