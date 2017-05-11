#ifndef ILUMINATION_H
#define ILUMINATION_H

#include "Lamp.h"
#include "SpotLight.h"
#include "Lamp.h"

/*
Clase iluminación. Define los parámetros de la iluminación de la escena y sus luces.
*/
class Ilumination {
private:
	/*Tamaño del array de luces.*/
	const GLint TAM_LIGHT = 8;
	/*Array de lámparas (luces normales).*/
	Lamp **lamps;
	/*Array de focos.*/
	SpotLight ** spots;
	/*Marcador, indica si una luz es foco o lámpara.*/
	bool markLamps[8];
	/*Número de luces establecido.*/
	GLint numLight;

public:

	/****************
	 *Constructoras.*
	 ****************/
	
	/*Constructora de la clase iluminación.*/
	Ilumination() {
		glClearColor(0.6f, 0.7f, 0.8f, 1.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

		lamps = new Lamp*[TAM_LIGHT];
		spots = new SpotLight*[TAM_LIGHT];
		numLight = 0;

		for (int i = 0; i < TAM_LIGHT; i++)
			markLamps[i] = false;

		//Añadimos la luz remota posicional.
		GLfloat d[] = { 1.0,1.0,1.0,1.0 };
		GLfloat a[] = { 0.0f,0.0f,0.0f,1.0 };
		GLfloat e[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat p[] = { 25.0, 25.0, 25.0, 0.0 };
		this->addLamp(d, a, e, p);
	}

	/*Destructora de la clase iluminación.*/
	~Ilumination() {
		for (int i = 0; i < numLight; i++)
			if (markLamps[i])
				delete lamps[i];
		delete lamps;
		for (int i = 0; i < numLight; i++)
			if (spots[i] != NULL)
				delete spots[i];
		delete spots;
	}

	/**********
	 *Getters.*
	 **********/

	/*Devuelve la lámpara en la posición i.*/
	Lamp *getLamp(GLint i) {
		if (i < numLight && i >= 0)
			if (markLamps[i])
				return lamps[i];
			else return NULL;
		else return NULL;
	}

	/*Devuelve el foco en la posición i.*/
	SpotLight *getSpot(GLint i) {
		if (i < numLight && i >= 0)
			if (spots[i] != NULL)
				return spots[i];
	}

	/**********
	 *Setters.*
	 **********/

	/*Añade una lámpara con valores por defecto.*/
	Lamp * addLamp() {
		if (numLight < TAM_LIGHT) {
			GLfloat d[] = { 1.0,1.0,1.0,1.0 };
			GLfloat a[] = { 0.0f,0.0f,0.0f,1.0 };
			GLfloat e[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat p[] = { 0.0, 0.0, 0.0, 1.0 };
			GLint num = 0x4000 + numLight;
			lamps[numLight] = new Lamp(num, d, a, e, p);
			numLight++;
			markLamps[numLight - 1] = true;
			return lamps[numLight - 1];
		}
		return NULL;
	}

	/*Añade una lámpara estableciendo sus valores.*/
	Lamp * addLamp(GLfloat d[], GLfloat a[], GLfloat e[], GLfloat p[]) {
		if (numLight < TAM_LIGHT) {
			GLint num = 0x4000 + numLight;
			lamps[numLight] = new Lamp(num, d, a, e, p);
			numLight++;
			markLamps[numLight - 1] = true;
			return lamps[numLight - 1];
		}
		return NULL;
	}

	/*Áñade un foco con valores por defecto.*/
	SpotLight * addSpot() {
		if (numLight < TAM_LIGHT) {
			GLfloat dir[] = {1.0f, -0.2f, 0.0f};
			GLfloat epsilon = 4;
			GLfloat alpha = 90;
			GLfloat d[] = {1.0f ,1.0f ,1.0f ,1.0f};
			GLfloat a[] = {0.3f,0.3f,0.3f, 1.0f};
			GLfloat e[] = {1.0f, 1.0f, 1.0f, 1.0f};
			GLfloat p[] = {25.0f, 25.0f, 0.0f, 1.0f};
			GLint num = 0x4000 + numLight;
			spots[numLight] = new SpotLight(num, epsilon, alpha, dir, d, a, e, p);
			numLight++;
			return spots[numLight - 1];
		}
		return NULL;
	}

	/*Añade un foco estableciendo sus valores.*/
	SpotLight * addSpot(GLint num, GLfloat epsilon, GLfloat alpha, GLfloat dir[], GLfloat d[], GLfloat a[], GLfloat e[], GLfloat p[]) {
		if (numLight < TAM_LIGHT) {
			GLint num = 0x4000 + numLight;
			spots[numLight] = new SpotLight(num, epsilon, alpha, dir, d, a, e, p);
			numLight++;
			return spots[numLight - 1];
		}
		return NULL;
	}

	/**********************
	 *Métodos de la clase.*
	 **********************/

	/*Enciende la luz en la posición i.*/
	void enableLight(GLint i) {
		if (i >= 0 && i < numLight)
			if(markLamps[i])
				lamps[i]->enable();
			else
				spots[i]->enable();
	}

	/*Apaga la luz en la posición i.*/
	void disableLight(GLint i) {
		if (i >= 0 && i < numLight)
			if (markLamps[i])
				lamps[i]->disable();
			else
				spots[i]->disable();
	}

	/*Enciende todas las luces.*/
	void enableAllLights() {
		for (int i = 0; i < numLight; i++)
			if(markLamps[i])
				lamps[i]->enable();
			else
				spots[i]->enable();
	}

	/*Apaga todas las luces.*/
	void disableAllLights() {
		for (int i = 0; i < numLight; i++)
			if (markLamps[i])
				lamps[i]->disable();
			else
				spots[i]->disable();
	}

	/*Enciende la luz de ambiente global.*/
	void enableAmbientLight() {
		GLfloat amb[] = {0.2f, 0.2f, 0.2f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	}

	/*Apaga la luz de ambiente global.*/
	void disableAmbientLight() {
		GLfloat amb[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
	}

	/*Repone todas las luces.*/
	void reponeAllLights() {
		for (int i = 0; i < numLight; i++)
			if (markLamps[i] == true)
				lamps[i]->reponeLight();
			else
				spots[i]->reponeLight();
	}

	/*Enciende la luz remota.*/
	void enciendeRemota() {
		this->getLamp(0)->enable();
	}

	/*Apaga la luz remota.*/
	void apagaRemota() {
		this->getLamp(0)->disable();
	}
};

#endif