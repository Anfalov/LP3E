#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>

using namespace std;

bool Simplex()
{
	//Считывание
	setlocale(LC_ALL, "RUSSIAN");
	int n, m;
	cout << "Введите количество переменных:" << endl;
	cin >> n;
	cout << "Введите количество условий:" << endl;
	cin >> m;
	vector<double> func(n + 1), b(m), cB(m), delta(n + m);
	vector<vector<double>> a(m, vector<double>(n + m));

	cout << "Введите коэффициенты максимизируемой функции (включая свободный член):" << endl;
	for (int i = 0; i < n + 1; i++)
		cin >> func[i];

	cout << "Введите коэффициенты условий:" << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
		cin >> b[i];
		for (int j = n; j < n + m; j++)
			a[i][j] = 0;
		a[i][n + i]++;
		cB[i] = n + i;
	}

	//Флаг о том, что решение найдено
	bool sol = false;

	//Основной цикл
	do
	{
		int otric = -1;
		for (int i = 0; i < n + m; i++)
		{
			//Если относится к базису, то delta = 0
			if (find(cB.begin(), cB.end(), i) != cB.end())
			{
				delta[i] = 0;
				continue;
			}
			//Присваиваем -Ci в дельту
			delta[i] = (i >= n) ? 0 : -func[i];
			//Суммируем в дельту Ai*Cb
			for (int j = 0; j < m; j++)
				delta[i] += a[j][i] * ((cB[j] >= n) ? 0 : func[cB[j]]);

			//Выбираем, если есть, минимальную из отрицательных дельта
			if (delta[i] < 0 && (otric == -1 || delta[i] < delta[otric]))
				otric = i;
		}

		//Если отрицательных нет, то мы нашли решение, выходим
		if (otric == -1)
		{
			sol = true;
			break;
		}

		//Ищем минимальный из положительных элементов A делённых на b в столбце с минимальной дельтой
		int min = -1;
		for (int i = 0; i < m; i++)
		{
			//Если элемент не отрицателен и минимален, то запоминаем его номер
			if (a[i][otric]>0 && (min == -1 || b[i] / a[i][otric] < b[min] / a[min][otric]))
				min = i;
		}

		//Если нет ни одного положительного элемента, то решения нет
		if (min == -1)
			break;

		//Переходим к другому базису
		cB[min] = otric;
		//Запоминаем делитель
		double tmp = a[min][otric];
		//Делим строку на элемент
		b[min] /= tmp;
		for (int i = 0; i < n + m; i++)
			a[min][i] /= tmp;

		//Вычитаем новую строку из других строк, для обнуления столбца 
		for (int i = 0; i < m; i++)
		{
			//Если это сама вычитаемая строка, то её не трогаем.
			if (i == min)
				continue;

			//Запоминаем множитель
			tmp = a[i][otric];
			for (int j = 0; j < n + m; j++)
				a[i][j] -= a[min][j] * tmp;
			b[i] -= b[min] * tmp;
		}
	} while (true);

	//Если решение найдено, выводим его
	if (sol)
	{
		//Считаем fmax, изначально присвоим значение свободного члена
		double fmax = func[n];
		for (int i = 0; i < m; i++)
			fmax += ((cB[i] >= n) ? 0 : func[cB[i]] * b[i]);
		cout << "Максимальное значение функции: " << fmax << endl;

		//Выводим вектор Xопт
		cout << "Вектор Xопт: (";
		for (int i = 0; i < n + m; i++)
		{
			//Проверяем, является ли элемент базисным, и находим его номер в решении
			int bas = -1;
			for (int j = 0; j < m; j++)
				if (cB[j] == i)
					bas = j;

			//Если элемента нет в базисе, то выводим 0, иначе его значение
			cout << ((bas == -1) ? 0 : b[bas]) << ((i != n + m - 1) ? "; " : ")");
		}
		cout << endl;
		return true;
	}

	//Если решение не найдено, сообщаем об этом
	else
		cout << "Решение не найдено." << endl;
	return false;
}