#include "const.h" 
#include <stdio.h>
void analit(const double t, double* theta)
{
	int m,n;
	double a, theta_new, theta_old;
	a=(ro_s-ro_l)/eta*gravity;
	for(m=1;m<M;m++)
	{
		if (h*m>=t*a/4) theta[m]=1.0;
		if (h*m<t*a/4)
		{	
			theta_old=1e6;
			theta_new=0.5;
			//n=0;
			while((theta_new-theta_old)*(theta_new-theta_old)>1e-14)
			{
				theta_old = theta_new;
				theta_new=(1+theta_old)*(1+theta_old)*(1+theta_old)*m*h/t/2/a;
				//n++;

			} 
			//printf ("%d\n",n);
			theta[m]=theta_new;
		}

	}


}