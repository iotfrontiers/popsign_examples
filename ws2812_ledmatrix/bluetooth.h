#ifndef _BLUETOOTH_
#define _BLUETOOTH_

#include "Arduino.h"
#include "BluetoothSerial.h"
#include "buffer_serial.h"

class Bluetooth {
private:
	BluetoothSerial* pSerialBT;
	uint8_t ser_recev_len;
	char temp[100];
	int cmd;
	int init_setup = 0;
	boolean recv_callback();
	
public:
	Bluetooth(BluetoothSerial* btSerial) {
		this->pSerialBT = btSerial;
	}
	void setup();
	int check();
	void disconnect();
	void end();
};

#endif
