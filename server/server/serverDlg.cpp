// serverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "E:\Program\������\Network\Program\include\Package.h"
#include "printf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct _tagCOMMUNICATION_
{
    CserverDlg* pWnd;
    int sock;
}COMMUNICATION, *LPCOMMUNICATION;

UINT ListenThread(LPVOID p)
{
    ((CserverDlg *)p)->m_ListenThread();
    
    return 1;
}

UINT ProCommunication(LPVOID p)
{
    LPCOMMUNICATION com = (LPCOMMUNICATION)p;
    com->pWnd->m_Communication(com->sock);
    
    return 1;
}
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CserverDlg �Ի���




CserverDlg::CserverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CserverDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iSeq = 0;
}

void CserverDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
   
    DDX_Control(pDX, IDC_CONNET, m_btnConnet);
    //DDX_Control(pDX, IDC_SEND, m_btnSend);
    DDX_Control(pDX, IDC_LSTMEMBER, m_lstMember);
}

BEGIN_MESSAGE_MAP(CserverDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    //ON_BN_CLICKED(IDC_SEND, &CserverDlg::OnBnClickedSend)
    ON_BN_CLICKED(IDC_CONNET, &CserverDlg::OnBnClickedConnet)
END_MESSAGE_MAP()


// CserverDlg ��Ϣ�������

BOOL CserverDlg::OnInitDialog()
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
	m_lstMember.InsertColumn(0, "�ͻ���", LVCFMT_LEFT, 200 );
	m_lstMember.InsertColumn(1, "socket", LVCFMT_LEFT, 200 );
	m_line = NULL;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CserverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CserverDlg::OnPaint()
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
HCURSOR CserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CserverDlg::OnBnClickedConnet()
{
   
    m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN m_rcvaddr;
	memset((void *)&m_rcvaddr, 0, sizeof(SOCKADDR_IN));
	m_rcvaddr.sin_family = AF_INET;
	m_rcvaddr.sin_addr.s_addr =  inet_addr("0.0.0.0");
	m_rcvaddr.sin_port = htons(1000);

	//��
	bind(m_ServerSocket, (struct sockaddr *)&m_rcvaddr, sizeof(SOCKADDR_IN));
	 
	m_btnConnet.EnableWindow(false);
    
   
	//����
	listen(m_ServerSocket, 5);
	
	AfxBeginThread(ListenThread,this);
}

void CserverDlg::m_ListenThread()
{   
    while(true)
    {
        //�ͻ���
	    SOCKET cmdsrv  = (int)accept(m_ServerSocket,NULL,NULL);
		if(cmdsrv == INVALID_SOCKET)
	    {
		    int err=GetLastError();
		    return;
	    }
		ptr_sock tmp = new sock;
		tmp->socket = cmdsrv;
		tmp->next = NULL;
		if(!m_line)
		{
			m_line = tmp;
		}
		else
		{
			tmp->next = m_line;
			m_line = tmp;
		}
	    
	    

	    int count = m_lstMember.GetItemCount();
		char pSock[32];
		sprintf(pSock, "%d", count);
		m_lstMember.InsertItem(count, pSock ,0);		//�ͻ���
		
		sprintf(pSock, "%d", cmdsrv);
		m_lstMember.SetItemText(count, 1, pSock);			//socket
		
		COMMUNICATION com;
		com.pWnd = this;
		com.sock = cmdsrv;
		AfxBeginThread(ProCommunication, &com);
	}  
}

void CserverDlg::m_Communication(int sock)
{
    while(true)
	{
		//��������
		DEAL head;
		int rxn = recv(sock, (char*)&head, sizeof(DEAL),0);
		
        if(rxn <=0 )//����Ͽ����¼�...
	    {
			    m_BreakConnet(sock);
			    break;
		 }
		int bodylength = ntohl(head.bodyLength);
		char *body = NULL;
		if(bodylength > 0)
		{
			body = new char[bodylength]; 
		    rxn = 0;//ÿ�ν��ܵĳ���
		    int length = bodylength;
		    while(TRUE)
		    {
			    rxn = recv(sock, body +(bodylength - length), length, 0);
                if(rxn <= 0)//��������Ͽ�...��ע���ڴ���ͷ�
                {
                    if(body != NULL)
                    {
                        delete []body;
                        body = NULL;
                    }
                    m_BreakConnet(sock);
                    return;
                }
			    length -= rxn;

			    if(length <= 0)
			    {
			        break;
			    }
		    }
		}//end if(length > 0)
		
		if(ntohl(head.error) != PACKAGE_ERROR)//�������...
		{
		   LOGString(stdout,"SS-MAINFRM","",1,1,"%s",head.desError);
		   continue;
		}
		
		int result,num,length;
		ptr_sock tmp = m_line;
		char *newbody = NULL;
		//����
		int function = ntohl(head.function);
		switch(function)
		{
		case PACKAGE_LOGIN://��¼
			result = m_ProLogin(body);
			m_RetLoginStatus(sock, result);//���߿ͻ���...
			break;
		case PACKAGE_TEL://ͨ��
			m_RetReqTel(sock,body);
			break;
	    case PACKAGE_HEART:
	        m_RetHeart(sock);
	        break;
	    default:
	        break;
		}

		if(body != NULL) 
		{
			delete[]body;
			body = NULL;
		}  
	}//end �����while��true��
}

void CserverDlg::m_RetHeart(int sock)
{
    DEAL head;
    
    head.compress = 0;
    head.function = htonl(PACKAGE_HEART_RESP);
    //��ˮ��
	CTime tm = CTime::GetCurrentTime();
	char seq[65];
	sprintf(seq, "                                        %s%010d", tm.Format("%Y%m%d%H%M%S"), m_iSeq++);
	strncpy(head.seq, seq, 64);
	head.bodyLength = 0;
	head.error = htonl(PACKAGE_ERROR);
    char* body = new char[sizeof(DEAL)];
	memcpy(body, (char*)&head, sizeof(DEAL));
    int n = send(sock, body,  sizeof(DEAL), 0);
    if(body != NULL)
    {
        delete []body;
        body = NULL;
    }
}

int CserverDlg::m_ProLogin(const char *body)
{
    const char *p = body;
	
	//�û����ڵ�
	char *userStartNode = "<account>";
	char *userEndNode = "</account>";

	//���û���
    const char *userStart = strstr(p, userStartNode);
	const char *userEnd   = strstr(p, userEndNode);
	int iUserlength = (userEnd-userStart)-strlen(userStartNode);
	char *pcUser = new char[iUserlength+1];
	
	//�ҵ�������
	if(userStart != NULL && userEnd!=NULL)
	{
		strncpy(pcUser, userStart+strlen(userStartNode), iUserlength);
		pcUser[iUserlength] = 0;
    }
    //LOGString(stdout,"SS-MAINFRM","",1,1,"%s",pcUser);
	
	//����ڵ���
	char *passStartNode = "<password>";
	char *passEndNode = "</password>";
    
    //������
	const char *passStart = strstr(p, passStartNode);
	const char *passEnd   = strstr(p, passEndNode);
	int iPasslength = passEnd-passStart-strlen(passStartNode);
	char *pcPass = new char[iPasslength+1];
	
	//�ҵ�������
	if(passStart != NULL && passEnd!=NULL)
	{
		strncpy(pcPass, passStart + strlen(passStartNode), iPasslength);
		pcPass[iPasslength] = 0;
    }
	LOGString(stdout,"SS-MAINFRM","",1,1,"%s",pcPass);
	
	int result;
	if(strcmp(pcUser,"admin") == 0 ) //�����Ƿ��¼�ɹ�
	{
	    if(strcmp(pcPass,"e10adc3949ba59abbe56e057f20f883e") == 0)
	        result = 0;
	    else
	        result = 1;
	}
	else
	{
	    result = 2;
	}
	
	//�ͷſռ�
	delete []pcUser;
	delete []pcPass;
	
	return result;

}

void CserverDlg::m_RetLoginStatus(const int sock, const int result)
{
    DEAL head;
    
    head.compress = 0;
    head.function = htonl(PACKAGE_LOGIN_RESP);
    //��ˮ��
	CTime tm = CTime::GetCurrentTime();
	char seq[65];
	sprintf(seq, "                                        %s%010d", tm.Format("%Y%m%d%H%M%S"), m_iSeq++);
	strncpy(head.seq, seq, 64);
	
	char xml[1024];
	char *body = NULL;
	int length;
	int n;
	switch(result)
    {    
        case 0:
            head.error = htonl(PACKAGE_ERROR);
             //��֯������
	        sprintf(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><UniCa><AuthRsp><productId>2a1f8d8d22bf4a0d031a</productId><authAddress>133.224.6.100</authAddress><authType>10</authType><authDate>2012-02-05 20:25:02</authDate><versionNum>1</versionNum><address>1</address></AuthRsp></UniCa>");
            //���㳤��
	        length = strlen(xml);
	        head.bodyLength = htonl(length);
	        body = new char[sizeof(DEAL)+ length];
	        memcpy(body, (char*)&head, sizeof(DEAL));
     	    memcpy(body+sizeof(DEAL), xml, length );
     	    n = send(sock, body,  sizeof(DEAL)+length, 0);
            if(n<=0)
            {   
                AfxMessageBox("�����ѶϿ�");
            }
            break;
        case 1:
            head.error = htonl(PACKAGE_PASSWORD_ERROR);
            strcpy(head.desError , "�������");
            head.bodyLength = 0;
            body = new char[sizeof(DEAL)];
            memcpy(body, (char*)&head, sizeof(DEAL));
            send(sock, body,  sizeof(DEAL)+head.bodyLength, 0);
            break;
         case 2:
            head.error = htonl(PACKAGE_USER_ERROR);
            strcpy(head.desError , "�û���������");
            head.bodyLength = 0;
            body = new char[sizeof(DEAL)];
            memcpy(body, (char*)&head, sizeof(DEAL));
            send(sock, body,  sizeof(DEAL)+head.bodyLength, 0);
            break;
         default:
            break;
    }
} 

void CserverDlg::m_RetReqTel(int id,char body[])
{
    DEAL head;
    
    head.compress = 0;
    head.function = htonl(PACKAGE_TEL_RESP);
    //��ˮ��
	CTime tm = CTime::GetCurrentTime();
	char seq[65];
	sprintf(seq, "                                        %s%010d", tm.Format("%Y%m%d%H%M%S"), m_iSeq++);
	strncpy(head.seq, seq, 64);
    head.error = htonl(PACKAGE_ERROR);
	 
	int length = strlen(body);
	head.bodyLength = htonl(length);
    char *newbody = new char[sizeof(DEAL)+length];
   
    memcpy(newbody, (char*)&head, sizeof(DEAL));
	memcpy(newbody+sizeof(DEAL), body, length );
	
	ptr_sock tmp = m_line;
	while(tmp)
	{
		int num = send(tmp->socket, newbody,sizeof(DEAL)+length, 0);
		
		tmp = tmp->next;
	}
       
}

void CserverDlg::m_BreakConnet(int sock)
{
    int count = m_lstMember.GetItemCount();
	for(int i=0; i<count; i++)    
	{   
		CString csSock = m_lstMember.GetItemText(i, 1);
	    int iSock = atoi(csSock);
		if(iSock == sock)		     
		{
		    m_lstMember.DeleteItem(i);
     	    break;
	     }   		    	 
	 }		    
}