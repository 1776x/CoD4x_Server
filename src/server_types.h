#pragma once
////////////////////////////////////////////////
// This file contains types used in server.h. //
////////////////////////////////////////////////

// MAX_CHALLENGES is made large to prevent a denial
// of service attack that could cycle all of them
// out before legitimate users connected
#define	MAX_CHALLENGES	1024
// Allow a certain amount of challenges to have the same IP address
// to make it a bit harder to DOS one single IP address from connecting
// while not allowing a single ip to grab all challenge resources
#define MAX_CHALLENGES_MULTI (MAX_CHALLENGES / 2)

/* 7472 */
typedef struct
{
  int svFlags;
  int clientMask[2];
  vec3_t absmin;
  vec3_t absmax;
}archivedEntityShared_t;

/* 7473 */
typedef struct archivedEntity_s
{
  entityState_t s;
  archivedEntityShared_t r;
}archivedEntity_t;

typedef enum {
    UN_VERIFYNAME,
    UN_NEEDUID,
    UN_OK
}username_t;
#pragma pack(1)


/*
typedef struct {
	netadr_t		adr;
	int			challenge;
	int			clientChallenge;
	int			time;				// time the last packet was sent to the autherize server
	int			pingTime;			// time the challenge response was sent to client
	int			firstTime;			// time the adr was first used, for authorize timeout checks
	char			pbguid[33];
	qboolean		connected;
	int			ipAuthorize;
} challenge_t;
*/

#define	MAX_STREAM_SERVERS	6
#define	MAX_MASTER_SERVERS	2	// max recipients for heartbeat packets
// this structure will be cleared only when the game dll changes


typedef struct{
int	challengeslot;
int	firsttime;
int	lasttime;
int	attempts;
}connectqueue_t;	//For fair queuing players who wait for an empty slot

#define MAX_TRANSCMDS 32
typedef struct{
	char cmdname[32];
	char cmdargument[1024];
}translatedCmds_t;

/*

Some Info:
svs.nextSnapshotEntities 0x13f18f94
svs.numSnapshotEntites 0x13f18f8c
svc_snapshot = 6;
svs.snapflagServerbit 0x13f18f88  //copied from real svs. to something else

*/

typedef struct archivedSnapshot_s
{
  int start;
  int size;
}archivedSnapshot_t;

typedef struct cachedSnapshot_s
{
  int archivedFrame;
  int time;
  int num_entities;
  int first_entity;
  int num_clients;
  int first_client;
  int usesDelta;
}cachedSnapshot_t;


typedef struct cachedClient_s
{
  int playerStateExists;
  clientState_t cs;
  playerState_t ps;
}cachedClient_t;



typedef struct
{
  int adr[5];
  int challenge;
  int time;
  int pingTime;
  int firstTime;
  int firstPing;
  qboolean connected;
  char guid[36];
}challenge2_t;

typedef struct{
	int time;
	char guid[32];
}banlist_t;


#define	MAX_SNAPSHOT_ENTITIES	1024

typedef struct {//0x8c51780

	cachedSnapshot_t cachedSnapshotFrames[512];
	archivedEntity_t cachedSnapshotEntities[16384];

	qboolean	initialized;				//0x90b4f80 sv_init has completed

	int		time;					// will be strictly increasing across level changes

	int		snapFlagServerBit;			// ^= SNAPFLAG_SERVERCOUNT every SV_SpawnServer()

	client_t	clients[MAX_CLIENTS];				// [sv_maxclients->integer];



	int		numSnapshotEntities;		//0xba0de8c sv_maxclients->integer*PACKET_BACKUP*MAX_PACKET_ENTITIES
	int		numSnapshotClients;
	int		nextSnapshotEntities;		//0xba0de94 next snapshotEntities to use
	int		nextSnapshotClients;

	entityState_t snapshotEntities[0x2A000];
	clientState_t snapshotClients[0x20000];

	int nextArchivedSnapshotFrames; //0xee95e9c

	archivedSnapshot_t archivedSnapshotFrames[1200];
	byte archivedSnapshotBuffer[0x2000000];
	int nextArchivedSnapshotBuffer;
	int nextCachedSnapshotEntities; //0x10e98420
	int nextCachedSnapshotClients;
	int nextCachedSnapshotFrames;
	cachedClient_t cachedSnapshotClients[4096];

	int nextHeartbeatTime;

	int nextStatusResponseTime;

	challenge2_t challenges[MAX_CHALLENGES];

	int redirectAddress[5];
	int authorizeAddress[5];

	char netProfilingBuf[1504];

	banlist_t banlist[16];

	int field_14850;

	vec3_t mapCenter;

	char field_14860[112];

}serverStatic_t; //Size: 0xb227580

