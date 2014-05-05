// serverDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

typedef struct sock
{
	int socket;
	struct sock* next;
}sock,*ptr_sock;


// CserverDlg 对话框
class CserverDlg : public CDialog
{
// 构造
public:
	CserverDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SERVER_DIALOG };

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
    afx_msg void OnBnClickedConnet();
    
    
   void m_ListenThread();
   void m_Communication(int sock);
   void m_BreakConnet(int sock);
   int m_ProLogin(const char *body);
   void m_RetLoginStatus(const int sock, const int result);
   
   void m_RetReqTel(char body[]);
   void m_RetHeart(int sock);
    int m_ServerSocket;
    
    CButton m_btnConnet;
	
    
    CListCtrl m_lstMember;
    int m_iSeq;

	ptr_sock m_line;
};
