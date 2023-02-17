// CIntroduce.cpp: 实现文件
//

#include "pch.h"
#include "LittleStringTools2.h"
#include "CIntroduce.h"
#include "afxdialogex.h"

#define MULTILINE(...) #__VA_ARGS__
// CIntroduce 对话框

IMPLEMENT_DYNAMIC(CIntroduce, CDialogEx)

CIntroduce::CIntroduce(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_About, pParent)
	, sIntruduce(_T(""))
{
	sIntruduce = MULTILINE(
		字符串隐藏使用说明\r\n
		输入 char* k = "hello world"; 或 char k[] = "hello world"; 或 "hello world" 都可以 \r\n
		输出可以指定变量名的变量（默认随机变量）\r\n
		unsigned char eV2gv[] = { 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64,  0x00 };\r\n\r\n

		
		函数调用的使用说明\r\n
		输入函数定义，例如：\r\n
			BOOL CreateProcessA(\r\n
				[in, optional]\t      LPCSTR               \t lpApplicationName, \r\n
				[in, out, optional]\t LPSTR                \t lpCommandLine, \r\n
				[in, optional]\t      LPSECURITY_ATTRIBUTES\t lpProcessAttributes, \r\n
				[in, optional]\t      LPSECURITY_ATTRIBUTES\t lpThreadAttributes, \r\n
				[in]          \t      BOOL                 \t bInheritHandles, \r\n
				[in]          \t      DWORD                \t dwCreationFlags, \r\n
				[in, optional]\t      LPVOID               \t lpEnvironment, \r\n
				[in, optional]\t      LPCSTR               \t lpCurrentDirectory, \r\n
				[in]          \t      LPSTARTUPINFOA       \t lpStartupInfo, \r\n
				[out]         \t      LPPROCESS_INFORMATION\t lpProcessInformation\r\n
			);\r\n

		输出：\r\n
		typedef BOOL (*CreateProcessAFunc)(\r\n
			[in, optional]\t      LPCSTR               \t lpApplicationName, \r\n
			[in, out, optional]\t LPSTR                \t lpCommandLine, \r\n
			[in, optional]\t      LPSECURITY_ATTRIBUTES\t lpProcessAttributes, \r\n
			[in, optional]\t      LPSECURITY_ATTRIBUTES\t lpThreadAttributes, \r\n
			[in]          \t      BOOL                 \t bInheritHandles, \r\n
			[in]          \t      DWORD                \t dwCreationFlags, \r\n
			[in, optional]\t      LPVOID               \t lpEnvironment, \r\n
			[in, optional]\t      LPCSTR               \t lpCurrentDirectory, \r\n
			[in]          \t      LPSTARTUPINFOA       \t lpStartupInfo, \r\n
			[out]         \t      LPPROCESS_INFORMATION\t lpProcessInformation\r\n
		); \r\n																 \r\n

		HMODULE hKernel32 = LoadLibrary((LPCSTR)"Kernel32.dll");\r\n
		CreateProcessAFunc pCreateProcessA = (CreateProcessAFunc)GetProcAddress(hKernel32, (LPCSTR)"CreateProcessA");\r\n
		

	);
}

CIntroduce::~CIntroduce()
{
}

void CIntroduce::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, sIntruduce);
}


BEGIN_MESSAGE_MAP(CIntroduce, CDialogEx)
	
END_MESSAGE_MAP()


// CIntroduce 消息处理程序
