/*
* Remote PC Shutdown using serial communication
* Shreyas K
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

using std::cout;
using std::endl;
#define MAX_DATA_LENGTH 255
#define baudrate CBR_9600
char *port_name = "\\\\.\\COM1"; //Change this to your current com port (do not remove the slashes).
char incomingData[MAX_DATA_LENGTH];
const char* magickeyword = "Hello";

class SerialPort
{
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;
public:
    SerialPort(char *portName);
    ~SerialPort();
    int readSerialPort(char *buffer, unsigned int buf_size);
    bool isConnected();
};

int main()
{
    SerialPort Serial(port_name); //Init serial port 
    if (!Serial.isConnected()) cout << "COM port not found" << endl;
    else cout << "Connected to COM Port! Waiting for keyword." << endl;
    while (Serial.isConnected()){
    Serial.readSerialPort(incomingData, MAX_DATA_LENGTH); //Get strings from serial stream
    if(strcmp(incomingData, magickeyword)==0) //Compare the string from serial with the keyword
        {
            cout << "Successfully recived keyword!" << endl;
            ShellExecute(NULL, "open", "c:/windows/system32/shutdown.exe", "/s /t 30 ", NULL, SW_SHOWDEFAULT); 
            // Call shutdown.exe in system32. change /s to /h to hibernate or change /t to for e.g. 60 to shutdown after 60 seconds.
            break;
        }
    Sleep(100); //Small delay
  }
}


SerialPort::~SerialPort()
{
    if (this->connected){
        this->connected = false;
        CloseHandle(this->handler);
    }
}

SerialPort::SerialPort(char *portName)
{
    this->connected = false;
    this->handler = CreateFileA(static_cast<LPCSTR>(portName),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    DCB dcbSerialParameters = {0};
    if (GetCommState(this->handler, &dcbSerialParameters)) {
        dcbSerialParameters.BaudRate = CBR_9600;
        dcbSerialParameters.ByteSize = 8;
        dcbSerialParameters.StopBits = ONESTOPBIT;
        dcbSerialParameters.Parity = NOPARITY;
        dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;
        if (SetCommState(handler, &dcbSerialParameters)) {
            this->connected = true;
            PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
            Sleep(2000);
        }
    }
}

int SerialPort::readSerialPort(char *buffer, unsigned int buf_size) 
{
    DWORD bytesRead;
    unsigned int toRead = 0;
    ClearCommError(this->handler, &this->errors, &this->status);
    if (this->status.cbInQue > 0){
        if (this->status.cbInQue > buf_size){
            toRead = buf_size;
        }
        else toRead = this->status.cbInQue;
    }
    memset(buffer, 0, buf_size);
    if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;
    return 0;
}

bool SerialPort::isConnected() //Connection status check
{
    if (!ClearCommError(this->handler, &this->errors, &this->status))
		this->connected = false;
    return this->connected;
}
