#include <unistd.h>
#include <fcntl.h>
#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//first version who program

#define SHOWHOST //inlcude remote machine on output
void show_info(struct utmp *);
void showtime(long);

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
	
	// if (utbufp->ut_type != USER_PROCESS) //user only 
	// 	return; //to do why i coulc not get current user and just get some system inline user
	printf("%-8.8s", utbufp->ut_user); //the username
	printf(" "); //space
	printf("%-8.8s", utbufp->ut_line); //the tty
	printf(" "); //space
	// printf("% 10d", utbufp->ut_time); //the time
	showtime(utbufp->ut_time);
	printf(" "); //space
	#ifdef SHOWHOST
	if (utbufp->ut_host[0] != '\0')
		printf("(%s)", utbufp->ut_host); //teh log
	#endif
	printf("\n"); //teh log
}

void showtime(long timeval)  {//display hte time in a format firt for human consumption
	char *cp; // hold the first address of time
	cp = ctime(&timeval); //covert the time to string like mon fed 4:00:46:40 est 1991/
	
	printf("%12.12s", cp);	
}