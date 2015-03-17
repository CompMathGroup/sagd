#include "const.h"

void termal(double* T, double* Tnew, double* q)
{	
	int m;
	for (m=0; m<M-1; m++)
		{
			q[m]=-la*(T[m+1]-T[m])/h;
		}
	for (m=1; m<M-1; m++)
		{
			Tnew[m]=-tau*(q[m]-q[m-1])/h/ro_l/c+T[m];
			//printf("%d, %f\n",m,-tau*(q[m]-q[m-1])/h/ro/c+T[m]);
			//Tnew[m]=(T[m-1]+T[m])/2;
		}
}