#include <nan.h>
#include <nogdb/nogdb.h>

class Class {
public:
    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(create);
};