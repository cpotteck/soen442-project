

#include <windows.h>
#include<stdio.h>
#include "bsl_stdtype.h"
#include "command_types.h"

#ifndef TARGET_PORT
#define TARGET_PORT "COM8"
#endif

HANDLE setupCommunication() {
  /*---------------------- Open Port ----------------------*/

  HANDLE handleCom;
  char PortName[] = TARGET_PORT;

  handleCom = CreateFile(PortName, // Port name
                      GENERIC_READ | GENERIC_WRITE, //Read/Write
                      0, // No Sharing
                      NULL, // No Security
                      OPEN_EXISTING,
                      0,
                      NULL);

  if (handleCom == INVALID_HANDLE_VALUE) {
    printf("Error in opening serial port \n\n");
    system("pause");
    exit(0);
  }
  else {
    printf("Successfully opened serial port \n");
  }

  /*---------------------- Set SerialPort Parameters ----------------------*/

  DCB dcbSerialParams = { 0 };
  dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
  BOOL Status = GetCommState(handleCom, &dcbSerialParams);

  if (Status == FALSE)
    printf("Error in GetCommState() \n");

  dcbSerialParams.BaudRate = CBR_9600;      // BaudRate = 9600
  dcbSerialParams.ByteSize = 8;             // ByteSize = 8
  dcbSerialParams.StopBits = ONESTOPBIT;    // StopBits = 1
  dcbSerialParams.Parity   = NOPARITY;      // Parity = None

  Status = SetCommState(handleCom, &dcbSerialParams);  // Set port settings

  if (Status == FALSE)
  {
    printf("Error in setting serial port configurations \n\n");
    system("pause");
    exit(0);
  }
  else
  {
    printf("\n Successfully set serial port configurations");
    printf("\n  Baudrate = %d", dcbSerialParams.BaudRate);
    printf("\n  ByteSize = %d", dcbSerialParams.ByteSize);
    printf("\n  StopBits = %d", dcbSerialParams.StopBits);
    printf("\n  Parity   = %d \n\n", dcbSerialParams.Parity);
  }

  /*---------------------- Set Timeouts ----------------------*/
    
  COMMTIMEOUTS comTimeouts = { 0 };

  comTimeouts.ReadIntervalTimeout         = 50;
  comTimeouts.ReadTotalTimeoutConstant    = 50;
  comTimeouts.ReadTotalTimeoutMultiplier  = 10;
  comTimeouts.WriteTotalTimeoutConstant   = 50;
  comTimeouts.WriteTotalTimeoutMultiplier = 10;

  if (SetCommTimeouts(handleCom, &comTimeouts) == FALSE){
    printf("Error in setting timeouts \n\n");
    system("pause");
    exit(0);
  }
  else {
    printf("Successfully set serial port timeouts \n\n");
  }

  return handleCom;
}

struct ReadBuffer receiveFromTarget(HANDLE handleCom) {
  /*---------------------- Receive ----------------------*/

  printf("Receiving...\n\n");
  DWORD dwEventMask;
  char  ReadData;
  DWORD NoBytesRead;
  struct ReadBuffer readTargetBuffer;
  char* SerialBuffer = (char*)calloc(0, sizeof(char));
  u8 count = 0;

  // Mask
  BOOL Status = SetCommMask(handleCom, EV_RXCHAR);
  if (Status == FALSE)
  {
    printf_s("Error in SetCommMask\n\n");
    system("pause");
    exit(0);
  }

  // Wait for receiving
  Status = WaitCommEvent(handleCom, &dwEventMask, NULL);
  if (Status == FALSE)
  {
    printf_s("Error in WaitCommEvent\n\n");
    system("pause");
    exit(0);
  }

  // Read and store in serial buffer
  do
  {
      Status = ReadFile(handleCom, &ReadData, sizeof(ReadData), &NoBytesRead, NULL);
      SerialBuffer = realloc(SerialBuffer, sizeof(char) + count);
      *(SerialBuffer + count) = ReadData;
      count++;
  }
  while (NoBytesRead > 0);
  count--;
      
  readTargetBuffer.buffer = SerialBuffer;
  readTargetBuffer.size = count;
  return readTargetBuffer;
}

void sendToTarget(HANDLE handleCom, byte* sendBuffer, i32 sendSize) {
  /*---------------------- Transmit Program ----------------------*/

  //byte messageBuf[5] = {  0x00, 0x04, 0x91, 0xFF, 0x82, 0x00 };
  // byte messageBuff[]= { 0x00, 0x59, 0xE1, 0x00, 0x25, 0x71, 0xD5, 0x00, 0x2F, 0xFF, 0x85, 0xD5, 0x00, 0x44, 0xFF, 0x85,
  //   0xD9, 0x09, 0xA8, 0xE0, 0x0E, 0xA0, 0x90, 0x1C, 0xE3, 0x04, 0xE0, 0x09, 0xA0, 0xB4, 0x00, 0xFF,
  //   0x82, 0xE0, 0xF4, 0xFF, 0x87, 0x03, 0x04, 0xE7, 0xFF, 0xFF, 0xE7, 0xFF, 0xDB, 0x00, 0x54, 0x2E,
  //   0x53, 0x74, 0x6D, 0x74, 0x00, 0x54, 0x65, 0x73, 0x74, 0x20, 0x31, 0x31, 0x3A, 0x20, 0x62, 0x72,
  //   0x65, 0x61, 0x6B, 0x20, 0x53, 0x74, 0x61, 0x74, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x0A, 0x00, 0x39,
  //   0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x0A, 0x00 };
  DWORD  numBytesBuf = 0; // Stores the number of bytes written using WriteFile

  BOOL Status = WriteFile(handleCom,
              sendBuffer,
              sendSize,
              &numBytesBuf,
              NULL);
  
  if (Status == FALSE) {
    printf("Error %d in WriteFile \n\n", GetLastError());
    system("pause");
    exit(0);
  }
}


