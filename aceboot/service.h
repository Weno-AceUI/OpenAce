// aceboot/service.h

#ifndef SERVICE_H
#define SERVICE_H

#include <sys/types.h>

typedef struct {
    char* name;
    char* exec_path;
    char** args;
    pid_t pid;
    int running;
} Service;

void start_service(Service* svc);
void stop_service(Service* svc);

#endif
