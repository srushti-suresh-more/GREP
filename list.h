

// This is the structure used to read file names in a particular directory
typedef struct node{
    char file_name[100];
    struct node *next;
}node;
typedef node* content;
void init(content *c);
void inserts(content *c,char *newfile);
void display(content c);
char* remov_pos(content *l,char * thisfile);
void enlist(char direct[],content *c);
