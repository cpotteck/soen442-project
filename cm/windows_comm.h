
#ifndef __windows_comm_h
#define __windows_comm_h

#include <windows.h>
#include "command_types.h"

HANDLE setupCommunication();
struct ReadBuffer receiveFromTarget(HANDLE handleCom);
void sendToTarget(HANDLE handleCom, byte* sendBuffer, i32 sendSize);

#endif