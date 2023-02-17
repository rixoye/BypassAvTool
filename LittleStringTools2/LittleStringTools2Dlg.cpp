
// LittleStringTools2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LittleStringTools2.h"
#include "LittleStringTools2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLittleStringTools2Dlg 对话框
CLittleStringTools2Dlg::CLittleStringTools2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LITTLESTRINGTOOLS2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLittleStringTools2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, ToolTab);
}

void CLittleStringTools2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CDialogEx* pWnd[3]{};
	if (m_page1)pWnd[0] = &m_page1;
	if (m_page2)pWnd[1] = &m_page2;
	if (m_page3)pWnd[2] = &m_page3;
	

	for (int i = 0; i < 3; i++)
	{
		//获取控件句柄 
		if (pWnd[i])//判断是否为空，因为对话框创建时会调用此函数，而当时控件还未创建 
		{
			CRect rc;
			this->GetClientRect(&rc);
			rc.DeflateRect(2, 40, 2, 2);
			pWnd[i]->MoveWindow(rc);

		}
	}


}

BEGIN_MESSAGE_MAP(CLittleStringTools2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CLittleStringTools2Dlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CLittleStringTools2Dlg 消息处理程序
BOOL CLittleStringTools2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	ToolTab.InsertItem(0, "字符串隐藏");
	ToolTab.InsertItem(1, "动态函数调用");
	ToolTab.InsertItem(2, "使用说明");



	//创建子窗口
	m_page1.Create(IDD_String, GetDlgItem(IDD_LITTLESTRINGTOOLS2_DIALOG));
	m_page2.Create(IDD_Func, GetDlgItem(IDD_LITTLESTRINGTOOLS2_DIALOG));
	m_page3.Create(IDD_About, GetDlgItem(IDD_LITTLESTRINGTOOLS2_DIALOG));

	//控制两个窗口的大小
	CRect rc;
	ToolTab.GetClientRect(&rc);
	rc.DeflateRect(2, 40, 2, 2);
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	m_page3.MoveWindow(&rc);


	//显示第一个子窗口
	m_page1.ShowWindow(SW_SHOW);
	m_page2.ShowWindow(SW_HIDE);
	m_page3.ShowWindow(SW_HIDE);

	//开启防双开
	HANDLE hMutex = CreateMutexA(NULL, FALSE, "YJ");
	if (hMutex)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			MessageBox("双开程序了");
			ExitProcess(-1);
		}
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CLittleStringTools2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLittleStringTools2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLittleStringTools2Dlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int CurSel = ToolTab.GetCurSel();
	switch (CurSel)
	{
	case 0:
		m_page1.ShowWindow(true);
		m_page2.ShowWindow(false);
		m_page3.ShowWindow(false);
		break;
	case 1:
		m_page1.ShowWindow(false);
		m_page2.ShowWindow(true);
		m_page3.ShowWindow(false);
		break;
	case 2:
		m_page1.ShowWindow(false);
		m_page2.ShowWindow(false);
		m_page3.ShowWindow(true);
		break;
	default:
		break;
	}


}
