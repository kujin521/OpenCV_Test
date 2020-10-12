
// StdManaerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "StdManaer.h"
#include "StdManaerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStdManaerDlg 对话框


/*
	构造函数
*/
CStdManaerDlg::CStdManaerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STDMANAER_DIALOG, pParent)
	, m_name(_T(""))
	, m_gender(0)
	, m_class(_T(""))
	, m_phone(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//手动初始化
	m_count = 0;

}

void CStdManaerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_StudentList, m_stdList);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Radio(pDX, IDC_MALE, m_gender);
	DDX_CBString(pDX, IDC_CLASS, m_class);
	DDX_Text(pDX, IDC_PHONE, m_phone);
	DDX_Control(pDX, IDC_ISLEADER, m_isLeader);
	DDX_Control(pDX, IDC_STDVIEW, m_stdView);
}

BEGIN_MESSAGE_MAP(CStdManaerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CStdManaerDlg::OnBnClickedAdd)
	ON_LBN_SELCHANGE(IDC_StudentList, &CStdManaerDlg::OnLbnSelchangeStudentlist)
END_MESSAGE_MAP()


// CStdManaerDlg 消息处理程序

BOOL CStdManaerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//添加表头
	m_stdView.InsertColumn(0, _T("姓名"), LVCFMT_CENTER, 90);
	m_stdView.InsertColumn(1, _T("性别"), LVCFMT_CENTER, 90);
	m_stdView.InsertColumn(2, _T("班级"), LVCFMT_CENTER, 90);
	m_stdView.InsertColumn(3, _T("手机号"), LVCFMT_CENTER, 150);
	m_stdView.InsertColumn(4, _T("班干部"), LVCFMT_CENTER, 90);
	//显示模式 报告模式
	m_stdView.ModifyStyle(0, LVS_REPORT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStdManaerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStdManaerDlg::OnPaint()
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
HCURSOR CStdManaerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
	点击添加 按钮 事件
*/
void CStdManaerDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_stStudent[m_count].m_Name = m_name;
	if (m_gender == 0) {
		m_stStudent[m_count].m_Gender = "男";
	}
	else {
		m_stStudent[m_count].m_Gender = "女";
	}
	m_stStudent[m_count].m_Class = m_class;
	m_stStudent[m_count].m_Phone = m_phone;
	if (m_isLeader.GetCheck()) {
		m_stStudent[m_count].m_IsLeader = "是";
	}
	else {
		m_stStudent[m_count].m_IsLeader = "否";
	}
	m_stdList.AddString(m_stStudent[m_count].m_Name);
	m_count = (m_count + 1) % 10;
}


void CStdManaerDlg::OnLbnSelchangeStudentlist()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_stdList.GetCurSel();
	m_stdView.DeleteAllItems();
	m_stdView.InsertItem(0, m_stStudent[index].m_Name);
	m_stdView.SetItemText(0, 1, m_stStudent[index].m_Gender);
	m_stdView.SetItemText(0, 2, m_stStudent[index].m_Class);
	m_stdView.SetItemText(0, 3, m_stStudent[index].m_Phone);
	m_stdView.SetItemText(0, 4, m_stStudent[index].m_IsLeader);
}
