// CHideFunc.cpp: 实现文件
//

#include "pch.h"
#include "LittleStringTools2.h"
#include "CHideFunc.h"
#include "afxdialogex.h"
#include <iostream>
#include <regex>


char sDlls[][MAX_LEN] = { "Kernel32.dll","User32.dll","ADVAPI32.dll","SHLWAPI.dll","SHELL32.dll","Winmm.dll",
        "WS2_32.dll","IMM32.dll","WININET.dll","AVICAP32.dll","MSVFW32.dll","PSAPI.DLL","WTSAPI32.dll" ,"Mpr.dll","Dnsapi.dll","advapi32.dll"};

// CHideFunc 对话框

IMPLEMENT_DYNAMIC(CHideFunc, CDialogEx)

CHideFunc::CHideFunc(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Func, pParent)
    , sShowFunc(_T(""))
{

}

CHideFunc::~CHideFunc()
{
}

BOOL CHideFunc::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    for (int i = 0; i < sizeof(sDlls) / sizeof(sDlls[0]); i++) {
        //DllCCombox.AddString(sDlls[i]);
        DllCCombox.InsertString(-1, sDlls[i]);
    }

    DllCCombox.SetCurSel(0);
    DllCCombox.SetDlgItemInt(0, 9);
	return TRUE; return 0;
}


void CHideFunc::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, DllCCombox);
    DDX_Text(pDX, IDC_EDIT2, sShowFunc);
    //DDX_Check(pDX, IDC_CHECK1, IsFindDll);
    DDX_Control(pDX, IDC_EDIT1, sFunc);
}


BEGIN_MESSAGE_MAP(CHideFunc, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CHideFunc::OnBnClickedCancel)
    ON_BN_CLICKED(IDOK, &CHideFunc::OnBnClickedOk)
END_MESSAGE_MAP()

string findDll(const string& sFunc)
{
    for (int i = 0; i < sizeof(sDlls) / sizeof(sDlls[0]); i++) {
        HMODULE hDll = LoadLibraryA(sDlls[i]);
        if (hDll) {
            FARPROC functionAddress = GetProcAddress(hDll, sFunc.c_str());
            if (functionAddress) {
                return sDlls[i];
            }
        }
    }
    return "";
}


// CHideFunc 结束进程
void CHideFunc::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	GetParent()->DestroyWindow();
}


bool IsDlls(char* sdll) {
    for (int i = 0; i < sizeof(sDlls) / sizeof(sDlls[0]); i++) {
        if (!strcmp(sDlls[i], sdll)) {
            return 1;
        }
    }
    return 0;
}

// 显示文本
void CHideFunc::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    CString sDll;
    CString sFuncName,input;
    string sFuncDef,strFirst,strLast, sFuncstr;

    // 根据函数定义获取函数名
    sFunc.GetWindowTextA(input);
    sFuncDef = input.GetBuffer();
    std::regex pattern("(^.*?\\s+)((?:\\w+\\s+){0,1}(\\w+))(\\([\\s\\S]*)");
    std::smatch matches;
    if (std::regex_search(sFuncDef, matches, pattern))
    {
        strFirst = matches[1].str();
        sFuncstr = matches[2].str();
        sFuncName = matches[3].str().c_str();
        strLast = matches[4].str();
    }

    // 判断函数名是否为空
    if (sFuncName.IsEmpty()){
        sShowFunc = "函数名不能为空";
        UpdateData(FALSE);
        return;
    }

    DllCCombox.GetWindowTextA(sDll);
    // 自动寻找dll,如果dll名不在数组中,则sdll值为输入值
    if (IsDlls(sDll.GetBuffer())) {
        sDll = "";
    }

    // 如果在数组中，则自动选择dll文件
    if (sDll.IsEmpty())
    {
        sDll = findDll(sFuncName.GetBuffer()).c_str();
        if (sDll.IsEmpty())
        {
            sShowFunc = "未找到dll，请手动输入";
            UpdateData(FALSE);
            return;
        }
    }


    // 根据dll名，自动拼接需要的字符串
    sShowFunc.Format("typedef %s(*%sFunc)%s\r\n\
HMODULE h%s = LoadLibrary((LPCSTR)\"%s\");\r\n\
%sFunc p%s = (%sFunc)GetProcAddress(h%s, (LPCSTR)\"%s\");\
", strFirst.c_str(), sFuncstr.c_str(), strLast.c_str(),sDll.Left(sDll.Find('.')).GetBuffer(),
sDll.GetBuffer(),sFuncName.GetBuffer(), sFuncName.GetBuffer(),sFuncName.GetBuffer(), sDll.Left(sDll.Find('.')).GetBuffer(), sFuncName.GetBuffer());

    UpdateData(FALSE);
}


BOOL CHideFunc::PreTranslateMessage(MSG* pMsg)
{
    return CDialogEx::PreTranslateMessage(pMsg);
}
