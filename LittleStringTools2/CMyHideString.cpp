// CMyHideString.cpp: 实现文件
//

#include "pch.h"
#include "LittleStringTools2.h"
#include "CMyHideString.h"
#include "afxdialogex.h"



void GenerateString(CString& dest, const unsigned int len)
{
	dest = "";
	const unsigned char allChar[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	unsigned int cnt, randNo;
	srand((unsigned int)time(NULL));

	for (cnt = 0; cnt < len; cnt++)
	{
		randNo = rand() % 62;
		char c = allChar[randNo];
		dest += c;
	}
}

// CMyHideString 对话框
IMPLEMENT_DYNAMIC(CMyHideString, CDialogEx)

CMyHideString::CMyHideString(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_String, pParent)
	, sVar(_T(""))
	, eLen(0)
	, sRaw(_T(""))
	, sOut(_T(""))
{
}

CMyHideString::~CMyHideString()
{
}

BOOL CMyHideString::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	eLen = 5;
	eLenOld = eLen;
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4);
	m_LenSpin.SetBuddy(pEdit);
	m_LenSpin.SetRange(5, 20);
	m_LenSpin.SetPos(eLen);


	GenerateString(sVar, eLen);
	UpdateData(FALSE);

	return TRUE;
}

void CMyHideString::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, sVar);
	DDX_Control(pDX, IDC_SPIN1, m_LenSpin);
	DDX_Text(pDX, IDC_EDIT4, eLen);
	DDV_MinMaxInt(pDX, eLen, 5, 20);
	DDX_Text(pDX, IDC_EDIT1, sRaw);
	DDX_Text(pDX, IDC_EDIT2, sOut);
}


BEGIN_MESSAGE_MAP(CMyHideString, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CMyHideString::OnBnClickedCancel)
	ON_BN_CLICKED(IDCANCEL2, &CMyHideString::OnBnClickedCancel2)
	ON_BN_CLICKED(IDOK, &CMyHideString::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyHideString 消息处理程序

void CMyHideString::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->DestroyWindow();
}


// 生成随机变量名
void CMyHideString::OnBnClickedCancel2()
{
	// TODO: 在此添加控件通知处理程序代码
	eLen = GetDlgItemInt(IDC_EDIT4);
	GenerateString(sVar, eLen);

	SetDlgItemText(IDC_EDIT3, sVar);

	//UpdateData(FALSE);
}


void HexToAscii(unsigned char* pHex, CString& pAscii, int nHexLen)
{
	char Nibble[2]{};
	for (int i = 0; i < nHexLen; i++)
	{
		Nibble[0] = (pHex[i] & 0xF0) >> 4;
		Nibble[1] = pHex[i] & 0x0F;
		for (int j = 0; j < 2; j++)
		{
			if (Nibble[j] < 10)
				Nibble[j] += 0x30;
			else
			{
				if (Nibble[j] < 16)
					Nibble[j] = Nibble[j] - 10 + 'A';
			}

		}	// for (int j = ...)
		pAscii += "0x";
		pAscii = pAscii + Nibble[0] + Nibble[1] + ", ";
	}	// for (int i = ...)
}

// 生成动态调用字符串
void CMyHideString::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT1, sRaw);
	if (sRaw.IsEmpty()) {
		return;
	}

	int i = sRaw.Find("\"");
	int j = sRaw.Find("\"", i + 1);

	if (i != -1) {
		// 截取字符串
		CString data = sRaw.Mid(i + 1, j - i - 1);
		eLen = GetDlgItemInt(IDC_EDIT4);
		if(eLenOld != eLen){
			OnBnClickedCancel2();
			eLenOld = eLen;
		}
		sOut = "unsigned char " + sVar + "[] = {";
		HexToAscii((unsigned char*)data.GetBuffer(), sOut, data.GetLength());
		sOut += " 0x00};\r\n";

	}

	SetDlgItemText(IDC_EDIT2, sOut);
}