#define MAX_CONFIGDATACACHE 4096

typedef struct {
	unsigned long long	nextHeartbeatTime;
	netadr_t		redirectAddress;			// for rcon return messages
	netadr_t		authorizeAddress;			// ??? for rcon return messages
	client_t		*redirectClient;		//used for SV_ExecuteRemoteControlCmd()
	int				secret;
	unsigned int	frameNextSecond;
	unsigned int	frameNextTenSeconds;
	connectqueue_t	connectqueue[11];
	//An array which contains a part of the update history for configdata
	int				changedConfigData[MAX_CONFIGDATACACHE];
	int				configDataSequence;
	char			commandWhitelistBuf[1024];
	char			sysrestartmessage[1024];
}serverStaticExt_t;

typedef struct {
	qboolean		cmdSystemInitialized;
	int			randint;
	translatedCmds_t	translatedCmd[MAX_TRANSCMDS];
	int			challenge;
	int			useuids;
	int			masterserver_messageid;
	int			masterServer_id;
	char			masterServer_challengepassword[33];
	netadr_t		masterServer_adr;
}permServerStatic_t;


typedef enum {
	SS_DEAD,			// no map loaded
	SS_LOADING,			// spawning level entities
	SS_GAME				// actively running
} serverState_t;




typedef struct svEntity_s {
	uint16_t worldSector;
	uint16_t nextEntityInWorldSector;
	archivedEntity_t		baseline;		// 0x04  for delta compression of initial sighting
	int			numClusters;		// if -1, use headnode instead
	int			clusternums[MAX_ENT_CLUSTERS];
	int			lastCluster;		// if all the clusters don't fit in clusternums
	int			linkcontents;
	float		linkmin[2];
	float		linkmax[2];
}svEntity_t; //size: 0x178

#define MAX_BPS_WINDOW 20

#pragma pack(push, 1)

typedef struct {//0x13e78d00
	serverState_t		state;
	int			timeResidual;		// <= 1000 / sv_frame->value
	int			frameusec;		// Frameusec set every Level-startup to the desired value from sv_fps    Replaces: byte inFrame; byte smp; byte allowNetPackets;
	qboolean		restarting;		// if true, send configstring changes during SS_LOADING
	int			start_frameTime;		//restartedServerId;	serverId before a map_restart
	int			checksumFeed;		// 0x14 the feed key that we use to compute the pure checksum strings
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=475
	// the serverId associated with the current checksumFeed (always <= serverId)
/*	int			checksumFeedServerId;
	int			snapshotCounter;	// incremented for each snapshot built

	int			nextFrameTime;		// when time > nextFrameTime, process world
	struct cmodel_s		*models[MAX_MODELS];*/
	byte			unk[0x800];

	uint16_t			emptyConfigString;		//0x13e79518
	uint16_t			configstrings[MAX_CONFIGSTRINGS]; //(0x13e7951a)

	short			unk3; //0x13e7a82e
	svEntity_t		svEntities[MAX_GENTITIES]; //0x1b30 (0x13e7a830) size: 0x5e000

	// the game virtual machine will update these on init and changes
	gentity_t		*gentities;	//0x5fb30  (0x13ed8830)
	int			gentitySize;	//0x5fb34  (0x13ed8834)
	int			num_entities;		// current number, <= MAX_GENTITIES

	playerState_t		*gameClients;		//0x5fb3c
	int			gameClientSize;		//0x5fb40 (13ed8840)will be > sizeof(playerState_t) due to game private data
/*
	int				restartTime;
	int				time;*/

	int			skelTimeStamp;
	int			skelMemPos;
	int			bpsWindow[MAX_BPS_WINDOW];
	int			bpsWindowSteps;
	int			bpsTotalBytes;
	int			bpsMaxBytes;
	int			ubpsWindow[MAX_BPS_WINDOW];
	int			ubpsTotalBytes;
	int			ubpsMaxBytes;
	float		ucompAve;
	int			ucompNum;
	char		gametype[MAX_QPATH]; //(0x13ed8908)
	byte		killserver;
	byte		pad3[3];
	const char* killreason;
} server_t;//Size: 0x5fc50

