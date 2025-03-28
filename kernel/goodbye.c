
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char exit_msg[32] = "Goodbye World xv6";
    exit(0, *exit_msg);
}
