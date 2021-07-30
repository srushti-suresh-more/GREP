#include<stdio.h>
#include<stdlib.h>
#include"search.h"
#include<string.h>
#include<ctype.h>
#include"list.h"
#include<dirent.h>
/* function prototype - int readline(FILE *fp, char *line);
 * Precondition - takes file pointer and char array as argument.
 * Split the file into lines and return the number of char in line
 * Postcondition - This will return number of char in line
*/
 int readline(FILE *fp,char *line){
     char get_char;
     int i=0;
     while(fread(&get_char,sizeof(char),1,fp)){
            if(get_char != '\n')
                    line[i++]=get_char;
            if(get_char == '\n'){
                    line[i++]='\0';
                    return i;
            }
     }
     line[i]='\0';
     //printf("%d",i);
     return i;
 }

/* Function prototype - find_word(char* line , char* word);
 * Precondition - take line and word to be searched as argument
 * this function will search for a word in a line
 * Postcondition - function will return 0 if word is not found else 1
*/
int find_word(char* line , char* word){
    int j=0,i=0,t=0;
    int wl=strlen(word);
    //printf("%d",wl);
    while(*(line+j) != '\0'){
        if(*(line+j)== *(word+i)){
                while(*(line+j) == *(word+i) && *(line+j)!='\0'){
                        j++;
                        i++;
                        //printf("%d",j);
                }
                if(i==wl && (*(line+j)==' ' || *(line+j)=='\0')){
                        t++;
                        // printf("%d",t);
                }
        }
        else{
                while(*(line+j)!=' '){
                        j++;
                        if(*(line+j)=='\0')
                            break;
                }
        }
        j++;
        i=0;
    }
    if(t>0)
            return 1;
    else
            return 0;
    return 0;
}

//*******************************************************************************************************************************
/*
int find_pat(char* line , char* sample){
int ll=strlen(line);
int wl=strlen(sample);
int j=0;
for(int i=0;i <= ll-wl;i++){
    for(j=0;j<wl;j++){
            if(*(line+i+j) != *(sample+j))
            break;
            }
        if(j==wl)
          return 1;
    }
return 0;
}

int match_insen(char* line,char *sample){

 char *ch=(char *)malloc(sizeof(char)*100);
 char *c=(char *)malloc(sizeof(char)*100);
int r;
int i=0;
for(iaq2=0;*(line+i)!='\0';i++){
        if(*(line+i)>='A' && *(line+i)<='Z'){
             *(c+i)=*(line+i);
             *(c+i)=tolower(*(line+i));
        }
        else
          *(c+i)=*(line+i);
}
*(c+i)='\0';
for(i=0;*(sample+i)!='\0';i++){
        if(*(sample+i)>='A' && *(sample+i)<='Z'){
             *(c+i)=*(line+i);
             *(ch+i)=tolower(*(sample+i));
        }
        else
          *(ch+i)=*(sample+i);
}
*(ch+i)='\0';
//puts(ch);
r=find_pat(c,ch);
return r;
}

//return 0 if element is found
//return 1 if not found
int rev_search(char* line,char *sample){
  int result=find_pat(line,sample);
    return !result;
}
*/
//****************************************************************************************************************************
/* Function prototype -char* convert(char* line);
 * Precondition - the line which is returned by readline function / or just a word  is taken as argument
 * this function is used as supplementary function for finds function
 * this converts given line completely into lower case string
 * Postcondition - This function returns the modified string
*/
char* convert(char* line){
    int i=0;
    char *c=(char *)malloc(sizeof(char)*100);
    for(i=0;*(line+i)!='\0';i++){
            if(*(line+i)>='A' && *(line+i)<='Z'){
                    //*(c+i)=*(line+i);
                    *(c+i)=tolower(*(line+i));
            }
            else
                    *(c+i)=*(line+i);
    }
    *(c+i)='\0';
    //puts(c);
    return c;
}

