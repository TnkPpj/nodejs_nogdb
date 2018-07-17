#include <nan.h>

#include "context.hpp"
#include "txn.hpp"
#include "class.hpp"

NAN_MODULE_INIT(InitModule)
{
    Context::Init(target);
    Txn::Init(target);
    Class::Init(target);
}

NODE_MODULE(nogdb_js, InitModule);