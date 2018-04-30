#include "iostream"
#include "fstream"
#include "math.h"
#include "cstdio"
using namespace std;


float L;
float l;
float d;
float h;
float V0;
int N;

int main()
{
	// Constantes del problema
	L = 5.0; // cm
	l = 2.0; // cm
	d = 1.0; // cm
	h = 5.0/512; // cm
	V0 = 100; // V
	N = 2*pow(L/h,2); // numero de iteraciones

	// Construir matrices de X y Y
	int npuntos = 512+1;
	float X[npuntos][npuntos];
	float Y[npuntos][npuntos];

	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			X[i][j] = float(j*h);
			Y[i][j] = float(i*h);
			//printf("%f ", Y[i][j]);
		}
		//printf("\n");
	}

	// Exportar matrices X Y
	FILE *XY=fopen("XY.txt","w");
	// Escribir x y
	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			fprintf(XY, "%f,", X[i][j]);
		}		
		fprintf(XY, "\n");
	}
	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			fprintf(XY, "%f,", Y[i][j]);
		}		
		fprintf(XY, "\n");
	}
	fclose(XY);
	printf("\n---| Matrices X,Y generadas\n");


	
	// Construir matriz V
	float V[npuntos][npuntos];
	float V_apoyo[npuntos][npuntos];
	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			V[i][j] = 0.0;
			V_apoyo[i][j] = 0.0;

			if (L/2-l/2 < X[i][j] & X[i][j] < L/2+l/2)
			{ // Posiciones x de la placa cargada
				if ( L/2-d/2-h/2 < Y[i][j]  &  Y[i][j] < L/2-d/2+h/2 )
				{ // Posiciones y en la plca de arriba
					V[i][j] = V0; // Asignar potencial
					V_apoyo[i][j] = V0/2.0;	
				}else if ( L/2+d/2-h/2 < Y[i][j]  &  Y[i][j] < L/2+d/2+h/2 )
				{  // Posiciones y en la plca de abajo
					V[i][j] = -V0; // Asignar potencial
					V_apoyo[i][j] = -V0/2.0;	
				}
			}
		}
	}
	printf("---| Matriz V generada\n");


	// Zonas donde aplicar relajacion
	//
	//
	//     ----------------------
	//     |  x             *   |
	//     |  x      3      *   |
	//     |  x   --------  *   |
	//     |  1             2   |
	//     |  x      4      *   |
	//     |  x   --------  *   |
	//     |  x             *   |
	//     |  x       5     *   |
	//     |  x             *   |
	//     ----------------------
	//
	// En estas zonas aplico la relajacion
	// Zona 1 -> x
	// Zona 2 -> *
	// Zona 3
	// Zona 4
	// Zona 5

	printf("---| Iniciando iteraciones de relajacion\n");
	// Relajar el potencial en las iteraciones
	int k=1;
	while (k<N/100) // Hago N/100 para no demorarme tanto probandolo
	{
		// reasignar valores para la nueva iteraXY
		for (int i = 0; i < npuntos; ++i)
		{
			for (int j = 0; j < npuntos; ++j)
			{
				V[i][j] = V_apoyo[i][j];
			}
		}		


		// Relajar el sistema
		for (int i = 0; i < npuntos; ++i)
		{
			for (int j = 0; j < npuntos; ++j)
			{
				if (X[i][j]!=0.0 & X[i][j]!=L & Y[i][j]!=0.0 & Y[i][j]!=L)
				{// Fuera de la frontera
					
					if ( X[i][j] < L/2-l/2 )
					{ // zona 1
						V_apoyo[i][j] = 0.25 * (V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]);
					}
					else if ( X[i][j] < L/2+l/2 )
					{ // zonas centrales
						if ( Y[i][j]<L/2-d/2-h/2  | ( L/2-d/2+h/2<Y[i][j] & Y[i][j] < L/2+d/2-h/2) | L/2+d/2+h/2 < Y[i][j])
						{ // Esta en zonas 3, 4, o 5
							V_apoyo[i][j] = 0.25 * (V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]);
						}
					}
					else
					{ // Zona 2
						V_apoyo[i][j] = 0.25 * (V[i+1][j]+V[i-1][j]+V[i][j+1]+V[i][j-1]);
					}
					
				}else
				{ // Frontera
					V_apoyo[i][j] = 0.0;
				}
			}
		}
		printf("%d..", k);
		k = k+1;

	}
	printf("\n---| Finalizado iteraciones de relajacion\n");

	// Calcular campo electrico "E" en "x" y en "y"
	float E[npuntos][npuntos][2];

	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			if (i!=0 & j != 0)
			{
				E[i][j][0] = -1.0*(V_apoyo[i][j]-V_apoyo[i][j-1])/(h/100.0);
				E[i][j][1] = -1.0*(V_apoyo[i][j]-V_apoyo[i-1][j])/(h/100.0);
				// Dividir h en 100 para que las unidades de h queden en m
				// y las del campo electrico en Potencial/m
			}
		}
	}
	

	// Exportar datos
	printf("\n---| Imprimiendo datos en 'salida.txt'\n");
	FILE *salida=fopen("salida.txt","w");
	// Escribir potencial
	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			fprintf(salida, "%f,", V_apoyo[i][j]);
		}		
		fprintf(salida, "\n");
	}
	
	// Escribir campo electrico x en el mismo archivo
	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			fprintf(salida, "%f,", E[i][j][0]);
		}		
		fprintf(salida, "\n");
	}

		// Escribir campo electrico y en el mismo archivo
	for (int i = 0; i < npuntos; ++i)
	{
		for (int j = 0; j < npuntos; ++j)
		{
			fprintf(salida, "%f,", E[i][j][1]);
		}		
		fprintf(salida, "\n");
	}
	fclose(salida);

	printf("\n---| Programa Finalizado\n");

	/* code */
	return 0;
}
