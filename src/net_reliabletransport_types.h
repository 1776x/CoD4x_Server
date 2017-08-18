#pragma once
#include "sys_net_types.h"
#include "msg_types.h"

#define MAX_PACKETLEN 1400 // max size of a network packet
#define MAX_FRAGMENT_SIZE (MAX_PACKETLEN - 200)

typedef struct fragment_t
{
    byte data[MAX_FRAGMENT_SIZE];
    int len;
    int ack;
    int packetnum;
    int senttime;
} fragment_t;

typedef struct rateTracker_t
{
    int nextRateCntTime; //Used by bytesPerSecond to know when to calculate the current rate
    //This counts only the sent bytes
    int bytes;
    int lastBytesSnap;
    int bytesPerSec;
    //This counts overhead like headers and retransmissions as well
    int bytesTotal;
    int lastBytesSnapTotal;
    int bytesPerSecTotal;
} rateTracker_t;

typedef struct framedata_t
{
    int sequence;     //Highest numbered packet in queue
    int bufferlen;    //Length of the whole buffer
    int acknowledge;  //Lowest numbered packet in queue
    int selackoffset; //Used to send not always the same selective acknowledges
    int frame;        //Current numbered packet which is going to be sent next. Any value in range of acknowledge and sequence
    int windowsize;   //Current size of our window
    fragment_t *fragments;
    int packets;
    msg_t fragmentbuffer;
    byte fragmentdata[MAX_FRAGMENT_SIZE];
    rateTracker_t rateInfo;
    int unsentmillipackets;
} framedata_t;

typedef struct netreliablemsg_t
{
    framedata_t txwindow;
    framedata_t rxwindow;
    int sock;
    netadr_t remoteAddress;
    int time;
    int nextacktime;
    int qport;
} netreliablemsg_t;
