// Курсовая работа
// Вариант 13: Код А - 18: Код Б - 1

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <locale.h>

#define N 1000

int main()
{
	//русский язык
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RU");

	float t[N], Uvx[N], Uvix[N];
	int n = 0, i = 0;

	wprintf(L"Введите количество точек для контрольного рассчета:");
	scanf("%d", &n);
	//printf("%f", exp(1)); //e^1 (e)

	float tn = 10, tk = 60, dt;
	dt = (tk - tn)/(n - 1);

	//формирование массива t
	for (i = 0; i < n; i++)
	{
		t[i] = tn + i * dt;
	}

	float t1 = 15, t2 = 60, a = 50, b = 0.07, c = 0.1;

	//формирование массива Uvx //код А, определение функции Uvx
	for (i = 0; i < n; i++)
	{
		if (t[i] <= t1)
		{
			Uvx[i] = 0;
		}
		else if (t1 < t[i] <= t2)
		{
			Uvx[i] = a * ( 1 - exp( (double)b * (-1) * ( (double)t[i] - (double)t1 ) ) );
		}
		else if (t[i] > t2)
		{
			Uvx[i] = a * ( 1 - exp( (double)b * (-1) * ( (double)t2 - (double)t1 ) )
				* exp( (double)c * (-1) * ( (double)t[i] - (double)t2 )));
		}
	}

	float a1 = 3.5;

	//Формирование массива Uvix //Код Б, определение функции Uvix
	for (i = 0; i < n; i++)
	{
		Uvix[i] = a * Uvx[i];
	}

	//Вывод данных в виде таблицы
	wprintf(L"    №         t      Uвх          Uвых");
	printf("\n--------------------------------------");
	for (i = 0; i < n; i++)
	{
		printf("\n| %2d | %6.4lf | %6.4lf | %6.4lf |", i, t[i], Uvx[i], Uvix[i]);
		printf("\n--------------------------------------");
	}

	printf("\n\n");
	return 0;
}
