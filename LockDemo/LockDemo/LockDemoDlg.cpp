
// LockDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LockDemo.h"
#include "LockDemoDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <iostream>
#include "usb.h"
#include<opencv2\opencv.hpp>
#include "pic_deal.h"
#include "def.h"
#include "packet.h"
#include <math.h>
#include<fstream>
#include <algorithm>

#define TIMER_PROG 9527



#define SEL_REGISTER	0x0
#define SEL_RECOGNISE	0x1


using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLockDemoDlg �Ի���



CLockDemoDlg::CLockDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLockDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LOCK_ICON);
}

void CLockDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, m_comboDeal);
}

BEGIN_MESSAGE_MAP(CLockDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DEAL, &CLockDemoDlg::OnBnClickedDeal)
	ON_BN_CLICKED(IDC_SELECTDIR, &CLockDemoDlg::OnBnClickedSelectdir)
	ON_BN_CLICKED(IDOK, &CLockDemoDlg::OnBnClickedOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS, &CLockDemoDlg::OnNMCustomdrawProgress1)
	ON_EN_CHANGE(IDC_SELECTPATH, &CLockDemoDlg::OnEnChangeSelectpath)
//	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CLockDemoDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO3, &CLockDemoDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_EXIT, &CLockDemoDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_SAVETO, &CLockDemoDlg::OnBnClickedSaveto)
//	ON_WM_CLOSE()
ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLockDemoDlg ��Ϣ�������

BOOL CLockDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	CProgressCtrl* prog = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
	prog->SetRange(0, 100);

	m_comboDeal.AddString(_T("Register"));
	m_comboDeal.AddString(_T("Recognise"));
	m_comboDeal.SetCurSel(0);
	((CButton*)GetDlgItem(IDC_SAVETO))->EnableWindow(FALSE);//���ð�ť

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CLockDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLockDemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLockDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CLockDemoDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



void CLockDemoDlg::OnBnClickedSelectdir()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int low, high;															/*clear Progress bar*/
	CProgressCtrl * prog;
	prog = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);
	prog->GetRange(low, high);
	prog->SetPos(low);

	CString des;
	CFolderPickerDialog fd(NULL, 0, this, 0);
	if (fd.DoModal() == IDOK)
	{

		des = fd.GetPathName();
		SetDlgItemText(IDC_SELECTPATH, des);
	}
	else
	{
		return;
	}
}

void get_filename(CString& path, CString& filename)
{
	int nPos = path.Find('\\');															/* get filename from file path */
	filename = path;
	while (nPos) {
		filename = filename.Mid(nPos + 1, filename.GetLength() - nPos);  //ȡ'\'�ұ��ַ���
		nPos = filename.Find('\\');   //������'\'������ֵ����-1
		if (nPos == -1)
		{
			nPos = 0;
		}
	}

	return;
}

bool id_cmp(CString s1, CString s2)
{
	CString subStr = s1;
	get_filename(s1, subStr);

	int s1_startPos = subStr.Find(_T("_"));
	int s1_endPos = subStr.Find(_T("."));
	CString s1_strID = subStr.Mid(s1_startPos + 1, s1_endPos - s1_startPos - 1);
	string s1_ID = static_cast<CStringA>(s1_strID);
	int s1_iID = atoi(s1_ID.c_str());

	get_filename(s2, subStr);
	int s2_startPos = subStr.Find(_T("_"));
	int s2_endPos = subStr.Find(_T("."));
	CString s2_strID = subStr.Mid(s2_startPos + 1, s2_endPos - s2_startPos - 1);
	string s2_ID = static_cast<CStringA>(s2_strID);
	int s2_iID = atoi(s2_ID.c_str());

	return s1_iID < s2_iID;
}




