
// ImageDemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ImageDemo.h"
#include "ImageDemoDlg.h"
#include "afxdialogex.h"
#include "usb.h"
#include "packet.h"

#include <opencv2\opencv.hpp>
#include <highgui.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <atlconv.h>

//LibJpeg
#include <jpeg_lib.h>
///////

#define IMG_HEIGHT 360	
#define IMG_WIDTH 640	
//#define JPEG_QUALITY 95
#define MAXBYTE  102400    //100KB

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//using namespace cv;
using namespace std;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageDemoDlg 对话框



CImageDemoDlg::CImageDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGEDEMO_DIALOG, pParent)
	, sn(_T(""))
	, path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, sn);
	DDX_Text(pDX, IDC_EDIT2, path);
	//DDX_Control(pDX, IDC_COMBO2, m_combox);
}

BEGIN_MESSAGE_MAP(CImageDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON5, &CImageDemoDlg::OnBnClickedButton5)
	//ON_BN_CLICKED(IDC_BUTTON4, &CImageDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &CImageDemoDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &CImageDemoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CImageDemoDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON6, &CImageDemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON2, &CImageDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CImageDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON10, &CImageDemoDlg::OnBnClickedButton10)
	//ON_BN_CLICKED(IDC_BUTTON11, &CImageDemoDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON4, &CImageDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON11, &CImageDemoDlg::OnBnClickedButton11)
END_MESSAGE_MAP()


// CImageDemoDlg 消息处理程序

BOOL CImageDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//m_combox.AddString(_T("IR IMG(640x360)"));
	//m_combox.AddString(_T("SPK IMG(640x360)"));
	//m_combox.AddString(_T("DEPTH IMG(640x360)"));
	//m_combox.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageDemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImageDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
CString name;//标定文件的路径
CString Spk90Name;  //压缩图片路径

static uint32_t irCount = 0;
static uint32_t spk_30 = 0;
static uint32_t spk_50 = 0;
static uint32_t spk_70 = 0;
static uint32_t spk_90 = 0;
static uint32_t depthCount = 0;


