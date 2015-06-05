#include "const.h" 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

static double K(double psi) {
	return (4*pow(psi,3))/(pow(1 + psi,2)*(2 + psi));
}

double dKdpsi(double psi) {  //Скорость распростронения волны (зависит от  psi)
	return (16 * pow(psi, 3) + 24 * psi * psi) / pow(1 + psi, 3) / pow(2 + psi, 2);
}

void analit(const double t, double* theta, const double* theta_new)
{
	int m;
	double a = (ro_s-ro_l)/eta*gravity*K_abs;

	const double psicr = (1 + sqrt(17)) / 2;
	const double psil = 4;

	double psi = psil;

	for(m=1;m<M;m++)
	{
		double xi = m*h / (a * t);		//Справа от волны
		if (xi >= dKdpsi(psicr)) {
			theta[m]=0.0;
			continue;
		}
		
		if (xi <= dKdpsi(psil) ) { //Слева от волны
			theta[m]= psil;
			continue;
		}

		while (dKdpsi(psi) < xi && psi > psicr)
			psi -= 1e-3;
		theta[m] = psi;
	}





	/*int m,n;
	double a, theta_new, theta_old;
	a=(ro_s-ro_l)/eta*gravity*K_abs;
	double p,q;
	double x;
	double D;
	double ro;
	double fi;
	double z1;
	double z2;
	double z;
	double z3;
	//Аналитическое решение ищется путем решения кубического уравнения на тетта в каждый момент времени и на каждом шаге по расстоянию
	for(m=1;m<M;m++)
	{
		double xi = m*h / (2 * a * t);
		if (xi > 1. / 8) {
			theta[m]=0.0;
			continue;
		}
		//printf ("%f %f\n",theta0, xi);	
		if (xi < theta0 / pow(theta0 + 1, 3)) {
			theta[m]=theta0;
			continue;
		}

		theta_old=1e6;
		theta_new=1.5;

		x=m*h;
		p=-1 / xi;
		q=-p;
		D=(p/3)*(p/3)*(p/3) +(q/2)*(q/2);
		if (D>0) {
			printf ("Error\n");
			exit(0);
		}
		ro=sqrt(-(p/3)*(p/3)*(p/3));
		fi=acos(-q/2/ro);
		z1=cos(fi/3);
		z2=cos(fi/3+2*M_PI/3);
		z3=cos(fi/3-2*M_PI/3);
		if(z1>z2) z=z1;
		if(z2>=z1) z=z2;
		if (z<z3) z=z3;
		z=2*pow(ro,1.0/3)*z;
		//n=0;
		/*while((theta_new-theta_old)*(theta_new-theta_old)>1e-14)
		{
			theta_old = theta_new;
			theta_new=(1+theta_old)*(1+theta_old)*(1+theta_old)*m*h/t/2/a;
			n++;
			//theta_new=1;

		} */
		//printf ("%d\n",n);
		//theta[m]=z-1;;
			//theta[m]=1;

	//}


}