// serverDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

typedef struct sock
{
	int socket;
	struct sock* next;
}sock,*ptr_sock;


// CserverDlg �Ի���
class CserverDlg : public CDialog
{
// ����
public:
	CserverDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
