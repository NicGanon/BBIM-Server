// clientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CclientDlg 对话框
class CclientDlg : public CDialog
{
// 构造
public:
	CclientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENT_DIALOG };

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
    afx_msg void OnBnClickedBreak();
    afx_msg void OnBnClickedSend();
    
    
    CEdit m_edtIp;
    CEdit m_edtPort;
    CEdit m_edtUser;
    CEdit m_edtPassword;
    CEdit m_edtReqPhoneNum;
    CEdit m_edtCallPhoneNum;
    
    int m_iFertSocket;
    void m_RcvMessage();
    bool m_CheckPhone(CString Rec, CString Call);
    int bin2hexstr(unsigned char *src, int len, char *dst);
   
    int m_iSeq;
    int m_iHeart;
    
    CButton m_btnConnet;
    CButton m_btnBreak;
    CButton m_btnLogin;
    CButton m_btnSend;
    
    CString m_csRecord;
    afx_msg void OnBnClickedBtnlogin();
     
    afx_msg void OnTimer(UINT_PTR nIDEvent);
	void m_ProMessage(const char *body);
};
