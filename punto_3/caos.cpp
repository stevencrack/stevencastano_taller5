#include "iostream"
#include "fstream"
#include "math.h"
using namespace std;
float u=0.001;
float pendiente[4];

float calcular(float q1, float q2, float p1, float p2)
{

float b1=-2.0*q1;

	// calcular derivadas en orden q1, q2, p1, p2

	// pendiente q1
	pendiente[0] = p1;

	// pendiente q2
	pendiente[1] = p2;

	// pendiente p1
	pendiente[2] =  b1/pow( 4.0*pow(q1,2) + pow(u,2) ,1.5);

	// pendiente p2
	

	float euler = pow(u,2)/4.0;

	pendiente[3] = q1-q2/pow( pow(q1-q2,2)+euler, 1.5 ) - (q1+q2)/pow( pow(q1+q2,2)+euler, 1.5 );
}


int main()
{
	int k;
	int i;
	int j;

	// variables del problema
	float tiempo = 0.006;
	int nt = 1 + 3000/tiempo;
	float a=1.0/(2.0*sqrt(2.0));

	// Imprimir valores de variables iniciales
	cout << tiempo << endl << nt << endl << u << endl << a << endl;

	// vectores q y p para el dominio del tiempo
	float q1[nt];
	float q2[nt];
	float p1[nt];
	float p2[nt];

	// condiciones iniciales
	q1[0] = a;
	p1[0] = 0.0;
	q2[0] = -a;
	p2[0] = 0.0;

	// vectores v1, v2, v3 y v4 para ks de todas las variables
	float v1[4];
	float v2[4];
	float v3[4];
	float v4[4];

	// Inicializar vectores en 0s
	for (i= 0; i < 4; ++i)
	{ 
		pendiente[i] = 0.0;
		v1[i] = 0.0;
		v2[i] = 0.0;
		v3[i] = 0.0;
		v4[i] = 0.0;
	}


	
	fstream caos_data("caos_data.txt");

	for (i = 0; i < nt-1; ++i)
	{
		//------------------------------------------ v1
		// calcular derivadas
		calcular(q1[i], q2[i], p1[i], p2[i]);
		// Guardar v1
		for (j = 0; j < 4; ++j)
		{	v1[j] = pendiente[j];	}


		//------------------------------------------ v2
		// calcular derivadas
		calcular(q1[i]+0.5*tiempo*v1[0], q2[i]+0.5*tiempo*v1[1], p1[i]+0.5*tiempo*v1[2], p2[i]+0.5*tiempo*v1[3]);		
		// Guardar v2
		for (j = 0; j < 4; ++j)
		{	v2[j] = pendiente[j];	}


		//------------------------------------------ v3
		// calcular derivadas
		calcular(q1[i]+0.5*tiempo*v2[0], q2[i]+0.5*tiempo*v2[1], p1[i]+0.5*tiempo*v2[2], p2[i]+0.5*tiempo*v2[3]);		
		// Guardar v3
		for (j = 0; j < 4; ++j)
		{	v3[j] = pendiente[j];	}


		//------------------------------------------ v4
		// calcular derivadas
		calcular(q1[i]+tiempo*v3[0], q2[i]+tiempo*v3[1], p1[i]+tiempo*v3[2], p2[i]+tiempo*v3[3]);		
		// Guardar v3
		for (j = 0; j < 4; ++j)
		{	v3[j] = pendiente[j];	}

		
		//------------------------------------------\\
		// Avanzar en el tiempo
		q1[i+1]	= q1[i] + tiempo/6.0*( v1[0] + 2.0*v2[0] + 2.0*v3[0] + v4[0] );
		q2[i+1]	= q2[i] + tiempo/6.0*( v1[1] + 2.0*v2[1] + 2.0*v3[1] + v4[1] );
		p1[i+1]	= p1[i] + tiempo/6.0*( v1[2] + 2.0*v2[2] + 2.0*v3[2] + v4[2] );
		p2[i+1]	= p2[i] + tiempo/6.0*( v1[3] + 2.0*v2[3] + 2.0*v3[3] + v4[3] );

		// cada que q1 pase de ser positivo a negativo el codigo va a 
		// imprimir los valores de q2 y p2
		if (q1[i]>0.0 & q1[i+1]<0.0)
		{
			caos_data << q2[i] << " " << p2[i] << endl;
		}
		cout << q1[i] << " " << q2[i] << " " << p1[i] << " " << p2[i] << endl;
	}

	return 0;
}
