#pragma once

#include "def.h"
#include <qdatetime.h>
#include <qdir.h>
#include <qtextstream.h>
#include "qmessagebox.h"
#include <qpushbutton.h>
#include <qcheckbox.h>

#define TIMEOUT     1000
#define TIMEOUT_2	2000
#define ESENDPACK   -21
#define ESENDSTS    -22
#define EGETSTS     -23
#define EGETDAT     -24

struct Hwid
{
	unsigned char One;
	unsigned char Two;
	unsigned char Three;
};

struct Wifi_mac {
	unsigned char One;
	unsigned char Two;
	unsigned char Three;
	unsigned char Four;
	unsigned char Five;
	unsigned char Six;
};

struct Bt_mac {
	unsigned char One;
	unsigned char Two;
	unsigned char Three;
	unsigned char Four;
	unsigned char Five;
	unsigned char Six;
}; 

struct Eth_mac {
	unsigned char One;
	unsigned char Two;
	unsigned char Three;
	unsigned char Four;
	unsigned char Five;
	unsigned char Six;
};

struct SN_360 {
	unsigned char company[2];
	unsigned char proName;
	unsigned char factory;
	unsigned char reserved;
	unsigned char version;
	unsigned char date[4];
	unsigned char prductNum[4];
};
//360_SN
struct product_info {
	//unsigned char sn[14];
	SN_360 sn;
	//unsigned char hwid[3];
	Hwid hwid;
	unsigned char switchs;
	unsigned char hwboardid;
	unsigned int deviceType;
	Wifi_mac wifi_mac;
	//unsigned char wifi_mac[6];
	Bt_mac bt_mac;
	//unsigned char bt_mac[6];
	Eth_mac eth_mac;
	//unsigned char eth_mac[6];
};

//360����Э��
typedef struct {
	uint8_t head[3];
	uint8_t cmd;
	uint8_t len[4];
}send_360Protocol;
//360����Э��
typedef struct {
	uint8_t head[3];
	uint8_t cmd;
	uint8_t result;
	uint8_t len[4];
}rec_360Protocol;
//360���յ����ݲ��֣���ȥͷ��)����
typedef struct {
	float A;
}rec_360Data;


//�궨ǰParam
typedef struct {
	uint8_t cmd;
	//uint8_t mA;   
	//uint8_t time[2];
	//uint8_t gain;
}calibration_param;

//�궨�������
typedef struct {
	//uint8_t cmd;
	double value;
}calc_after_ir;

//SN
typedef struct {
	uint8_t sn[4];
}img_sn_inf;
//���͵�ͷ
typedef struct {
	uint8_t head[3];
	uint8_t cmd;
	uint8_t id[4];
	uint8_t len[4];
	uint8_t dat[0];
} req_pack_head_t;

//�������ݵ�Э��
typedef struct {
	uint8_t type;
	uint8_t pixs;
	uint8_t ch[2];
	uint8_t height[2];
	uint8_t width[2];
} img_resolution_t;

//�������ݵ�Э��
typedef struct {
	img_resolution_t ir;
	img_resolution_t rgb;
	img_resolution_t depth;
} img_param_payload_t;


typedef struct {
	uint8_t expo;
} exposure_para_t;

//�ļ�ͷ
typedef struct {
	uint8_t ch[2];
	uint8_t height[2];
	uint8_t width[2];
	uint8_t dat[0];
} pic_payload_t;
//��ȡ���ݵ�Э���֡ͷ
typedef struct {
	uint8_t head[3];
	uint8_t cmd;
	uint8_t result;
	uint8_t id[4];
	uint8_t len[4];
	uint8_t dat[0];
} resp_pack_head_t;

typedef struct {
	uint8_t faceid[4];
	uint8_t score[2];
	uint8_t qvalue[2];
} pic_score_t;

//360�Ž�����CMD
#define CMD_DOWNA		0x1
#define CMD_RUNA		0x2
#define CMD_SN			0x3
#define CMD_LCD			0x4
#define CMD_CAMERA		0x5
#define CMD_LED			0x6
#define CMD_BT_WIFI		0x7
#define CMD_NETWORK		0x8
#define CMD_DATA		0x9		//���ݼ���
#define CMD_SENSOR		0xA
#define CMD_MIC_SPEAKER	0xB		
#define CMD_PREVENT		0xC     //����
#define CMD_USB_OTG		0xD
#define CMD_WG			0xE		//Τ��
#define CMD_WARNING		0xF		//����
#define CMD_CONNECT		0x10	//�ɽӵ�
#define	CMD_UART		0x11
#define CMD_GPIO		0x12
#define CMD_IRLAMP		0x30	//ir��
#define CMD_RTC			0x31    //RTC

