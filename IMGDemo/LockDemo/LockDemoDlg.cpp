
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
#include "fill.h"
#include <math.h>
#include<fstream>

#define TIMER_PROG 9527


using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

uint32_t gContinuous = SINGLE_SAVE_MODE;

extern void transToDepthMap(int16_t *src, uint16_t *dst);
extern void depth_affine_api(uint16_t *src, uint16_t *dst, int h, int w);

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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_PIC_ICON);
}

void CLockDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO3, m_comboDeal);
	DDX_Control(pDX, IDC_COMBO1, m_mcomboDeal);
	DDX_Control(pDX, IDC_COMBO2, m_mcomboSetExpo);
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
	//ON_CBN_SELCHANGE(IDC_COMBO3, &CLockDemoDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_EXIT, &CLockDemoDlg::OnBnClickedExit)
	//ON_BN_CLICKED(IDC_SAVETO, &CLockDemoDlg::OnBnClickedSaveto)
//	ON_WM_CLOSE()
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_SAVE_ALL_IMG, &CLockDemoDlg::OnBnClickedSaveAllImg)
ON_BN_CLICKED(IDC_SAVE_ALL_IMG2, &CLockDemoDlg::OnBnClickedSaveAllImg2)
ON_BN_CLICKED(IDC_SET_WORKMODE, &CLockDemoDlg::OnBnClickedSetWorkmode)
ON_CBN_SELCHANGE(IDC_COMBO1, &CLockDemoDlg::OnCbnSelchangeCombo1)
ON_BN_CLICKED(IDC_POINT_CLOUD, &CLockDemoDlg::OnBnClickedPointCloud)
ON_BN_CLICKED(IDC_CONTINUOUS_SAVE, &CLockDemoDlg::OnBnClickedContinuousSave)
ON_BN_CLICKED(IDC_SET_WORKMODE2, &CLockDemoDlg::OnBnClickedSetWorkmode2)
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
	//AfxGetMainWnd()->SetWindowText(_T("DepthMapDemo"));             /* simple way to change app name */
	m_mcomboDeal.AddString(_T("All IMGS-DEP/IR/RGB(640x360)"));
	m_mcomboDeal.AddString(_T("All IMGS-SPK/IR/RGB(640x360)"));
	m_mcomboDeal.AddString(_T("RGB IMG(1920x1080)"));
	m_mcomboDeal.AddString(_T("IR IMG(1280x720)"));
	m_mcomboDeal.AddString(_T("X-All IMGS-SPK/IR/RGB(640x360)"));
	m_mcomboDeal.SetCurSel(0);

	m_mcomboSetExpo.AddString(_T("Auto Exposure"));
	m_mcomboSetExpo.AddString(_T("Manual Exposure(indoor)"));
	m_mcomboSetExpo.AddString(_T("Manual Exposure(outdoor)"));
	m_mcomboSetExpo.SetCurSel(0);
	
	((CButton *)GetDlgItem(IDC_POINT_CLOUD))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_CONTINUOUS_SAVE))->SetCheck(FALSE);
	//((CButton*)GetDlgItem(IDC_SET_WORKMODE))->EnableWindow(FALSE);
	//((CButton *)GetDlgItem(IDC_POINT_CLOUD))->EnableWindow(FALSE);    //���Ʋ��ɵ�

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



void CLockDemoDlg::OnBnClickedDeal()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������		
	static uint32_t pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString sID;

	uint8_t recv_buf[BUF_RECV_DEPTH_MAP_LEN] = { 0 };
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };														/* packet buffer */
	
	if (usb_initial() < 0) {
		AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		return;
	}

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

	pack_head(CMD_GET_DEPTH_MAP, pic_id, 0, send_buf);
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
		AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
		goto RELEASE;
	}
	if (get_depth_map(pic_id, send_buf, recv_buf) < 0) {
		AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
		goto RELEASE;
	}

	sID.Format(_T("\\depmap%d_640x360.raw"), pic_id);
	GetDlgItemText(IDC_SELECTPATH, strFilePathName);
	strFilePathName += sID;

	if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
		AfxMessageBox(_T("Open file error!"), MB_ICONSTOP);
		goto RELEASE;
	}

	uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
	short tmpbuf[DEPTH_MAP_LEN] = { 0 };
	memcpy(tmpbuf, recv_buf + offset, sizeof(tmpbuf));
	for (int i = 0; i < DEPTH_MAP_LEN; i++) {
		if (tmpbuf[i] < 0)
			tmpbuf[i] = 0;
	}
	saveFile.Write(tmpbuf, sizeof(tmpbuf));
	saveFile.Close();
	pic_id++;
