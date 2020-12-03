
#ifndef __command_types
#define __command_types

#define ACK 0xCC
#define NAK 0x33

#define PING 0x20
#define DOWNLOAD 0x21
#define RUN 0x22
#define GET_STATUS 0x23
#define SEND_DATA 0x24
#define RESET 0x25

struct ReadTargetBuffer {
  char* buffer;
  u8 size;
};

#endif