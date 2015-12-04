#ifndef CONSTANTS_HH
#define CONSTANTS_HH

namespace DataSet {

static const int ROOT_ID = 0;
static const unsigned int RETRY_LIMIT = 5;

enum ERROR_CODE
{
    EXECUTOR_INIT_EXCEPTION = 0,
    EXECUTOR_RUN_EXCEPTION
};

}

#endif // CONSTANTS_HH
