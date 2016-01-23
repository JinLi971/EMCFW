#ifndef DEBUGHELPER_HH
#define DEBUGHELPER_HH

static void Debug(bool condition = true)
{
    int debug = 1;
    int noUse = 0;
    while(condition && debug)
    {
        noUse = 1;
    }
}

#endif // DEBUGHELPER_HH
