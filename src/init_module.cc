#include <nan.h>

#include "classFilter.hpp"
#include "condition.hpp"
#include "context.hpp"
#include "record.hpp"
#include "txn.hpp"
#include "class.hpp"
#include "property.hpp"
#include "vertex.hpp"
#include "edge.hpp"
#include "db.hpp"
#include "traverse.hpp"

NAN_MODULE_INIT(InitModule)
{
    ClassFilter::Init(target);
    Condition::Init(target);
    Context::Init(target);
    Record::Init(target);
    Txn::Init(target);
    Class::Init(target);
    Property::Init(target);
    Vertex::Init(target);
    Edge::Init(target);
    Db::Init(target);
    Traverse::Init(target);
}

NODE_MODULE(nogdb_js, InitModule);