GLOBAL(void)/*void*/ write_IR_JPEG_file(/*char * dst_path,*/ int quality, JSAMPLE* image_buffer, unsigned char *compressedBuffer, size_t &outsize)
{
	unsigned char *outBuffer = nullptr;
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	//FILE * outfile;    
	JSAMPROW row_pointer[1];
	int row_stride;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	//errno_t err;
	//err = fopen_s((&outfile), dst_path, "wb");
	//if (err != 0)
	//{
	//	std::cout << "FAILED TO CREATE OUTPUT IMAGE!!!";
	//	exit(-1);
	//}
	//jpeg_stdio_dest(&cinfo, outfile);    //压缩保存到outfile文件（注释部分为压缩到文件代码）
	jpeg_mem_dest(&cinfo, &outBuffer, &outsize);    //压缩保存到outBuffer内存中，outsize为压缩完成后的大小，outsize会初始化一个值

	cinfo.image_width = IMG_WIDTH;
	cinfo.image_height = IMG_HEIGHT;
	cinfo.input_components = 1;
	cinfo.in_color_space = JCS_GRAYSCALE;
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
	jpeg_start_compress(&cinfo, TRUE);
	row_stride = IMG_WIDTH;	/* JSAMPLEs per row in image_buffer */
	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_pointer[0] = (JSAMPROW)&image_buffer[cinfo.next_scanline * row_stride];
		(void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress(&cinfo);    //压缩完成后,outsize会计算出实际值
	outsize = outsize > IMG_WIDTH * IMG_HEIGHT ? IMG_WIDTH * IMG_HEIGHT : outsize;
	for (int i = 0; i < outsize; i++)
	{
		compressedBuffer[i] = outBuffer[i];
	}
	//fclose(outfile);
	if (outBuffer != nullptr)
	{
		free(outBuffer);
		outBuffer = nullptr;
	}
	jpeg_destroy_compress(&cinfo);
}



//选择模式
//void CImageDemoDlg::OnBnClickedButton4()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
//	uint8_t send_buf[BUF_SEND_LEN] = { 0 };														/* packet buffer */
//
//	if (usb_initial() < 0) {
//		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);	
//		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);							/* usb init */
//		return;
//	}
//	int nSel = m_combox.GetCurSel();
//	resolution_pack_payload(nSel + 0x50, send_buf + sizeof(req_pack_head_t));  //send_buf已经申请了长度为128+512字节的内存，所以首地址已经确定，从send_buf这个位置开始写就是往send_buf数组里写  //send_buf是send_buf数组的首地址，加上一个12字节的头长，意思是将send_buf这个首地址向后移了12字节，从第13字节开始存数据（不加的话就从首字节开始存了）
//	uint32_t payload_len = sizeof(img_param_payload_t);
//	pack_head(CMD_SET_IMG_PARAM, 0, payload_len, send_buf);   //加头
//	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
//		//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
//		MessageBox(_T("USB 发送失败!"), _T("ImageDemo"), MB_ICONSTOP);
//		goto RELEASE;
//	}
//	if (get_response(0, send_buf, recv_buf) < 0) {                     //有发送有接收，但只是上下确认
//		//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
//		MessageBox(_T("USB 接收失败!"), _T("ImageDemo"), MB_ICONSTOP);
//		goto RELEASE;
//	}
//	if (GET_RESP_RESULT(recv_buf) == RESULT_FAIL) {
//		//AfxMessageBox(_T("Set Work Mode Fail!"), MB_ICONSTOP);
//		MessageBox(_T("模式设定失败!"), _T("ImageDemo"), MB_ICONSTOP);
//	}
//	//AfxMessageBox(_T("Set Work Mode success!"), MB_ICONINFORMATION);
//	MessageBox(_T("模式设定成功!"), _T("ImageDemo"), MB_ICONINFORMATION);
//
//RELEASE:
//	usb_release();
//}

//打开文件路径
void CImageDemoDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CString des;
	CFolderPickerDialog fd(NULL, 0, this, 0);
	if (fd.DoModal() == IDOK)
	{
		des = fd.GetPathName();
		SetDlgItemText(IDC_EDIT2, des);    //将des赋值到IDC_EDIT2
	}
	else
	{
		return;
	}
}
int changeSN = 0;
CString touthFile;   //二级文件路径
//写入SN
void CImageDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	irCount = 0;
	spk_30 = 0;
	spk_50 = 0;
	spk_70 = 0;
	spk_90 = 0;
	depthCount = 0;

	CString pa;  //创建二级文件夹
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };	
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);	
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);							/* usb init */
		return;
	}
	CString inpSN;
	GetDlgItemText(IDC_EDIT1, inpSN);    //获取IDC_EDIT1的值输入到inpSN
	uint32_t SN = _ttoi(inpSN);
	uint32_t sn_len = sizeof(img_sn_inf);    //头里面的len指的是数据部分长度吧，需要改成sn长度，发送的send_buf的长度就是头+数据
	//uint8_t head_len = sizeof(req_pack_head_t);    //头长，sn偏移用
	pack_head(CMD_GET_OFI_SN, 0, sn_len, send_buf);   //加头（头里面的len写的是除去头的数据的长度，因为在send_packet（）参数里的GET_REQ_LEN(send_buf)是头的长度加上len的长度）
	//pack_sn(send_buf, SN, head_len);  //加sn
	pack_new_sn(send_buf + sizeof(req_pack_head_t), SN);
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0)
	{
		MessageBox(_T("USB 发送失败!"), _T("ImageDemo"), MB_ICONSTOP);
		//usb_release();
		//return;
		goto RELEASE;
	}
	//510写入read里需要时间
	//Sleep(200);
	if (get_response(0, send_buf, recv_buf) < 0) {
		//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
		MessageBox(_T("USB 读取失败!"), _T("ImageDemo"), MB_ICONSTOP);
		//usb_release();
		//return;
		goto RELEASE;
	}
	if (GET_RESP_RESULT(recv_buf) == RESULT_FAIL) {
		//AfxMessageBox(_T("Set Work Mode Fail!"), MB_ICONSTOP);
		MessageBox(_T("SN写入失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	MessageBox(_T("SN写入成功!"), _T("ImageDemo"), MB_ICONINFORMATION);
	//usb_release();
RELEASE:
	usb_release();

	//创建二级文件

	GetDlgItemText(IDC_EDIT2, pa);
	if (!PathIsDirectory(pa))
	{
		::CreateDirectory(pa, NULL);//创建目录,已有的话不影响
	}
	inpSN.Format(_T("\\%s"), inpSN);
	pa += inpSN;
	if (!PathIsDirectory(pa))
	{
		::CreateDirectory(pa, NULL);//创建目录,已有的话不影响
	}
	touthFile = pa;
}
//创建.txt并写入数据
void CreatTxt(char* pathName,string path/*, int length*/)//创建txt文件
{
	//char* path = "C:\\1.txt"; // 你要创建文件的路径
	ofstream fout/*(pathName)*/;
	fout.open(pathName, ios_base::app);   //(,ios_base::app参数可保证之前的内容不删除)
	if (fout) { // 如果创建成功
		/*for (int i = 0; i < length; i++)
		{*/
			fout << path << endl; // 使用与cout同样的方式进行写入

		//}

		fout.close();  // 执行完操作后关闭文件句柄
	}
}

//IR标定保存
void CImageDemoDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	static uint32_t all_pic_id = 0;
	//static uint32_t all_pic_spk_id = 0;
	static uint32_t ir_pic_id = 0;
	static uint32_t rgb_pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString sID;
	CString txtName;
	uint32_t offset;   //偏移量
	CString inpSN;  //获取sn
	GetDlgItemText(IDC_EDIT1, inpSN);    //获取IDC_EDIT1的值输入到inpSN
	CString currentPath = touthFile;   //当前二级路径
	

	uint8_t send_buf[BUF_SEND_LEN] = { 0 };															/* packet buffer */

	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	if (recv_buf == nullptr) {
		//AfxMessageBox(_T("malloc error!"), MB_ICONSTOP);
		MessageBox(_T("内存分配失败!"), _T("ImageDemo"), MB_ICONSTOP);
	}

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	//int nSel = m_combox.GetCurSel();
	////ir
	//if (1 == nSel) {
	uint8_t *recv_spk_buf = recv_buf;
	uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
	uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

	{
		//uint8_t head_len = sizeof(req_pack_head_t);    //头长，sn偏移用
		uint32_t cmd_len = sizeof(calibration_param);    
		pack_head(CMD_GET_ALL_IMG_SPK, /*all_pic_spk_id*/irCount, cmd_len, send_buf);    //参数len必须是uint32_t，因为是uint32_t转4字节，uint8_t会出错
		calibrationParamIr(send_buf + sizeof(req_pack_head_t));   //加ir参数
		//pack_new_sn(send_buf + sizeof(req_pack_head_t), 243);  //ir参数发送以sn形式
		if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
			//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
			MessageBox(_T("USB 发送错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --- recv spk img --- */
		if (get_depth_map(irCount, send_buf, recv_spk_buf) < 0) {
			//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
			MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --- recv ir img --- */
		if (get_ir_image(irCount, send_buf, recv_ir_buf) < 0) {
			//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
			MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --- recv rgb img --- */
		if (get_rgb_image(irCount, send_buf, recv_rgb_buf) < 0) {
			//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
			MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --------- deal imgs --------- */
		/* --- spk img --- */
		uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
		/* spk raw */
		//sID.Format(_T("\\inter_spk%d_640x360.raw"), all_pic_spk_id);
		//GetDlgItemText(IDC_EDIT2, strFilePathName);
		//strFilePathName += sID;
		//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
		//	//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
		//	MessageBox(_T("Open SPK IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
		//	goto RELEASE;
		//}
		//saveFile.Write(recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
		//saveFile.Close();

		/* --- ir img --- */
		/* ir raw */
		sID.Format(_T("\\%s_ir%d_640x360.raw"), inpSN, irCount);
		//GetDlgItemText(IDC_EDIT2, strFilePathName);
		//currentPath += sID;
		if (!saveFile.Open(currentPath + sID, CFile::modeCreate | CFile::modeWrite)) {
			//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
			MessageBox(_T("打开Ir图片文件错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}
		saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
		saveFile.Close();

		//保存bmp图像
		int cols = 640;
		int rows = 360;
		sID.Format(_T("\\%s_ir%d_640x360.bmp"), inpSN, irCount);
		uint8_t * pDat = (uint8_t *)(recv_ir_buf + offset);
		cv::Mat mat(rows, cols, CV_8UC1, pDat);
		//cv::imshow("img", mat);
		//cv:waitKey(0.1);
		//GetDlgItemText(IDC_EDIT2, strFilePathName);
		//currentPath += sID;
		USES_CONVERSION;   //和下面的W2A实现Cstring转cv::string
		cv::imwrite(W2A(currentPath + sID), mat);
		//name = touthFile;

		//bmp文件路径写入txt中(第一张图不要)
		if (irCount != 0)
		{
			txtName.Format(_T("\\%s_calib_image_list.txt"), inpSN);
			CreatTxt(W2A(currentPath + txtName), W2A(currentPath + sID));
			name = currentPath + txtName;
		}
		//bmp文件路径写入txt中
		//txtName.Format(_T("\\%s_calib_image_list.txt"), inpSN);
		//CreatTxt(W2A(currentPath + txtName), W2A(currentPath + sID));
		//name = currentPath + txtName;
		/* --- rgb img --- */
		/* rgb raw */
		//sID.Format(_T("\\inter_rgb%d_640x360.raw"), all_pic_spk_id);
		//GetDlgItemText(IDC_EDIT2, strFilePathName);
		//strFilePathName += sID;
		//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
		//	//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
		//	MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
		//	goto RELEASE;
		//}
		//saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
		//saveFile.Close();

		irCount++;

		/* msg route */
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	//}
	//else
	//{
	//	MessageBox(_T("请选择Ir图模式!"), _T("ImageDemo"), MB_ICONSTOP);
	//	return;
	//}

	MessageBox(_T("保存Ir图片成功!"), _T("ImageDemo"), MB_ICONINFORMATION);

	//RELEASE:
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}

//保存SKP图(30cm)
void CImageDemoDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	static uint32_t all_pic_id = 0;
	//static uint32_t all_pic_spk_id = 0;
	static uint32_t ir_pic_id = 0;
	static uint32_t rgb_pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString sID;
	uint32_t offset;   //偏移量
	CString inpSN;  //获取sn
	GetDlgItemText(IDC_EDIT1, inpSN);    //获取IDC_EDIT1的值输入到inpSN
	CString currentPath = touthFile;   //当前二级路径


	uint8_t send_buf[BUF_SEND_LEN] = { 0 };															/* packet buffer */

	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	if (recv_buf == nullptr) {
		//AfxMessageBox(_T("malloc error!"), MB_ICONSTOP);
		MessageBox(_T("内存分配失败!"), _T("ImageDemo"), MB_ICONSTOP);
	}

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	//int nSel = m_combox.GetCurSel();
	//if (2 == nSel)
	//{
		uint8_t *recv_spk_buf = recv_buf;
		uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
		uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

		{
			uint32_t cmd_len = sizeof(calibration_param);

			//uint8_t head_len = sizeof(req_pack_head_t);    //头长，sn偏移用

			pack_head(CMD_GET_ALL_IMG_SPK, /*all_pic_spk_id*/spk_30, cmd_len, send_buf);
			calibrationParamSpk(send_buf + sizeof(req_pack_head_t));
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB 发送错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv spk img --- */
			if (get_depth_map(spk_30, send_buf, recv_spk_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv ir img --- */
			if (get_ir_image(spk_30, send_buf, recv_ir_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv rgb img --- */
			if (get_rgb_image(spk_30, send_buf, recv_rgb_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --------- deal imgs --------- */
			/* --- spk img --- */
			uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
			/* spk raw */
			sID.Format(_T("\\%s_spk%d_640x360(30cm).raw"), inpSN, spk_30);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			if (!saveFile.Open(currentPath + sID, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("打开SPK图片文件错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}
			saveFile.Write(recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
			saveFile.Close();

			/* --- ir img --- */
			/* ir raw */
			//sID.Format(_T("\\inter_ir%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
			//saveFile.Close();

			/* --- rgb img --- */
			/* rgb raw */
			//sID.Format(_T("\\inter_rgb%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
			//saveFile.Close();

			spk_30++;

			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	//}
	//else
	//{
	//	MessageBox(_T("请选择SPK图模式!"), _T("ImageDemo"), MB_ICONSTOP);
	//	return;
	//}

	MessageBox(_T("保存SPK图片成功!"), _T("ImageDemo"), MB_ICONINFORMATION);

	//RELEASE:
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}

//保存深度图
void CImageDemoDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	static uint32_t all_pic_id = 0;
	//static uint32_t all_pic_spk_id = 0;
	static uint32_t ir_pic_id = 0;
	static uint32_t rgb_pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString currentPath = touthFile;   //当前二级路径

	CString sID;
	uint32_t offset;   //偏移量
	CString inpSN;  //获取sn
	GetDlgItemText(IDC_EDIT1, inpSN);    //获取IDC_EDIT1的值输入到inpSN

	uint8_t send_buf[BUF_SEND_LEN] = { 0 };															/* packet buffer */

	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	if (recv_buf == nullptr) {
		//AfxMessageBox(_T("malloc error!"), MB_ICONSTOP);
		MessageBox(_T("内存分配失败!"), _T("ImageDemo"), MB_ICONSTOP);
	}

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	/*int nSel = m_combox.GetCurSel();
	if (0 == nSel)
	{*/
		uint8_t *recv_depth_buf = recv_buf;
		uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
		uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

		{
			pack_head(CMD_GET_ALL_IMG, /*all_pic_spk_id*/depthCount, 0, send_buf);
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB 发送错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv spk img --- */
			if (get_depth_map(depthCount, send_buf, recv_depth_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv ir img --- */
			if (get_ir_image(depthCount, send_buf, recv_ir_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv rgb img --- */
			if (get_rgb_image(depthCount, send_buf, recv_rgb_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --------- deal imgs --------- */
			/* --- spk img --- */
			uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
			/* spk raw */
			sID.Format(_T("\\%s_depth%d_640x360.raw"), inpSN, depthCount);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			if (!saveFile.Open(currentPath+sID, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("打开深度图文件错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}
			saveFile.Write(recv_depth_buf + offset, GET_RESP_LEN(recv_depth_buf) - offset);
			saveFile.Close();

			cv::Mat depth(DEPTH_MAP_HEIGHT, DEPTH_MAP_WIDTH, CV_16UC1, recv_depth_buf + offset);
			sID.Format(_T("\\%s_depth%d_640x360.png"), inpSN, depthCount);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			USES_CONVERSION;
			cv::imwrite(W2A(currentPath + sID), depth);
			
			//深度判断
			//USES_CONVERSION;
			string imgPath = /*"./Mean_Depth/depth16u.png"*/W2A(currentPath + sID); /*深度图(ushort类型)路径*/

			float rowRate = 0.9, colRate = 0.8;
			cv::Mat depthImg = cv::imread(imgPath, -1);
			int ypadding = int(round(depthImg.rows *((1 - rowRate) / 2)));
			int xpadding = int(round(depthImg.cols *((1 - colRate) / 2)));
			int y1 = ypadding, y2 = depthImg.rows - ypadding;
			int x1 = xpadding, x2 = depthImg.cols - xpadding;
			ushort val = 0;
			double sum = 0.0;
			int count = 0;
			for (int y0 = y1; y0 < y2; y0++) {
				for (int x0 = x1; x0 < x2; x0++) {
					val = depthImg.at<ushort>(y0, x0);
					sum += val;
					count++;
				}
			}
			float meanDepth = sum * 1.0 / count;
			printf("\nimgPath=%s\n", imgPath.c_str());
			printf("meanDepth=%f\n\n", meanDepth);
			if (fabs(meanDepth - 1000.0f)<=10.0f)//meanDepth是否是mm
			{
				MessageBox(_T("深度图合格!"), _T("ImageDemo"), MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(_T("深度图不合格!"), _T("ImageDemo"), MB_ICONSTOP);
			}
			
			//if (meanDepth - 3 >= 3)
			//{
			//	if (MessageBox(TEXT("不合格，是否保存."), TEXT("Result"), MB_OKCANCEL) == IDOK)
			//	{
			//		
			//	}

			//}

			//saveFile.Write(recv_depth_buf + offset, GET_RESP_LEN(recv_depth_buf) - offset);
			//saveFile.Close();

			/* --- ir img --- */
			/* ir raw */
			//sID.Format(_T("\\inter_ir%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
			//saveFile.Close();

			/* --- rgb img --- */
			/* rgb raw */
			//sID.Format(_T("\\inter_rgb%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
			//saveFile.Close();

			depthCount++;

			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	/*}
	else
	{
		MessageBox(_T("请选择Depth图模式!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}*/

	MessageBox(_T("保存Depth图片成功!"), _T("ImageDemo"), MB_ICONINFORMATION);

	//RELEASE:
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}

void calcF(cv::Mat &mat, uchar *dat, double *daf,double a)
{
	dat = mat.data;
	daf = (double *)dat;
	a = daf[0];
}

//传输标定参数（1.从文件读；2.读取到的数据直接处理）
void CImageDemoDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CString currentPath = touthFile;
	CString sid;
	static uint32_t xmlNum = 0;
	sid.Format(_T("\\calib_result%d.xml"), xmlNum);
	//ifstream fin("D:/calib_image_list.txt"); /* 标定所用图像文件的路径 */
	ifstream fin(name); /* 标定所用图像文件的路径 */
	USES_CONVERSION;
	cv::FileStorage fs(W2A(currentPath + sid), cv::FileStorage::WRITE);  /* 保存标定结果的文件 */
	int rowPoints = 8, colPoints = 11;    /* 标定板上每行、列的角点数 */
	int cellW = 25, cellH = 25;  /* 实际测量得到的标定板上每个棋盘格的大小 */

	cout << "开始提取角点………………" << endl;
	int image_count = 0;
	cv::Size image_size;
	cv::Size board_size = cv::Size(rowPoints, colPoints);
	vector<cv::Point2f> image_points_buf;
	image_points_buf.reserve(100);

	vector<vector<cv::Point2f>> image_points_seq;
	image_points_seq.reserve(100);

	string filename;
	while (getline(fin, filename)) {
		image_count++;
		cv::Mat imageInput = cv::imread(filename);
		if (image_count == 1) {
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			cout << "image_width = " << image_size.width << endl;
			cout << "image_height = " << image_size.height << endl;
		}
		cout << "image_count = " << image_count << endl;
		if (0 == findChessboardCorners(imageInput, board_size, image_points_buf)) {
			cout << "can not find chessboard corners!\n";
			MessageBox(_T("找不到棋盘格角点!"), _T("ImageDemo"), MB_ICONSTOP);
			return;
			//exit(1);
		}
		else {
			cv::Mat view_gray;
			cvtColor(imageInput, view_gray, CV_RGB2GRAY);
			cornerSubPix(view_gray, image_points_buf, cv::Size(5, 5), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 100, 0.0001));
			image_points_seq.push_back(image_points_buf);
		}
	}
	int total = image_points_seq.size();
	cout << "total = " << total << endl;
	cout << "角点提取完成！\n";
	cout << "开始标定………………";
	cv::Size square_size = cv::Size(cellW, cellH);
	vector<vector<cv::Point3f>> object_points;
	object_points.reserve(100);

	cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0));
	vector<int> point_counts;
	point_counts.reserve(100);

	cv::Mat distCoeffs = cv::Mat(1, 5, CV_32FC1, cv::Scalar::all(0));
	vector<cv::Mat> tvecsMat;
	tvecsMat.reserve(100);

	vector<cv::Mat> rvecsMat;
	rvecsMat.reserve(100);

	int i, j, t;
	for (t = 0; t < image_count; t++) {
		vector<cv::Point3f> tempPointSet;
		for (i = 0; i < board_size.height; i++) {
			for (j = 0; j < board_size.width; j++) {
				cv::Point3f realPoint;
				realPoint.x = (float)i * square_size.width;
				realPoint.y = (float)j * square_size.height;
				realPoint.z = 0.0f;
				tempPointSet.push_back(realPoint);
			}
		}
		object_points.push_back(tempPointSet);
	}
	for (i = 0; i < image_count; i++) {
		point_counts.push_back(board_size.width*board_size.height);
	}
	calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, CV_CALIB_FIX_K3);
	cout << "标定完成！\n";
	cout << "开始评价标定结果………………\n";
	double total_err = 0.0;
	double err = 0.0;
	vector<cv::Point2f> image_points2;
	image_points2.reserve(100);

	cout << "\t每幅图像的标定误差：\n";
	for (i = 0; i < image_count; i++) {
		vector<cv::Point3f> tempPointSet = object_points[i];
		projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points2);
		vector<cv::Point2f> tempImagePoint = image_points_seq[i];
		cv::Mat tempImagePointMat = cv::Mat(1, tempImagePoint.size(), CV_32FC2);
		cv::Mat image_points2Mat = cv::Mat(1, image_points2.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++) {
			image_points2Mat.at<cv::Vec2f>(0, j) = cv::Vec2f(image_points2[j].x, image_points2[j].y);
			tempImagePointMat.at<cv::Vec2f>(0, j) = cv::Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, cv::NORM_L2);
		total_err += err /= point_counts[i];
		cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
	}
	cout << "总体平均误差：" << total_err / image_count << "像素" << endl;
	cout << "评价完成！" << endl;
	cout << "开始保存定标结果………………" << endl;
	fs << "cameraMatrix" << cameraMatrix;
	fs << "distCoeffs" << distCoeffs;
	fs.release();
	cout << "标定完成." << endl << endl;
	xmlNum++;
	//MessageBox(_T("标定完成!"), _T("ImageDemo"), MB_ICONINFORMATION);
	
	//传输
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);	
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);							/* usb init */
		return;
	}
	uchar *dat = nullptr;
	dat = cameraMatrix.data;
	double *daf = nullptr;
	daf = (double*)dat;
	double a = daf[0];
	//calcF(cameraMatrix,)
	if (a > 490 && a < 470)
	{
		a = 480;
	}
	//uint8_t head_len = sizeof(req_pack_head_t);    //头长，sn偏移用
	uint32_t param_len = sizeof(calc_after_ir);
	pack_head(CMD_OFI_CALC_AFTER, 0, param_len, send_buf);   //加头（头里面的len写的是除去头的数据的长度，因为在send_packet（）参数里的GET_REQ_LEN(send_buf)是头的长度加上len的长度）
	calcIrPam(send_buf + sizeof(req_pack_head_t), a);   //发送参数
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0)
	{
		MessageBox(_T("USB 发送失败!"), _T("ImageDemo"), MB_ICONSTOP);
		//usb_release();
		//return;
		goto RELEASE;
	}
	//510写入read里需要时间
	//Sleep(200);
	if (get_response(0, send_buf, recv_buf) < 0) {
		//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
		MessageBox(_T("USB 读取失败!"), _T("ImageDemo"), MB_ICONSTOP);
		//usb_release();
		//return;
		goto RELEASE;
	}
	if (GET_RESP_RESULT(recv_buf) == RESULT_FAIL) {
		//AfxMessageBox(_T("Set Work Mode Fail!"), MB_ICONSTOP);
		MessageBox(_T("参数发送失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	MessageBox(_T("参数发送成功!"), _T("ImageDemo"), MB_ICONINFORMATION);
	//usb_release();
RELEASE:
	usb_release();
	dat = nullptr;
	daf = nullptr;
}

//保存50cmSPK
void CImageDemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	static uint32_t all_pic_id = 0;
	//static uint32_t all_pic_spk_id = 0;
	static uint32_t ir_pic_id = 0;
	static uint32_t rgb_pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString sID;
	uint32_t offset;   //偏移量
	CString inpSN;  //获取sn
	CString currentPath = touthFile;   //当前二级路径

	GetDlgItemText(IDC_EDIT1, inpSN);    //获取IDC_EDIT1的值输入到inpSN

	uint8_t send_buf[BUF_SEND_LEN] = { 0 };															/* packet buffer */

	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	if (recv_buf == nullptr) {
		//AfxMessageBox(_T("malloc error!"), MB_ICONSTOP);
		MessageBox(_T("内存分配失败!"), _T("ImageDemo"), MB_ICONSTOP);
	}

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	//int nSel = m_combox.GetCurSel();
	//if (2 == nSel)
	//{
		uint8_t *recv_spk_buf = recv_buf;
		uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
		uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

		{
			uint32_t cmd_len = sizeof(calibration_param);

			//uint8_t head_len = sizeof(req_pack_head_t);    //头长，sn偏移用

			pack_head(CMD_GET_ALL_IMG_SPK, /*all_pic_spk_id*/spk_50, cmd_len, send_buf);
			calibrationParamSpk(send_buf + sizeof(req_pack_head_t));
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB 发送错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv spk img --- */
			if (get_depth_map(spk_50, send_buf, recv_spk_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv ir img --- */
			if (get_ir_image(spk_50, send_buf, recv_ir_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv rgb img --- */
			if (get_rgb_image(spk_50, send_buf, recv_rgb_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --------- deal imgs --------- */
			/* --- spk img --- */
			uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
			/* spk raw */
			sID.Format(_T("\\%s_spk%d_640x360(50cm).raw"), inpSN, spk_50);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			if (!saveFile.Open(currentPath+sID, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("打开SPK图片文件错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}
			saveFile.Write(recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
			saveFile.Close();

			/* --- ir img --- */
			/* ir raw */
			//sID.Format(_T("\\inter_ir%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
			//saveFile.Close();

			/* --- rgb img --- */
			/* rgb raw */
			//sID.Format(_T("\\inter_rgb%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
			//saveFile.Close();

			spk_50++;

			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	//}
	//else
	//{
	//	MessageBox(_T("请选择SPK图模式!"), _T("ImageDemo"), MB_ICONSTOP);
	//	return;
	//}

	MessageBox(_T("保存SPK图片成功!"), _T("ImageDemo"), MB_ICONINFORMATION);

	//RELEASE:
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}

//保存90cmSPK
void CImageDemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	static uint32_t all_pic_id = 0;
	//static uint32_t all_pic_spk_id = 0;
	static uint32_t ir_pic_id = 0;
	static uint32_t rgb_pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString sID;
	uint32_t offset;   //偏移量
	CString currentPath = touthFile;   //当前二级路径

	CString inpSN;  //获取sn
	GetDlgItemText(IDC_EDIT1, inpSN);    //获取IDC_EDIT1的值输入到inpSN

	uint8_t send_buf[BUF_SEND_LEN] = { 0 };															/* packet buffer */

	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	if (recv_buf == nullptr) {
		//AfxMessageBox(_T("malloc error!"), MB_ICONSTOP);
		MessageBox(_T("内存分配失败!"), _T("ImageDemo"), MB_ICONSTOP);
	}

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	//int nSel = m_combox.GetCurSel();
	//if (2 == nSel)
	//{
		uint8_t *recv_spk_buf = recv_buf;
		uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
		uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

		{
			uint32_t cmd_len = sizeof(calibration_param);

			//uint8_t head_len = sizeof(req_pack_head_t);    //头长，sn偏移用

			pack_head(CMD_GET_ALL_IMG_SPK, /*all_pic_spk_id*/spk_90, cmd_len, send_buf);
			calibrationParamSpk(send_buf + sizeof(req_pack_head_t));
			if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
				//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
				MessageBox(_T("USB 发送错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv spk img --- */
			if (get_depth_map(spk_90, send_buf, recv_spk_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv ir img --- */
			if (get_ir_image(spk_90, send_buf, recv_ir_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --- recv rgb img --- */
			if (get_rgb_image(spk_90, send_buf, recv_rgb_buf) < 0) {
				//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
				MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}

			/* --------- deal imgs --------- */
			/* --- spk img --- */
			uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
			/* spk raw */
			sID.Format(_T("\\%s_spk%d_640x360(90cm).raw"), inpSN, spk_90);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			if (!saveFile.Open(currentPath+ sID, CFile::modeCreate | CFile::modeWrite)) {
				//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
				MessageBox(_T("打开SPK图片文件错误!"), _T("ImageDemo"), MB_ICONSTOP);
				//goto RELEASE;
				if (recv_buf != nullptr) {
					free(recv_buf);
					recv_buf = nullptr;
				}
				usb_release();
				return;
			}
			saveFile.Write(recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
			saveFile.Close();

			/* --- ir img --- */
			/* ir raw */
			//sID.Format(_T("\\inter_ir%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
			//saveFile.Close();

			/* --- rgb img --- */
			/* rgb raw */
			//sID.Format(_T("\\inter_rgb%d_640x360.raw"), all_pic_spk_id);
			//GetDlgItemText(IDC_EDIT2, strFilePathName);
			//strFilePathName += sID;
			//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
			//	//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
			//	MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
			//	goto RELEASE;
			//}
			//saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
			//saveFile.Close();

			spk_90++;

			/* msg route */
			MSG msg;
			while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
	//}
	//else
	//{
	//	MessageBox(_T("请选择SPK图模式!"), _T("ImageDemo"), MB_ICONSTOP);
	//	return;
	//}

	MessageBox(_T("保存SPK图片成功!"), _T("ImageDemo"), MB_ICONINFORMATION);
	Spk90Name = currentPath + sID;
	//RELEASE:
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}

//保存70cmSPK

void CImageDemoDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	static uint32_t all_pic_id = 0;
	//static uint32_t all_pic_spk_id = 0;
	static uint32_t ir_pic_id = 0;
	static uint32_t rgb_pic_id = 0;
	CFile saveFile;
	CString strFilePathName;
	CString sID;
	CString currentPath = touthFile;   //当前二级路径

	uint32_t offset;   //偏移量
	CString inpSN;  //获取sn
	GetDlgItemText(IDC_EDIT1, inpSN);    //获取IDC_EDIT1的值输入到inpSN

	uint8_t send_buf[BUF_SEND_LEN] = { 0 };															/* packet buffer */

	uint8_t *recv_buf = (uint8_t *)malloc(20 * 1024 * 1024);   //分配1M内存//ir是640*360=225kB
	if (recv_buf == nullptr) {
		//AfxMessageBox(_T("malloc error!"), MB_ICONSTOP);
		MessageBox(_T("内存分配失败!"), _T("ImageDemo"), MB_ICONSTOP);
	}

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	//int nSel = m_combox.GetCurSel();
	//if (2 == nSel)
	//{
	uint8_t *recv_spk_buf = recv_buf;
	uint8_t *recv_ir_buf = recv_buf + BUF_RECV_GAP_LEN;
	uint8_t *recv_rgb_buf = recv_ir_buf + BUF_RECV_GAP_LEN;

	{
		uint32_t cmd_len = sizeof(calibration_param);

		//uint8_t head_len = sizeof(req_pack_head_t);    //头长，sn偏移用

		pack_head(CMD_GET_ALL_IMG_SPK, /*all_pic_spk_id*/spk_70, cmd_len, send_buf);
		calibrationParamSpk(send_buf + sizeof(req_pack_head_t));
		if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
			//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
			MessageBox(_T("USB 发送错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --- recv spk img --- */
		if (get_depth_map(spk_70, send_buf, recv_spk_buf) < 0) {
			//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
			MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --- recv ir img --- */
		if (get_ir_image(spk_70, send_buf, recv_ir_buf) < 0) {
			//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
			MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --- recv rgb img --- */
		if (get_rgb_image(spk_70, send_buf, recv_rgb_buf) < 0) {
			//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
			MessageBox(_T("USB 接收错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}

		/* --------- deal imgs --------- */
		/* --- spk img --- */
		uint32_t offset = sizeof(resp_pack_head_t) + sizeof(pic_payload_t);
		/* spk raw */
		sID.Format(_T("\\%s_spk%d_640x360(70cm).raw"), inpSN, spk_70);
		//GetDlgItemText(IDC_EDIT2, strFilePathName);
		//strFilePathName += sID;
		if (!saveFile.Open(currentPath + sID, CFile::modeCreate | CFile::modeWrite)) {
			//AfxMessageBox(_T("Open Depth Map file error!"), MB_ICONSTOP);
			MessageBox(_T("打开SPK图片文件错误!"), _T("ImageDemo"), MB_ICONSTOP);
			//goto RELEASE;
			if (recv_buf != nullptr) {
				free(recv_buf);
				recv_buf = nullptr;
			}
			usb_release();
			return;
		}
		saveFile.Write(recv_spk_buf + offset, GET_RESP_LEN(recv_spk_buf) - offset);
		saveFile.Close();

		/* --- ir img --- */
		/* ir raw */
		//sID.Format(_T("\\inter_ir%d_640x360.raw"), all_pic_spk_id);
		//GetDlgItemText(IDC_EDIT2, strFilePathName);
		//strFilePathName += sID;
		//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
		//	//AfxMessageBox(_T("Open IR IMG file error!"), MB_ICONSTOP);
		//	MessageBox(_T("Open IR IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
		//	goto RELEASE;
		//}
		//saveFile.Write(recv_ir_buf + offset, GET_RESP_LEN(recv_ir_buf) - offset);
		//saveFile.Close();

		/* --- rgb img --- */
		/* rgb raw */
		//sID.Format(_T("\\inter_rgb%d_640x360.raw"), all_pic_spk_id);
		//GetDlgItemText(IDC_EDIT2, strFilePathName);
		//strFilePathName += sID;
		//if (!saveFile.Open(strFilePathName, CFile::modeCreate | CFile::modeWrite)) {
		//	//AfxMessageBox(_T("Open RGB IMG file error!"), MB_ICONSTOP);
		//	MessageBox(_T("Open RGB IMG file error!"), _T("IMGDemo"), MB_ICONSTOP);
		//	goto RELEASE;
		//}
		//saveFile.Write(recv_rgb_buf + offset, GET_RESP_LEN(recv_rgb_buf) - offset);
		//saveFile.Close();

		spk_70++;

		/* msg route */
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	//}
	//else
	//{
	//	MessageBox(_T("请选择SPK图模式!"), _T("ImageDemo"), MB_ICONSTOP);
	//	return;
	//}

	MessageBox(_T("保存SPK图片成功!"), _T("ImageDemo"), MB_ICONINFORMATION);

	//RELEASE:
	if (recv_buf != nullptr) {
		free(recv_buf);
		recv_buf = nullptr;
	}
	usb_release();
}

//传输默认参数(480)
void CImageDemoDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	uint8_t recv_buf[BUF_RESERVE_LEN] = { 0 };
	uint8_t send_buf[BUF_SEND_LEN] = { 0 };														/* packet buffer */

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);	
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);							/* usb init */
		return;
	}
	pack_head(CMD_OFI_CALC_DEFAULT, 0, 0, send_buf);   //加头
	//defaultParam(send_buf + sizeof(req_pack_head_t));
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
		//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
		MessageBox(_T("USB 发送失败!"), _T("ImageDemo"), MB_ICONSTOP);
		goto RELEASE;
	}
	if (get_response(0, send_buf, recv_buf) < 0) {                     //有发送有接收，但只是上下确认
		//AfxMessageBox(_T("USB receive error!"), MB_ICONSTOP);
		MessageBox(_T("USB 接收失败!"), _T("ImageDemo"), MB_ICONSTOP);
		goto RELEASE;
	}
	if (GET_RESP_RESULT(recv_buf) == RESULT_FAIL) {
		//AfxMessageBox(_T("Set Work Mode Fail!"), MB_ICONSTOP);
		MessageBox(_T("模式设定失败!"), _T("ImageDemo"), MB_ICONSTOP);
	}
	//AfxMessageBox(_T("Set Work Mode success!"), MB_ICONINFORMATION);
	MessageBox(_T("模式设定成功!"), _T("ImageDemo"), MB_ICONINFORMATION);

RELEASE:
	usb_release();
}

//压缩图像
void CImageDemoDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	int JPEG_QUALITY = 99;   //压缩质量
	FILE * infile = nullptr;
	errno_t err;
	CFile cfile;
	CString destPath;
	int filesize;
	
	unsigned char compressedBuffer[IMG_HEIGHT*IMG_WIDTH] = { 0 };
	uint8_t send_buf[sizeof(req_pack_head_t) + IMG_HEIGHT * IMG_WIDTH] = { 0 };
	//unsigned char *outBuffer;
	//outBuffer = (unsigned char*)malloc(IMG_HEIGHT*IMG_WIDTH);
	
	size_t outSize = 0;  //压缩完成后的大小

	//char *src_path = "D:\\ARGB\\14\\14_spk0_640x360(90cm).raw";
	USES_CONVERSION;
	char *src_path = T2A(Spk90Name.GetBuffer(0));
	Spk90Name.ReleaseBuffer();
	//char *src_path = "D:\\ARGB\\300mmSPK\\Sanban_300.raw";
	err = fopen_s((&infile), src_path, "rb");
	if (err != 0) {
		//std::cout << "FAILED TO READ SRC IMAGE!!!" << std::endl;
		MessageBox(_T("读取源文件失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return /*-1*/;
	}
	JSAMPLE image_buffer[IMG_HEIGHT*IMG_WIDTH];
	int result = fread(image_buffer, sizeof(unsigned char), IMG_HEIGHT*IMG_WIDTH, infile);

	if (result != IMG_HEIGHT * IMG_WIDTH) {
		//std::cout << "ERROR TO READ SRC IMAGE!!!" << std::endl; 
		MessageBox(_T("读取源文件错误!"), _T("ImageDemo"), MB_ICONSTOP);
		return /*-1*/;
	}
	write_IR_JPEG_file(/*dst_path,*/ JPEG_QUALITY, image_buffer, compressedBuffer, outSize);  //outSize为数据长度大小
	while (outSize > MAXBYTE && JPEG_QUALITY >= 70)
	{
		JPEG_QUALITY--;
		outSize = 0;
		write_IR_JPEG_file(JPEG_QUALITY, image_buffer, compressedBuffer, outSize);
	}

	//将压缩buffer传输下位机
	uint32_t sendBufferLen = outSize;
	pack_head(CMD_OFI_SPK_COMPRESS, 0, sendBufferLen, send_buf);
	//compressedBf(send_buf + sizeof(req_pack_head_t), compressedBuffer);
	memcpy(send_buf + sizeof(req_pack_head_t), compressedBuffer, sendBufferLen);   //两个数组加到一起需要用memcpy

	if (usb_initial() < 0) {
		//AfxMessageBox(_T("USB init error!"), MB_ICONSTOP);											/* usb init */
		MessageBox(_T("USB 初始化失败!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}
	
	if (send_packet(send_buf, GET_REQ_LEN(send_buf)) < 0) {
		//AfxMessageBox(_T("USB send error!"), MB_ICONSTOP);
		MessageBox(_T("USB 发送错误!"), _T("ImageDemo"), MB_ICONSTOP);
		return;
	}

	//将内存中的数据写入文件（用于验证内存大小是否与文件大小一样，图片是否一样）
	destPath.Format(_T("D:\\compressed.jpg"));
	if (!cfile.Open(destPath, CFile::modeCreate | CFile::modeWrite))
		return;
	cfile.Write(compressedBuffer, outSize);
	cfile.Close();

	////READ SRC IMG DATA END////之前的将压缩文件存入本地，再读取其大小，不合适再进行压缩，最后将压缩合格的保存本地的文件再读取出来传输下位机，太麻烦
	//char *dst_path = "D:\\compressed.jpg"; 
	//if (cfile.Open(destPath, CFile::modeRead))
	//	filesize = cfile.GetLength();
	//cfile.Close();
	//while (filesize > MAXBYTE && JPEG_QUALITY >= 70)   //压缩图片最大不能超过100kB，最小的压缩比不能小于70
	//{
	//	JPEG_QUALITY--;
	//	write_IR_JPEG_file(dst_path, JPEG_QUALITY, image_buffer);
	//	if (cfile.Open(destPath, CFile::modeRead))
	//		filesize = cfile.GetLength();
	//	cfile.Close();
	//}
}
