#ifndef STD_H
#define STD_H

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

#endif

#ifndef WIN32_CLIENT
#define WIN32_CLIENT

    #include <winsock2.h>

#endif

#ifndef COM_H
#define COM_H

#include "common.h"

#endif

#define SERVER_PORT 5208 //�����˿�

void startWin32Client();