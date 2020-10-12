
// Demo2Dlg.h: 头文件
//
#include<opencv2/highgui/highgui_c.h>
#pragma once

using namespace cv;


// CDemo2Dlg 对话框
class CDemo2Dlg : public CDialogEx
{
// 构造
public:
	CDemo2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMO2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Mat src;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnDoubleclickedButton1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedVidio();
	afx_msg void OnBnClickedResize();
	int m_width;
	int m_height;
	double m_angle;
	afx_msg void OnBnClickedRotatek();
};
