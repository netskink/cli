#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "parser.h"
#include "main.h"

//http://rabbit.eng.miami.edu/class/een218/getchar.html


char * ReadLine(char *) ;


int prompt(void) {



	char *pchLineBuffer;
	int iRC=1;

	printf("-> ");
	pchLineBuffer = (char *)malloc(80);
	ReadLine(pchLineBuffer);
	//printf("%s",pchLineBuffer);
	iRC = process_line(pchLineBuffer);
	free(pchLineBuffer);

	return iRC;

//#define foo
#ifdef foo
	int bytes_read;
	char *buffer;
	int buff_size = 4;

	printf("-> ");
    //ssize_t read(int fildes, void *buf, size_t nbyte);
	buffer = malloc(buff_size);

    //bytes_read = read(STDIN_FILENO, buffer, buff_size);
	//while((n = read(STDIN_FILENO, buff, BUFSIZ)) > 0)	
	//bytes_read = read(stdin, buffer, buff_size);	
	//while ((bytes_read = read(0, buffer, buff_size)) > 0)
	bytes_read = read(0, buffer, buff_size);
	printf("%s \n",buffer);
	return bytes_read;
#endif

#ifdef goo
	char line[1024];  /* Generously large value for most situations */

	char *eof;

	printf("-> ");
	line[0] = '\0'; /* Ensure empty line if no input delivered */
	line[sizeof(line)-1] = ~'\0';  /* Ensure no false-null at end of buffer */

	eof = fgets(line, sizeof(line), stdin);
	return 1;
#endif

} 


char * ReadLine(char *pchLineBuffer) { 
	char *pchChar;
	while (1) { 
		int c = getchar();
		if (c=='\n' || c==EOF) break;
		pchChar = (char *)&c;
		pchLineBuffer= (char *)strncat(pchLineBuffer,pchChar,79); 	
	}
	return pchLineBuffer; 
}
