#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int size = 1 << 16; // 01 is 2 in  binary and we move it 16 bits to left so we'll get: 2^16 = 65536 in decimal
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = i;
    int child_num = 4;
    int part = size / child_num;

    int pids[child_num];
    int statuses[child_num];
    int n = 0;
    int sumP = 0;
    // Call the new fork system call
    int curr_proc = forkn(child_num, pids);

    if (curr_proc < 0)
    {
        printf("forkn failed\n");
        exit(1, "");
    }

    if (curr_proc > 0) // forkn>0 => child process
    {
        int start = (curr_proc - 1) * part;
        int finish = curr_proc * part;
        if (curr_proc == child_num) // case size / child_num not return a complete number
            finish = size;
        int sum = 0;
        for (int i = start; i < finish; i++)
            sum = sum + arr[i];
        printf("sum: %d\n");
        exit(sum, "");
    }

    // we'll get here only if forkn=0, this is the parent process
    if (waitall(&n, statuses) != 0)
    {
        printf("Parent: waitall failed\n");
        exit(1, "waitall failed");
    }

    // Print results
    if (child_num == n)
        printf("all childen that were created have finished :)\n");
    else
        printf("not all childen that were created have finished :(\n");
    printf("number of children completed successfully: %d\n", n);

    for (int i = 0; i < n; i++)
        printf("child pid: %d \n", pids[i]);

    for (int i = 0; i < n; i++)
        sumP = sumP + statuses[i];

    printf("total parent sum: %d\n", sumP);

    exit(0, "");
}
