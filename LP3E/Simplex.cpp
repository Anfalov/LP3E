#include<iostream>
#include<math.h>
#include<vector>
#include<algorithm>

using namespace std;

bool Simplex()
{
	//����������
	setlocale(LC_ALL, "RUSSIAN");
	int n, m;
	cout << "������� ���������� ����������:" << endl;
	cin >> n;
	cout << "������� ���������� �������:" << endl;
	cin >> m;
	vector<double> func(n + 1), b(m), cB(m), delta(n + m);
	vector<vector<double>> a(m, vector<double>(n + m));

	cout << "������� ������������ ��������������� ������� (������� ��������� ����):" << endl;
	for (int i = 0; i < n + 1; i++)
		cin >> func[i];

	cout << "������� ������������ �������:" << endl;
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

	//���� � ���, ��� ������� �������
	bool sol = false;

	//�������� ����
	do
	{
		int otric = -1;
		for (int i = 0; i < n + m; i++)
		{
			//���� ��������� � ������, �� delta = 0
			if (find(cB.begin(), cB.end(), i) != cB.end())
			{
				delta[i] = 0;
				continue;
			}
			//����������� -Ci � ������
			delta[i] = (i >= n) ? 0 : -func[i];
			//��������� � ������ Ai*Cb
			for (int j = 0; j < m; j++)
				delta[i] += a[j][i] * ((cB[j] >= n) ? 0 : func[cB[j]]);

			//��������, ���� ����, ����������� �� ������������� ������
			if (delta[i] < 0 && (otric == -1 || delta[i] < delta[otric]))
				otric = i;
		}

		//���� ������������� ���, �� �� ����� �������, �������
		if (otric == -1)
		{
			sol = true;
			break;
		}

		//���� ����������� �� ������������� ��������� A ������� �� b � ������� � ����������� �������
		int min = -1;
		for (int i = 0; i < m; i++)
		{
			//���� ������� �� ����������� � ���������, �� ���������� ��� �����
			if (a[i][otric]>0 && (min == -1 || b[i] / a[i][otric] < b[min] / a[min][otric]))
				min = i;
		}

		//���� ��� �� ������ �������������� ��������, �� ������� ���
		if (min == -1)
			break;

		//��������� � ������� ������
		cB[min] = otric;
		//���������� ��������
		double tmp = a[min][otric];
		//����� ������ �� �������
		b[min] /= tmp;
		for (int i = 0; i < n + m; i++)
			a[min][i] /= tmp;

		//�������� ����� ������ �� ������ �����, ��� ��������� ������� 
		for (int i = 0; i < m; i++)
		{
			//���� ��� ���� ���������� ������, �� � �� �������.
			if (i == min)
				continue;

			//���������� ���������
			tmp = a[i][otric];
			for (int j = 0; j < n + m; j++)
				a[i][j] -= a[min][j] * tmp;
			b[i] -= b[min] * tmp;
		}
	} while (true);

	//���� ������� �������, ������� ���
	if (sol)
	{
		//������� fmax, ���������� �������� �������� ���������� �����
		double fmax = func[n];
		for (int i = 0; i < m; i++)
			fmax += ((cB[i] >= n) ? 0 : func[cB[i]] * b[i]);
		cout << "������������ �������� �������: " << fmax << endl;

		//������� ������ X���
		cout << "������ X���: (";
		for (int i = 0; i < n + m; i++)
		{
			//���������, �������� �� ������� ��������, � ������� ��� ����� � �������
			int bas = -1;
			for (int j = 0; j < m; j++)
				if (cB[j] == i)
					bas = j;

			//���� �������� ��� � ������, �� ������� 0, ����� ��� ��������
			cout << ((bas == -1) ? 0 : b[bas]) << ((i != n + m - 1) ? "; " : ")");
		}
		cout << endl;
		return true;
	}

	//���� ������� �� �������, �������� �� ����
	else
		cout << "������� �� �������." << endl;
	return false;
}