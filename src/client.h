#pragma once
#include "netchan_types.h"
#include "filesystem_types.h"
#include "g_hud_types.h"
#include "msg_types.h"
#include "net_reliabletransport_types.h"
#include "q_shared_types.h"
#include "gentity.h"
#include "q_math_types.h"
#include "player.h"

typedef enum clientConnectState_t {
    CS_FREE,      // can be reused for a new connection
    CS_ZOMBIE,    // client has been disconnected, but don't reuse
                  // connection for a couple seconds
    CS_CONNECTED, // has been assigned to a client_t, but no gamestate yet
    CS_PRIMED,    // gamestate has been sent, but client hasn't sent a usercmd
    CS_ACTIVE     // client is fully in game
} clientConnectState_t;

typedef struct reliableprotocol_t
{
    netreliablemsg_t *netstate;
    msg_t recvbuffer;
} reliableprotocol_t;

typedef struct voices_t
{
    char num;
    char data[256];
    int dataLen;
} voices_t;

typedef struct
{
    byte bytedata[2000];
    int longdata[1547];
} statData_t;

typedef struct
{
    int checksum;
    statData_t data;
} stats_t;

typedef struct client_s
{ //90b4f8c
    clientConnectState_t state;
    int unksnapshotvar;   // must timeout a few frames in a row so debugging doesn't break
    int deltaMessage;     // (0x8) frame last client usercmd message
    qboolean rateDelayed; // true if nextSnapshotTime was set based on rate instead of snapshotMsec
    netchan_t netchan;    //(0x10)
    //DemoData
    fileHandleData_t demofile;
    qboolean demorecording;
    qboolean demowaiting;
    char demoName[MAX_QPATH];
    int demoArchiveIndex;
    int demoMaxDeltaFrames;
    int demoDeltaFrameCount;
    qboolean undercover;
    int bantime;
    int clienttimeout;
    int power;
    qboolean firstSpawn;
    game_hudelem_t *hudMsg;
    int msgType;
    unsigned int currentAd;
    int enteredWorldTime;
    byte entityNotSolid[MAX_GENTITIES / 8];  //One bit for entity  - No use
    byte entityInvisible[MAX_GENTITIES / 8]; //One bit for entity  - No use
    unsigned int clFrames;
    unsigned int clFrameCalcTime;
    unsigned int clFPS;
    float jumpHeight;
    int gravity;
    int playerMoveSpeed;
    qboolean needPassword;

    qboolean enteredWorldForFirstTime;
    unsigned int connectedTime;
    char xversion[8];
    int protocol;
    qboolean needupdate;
    qboolean updateconnOK;
    unsigned int updateBeginTime;
    reliableprotocol_t reliablemsg;
    msg_t incommingrmsg;
    uint64_t steamid;
    uint64_t steamidPending;
    uint64_t clanid;
    uint64_t clanidPending;
    uint64_t playerid;
    int steamstatus;
    int isMember; //Steam group membership.
    //If sv_steamgroup is set up this variable will be 0 if membership status is still unknown.
    //It will be -1 if he is not a member or 1 if he is a member or 2 if he is an officer
    int free1[1];
    int mutelevel; //1 = voice blocked; 2 = chat and voice blocked
    int lastFollowedClient;
    byte ssdata[24];

    char name[36];
    char clantag[16];

    char *commandWhitelist[32];

    //Free Space
    byte free[420];

    int configDataAcknowledge;     //New: to determine which config data updates the client has not yet received
    vec3_t predictedOrigin;        //0x63c
    int predictedOriginServerTime; //0x640

    const char *delayDropMsg;                                   //0x64c
    char userinfo[MAX_INFO_STRING];                             // name, etc (0x650)
    reliableCommands_t reliableCommands[MAX_RELIABLE_COMMANDS]; // (0xa50)
    int reliableSequence;                                       // (0x20e50)last added reliable message, not necesarily sent or acknowledged yet
    int reliableAcknowledge;                                    // (0x20e54)last acknowledged reliable message
    int reliableSent;                                           // last sent reliable message, not necesarily acknowledged yet
    int messageAcknowledge;                                     // (0x20e5c)
    int gamestateMessageNum;                                    // (0x20e60) netchan->outgoingSequence of gamestate
    int challenge;                                              //0x20e64
                                                                //Unknown where the offset error is
    usercmd_t lastUsercmd;                                      //(0x20e68)
    int lastClientCommand;                                      //(0x20e88) reliable client message sequence
    char lastClientCommandString[MAX_STRING_CHARS];             //(0x20e8c)
    gentity_t *gentity;                                         //(0x2128c)

    char shortname[MAX_NAME_LENGTH]; //(0x21290) extracted from userinfo, high bits masked
    int wwwDl_var01;
    // downloading
    char downloadName[MAX_QPATH];               //(0x212a4) if not empty string, we are downloading
    fileHandle_t download;                      //(0x212e4) file being downloaded
    int downloadSize;                           //(0x212e8) total bytes (can't use EOF because of paks)
    int downloadCount;                          //(0x212ec) bytes sent
    int downloadClientBlock;                    //(0x212f0) Current block we send to client
    int downloadCurrentBlock;                   //(0x212f4) current block number
    int downloadXmitBlock;                      //(0x212f8) last block we xmited
    unsigned char *dfree1[MAX_DOWNLOAD_WINDOW]; //(0x212fc) the buffers for the download blocks
    int dfree2[MAX_DOWNLOAD_WINDOW - 3];        //(0x2131c)
    int downloadBeginOffset;
    int downloadNumBytes;
    int downloadBlockSize;
    qboolean downloadEOF;            //(0x2133c) We have sent the EOF block
    int downloadSendTime;            //(0x21340) time we last got an ack from the client
    char wwwDownloadURL[MAX_OSPATH]; //(0x21344) URL from where the client should download the current file

    qboolean wwwDownload;        // (0x21444)
    qboolean wwwDownloadStarted; // (0x21448)
    qboolean wwwDlAck;           // (0x2144c)
    qboolean wwwDl_failed;
    int nextReliableTime; // (0x21454) svs.time when another reliable command will be allowed
    int floodprotect;     // (0x21458)
    int lastPacketTime;   // (0x2145c)svs.time when packet was last received
    int lastConnectTime;  // (0x21460)svs.time when connection started
    int nextSnapshotTime; // (0x21464) send another snapshot when svs.time >= nextSnapshotTime
    int timeoutCount;
    clientSnapshot_t frames[PACKET_BACKUP]; // (0x2146c) updates can be delta'd from here
    int ping;                               //(0x804ec)
    int rate;                               //(0x804f0)		// bytes / second
    int snapshotMsec;                       //(0x804f4)	// requests a snapshot every snapshotMsec unless rate choked
    int unknown6;
    int pureAuthentic;                                //(0x804fc)
    byte unsentBuffer[NETCHAN_UNSENTBUFFER_SIZE];     //(0x80500)
    byte fragmentBuffer[NETCHAN_FRAGMENTBUFFER_SIZE]; //(0xa0500)
    char legacy_pbguid[33];                           //0xa0d00
    byte pad;
    short clscriptid; //0xa0d22
    int canNotReliable;
    int serverId; //0xa0d28
    voices_t voicedata[40];
    int unsentVoiceData; //(0xa35f4)
    byte mutedClients[MAX_CLIENTS];
    byte hasVoip;       //(0xa3638)
    stats_t stats;      //(0xa3639)
    byte receivedstats; //(0xa5639)
    byte gamestateSent;
    byte hasValidPassword;
} client_t; //0x0a563c
