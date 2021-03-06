extern int M;
extern int N;			//Количество шагов по времени
extern double T0;					//Температура среды и верхней стенки
extern double T1;					//Температура нижней стенки		(К)
extern double length;  		//Длина области в метрах		(м)
extern double time_const;		//Время эксперимента 			(с)
//extern double tau;	//Величина шага по времени		(с) 
extern double h;				//Величина шага по расстоянию	(м)
//extern double eta; 			//Коэффициент Вязости			(Па*с)
extern double la;				//Коэффициент Теплопроводности	(Дж/(м*с*К))
extern double ro_l;			//Плотность жидкости			(Кг/м3)
extern double ro_s; 			//Плотность скелета				(Кг/м3)
extern double c_l;				//Теплоемкость	флюида				(Дж/К)
extern double c_s;				//Теплоемкость скелета				(Дж/К)
extern double gravity;			//Постоянная свободного падения	(м/с2)
extern double K_abs;			//Абсолютная проницаемость
extern double psi0;			//Насыщенность на границе
extern double psi_crit;		//Критическое значение насыщенности (относительной)
extern double alpha;		//Коэффициент в показателе экспоненты для расчета вязкости
extern double Tcrit;		//Температура в экспоненте для расчечта вязкоти