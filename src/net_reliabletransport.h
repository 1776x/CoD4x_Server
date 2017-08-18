#include "msg.h"
#include "net_reliabletransport_types.h"

void ReliableMessagesFrame(netreliablemsg_t *chan, int msec);
void ReliableMessagesReceiveNextFragment(netreliablemsg_t *chan, msg_t* buf);
int ReliableMessageReceive(netreliablemsg_t *chan, byte* outdata, int len);
int ReliableMessageReceiveSingleFragment(netreliablemsg_t *chan, byte* outdata, int len);
int ReliableMessageSend(netreliablemsg_t *chan, byte* indata, int len);
netreliablemsg_t* ReliableMessageSetup(int qport, int netsrc, netadr_t* remote);
void Net_TestingFunction(netreliablemsg_t *chan);
void ReliableMessageDisconnect(netreliablemsg_t *chan);
