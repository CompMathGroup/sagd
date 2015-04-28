#include "const.h"
#include <math.h>

double theta_l(const double psi)
{
	return ( psi / (1 + psi) );

}

double theta_s(const double psi)
{
	return ( 1 / (1 + psi) ); 
}

void K_permeability(double* psi, double* K_perm) //Проницаемость
{
	int m;
	for (m=0;m<M;m++)
	{
		K_perm[m] = pow( theta_l( psi[m] ), 2);   //Задаю проницаемость как квадрат насыщенности.
	}															//(На самом деле в тетта лежит отношение насыщеносттей, поэтому такая формула)
}


void viscosity(double * eta, const double* T)
{
	int m;
	for (m = 1; m < M; m++)
	{
		//eta[m] = 0.001 * exp( alpha * (Tcrit - T[m]) );
		eta[m] = 1e-3;
	}
}

void filtr_satur(const double *K_perm, const double *psi, double *psi_new, double *W_fil, const double tau, double* a_max, const double* eta)
{
	int m;
	double psi_temporary;
	*a_max = 0;
	for (m = 1; m < M; m++)
	{
		W_fil[m]=K_abs*K_perm[m] / eta[m] * (ro_s - ro_l) * gravity;
		psi_temporary = psi[m] - tau * (W_fil[m] - W_fil[m-1])/h;

		if (2 * psi_temporary / pow((1+psi_temporary), 3) / eta[m] > *a_max ) //Вычисляем максимальное a для условия Куранта
		{
			*a_max = 2 * psi_temporary / pow((1+psi_temporary) , 3) / eta[m];
		}

		if (psi_temporary >= psi_crit)
		{
			psi_new[m] = psi_temporary;
			continue;
		}
		if (psi_temporary < psi_crit)
		{
			psi_new[m] = psi_crit;
			W_fil[m] = W_fil[m-1] + (psi[m] - psi_new[m]) * h / tau;
		}

		if (2 * psi_new[m] / pow((1+psi_new[m]), 3) / eta[m]  > *a_max ) 	//Вычисляем максимальное a для условия Куранта
		{
			*a_max = 2 * psi_new[m] / pow((1+psi_new[m]) , 3) / eta[m];
		}
	}

}