#pragma once
#include"Drawer.h"
#include<math.h>
using namespace std;


const double pi = 4 * atan(1);


class Sign
{
private:
	int
		N,
		N1,
		N2,
		N3,
		resl,
		resr;
	

	int
		wlen;


	double
		f1,
		f2,
		f3;


	double
		fd,
		cap;


	Drawer
		signal_drv,
		error_drv;


	vector<double>
		signal,
		prediction,
		error,
		average;


protected:
	vector<double> CreateSign();
	vector<double> MakePrediction();
	vector<double> CalcError();
	vector<double> CalcAverage();
	double CalcWindowAverage(int left, int right);
	void Find();

	void Draw();


public:
	Sign();


	void SetNs(int n1, int n2, int n3);
	void Setfs(double ff1, double ff2, double ff3);
	void Setfd(double FD);
	void SetWlen(int WLEN);
	void SetCap(double Cap);
	void SetSignalDrvHWND(HWND hWnd);
	void SetErrorDrvHWND(HWND hWnd);


	int GetResL();
	int GetResR();


	void test();
};