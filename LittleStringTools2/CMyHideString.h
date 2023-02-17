#pragma once


// CMyHideString 对话框

class CMyHideString : public CDialogEx
{
	DECLARE_DYNAMIC(CMyHideString)

public:
	CMyHideString(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMyHideString();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_String };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString sVar;
	CSpinButtonCtrl m_LenSpin;

	INT eLen,eLenOld;
	afx_msg void OnBnClickedCancel2();
	afx_msg void OnBnClickedOk();
	CString sRaw;
	CString sOut;
};
