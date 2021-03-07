#include "libwk.h"

int main()
{
    const char fname[] = "../job/job.lua";
    wk w;
    wkExecScri(w, fname);
    return 0;
}
