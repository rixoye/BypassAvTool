#pragma once


// CIntroduce 对话框

class CIntroduce : public CDialogEx
{
	DECLARE_DYNAMIC(CIntroduce)

public:
	CIntroduce(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CIntroduce();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_About };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString sIntruduce;
};
