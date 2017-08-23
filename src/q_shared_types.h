#pragma once

#define HOMEPATH_NAME_UNIX ".callofduty4"
#define HOMEPATH_NAME_WIN		"CallofDuty4"
#define HOMEPATH_NAME_MACOSX		HOMEPATH_NAME_WIN

#define	MAX_STRING_TOKENS	1024	// max tokens resulting from Cmd_TokenizeString
#define	MAX_STRING_CHARS	1024

#define MAX_OSPATH 256
#define	MAX_INFO_STRING		1024
#define	MAX_INFO_KEY		1024
#define	MAX_INFO_VALUE		1024
#define	MAX_TOKEN_CHARS		1024

#define	MAX_NAME_LENGTH		16	// max length of a client name
#define	MAX_QPATH		64	// max length of a quake game pathname

#define	BIG_INFO_STRING		8192  // used for system info key only
#define	BIG_INFO_KEY		8192
#define	BIG_INFO_VALUE		8192

#define TRUNCATE_LENGTH	64

#define NET_WANT_READ -0x7000
#define NET_WANT_WRITE -0x7001
#define NET_CONNRESET -0x7002
#define NET_ERROR -0x7003

#define MAXPRINTMSG 4096
#define	MAX_RELIABLE_COMMANDS	128	// max string commands buffered for restransmit
#define MAX_DOWNLOAD_WINDOW	8	// max of eight download frames
#define MAX_DOWNLOAD_BLKSIZE	2048	// 2048 byte block chunks
#define MAX_PACKET_USERCMDS	32

#define	PACKET_BACKUP		32
#define PACKET_MASK ( PACKET_BACKUP - 1 )

#define Q3CONFIG_CFG "q3config_server.cfg"

#define cod4xpem "-----BEGIN PUBLIC KEY-----\n\
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwu8nEsLD4sTP+Py30Fnq\n\
UOlgZZrGb7aIiQhn8iXAXXuhLC0pKOQ2drq3KWMbHeiNSAaxI2TGRirYCiZETnkX\n\
WCt0NxvrGtbvbsDHBaVju/5X9CiyJBFr+YFhZ8RK/UH8KxMqIAlvN5f3H30rPqwB\n\
QlI+scIXp5ZrFt97zaYw4czpWod4iZVm4O8fNJJAFq9qR2yxVyKaP7DZr3wZEt1+\n\
WJrOmkWPYkNC/YC1qnY35ubDAS7vZPvPtmw4oeJKSsTFwR5ddKMiLvPzRW3KgpT1\n\
B4zHBTO1xOKTYvEQqJqspz1ELUeSPemEYmZEZdakVLDKyzPZ5+a0WR4q3pDtmrZG\n\
KwIDAQAB\n\
-----END PUBLIC KEY-----"

typedef unsigned char byte;
typedef enum qboolean
{
    qfalse,
    qtrue
} qboolean;

typedef int fileHandle_t;
typedef unsigned int clipHandle_t;
typedef int scr_entref_t;

typedef unsigned short uint16_t;
