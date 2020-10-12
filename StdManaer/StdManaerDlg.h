
// StdManaerDlg.h: 头文件
//

#pragma once
using namespace std;
//定义结构体
typedef struct tag_Student 
{
	CString m_Name;
	CString m_Gender;
	CString m_Class;
	CString m_Phone;
	CString m_IsLeader;
	//Student 别名
}Student;

// CStdManaerDlg 对话框
class CStdManaerDlg : public CDialogEx
{
// 构造
public:
	CStdManaerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STDMANAER_DIALOG };
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
	//定义结构体数组
	Student m_stStudent[10];
	int m_count;

	CListBox m_stdList;
	CString m_name;
	int m_gender;
	CString m_class;
	CString m_phone;
	CButton m_isLeader;
	CListCtrl m_stdView;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnLbnSelchangeStudentlist();
};