void CLockDemoDlg::OnBnClickedDeal()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������		
	uint8_t recv_buf[BUF_RECV_SPACE] = { 0 };
	uint8_t send_buf[PIC_WIDTH * PIC_HEIGHT * PIC_CHANNELS + BUF_RESERVE_SPACE] = { 0 };			/* packet buffer */

	int prog_min, prog_max;
	CProgressCtrl * prog;
	prog = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS);												/* get process bar info */
	prog->GetRange(prog_min, prog_max);

	if (usb_initial() < 0) {
		AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		return;
	}

	CFile logfile;																					/* log file */
	char log[BUF_RESERVE_SPACE];
	if (!logfile.Open(_T("lockdemo.log"), CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox(_T("Can't open the log file!"), MB_ICONSTOP);
		return;
	}
																				
	CFile result;																					/* recognition result file */
	char result_output[BUF_RESERVE_SPACE];
	int nSel = m_comboDeal.GetCurSel();
	if (SEL_RECOGNISE == nSel) {
		CString ResultFileName;
		GetDlgItemText(IDC_SAVEPATH, ResultFileName);
		if (!result.Open(ResultFileName, CFile::modeCreate | CFile::modeWrite)) {
			AfxMessageBox(_T("Can't open the result file!"), MB_ICONSTOP);
			logfile.Close();
			return;
		}
		sprintf_s(result_output, "������Ƭ,��ߵ÷���Ƭ,�ȶԵ÷�\n");
		result.Write(result_output, strlen(result_output));
	}

	CString des;
	vector<CString> m_FileList;																		/* get all picture's pathname in the directory */
	CFileFind finder;
	GetDlgItemText(IDC_SELECTPATH, des);
	// build a string with wildcards
	des += _T("\\*.jpg");

	// start working for files
	uint32_t pic_cnt = 0;
	BOOL bWorking = finder.FindFile(des);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		// skip . and .. files; otherwise, we'd
		// recur infinitely!
		if (finder.IsDots())
			continue;
		// if it's a directory, recursively search it
		CString str = finder.GetFilePath();
		//if (0 == str.Right(3).CompareNoCase(_T("jpg")))
		//TRACE(_T("%s\n"), (LPCTSTR)str);
		m_FileList.push_back(str);
		pic_cnt++;
	}
	finder.Close();
#ifdef SORT_DEBUG
	for (auto it = m_FileList.begin(); it != m_FileList.end(); ++it) {
		MessageBox(*it);
	}
#endif
	sort(m_FileList.begin(), m_FileList.end(), id_cmp);												/* sort picture's pathname by ID */
#ifdef SORT_DEBUG
	for (auto it = m_FileList.begin(); it != m_FileList.end(); ++it) {
		MessageBox(*it);
	}
#endif

#ifdef TIME_DEBUG
	///////////////////////////////////Time test///////////////////////
	LARGE_INTEGER timeStart;    //��ʼʱ��  
	LARGE_INTEGER timeEnd;      //����ʱ��  
	double elapsed;
	CString s;
	LARGE_INTEGER frequency;    //��ʱ��Ƶ��  
	QueryPerformanceFrequency(&frequency);
	double quadpart = (double)frequency.QuadPart;//��ʱ��Ƶ��  

	QueryPerformanceCounter(&timeStart);
	///////////////////////////////////Time test///////////////////////
