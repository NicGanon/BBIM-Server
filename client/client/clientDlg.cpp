// clientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "E:\Program\������\ʵϰ\Program\include\Package.h"
#include "md5.h"
#include "global.h"
#include "printf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
UINT RcvMessage(void *p)
{
	((CclientDlg *)p)->m_RcvMessage();

	return 1;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CclientDlg �Ի���

CclientDlg::CclientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CclientDlg::IDD, pParent)
{
   // 
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_iSeq = 1;
	m_iHeart = 0;
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_REQPHONE, m_edtReqPhoneNum);
    DDX_Control(pDX, IDC_CALLPHONE, m_edtCallPhoneNum); 
    
    DDX_Control(pDX, IDC_SEND, m_btnSend);
    
    DDX_Control(pDX, IDC_IP, m_edtIp);
    DDX_Control(pDX, IDC_PORT, m_edtPort);
    
    DDX_Control(pDX, IDC_CONNET, m_btnConnet);
    DDX_Control(pDX, IDC_BREAK, m_btnBreak);
    
   
    
    DDX_Control(pDX, IDC_USER, m_edtUser);
    DDX_Control(pDX, IDC_PASSWORD, m_edtPassword);
    
    DDX_Control(pDX, IDC_BTNLOGIN, m_btnLogin);
    
}

BEGIN_MESSAGE_MAP(CclientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_CONNET, &CclientDlg::OnBnClickedConnet)
    ON_BN_CLICKED(IDC_BREAK, &CclientDlg::OnBnClickedBreak)
    ON_BN_CLICKED(IDC_SEND, &CclientDlg::OnBnClickedSend)
    ON_BN_CLICKED(IDC_BTNLOGIN, &CclientDlg::OnBnClickedBtnlogin)
//    ON_WM_TIMER()
//ON_WM_TIMER()
ON_WM_TIMER()
END_MESSAGE_MAP()


// CclientDlg ��Ϣ�������

BOOL CclientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_edtIp.SetWindowText("127.0.0.1");
    m_edtPort.SetWindowText("1000");
    m_btnBreak.EnableWindow(false);
    m_btnSend.EnableWindow(false);
    m_btnLogin.EnableWindow(false);
	m_edtIp.SetFocus();
    
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CclientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CclientDlg::OnBnClickedConnet()
{
    SOCKADDR_IN m_SrvAddr;
	m_iFertSocket = socket(AF_INET, SOCK_STREAM, 0);
	memset((void *)&m_SrvAddr, 0, sizeof(SOCKADDR_IN));
	m_SrvAddr.sin_family = AF_INET;
	
	CString ip,port;
	m_edtIp.GetWindowText(ip);
	m_edtPort.GetWindowText(port);
	if(ip.IsEmpty())
	{
	    AfxMessageBox("IP��ַ����Ϊ��");
	    m_edtIp.SetFocus();
	    return;
	}
	if(port.IsEmpty())
	{
	    AfxMessageBox("�˿ڵ�ַ����Ϊ��");
	    m_edtPort.SetFocus();
	    return;
	}
	m_SrvAddr.sin_addr.s_addr =  inet_addr(ip);
	m_SrvAddr.sin_port = htons(atoi(port));

	int ret = connect(m_iFertSocket,(struct sockaddr *)&m_SrvAddr,sizeof(m_SrvAddr));
	if(ret != 0)
	{
		AfxMessageBox("�޷����ӵ�������");
		return;
	}
	//���°�ť״̬
    m_btnConnet.EnableWindow(false);
    m_btnBreak.EnableWindow(true);
    m_btnLogin.EnableWindow(true);
    m_edtUser.SetFocus();
   // SetTimer(1, 10000, NULL);
    AfxBeginThread(RcvMessage, this);
}
void CclientDlg::OnBnClickedBreak()
{  
    
    closesocket(m_iFertSocket);
    m_btnConnet.EnableWindow(true);
    m_btnBreak.EnableWindow(false);
    m_btnSend.EnableWindow(false);
    m_btnLogin.EnableWindow(false);
    m_edtReqPhoneNum.SetWindowText("");
    m_edtCallPhoneNum.SetWindowText("");
    KillTimer(1);
}

