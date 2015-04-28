#include "const.h"
double theta_s(const double psi);
double theta_l(const double psi);


void T_cond(double* q, const double* psi, const double* T)
{
	int m;
	for (m=0; m<M-1; m++)
	{
		q[m] = -1. / (1 + psi[m]) * la * (T[m+1] - T[m]) / h;  // q_m+1/2
	}
}

void termal(const double* T, double* Tnew, const double* q, const double* psi, const double* W_fil, const double* psi_new, const double tau)
{	
	int m;
	double A2, A1, B, C;
	for (m=1; m<M; m++)
	{
		A2 = (theta_l(psi_new[m]) * ro_l * c_l + theta_s(psi_new[m]) * ro_s * c_s ) / theta_s(psi_new[m]);
		A1 = ( ro_l * theta_l(psi[m]) * c_l + ro_s * theta_s(psi[m]) * c_s ) / theta_s(psi[m]);
		B = ro_l * c_l;
		Tnew[m] =( A1 * T[m] - (q[m] - q[m-1]) * tau / h - B * ( T[m] * W_fil[m] - T[m-1] * W_fil[m-1] ) * tau / h ) / A2 ;
		//printf("%d, %f\n",m,-tau*(q[m]-q[m-1])/h/ro/c+T[m]);
		//Tnew[m]=(T[m-1]+T[m])/2;
	}
}