#endif
	uint32_t err_cnt = 0;
	uint32_t deal_cnt = 0;
	for (auto it = m_FileList.begin(); it != m_FileList.end(); ++it) {	
		USES_CONVERSION;		
		uint8_t cmd;
		cv::Mat img;
		img = cv::imread(W2A(*it));
		if (!img.data) {
			AfxMessageBox(_T("Read image error!"), MB_ICONSTOP);
			goto RELEASE;
		}
		
		CString subStr = (*it);
		get_filename((*it), subStr);
		int start_Pos = subStr.Find(_T("_"));
		int end_Pos = subStr.Find(_T("."));
		CString strID = subStr.Mid(start_Pos + 1, end_Pos - start_Pos - 1);							/* get picture's ID */
		string sID = static_cast<CStringA>(strID);
		int iID = atoi(sID.c_str());

		uint32_t payload_len = sizeof(pic_payload_t) + PIC_WIDTH * PIC_HEIGHT * PIC_CHANNELS;
		pic_pack_payload(img, send_buf + sizeof(req_pack_head_t));
		if (SEL_REGISTER == nSel)
			cmd = CMD_REGISTER;
		else if (SEL_RECOGNISE == nSel)
			cmd = CMD_RECOGNISE;

		pack_head(cmd, iID, payload_len, send_buf);	
#ifdef PIC_DEBUG
		FILE *fout;
		fopen_s(&fout, "./pic_dat.txt","wt");
		for (int i = 0; i < payload_len; i++)
		{
			fprintf(fout, "%02x", send_buf[i + sizeof(req_pack_head_t)]);
		}
		fclose(fout);
#endif
		if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
			AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
			goto RELEASE;
		}
		if (get_response(iID, send_buf, recv_buf) < 0) {
			AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
			goto RELEASE;
		}
		if (GET_RESP_RESULT(recv_buf) == RESULT_FAIL) {
			if (SEL_RECOGNISE == nSel) {
				sprintf_s(log, "recognise pic id:%d error.\n", iID);
				logfile.Write(log, strlen(log));
			}
			else if (SEL_REGISTER == nSel) {
				sprintf_s(log, "register pic id:%d error.\n", iID);
				logfile.Write(log, strlen(log));
			}
			err_cnt++;
		}
		
		if (SEL_RECOGNISE == nSel) {
			pic_score_t *pic_score = (pic_score_t *)(recv_buf + sizeof(resp_pack_head_t));				/* output recognition result */

			short score_original = GET_PIC_SCORE(pic_score);
			double score = score_original / pow(2, GET_PIC_QVALUE(pic_score));							/* 2^n */
			sprintf_s(result_output, "B_%d, A_%d, %f\n", iID, GET_PIC_ID(pic_score), score);
			result.Write(result_output, strlen(result_output));
		}
		deal_cnt++;
		float update_value = ((float)deal_cnt / pic_cnt) * prog_max;									/* update process bar */
		prog->SetPos(update_value);
		
		/* msg route */
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		//MessageBox(*it);
	}

#ifdef TIME_DEBUG
	///////////////////////////////////Time test///////////////////////
	QueryPerformanceCounter(&timeEnd);
	elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
	s.Format(_T("elapsed %fs"), elapsed);
	MessageBox(s);
	///////////////////////////////////Time test///////////////////////
#endif
	AfxMessageBox(_T("Deal over!"), MB_ICONINFORMATION);
	
	if (0 == err_cnt) {
		sprintf_s(log, "pass.\n");
		logfile.Write(log, strlen(log));
	}

RELEASE:
	if (SEL_RECOGNISE == nSel) {
		result.Close();
	}
	logfile.Close();
	usb_release();
}


void CLockDemoDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CLockDemoDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CLockDemoDlg::OnEnChangeSelectpath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}



void CLockDemoDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CLockDemoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CLockDemoDlg::OnCbnSelchangeCombo3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nSel = m_comboDeal.GetCurSel();
	if (SEL_RECOGNISE == nSel)
		((CButton*)GetDlgItem(IDC_SAVETO))->EnableWindow(TRUE);
	else if (SEL_REGISTER == nSel)
		((CButton*)GetDlgItem(IDC_SAVETO))->EnableWindow(FALSE);
}


void CLockDemoDlg::OnBnClickedExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}


void CLockDemoDlg::OnBnClickedSaveto()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strFilePathName;
	CString fileName = L"result";			//Ĭ�ϴ򿪵��ļ���  
	CFileDialog dlg(FALSE,					//TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		_T("csv"),
		fileName,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		strFilePathName = dlg.GetPathName(); //�ļ�����������FilePathName��
		SetDlgItemText(IDC_SAVEPATH, strFilePathName);
	}
	else
	{
		return;
	}
}


void CLockDemoDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HANDLE MyProcess = GetCurrentProcess();
	TerminateProcess(MyProcess, 0);
	CDialogEx::OnClose();
}
