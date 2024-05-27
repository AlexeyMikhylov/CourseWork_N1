// Курсовая работа по программированию
// Студента: Михайлов Алексей
// Группа: ИКПИ-34
// Вариант 13: Код А - 18: Код Б - 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <windows.h>
#include <locale.h>
#include <wchar.h>
#define N 1000

void clearBuffer();

// формирование массива времени
void form_t(int n, float *t)
{
	float tn = 10, tk = 60;
	float dt = (tk - tn) / (n - 1);

	for (int i = 0; i < n; i++)
	{
		t[i] = tn + i * dt;
	}
}

// формирование массива Uvx //код А, определение функции Uvx
void form_Uvx(float *Uvx, float *t, int n)
{
	float t1 = 15, t2 = 30, a = 50, b = 0.07, c = 0.1;

	for (int i = 0; i < n; i++)
	{
		if (t[i] <= t1)
		{
			Uvx[i] = 0;
		}
		else if (t[i] > t1 && t[i] <= t2)
		{
			Uvx[i] = a * (1 - pow(M_E, (double)(-b * (t[i] - t1))));
		}
		else if (t[i] > t2)
		{
			Uvx[i] = a * (1 - pow(M_E, (double)(-b * (t2 - t1)))) * pow(M_E, (double)(-c * (t[i] - t2)));
		}
	}
}

// формирование массива Uvix //Код Б, определение функции Uvix
void form_Uvix(float *Uvix, float *Uvx, int n)
{
	float a1 = 3.5;

	for (int i = 0; i < n; i++)
	{
		Uvix[i] = a1 * Uvx[i];
	}
}

// вывод данных в виде таблицы
void form_table(int n, float *t, float *Uvx, float *Uvix)
{
	wprintf(L"  №          t      Uвх          Uвых");
	printf("\n--------------------------------------");
	for (int i = 0; i < n; i++)
	{
		printf("\n| %2d | %6.4lf | %6.4lf | %6.4lf |", i, t[i], Uvx[i], Uvix[i]);
		printf("\n--------------------------------------");
	}
	printf("\n\n");
}

float parametr(int n, float *t, float *Uvx)
{
	float max = -999999;

	for (int i = 0; i < n; i++)
	{
		if (Uvx[i] > max)
		{
			max = Uvx[i];
		}
	}

	float vremya = 0;
	for (int i = 0; i < n; i++)
	{
		if (Uvx[i] == max)
		{
			vremya = t[i];
			break;
		}
	}

	return vremya;
}

// расчет погрешности
void pogreshnost(int n, float *t, float *Uvx, float *Uvix)
{
	float p = 1;
	float eps = 0.01; 
	float par = 1E+10; // начальное значение параметра (очень большое число)
	float par1;

	while (p > eps)
	{
		form_t(n, t);

		form_Uvx(Uvx, t, n);

		form_Uvix(Uvix, Uvx, n);

		par1 = parametr(n, t, Uvx);
		p = fabs(par - par1) / par1;
		wprintf(L"n = %d параметр = %6.3lf погрешность = %6.3lf\n", n, par1, p);
		par = par1;
		n = 2 * n;
	}
}

void zastavka()
{
	FILE* f = fopen("zast.txt", "r, ccs=UTF-8");
	if (f == NULL)
	{
		printf("Ошибка открытия файла\n");
		return 1;
	}

	wchar_t ch;
	while ((ch = fgetwc(f)) != WEOF)
	{
		putwchar(ch);
	}

	fclose(f);

	printf("\n\n");
}

void zapis(int n, float *t, float *Uvx, float *Uvix)
{
	FILE* f1, * f2, * f3;

	f1 = fopen("massiv_t.txt", "w");
	f2 = fopen("massiv_Uvx.txt", "w");
	f3 = fopen("massiv_Uvix.txt", "w");

	for (int i = 0; i < n; i++)
	{
		fprintf(f1, "\n %6.4f", t[i]);
		fprintf(f2, "\n %6.4f", Uvx[i]);
		fprintf(f3, "\n %6.4f", Uvix[i]);
	}

	fclose(f1);
	fclose(f2);
	fclose(f3);
}

void menu(int n, float *t, float *Uvx, float *Uvix)
{
	while (1)
	{
		wprintf(L"1 - контрольный рассчет для n точек\n2 - расчет параметра с заданной точностью\n3 - запись данных в файл\n");
		int option;
		scanf("%d", &option);

		switch (option)
		{
		case 1:
			wprintf(L"Введите количество точек для контрольного рассчета:");
			scanf("%d", &n);

			form_t(n, t);
			form_Uvx(Uvx, t, n);
			form_Uvix(Uvix, Uvx, n);
			form_table(n, t, Uvx, Uvix);
			break;
		case 2:
			wprintf(L"Введите количество точек для контрольного рассчета:");
			scanf("%d", &n);

			form_t(n, t);
			form_Uvx(Uvx, t, n);
			form_Uvix(Uvix, Uvx, n);

			pogreshnost(n, t, Uvx, Uvix);
			break;
		case 3:
			wprintf(L"Введите количество точек для контрольного рассчета:");
			scanf("%d", &n);

			form_t(n, t);
			form_Uvx(Uvx, t, n);
			form_Uvix(Uvix, Uvx, n);
			zapis(n, t, Uvx, Uvix);
			break;
		default:
			break;
		}

		clearBuffer();
		wprintf(L"\nПродолжить?\n'y' - да\n'q' - нет\n");
		char option2;
		scanf("%c", &option2);

		switch (option2)
		{
		case 'y':
			menu(n, t, Uvx, Uvix);
		case 'q':
			return 0;
		default:
			break;
		}
	}
}

void clearBuffer()
{
	if (getchar() != '\n')
	{
		printf("\n");

		while (getchar() != '\n');
	}
	return 0;
}

int main()
{
	//русский язык
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RU");

	//system("chcp 1251");
	//setlocale(LC_ALL, "UTF8");

	float t[N], Uvx[N], Uvix[N];
	int n = 0;

	zastavka();

	menu(n, t, Uvx, Uvix);

	printf("\n\n");
	return 0;
}
