#ifndef _BUFFER_SERIAL_
#define _BUFFER_SERIAL_

#include "BluetoothSerial.h"

#define MAX_SERIAL_BUF 1024
#define PACKET_SIZE (9*1024)+20 // 9Kbyte + 20byte
#define STX 0x02
#define ETX 0x03
//#define ACK 0x06
#define NCK 0x15

#define SIZE_STX				1
#define SIZE_LEN1				2
#define SIZE_LEN2				2
#define SIZE_CMD                1
#define SIZE_CRC                2
#define SIZE_ETX                1
#define SIZE_FIELD              5
#define SIZE_PAGE               1
#define SIZE_SET_DRAW_FIELD     SIZE_FIELD + SIZE_PAGE + SIZE_LEN1
#define SIZE_WIFI_SSID          1
#define SIZE_WIFI_PW            1
#define SIZE_WIFI_STATUS        1
#define SIZE_PKT_DATA			SIZE_STX + SIZE_LEN1 + SIZE_LEN2 + SIZE_CMD + SIZE_CRC + SIZE_ETX;
#define SIZE_ACTION                    3
#define SIZE_EFFECT                    9

#define IDX_STX					0
#define IDX_LEN					IDX_STX + SIZE_STX
#define IDX_CMD					IDX_LEN + SIZE_LEN1 + SIZE_LEN2
#define IDX_CRC					IDX_CMD + SIZE_CMD
#define IDX_ETX					IDX_CRC + SIZE_CRC

#define TRANSMIT_BLUETOOTH	1
#define TRANSMIT_UART_GPIO 	0
#define TRANSMIT_WIFI_PACKET 	2

class BufferSerial{
private:
	uint8_t  buf[MAX_SERIAL_BUF];
	uint16_t head;
	uint16_t tail;
	char packet[PACKET_SIZE];

	BluetoothSerial* pSerialBT;

	void send_bt_packet(char* sendPacket, uint16_t sendDataLen);
	void send_uart_packet(char* sendPacket, uint16_t sendDataLen);
	boolean recv_callback();
	uint8_t serialType;
public:
	BufferSerial(BluetoothSerial* btSerial){
		this->pSerialBT = btSerial;
  		memset(buf, 0, sizeof(buf));
		head = 0;
		tail = 0;
	}
	bool rcvComplete = true;
	void process();
	void cmd_process(char cmd, char* data, int len);

};

#endif
