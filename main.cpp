//#include <stdio.h>
#include "const.h"
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
//-----------------------------Глобальные переменные-------------------------
int M=10;						//Количество шагов по растоянию
int N=10000;						//Количество шагов по времени
int T0=300;						//Температура среды и верхней стенки
int T1=400;						//Температура нижней стенки		(К)
double length=10.0;  			//Длина области в метрах		(м)
double time_const =1e-4;			//Время эксперимента 			(с)
double tau=1.0*time_const/N;	//Величина шага по времени		(с) 
double h=length/M;				//Величина шага по расстоянию	(м)
double etta=1e-3; 				//Коэффициент Вязости			(Па*с)
double la=0.6;					//Коэффициент Теплопроводности	(Дж/(м*с*К))
double ro_l=1000.0; 			//Плотность жидкости			(Кг/м3)
double ro_s=1400.0; 			//Плотность скелета				(Кг/м3)
double c=1.0;					//Теплоемкость					(Дж/К)
double gravity=9.8;				//Постоянная свободного падения	(м/с2)
//---------------------------------------------------------------------------------------------------

void K_permeability(double* tetta, double* K_perm);
void termal(double* T, double* Tnew, double* q);
void W_filtration(double* tetta, double* K_perm, double* W_fil );
void saturation(double* tetta, double* W_fil, double* tetta_new);




main()
{	int n;//Шаг по времени
	int m;//Шаг по расстоянию
	std::fstream fs;
	std::fstream fs1;
	fs.open("output.txt", std::fstream::out);
	fs1.open("lay1.txt", std::fstream::out);
	double* switcher;					//Меняет местами старый слой c новым


	double* W_fil=(double*)calloc(M+1, sizeof(double)); 		// Вектор Фильтрации
	double* tetta_new=(double*)calloc(M, sizeof(double));		//Отношение двух нассыщеностей на новом слое
	double* tetta=(double*)calloc(M, sizeof(double));			//Отношение двух нассыщеностей
	double* K_perm=(double*)calloc(M, sizeof(double));			//Проницаемость
//----------------------------------------Начальные и граничные условия---------------------------
	
	W_fil[0]=0;
	W_fil[M-2]=0;

	for (m=1; m<M-1; m++)
	{
		tetta[m]=1.0;
		fs <<(tetta[m]/(tetta[m]+1)) <<" ";
	}
	fs << std::endl;
//----------------------------------------Расчет----------------------------------------------------

	for (n=0;n<N;n++)
	{
		K_permeability(tetta, K_perm);
		W_filtration(tetta, K_perm, W_fil );
		saturation(tetta, W_fil,tetta_new);
//-------------------------------Вывод-------------------------------------------------------
		for (m=0;m<M;m++)
		{
			fs <<(tetta_new[m]/(1+tetta_new[m])) <<" ";
			//fs <<W_fil[m]<<" ";
			//fs <<K_perm[m]<<" ";
		} 
		fs << std::endl;
		fs1 << n <<" " << (tetta_new[5]/(1+tetta_new[5]));
		fs1 << std::endl;
//----------------------------------Конец Вывода-----------------------------------------------
		switcher=tetta;
		tetta=tetta_new;
		tetta_new=switcher;
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