/* function prototype -  int finds(char *line , char *sample , int case , int word)
 * Precondition - The line read by readline is being passed to this function as a parameter , word/pattern to be searched will be the second parameter
 * The given function will search for a pattern / word according to the inputs we are giving to the parameters case and word.
 * There are four combinations possible :- 1) case=0 , word=0     2)case=1 , word=0   3) case=0 , word=1 4) case=1 , word=1
 * Here, case=1 means case sensitive , word=1 means search for a complete word and not a pattern
 * Postcondition- this function will return a boolean value of our search result , i,e 1 if we find string otherwise zero
*/
int finds(char *line , char *sample , int cases , int word){
   char *result;
   // case sensitive and a substring
   if(cases == 1 && word == 0){
            result=strstr(line,sample);
            if(result){
                //puts(result);
                return 1;
            }
            else
                return 0;
    }
   // case insensitive but a substring
   if(cases == 0 && word == 0){
            // printf("hi");
            char *m=convert(line);
            //puts(m);
            char *n=convert(sample);
            //puts(n);
            result=strstr(m,n);
            if(result){
               //puts(result);
                return 1;
            }
            else
                return 0;
    }
   // case insensitive but a word
   if(cases == 0 && word == 1){
            char *m=convert(line);
            //puts(m);
            char *n=convert(sample);
            return find_word(m,n);
    }
   // case sensitive word. It is basically -w flag
   if(cases == 1 && word == 1){
            //printf("here\n");
            return find_word(line,sample);
   }
   else
            return 0;
}

void helppage(){
    puts("-c : This prints only a count of the lines that match a pattern");
    puts("-h : Display the matched lines, but do not display the filenames.");
    puts("-H : It displays the matched lines along with filenames");
    puts("-i : Ignores, case for matching");
    puts("-l : Displays list of a filenames only.");
    puts("-n : Display the matched lines and their line numbers.");
    puts("-v : This prints out all the lines that do not matches the pattern");
    puts("-f file : Takes patterns from file, one per line.");
    puts("-w : Match whole word");
    puts("-o : Print only the matched parts of a matching line,with each such part on a separate output line.");
    puts("-m NUM :  Stop reading a file after NUM matching lines.");
    puts("-q : quiet");
    puts("-r : Recursively search through all the files ");
    return;
}
int isdirectory(char ch[]){
    DIR *dc = opendir(ch);
    if(!dc){
        closedir(dc);
        return 0;
    }
    else{
        closedir(dc);
        return 1;
    }
 }

int isfile(char ch[]){
    FILE *fp=fopen(ch,"r");
    if(fp){
        fclose(fp);
        return 1;
    }
    return 0;
}

int iscommand(char ch[]){
    return ch[0]== '-';
 }

 int isvalidf(char ch[]){
    int len=strlen(ch);
    if(ch[len-1]=='f')
        return 1;
    return 0;
 }
/*
 char validof2(char argument[]){
    int len=strlen(argument);
    char ch;
    for(int i=0;i<len;i++){
        if(argument[i]=='h'){
            ch='H';
            return ch;
        }
        else if(argument[i]=='H'){
            ch='h';
            return ch;
        }
    }
 }
*/
 int isvalidm(char ch[]){
    int len=strlen(ch),i=0,num=0;
    char *c=(char *)malloc(sizeof(char)*100);
    for( i=0;i< len ;i++){
        if(ch[i] == 'm' ){
            break;
        }
    }
    if(i < len-1){
        int k=0;
        for(int j = i + 1;j < len;j++){
            if( !isdigit(ch[j]))
                return INT_MIN;
            else
                c[k++]=ch[j];
        }
        num=atoi(c);
        return num;
    }
    else
        return INT_MIN;
 }

 char* for_oflag(char *line,char *word,int cases){
     char *r = strstr(word,"^");
     char *s = strstr(word,"$");
     if(r && !s){
        char *temp_word = (char *)malloc(sizeof(char)*(strlen(word)-1) );
        int i=1,j=0;
        while(word[i] != '\0'){
            temp_word[j++] = word[i];
            i++;
        }
        temp_word[j]='\0';
        strcpy(word,temp_word);
     }
     if(s && !r){
        int wl = strlen(word);
        char *temp_word = (char *)malloc(sizeof(char)*wl);
        int i=0,j=0;
        while(i < wl -1){
            temp_word[j++] = word[i];
            i++;
        }
       // printf("here");
        temp_word[j]='\0';
        strcpy(word,temp_word);
     }
     if( r && s){
        int i=1,j=0;
        int len1=strlen(word);
        char *temp_word = (char *)malloc(sizeof(char)*(len1 - 2));
        while(i < len1-1){
            temp_word[j++] = word[i];
            i++;
        }
        temp_word[i] = '\0';
        strcpy(word,temp_word);
     }
    //int len1=strlen(line);
    int len2=strlen(word);
    char *result=(char *)malloc(sizeof(char)*1024);
    if(cases == 0){
        int i=0,j=0;
        while(line[j]!= '\0'){
            if(line[j] == word[i] || line[j] == word[i] - 32 || line[j] == word[i] +32 ){
                result[i]=line[j];
                i++;
                if(len2 == i)
                    break;
            }
            else
                i=0;
            j++;
        }
        result[i]='\0';
    }
    if(cases == 1){
       int i=0,j=0;
        while(line[j]!= '\0'){
            if(line[j] == word[i] ){
                result[i]=line[j];
                i++;
                if(len2 == i)
                    break;
            }
            else
                i=0;
            j++;
        }
        result[i]='\0';
    }
    return result;
 }

