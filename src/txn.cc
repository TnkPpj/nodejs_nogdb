#include <memory>
#include <nan.h>
#include <nogdb/nogdb.h>

#include "context.hpp"

#include "txn.hpp"

Nan::Persistent<v8::FunctionTemplate> Txn::constructor;

NAN_MODULE_INIT(Txn::Init)
{
    v8::Local<v8::FunctionTemplate> constructTemplate =
        Nan::New<v8::FunctionTemplate>(Txn::New);

    constructor.Reset(constructTemplate);
    constructTemplate->InstanceTemplate()->SetInternalFieldCount(1);
    constructTemplate->SetClassName(Nan::New("Txn").ToLocalChecked());

    Nan::SetPrototypeMethod(constructTemplate, "commit", commit);

    target->Set(Nan::New("Txn").ToLocalChecked(), constructTemplate->GetFunction());
}

NAN_METHOD(Txn::New)
{
    if (!info.IsConstructCall())
    {
        return Nan::ThrowError(
            Nan::New("Txn::New - called without new keyword").ToLocalChecked());
    }

    Context *ctx = Nan::ObjectWrap::Unwrap<Context>(info[0]->ToObject());

    std::shared_ptr<nogdb::Txn> baseTxn = std::make_shared<nogdb::Txn>(ctx->base, nogdb::Txn::Mode::READ_WRITE);

    Txn *txn = new Txn(baseTxn);
    txn->Wrap(info.Holder());

    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Txn::commit)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info.This());
    txn->base->commit();
    info.GetReturnValue().SetUndefined();
}