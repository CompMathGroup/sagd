//#include <stdio.h>
#include "const.h"
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
//-----------------------------Глобальные переменные-------------------------
int M=500;						//Количество шагов по растоянию
int N=1000;					//Количество шагов по времени
double T0=300.0;						//Температура среды и верхней стенки
double T1=400.0;						//Температура нижней стенки		(К)
double length=10.0;  			//Длина области в метрах		(м)
double time_const =1e-6;		//Время эксперимента 			(с)
double tau=1.0*time_const/N;	//Величина шага по времени		(с) 
double h=length/(M);				//Величина шага по расстоянию	(м)
double eta=1e-3; 				//Коэффициент Вязости			(Па*с)
double la=0.6;					//Коэффициент Теплопроводности	(Дж/(м*с*К))
double ro_l=1000.0; 			//Плотность жидкости			(Кг/м3)
double ro_s=1400.0; 			//Плотность скелета				(Кг/м3)
double c=1.0;					//Теплоемкость					(Дж/К)
double gravity=9.8;				//Постоянная свободного падения	(м/с2)
double K_abs=1.0;				//Абсолютная проницаемость
double theta0=2.0;
//---------------------------------------------------------------------------------------------------
void analit(const double t, double* theta);
void K_permeability(double* theta, double* K_perm);
void termal(double* T, double* Tnew, double* q);
void W_filtration(double* theta, double* K_perm, double* W_fil );
void saturation(double* theta, double* W_fil, double* theta_new);


main()
{	int n;//Шаг по времени
	int m;//Шаг по расстоянию
	std::fstream fs;
	std::fstream fs1;
	char buf[128];
	fs.open("output.txt", std::fstream::out);
	fs1.open("lay1.txt", std::fstream::out);
	double* switcher;					//Меняет местами старый слой c новым
	std::fstream fs2;
	double* W_fil=(double*)calloc(M+1, sizeof(double)); 		// Вектор Фильтрации
	double* theta_new=(double*)calloc(M+1, sizeof(double));		//Отношение двух нассыщеностей на новом слое
	double* theta=(double*)calloc(M+1, sizeof(double));			//Отношение двух нассыщеностей
	double* theta_analytic=(double*)calloc(M+1, sizeof(double));//Отношение насыщенностей по аналитическому решению
	double* K_perm=(double*)calloc(M+1, sizeof(double));			//Проницаемость
//----------------------------------------Начальные и граничные условия---------------------------
	//W_fil[0]=0;
	//W_fil[M-2]=0;
	theta[0]=theta0;
	theta_new[0]=theta0;
	for (m=1; m<M; m++)
	{
		theta[m]=0.0;
	}
//----------------------------------------Расчет----------------------------------------------------

	for (n=0;n<N;n++)
	{
		K_permeability(theta, K_perm);			//Вычисление проницаемости
		W_filtration(theta, K_perm, W_fil );	//Вычисление скорости филтрации 
		saturation(theta, W_fil,theta_new);		//Вычисление насыщенности на новом слое

		analit((n+1)*tau, theta_analytic); 		//Аналитическое решение
//-------------------------------Вывод-------------------------------------------------------
		sprintf(buf,"./out/output%06d.csv",n);
		fs2.open(buf, std::fstream::out);
		fs2 << "x,theta,analytic" << std::endl;
		for (m=0;m<M;m++)
		{
			fs2 << m * h <<","<<(theta_new[m]/(1+theta_new[m]))<<","<<(theta_analytic[m]/(1+theta_analytic[m]));
			//fs2 << m * h <<","<<theta_new[main];						//вывод отношения насыщенностей
			fs2 << std::endl;
		}
		fs2.close();
//----------------------------------Конец Вывода-----------------------------------------------
		switcher=theta;
		theta=theta_new;
		theta_new=switcher;
	}

	

/*
//--------------------------------------Тепловой Расчет-------------------------------------------------
	double* T=(double*)calloc(M, sizeof(double));				//Температура на старом слое 
	double* Tnew=(double*)calloc(M, sizeof(double)); 			//Температура на новом слое	
	double* q=(double*)calloc(M, sizeof(double));				// Поток тепла

//----------------------------------Начальные и граничные условия----------------------------
	T[0]=T1;
	fs <<T[0] <<" ";
	Tnew[0]=T1;
	Tnew[M-1]=T0;
	for (m=1; m<M; m++)
		{
			T[m]=T0;
			fs <<T[m] <<" ";

		}
		fs << std::endl;
//--------------------------------------Расчет-------------------------------------
	for (n=0;n<N;n++)
	{
		termal(T, Tnew, q);
//----------------------------------Вывод-----------------------------------------------------
		for (m=0; m<M; m++)
		{
			fs <<Tnew[m] <<" ";
		}
		fs1 <<n <<" "<<Tnew[5];
		fs1 << std::endl;
		fs << std::endl;
//--------------------------------Конец Вывода--------------------------------------------
		switcher=T;
		T=Tnew;
		Tnew=switcher;
	}
	*/
	fs.close();
	fs1.close();
	return 0;
}