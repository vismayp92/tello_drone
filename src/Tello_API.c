/*
 ****************************************************
 * Author	:	Vismay Patel						*
 * Created	:	18th October, 2021.					*
 * Website	:	https://github.com/vismayp92		*
 * Email	:	patelvismay92@gmail.com				*
 *													*
 * About:											*
 * This is the free to share and use source code.	*
 ****************************************************
 */

/* Tello C API Source Code
 * Utilising Tello SDK commands over UDP port(s) */

#include "Tello_API.h"

static int isTelloReady = 0;
static int sock1 = -1, sock2 = -1;
static struct sockaddr_in serv1_addr, serv2_addr;

/* Function: Tello_Init
 * Initializes UDP sockets for communication
 * must be called first before utilising any of APIs
 * returns: 0 for success, non-zero otherwise
 */
int Tello_Init(void) {
	int ret;
	char telloBuf[MAX_DATA_LEN];
	struct timeval telloTimeout = {TELLO_ACK_TIMEOUT,0};

	if(isTelloReady) {
		return 0;
	}

	/* Setup main command send/receive Port 8889 */
	sock1 = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock1 < 0) {
		return sock1;
	}
	ret = setsockopt(sock1, SOL_SOCKET, SO_RCVTIMEO, &telloTimeout, sizeof(telloTimeout));
	if(ret < 0) {
		Tello_Cleanup();
		return ret;
	}
	memset(&serv1_addr, 0, sizeof(serv1_addr));
	serv1_addr.sin_family = AF_INET;
	serv1_addr.sin_port = htons(TELLO_UDP_TX_PORT);
	serv1_addr.sin_addr.s_addr = inet_addr(TELLO_WLAN_IP);

	isTelloReady = 1;

	ret = Tello_Send_Command("command", telloBuf);
	if(ret < 0) {
		Tello_Cleanup();
		return ret;
	}

	if(!strcmp(telloBuf,"error")) {
		Tello_Cleanup();
		return -EBUSY;
	}

	/* Setup data state listener Port 8890 */
	sock2 = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock2 < 0) {
		Tello_Cleanup();
		return sock2;
	}
	ret = setsockopt(sock2, SOL_SOCKET, SO_RCVTIMEO, &telloTimeout, sizeof(telloTimeout));
	if(ret < 0) {
		Tello_Cleanup();
		return ret;
	}
	memset(&serv2_addr, 0, sizeof(serv2_addr));
	serv2_addr.sin_family = AF_INET;
	serv2_addr.sin_port = htons(TELLO_UDP_RX_PORT);
	serv2_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(sock2, (const struct sockaddr *)&serv2_addr, sizeof(serv2_addr));
	if(ret < 0) {
		Tello_Cleanup();
		return ret;
	}

	return 0;
}

/* Function: Tello_Send_Command
 * sends the given command to Tello Aircraft
 * param @tellocmd: command to send
 * param @telloreply: response from Tello Aircraft is received here,
 * 			   		  to be allocated by the user,
 * 			   		  a pointer to 1024 bytes of memory
 * returns: zero or greater in success, negative otherwise
 */
int Tello_Send_Command(const char * tellocmd, char * telloreply) {
	int addr_len, recv_len;
	struct sockaddr_in serv1_resp_addr;

	if(!isTelloReady)
		return -1;

	sendto(sock1, tellocmd, strlen(tellocmd),
			MSG_CONFIRM, (const struct sockaddr *) &serv1_addr,
			sizeof(serv1_addr));

	addr_len = sizeof(serv1_resp_addr);

	recv_len = recvfrom(sock1, telloreply, MAX_DATA_LEN,
				MSG_WAITALL, (struct sockaddr *) &serv1_resp_addr,
				&addr_len);
	if(recv_len >= 0)
			telloreply[recv_len] = '\0';
	return recv_len;
}

/* Function: Tello_Get_State
 * requests Data state from Tello Aircraft
 * param @tellodata: data state report from Tello Aircraft is received here,
 * 			  		 to be allocated by the user,
 * 			  		 a pointer to 1024 bytes of memory
 * returns: zero or greater in success, negative otherwise
 */
int Tello_Get_State(char * tellodata) {
	int addr_len, recv_len;
	struct sockaddr_in cl2_addr;

	if(!isTelloReady)
		return -1;

	memset(&cl2_addr, 0, sizeof(cl2_addr));
	addr_len = sizeof(cl2_addr);

	recv_len = recvfrom(sock2, tellodata, MAX_DATA_LEN,
				MSG_WAITALL, (struct sockaddr *) &cl2_addr,
				&addr_len);
	if(recv_len >= 0)
			tellodata[recv_len] = '\0';
	return recv_len;
}

/* Function: Tello_Cleanup
 * Terminates the UDP connections to Tello and releases resources
 * must be called before quitting the app */
void Tello_Cleanup(void) {
	if(sock2 > 0)
		close(sock2);
	if(sock1 > 0)
		close(sock1);
	sock1 = -1; sock2 = -1;
	isTelloReady = 0;
}
