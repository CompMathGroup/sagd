#include "const.h"
void K_permeability(double* theta, double* K_perm) //Проницаемость
{
	int m;
	for (m=1;m<M;m++)
	{
		K_perm[m]=(theta[m]*theta[m])/(1+theta[m])/(1+theta[m]);   //Задаю проницаемость как квадрат насыщенности.
	}															//(На самом деле в тетта лежит отношение насыщеносттей, поэтому такая формула)
}


void W_filtration(double* theta, double* K_perm, double* W_fil ) //Вектор Фильтрации. (На границах задаем что он ноль)
{
	int m;
	for (m=0;m<M;m++)
	{
		W_fil[m]=K_abs*K_perm[m]/eta*(ro_s-ro_l)*gravity;		//m+1/2
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

void filtr_satur(const double *K_perm, const double *theta, double *theta_new, double *W_fil)
{
	int m;
	double theta_temporary;
	for (m = 1; m < M; m++)
	{
		W_fil[m]=K_abs*K_perm[m]/eta*(ro_s-ro_l)*gravity;
		theta_temporary = theta[m] - tau * (W_fil[m] - W_fil[m-1])/h;

		if (theta_temporary >= theta_crit)
		{
			theta_new[m] = theta_temporary;
			continue;
		}
		if (theta_temporary < theta_crit)
		{
			theta_new[m] = theta_crit;
			W_fil[m] = W_fil[m-1] + (theta[m] - theta_new[m]) * h / tau;
		}
	}

}