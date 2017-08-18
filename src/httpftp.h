/*
 *  httpftp.h
 *
 */
#ifndef _HTTPFTP_H_
#define _HTTPFTP_H_

#include "q_shared.h"
#include "msg.h"
#include "sys_net.h"
#include "httpftp_types.h"

int HTTP_SendReceiveData(ftRequest_t* request);
void FileDownloadFreeRequest(ftRequest_t* request);
ftRequest_t* FileDownloadRequest( const char* url);
int FileDownloadSendReceive( ftRequest_t* request );
const char* FileDownloadGenerateProgress( ftRequest_t* request );
void HTTPServer_Init();
ftRequest_t* HTTPRequest(const char* url, const char* method, msg_t* msg, const char* additionalheaderlines);
qboolean HTTP_BuildNewRequest( ftRequest_t* request, const char* method, msg_t* msg, const char* additionalheaderlines);
void HTTP_DecodeURLFormData(char* url);
void HTTP_DecodeURL(char* url);
void HTTP_CreateString_x_www_form_urlencoded(char* outencodedstring, int len, const char* key, const char *value);
void HTTP_ParseFormDataBody(char* body, httpPostVals_t* values);
const char* HTTP_GetFormDataItem(httpPostVals_t* values, const char* search);


#endif
