#include <stdio.h>

//#include "log.h"
#include "cmdargs.h"

char *cmdargs[] = {"arg1", "arg2", "arg3"};

int main(int argc, char *argv[]) {
        //  LOG_INFO("Start");
    table *t = ca_init(3);
    ca_parse_args(argc, argv, t);
        //if (ca_is_arg("arg1", t))
        // printf("%s is set.\n", "arg1");
    return 0;
}
