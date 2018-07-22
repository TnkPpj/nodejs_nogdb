#include <memory>
#include <nan.h>
#include <nogdb/nogdb.h>

#include "classFilter.hpp"
#include "condition.hpp"
#include "record.hpp"
#include "txn.hpp"
#include "toV8type.hpp"

#include "vertex.hpp"

NAN_MODULE_INIT(Vertex::Init)
{
    v8::Handle<v8::Object> v = v8::Object::New(v8::Isolate::GetCurrent());

    Nan::SetMethod(v, "create", create);
    Nan::SetMethod(v, "update", update);
    Nan::SetMethod(v, "destroy", destroy);
    Nan::SetMethod(v, "get", get);
    Nan::SetMethod(v, "getInEdge", getInEdge);
    Nan::SetMethod(v, "getOutEdge", getOutEdge);
    Nan::SetMethod(v, "getAllEdge", getAllEdge);
    Nan::SetMethod(v, "getIndex", getIndex);

    target->Set(Nan::New("Vertex").ToLocalChecked(), v);
}

NAN_METHOD(Vertex::create)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string className = *Nan::Utf8String(info[1]->ToString());
    Record *record = Nan::ObjectWrap::Unwrap<Record>(info[2]->ToObject());
    nogdb::RecordDescriptor recD = nogdb::Vertex::create(*txn->base, className, record->base);
    info.GetReturnValue().Set(v8RecordDescriptor(recD));
}

