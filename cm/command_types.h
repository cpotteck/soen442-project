
#ifndef __command_types
#define __command_types

#define ACK 0xCC
#define NAK 0x33

typedef enum {
  PING = 0x20,
  DOWNLOAD,
  RUN,
  GET_STATUS,
  SEND_DATA,
  RESET
};

struct ReadTargetBuffer {
  char* buffer;
  u8 size;
};

#endif