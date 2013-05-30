#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "io.h"
#include "main.h"

int main(int argc, char *argv[]) {

	int iRC;
//	char *str1, *token;
//	char *str2, *subtoken;
//	char *saveptr1;
//	char *saveptr2;
//	int j;
	
//	char **words;
//	int word_cnt;

	//printf("argc = %d\n",argc);
	iRC=EXIT_SUCCESS;

//	if (argc != 4) {
//		fprintf(stderr, "Usage: %s string delim subdelim\n",
//	if (argc != 3) {
//		fprintf(stderr, "Usage: %s string delim \n",
	if (argc != 1) {
		fprintf(stderr, "Usage: %s \n",
		argv[0]);
		iRC=EXIT_FAILURE;
		exit(iRC);
	}

//	words=malloc(15*8);  // 15 word pointers. pointers are 64-bit
//	bzero(words,15*8);
//	word_cnt=0;

	build_cmd_list();

	while(1) { 
		if (prompt()) break;
	}


//	for (j = 1, str1 = argv[1]; ; j++, str1 = NULL) {
//		token = strtok_r(str1, argv[2], &saveptr1);
//		if (token == NULL)
//			break;

		// We have a word. What type of word.
		//printf("%d: %s\n", j, token);
//		words[word_cnt]=(char *) malloc(strlen(token)+1);
//		strcpy(words[word_cnt++],token);


//		for (str2 = token; ; str2 = NULL) {
//			subtoken = strtok_r(str2, argv[3], &saveptr2);
//			if (subtoken == NULL)
//				break;
//			printf(" --> %s\n", subtoken);
//		}
//	}




	exit(iRC);

}

void unit_test(char **words, int word_cnt) {
//	dump_words(words,word_cnt);
//	dump_cmd_list();
	parse_words(words,word_cnt);
}


