#include <memory>
#include <nan.h>
#include <nogdb/nogdb.h>

#include "record.hpp"

Nan::Persistent<v8::FunctionTemplate> Record::constructor;

NAN_MODULE_INIT(Record::Init)
{
    v8::Local<v8::FunctionTemplate> constructTemplate =
        Nan::New<v8::FunctionTemplate>(Record::New);

    constructor.Reset(constructTemplate);
    constructTemplate->InstanceTemplate()->SetInternalFieldCount(1);
    constructTemplate->SetClassName(Nan::New("Record").ToLocalChecked());

    Nan::SetPrototypeMethod(constructTemplate, "set", Record::set);
    Nan::SetPrototypeMethod(constructTemplate, "getProperties", Record::getProperties);
    Nan::SetPrototypeMethod(constructTemplate, "unset", Record::unset);
    Nan::SetPrototypeMethod(constructTemplate, "size", Record::size);
    Nan::SetPrototypeMethod(constructTemplate, "empty", Record::empty);
    Nan::SetPrototypeMethod(constructTemplate, "clear", Record::clear);

    target->Set(Nan::New("Record").ToLocalChecked(), constructTemplate->GetFunction());
}

NAN_METHOD(Record::New)
{
    Record *record = new Record();
    record->Wrap(info.Holder());

    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Record::set) 
{
    Record *record = Nan::ObjectWrap::Unwrap<Record>(info.This());
    if (info.Length() == 2 && info[0]->IsString() && info[1]->IsString())
    {
        std::string propName = *Nan::Utf8String(info[0]->ToString());
        std::string value = *Nan::Utf8String(info[1]->ToString());
        record->base = record->base.set(propName,value);
        info.GetReturnValue().SetUndefined();
    } 
    else if (info.Length() == 2 && info[0]->IsString() && info[1]->IsNumber())
    {
        std::string propName = *Nan::Utf8String(info[0]->ToString());
        double value = info[1]->NumberValue();
        record->base = record->base.set(propName,value);
        info.GetReturnValue().SetUndefined();
    }
    else
    {
        return Nan::ThrowError(Nan::New("Record::set - invalid arugment(s)").ToLocalChecked());
    }
}

NAN_METHOD(Record::getProperties) 
{
    Record *record = Nan::ObjectWrap::Unwrap<Record>(info.This());
    std::vector<std::string> properties =  record->base.getProperties();
    v8::Local<v8::Array> retval = Nan::New<v8::Array>(record->base.size());
    int i = 0;
    for(std::vector<std::string>::iterator it = properties.begin(); it != properties.end(); ++it)
    {
        std::string property (*it);
        Nan::Set(retval, i, Nan::New<v8::String>(property).ToLocalChecked());
        i++;
    }
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(Record::unset) 
{
    Record *record = Nan::ObjectWrap::Unwrap<Record>(info.This());
    if (info.Length() == 1 && info[0]->IsString())
    {
        std::string propName = *Nan::Utf8String(info[0]->ToString());
        record->base.unset(propName);
        info.GetReturnValue().SetUndefined();
    }
    else
    {
        return Nan::ThrowError(Nan::New("Record::unset - invalid arugment(s)").ToLocalChecked());
    }
}

NAN_METHOD(Record::size) 
{
    Record *record = Nan::ObjectWrap::Unwrap<Record>(info.This());
    int size =  record->base.size();
    info.GetReturnValue().Set(size);
}

NAN_METHOD(Record::empty) 
{
    Record *record = Nan::ObjectWrap::Unwrap<Record>(info.This());
    bool empty = record->base.empty();
    v8::Local<v8::Boolean> retval = Nan::New(empty);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(Record::clear) 
{
    Record *record = Nan::ObjectWrap::Unwrap<Record>(info.This());
    record->base.clear();
    info.GetReturnValue().SetUndefined();
}