void CclientDlg::OnBnClickedSend()
{
    CString csCall;
   
    m_edtCallPhoneNum.GetWindowText(csCall);
    
	
	DEAL head;
	head.function = htonl(PACKAGE_TEL);
	head.compress = 0;
	head.error = htonl(PACKAGE_ERROR);
	
	CTime t = CTime::GetCurrentTime();
    char seq[65];
    sprintf(seq, "                                        %s%010d", t.Format("%Y%m%d%H%M%S"), m_iSeq++);
	strncpy(head.seq, seq, 64);
    
    char xml[1024];
	sprintf(xml, "<?xml version=\"1.0\"encoding=\"UTF8\"?><UniCa><ClickToDialReq><CallPhoneNum>%s</CallPhoneNum></ClickToDialReq></UniCa>",csCall);
    int length = strlen(xml);
    head.bodyLength = htonl(length);
    
    char *pcbody = new char[sizeof(DEAL) + length];
     
	memcpy(pcbody, (char*)&head, sizeof(DEAL));
	memcpy(pcbody+sizeof(DEAL), xml, length);

	int n = send(m_iFertSocket, pcbody,  sizeof(DEAL)+length, 0);
	delete []pcbody;
}

void CclientDlg::m_RcvMessage()
{
	
	while(true)
	{
        DEAL head;//���ձ���ͷ
		int rcv =recv(m_iFertSocket, (char*)&head, sizeof(DEAL), 0);
		//ע���п���һ�β��ܽ��յ������İ�...
		if(rcv <= 0)//�������״̬...
		{
		    AfxMessageBox("�����жϣ�����������");
		    OnBnClickedBreak();
		    return;
		}
		//LOGString(stdout,"SS-MAINFRM","",1,1,"%s","��������");
		char *buf = NULL;
		int bodylength = ntohl(head.bodyLength);
		if(bodylength > 0)
		{
			buf = new char[bodylength];
			rcv = 0;
			int length = bodylength;
		    while(true)//ע���п���һ�β��ܽ��յ������İ�...
		    {
		        rcv = recv(m_iFertSocket, buf + (bodylength - length), length, 0);
    		    
		        length -= rcv;
		        if(length <= 0)
		        {   
			        break;
		        }
		    }//end while(true)
		    if(rcv <= 0)
		    {
		        if(buf != NULL)
		        {
		            delete []buf;
			        buf = NULL;
			    }
		        AfxMessageBox("�����жϣ�����������");
		        OnBnClickedBreak();
		        return;
		    }
		}// end if(head.bodyLength > 0)

		if(ntohl(head.error) != PACKAGE_ERROR)//�ж��Ƿ��Ǵ���
		{
			AfxMessageBox(head.desError);//��ʾ�û�����...
			continue;
		}
        
		int function = ntohl(head.function);
		
		switch(function)
		{
		     case PACKAGE_LOGIN_RESP://�����¼
			        m_btnSend.EnableWindow(true); //��¼�ɹ����ð�ť״̬
		            m_btnLogin.EnableWindow(false);
			    break;
		     case PACKAGE_TEL_RESP://����ͨ��
				 m_ProMessage(buf);
			    break;
		     case PACKAGE_HEART_RESP:
		            m_iHeart = 0;
		            break;
		    default:
			    break;
		}// end switch
		
	}//end �����while��true��
}

