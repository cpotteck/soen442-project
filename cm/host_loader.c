//======================= Inspired by =======================//
// www.xanthium.in
// Copyright (C) 2014 Rahul.S
//===========================================================//

#include<windows.h>
#include<stdio.h>
#include <string.h>
int main()
{

  /*---------------------- Open Port ----------------------*/

  HANDLE handleCom;
  char PortName[] = "COM8";

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
    printf("Error! in Setting DCB Structure \n\n");
    system("pause");
    exit(0);
  }
  else
  {
    printf("\nSetting DCB Structure Successfull");
    printf("\n  Baudrate = %d", dcbSerialParams.BaudRate);
    printf("\n  ByteSize = %d", dcbSerialParams.ByteSize);
    printf("\n  StopBits = %d", dcbSerialParams.StopBits);
    printf("\n  Parity   = %d", dcbSerialParams.Parity);
  }

  /*---------------------- Set Timeouts ----------------------*/
		
  COMMTIMEOUTS comTimeouts = { 0 };

  comTimeouts.ReadIntervalTimeout         = 50;
  comTimeouts.ReadTotalTimeoutConstant    = 50;
  comTimeouts.ReadTotalTimeoutMultiplier  = 10;
  comTimeouts.WriteTotalTimeoutConstant   = 50;
  comTimeouts.WriteTotalTimeoutMultiplier = 10;

  if (SetCommTimeouts(handleCom, &comTimeouts) == FALSE){
    printf("Error! in Setting Time Outs \n\n");
    system("pause");
    exit(0);
  }
  else {
    printf("Setting Serial Port Timeouts Successfull \n");
  }

  /*---------------------- Transmit Message ----------------------*/

  char   messageBuf[] = "a";            // char or byte array
  DWORD  sizeBuf = sizeof(messageBuf);
  DWORD  numBytesBuf = 0;               // Stores the number of bytes written using WriteFile


  Status = WriteFile(handleCom,
              messageBuf,
              sizeBuf,
              &numBytesBuf,
              NULL);
  
  if (Status == FALSE) {
    printf("Error %d in WriteFile \n\n", GetLastError());
    system("pause");
    exit(0);
  }
  else {
    printf("\n Message sent to %s: %s \n", PortName, messageBuf);
  }

  CloseHandle(handleCom);
  return 0;
}
