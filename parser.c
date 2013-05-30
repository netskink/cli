#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "main.h"

struct command *pCmdList;
const int coniNumCommands = 10;

struct variable *pVariableList;
const int coniNumVariables = 10;
int iNumVarUsed = 0;

//struct variable {
//	char *pName;
//	enum var_type_t type;
//	void *pValue;
//};




void build_cmd_list(void) {

	int i=0;

	pCmdList = (struct command *) malloc(sizeof(struct command)*coniNumCommands);
	bzero(pCmdList,sizeof(struct command)*coniNumCommands);

	pVariableList = (struct variable *) malloc(sizeof(struct variable)*coniNumVariables);
	bzero(pVariableList,sizeof(struct variable)*coniNumVariables);


#define	HELP_CMD "help"
#define	HELP_TEXT "readFile writeFile quit set echo"
	
	pCmdList[i].word = (char *)malloc(strlen(HELP_CMD)+1);
	strcpy(pCmdList[i].word,HELP_CMD);
	pCmdList[i].help_text = (char *)malloc(strlen(HELP_TEXT)+1);
	strcpy(pCmdList[i].help_text,HELP_TEXT);
	pCmdList[i].pFunc=Help;
	pCmdList[i].code = calc_crc(HELP_CMD);
	i++;
 

#define	READFILE_CMD "readfile"
#define	READFILE_TEXT "This is the readfile command."
	
	pCmdList[i].word = (char *)malloc(strlen(READFILE_CMD)+1);
	strcpy(pCmdList[i].word,READFILE_CMD);
	pCmdList[i].help_text = (char *)malloc(strlen(READFILE_TEXT)+1);
	strcpy(pCmdList[i].help_text,READFILE_TEXT);
	pCmdList[i].pFunc=ReadFile;
	pCmdList[i].code = calc_crc(READFILE_CMD);
	i++;
 

#define	WRITEFILE_CMD "writefile"
#define	WRITEFILE_TEXT "This is the writefile command."
	
	pCmdList[i].word = (char *)malloc(strlen(WRITEFILE_CMD)+1);
	strcpy(pCmdList[i].word,WRITEFILE_CMD);
	pCmdList[i].help_text = (char *)malloc(strlen(WRITEFILE_TEXT)+1);
	strcpy(pCmdList[i].help_text,WRITEFILE_TEXT);
	pCmdList[i].pFunc=WriteFile;
	pCmdList[i].code = calc_crc(WRITEFILE_CMD);
	i++;


#define	QUIT_CMD "quit"
#define	QUIT_TEXT "This is the quit command."
	
	pCmdList[i].word = (char *)malloc(strlen(QUIT_CMD)+1);
	strcpy(pCmdList[i].word,QUIT_CMD);
	pCmdList[i].help_text = (char *)malloc(strlen(QUIT_TEXT)+1);
	strcpy(pCmdList[i].help_text,QUIT_TEXT);
	pCmdList[i].pFunc=Quit;
	pCmdList[i].code = calc_crc(QUIT_CMD);
	i++;


#define	SET_CMD "set"
#define	SET_TEXT "usage: set <int|string> <name>=<value> \n usage: set <buffer> <name>=<size>"
	
	pCmdList[i].word = (char *)malloc(strlen(SET_CMD)+1);
	strcpy(pCmdList[i].word,SET_CMD);
	pCmdList[i].help_text = (char *)malloc(strlen(SET_TEXT)+1);
	strcpy(pCmdList[i].help_text,SET_TEXT);
	pCmdList[i].pFunc=Set;
	pCmdList[i].code = calc_crc(SET_CMD);
	i++;


#define	ECHO_CMD "echo"
#define	ECHO_TEXT "This is the echo command."
	
	pCmdList[i].word = (char *)malloc(strlen(ECHO_CMD)+1);
	strcpy(pCmdList[i].word,ECHO_CMD);
	pCmdList[i].help_text = (char *)malloc(strlen(ECHO_TEXT)+1);
	strcpy(pCmdList[i].help_text,ECHO_TEXT);
	pCmdList[i].pFunc=Echo;
	pCmdList[i].code = calc_crc(ECHO_CMD);
	i++;
}

