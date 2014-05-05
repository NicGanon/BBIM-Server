// serverDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "E:\Program\大三下\Network\Program\include\Package.h"
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CserverDlg 对话框




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


// CserverDlg 消息处理程序

BOOL CserverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_lstMember.InsertColumn(0, "客户端", LVCFMT_LEFT, 200 );
	m_lstMember.InsertColumn(1, "socket", LVCFMT_LEFT, 200 );
	m_line = NULL;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CserverDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	//绑定
	bind(m_ServerSocket, (struct sockaddr *)&m_rcvaddr, sizeof(SOCKADDR_IN));
	 
	m_btnConnet.EnableWindow(false);
    
   
	//监听
	listen(m_ServerSocket, 5);
	
	AfxBeginThread(ListenThread,this);
}

void CserverDlg::m_ListenThread()
{   
    while(true)
    {
        //客户端
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
		m_lstMember.InsertItem(count, pSock ,0);		//客户端
		
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
		//接收数据
		DEAL head;
		int rxn = recv(sock, (char*)&head, sizeof(DEAL),0);
		
        if(rxn <=0 )//处理断开的事件...
	    {
			    m_BreakConnet(sock);
			    break;
		 }
		int bodylength = ntohl(head.bodyLength);
		char *body = NULL;
		if(bodylength > 0)
		{
			body = new char[bodylength]; 
		    rxn = 0;//每次接受的长度
		    int length = bodylength;
		    while(TRUE)
		    {
			    rxn = recv(sock, body +(bodylength - length), length, 0);
                if(rxn <= 0)//处理网络断开...，注意内存的释放
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
		
		if(ntohl(head.error) != PACKAGE_ERROR)//处理错误...
		{
		   LOGString(stdout,"SS-MAINFRM","",1,1,"%s",head.desError);
		   continue;
		}
		
		int result,num,length;
		ptr_sock tmp = m_line;
		char *newbody = NULL;
		//处理
		int function = ntohl(head.function);
		switch(function)
		{
		case PACKAGE_LOGIN://登录
			result = m_ProLogin(body);
			m_RetLoginStatus(sock, result);//告诉客户端...
			break;
		case PACKAGE_TEL://通信
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
	}//end 最外层while（true）
}

void CserverDlg::m_RetHeart(int sock)
{
    DEAL head;
    
    head.compress = 0;
    head.function = htonl(PACKAGE_HEART_RESP);
    //流水号
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
	
	//用户名节点
	char *userStartNode = "<account>";
	char *userEndNode = "</account>";

	//找用户名
    const char *userStart = strstr(p, userStartNode);
	const char *userEnd   = strstr(p, userEndNode);
	int iUserlength = (userEnd-userStart)-strlen(userStartNode);
	char *pcUser = new char[iUserlength+1];
	
	//找到的条件
	if(userStart != NULL && userEnd!=NULL)
	{
		strncpy(pcUser, userStart+strlen(userStartNode), iUserlength);
		pcUser[iUserlength] = 0;
    }
    //LOGString(stdout,"SS-MAINFRM","",1,1,"%s",pcUser);
	
	//密码节点名
	char *passStartNode = "<password>";
	char *passEndNode = "</password>";
    
    //找密码
	const char *passStart = strstr(p, passStartNode);
	const char *passEnd   = strstr(p, passEndNode);
	int iPasslength = passEnd-passStart-strlen(passStartNode);
	char *pcPass = new char[iPasslength+1];
	
	//找到的条件
	if(passStart != NULL && passEnd!=NULL)
	{
		strncpy(pcPass, passStart + strlen(passStartNode), iPasslength);
		pcPass[iPasslength] = 0;
    }
	LOGString(stdout,"SS-MAINFRM","",1,1,"%s",pcPass);
	
	int result;
	if(strcmp(pcUser,"admin") == 0 ) //返回是否登录成功
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
	
	//释放空间
	delete []pcUser;
	delete []pcPass;
	
	return result;

}

void CserverDlg::m_RetLoginStatus(const int sock, const int result)
{
    DEAL head;
    
    head.compress = 0;
    head.function = htonl(PACKAGE_LOGIN_RESP);
    //流水号
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
             //组织报文体
	        sprintf(xml, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><UniCa><AuthRsp><productId>2a1f8d8d22bf4a0d031a</productId><authAddress>133.224.6.100</authAddress><authType>10</authType><authDate>2012-02-05 20:25:02</authDate><versionNum>1</versionNum><address>1</address></AuthRsp></UniCa>");
            //计算长度
	        length = strlen(xml);
	        head.bodyLength = htonl(length);
	        body = new char[sizeof(DEAL)+ length];
	        memcpy(body, (char*)&head, sizeof(DEAL));
     	    memcpy(body+sizeof(DEAL), xml, length );
     	    n = send(sock, body,  sizeof(DEAL)+length, 0);
            if(n<=0)
            {   
                AfxMessageBox("连接已断开");
            }
            break;
        case 1:
            head.error = htonl(PACKAGE_PASSWORD_ERROR);
            strcpy(head.desError , "密码错误");
            head.bodyLength = 0;
            body = new char[sizeof(DEAL)];
            memcpy(body, (char*)&head, sizeof(DEAL));
            send(sock, body,  sizeof(DEAL)+head.bodyLength, 0);
            break;
         case 2:
            head.error = htonl(PACKAGE_USER_ERROR);
            strcpy(head.desError , "用户名不存在");
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
    //流水号
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