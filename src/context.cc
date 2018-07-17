#include <nan.h>
#include <nogdb/nogdb.h>

#include "context.hpp"

Nan::Persistent<v8::FunctionTemplate> Context::constructor;

NAN_MODULE_INIT(Context::Init)
{
    v8::Local<v8::FunctionTemplate> constructTemplate =
        Nan::New<v8::FunctionTemplate>(Context::New);

    constructor.Reset(constructTemplate);
    constructTemplate->InstanceTemplate()->SetInternalFieldCount(1);
    constructTemplate->SetClassName(Nan::New("Context").ToLocalChecked());

    target->Set(Nan::New("Context").ToLocalChecked(), constructTemplate->GetFunction());
}

NAN_METHOD(Context::New)
{
    if (!info.IsConstructCall())
    {
        return Nan::ThrowError(
            Nan::New("Context::New - called without new keyword").ToLocalChecked());
    }

    if (info.Length() == 1 && info[0]->IsString())
    {
        Context *ctx = new Context(*(Nan::Utf8String(info[0]->ToString())));
        ctx->Wrap(info.Holder());

        info.GetReturnValue().Set(info.Holder());
    }
    else
    {
        return Nan::ThrowError(Nan::New("Context::New - invalid arugment(s)").ToLocalChecked());
    }
}