#ifdef TIME_DEBUG
	///////////////////////////////////Time test///////////////////////
	QueryPerformanceCounter(&timeEnd);
	elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
	s.Format(_T("elapsed %fs"), elapsed);
	MessageBox(s);
	///////////////////////////////////Time test///////////////////////
#endif
	AfxMessageBox(_T("Save complete!"), MB_ICONINFORMATION);
	
RELEASE:
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


//void CLockDemoDlg::OnCbnSelchangeCombo3()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	int nSel = m_comboDeal.GetCurSel();
//	if (SEL_RECOGNISE == nSel)
//		((CButton*)GetDlgItem(IDC_SAVETO))->EnableWindow(TRUE);
//	else if (SEL_REGISTER == nSel)
//		((CButton*)GetDlgItem(IDC_SAVETO))->EnableWindow(FALSE);
//}


void CLockDemoDlg::OnBnClickedExit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}


//void CLockDemoDlg::OnBnClickedSaveto()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	CString strFilePathName;
//	CString fileName = L"result";			//Ĭ�ϴ򿪵��ļ���  
//	CFileDialog dlg(FALSE,					//TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
//		_T("csv"),
//		fileName,
//		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//		(LPCTSTR)_TEXT("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"),
//		NULL);
//	if (dlg.DoModal() == IDOK)
//	{
//		strFilePathName = dlg.GetPathName(); //�ļ�����������FilePathName��
//		SetDlgItemText(IDC_SAVEPATH, strFilePathName);
//	}
//	else
//	{
//		return;
//	}
//}


void CLockDemoDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HANDLE MyProcess = GetCurrentProcess();
	TerminateProcess(MyProcess, 0);
	CDialogEx::OnClose();
}



void CLockDemoDlg::OnBnClickedSaveAllImg()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


using namespace std;
void depth2cloud(uint16_t * depthImg, int h, int w, string txtPath) {
	ofstream outFile(txtPath.c_str(), ios::out);
	float fx = 479.870079632894200, fy = 479.454722120008850, cx = 314.307313995870400, cy = 179.104964865166660;
	float px, py, pz;
	int idx = 0;
	for (int y0 = 0; y0 < h; y0++) {
		for (int x0 = 0; x0 < w; x0++) {
			py = (y0 - cy) / fy;
			px = (x0 - cx) / fx;
			pz = depthImg[idx];
			if (pz != 0)
				outFile << px*pz << " " << py*pz << " " << pz << endl;
			idx++;

			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}

		}
	}
	outFile.close();
}

//ÿ����usb_initial���豸��ÿ�ζ���ر�
//����ͼƬ��ÿ�α���Ҫusb_initial���豸��ÿ�δ���һ�����͹رգ�
void CLockDemoDlg::OnBnClickedSaveAllImg2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	static uint32_t all_pic_id = 0;
	static uint32_t all_pic_spk_id = 0;
	static uint32_t ir_pic_id = 0;
	static uint32_t rgb_pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString sID;
	uint32_t offset;

#ifdef DEPTH_DEAL_DEBUG
	///////////////////////////////////Depth Deal test///////////////////////
	extern size_t read_file(char * path, void * out, size_t size);
	extern size_t write_file(char * path, void * in, size_t size);

	int16_t src[DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT];
	uint16_t dst[DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT];
	uint16_t dst1[DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT];
	read_file("disp_640x360-ref.raw", src, DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT * 2);
	transToDepthMap(src, dst);
	write_file("depth_640x360.raw", dst, DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT * 2);
	read_file("depth16_640x360.raw", dst, DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT * 2);
	depth_affine_api(dst, dst1, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH);
	write_file("out.raw", dst1, DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT * 2);
	///////////////////////////////////Depth Deal test///////////////////////