void CclientDlg::OnBnClickedBtnlogin()
{
   CString user,password;
   m_edtUser.GetWindowText(user);
   m_edtPassword.GetWindowText(password);
   if(user.IsEmpty())
    {
        AfxMessageBox("�û�������Ϊ��");
        m_edtUser.SetFocus();
        return;
    }
    if(password.IsEmpty())
    {
        AfxMessageBox("���벻��Ϊ��");
        m_edtPassword.SetFocus();
        return;
    }
    
    
    char pass[128];
    sprintf(pass,password,password.GetLength());
    pass[password.GetLength()] = 0;
    
    MD5_CTX md5;
    MD5Init(&md5);
    MD5Update(&md5, (unsigned char* )pass, strlen(pass));
    unsigned char md5Pass[16];
    MD5Final(md5Pass, &md5);
   
    char dest[33];
    bin2hexstr(md5Pass,16,dest);
    dest[32]='\0';
   
    DEAL head;
    head.compress = 0;
    head.function = htonl(PACKAGE_LOGIN);
    head.error = htonl(PACKAGE_ERROR);
    CTime t = CTime::GetCurrentTime();
    char seq[65];
    sprintf(seq, "                                        %s%010d", t.Format("%Y%m%d%H%M%S"), m_iSeq++);
	strncpy(head.seq, seq, 64);
   
    char xml[1024];
	sprintf(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><UniCa><AuthReq><productSpec>1</productSpec><account>%s</account><password>%s</password><loginType>2</loginType><clientType>10</clientType><phoneType>1234</phoneType><version>1</version></AuthReq></UniCa>",
		user, dest);
    int length = strlen(xml);
    head.bodyLength = htonl(length);
    
    char *body = new char[sizeof(DEAL)+ length];
	memcpy(body, (char*)&head, sizeof(DEAL));
	memcpy(body+sizeof(DEAL), xml, length );
    int nbody = strlen(body);						
	int n = send(m_iFertSocket, body, sizeof(DEAL)+length, 0);	
	if(body == NULL)
	{
	    delete []body;
	    body = NULL;
	}
}

int CclientDlg::bin2hexstr(unsigned char *src, int len, char *dst)
{
	int i;
	for(i=0; i<len; i++)
	sprintf(&dst[i*2], "%02x", src[i]&0x00ff);

	return i*2;
}


void CclientDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(m_iHeart > 3)
    {  
        AfxMessageBox("�����жϣ�����������");
        OnBnClickedBreak();
        return;
    }
    m_iHeart += 1;
    DEAL heart;
    heart.compress = 0;
    heart.error = htonl(PACKAGE_ERROR);
    heart.function = htonl(PACKAGE_HEART);
    heart.bodyLength = 0;
    CTime t = CTime::GetCurrentTime();
    char seq[65];
    sprintf(seq, "                                        %s%010d", t.Format("%Y%m%d%H%M%S"), m_iHeart);
	strncpy(heart.seq, seq, 64);
    
    char *buf = new char[sizeof(DEAL)];
     
	memcpy(buf, (char*)&heart, sizeof(DEAL));
    send(m_iFertSocket, buf, sizeof(DEAL), 0);
    
    CDialog::OnTimer(nIDEvent);
}

void CclientDlg::m_ProMessage(const char *body)
{
	//LOGString(stdout,"SS-MAINFRM","",1,1,"%s","��������");
    const char *p = body;
	
	char *messStartNode = "<CallPhoneNum>";
	char *messEndNode = "</CallPhoneNum>";
    
   
	const char *messStart = strstr(p, messStartNode);
	const char *messEnd   = strstr(p, messEndNode);
	int iMesslength = messEnd-messStart-strlen(messStartNode);
	char *pcMess = new char[iMesslength+1];
	
	//�ҵ�������
	if(messStart != NULL && messEnd!=NULL)
	{
		strncpy(pcMess, messStart + strlen(messStartNode), iMesslength);
		pcMess[iMesslength] = 0;
    }
	//LOGString(stdout,"SS-MAINFRM","",1,1,"%s",pcMess);
	
	CString tmp(pcMess);
	m_csRecord += "\r\n";
	m_csRecord +=tmp;
	m_edtReqPhoneNum.SetWindowText(m_csRecord);
	
}