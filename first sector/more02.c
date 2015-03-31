#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();
int main(int ac, char *av[]) {
	FILE *fp;
	if (ac == 1)
		do_more(stdin);
	else
		while (--ac)
	       if ((fp = fopen(*(av + 1), "r")) != NULL) {
	       	do_more(fp);
	       	fclose(fp);
	       } else {
	       	exit(1);
	       }
    return 0;
}

/*
print message wait for response return # of lines to advance
and q means no space mean yes CR means one line
*/
int see_more(FILE* cmd) {          //new accepts arg
	int c;
	printf("\033[7m more? \033[m");
	while ((c = getccmd)) != EOF) { //new read form tty
		if (c == 'q')      // q is quit
			return 0;
		if (c == ' ')      // ' ' is next page
			return PAGELEN;
		if (c == '\n')     //enter is  1 line
			return 1;
	}
	return 0;
}

/*
read PAGELEN lines, then call see_more() for further instructions
*/
void do_more(FILE* fp) {
	char line[PAGELEN];
	int num_of_line = 0;
	int reply, see_more(FILE*);
	FILE* fp_tty;
	fp_tty = fopen("/dev/tty", "r");  //new cmd stream
	if (fp_tty == NULL)               //if open fails
		exit(1);                      //no use in use
	while (fgets(line, LINELEN, fp)) { //more input
		if (num_of_line == PAGELEN) { //full screen?
			reply = see_more(fp_tty);       //y:ask user
			if (reply == 0)           //no done
				break;
			num_of_line -= reply;
		}
		if (fputs(line, stdout) == EOF) //show line
			exit(1);                //or die
		num_of_line++;              //count it
	}
}