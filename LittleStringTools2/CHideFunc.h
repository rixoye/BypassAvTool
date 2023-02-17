#pragma once
#include <Windows.h>
#define MAX_LEN 255


using namespace std;
// CHideFunc 对话框




class CHideFunc : public CDialogEx
{
	DECLARE_DYNAMIC(CHideFunc)

public:
	CHideFunc(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHideFunc();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Func };
#endif

public:

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedCancel();


	CComboBox DllCCombox;
	afx_msg void OnBnClickedOk();
	CString sShowFunc;
	//BOOL IsFindDll;
	CEdit sFunc;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
