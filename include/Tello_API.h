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

/* Tello C API Header file
 * Model: Tello TLW004
 */

#ifndef tello_h__
#define tello_h__

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ifaddrs.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/* Tello Aircraft WLAN IP */
#define TELLO_WLAN_IP "192.168.10.1"

/* Tello Send Command port */
#define TELLO_UDP_TX_PORT 8889

/* Tello Recieve State port */
#define TELLO_UDP_RX_PORT 8890

/* Tello Response timeout (seconds) (based on tests) */
#define TELLO_ACK_TIMEOUT 10

/* Estimated based on Tello SDK commands Ref */
#define MAX_CMD_LEN 100

/* Define max data length bytes */
#define MAX_DATA_LEN 1024

/* Function: Tello_Init
 * Initializes UDP sockets for communication
 * must be called first before utilising any of APIs
 * returns: 0 for success, non-zero otherwise
 */
int Tello_Init(void);

/* Function: Tello_Send_Command
 * sends the given command to Tello Aircraft
 * param @tellocmd: command to send
 * param @telloreply: response from Tello Aircraft is received here,
 * 			   		  to be allocated by the user,
 * 			   		  a pointer to 1024 bytes of memory
 * returns: zero or greater in success, negative otherwise
 */
int Tello_Send_Command(const char * tellocmd, char * telloreply);

/* Function: Tello_Get_State
 * requests Data state from Tello Aircraft
 * param @tellodata: data state report from Tello Aircraft is received here,
 * 			  		 to be allocated by the user,
 * 			  		 a pointer to 1024 bytes of memory
 * returns: zero or greater in success, negative otherwise
 */
int Tello_Get_State(char * tellodata);

/* Function: Tello_Cleanup
 * Terminates the UDP connections to Tello and releases resources
 * must be called before quitting the app */
void Tello_Cleanup(void);

#endif //tello_h__
