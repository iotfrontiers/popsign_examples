#include "bluetooth.h"
#include "BluetoothSerial.h"

void Bluetooth::setup()
{
  pSerialBT->begin("led_min"); //Bluetooth device name
}

int Bluetooth::check()
{
	return pSerialBT->available();
}

void Bluetooth::disconnect()
{
  pSerialBT->disconnect();
  // SerialBT->flush();
  pSerialBT->end(); 
}

void Bluetooth::end()
{
  pSerialBT->end(); 
}
