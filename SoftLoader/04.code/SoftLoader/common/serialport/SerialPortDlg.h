#pragma once

#include <QDialog>
#include "ui_SerialPortDlg.h"
#include <QButtonGroup>

#include "../datastruct/DataStruct_anc_eq.h"

class HandleCom;

class SerialPortDlg : public QDialog
{
	Q_OBJECT

public:
	SerialPortDlg(QWidget *parent = Q_NULLPTR, int nPowerOfTwo = 27);
	~SerialPortDlg();

	void setData(const QVector<IIR_INFO> & vec);

	void setData(const QVector<IIR_INFO> & vec_iir_ff, const QVector<IIR_INFO> & vec_iir_fb);

private:
	void initUI();
	//��ʼ�����ڲ���
	void initComParam();

	//���ÿ��ƿ���״̬
	void setCtrlStatus(bool bFlag);

	QString strASCIIToHex(const QString & strAscii);
	QString strHexToASCII(const QString & strHex);

	void sendEQMsg();
	void sendANCMsg();
	int sendMsg(const QVector<IIR_INFO> &vec, unsigned char nMsgID);


public slots:
	void slot_recv_data(QByteArray strData);
	void slot_btn_start();
	void slot_btn_stop();
	void slot_btn_send();
	void slot_btn_send_IIR();
	void slot_btn_clear();

	void slot_recv_radio_clicked(bool bChecked);
	void slot_send_radio_clicked(bool bChecked);

	void slot_checkbox_stateChanged(int state);

private:
	enum APP_TYPE
	{
		EQ_APP,
		ANC_APP
	};
	HandleCom* m_pHandleCom;
	bool m_bSendASCII;		//���͵�������ʾΪASCII��
	bool m_bRecvASCII;		//���յ�������ʾΪASCII��
	char m_cData[5000];
	int  m_nLen;
	QVector<IIR_INFO> m_vec_data;
	QVector<IIR_INFO> m_vec_data_FF;
	QVector<IIR_INFO> m_vec_data_FB;

	bool m_bAutoWrap;		//�Ƿ��Զ�����
	bool m_bShowSended;		//�Ƿ���ʾ����
	bool m_bShowTm;			//�Ƿ���ʾʱ��

private:
	Ui::SerialPortDlg ui;
	APP_TYPE m_nType;
	int m_nPowerOfTwo;
};
