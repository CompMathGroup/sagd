#include "const.h" 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void analit(const double t, double* psi, const double eta)
{
	int m,n;
	double a, psi_new, psi_old;
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
			psi[m]=0.0;
			continue;
		}
		//printf ("%f %f\n",psi0, xi);	
		if (xi < psi0 / pow(psi0 + 1, 3)) {
			psi[m]=psi0;
			continue;
		}

		psi_old=1e6;
		psi_new=1.5;

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
		/*while((psi_new-psi_old)*(psi_new-psi_old)>1e-14)
		{
			psi_old = psi_new;
			psi_new=(1+psi_old)*(1+psi_old)*(1+psi_old)*m*h/t/2/a;
			n++;
			//psi_new=1;

		} */
		//printf ("%d\n",n);
		psi[m]=z-1;;
			//psi[m]=1;

	}


}