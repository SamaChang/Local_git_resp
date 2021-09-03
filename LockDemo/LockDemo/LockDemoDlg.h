
// LockDemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CLockDemoDlg 对话框
class CLockDemoDlg : public CDialogEx
{
// 构造
public:
	CLockDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOCKDEMO_DIALOG };

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
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSelectdir();
	afx_msg void OnBnClickedDeal();
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeSelectpath();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
	CComboBox m_comboDeal;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedSaveto();
//	afx_msg void OnClose();
	afx_msg void OnClose();
};