int process_line(char *line) {
	
	char **words;
	int word_cnt;

	char *str1, *token;
//	char *str2, *subtoken;
	char *saveptr1;
//	char *saveptr2;
	int j;
	

//	printf("%s",line);

	words=malloc(15*8);  // 15 word pointers. pointers are 64-bit
	bzero(words,15*8);
	word_cnt=0;


	for (j = 1, str1 = line; ; j++, str1 = NULL) {
		token = strtok_r(str1, " ", &saveptr1);
		if (token == NULL)
			break;

		// We have a word. What type of word.
		//printf("%d: %s\n", j, token);
		words[word_cnt]=(char *) malloc(strlen(token)+1);
		strcpy(words[word_cnt++],token);


//		for (str2 = token; ; str2 = NULL) {
//			subtoken = strtok_r(str2, argv[3], &saveptr2);
//			if (subtoken == NULL)
//				break;
//			printf(" --> %s\n", subtoken);
//		}
	}


	parse_words(words,word_cnt);
	return 0;
}

int doAssignment(struct variable sVar,char *pValue) {

	int i, iRC = 0;
	printf("doAssignment %s %s\n",sVar.pName, pValue);
	return iRC;
}

int parse_words(char **words, int word_cnt) {

	int i,j,k;
	unsigned int uiCode;
	int iRC;
	int found;

	char *pBuf;
	int iLen;

	char *str1, *token;
	char *saveptr1;

	struct variable *pVariable;

	printf("parse_words()\n");

	// See if it is a command
	for (i=0;i<word_cnt;i++) {
		printf("Looking for %s\n",words[i]);
		uiCode = calc_crc(words[i]);
		found=0;
		//printf("uiCode = %x\n",uiCode);
		for (j=0; j<coniNumCommands; j++) {
			if (pCmdList[j].code == uiCode) {
				//pCmdList[j].pFunc(&pCmdList[j],words[i]);
				pCmdList[j].pFunc(&(pCmdList[j]),words,word_cnt);
				found=1;
				return 0;
//				break;
			} 
		}
		if (0==found) {
			printf("%s is unrecognized command\n",words[i]);
		}
	}
	

	iLen=strlen(words[0]);
	pBuf=(char *)malloc(iLen+1);
	strcpy(pBuf,words[0]);

	for (j = 1, str1 = pBuf; ; j++, str1 = NULL) {
		token = strtok_r(str1, "=", &saveptr1);
		if (token == NULL)
			break;

		// We have a word. What type of word.
		printf("%d: %s\n", j, token);
		if (1==j) {
			// first token is possibly a variable
			found=0;
			for (k=0; k<iNumVarUsed; k++) {
				if (0 == strcmp(pVariableList[k].pName,token)) {
					//pVariable = pVariableList[k];
					found=1;
					break;
				}
			}
			if (0==found) {
				printf("%s is unrecognized variable\n",token);
				return -1;
			}
		}

		if (2==j) {
			printf("%s is value\n",token);
			//iRC = doAssignment(pVariable,);
		}
	// See if it is an existing variable assignment
	// word will be of form a=10
//	for (j=0; j<iNumVarUsed; j++) {
//	char *strcasestr(const char *haystack, const char *needle);
//		if (0 == strcmp(pVariableList[j].pName,words[i])) {
//			iRC = doAssignment(pVariableList[j],words[i]);
//			return iRC;
//	}

	}


	return 1;
}

void dump_words(char **words, int word_cnt) {

	int i;
	for(i=0;i<word_cnt;i++) {
		printf("words [%d] = %s %x\n", i ,words[i], calc_crc(words[i]) );
	}
}

void dump_cmd_list(void) {

	int i;
	for(i=0;i<coniNumCommands ;i++) {
		if (NULL != pCmdList[i].word ) {
			printf("%s %x - ", pCmdList[i].word, pCmdList[i].code);
			printf("%s \n", pCmdList[i].help_text);
		}
	}
 
}

int variable_exists(char *name) {
	int i, iRC = 0;
	for (i = 0; i<iNumVarUsed; i++) {
		if (0 == strcmp(pVariableList[i].pName,name)) {
			iRC = 1;
			return iRC;
		}
	}
	return iRC;

}
unsigned int calc_crc(char *word) {

	unsigned int uiCode = 0xAAAAAAAA;
	int i;
	int len;

	len = strlen(word);
	for (i=0;i<len;i++) {
		uiCode = word[i] ^ (uiCode>>i);
	}

	return uiCode;
}







int Quit(struct command *pCmd, char **words, int word_cnt) {
	exit(0);
}



/*
 * set int a=10  
 *	set
 *  int
 *  a=10
 * set string b=10
 * set buffer b=100
 */
