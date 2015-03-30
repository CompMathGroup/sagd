#include "const.h"
void K_permeability(double* tetha, double* K_perm) //Проницаемость
{
	int m;
	for (m=1;m<M;m++)
	{
		K_perm[m]=(tetha[m]*tetha[m])/(1+tetha[m])/(1+tetha[m]);   //Задаю проницаемость как квадрат насыщенности.
	}															//(На самом деле в тетта лежит отношение насыщеносттей, поэтому такая формула)
}


void W_filtration(double* tetha, double* K_perm, double* W_fil ) //Вектор Фильтрации. (На границах задаем что он ноль)
{
	int m;
	for (m=1;m<M;m++)
	{
		W_fil[m]=K_abs*K_perm[m]/eta*(ro_s-ro_l)*gravity;		//m+1/2
	}
}


void saturation(double* tetha, double* W_fil, double* tetha_new) // отношение относительных насыщенностей жидкости и скелета
{
	int m;
	for (m=1;m<M;m++)
	{
		tetha_new[m]=tetha[m]-tau*(W_fil[m]-W_fil[m-1])/h;	
	}
}