NAN_METHOD(Vertex::update)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());

    v8::Local<v8::Object> recD = info[1]->ToObject();
    v8::Local<v8::Object> rid = Nan::Get(recD, Nan::New<v8::String>("rid").ToLocalChecked()).ToLocalChecked()->ToObject();
    unsigned int classId = Nan::Get(rid, Nan::New<v8::String>("classId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    unsigned int positionId = Nan::Get(rid, Nan::New<v8::String>("positionId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    nogdb::RecordDescriptor recordD(classId,positionId);

    Record *record = Nan::ObjectWrap::Unwrap<Record>(info[2]->ToObject());
    nogdb::Vertex::update(*txn->base, recordD, record->base);
    info.GetReturnValue().SetUndefined();
}

NAN_METHOD(Vertex::destroy)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    // ver 1 recordD
    if(info[1]->IsObject()){
        v8::Local<v8::Object> recD = info[1]->ToObject();
        v8::Local<v8::Object> rid = Nan::Get(recD, Nan::New<v8::String>("rid").ToLocalChecked()).ToLocalChecked()->ToObject();
        unsigned int classId = Nan::Get(rid, Nan::New<v8::String>("classId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
        unsigned int positionId = Nan::Get(rid, Nan::New<v8::String>("positionId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
        nogdb::RecordDescriptor recordD(classId,positionId);

        nogdb::Vertex::destroy(*txn->base, recordD);
    }
    // ver 2 className
    else if(info[1]->IsString()){
        std::string className = *Nan::Utf8String(info[1]->ToString());
        nogdb::Vertex::destroy(*txn->base, className);
    } else {
        return Nan::ThrowError(Nan::New("Vertex::destroy - invalid arugment(s)").ToLocalChecked());
    }
    info.GetReturnValue().SetUndefined();
}

NAN_METHOD(Vertex::get)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string className = *Nan::Utf8String(info[1]->ToString());
    // get
    if(info.Length() == 2){
        nogdb::ResultSet resultSet = nogdb::Vertex::get(*txn->base,className);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }
    // get with condition
    else if(info.Length() == 3){
        Condition *cond = Nan::ObjectWrap::Unwrap<Condition>(info[2]->ToObject());
        nogdb::ResultSet resultSet = nogdb::Vertex::get(*txn->base,className,cond->base);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }else {
        return Nan::ThrowError(Nan::New("Vertex::get - invalid arugment(s)").ToLocalChecked());
    }
}

NAN_METHOD(Vertex::getInEdge)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    v8::Local<v8::Object> recD = info[1]->ToObject();
    v8::Local<v8::Object> rid = Nan::Get(recD, Nan::New<v8::String>("rid").ToLocalChecked()).ToLocalChecked()->ToObject();
    unsigned int classId = Nan::Get(rid, Nan::New<v8::String>("classId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    unsigned int positionId = Nan::Get(rid, Nan::New<v8::String>("positionId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    nogdb::RecordDescriptor recordD(classId,positionId);
    // getInEdge
    if(info.Length() == 3){
        ClassFilter *classF = Nan::ObjectWrap::Unwrap<ClassFilter>(info[2]->ToObject());
        nogdb::ResultSet resultSet = nogdb::Vertex::getInEdge(*txn->base,recordD,classF->base);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }
    // getInEdge with condition
    else if(info.Length() == 4){
        Condition *cond = Nan::ObjectWrap::Unwrap<Condition>(info[2]->ToObject());
        ClassFilter *classF = Nan::ObjectWrap::Unwrap<ClassFilter>(info[3]->ToObject());
        nogdb::ResultSet resultSet = nogdb::Vertex::getInEdge(*txn->base,recordD,cond->base,classF->base);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }else {
        return Nan::ThrowError(Nan::New("Vertex::getInEdge - invalid arugment(s)").ToLocalChecked());
    }
}

NAN_METHOD(Vertex::getOutEdge)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    v8::Local<v8::Object> recD = info[1]->ToObject();
    v8::Local<v8::Object> rid = Nan::Get(recD, Nan::New<v8::String>("rid").ToLocalChecked()).ToLocalChecked()->ToObject();
    unsigned int classId = Nan::Get(rid, Nan::New<v8::String>("classId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    unsigned int positionId = Nan::Get(rid, Nan::New<v8::String>("positionId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    nogdb::RecordDescriptor recordD(classId,positionId);
    // getOutEdge
    if(info.Length() == 3){
        ClassFilter *classF = Nan::ObjectWrap::Unwrap<ClassFilter>(info[2]->ToObject());
        nogdb::ResultSet resultSet = nogdb::Vertex::getOutEdge(*txn->base,recordD,classF->base);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }
    // getOutEdge with condition
    else if(info.Length() == 4){
        Condition *cond = Nan::ObjectWrap::Unwrap<Condition>(info[2]->ToObject());
        ClassFilter *classF = Nan::ObjectWrap::Unwrap<ClassFilter>(info[3]->ToObject());
        nogdb::ResultSet resultSet = nogdb::Vertex::getOutEdge(*txn->base,recordD,cond->base,classF->base);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }else {
        return Nan::ThrowError(Nan::New("Vertex::getOutEdge - invalid arugment(s)").ToLocalChecked());
    }
}

NAN_METHOD(Vertex::getAllEdge)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    v8::Local<v8::Object> recD = info[1]->ToObject();
    v8::Local<v8::Object> rid = Nan::Get(recD, Nan::New<v8::String>("rid").ToLocalChecked()).ToLocalChecked()->ToObject();
    unsigned int classId = Nan::Get(rid, Nan::New<v8::String>("classId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    unsigned int positionId = Nan::Get(rid, Nan::New<v8::String>("positionId").ToLocalChecked()).ToLocalChecked()->Uint32Value();
    nogdb::RecordDescriptor recordD(classId,positionId);
    // getAllEdge
    if(info.Length() == 3){
        ClassFilter *classF = Nan::ObjectWrap::Unwrap<ClassFilter>(info[2]->ToObject());
        nogdb::ResultSet resultSet = nogdb::Vertex::getAllEdge(*txn->base,recordD,classF->base);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }
    // getAllEdge with condition
    else if(info.Length() == 4){
        Condition *cond = Nan::ObjectWrap::Unwrap<Condition>(info[2]->ToObject());
        ClassFilter *classF = Nan::ObjectWrap::Unwrap<ClassFilter>(info[3]->ToObject());
        nogdb::ResultSet resultSet = nogdb::Vertex::getAllEdge(*txn->base,recordD,cond->base,classF->base);
        info.GetReturnValue().Set(v8ResultSet(resultSet));
    }else {
        return Nan::ThrowError(Nan::New("Vertex::getAllEdge - invalid arugment(s)").ToLocalChecked());
    }
}

NAN_METHOD(Vertex::getIndex)
{
    Txn *txn = Nan::ObjectWrap::Unwrap<Txn>(info[0]->ToObject());
    std::string className = *Nan::Utf8String(info[1]->ToString());
    Condition *cond = Nan::ObjectWrap::Unwrap<Condition>(info[3]->ToObject());

    nogdb::ResultSet resultSet = nogdb::Vertex::getIndex(*txn->base,className,cond->base);
    info.GetReturnValue().Set(v8ResultSet(resultSet));
}