//360�����֧����
#define FIRST			0xE0
#define SECOND			0xE1
#define THIRD			0xE2
#define FOURTH			0xE3
#define FIFTH			0xE4
#define SIXTH			0xE5
#define SEVENTH			0xE6
#define EIGHTTH			0xE7


#define CMD_REGISTER			0x1
#define CMD_RECOGNISE			0x2
#define CMD_GET_RESULT			/*0x3*/0xC3
#define CMD_GET_DEPTH_MAP		0x4
#define CMD_GET_ALL_IMG			0x5
#define CMD_GET_IR_IMG			0x6
#define CMD_GET_RGB_IMG			0x7
#define CMD_SET_IMG_PARAM		0x8
#define CMD_GET_ALL_IMG_SPK		0x9
#define CMD_SET_EXPOSURE		0xA


#define CMD_GET_OFI_SN          0xB    //����λ��Ҫ
//ŷ������   ����ͼƬ����ȡԭʼ���ݣ�ʱ���͸���λ����
#define CMD_GET_OFI_IR          0xC
#define CMD_GET_OFI_SPK         0xD
#define CMD_GET_OFI_DEPTH       0xE
//ŷ�Ʊ궨ǰ�����趨CMD
#define CMD_OFI_IR              0xF3
#define CMD_OFI_SPK             0xF4
//ŷ�Ʊ궨��������
#define CMD_OFI_CALC_AFTER      0xF5
//ŷ��Ĭ�ϲ���
#define CMD_OFI_CALC_DEFAULT    0xF6


#define RESULT_NOT_READY		0xF0
#define RESULT_SUCCESS			0xF1
#define RESULT_FAIL				0xF2

//360��������cmd
#define GET_360_SEND_CMD(send_packet)		((((send_360Protocol*)send_packet)->cmd))
//��ȡ360�Ž��������ݵĳ��ȣ�����ͷ����
#define GET_360_SEND_LEN(send_packet)		(sizeof(send_360Protocol) + ((((send_360Protocol*)send_packet)->len[0]) << 24) \
											+ ((((send_360Protocol*)send_packet)->len[1]) << 16) + ((((send_360Protocol*)send_packet)->len[2]) << 8) \
											+ (((send_360Protocol*)send_packet)->len[3]))
//360�յ�����cmd
#define GET_360_REC_CMD(rec_packet)			((((rec_360Protocol*)rec_packet)->cmd))
#define GET_360_REC_RESULT(rec_packet)		((((rec_360Protocol*)rec_packet)->result))
//360�յ����ݳ��ȣ�����ͷ����
#define GET_360_REC_LEN(rec_packet)			(sizeof(rec_360Protocol) + ((((rec_360Protocol*)rec_packet)->len[0]) << 24) \
											+ ((((rec_360Protocol*)rec_packet)->len[1]) << 16) + ((((rec_360Protocol*)rec_packet)->len[2]) << 8) \
											+ (((rec_360Protocol*)rec_packet)->len[3]))


#define GET_REQ_CMD(req)       ((((req_pack_head_t*)req)->cmd))
#define GET_REQ_LEN(req)       (sizeof(req_pack_head_t) + ((((req_pack_head_t*)req)->len[0]) << 24) \
                                + ((((req_pack_head_t*)req)->len[1]) << 16) + ((((req_pack_head_t*)req)->len[2]) << 8) \
                                + (((req_pack_head_t*)req)->len[3]))


#define GET_RESP_CMD(resp)     ((((resp_pack_head_t*)resp)->cmd))
#define GET_RESP_RESULT(resp)  ((((resp_pack_head_t*)resp)->result))
#define GET_RESP_ID(resp)     (((((resp_pack_head_t*)resp)->id[0]) << 24) + ((((resp_pack_head_t*)resp)->id[1]) << 16) \
                                + ((((resp_pack_head_t*)resp)->id[2]) << 8) + (((resp_pack_head_t*)resp)->id[3]))

