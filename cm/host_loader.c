//======================= Inspired by =======================//
// www.xanthium.in
// Copyright (C) 2014 Rahul.S
// https://github.com/xanthium-enterprises/Serial-Programming-Win32API-C
//===========================================================//

#include<windows.h>
#include<stdio.h>
#include <string.h>
#include "vm.h"

byte* messageBuf;

const char *GetFilenameExt(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

const char *GetFileName(const char *path) {
    const char *pfile = path + strlen(path);
    for (; pfile > path; pfile--) {
        if ((*pfile == '\\') || (*pfile == '/')) {
            pfile++;
            break;
        }
    }
    return pfile;
}

static u16 loadObjFile(FILE* f) {
    u16 n, size;
    u8  buf[2];

    buf[0] = (u8)fgetc(f);
    buf[1] = (u8)fgetc(f);
    messageBuf = realloc(messageBuf, sizeof(byte) + 1);
    *(messageBuf) = buf[0];
    *(messageBuf + 1) = buf[1];
    size = (u16)((buf[0] << 8) | buf[1]) + 2; // Include first two bytes

    for (n = 2; n < size+2; n++) {
        messageBuf = realloc(messageBuf, sizeof(byte) + n);
        *(messageBuf + n) = (u8)fgetc(f);
    }

    /*
    // Print file size
    printf("Size: %d\n", size);

    // Print as hex
    printf("---Hex---\n");
    int index;
    for (index = 0; index < size+2; index++)
    {
      printf("0x%02x ", (unsigned char)messageBuf[index]);
    }
    printf("\n");
    */

    fclose(f);
    return size;
}

byte* readFile(int argc, char* argv[]) {
  FILE* file;
  char  filename[200];
  const char* name;
  const char* ext;

  if (argc == 2) {
      char *pfile;

      strcpy(filename, argv[1]);
      name = GetFileName(filename);
      ext  = GetFilenameExt(filename);
      strcpy(filename, name);

      if (ext && (strcmp(ext, "exe") == 0)) {
          char pb[50];

          strcpy(pb, "");
          pfile = strcat(pb, filename);
          file = fopen(pfile, "rb" );
          if (file == NULL) {
              printf("%s does not exist.\n", filename);
              return -1;
          }

          if (!loadObjFile(file)) {
            printf("Successfully loaded program file.\n");
            return -2;
          }
      } else {
          printf("Error: Must have a file with '.exe' extension.\n");
          return -3;
      }
  } else {
      printf("Error: Must have a file to load.\n");
      return -4;
  }
}




int main(int argc, char* argv[]) {

  /*---------------------- Read .exe Program File ----------------------*/

  messageBuf = (u8*)calloc(0, sizeof(u8));
  u16 messageBufSize = readFile(argc, argv);
  
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

  /*---------------------- Transmit Program ----------------------*/

  //byte messageBuf[5] = {  0x00, 0x04, 0x91, 0xFF, 0x82, 0x00 };
  // byte messageBuff[]= { 0x00, 0x59, 0xE1, 0x00, 0x25, 0x71, 0xD5, 0x00, 0x2F, 0xFF, 0x85, 0xD5, 0x00, 0x44, 0xFF, 0x85,
  //   0xD9, 0x09, 0xA8, 0xE0, 0x0E, 0xA0, 0x90, 0x1C, 0xE3, 0x04, 0xE0, 0x09, 0xA0, 0xB4, 0x00, 0xFF,
  //   0x82, 0xE0, 0xF4, 0xFF, 0x87, 0x03, 0x04, 0xE7, 0xFF, 0xFF, 0xE7, 0xFF, 0xDB, 0x00, 0x54, 0x2E,
  //   0x53, 0x74, 0x6D, 0x74, 0x00, 0x54, 0x65, 0x73, 0x74, 0x20, 0x31, 0x31, 0x3A, 0x20, 0x62, 0x72,
  //   0x65, 0x61, 0x6B, 0x20, 0x53, 0x74, 0x61, 0x74, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x0A, 0x00, 0x39,
  //   0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x0A, 0x00 };
  //char messageBuf[4] = { 'T', 'e', 's', 't' };
  DWORD  sizeBuf = sizeof(*messageBuf);
  DWORD  numBytesBuf = 0;               // Stores the number of bytes written using WriteFile

  Status = WriteFile(handleCom,
              messageBuf,
              messageBufSize,
              &numBytesBuf,
              NULL);
  
  if (Status == FALSE) {
    printf("Error %d in WriteFile \n\n", GetLastError());
    system("pause");
    exit(0);
  }
  else {
    //printf("\n Message sent to %s: %c \n", PortName, messageBuf[0]);
  }

/*---------------------- Receive ----------------------*/

  printf("Receiving...\n\n");
  DWORD dwEventMask;
  char  ReadData;
  DWORD NoBytesRead;
  char* SerialBuffer = (char*)calloc(0, sizeof(char));
  unsigned char count = 0;

  // Mask
  Status = SetCommMask(handleCom, EV_RXCHAR);
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
  printf("---Character Count---\n%d", count);

  int index = 0;

  // Print as ASCII characters
  printf("\n\n---ASCII---\n");
  for (index = 0; index < count; index++)
  {
    printf("%c", *(SerialBuffer + index));
  }
  printf("\n");

  // Print as hex
  printf("---Hex---\n");
  for (index = 0; index < count; index++)
  {
    printf("0x%02x ", (unsigned char)SerialBuffer[index]);
  }
  printf("\n");


/*---------------------- Close ----------------------*/

  CloseHandle(handleCom);

  return 0;
}
