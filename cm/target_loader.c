//======================= Inspired by =======================//
// www.xanthium.in
// Copyright (C) 2014 Rahul.S
// https://github.com/xanthium-enterprises/Serial-Programming-Win32API-C
//===========================================================//

#include<windows.h>
#include<stdio.h>
#include <string.h>
#include "vm.h"
#include "command_types.h"
#include "windows_comm.h"

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

static struct ReadBuffer loadObjFile(FILE* f) {
    u16 n, size = 0;
    u8  buf[2];

    buf[0] = (u8)fgetc(f);
    buf[1] = (u8)fgetc(f);
    struct ReadBuffer readTargetBuffer;
    u8* messageBuf = (u8*)calloc(0, sizeof(u8));
    messageBuf = realloc(messageBuf, sizeof(u8) + 1);
    *(messageBuf) = buf[0];
    *(messageBuf + 1) = buf[1];
    size = (u16)((buf[0] << 8) | buf[1]) + 2; // Include first two bytes

    for (n = 2; n < size+2; n++) {
        messageBuf = realloc(messageBuf, sizeof(u8) + n);
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
    readTargetBuffer.buffer = messageBuf;
    readTargetBuffer.size = size;
    return readTargetBuffer;
}

struct ReadBuffer readFile(char* argv) {
  FILE* file;
  char  filename[200];
  const char* name;
  const char* ext;
  struct ReadBuffer readTargetBuffer;
  readTargetBuffer.size = 0;

  char *pfile;

  strcpy(filename, argv);
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
          return readTargetBuffer;
      }
      readTargetBuffer = loadObjFile(file);
      u16 size = readTargetBuffer.size;
      if (size) {
        printf("Successfully read program file.\n");
        return readTargetBuffer;
      }
  } else {
      printf("Error: Must have a file with '.exe' extension.\n");
      return readTargetBuffer;
  }

}

void printUsage() {
  printf("Options: \n");
  printf("-send <filename>\t Send and run program on target.\n");
}

void printReadBuffer(struct ReadBuffer receiveBuffer) {
  char* buffer = receiveBuffer.buffer;
  int bufferSize = receiveBuffer.size;
  printf("---Character Count---\n%d", bufferSize);

  int index = 0;

  // Print as ASCII characters
  printf("\n\n---ASCII---\n");
  for (index = 0; index < bufferSize; index++)
  {
    printf("%c", *(buffer + index));
  }
  printf("\n");

  // Print as hex
  printf("---Hex---\n");
  for (index = 0; index < bufferSize; index++)
  {
    printf("0x%02x ", (unsigned char)buffer[index]);
  }
  printf("\n");
}




int main(int argc, char* argv[]) {
  
  if (argc == 1) {
    printUsage();
  }
  else {
    if (!strcmp(argv[1], "-send")) {
      if (argc < 3) {
        printf("Must specify .exe filename to send.\n");
        return 0;
      }
      
      /*---------------------- Read .exe Program File ----------------------*/

      struct ReadBuffer readTargetBuffer = readFile(argv[2]);
      byte* messageBuf = readTargetBuffer.buffer;
      u16 messageBufSize = readTargetBuffer.size;
      if (messageBufSize <= 0) {
        return 0;
      }
      printf("Program file size: %u bytes\n", messageBufSize);

      /*---------------------- Setup Communication ----------------------*/
      
      HANDLE handleCom = setupCommunication();

      /*---------------------- Send Program ----------------------*/

      sendToTarget(handleCom, messageBuf, messageBufSize);

      /*---------------------- Print Received ----------------------*/

      struct ReadBuffer receiveBuffer = receiveFromTarget(handleCom);
      printReadBuffer(receiveBuffer);

      /*---------------------- Close ----------------------*/

      CloseHandle(handleCom);

    }
    else {
      printUsage();
    }
  }
  
  return 0;
}