#define GET_RESP_LEN(resp)     (sizeof(resp_pack_head_t) + ((((resp_pack_head_t*)resp)->len[0]) << 24) \
                                + ((((resp_pack_head_t*)resp)->len[1]) << 16) + ((((resp_pack_head_t*)resp)->len[2]) << 8) \
                                + (((resp_pack_head_t*)resp)->len[3]))


#define GET_PIC_CHANNEL(pic_payload)   (((((pic_payload_t*)pic_payload)->ch[0]) << 8) + (((pic_payload_t*)pic_payload)->ch[1]))
#define GET_PIC_HEIGHT(pic_payload)    (((((pic_payload_t*)pic_payload)->height[0]) << 8) + (((pic_payload_t*)pic_payload)->height[1]))
#define GET_PIC_WIDTH(pic_payload)     (((((pic_payload_t*)pic_payload)->width[0]) << 8) + (((pic_payload_t*)pic_payload)->width[1]))


#define GET_PIC_ID(pic_score)   (((((pic_score_t*)pic_score)->faceid[0]) << 24) + ((((pic_score_t*)pic_score)->faceid[1]) << 16) \
                                + ((((pic_score_t*)pic_score)->faceid[2]) << 8) + (((pic_score_t*)pic_score)->faceid[3]))
#define GET_PIC_SCORE(pic_score)   (((((pic_score_t*)pic_score)->score[0]) << 8) + (((pic_score_t*)pic_score)->score[1]))
#define GET_PIC_QVALUE(pic_score)   (((((pic_score_t*)pic_score)->qvalue[0]) << 8) + (((pic_score_t*)pic_score)->qvalue[1]))


void match_sn_mac(uint8_t *mac, uint8_t *mac_b, uint8_t *mac_e);   //ƥ��SN��Ӧ��3��Mac
void recordResult(QString result);
void writeCSV(QString SN, QString testPerson,QString result, QString number, QString currentTime, QString testName, QString unit, QString minValue, QString maxValue, QString testValue, QString noGood);
void pcak_360_eth_mac(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six, /*uint8_t *packet*/Eth_mac *eth);
void pack_360_bt_mac(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six, /*uint8_t *packet*/Bt_mac *bt);
void pack_360_wifi_mac(uint8_t one, uint8_t two, uint8_t three, uint8_t four, uint8_t five, uint8_t six, /*uint8_t *packet*/Wifi_mac *wifi);
void pack_360_hwid(uint8_t one, uint8_t two, uint8_t three, /*uint8_t *packet*/Hwid *hwid);
void pack_360_SN(uint8_t proName, uint8_t factory, uint8_t reserved, uint8_t version, uint32_t date, uint32_t prductNum , /*uint8_t *packet*/SN_360 *req);
void pack_360_Info(uint8_t *packet, uint8_t switchs, uint8_t hwboardid, unsigned int deviceType, SN_360 sn, Hwid hwid, Wifi_mac wifi, Bt_mac bt, Eth_mac eth);
void checkStyle(QCheckBox *box, QString path);
void buttonStyle(QPushButton *button, QString path);
void saveLog(const QString &SN, const QString &item, const QString &isPass);
float pack360_A(uint8_t *packet);
void pcak360_buffer(uint8_t *packet, uint8_t cmd);
void pack360_head(uint8_t cmd, uint32_t payload_len, uint8_t *packet);
void defaultParam(uint8_t *packet);
void calcIrPam(uint8_t *packet, double calValue);
void calibrationParamSpk(uint8_t *packet);
void calibrationParamIr(uint8_t *packet);
void pack_sn(uint8_t *packet, uint32_t snNum, uint8_t offset);
void pack_new_sn(uint8_t *packet, uint32_t snNum);
void pack_head(uint8_t cmd, uint32_t id, uint32_t payload_len, uint8_t *packet);
void exposure_pack_payload(int sel, uint8_t *buf);
void resolution_pack_payload(int sel, uint8_t *buf);
int send_packet(uint8_t *packet, uint32_t len);
int get_depth_map(uint32_t id, uint8_t *send, uint8_t *recv);
int get_ir_image(uint32_t id, uint8_t *send, uint8_t *recv);
int get_rgb_image(uint32_t id, uint8_t *send, uint8_t *recv);
int get_response(uint32_t id, uint8_t *send, uint8_t *recv);