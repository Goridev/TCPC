#include "nsx_conf.h"
#ifndef tcp_cmd_h
#define tcp_cmd_h

typedef struct nsx_cmd nsx_cmd;
struct nsx_cmd
{
    char buffer[MAX];
    nsx_cmd (*exit)(nsx_cmd *);
};

nsx_cmd nsx_cmd_exit(nsx_cmd *self)
{
    if ((strncmp(self->buffer, "exit", 4)) == 0) {
        printf(""CLIENT_LOG" client exit...\n");
    }
}


#endif