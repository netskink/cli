
struct command {
	char *word;
	char *help_text;
	unsigned int code;
	int (*pFunc)(struct command *pCmd, char **words, int word_cnt);
};

typedef enum { eINT, eSTRING, eBUFFER } var_type_t;

struct variable {
	char *pName;
	var_type_t type;
	void *pValue;
	int iValueSize;
};


void dump_words(char **words, int word_cnt);
void build_cmd_list(void);
void dump_cmd_list(void);
unsigned int calc_crc(char *);
int parse_words(char **, int );
int process_line(char *line);

int Nop(struct command *pCmd, char **words, int word_cnt);
int ReadFile(struct command *pCmd, char **words, int word_cnt);
int WriteFile(struct command *pCmd, char **words, int word_cnt);
int Quit(struct command *pCmd, char **words, int word_cnt);
int Set(struct command *pCmd, char **words, int word_cntv);
int Echo(struct command *pCmd, char **words, int word_cntv);
int Help(struct command *pCmd, char **words, int word_cnt);

