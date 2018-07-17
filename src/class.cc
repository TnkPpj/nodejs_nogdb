#include <memory>
#include <nan.h>
#include <nogdb/nogdb.h>

#include "txn.hpp"

#include "class.hpp"

NAN_MODULE_INIT(Class::Init)
{
    v8::Handle<v8::Object> c = v8::Object::New(v8::Isolate::GetCurrent());

    Nan::SetMethod(c, "create", create);

    target->Set(Nan::New("Class").ToLocalChecked(), c);
}

NAN_METHOD(Class::create)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string className = *Nan::Utf8String(info[1]->ToString());
    
    nogdb::ClassDescriptor classD = nogdb::Class::create(*txn->base, className, nogdb::ClassType::VERTEX);

    info.GetReturnValue().SetUndefined();
}