int for_carat(char *line,char *word ,int cases , int isword){
    int wl = strlen(word);
    char *m=convert(line);
    char *temp_word = (char *)malloc(sizeof(char)*wl);
    int i=1,j=0;
    while(word[i] != '\0'){
        temp_word[j++] = word[i];
        i++;
    }
    temp_word[j]='\0';
    char *n=convert(temp_word);
    //puts(n);
    i=0,j=0;
    if(cases == 1 && isword == 0){
        for( i=0;i < strlen(temp_word);i++){
            if(line[i] != temp_word[i])
                return 0;
        }
        return 1;
    }
    i=0,j=0;
    if(cases == 0 && isword == 0){
        for( i=0;i < strlen(temp_word);i++){
            if(m[i] != n[i])
                return 0;
        }
        return 1;
    }
    i=0,j=0;
    if(cases == 0 && isword == 1){
        for(i=0;i < strlen(temp_word);i++){
            if(m[i] != n[i]){
                return 0;
            }
        }
        if(m[i] == ' ')
           return 1;
        else
            return 0;
    }
    if(cases == 1 && isword==1){
        for( i=0;i < strlen(temp_word);i++){
            if(line[i] != temp_word[i])
                return 0;
        }
        if(line[i] == ' ')
            return 1;
        else
            return 0;
    }
    return 0;
}

int for_dollar(char *line , char* word, int cases , int isword){
    int ll= strlen(line);
    int wl = strlen(word);
    char *m=convert(line);
    char *temp_word = (char *)malloc(sizeof(char)*wl );
    int i=0,j=0;
    while(i < wl -1){
        temp_word[j++] = word[i];
        i++;
    }
    temp_word[j]='\0';

   // puts(temp_word);
    char *n=convert(temp_word);
//printf("j=%c\n",line[ll-1]);
    j=wl-2;
    if(cases == 1 && isword == 0){

        for(i= ll -1 ;  j >=0;i --){
            if(line[i] != temp_word[j--]){
                return 0;
            }
        }

        return 1;
    }
    j=wl-2;
    if(cases == 0 && isword == 0){
        for(i= ll -1 ;  j >= 0;i --){
            if(m[i] != n[j--]){
                return 0;
            }
        }
        return 1;
    }
    j=wl-2;
    if(cases == 0 && isword == 1){
        for(i= ll -1 ;  j >= 0;i --){
            if(m[i] != n[j--]){
                return 0;
            }
        }
        if(m[i] == ' ')
            return 1;
        else
            return 0;
    }
    if(cases == 1 && isword == 1){
        for(i= ll -1 ;  j >=0;i --){
            if(line[i] != temp_word[j--])
                return 0;
        }
        if(m[i] == ' ')
            return 1;
        else
            return 0;
    }
 return 0;
}

int for_carndoll(char *line,char *word,int cases){
    int i=1,j=0;
    int len1=strlen(word);
    char *temp_word = (char *)malloc(sizeof(char)*(len1 - 2));
    while(i < len1-1){
        temp_word[j++] = word[i];
        i++;
    }
    temp_word[i] = '\0';
    //puts(temp_word);
    char *m = convert(line);
    char *n = convert(temp_word);
    if(cases == 1){
        //printf("%d - return\n",strcmp(line,temp_word));
        return strcmp(line,temp_word) == 0;
    }
    else{
        //printf("%d - return\n",strcmp(m,n));
        return strcmp(m,n) == 0;
    }
}


int findsr(char *line , char *sample , int cases , int isword){
    char *r = strstr(sample,"^");
    char *s = strstr(sample,"$");
    if(r || s){
        if(r && !s){
            //printf("here\n");
            return for_carat(line,sample,cases,isword);
        }
        if(!r && s){
            //printf("here\n");
            return for_dollar(line,sample,cases,isword);
        }
        if(r && s){
            return for_carndoll(line,sample,cases);
        }
    }
    else if(!r && !s){
       // printf("here\n");
        return finds(line,sample,cases,isword);
    }
    else
        return 0;

}
