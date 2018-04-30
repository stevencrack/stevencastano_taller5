#include "iostream"
#include "fstream"
#include "math.h"
#include "cstdio"
using namespace std;

const int n = 20;
const float L = 100;
const float dx = L/float(n-1);
const float c = 2.0;
const float Tf=3*200.0;
const float dt=sqrt(0.9*dx*dx/(c*c));
const int nt = Tf/dt;

float x[n];
float cuerda_pasado[n];
float cuerda_presente[n];
float cuerda_futuro[n];
FILE *salida;


int crear_x()
{
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	
	int i;
	x[0] = 0.0;
	for (i = 1; i < n; ++i)
	{
		x[i] = x[i-1] + dx;
	}

	return 0;
}


int condicion_inicial()
{
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	int i;
	for (i = 0; i < n; ++i)
	{
		if (x[i]<0.8*L)
		{
			cuerda_pasado[i] = 1.25*x[i]/L;
		}
		if (x[i]>0.8*L)
		{
			cuerda_pasado[i] = 5.0-5.0*x[i]/L;
		}
	}

	
	for (i = 0; i < n; ++i)
	{
		cuerda_presente[i] = cuerda_pasado[i];
		cuerda_futuro[i] = 0.0;
	}	

	return 0;
}

int actualizar_sistema()
{
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	
	int i;
	
	
	for (i = 1; i < n-1; ++i)
	{
		cuerda_presente[i] = cuerda_futuro[i];
		cuerda_pasado[i] = cuerda_presente[i];
	}

	return 0;
}



int nuevo_paso()
{
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	
	int i;
	
	
	for (i = 1; i < n-1; ++i)
	{

		//cuerda_futuro[i] = -1.0*cuerda_pasado[i] + 2.0*cuerda_presente[i] + pow(dt*c/dx,2)*( cuerda_presente[i-1] - 2.0*cuerda_presente[i] + cuerda_presente[i+1] );
		cuerda_futuro[i] = -1.0*cuerda_pasado[i] + 2.0*cuerda_presente[i] + 0.6*( cuerda_presente[i-1] - 2.0*cuerda_presente[i] + cuerda_presente[i+1] );
	}

	return 0;
}

int imprimir(float t)
{
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	
	int i;
	
	// Imprimir tiempo futuro en archivo de salida
	for (i = 1; i < n-1; ++i)
	{
		fprintf(salida, "%f ", cuerda_presente[i]);
	}
	fprintf(salida, "\n");

	cout << "Imprimiendo t= " << t << endl;

	return 0;
}


int main(int argc, char const *argv[])
{
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	// *******************************************************
	int k;
	k = crear_x();
	if (k==0)
	{
		cout << "Vector X generado" << endl;
	}


	k = condicion_inicial();
	if (k==0)
	{
		cout << "Condicion inicial generada" << endl;
	}


	int m;
	salida = fopen("salida.txt", "w");

	for (k = 0; k < nt+2; ++k)
	{
		m = nuevo_paso();
		m = actualizar_sistema();
		m = imprimir(float(k*dt));
	}
	
	fclose(salida);
	
	return 0;
}
