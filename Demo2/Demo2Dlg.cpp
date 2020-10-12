
// Demo2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Demo2.h"
#include "Demo2Dlg.h"
#include "afxdialogex.h"

#include<openCV2/core/core.hpp>
#include<openCV2/highgui/highgui.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;


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
	DECLARE_MESSAGE_MAP(CDemo2Dlg::CDemo2Dlg)
public:
	
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


// CDemo2Dlg 对话框



CDemo2Dlg::CDemo2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMO2_DIALOG, pParent)
	, m_width(0)
	, m_height(0)
	, m_angle(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemo2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_width);
	DDX_Text(pDX, IDC_EDIT3, m_height);
	DDX_Text(pDX, IDC_EDIT4, m_angle);
}

BEGIN_MESSAGE_MAP(CDemo2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDemo2Dlg::OnBnClickedOk)
	ON_BN_DOUBLECLICKED(IDC_BUTTON1, &CDemo2Dlg::OnBnDoubleclickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDemo2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_VIDIO, &CDemo2Dlg::OnBnClickedVidio)
	ON_BN_CLICKED(IDC_RESIZE, &CDemo2Dlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_ROTATEK, &CDemo2Dlg::OnBnClickedRotatek)
END_MESSAGE_MAP()


// CDemo2Dlg 消息处理程序

BOOL CDemo2Dlg::OnInitDialog()
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

	Mat view = imread("a.jpg");

	namedWindow("view");

	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);

	::SetParent(hWnd, GetDlgItem(IDC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDemo2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemo2Dlg::OnPaint()
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
HCURSOR CDemo2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemo2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDemo2Dlg::OnBnDoubleclickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDemo2Dlg::OnBnClickedButton1()
{
	// 点击open 打开图片事件

	//CFileDialog类封装了Windows常用的文件对话框，提供了文件打开和文件存盘对话框功能。可以用其构造函数创建打开图片或视频的对话框；
	CFileDialog dlg(TRUE, _T("*.jpg"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("Image files(*.bmp,*.jpg)|*.bmp;*.jpg|All files(*.*)|*.*|"), NULL);


	dlg.m_ofn.lpstrTitle = _T("Open Images");

	if (dlg.DoModal() != IDOK) {
		return;
	}

	//获取路径
	CString filePath = dlg.GetPathName();

	//将路径转换字符类型
	string sFileName=(LPCTSTR) filePath;

	//Imread（）函数用来图像的读取
	src = imread(sFileName);

	//如果 内容为空
	if (src.empty())
	{
		AfxMessageBox(_T("图像读取错误! "));
		return;
	}
	else {
		CRect rect;
		//图片控件绑定
		GetDlgItem(IDC_PIC)->GetClientRect(&rect);
		Mat img;

		//图片缩放 到正常大小
		resize(src, img, Size(rect.Width(), rect.Height()));

		//显示图片
		imshow("view", img);
	}
}


void CDemo2Dlg::OnBnClickedVidio()
{
	// 打开视频事件

	/*CFileDialog dlg(TRUE, _T("*.avi"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("Vidio files(*.avi)|*.avi|All files(*.*)|*.*|"), NULL);


	dlg.m_ofn.lpstrTitle = _T("Open Vido");

	if (dlg.DoModal() != IDOK) {
		return;
	}

	CString filePath = dlg.GetPathName();

	string sFileName = (LPCTSTR)filePath;*/

	VideoCapture capture;

	//int re=capture.open(sFileName);

	//打开摄像头
	//int re = capture.open(0);

	//打开网络源 cctv5
	int re = capture.open("http://ivi.bupt.edu.cn/hls/hunanhd.m3u8");

	if (!re) {
		AfxMessageBox("Can not open Video!");
		return;
	}

	CRect rect;

	GetDlgItem(IDC_PIC)->GetClientRect(&rect);

	Mat img;
	Mat frame;

	while(1) {

		capture >> frame;

		if (frame.empty())
		{
			//AfxMessageBox(_T("视频读取错误! "));
			return;
		}
		else {
			resize(frame, img, Size(rect.Width(), rect.Height()));

			imshow("view", img);

			waitKey(30);
		}

		
	}

}


void CDemo2Dlg::OnBnClickedResize()
{
	// 缩放按钮 响应函数
	UpdateData(TRUE);

	Mat dst;

	resize(src,dst, Size(m_width, m_height));

	imshow("resize", dst);
}

void CDemo2Dlg::OnBnClickedRotatek()
{
	// 旋转
	UpdateData(TRUE);

	Mat rot_mat(2, 3, CV_32FC1); //旋转矩阵
	Mat dst;

	//计算旋转之后的画布大小
	double sin_value = sin(m_angle * CV_PI / 180);
	double cos_value = cos(m_angle * CV_PI / 180);

	int width = src.cols;
	int height = src.rows;

	int rorate_width = (int)(height * fabs(sin_value) + width * fabs(cos_value));
	int rorate_height = (int)(width * fabs(sin_value) + height * fabs(cos_value));

	//计算旋转矩阵
	Point center = Point(src.cols / 2, src.rows / 2);
	double angle = m_angle;
	double scale = 1;

	rot_mat = getRotationMatrix2D(center, angle, scale);

	//计算平移量
	rot_mat.at<double>(0, 2) += (rorate_width - width) / 2;
	rot_mat.at<double>(1, 2) += (rorate_height - height) / 2;

	//利用仿射变换 进行旋转
	warpAffine(src, dst, rot_mat, Size(rorate_width, rorate_height));

	imshow("rotate", dst);
}
