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

void K_permeability(double* theta, double* K_perm) //Проницаемость
{
	int m;
	for (m=0;m<M;m++)
	{
		//K_perm[m]=pow(theta_l(theta[m]), 3) / pow(theta_s(theta[m]), 2);   
		K_perm[m] = 4 * pow( theta[m], 3) / pow(1 + theta[m], 2) / (2 + theta[m]) ; 
	}															
}


void W_filtration(double* theta, double* K_perm, double* W_fil ) //Вектор Фильтрации. (На границах задаем что он ноль)
{
	int m;
	for (m=0;m<M;m++)
	{
		W_fil[m] = K_abs * K_perm[m] / eta * (ro_s - ro_l) * gravity;		//m+1/2
	}
}


void saturation(double* theta, double* W_fil, double* theta_new) // отношение относительных насыщенностей жидкости и скелета
{
	int m;
	for (m=1;m<M;m++)
	{
		theta_new[m]=theta[m]-tau*(W_fil[m]-W_fil[m-1])/h;	
	}
}
