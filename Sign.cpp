#include"pch.h"
#include"Sign.h"


Sign::Sign() :N1(0), N2(0), N3(0), f1(0), f2(0), f3(0), fd(0) {};


void Sign::SetNs(int n1, int n2, int n3)
{
	N1 = n1;
	N2 = n2;
	N3 = n3;
	N = N1 + N2 + N3;
}
void Sign::Setfs(double ff1, double ff2, double ff3)
{
	f1 = ff1;
	f2 = ff2;
	f3 = ff3;
}
void Sign::Setfd(double FD)
{
	fd = FD;
}
void Sign::SetWlen(int WLEN)
{
	wlen = WLEN;
}
void Sign::SetCap(double Cap)
{
	cap = Cap;
}
void Sign::SetSignalDrvHWND(HWND hWnd)
{
	signal_drv.Create(hWnd);
}
void Sign::SetErrorDrvHWND(HWND hWnd)
{
	error_drv.Create(hWnd);
}


int Sign::GetResL()
{
	return resl;
}
int Sign::GetResR()
{
	return resr;
}


vector<double> Sign::CreateSign()
{
	vector<double>res;


	double ph = 0;
	for (int i = 0; i < N1; i++)
	{
		ph += 2 * pi * f1 / fd;
		res.push_back(100 * sin(ph));
	}
	for (int i = 0; i < N2; i++)
	{
		ph += 2 * pi * f2 / fd;
		res.push_back(100 * sin(ph));
	}
	for (int i = 0; i < N3; i++)
	{
		ph += 2 * pi * f3 / fd;
		res.push_back(100 * sin(ph));
	}

	signal = res;
	return res;
}
vector<double> Sign::MakePrediction()
{
	prediction.push_back(signal[0]);
	prediction.push_back(signal[1]);
	for (int i = 2; i < signal.size(); i++)prediction.push_back(2 * cos(2 * pi * f2 / fd) * signal[i - 1] - signal[i - 2]);
	return prediction;
}
vector<double> Sign::CalcError()
{
	for (int i = 0; i < signal.size(); i++)error.push_back((signal[i] - prediction[i]) * (signal[i] - prediction[i]));
	return error;
}
vector<double> Sign::CalcAverage()
{
	if (wlen % 2 != 0)wlen++;


	for (int i = wlen / 2; i < error.size() - wlen / 2; i++)
	{
		average.push_back(CalcWindowAverage(i-wlen/2, i + wlen/2));
	}


	return average;
}
double Sign::CalcWindowAverage(int left, int right)
{
	double res = 0;
	for (int i = left; i < right; i++)
	{
		res += error[i];
	}
	return res;
}
void Sign::Find()
{
	if (cap == 0)
	{
		resl = -1;
		resr = -1;
		return;
	}


	resl = 0;
	while (average[resl] > cap)
	{
		resl++;
		if (resl == average.size())
		{
			resl = -1;
			resr = -1;
			return;
		};
	}


	resr = resl;
	while (average[resr] < cap)
	{
		resr++;
		if (resr == average.size())
		{
			resr = -1;
			return;
		}
	}
	resr += wlen;
}

void Sign::Draw()
{
	signal_drv.DrawGraph(signal, fd);
	error_drv.DrawTwoGraph(error, average, fd, wlen / 2, cap);
}


void Sign::test()
{
	CreateSign();
	MakePrediction();
	CalcError();
	CalcAverage();
	Find();
	Draw();
}