int Set(struct command *pCmd, char **words, int word_cnt) {
	char *str1, *token;
//	char *str2, *subtoken;
	char *saveptr1;
//	char *saveptr2;
	int j;
	int i, iRC = 0;
	int value;

	//printf("set command\n");
	for (i=0;i<word_cnt;i++) {
		//printf("words[%d] = %s\n", i, words[i]);
	}

	if (1 == word_cnt) {
		printf("variables in use:\n");

		for (i = 0; i<iNumVarUsed; i++) {
			printf("%s = ",pVariableList[i].pName);
			if (eINT == pVariableList[i].type) {
				printf("0x%02X\n",*(int *) pVariableList[i].pValue);
			} else if (eSTRING == pVariableList[i].type){
				printf("\"%s\"\n",(char *) pVariableList[i].pValue);
			} else if (eBUFFER == pVariableList[i].type) {
				printf("buffer with size %d\n",pVariableList[i].iValueSize);
				//printf("first 16 bytes \n");
				for (j=0;j<pVariableList[i].iValueSize;j++) {
					printf("%x ",((char *) (pVariableList[i].pValue))[j]);
				}
				printf("\n");
			} else {
				printf("invalid type\n");
			}
		}


		return iRC;
	}


	if (3 != word_cnt) {
		printf("usage: set <int|string|buffer> <name>=<value|size>\n");
		iRC=-1;
		return iRC;
	}

	if (0 == strcmp("int",words[1])) {
		//printf("int\n");
		pVariableList[iNumVarUsed].type=eINT;

	} else if  (0 == strcmp("string",words[1])) {
		//printf("string\n");
		pVariableList[iNumVarUsed].type=eSTRING;
	} else if  (0 == strcmp("buffer",words[1])) {
		//printf("buffer\n");
		pVariableList[iNumVarUsed].type=eBUFFER;
	} else {
		printf("usage: set <int|string|buffer> <name>=<value|size>\n");
		iRC=-1;
		return iRC;
	}



	for (j = 1, str1 = words[2]; ; j++, str1 = NULL) {
		token = strtok_r(str1, "=", &saveptr1);
		if (token == NULL)
			break;

		//printf("%d: %s\n", j, token);
		if (1==j) {

			// Determine if variable exists already. if so alert user
			if (variable_exists(token)) {
				printf("variable exists already. Input ignored.\n");
				iRC=-1;
				return iRC;
			}
			pVariableList[iNumVarUsed].pName = (char*) malloc(strlen(token)+1);
			strcpy(pVariableList[iNumVarUsed].pName,token);	
		}
		if (2==j) {
			if (eINT == pVariableList[iNumVarUsed].type) {
				pVariableList[iNumVarUsed].pValue = (int *) malloc(4);
				value = atoi(token);
				memcpy(pVariableList[iNumVarUsed].pValue,&value,4); 
			} else if (eSTRING == pVariableList[iNumVarUsed].type) {
				pVariableList[iNumVarUsed].pValue = (char *) malloc(80);
				strcpy( (char *) pVariableList[iNumVarUsed].pValue, token);
			} else if (eBUFFER == pVariableList[iNumVarUsed].type) {
				value = atoi(token);
				pVariableList[iNumVarUsed].iValueSize = value;
				pVariableList[iNumVarUsed].pValue = (char *) malloc(value);
			} else {
				iRC=-1;
				return iRC;
			}
		}
	}
	iNumVarUsed++;

	return iRC;
}

//struct variable pVariableList;
//const int coniNumVariables = 10;
//int iNumVarUsed = 0;
//struct variable {
//	char *pName;
//	enum var_type_t type;
//	void *pValue;
//};




int Echo(struct command *pCmd, char **words, int word_cnt) {
	int i, iRC = 0;
	printf("echo command\n");
	for (i=0;i<word_cnt;i++) {
		printf("words[%d] = %s\n", i, words[i]);
	}
	return iRC;
}


int Help(struct command *pCmd, char **words, int word_cnt) {
	int iRC = 0;
	printf("Available commands:\n");
	printf("%s\n",pCmd->help_text);
	
	return iRC;
}

int Nop(struct command *pCmd, char **words, int word_cnt) {
	printf("do nothing\n");
	return 0;
}

int ReadFile(struct command *pCmd, char **words, int word_cnt) {
	printf("readfile called\n");
	return 0;
}


int WriteFile(struct command *pCmd, char **words, int word_cnt) {
	printf("writefile called\n");
	return 0;
}


