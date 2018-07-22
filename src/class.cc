#include <memory>
#include <nan.h>
#include <nogdb/nogdb.h>

#include "txn.hpp"

#include "class.hpp"

#include "toV8type.hpp"

NAN_MODULE_INIT(Class::Init)
{
    v8::Handle<v8::Object> c = v8::Object::New(v8::Isolate::GetCurrent());

    Nan::SetMethod(c, "create", create);
    Nan::SetMethod(c, "createExtend", createExtend);
    Nan::SetMethod(c, "drop", drop);
    Nan::SetMethod(c, "alter", alter);

    target->Set(Nan::New("Class").ToLocalChecked(), c);
}

NAN_METHOD(Class::create)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string className = *Nan::Utf8String(info[1]->ToString());
    std::string type = *Nan::Utf8String(info[2]->ToString());

    nogdb::ClassType classType;
    if(type=="VERTEX")      classType = nogdb::ClassType::VERTEX;
    else if(type=="EDGE")   classType = nogdb::ClassType::EDGE;
    else Nan::ThrowError("ClassType Invalid");
    
    nogdb::ClassDescriptor classD = nogdb::Class::create(*txn->base, className, classType);

    info.GetReturnValue().Set(v8ClassDescriptor(classD));
}

NAN_METHOD(Class::createExtend)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string className = *Nan::Utf8String(info[1]->ToString());
    std::string superClass = *Nan::Utf8String(info[2]->ToString());

    nogdb::ClassDescriptor classD = nogdb::Class::createExtend(*txn->base, className, superClass);

    info.GetReturnValue().Set(v8ClassDescriptor(classD));
}

NAN_METHOD(Class::drop)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string className = *Nan::Utf8String(info[1]->ToString());

    nogdb::Class::drop(*txn->base, className);

    info.GetReturnValue().SetUndefined();
}

NAN_METHOD(Class::alter)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string oldClassName = *Nan::Utf8String(info[1]->ToString());
    std::string newClassName = *Nan::Utf8String(info[2]->ToString());

    nogdb::Class::alter(*txn->base, oldClassName, newClassName);

    info.GetReturnValue().SetUndefined();
}