#endif


	//uint8_t recv_buf[BUF_RECV_LEN] = { 0 };
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };															/* packet buffer */

	uint8_t *recv_buf = (uint8_t *)malloc(BUF_RECV_LEN);
	if (recv_buf == NULL) {
		//AfxMessageBox(_T("malloc error!"), MB_ICONSTOP);
		MessageBox(_T("malloc error!"), _T("IMGDemo"), MB_ICONSTOP);
	}

#ifdef YUV_TO_PNG_DEBUG
	extern size_t read_file(char * path, void * out, size_t size);
	read_file("A_1080P_rgb.yuv", recv_buf, RGB_IMG_HEIGHT * RGB_IMG_WIDTH * 2);
	uint8_t *rgb_buf = recv_buf + BUF_RGB_RECV_GAP_LEN;
	Mat rgb_img(RGB_IMG_HEIGHT, RGB_IMG_WIDTH, CV_8UC3, rgb_buf);
	Mat yuv_img(RGB_IMG_HEIGHT, RGB_IMG_WIDTH, CV_8UC2, recv_buf);
	cv::cvtColor(yuv_img, rgb_img, CV_YUV2BGR_UYVY);//CV_YUV2RGB_YUYV//
	sID.Format(_T("\\rgb%d.png"), rgb_pic_id);
	GetDlgItemText(IDC_SELECTPATH, strFilePathName);
	strFilePathName += sID;
	USES_CONVERSION;
	imwrite(W2A(strFilePathName), rgb_img);
