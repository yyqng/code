#include "otst.h"
#include "test.h"
#include "mem.h"
 
int mem_test(int argc, char *argv[])
{
    
    if(argc < 2){
        printf("Usage:test <process_name> [user]\n");
        return 1;
    }
    
    unsigned int pid=0;
    
    if(argc > 2){
        pid = get_pid(argv[1],argv[2]);
    }
    else{
        pid = get_pid(argv[1]);
    }
    
    printf("pid=%d\n",pid);
    printf("pcpu=%f\n",get_proc_cpu(pid));
    printf("procmem=%d\n",get_proc_mem(pid));
    printf("virtualmem=%d\n",get_proc_virtualmem(pid)); 
    return 0;
}

int main()
{
    //test(vector<int>());
    //testSocket();
    //echo_client();
    //thread_test();
    set_mem_test();
}
