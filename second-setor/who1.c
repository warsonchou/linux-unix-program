#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
//first version who program

#define SHOWHOST //inlcude remote machine on output
void show_info(struct utmp *);

int main(int argc, char const *argv[])
{
	struct utmp current_record; //read hteinfo into here
	int utmfd;                 //read from this descriptor
	int reclen = sizeof(current_record);

	if ((utmfd = open(UTMP_FILE,  O_RDONLY)) == -1) {
		perror(UTMP_FILE); //uUTMP_FILE is in utmp.h
		exit(1);
	}

	while (read(utmfd, &current_record, reclen)) {
		show_info(&current_record);
		close(utmfd);
	}
	return 0;
}

/*show_info()
displays contents of the struct in human form 
*/
void show_info(struct utmp * utbufp) {
	printf("%-8.8s", utbufp->ut_user); //the username
	printf(" "); //space
	printf("%-8.8s", utbufp->ut_line); //the tty
	printf(" "); //space
	printf("% 10d", utbufp->ut_time); //the time
	printf(" "); //space
	#ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host); //teh log
	#endif
	printf("\n"); //teh log
}