
// LittleStringTools2Dlg.h: 头文件
//

#pragma once
#include "CHideFunc.h"
#include "CIntroduce.h"
#include "CMyHideString.h"

// CLittleStringTools2Dlg 对话框
class CLittleStringTools2Dlg : public CDialogEx
{
// 构造
public:
	CLittleStringTools2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LITTLESTRINGTOOLS2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	afx_msg void OnSize(UINT nType, int cx, int cy);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	CMyHideString m_page1;
	CHideFunc m_page2;
	CIntroduce m_page3;

public:
	CTabCtrl ToolTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
};
