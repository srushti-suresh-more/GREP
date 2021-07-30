#include<stdio.h>
#include <stdlib.h>
#include"list.h"
#include<string.h>
#include<dirent.h>

void init(content *c){
     *c=NULL;
     return;
}
void inserts(content *c,char newfile[]){
    node *nn=(node *)malloc(sizeof(node));
    if(!nn)
        return;
    strcpy(nn->file_name,newfile);
    nn->next=NULL;
    //if this is the only node in list
    if(*c==NULL){
        *c=nn;
        return;
    }
    node *p = *c;
    while(p->next){
        p=p->next;
    }
    p->next=nn;
    return;

}
void display(content c){
    if(c == NULL)
         return;
    node *p = c;
    while(p){
        printf("%s \n",p->file_name);
        p = p->next;
    }
    return;
}

char* remov_pos(content *c,char * thisfile){
    node *p=*c,*q;
    q=p;
    if(strcmp(thisfile,q->file_name)==0){
         p=p->next;
         *c=q->next;
         char *temp=q->file_name;
         free(q);
         return temp;
    }
    while(p){
            //q=p;
        if(strcmp(thisfile,p->file_name)==0){
            if(p->next == NULL){
                    char *temp=p->file_name;
                    free(p);
                    q->next=NULL;
                    return temp;

            }
            q->next=p->next;
            char *temp=p->file_name;
            free(p);
            return temp;
        }
        else{
            q=p;
            p=p->next;
        }

    }
    return NULL;
}



void enlist(char direct[],content *c){
   // init(&c);
    DIR *dc = opendir(direct);
    if(!dc){
        printf("enter valid directory name or look for other errors");
        return;
    }
    // .o , .cbp, .exe
    struct dirent *name_dr;
    char temp_path[200],temp_path2[200];
    while((name_dr=readdir(dc))!= NULL){
            if(strcmp(name_dr->d_name,".")!= 0 && strcmp(name_dr->d_name,"..")!= 0){
                    if(strstr(name_dr->d_name,".")!=0){
                            strcpy(temp_path2,direct);
                            strcat(temp_path2,"\\");
                            strcat(temp_path2,name_dr->d_name);
                            inserts(c,temp_path2);
                           // printf("%s ",name_dr->d_name);
                    }

                    else {
                        strcpy(temp_path,direct);
                        strcat(temp_path, "\\");
                        strcat(temp_path, name_dr->d_name);
                        enlist(temp_path,c);
                    }
           }
    }
    closedir(dc);
    return;
}
int searches(content c,char line[]){
     if(c == NULL)
        return 0;
    node *p= c;
    int i=0;
    while(p){
        char *ch=p->file_name;
        for(i=0;i<strlen(line);i++){
            if(ch[i] != line[i] )
                break;
        }
        if(i == strlen(line))
            return 1;
        p=p->next;
    }
 return 0;
 }
