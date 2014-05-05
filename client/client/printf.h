#ifndef _PRINTF_H_
#define _PRINTF_H_

int LOGString(
    FILE    *stream,
	char* source, 
	char *desc, 
	int type,
	int iInFile,
    const char *format,
    ...);

#define LEVELFERTERROR		31
#define LEVELFERTCOMMON		38
#define LEVELFERTPACKET		39

#define LEVELSERVERERROR	41
#define LEVELSERVERCOMMON	48
#define LEVELSERVERPACKET	49

#define LEVELINPUTERROR		43
#define LEVELINPUTCOMMON	44
#define LEVELINPUTPACKET	45

#define LEVELCMPPCOMMON		59
#define LEVELCMPPCOMMONERR	55
#define LEVELCMPPCONNERR	52

#define LEVELSGIPCOMMON		69
#define LEVELSGIPCOMMONERR	65
#define LEVELSGIPCONNERR	62

#define LEVELCNGPCOMMON		79
#define LEVELCNGPCOMMONERR	75
#define LEVELCNGPCONNERR	72

#define LEVELDBCOMMON		89
#define LEVELDBERROR		82
#endif