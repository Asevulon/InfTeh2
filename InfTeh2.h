
// InfTeh2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CInfTeh2App:
// Сведения о реализации этого класса: InfTeh2.cpp
//

class CInfTeh2App : public CWinApp
{
public:
	CInfTeh2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CInfTeh2App theApp;
