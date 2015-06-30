//#include <stdio.h>
#include "const.h"
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
//-----------------------------Глобальные переменные-------------------------
int M=500;						//Количество шагов по растоянию
int N=2000;						//Количество шагов по времени
double T0=300.0;				//Температура среды и верхней стенки
double T1=500.0;				//Температура нижней стенки		(К)
double length=10.0;  			//Длина области в метрах		(м)
double time_const = 4e7;		//Время эксперимента 			(с)
//double tau=1.0*time_const/N;	//Величина шага по времени		(с) 
double h=length/(M);			//Величина шага по расстоянию	(м)
//double eta=1e-3; 				//Коэффициент Вязости			(Па*с)
double la=0.6;					//Коэффициент Теплопроводности	(Дж/(м*с*К))
double ro_l=1000.0; 			//Плотность жидкости			(Кг/м3)
double ro_s=1400.0; 			//Плотность скелета				(Кг/м3)
double c_l = 1e3;				//Теплоемкость флюида			(Дж/К)
double c_s = 2e3;				//Теплоемкость скелета
double gravity=9.8;				//Постоянная свободного падения	(м/с2)
double K_abs=1e-11;				//Абсолютная проницаемость
double psi0=2.0;				//Насыщенность на границе
double psi_crit=0.1/0.9;			//Критическое значение насыщенности (относительной)
double alpha = 0.02;			//Коэффициент в показателе экспоненты для расчета вязкости
double Tcrit = 400;				//Температура в экспоненте для расчечта вязкоти
//---------------------------------------------------------------------------------------------------
double theta_s(const double psi);
double theta_l(const double psi);
void analit(const double t, double* psi, const double eta);
void K_permeability(double* psi, double* K_perm);
void T_cond(double* q, const double* psi, const double* T);
void termal(const double* T, double* Tnew, const double* q, const double* psi, const double* W_fil, const double* psi_new, const double tau);
void W_filtration(double* psi, double* K_perm, double* W_fil, double tau);
void saturation(double* psi, double* W_fil, double* psi_new);
void filtr_satur(const double *K_perm, const double *psi, double *psi_new, double *W_fil, double tau, double *a_max, const double* eta);
void viscosity(double * eta, const double* T);


main()
{	int n;				//Шаг по времени
	int m;				//Шаг по расстоянию
	double a_max;		//Максимальная скорость фильтрации для вычисления шага по времени
	double tau, t;
	double z;
	std::fstream fs;
	std::fstream fs1;
	char buf[128];
	fs.open("output.txt", std::fstream::out);
	fs1.open("lay1.txt", std::fstream::out);
	double* switcher;					//Меняет местами старый слой c новым
	std::fstream fs2;

	double tau1, tau2;
	double T_analyt, kappa;
	double* T=(double*)calloc(M, sizeof(double));				//Температура на старом слое 
	double* Tnew=(double*)calloc(M, sizeof(double)); 			//Температура на новом слое	
	double* q=(double*)calloc(M, sizeof(double)); 			//Температура на новом слое	
	double* eta = (double*)calloc(M+1, sizeof(double));			//Вязкость
	double* W_fil=(double*)calloc(M+1, sizeof(double)); 		// Вектор Фильтрации
	double* psi_new=(double*)calloc(M+1, sizeof(double));		//Отношение двух нассыщеностей на новом слое
	double* psi=(double*)calloc(M+1, sizeof(double));			//Отношение двух нассыщеностей
	double* psi_analytic=(double*)calloc(M+1, sizeof(double));	//Отношение насыщенностей по аналитическому решению
	double* K_perm=(double*)calloc(M+1, sizeof(double));			//Проницаемость
//----------------------------------------Начальные и граничные условия---------------------------
	W_fil[0]=0;
	T[0] = T0;
	Tnew[0] = T0;
	psi[0] = 0;
	psi_new[0] = 0;
	for (m=1; m<M; m++)
	{
		psi[m]=3.0; 
		T[m] = T1;
		//eta[m] = 1000.0;
	}
	t = 0;
	tau = 1e-20;
	n = 0;
	//T[50] = T1;

//----------------------------------------Расчет----------------------------------------------------
	while (t < time_const)
	{
		K_permeability(psi, K_perm);									//Вычисление проницаемости
		viscosity(eta, T);												//Вычисление вязкости
		filtr_satur(K_perm, psi, psi_new, W_fil, tau, &a_max, eta);		//Вычисление скорости фильтрации и отношений насыщенностей + a_max
		T_cond(q, psi, T);
		termal(T, Tnew, q, psi, W_fil, psi_new, tau);

		//W_filtration(psi, K_perm, W_fil );	//Вычисление скорости филтрации 
		//saturation(psi, W_fil,psi_new, tau);		//Вычисление насыщенности на новом слое
		//analit((n+1)*tau, psi_analytic); 		//Аналитическое решение
//-------------------------------Вывод-------------------------------------------------------
		if (n % 10 == 0)
		{
			fs1 << tau1 << ',' << tau2 << ',' << t;
			fs1 <<std::endl;
			sprintf(buf,"./out/output%07d.csv",n);
			fs2.open(buf, std::fstream::out);
			fs2 << "x, psi, W_fil, eta , T , Q, z, T_analyt" << std::endl;
			z = 0;
			for (m=1;m<M;m++)
			{
				kappa = la /(ro_l * c_l * psi_new[m] + ro_s * c_s) /(1 + psi_new[m]);
				T_analyt = 300 + 200. * erfc( m * h / sqrt(4 * t * kappa));
				z = z + h *(1 + psi_new[m]);
				fs2 << m * h <<","<<(psi_new[m]/(1+psi_new[m])) <<"," << W_fil[m] <<"," << eta[m] <<"," << Tnew[m] <<"," << q[m] <<"," << z <<"," << T_analyt ;
				//fs2 << m * h <<","<<psi_new[main];						//вывод отношения насыщенностей
				fs2 << std::endl;
			}
			fs2.close();
		}

//----------------------------------Конец Вывода-----------------------------------------------
		switcher = psi;
		psi = psi_new;
		psi_new = switcher;

		switcher = T;
		T = Tnew;
		Tnew = switcher;

		n++;
		t+=tau;
		tau1 = h / a_max / 2 / (K_abs  * (ro_s - ro_l) * gravity );
		tau2 = h * h * ro_s * c_s / la / 2;
		if (tau1 > tau2)
			tau = tau2;
		else 
			tau = tau1;
		
		//printf(" %d %.8f \n",n, t);
	}

	


	fs.close();
	fs1.close();
	return 0;
}