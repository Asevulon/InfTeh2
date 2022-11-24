
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "InfTeh2.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFTEH2_DIALOG, pParent)
	, N1(100)
	, N2(150)
	, N3(250)
	, f1(5)
	, f2(25)
	, f3(50)
	, fd(600)
	, wlen(24)
	, cap(0)
	, resl(0)
	, resr(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, N1);
	DDX_Text(pDX, IDC_EDIT2, N2);
	DDX_Text(pDX, IDC_EDIT1, N3);
	DDX_Text(pDX, IDC_EDIT4, f1);
	DDX_Text(pDX, IDC_EDIT5, f2);
	DDX_Text(pDX, IDC_EDIT6, f3);
	DDX_Text(pDX, IDC_EDIT7, fd);
	DDX_Text(pDX, IDC_EDIT8, wlen);
	DDX_Text(pDX, IDC_EDIT9, cap);
	DDX_Text(pDX, IDC_EDIT10, resl);
	DDX_Text(pDX, IDC_EDIT11, resr);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void MyDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	Sign sgn;
	sgn.SetSignalDrvHWND(GetDlgItem(IDC_SIGNAL)->GetSafeHwnd());
	sgn.SetErrorDrvHWND(GetDlgItem(IDC_ERROR)->GetSafeHwnd());


	UpdateData();


	sgn.SetNs(N1, N2, N3);
	sgn.Setfs(f1, f2, f3);
	sgn.Setfd(fd);
	sgn.SetWlen(wlen);
	sgn.SetCap(cap);

	sgn.test();
	resl = sgn.GetResL();
	resr = sgn.GetResR();
	UpdateData(FALSE);
}
