/*
 ****************************************************
 * Author	:	Vismay Patel
 * Created	:	18th October, 2021.
 * Website	:	https://github.com/vismayp92
 * Email	:	patelvismay92@gmail.com
 *
 * About:
 * This is the free to share and use source code.
 ****************************************************
 */

/* Tello TLW004 interactive test application */

#include "Tello_API.h"

void telloTerminal(void) {
	int ret;
	char telloCommand[MAX_CMD_LEN];
	char telloResponse[MAX_DATA_LEN];

	while(1) {
		printf("TelloTLW004:/ # ");
		fgets(telloCommand, MAX_CMD_LEN, stdin);
		telloCommand[strlen(telloCommand) - 1] = '\0';
		if(telloCommand[0] == '\0') {
			continue;
		}
		else if(!strcmp(telloCommand, "exit")) {
			Tello_Cleanup();
			break;
		}
		else if(!strcmp(telloCommand, "getdataset")) {
			ret = Tello_Get_State(telloResponse);
		}
		else {
			ret = Tello_Send_Command((const char *)telloCommand, telloResponse);
		}
		if(ret < 0)
			printf("Command failed: %s\n", telloResponse);
		else
			printf("%s\n", telloResponse);
	}
}

int main() {
	int ret;
	printf("INFO: Initializing Tello Communication Sockets ...\n");
	ret = Tello_Init();
	if(ret) {
		printf("ERROR: Socket failed or Tello Aircraft reported error!\n");
		return ret;
	}
	printf("SUCCESS: Tello Terminal Ready\n");
	telloTerminal();
	return 0;
}
