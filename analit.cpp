#include "const.h" 
#include <stdio.h>
void analit(const double t, double* tetta)
{
	int m,n;
	double a, tetta_new, tetta_old;
	a=(ro_s-ro_l)/etta*gravity;
	for(m=1;m<M;m++)
	{
		if (h*m>=t*a/4) tetta[m]=1.0;
		if (h*m<t*a/4)
		{	
			tetta_old=1e6;
			tetta_new=0.5;
			//n=0;
			while((tetta_new-tetta_old)*(tetta_new-tetta_old)>1e-14)
			{
				tetta_old = tetta_new;
				tetta_new=(1+tetta_old)*(1+tetta_old)*(1+tetta_old)*m*h/t/2/a;
				//n++;

			} 
			//printf ("%d\n",n);
			tetta[m]=tetta_new;
		}

	}


}