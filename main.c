#include <stdio.h>
#include <stdlib.h>
#include"search.h"
#include<dirent.h>
#include<getopt.h>
#include"list.h"
#include<string.h>
/*  For raising flags we've declared array of int of fixed size
 *  All the elements are initialized to -1.-
 *  use index 0 for -r .
 *  use index 1 for -i .
 *  use index 2 for -w .
 *  use index 3 for -c .
 *  use index 4 for -n .
 *  use index 5 for -v .
 *  use index 6 for -o .
 *  use index 7 for -H .
 *  use index 8 for -h .
 *  use index 9 for -l .
 *  use index 10 for -m .
 *  use index 11 for -f .
 *  use index 12 for -q .
*/
int main(int argc, char * argv[]){
    int *flag=(int *)malloc(sizeof(int)*13);
    for(int i = 0 ;i < 13; i++)
            *(flag + i) = -1;
    int opt=0  ;
   // printf("%d argc",argc);
    char line1[2048],line2[2048];

    //getopt needs : for some flags who has compulsory an argument following it . in our case -f and -m.
    while((opt = getopt( argc , argv , "riwcnvoHhlm:f:q"))!= -1){
            switch(opt){

                      case 'r':
                              flag[0] = 0;
                             // printf(" in flag 0\n");
                              break;

                      case 'i':
                              flag[1] = 1;
                             // printf(" in flag 1\n");
                              break;

                      case 'w':
                              flag[2] = 2;
                              //printf(" in flag 2\n");
                              break;

                      case 'c':
                              flag[3] = 3;
                              //printf(" in flag 3\n");
                              break;

                      case 'n':
                              flag[4] = 4;
                              //printf(" in flag 4\n");
                              break;

                      case 'v':
                              flag[5] = 5;
                              //printf(" in flag 5\n");
                              break;
                      case 'o':
                              flag[6] = 6;
                              //printf(" in flag 6\n");
                              break;

                      case 'H':
                              flag[7] = 7;
                              if(flag[8] == 8)
                                    flag[8] = -1;
                              //printf(" in flag 7\n");
                              break;

                      case 'h':
                              flag[8] = 8;
                                //  printf(" in flag 8\n");
                              if(flag[7] == 7)
                                    flag[7] = -1;
                              break;

                      case 'l':
                              flag[9] = 9;
                              //printf(" in flag 9\n");
                              break;

                      case 'm':
                          /*
                              if(argc < 4){
                                    printf("less arguments for type of flag -m ");
                                    return 0;
                              }
                              */
                              flag[10] = 10;
                              //printf(" in flag 10\n");
                              break;

                      case 'f':
                              flag[11] = 11;
                              //printf(" in flag 11\n");
                              break;

                      case 'q':
                              flag[12] = 12;
                              //printf(" in flag 12\n");
                              break;

            }
    }


    // after encountering -q flag , exit with the 0 return status
    if( flag[12] == 12)
            exit(0);
    if(flag[6]==6 && flag[5] == 5 && flag[3]!=3 && flag[9]!=9){
        exit(0);
    }
    FILE *fp,*fp1;
    int cases=1;
    int isword=0;
    if(flag[1] == 1){
         cases = 0;
    }
    if(flag[2] == 2){
         isword=1;
    }
     content c;
     init(&c);
     // o flag
     content c1;
     init(&c1);
     int i = 1;
     int dflag = 0,normal=0,num_file1=0,num_file2=0,count=0,acount=0,max_count,mcount=0,fal=0;
     char dname[1024],pattern[1024],file1[1024],file2[1024];
     char *temp_line=NULL;
     while(i < argc){
        if(isfile(argv[i])){
                if(fal == 0){
                    inserts(&c,argv[i]);
                }
                fal=0;
        }
        if(isdirectory(argv[i])){
            if(flag[0] == 0){
                enlist(argv[i],&c);
            }
            dflag = 1;
            strcpy(dname,argv[i]);
        }
        if(iscommand(argv[i])){

            normal=1;
            //printf("hello");
            if(strstr(argv[i],"m")){
                 max_count= isvalidm(argv[i]);
                if(max_count  == INT_MIN){
                     printf("Invalid max count ");
                    return 0;
                }
                else if(max_count == 0){
                    exit(0);
                }
            }
            if(isfile(argv[i+1]) && flag[11]!=11){
                    strcpy(pattern,argv[i+1]);
                    fal=1;
                    //puts(pattern);
            }
        }
        if(!isdirectory(argv[i]) && !isfile(argv[i]) && !iscommand(argv[i])){
            strcpy(pattern,argv[i]);
        }
        i++;
     }
     //display(c);

    if(normal == 0){
        node *p = c;
        while(p){
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("%s : No such file or directory",file1);
                return 0;
            }
            while(readline(fp,line1)){
                if(findsr(line1,pattern ,1,0) == 1){
                    printf("%s : ",file1);
                    puts(line1);
                }
            }
            fclose(fp);
            p=p->next;
        }
        return 0;
    }
    if(flag[11] == 11){
        //if(argc > 4){
          //  exit(0);
        //}
        if(flag[0] != 0 && dflag){
            printf("%s : Is a directory",dname);
        }

        if(flag[5] == 5){
            node *p=c;
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("cannot open file %s",file1);
                return 0;
            }
            while(readline(fp,line1)){
                num_file1++;
            }
            fclose(fp);
            p=p->next;
            while(p){
                strcpy(file2,p->file_name);
                fp1=fopen(file2,"r");
                if(!fp1){
                    printf("cannot open file %s",file2);
                    return 0;
                }
                num_file2=0;
                while(readline(fp1,line2)){
                    num_file2++;
                    fp=fopen(file1,"r");
                    if(!fp){
                        printf("cannot open file %s",file1);
                        return 0;
                    }
                    while(readline(fp,line1)){
                        if(findsr(line2,line1,cases,isword) == 0){
                            count++;
                        }

                    }
                    fclose(fp);
                    if(num_file1 == count){
                        acount++;
                        if(flag[4] != 4 && flag[3]!= 3 && flag[9]!=9 && flag[6] !=6 ){
                            if(flag[10] == 10){
                                if(flag[7] == 7 || (flag[8]!=8 && flag[7]!=7)){
                                    if(mcount < max_count){
                                        printf("%s ",file2);
                                        puts(line2);
                                        mcount+=1;
                                    }
                                }
                                if(flag[8] == 8){
                                    if(mcount < max_count){
                                        puts(line2);
                                        mcount+=1;
                                    }
                                }
                            }
                            else if(flag[10]!=10){
                                if(flag[7] == 7 || (flag[8]!=8 && flag[7]!=7)){
                                    printf("%s ",file2);
                                    puts(line2);
                                }
                                if(flag[8]==8){
                                    puts(line2);
                                }
                            }

                        }
                        if(flag[4] == 4 && flag[3]!=3 && flag[9]!=9){
                          //  printf("%d -max count",max_count);
                            if(flag[8] == 8 && flag[10]==10){
                                if(mcount < max_count){
                                    printf("%d :%s\n",num_file2,line2);
                                    mcount++;
                                }
                            }
                            else if(flag[8] == 8 && flag[10]!=10){
                                printf("%d :%s\n",num_file2,line2);
                            }
                            if(flag[7] == 7 && flag[10]==10){
                                    if(mcount < max_count){
                                        printf("%s :%d : %s\n",file2,num_file2,line2);
                                        mcount++;
                                    }
                            }
                            else if(flag[7] == 7 && flag[10]!=10){
                                 printf("%s :%d : %s\n",file2,num_file2,line2);
                            }
                            if(flag[7]!=7 && flag[8]!=8 && flag[10]!=10){
                                printf("%s :%d : %s\n",file2,num_file2,line2);
                            }
                            if(flag[10]==10 && flag[7]!=7 && flag[8]!=8){
                               if(mcount < max_count){
                                        printf("%s :%d : %s\n",file2,num_file2,line2);
                                        mcount++;
                                }
                            }
                        }
                    }
                    count=0;
                }
                if(acount > 0){
                    if(flag[9] == 9){
                        printf("%s\n",file2);
                    }
                }
                if(flag[3] == 3 && flag[9] != 9){
                    if(flag[10] != 10){
                        if(flag[8] == 8)
                            printf("%d\n",acount);
                        else if(flag[7] == 7)
                            printf("%s : %d\n",file2,acount);
                        else if(flag[7] != 7 && flag[8] != 8){
                            printf("%s : %d\n",file2,acount);
                        }
                    }
                    else if(flag[10] == 10 ){
                        if(acount > max_count){
                            acount = max_count;
                        }
                        if(mcount < max_count){
                            if(flag[8] == 8)
                                printf("%d\n",acount);
                            else if(flag[7] == 7)
                                printf("%s : %d\n",file2,acount);
                            else if(flag[7] != 7 && flag[8] != 8){
                                if(mcount < max_count)
                                    printf("%s : %d\n",file2,acount);
                            }
                            mcount++;
                        }

                    }
                }
                if(flag[6] == 6 && flag[9]!= 9 && flag[3]!= 3){
                    exit(0);
                }
                count=0;
                acount=0;
                mcount=0;
                //printf("here");
                fclose(fp1);
                p=p->next;
            }
        }

        // flag for v is not raised
        else if(flag[5] != 5){
            node *p=c;
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("cannot open file %s",file1);
                return 0;
            }
            while(readline(fp,line1)){
                num_file1++;
            }
            fclose(fp);
            p=p->next;
            while(p){
                strcpy(file2,p->file_name);
                fp1=fopen(file2,"r");
                if(!fp1){
                    printf("cannot open file %s",file2);
                    return 0;
                }
                num_file2=0;
                while(readline(fp1,line2)){
                    num_file2++;
                    fp=fopen(file1,"r");
                    if(!fp){
                        printf("cannot open file %s",file1);
                        return 0;
                    }

                    while(readline(fp,line1)){
                        if(findsr(line2,line1,cases,isword) == 1){
                            if(flag[6]==6){
                                temp_line=for_oflag(line2,line1,cases);
                                inserts(&c1,temp_line);
                            }
                            count++;
                        }

                    }
                    fclose(fp);
                    if( count > 0){
                        acount++;
                        if(flag[4] != 4 && flag[3]!= 3 && flag[9]!=9 ){
                            if(flag[10] == 10){
                                if(flag[7] == 7 || (flag[8]!=8 && flag[7]!=7)){
                                    if(mcount < max_count){
                                        if(flag[6] == 6){
                                            node *p=c1;
                                            while(p){
                                                printf("%s : %s\n",file2,p->file_name);
                                                p=p->next;
                                            }
                                        }
                                        else{
                                            printf("%s : ",file2);
                                            puts(line2);
                                        }
                                        mcount+=1;
                                    }
                                }
                                if(flag[8]==8){
                                    if(mcount < max_count){
                                        if(flag[6] == 6){
                                            node *p=c1;
                                            while(p){
                                                printf("%s\n",p->file_name);
                                                p=p->next;
                                            }
                                        }
                                        else
                                            puts(line2);
                                        mcount+=1;
                                    }
                                }
                            }
                            else if(flag[10]!=10){
                                 if(flag[7] == 7 || (flag[8]!=8 && flag[7]!=7)){
                                    if(flag[6] == 6){
                                        node *p=c1;
                                        while(p){
                                            printf("%s : %s\n",file2,p->file_name);
                                            p=p->next;
                                        }
                                    }
                                    else{
                                        printf("%s ",file2);
                                        puts(line2);
                                    }
                                }
                                if(flag[8]==8){
                                        if(flag[6] == 6){
                                            node *p=c1;
                                            while(p){
                                                printf(" %s\n",p->file_name);
                                                p=p->next;
                                            }
                                        }
                                        else
                                            puts(line2);
                                }
                            }

                        }
                        if(flag[4] == 4 && flag[3]!=3 && flag[9]!=9){
                          //  printf("%d -max count",max_count);
                            if(flag[8] == 8 && flag[10]==10){
                                if(mcount < max_count){
                                    if(flag[6] == 6){
                                        node *p=c1;
                                        while(p){
                                           printf("%d : %s\n",num_file2,p->file_name);
                                           p=p->next;
                                        }
                                    }
                                    else{
                                    printf("%d :%s\n",num_file2,line2);
                                    }
                                    mcount++;
                                }
                            }
                            else if(flag[8] == 8 && flag[10]!=10){
                                 if(flag[6] == 6){
                                        node *p=c1;
                                        while(p){
                                           printf("%d : %s\n",num_file2,p->file_name);
                                           p=p->next;
                                        }
                                 }
                                 else
                                        printf("%d :%s\n",num_file2,line2);
                            }
                            if(flag[7] == 7 && flag[10]==10){
                                    if(mcount < max_count){
                                        if(flag[6]==6){
                                            node *p=c1;
                                            while(p){
                                                 printf("%s :%d : %s\n",file2,num_file2,p->file_name);
                                                p=p->next;
                                            }

                                        }
                                        else
                                            printf("%s :%d : %s\n",file2,num_file2,line2);
                                        mcount++;
                                    }
                            }
                            else if(flag[7] == 7 && flag[10]!=10){
                                if(flag[6]==6){
                                    node *p=c1;
                                    while(p){
                                        printf("%s :%d : %s\n",file2,num_file2,p->file_name);
                                        p=p->next;
                                    }
                                }
                                else
                                    printf("%s :%d : %s\n",file2,num_file2,line2);
                            }
                            if(flag[7]!=7 && flag[8]!=8 && flag[10]!=10){
                                if(flag[6]==6){
                                     node *p=c1;
                                     while(p){
                                        printf("%s :%d : %s\n",file2,num_file2,p->file_name);
                                        p=p->next;
                                    }
                                }
                                else
                                    printf("%s :%d : %s\n",file2,num_file2,line2);
                            }
                            if(flag[10]==10 && flag[7]!=7 && flag[8]!=8){
                               if(mcount < max_count){
                                        if(flag[6]==6){
                                            node *p=c1;
                                            while(p){
                                                 printf("%s :%d : %s\n",file2,num_file2,p->file_name);
                                                 p=p->next;
                                            }
                                        }
                                        else
                                            printf("%s :%d : %s\n",file2,num_file2,line2);
                                        mcount++;
                                }
                            }
                        }
                    }
                    count=0;
                    init(&c1);
                }
                if(acount > 0){
                    if(flag[9] == 9){
                        printf("%s\n",file2);
                    }
                }
                if(flag[3] == 3 && flag[9] != 9){
                    if(flag[10] != 10){
                        if(flag[8] == 8)
                            printf("%d\n",acount);
                        else if(flag[7] == 7)
                            printf("%s : %d\n",file2,acount);
                        else if(flag[7] != 7 && flag[8] != 8){
                            printf("%s : %d\n",file2,acount);
                        }
                    }
                    else if(flag[10] == 10 ){
                        if(acount > max_count){
                            acount = max_count;
                        }
                        if(mcount < max_count){
                            if(flag[8] == 8)
                                printf("%d\n",acount);
                            else if(flag[7] == 7)
                                printf("%s : %d\n",file2,acount);
                            else if(flag[7] != 7 && flag[8] != 8){
                                if(mcount < max_count)
                                    printf("%s : %d\n",file2,acount);
                            }
                            mcount++;
                        }

                    }
                }
                count=0;
                acount=0;
                mcount=0;

                //printf("here");
                fclose(fp1);
                p=p->next;
            }
        }
        return 0;
    }
    // m flag i.e index 10

    if(flag[10] == 10){
        if(flag[0] != 0 && dflag){
            printf("%s : Is a directory",dname);
            return 0;
        }
        if(flag[5] == 5){
            if(flag[6]==6 && flag[3]!=3 && flag[9]!= 9){
                exit(0);
            }
            node *p=c;
            mcount=0,count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("cannot open file %s",file1);
                    return 0;
                }
                num_file1=0;
                init(&c1);
                while(readline(fp,line1)){
                    num_file1++;
                    if(findsr(line1,pattern,cases,isword) == 0){
                        count++;
                        if(mcount < max_count){
                            if(flag[4] == 4 && flag[3]!= 3 && flag[9]!=9){
                                if(flag[8]== 8){
                                        printf("%d : ",num_file1);
                                        puts(line1);
                                        mcount++;

                                }
                                else{
                                        printf("%s : %d : ",file1,num_file1);
                                        puts(line1);
                                        mcount++;
                                }
                            }
                            if(flag[4] != 4 && flag[3]!= 3 && flag[9]!=9){
                                if(flag[8]== 8){
                                    puts(line1);
                                    mcount++;
                                }
                                else{
                                    printf("%s : ",file1);
                                    puts(line1);
                                    mcount++;
                                }
                            }
                        }
                    }

                }
                fclose(fp);
                if(flag[9]==9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3]== 3 && flag[9]!=9){
                    if(count > max_count){
                        count=max_count;
                    }
                    if(flag[8]==8){
                        printf("%d\n",count);
                    }
                    else
                        printf("%s : %d\n",file1,count);
                }
                count=0;
                mcount=0;
                p=p->next;

            }

        }
        // without v
        else if(flag[5] != 5){
               // puts("hello");
            node *p=c;
            mcount=0,count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("cannot open file %s",file1);
                    return 0;
                }
                num_file1=0;
                init(&c1);
                while(readline(fp,line1)){
                    num_file1++;
                    if(findsr(line1,pattern,cases,isword) == 1){
                        count++;
                       // puts("hello");
                        if(mcount < max_count){
                            if(flag[4] == 4 && flag[3]!= 3 && flag[9]!=9){
                                if(flag[8]== 8){
                                        if(flag[6]==6){
                                             temp_line=for_oflag(line1,pattern,cases);
                                             printf("%d : ",num_file1);
                                             puts(temp_line);
                                        }
                                        else if(flag[6]!= 6){
                                           printf("%d : ",num_file1);
                                           puts(line1);
                                        }

                                        mcount++;

                                }
                                else{
                                        if(flag[6] == 6 ){
                                            temp_line=for_oflag(line1,pattern,cases);

                                            printf("%s : %d : ",file1,num_file1);
                                            puts(temp_line);
                                        }
                                        else if (flag[6]!=6){
                                            printf("%s : %d : ",file1,num_file1);
                                            puts(line1);
                                        }
                                        mcount++;
                                }
                            }
                            if(flag[4] != 4 && flag[3]!= 3 && flag[9]!=9){
                                if(flag[8]== 8){
                                    if(flag[6]==6){
                                       // puts("hello");
                                        puts(for_oflag(line1,pattern,cases));
                                    }
                                    else
                                        puts(line1);
                                    mcount++;
                                }
                                else{
                                    if(flag[6] == 6){
                                            temp_line=for_oflag(line1,pattern,cases);
                                            printf("%s : ",file1);
                                            puts(temp_line);
                                    }
                                    else{
                                        printf("%s : ",file1);
                                        puts(line1);
                                    }
                                    mcount++;
                                }
                            }
                        }
                    }

                }
                fclose(fp);
                if(flag[9]==9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3]== 3 && flag[9]!=9){
                    if(count > max_count){
                        count=max_count;
                    }
                    if(flag[8]==8){
                        printf("%d\n",count);
                    }
                    else
                        printf("%s : %d\n",file1,count);
                }
                count=0;
                mcount=0;
                p=p->next;

            }

        }

        return 0;
    }
    // r flag i.e index 0
    // we won't consider -f and -m here as we've taken care in respective flags
    if(flag[0]==0){
        if(flag[5] == 5){
            if(flag[6]==6 && flag[3]!=3 && flag[9]!= 9){
                exit(0);
            }
            node *p=c;
            count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf(" %s No such file or directory ",file1);
                    return 0;
                }
                num_file1=0;
                while(readline(fp,line1)){
                    num_file1++;
                    if(findsr(line1,pattern,cases,isword) == 0){
                        count++;
                        if(flag[4] != 4 && flag[3] != 3 && flag[9] != 9){
                            if(flag[8] == 8){
                                puts(line1);
                            }
                            else{
                                printf("%s : ",file1);
                                puts(line1);
                            }
                        }
                        if(flag[4] == 4 && flag[3] != 3 && flag[9] != 9){
                            if(flag[8] == 8){
                                printf("%d : ",num_file1);
                                puts(line1);
                            }
                            else{
                                printf("%s : %d : ",file1,num_file1);
                                puts(line1);
                            }
                        }
                    }

                }
                if(flag[9] == 9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3] == 3 && flag[9] != 9){
                    if(flag[8]== 8){
                        printf("%d\n",count);
                    }
                    else{
                        printf("%s : %d\n",file1,count);
                    }
                }
            count=0;
            p=p->next;

            }
        }

        else if(flag[5]!=5){
            node *p = c;
            count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp = fopen(file1,"r");
                if(!fp){
                    printf("%s no such file or directory",file1);
                    return 0;
                }
                num_file1=0;
                while(readline(fp,line1)){
                    num_file1++;
                    if(findsr(line1,pattern,cases,isword)== 1){
                        count++;
                        if(flag[4] !=4 && flag[3]!=3 && flag[9]!=9){
                            if(flag[6] == 6 ){
                                temp_line=for_oflag(line1,pattern,cases);
                            }
                            if(flag[6] == 6){
                                if(flag[8] == 8){
                                    puts(temp_line);
                                }
                                else{
                                    printf("%s :",file1);
                                    puts(temp_line);
                                }
                            }
                            else{
                                if(flag[8] == 8){
                                    puts(line1);
                                }
                                else{
                                    printf("%s :",file1);
                                    puts(line1);
                                }

                            }

                        }
                        else if(flag[4] == 4 && flag[3]!=3 && flag[9]!=9){
                            if(flag[6] == 6){
                                temp_line=for_oflag(line1,pattern,cases);
                            }
                             if(flag[6] == 6){
                                if(flag[8] == 8){
                                    printf("%d : ",num_file1);
                                    puts(temp_line);
                                }
                                else{
                                    printf("%s : %d :",file1,num_file1);
                                    puts(temp_line);
                                }
                            }
                            else{
                                if(flag[8] == 8){
                                    printf("%d : ",num_file1);
                                    puts(line1);
                                }
                                else{
                                    printf("%s : %d : ",file1,num_file1);
                                    puts(line1);
                                }

                            }

                        }
                    }
                }
                if(flag[9] == 9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3] == 3 && flag[9] != 9){
                    if(flag[8] == 8){
                        printf("%d\n",count);
                    }
                    else{
                        printf("%s : %d\n",file1,count);
                    }
                }
                count=0;
                p=p->next;
            }
        }
        return 0;
    }
    // flag o i.e. index 6
    if(flag[6] == 6){
        if(flag[5] == 5 && flag[3]!=3 && flag[9]!=9){
            exit(0);
        }
        if(flag[5]== 5){
            node *p=c;
            count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("No such file or directory");
                    return 0;
                }
                while(readline(fp,line1)){
                    if(findsr(line1,pattern,cases,isword) == 0){
                        count++;
                    }
                }
                if(flag[9] == 9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3]==3 && flag[9]!=9){
                    if(flag[8]==8){
                        printf("%d\n",count);
                    }
                    else{
                        printf("%s : %d\n",file1,count);
                    }
                }
                count=0;
                fclose(fp);
                p=p->next;
            }
        }
        else if(flag[5]!= 5){
            node *p=c;
            count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("No such file or directory");
                    return 0;
                }
                num_file1=0;
                while(readline(fp,line1)){
                    num_file1++;
                    if(findsr(line1,pattern,cases,isword) == 1){
                        count++;
                        if(flag[4] != 4 && flag[3]!=3 && flag[9]!=9){
                            temp_line = for_oflag(line1,pattern,cases);
                            if(flag[8] == 8){
                                puts(temp_line);
                            }
                            else{
                                printf("%s : ",file1);
                                puts(temp_line);
                            }
                        }
                        if(flag[4] == 4 && flag[3]!=3 && flag[9]!=9){
                            temp_line = for_oflag(line1,pattern,cases);
                            if(flag[8] == 8){
                                printf("%d : ",num_file1);
                                puts(temp_line);
                            }
                            else{
                                printf("%s : %d :",file1,num_file1);
                                puts(temp_line);
                            }
                        }

                    }
                }
                if(flag[9] == 9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3]==3 && flag[9]!=9){
                    if(flag[8]==8){
                        printf("%d\n",count);
                    }
                    else{
                        printf("%s : %d\n",file1,count);
                    }
                }
                count=0;
                fclose(fp);
                p=p->next;
            }
        }
    return 0;
    }
    if(flag[4] == 4){
        if(flag[5] == 5){
            node* p=c;
            count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("No such file or directory");
                    return 0;
                }
                num_file1=0;
                while(readline(fp,line1)){
                    num_file1++;
                    if(findsr(line1,pattern,cases,isword)== 0){
                        count++;
                        if(flag[3] != 3 && flag[9]!= 9){
                            if(flag[8] == 8){
                                printf("%d : ",num_file1);
                                puts(line1);
                            }
                            else{
                                printf("%s : %d : ",file1,num_file1);
                                puts(line1);
                            }
                        }
                    }
                }
                if(flag[9] == 9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3] == 3 && flag[9] != 9){
                    if(flag[8] == 8){
                        printf("%d\n",count);
                    }
                    else{
                        printf("%s : %d\n",file1,count);
                    }
                }
            count=0;
            fclose(fp);
            p=p->next;
            }
        }
        else if(flag[5] != 5){
            node *p =c;
            count=0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("%s : No such file or directory",file1);
                    return 0;
                }
                num_file1=0;
                while(readline(fp,line1)){
                    num_file1++;
                    if(findsr(line1,pattern,cases,isword) == 1){
                        count++;
                        if(flag[3]!=3 && flag[9]!= 9){
                            if(flag[6]==6 ){
                                temp_line=for_oflag(line1,pattern,cases);
                            }
                            if(flag[6] == 6){
                                if(flag[8] == 8){
                                    printf("%d : ",num_file1);
                                    puts(temp_line);
                                }
                                else{
                                    printf("%s : %d :",file1,num_file1);
                                    puts(temp_line);
                                }
                            }
                            else{
                                if(flag[8] == 8){
                                    printf("%d : ",num_file1);
                                    puts(line1);
                                }
                                else{
                                    printf("%s : %d :",file1,num_file1);
                                    puts(line1);
                                }
                            }
                        }
                    }
                }
                if(flag[9] == 9){
                    if(count > 0)
                        puts(file1);
                }
                if(flag[3] == 3 && flag[9]!= 9){
                    if(flag[8] == 8){
                        printf("%d\n",count);
                    }
                    else{
                        printf("%s : %d\n",file1,num_file1);
                    }
                }
                count=0;
                fclose(fp);
                p=p->next;
            }
        }
        return 0;
    }
    // flag l

    if(flag[9] == 9){
        if(flag[5] == 5){
            node *p=c;
            count =0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("%s : No such file or directory",file1);
                    return 0;
                }
                while(readline(fp,line1)){
                    if(findsr(line1,pattern,cases,isword) == 0){
                        count++;
                    }
                }
                if(count > 0)
                    puts(file1);
                count=0;
                fclose(fp);
                p=p->next;
            }
        }
        else if(flag[5]!=5){
            node *p=c;
            count =0;
            while(p){
                strcpy(file1,p->file_name);
                fp=fopen(file1,"r");
                if(!fp){
                    printf("%s : No such file or directory",file1);
                    return 0;
                }
                while(readline(fp,line1)){
                    if(findsr(line1,pattern,cases,isword) == 1){
                        count++;
                    }
                }
                if(count > 0)
                    puts(file1);
                count=0;
                fclose(fp);
                p=p->next;
            }
        }
        return 0;
    }
    // v flag
    // combination of v with f,r,o,m,n,l is already done
    // with c , H,h ,i,w remained
    if(flag[5] == 5){
        node *p=c;
        count=0;
        while(p){
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("%s : No such file or directory",file1);
                return 0;
            }
            while(readline(fp,line1)){
                if(findsr(line1,pattern,cases ,isword) == 0){
                    count++;
                    if(flag[3]!= 3){
                        if(flag[8] == 8){
                            puts(line1);
                        }
                        else{
                            printf("%s : ",file1);
                            puts(line1);
                        }
                    }
                }
            }
            if(flag[3] == 3){
                if(flag[8] == 8){
                    printf("%d\n",count);
                }
                else{
                    printf("%s : %d\n",file1,count);
                }
            }
         count=0;
         fclose(fp);
         p=p->next;
        }
        return 0;
    }
    // flag c i.e flag 3
    // c will have combination with h,H,i, w
    // combination of vc is already done
    if(flag[3] == 3){
        node *p=c;
        count=0;
        while(p){
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("%s : No such file or directory",file1);
                return 0;
            }
            while(readline(fp,line1)){
                if(findsr(line1,pattern,cases,isword) == 1){
                    count++;
                }
            }
            if(flag[8] == 8){
                printf("%d\n",count);
            }
            else{
                printf("%s : %d\n",file1,count);
            }
            count=0;
            fclose(fp);
            p=p->next;
        }
        return 0;
    }
    // flag 7 will be considered
    if(flag[7] == 7){
        node* p=c;
        count=0;
        while(p){
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("%s : No such file or directory",file1);
                return 0;
            }
            while(readline(fp,line1)){
                if(findsr(line1,pattern,cases,isword) == 1){
                    printf("%s : ",file1);
                    puts(line1);
                }
            }
            p=p->next;
        }
        return 0;
    }
    if(flag[8] == 8){
        node* p=c;
        count=0;
        while(p){
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("%s : No such file or directory",file1);
                return 0;
            }
            while(readline(fp,line1)){
                if(findsr(line1,pattern,cases,isword) == 1){
                    puts(line1);
                }
            }
            p=p->next;
        }
        return 0;
    }
    // w flag
    if(flag[2] == 2){
        node* p=c;
        count=0;
        while(p){
            strcpy(file1,p->file_name);
            //printf("%s\n",file1);
            fp=fopen(file1,"r");
            if(!fp){
                printf("%s : No such file or directory",file1);
                return 0;
            }
           // printf("%s : read\n",file1);
            while(readline(fp,line1)){
                if(findsr(line1,pattern,cases,isword) == 1){
                    printf("%s : ",file1);
                    puts(line1);
                }
            }
            fclose(fp);
            p=p->next;
        }
        return 0;
    }
    // i flag
    if(flag[1] == 1){
        node* p=c;
        count=0;
        while(p){
            strcpy(file1,p->file_name);
            fp=fopen(file1,"r");
            if(!fp){
                printf("%s : No such file or directory",file1);
                return 0;
            }
            while(readline(fp,line1)){
                if(findsr(line1,pattern,0,isword) == 1){
                    printf("%s : ",file1);
                    puts(line1);
                }
            }
            p=p->next;
        }
        return 0;
    }

 return 0;
}