#pragma pack(pop)


typedef struct{//13F18F80
	client_t	*clients;
	int			time;
	int			snapFlagServerBit;// ^= SNAPFLAG_SERVERCOUNT every SV_SpawnServer()
	int			numSnapshotEntities;	//0x13f18f8c sv_maxclients->integer*PACKET_BACKUP*MAX_PACKET_ENTITIES
	int			numSnapshotClients;
	int			nextSnapshotEntities;	//0x13f18f94 next snapshotEntities to use
	int			nextSnapshotClients;	//0x13f18f98
	entityState_t	*snapshotEntities;	//0x13f18f9c
	clientState_t	*snapshotClients;	//0x13f18fa0
	svEntity_t		*svEntities;		//0x13f18fa4

	vec3_t mapCenter;
	archivedEntity_t *cachedSnapshotEntities;
	cachedClient_t *cachedSnapshotClients;
	byte *archivedSnapshotBuffer;
	cachedSnapshot_t *cachedSnapshotFrames;
	int nextCachedSnapshotFrames;
	int nextArchivedSnapshotFrames;
	int nextCachedSnapshotEntities;
	int nextCachedSnapshotClients;
	int num_entities;
	int maxClients;
	int fps;
	qboolean canArchiveData;
	gentity_t *gentities;
	int gentitySize;
	clientState_t *gclientstate;
	gclient_t *gplayerstate;
	int gclientSize;

}svsHeader_t;



typedef struct
{
  int numSnapshotEntities;
  int snapshotEntities[MAX_SNAPSHOT_ENTITIES];
}snapshotEntityNumbers_t;



typedef struct
{
  const float *mins;
  const float *maxs;
  int *list;
  int count;
  int maxcount;
  int contentmask;
}areaParms_t;

/* 7561 */
struct worldContents_s
{
  int contentsStaticModels;
  int contentsEntities;
  int linkcontentsEntities;
  uint16_t entities;
  uint16_t staticModels;
};

/* 7563 */
struct worldTree_s
{
  float dist;
  uint16_t axis;
  union
  {
	uint16_t parent;
	uint16_t nextFree;
  };
  uint16_t child[2];
};

/* 7564 */
struct worldSector_s
{
  struct worldContents_s contents;
  struct worldTree_s tree;
};

/* 7565 */
struct cm_world_t
{
  float mins[3];
  float maxs[3];
  uint16_t freeHead;
  uint16_t gap;
  struct worldSector_s sectors[1024];
};




typedef struct
{
  //Player banned
  char playername[33];
  uint64_t steamid;
  uint64_t playerid;
  netadr_t adr;

  //Admin who did ban
  char adminname[33];
  uint64_t adminsteamid;

  //Details about the ban
  char message[1024];
  time_t expire;
  unsigned int duration; //minutes
	time_t created;
}baninfo_t;
