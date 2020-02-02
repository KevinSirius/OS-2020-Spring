#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

int main(int argc, char *argv[])
{
    int fd;
    
    for (i = 1; i < arc; i++){
        if ((fd = open(argv[i], 0) < 0){
            printf(1, "uniq: cannot open %s\n", argv[i]);
            exit();
        }
        uniq(fd, argv[i]);
        close(fd);
    }
    exit();
}

void uniq(int fd, char *name)
{   
    int l, w, c, i;
    l = w = c = 0;
    int n;
    while ((n = read(fd, buf, sizeof(buf))) > 0){   //read() returns # of bytes read
        char *lines[sizeof(buf)];
        i = 0;
        while (i < n){
            while (buf[i] != '\n'){
                lines[l] += buf[i];
            }
        }
 }
}