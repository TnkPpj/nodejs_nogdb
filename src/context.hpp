#include <nan.h>
#include <nogdb/nogdb.h>

class Context : public Nan::ObjectWrap {
public:
    nogdb::Context base;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);

private:
    explicit Context(const std::string &path) : base(path) {} ;

    static Nan::Persistent<v8::FunctionTemplate> constructor;
};