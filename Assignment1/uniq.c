#include "types.h"
#include "stat.h"
#include "user.h"
#define MAX 900

char buf[MAX];

void uniq(int fd, char *name, int occurance,int print_dup,int ignore_case) {
    int i, n,j,r,f;
    int l, w, c;
    l = w = c = j = r = f = 0;
    char prevLine[MAX], thisLine[MAX];
    char prepre[MAX];
    int count_dup;
    count_dup = 1;
    char *prev, *this,*prep;
    prev = prevLine;
    this = thisLine;
    prep = prepre;
    
    int ignore_case_cmp(const char* this,const char* prev){
                const char* s1 = prev;
                const char* s2 = this;
                char c1, c2;
                while(*s1 != '\0'){
                        if(*s1 <= 'Z' && *s1 >= 'A'){
                                c1 = *s1 + 32;
                        } else {
                                c1 = *s1;
                        }
                        if (*s2 <= 'Z' && *s2 >= 'A'){
                                c2 = *s2 + 32;
                        } else {
                                c2 = *s2;
                        }
                        if ((c1-c2) != 0)  return 1;
                        s1++;
                        s2++;
                }
                if(*s2 == '\0') return 0;
                return 1;
    }
    void outputLine(char temp[],int f){
            if(occurance){ 
                printf(1,"%d %s\n",count_dup,temp);
            } else {
                if(print_dup){
                    if(count_dup>1){
                        printf(1,"%s\n",temp);
                    }
                } else 
                    printf(1,"%s\n",temp);
            }
            if(f){
                strcpy(temp,thisLine);
                memset(thisLine, 0, MAX);
            }
    }

    while((n = read(fd, buf, sizeof(buf))) > 0){
        
        for(i=0; i<n; i++){
            if(buf[i] == '\n'){  
                if(l != 0){
                    memset(prepre, 0, MAX);
                    strcpy(prepre,prevLine);
                    
                    if(ignore_case){ 
                        if(ignore_case_cmp(this,prev) != 0){ 
                            outputLine(prevLine,1);
                            count_dup = 1;
                        } else { 
                            count_dup++;
                        }
                    } else {
                        if(strcmp(thisLine,prevLine) != 0){
                            outputLine(prevLine,1);
                            count_dup = 1;
                        } else {
                            count_dup++;
                        }
                    }
                } else {
                    strcpy(prevLine,thisLine);
                }
                l++;
                c = 0;
            } else {
                thisLine[c] = buf[i];
                c++;
            }
        }
        
    
    
    }
    if(ignore_case){
        if(ignore_case_cmp(this,prev) != 0){ 
            outputLine(prevLine,0);
            count_dup = 1;
            if(strcmp(thisLine,"") != 0)
                outputLine(thisLine,0);
        } else {  
            if(ignore_case_cmp(this,prep) != 0){
                count_dup = 2;
                if(strcmp(thisLine,"") != 0)
                    outputLine(prevLine,0);
            } else {
                outputLine(prepre,0);
            }
        }
    } else {
        if(strcmp(thisLine,prevLine) != 0){ 
            outputLine(prevLine,0);
            count_dup = 1;
            if(strcmp(thisLine,"") != 0)
                outputLine(thisLine,0);
        } else { 
            if(strcmp(thisLine,prepre) != 0){
                count_dup = 2;
                if(strcmp(thisLine,"") != 0)
                    outputLine(prevLine,0);
            } else {
                outputLine(prepre,0);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int fd, i;
    char *name;
    int occur, dup, ig;
    occur=dup=ig=0;
    
    fd = 0;
    name = "";
    if (argc <= 1) {
        uniq(fd, name, occur,dup,ig);
        exit();
    }
    
    else {
        for (i = 0; i < argc; i++) {
            if(strcmp(argv[i],"-i") == 0){
                ig = 1;
            }else if(strcmp(argv[i],"-c") == 0){ 
                occur = 1;
            }else if(strcmp(argv[i],"-d") == 0){ 
                dup = 1;
            }
            
            if (atoi(argv[i]) == 0 && *argv[i] != '0' && *argv[i] != '-') {
                if ((fd = open(argv[i], 0)) < 0) {
                    printf(1, "uniq: cannot open %s\n", argv[i]);
                    exit();
                }
            }
            else {
                argv[i]++;
            }
        }
        if(dup == 1 && occur == 1){
            printf(1, "uniq: -d -c cannot be execute in the same time %s\n", argv[i]);
            exit();
        } else {
            uniq(fd, name, occur,dup,ig);
            close(fd);
            exit();
        }
        
    }
}