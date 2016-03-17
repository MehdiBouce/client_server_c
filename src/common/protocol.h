#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef enum PROTOCOL_MESSAGE p_msg;
enum PROTOCOL_MESSAGE
{
  BEGIN,
  CLOSE,
  ACK,
  REQ,
  WAIT,
  END,
  REFUSE,
  INIT
};

#endif
