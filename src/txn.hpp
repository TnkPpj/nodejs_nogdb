#include <memory>
#include <nan.h>
#include <nogdb/nogdb.h>

class Txn : public Nan::ObjectWrap {
public:
    std::shared_ptr<nogdb::Txn> base;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static NAN_METHOD(commit);

private:
    explicit Txn(std::shared_ptr<nogdb::Txn> txn_) : base(txn_) {} ;

    static Nan::Persistent<v8::FunctionTemplate> constructor;
};