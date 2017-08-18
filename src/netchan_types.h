#pragma once
#include "sys_net_types.h"

#define NETCHAN_UNSENTBUFFER_SIZE 0x20000
#define NETCHAN_FRAGMENTBUFFER_SIZE 0x800

#define MAX_PACKETLEN 1400 // max size of a network packet
#define FRAGMENT_SIZE (MAX_PACKETLEN - 100)

typedef struct reliableCommands_t
{
    char command[MAX_STRING_CHARS];
    int cmdTime;
    int cmdType;
} reliableCommands_t;

typedef struct netchan_t
{
    // sequencing variables
    int outgoingSequence;
    netsrc_t sock;
    int dropped; // between last packet and previous
    int incomingSequence;

    //Remote address
    netadr_t remoteAddress; // (0x10)
    unsigned short qport;   // qport value to write when transmitting (0x24)
    unsigned short upperqport;
    // incoming fragment assembly buffer
    int fragmentSequence;
    int fragmentLength;
    byte *fragmentBuffer; // Old: (0x30)
    int fragmentBufferSize;

    // outgoing fragment buffer
    // we need to space out the sending of large fragmented messages
    qboolean unsentFragments;
    int unsentFragmentStart;
    int unsentLength;
    byte *unsentBuffer; //Old: (0x44)
    int unsentBufferSize;
} netchan_t;
