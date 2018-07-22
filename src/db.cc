#include <nogdb/nogdb.h>

#include "txn.hpp"

#include "db.hpp"

#include "toV8type.hpp"

NAN_MODULE_INIT(Db::Init)
{
    v8::Handle<v8::Object> d = v8::Object::New(v8::Isolate::GetCurrent());

    Nan::SetMethod(d, "getRecord", getRecord);
    Nan::SetMethod(d, "getSchema", getSchema);
    Nan::SetMethod(d, "getDbInfo", getDbInfo);

    target->Set(Nan::New("Db").ToLocalChecked(), d);
}

NAN_METHOD(Db::getRecord)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());

    v8::Local<v8::Object> recD = info[1]->ToObject();
    v8::Local<v8::Object> rid = Nan::Get(recD, Nan::New<v8::String>("rid").ToLocalChecked()).ToLocalChecked()->ToObject();
    unsigned int classId = Nan::Get(rid, Nan::New<v8::String>("classId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    unsigned int positionId = Nan::Get(rid, Nan::New<v8::String>("positionId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    nogdb::RecordDescriptor recordD(classId,positionId);

    nogdb::Record record = nogdb::Db::getRecord(*txn->base, recordD);
    info.GetReturnValue().Set(v8Record(record));
}

NAN_METHOD(Db::getSchema)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    // ver 1 only txn
    if(info.Length() == 1){
        std::vector<nogdb::ClassDescriptor> classDs = nogdb::Db::getSchema(*txn->base);
        v8::Local<v8::Array> retval = Nan::New<v8::Array>(classDs.size());
        int i = 0;
        for(std::vector<nogdb::ClassDescriptor>::iterator it = classDs.begin(); it != classDs.end(); ++it)
        {
            Nan::Set(retval, i, v8ClassDescriptor(*it));
            i++;
        }
        info.GetReturnValue().Set(retval);
    }
    // ver 2 txn & className
    else if (info.Length() == 2 && info[1]->IsString()){
        std::string className = *Nan::Utf8String(info[1]->ToString());
        nogdb::ClassDescriptor classD = nogdb::Db::getSchema(*txn->base,className);
        info.GetReturnValue().Set(v8ClassDescriptor(classD));
    } 
    // ver 3 txn & classId
    else if (info.Length() == 2 && info[1]->IsUint32()){
        unsigned int classId = info[1]->Uint32Value();
        nogdb::ClassDescriptor classD = nogdb::Db::getSchema(*txn->base,classId);
        info.GetReturnValue().Set(v8ClassDescriptor(classD));
    } else {
        return Nan::ThrowError(Nan::New("Db::getSchema - invalid arugment(s)").ToLocalChecked());
    }
}

NAN_METHOD(Db::getDbInfo)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    nogdb::DBInfo dbInfo = nogdb::Db::getDbInfo(*txn->base);
    info.GetReturnValue().Set(v8DBInfo(dbInfo));
}