#endif


	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB init error!"), _T("IMGDemo"), MB_ICONSTOP);
		return;
	}

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
	int nSel = m_mcomboDeal.GetCurSel();
	if (SEL_ALL_IMGS == nSel) {
		uint8_t *recv_depth_buf = recv_buf;     //�����ڴ��ȴ���� //(1 * 1024 * 1024)	/* 1M */ 
		uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;    //irָ������������ô���ֽڿ�ʼ
		uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;    //irҲ�Ǵ���1*1024*1024  1M���ֽ�
		//do...while����ִ��һ��do�Ĵ��룬���continue save�����ģ�ѡ�У���while��ʼѭ������
		do {
			pack_head(CMD_GET_ALL_IMG, all_pic_id, 0, send_buf);
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {   //GET_REQ_LEN��˵�4�ֽ�����תint����һ�η���
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB send error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv depth map --- */
			if (get_depth_map(all_pic_id, send_buf, recv_depth_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv ir img --- */
			if (get_ir_image(all_pic_id, send_buf, recv_ir_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv rgb img --- */
			if (get_rgb_image(all_pic_id, send_buf, recv_rgb_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --------- deal imgs --------- */
			/* --- depth map --- */
			/* disp raw */
#ifdef DEPTH_DEBUG
			sID.Format(_T("\\imgs_disp%d_640x360.raw"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("Open Depth Map file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
#endif

			uint32_t offset = sizeof(resp_pack_head_t)+sizeof(pic_payload_t);         //֡ͷ��13B��+�ļ�ͷ��6B��
			short tmpbuf[DEPTH_MAP_LEN / sizeof(short)] = { 0 };
			uint16_t tmpbufDst[DEPTH_MAP_LEN / sizeof(short)] = { 0 };
			uint16_t tmpbufAffine[DEPTH_MAP_LEN / sizeof(short)] = { 0 };
			memcpy(tmpbuf, recv_depth_buf + offset, sizeof(tmpbuf));    //��ΪҪ��������ݽ��в��������Ը��Ƶ�������

#ifdef POINT_CLOUD_RECTIFY_DEBUG		
			extern size_t read_file(char * path, void * out, size_t size);
			read_file("depth16_640x360.raw", tmpbuf, DEPTH_MAP_WIDTH * DEPTH_MAP_HEIGHT * 2);
#endif

			for (int i = 0; i < DEPTH_MAP_LEN / sizeof(short); i++) {
				if (tmpbuf[i] < 0)
					tmpbuf[i] = 0;
			}
#ifdef DEPTH_DEBUG
			saveFile.Write(tmpbuf, sizeof(tmpbuf));
			saveFile.Close();
#endif

#ifdef DEPTH_DEBUG
			/* depth orignal raw */
			sID.Format(_T("\\imgs_org_depmap%d_640x360.raw"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("Open Depth Map file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
#endif

#ifndef DOUBLE_BASE
			transToDepthMap(tmpbuf, tmpbufDst);
#else
			memcpy(tmpbufDst, tmpbuf, sizeof(tmpbuf));
#endif

#ifdef DEPTH_DEBUG
			saveFile.Write(tmpbufDst, sizeof(tmpbufDst));
			saveFile.Close();
#endif

			/* depth raw */
			sID.Format(_T("\\imgs_depmap%d_640x360.raw"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("Open Depth Map file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
#ifdef IMG_AFFINE
			depth_affine_api(tmpbufDst, tmpbufAffine, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH);
			fill_gray16(tmpbufAffine, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH);
#else
			memcpy(tmpbufAffine, tmpbufDst, sizeof(tmpbufAffine));
			for (int i = 0; i < DEPTH_MAP_LEN / sizeof(short); i++) {
				tmpbufAffine[i] >>= 4;
			}
#endif
			//�����㷨����������޸�
#ifdef POINT_CLOUD_RECTIFY
			for (int i = 0; i < DEPTH_MAP_LEN / sizeof(short); i++) {
				if (tmpbufAffine[i] < POINT_CLOUD_THRED)
					tmpbufAffine[i] = 0;
			}

			int fill_zero_w = (float)DEPTH_MAP_WIDTH * 12.5f / 100;
			int fill_zero_h = (float)DEPTH_MAP_HEIGHT * 5.0f / 100;
			for (int y = 0; y < DEPTH_MAP_HEIGHT; y++)
			{
				for (int x = 0; x < fill_zero_w; x++)
				{
					tmpbufAffine[y * DEPTH_MAP_WIDTH + x] = 0;
				}
				for (int x = DEPTH_MAP_WIDTH - fill_zero_w; x < DEPTH_MAP_WIDTH; x++)
				{
					tmpbufAffine[y * DEPTH_MAP_WIDTH + x] = 0;
				}
			}

			for (int y = 0; y < fill_zero_h; y++)
			{
				for (int x = 0; x < DEPTH_MAP_WIDTH; x++)
				{
					tmpbufAffine[y * DEPTH_MAP_WIDTH + x] = 0;
				}
			}

			for (int y = DEPTH_MAP_HEIGHT - fill_zero_h; y < DEPTH_MAP_HEIGHT; y++)
			{
				for (int x = 0; x < DEPTH_MAP_WIDTH; x++)
				{
					tmpbufAffine[y * DEPTH_MAP_WIDTH + x] = 0;
				}
			}
#endif
			//tmpbufAffineΪԭʼ��������޸ĺ������
			saveFile.Write(tmpbufAffine, sizeof(tmpbufAffine));
			saveFile.Close();

			/* depth png*/
			Mat depth(DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH, CV_16UC1, tmpbufAffine);
			sID.Format(_T("\\imgs_depmap%d.png"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			USES_CONVERSION;
			imwrite(W2A(strFilePathName), depth);
			//ѡ�е����ĵ���
			/* depth  cloud*/
			int state = ((CButton *)GetDlgItem(IDC_POINT_CLOUD))->GetCheck();
			if (1 == state) {
				sID.Format(_T("\\imgs_depth_cloud%d.txt"), all_pic_id);
				GetDlgItemText(IDC_SELECTPATH, strFilePathName);
				strFilePathName += sID;
				string strCloudPath = static_cast<CStringA>(strFilePathName);
				depth2cloud(tmpbufAffine, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH, strCloudPath);
			}


			/* --- ir img --- */
			/* ir orignal raw */
#ifdef IR_DEBUG
			sID.Format(_T("\\imgs_ir_org%d_640x360.raw"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
				MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
			saveFile.Close();
#endif

			/* ir raw */
			sID.Format(_T("\\imgs_ir%d_640x360.raw"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
				MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}


#ifdef IMG_AFFINE
			uint16_t tmpbufIr[IR_IMG_LEN] = { 0 };
			uint16_t tmpbufIrDst[IR_IMG_LEN] = { 0 };
			uint8_t *p_ir = recv_ir_buf + offset;
			for (int i = 0; i < IR_IMG_LEN; i++) {
				tmpbufIr[i] = p_ir[i];
			}
			depth_affine_api(tmpbufIr, tmpbufIrDst, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH);
			fill_gray16(tmpbufIrDst, DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH);
			saveFile.Write(tmpbufIrDst, sizeof(tmpbufIrDst));
#else
			//memcpy(tmpbufIrDst, tmpbufIr, sizeof(tmpbufAffine));
			saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);     //offset��13B+6B��ͷ������ȫ�����ݲ���
#endif
			//saveFile.Write(tmpbufIrDst, sizeof(tmpbufIrDst));
			saveFile.Close();

			/* ir png*/
			Mat ir(DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH, CV_8UC1, recv_ir_buf + offset);
			sID.Format(_T("\\imgs_ir%d.png"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			imwrite(W2A(strFilePathName), ir);

			/* --- rgb img --- */
			/* rgb raw */
			sID.Format(_T("\\imgs_rgb%d_640x360.raw"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
				MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
			saveFile.Close();

			/* rgb png */
			Mat rgb(DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH, CV_8UC4, recv_rgb_buf + offset);
			cv::Mat imgc3 = cv::Mat::zeros(rgb.rows, rgb.cols, CV_8UC3);
			cv::cvtColor(rgb, imgc3, cv::COLOR_BGRA2BGR);  //COLOR_BGRA2RGB
			sID.Format(_T("\\imgs_rgb%d.png"), all_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			imwrite(W2A(strFilePathName), imgc3);

			all_pic_id++;
			
			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}

		} while (CONTINUOUS_SAVE_MODE == gContinuous);
	}
	else if (SEL_ALL_IMGS_SPK == nSel) {
		uint8_t *recv_spk_buf = recv_buf;
		uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
		uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

		do {
			pack_head(CMD_GET_ALL_IMG_SPK, all_pic_spk_id, 0, send_buf);
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB send error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv spk img --- */
			if (get_depth_map(all_pic_spk_id, send_buf, recv_spk_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv ir img --- */
			if (get_ir_image(all_pic_spk_id, send_buf, recv_ir_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv rgb img --- */
			if (get_rgb_image(all_pic_spk_id, send_buf, recv_rgb_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --------- deal imgs --------- */
			/* --- spk img --- */
			uint32_t offset = sizeof(resp_pack_head_t)+sizeof(pic_payload_t);
			/* spk raw */
			sID.Format(_T("\\inter_spk%d_640x360.raw"), all_pic_spk_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("Open SPK IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
			saveFile.Close();

			/* --- ir img --- */
			/* ir raw */
			sID.Format(_T("\\inter_ir%d_640x360.raw"), all_pic_spk_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
				MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
			saveFile.Close();

			/* --- rgb img --- */
			/* rgb raw */
			sID.Format(_T("\\inter_rgb%d_640x360.raw"), all_pic_spk_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
				MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
			saveFile.Close();

			all_pic_spk_id++;
			
			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		} while (CONTINUOUS_SAVE_MODE == gContinuous);
	}
	else if (SEL_ALL_IMGS_SPK_DBG == nSel) {
		uint8_t *recv_spk_buf = recv_buf;
		uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
		uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

		do {
			pack_head(CMD_GET_ALL_IMG_SPK, all_pic_spk_id, 0, send_buf);
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB send error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv spk img --- */
			if (get_depth_map(all_pic_spk_id, send_buf, recv_spk_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv ir img --- */
			if (get_ir_image(all_pic_spk_id, send_buf, recv_ir_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			/* --- recv rgb img --- */
			if (get_rgb_image(all_pic_spk_id, send_buf, recv_rgb_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			uint8_t *ptr = recv_rgb_buf + sizeof(resp_pack_head_t);
			if (0 == memcmp(ptr, SPK_DBG_END_STR, SPK_DBG_END_STR_LEN)) {
				break;
			}
			uint8_t ir_reg = *(ptr + 0);
			uint8_t spk_reg = *(ptr + 1);
			uint8_t expH_reg = *(ptr + 2);
			uint8_t expL_reg = *(ptr + 3);
			uint8_t gain_reg = *(ptr + 4);

			/* --------- deal imgs --------- */
			/* --- spk img --- */
			uint32_t offset = sizeof(resp_pack_head_t)+sizeof(pic_payload_t);
			/* spk raw */
			sID.Format(_T("\\spk_ir_%x_spk_%x_exH_%x_exL_%x_ga_%x.raw"), ir_reg, spk_reg, expH_reg, expL_reg, gain_reg);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("Open SPK IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
			saveFile.Close();

			/* --- ir img --- */
			/* ir raw */
			sID.Format(_T("\\ir_ir_%x_spk_%x_exH_%x_exL_%x_ga_%x.raw"), ir_reg, spk_reg, expH_reg, expL_reg, gain_reg);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
				MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
			saveFile.Close();

			/* --- rgb img --- */
			/* rgb raw */
			sID.Format(_T("\\rgb_ir_%x_spk_%x_exH_%x_exL_%x_ga_%x.raw"), ir_reg, spk_reg, expH_reg, expL_reg, gain_reg);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
				MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
			saveFile.Close();

			all_pic_spk_id++;

			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		} while (CONTINUOUS_SAVE_MODE == gContinuous);
	}
	else if (SEL_IR_IMG == nSel) {
		do {
			pack_head(CMD_GET_IR_IMG, ir_pic_id, 0, send_buf);
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB send error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			if (get_depth_map(ir_pic_id, send_buf, recv_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			sID.Format(_T("\\ir%d_1280x720.raw"), ir_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;

			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open file error!"), MB_ICONSTOP);
				MessageBox(_T("Open file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			offset = sizeof(resp_pack_head_t)+sizeof(pic_payload_t);
			saveFile.Write(recv_buf + offset, GET_RESP_LEN(recv_buf) - offset);
			saveFile.Close();

			/* ir png*/
			Mat ir(IR_IMG_HEIGHT, IR_IMG_WIDTH, CV_16UC1, recv_buf + offset);
			sID.Format(_T("\\ir%d.png"), ir_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			USES_CONVERSION;
			imwrite(W2A(strFilePathName), ir);

			ir_pic_id++;

			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		} while (CONTINUOUS_SAVE_MODE == gContinuous);
	}
	else if (SEL_RGB_IMG == nSel) {
		do {
			pack_head(CMD_GET_RGB_IMG, rgb_pic_id, 0, send_buf);
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB send error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			if (get_depth_map(rgb_pic_id, send_buf, recv_buf) < 0) {                 //������������з����н���
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}

			sID.Format(_T("\\rgb%d_1920x1080.yuv"), rgb_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;

			if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open file error!"), MB_ICONSTOP);
				MessageBox(_T("Open file error!"), _T("IMGDemo"), MB_ICONSTOP);
				goto RELEASE;
			}
			offset = sizeof(resp_pack_head_t)+sizeof(pic_payload_t);
			saveFile.Write(recv_buf + offset, GET_RESP_LEN(recv_buf) - offset);
			saveFile.Close();

			/* rgb png */
			uint8_t *rgb_buf = recv_buf + BUF_RGB_RECV_GAP_LEN;
			Mat rgb_img(RGB_IMG_HEIGHT, RGB_IMG_WIDTH, CV_8UC3, rgb_buf);
			Mat yuv_img(RGB_IMG_HEIGHT, RGB_IMG_WIDTH, CV_8UC2, recv_buf);
			cv::cvtColor(yuv_img, rgb_img, CV_YUV2BGR_UYVY);//CV_YUV2RGB_YUYV//
			sID.Format(_T("\\rgb%d.png"), rgb_pic_id);
			GetDlgItemText(IDC_SELECTPATH, strFilePathName);
			strFilePathName += sID;
			USES_CONVERSION;
			imwrite(W2A(strFilePathName), rgb_img);

			rgb_pic_id++;
			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		} while (CONTINUOUS_SAVE_MODE == gContinuous);
	}
#ifdef TIME_DEBUG
	///////////////////////////////////Time test///////////////////////
	QueryPerformanceCounter(&timeEnd);
	elapsed = (timeEnd.QuadPart - timeStart.QuadPart) / quadpart;
	s.Format(_T("elapsed %fs"), elapsed);
	MessageBox(s);
	///////////////////////////////////Time test///////////////////////
#endif
	//AfxMessageBox(_T("Save IMG Complete!"), MB_ICONINFORMATION);
	MessageBox(_T("Save IMG Complete!"), _T("IMGDemo"), MB_ICONINFORMATION);
	
RELEASE:
	if (recv_buf != NULL) {
		free(recv_buf);
		recv_buf = NULL;
	}
	usb_release();
}

//ѡ��ģʽ
void CLockDemoDlg::OnBnClickedSetWorkmode()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };														/* packet buffer */

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);	
		MessageBox(_T("USB init error!"), _T("IMGDemo"), MB_ICONSTOP);							/* usb init */
		return;
	}
	int nSel = m_mcomboDeal.GetCurSel();
	resolution_pack_payload(nSel, send_buf + sizeof(req_pack_head_t));  //send_buf�Ѿ������˳���Ϊ128+512�ֽڵ��ڴ棬�����׵�ַ�Ѿ�ȷ������send_buf���λ�ÿ�ʼд������send_buf������д  //send_buf��send_buf������׵�ַ������һ��12�ֽڵ�ͷ������˼�ǽ�send_buf����׵�ַ�������12�ֽڣ��ӵ�13�ֽڿ�ʼ�����ݣ����ӵĻ��ʹ����ֽڿ�ʼ���ˣ�
	uint32_t payload_len = sizeof(img_param_payload_t);
	pack_head(CMD_SET_IMG_PARAM, 0, payload_len, send_buf);   //��ͷ
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
		//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
		MessageBox(_T("USB send error!"), _T("IMGDemo"), MB_ICONSTOP);
		goto RELEASE;
	}
	if (get_response(0, send_buf, recv_buf) < 0) {
		//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
		MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
		goto RELEASE;
	}
	if (GET_RESP_RESULT(recv_buf) == RESULT_FAIL) {
		//AfxMessageBox(_T("Set Work Mode Fail!"), MB_ICONSTOP);
		MessageBox(_T("Set Work Mode Fail!"), _T("IMGDemo"), MB_ICONSTOP);
	}
	//AfxMessageBox(_T("Set Work Mode success!"), MB_ICONINFORMATION);
	MessageBox(_T("Set Work Mode success!"), _T("IMGDemo"), MB_ICONINFORMATION);

RELEASE:
	usb_release();
}

//ѡ����ͼ���͵�combox����ʱ�����¼�
void CLockDemoDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nSel = m_mcomboDeal.GetCurSel();
	if (SEL_ALL_IMGS == nSel) {
		((CButton *)GetDlgItem(IDC_POINT_CLOUD))->EnableWindow(TRUE);
	}
	else {
		((CButton *)GetDlgItem(IDC_POINT_CLOUD))->EnableWindow(FALSE);
	}
}


void CLockDemoDlg::OnBnClickedPointCloud()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CLockDemoDlg::OnBnClickedContinuousSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	gContinuous = ((CButton *)GetDlgItem(IDC_CONTINUOUS_SAVE))->GetCheck();
}

//�ع�����
void CLockDemoDlg::OnBnClickedSetWorkmode2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };														/* packet buffer */

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);	
		MessageBox(_T("USB init error!"), _T("IMGDemo"), MB_ICONSTOP);							/* usb init */
		return;
	}
	int nSel = m_mcomboSetExpo.GetCurSel();
	exposure_pack_payload(nSel, send_buf + sizeof(req_pack_head_t));
	uint32_t payload_len = sizeof(exposure_para_t);
	pack_head(CMD_SET_EXPOSURE, 0, payload_len, send_buf);
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
		//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
		MessageBox(_T("USB send error!"), _T("IMGDemo"), MB_ICONSTOP);
		goto RELEASE;
	}
	if (get_response(0, send_buf, recv_buf) < 0) {
		//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
		MessageBox(_T("USB receive error!"), _T("IMGDemo"), MB_ICONSTOP);
		goto RELEASE;
	}
	if (GET_RESP_RESULT(recv_buf) == RESULT_FAIL) {
		//AfxMessageBox(_T("Set Work Mode Fail!"), MB_ICONSTOP);
		MessageBox(_T("Set Exposure Mode Fail!"), _T("IMGDemo"), MB_ICONSTOP);
	}
	//AfxMessageBox(_T("Set Work Mode success!"), MB_ICONINFORMATION);
	MessageBox(_T("Set Exposure Mode success!"), _T("IMGDemo"), MB_ICONINFORMATION);

RELEASE:
	usb_release();
}
