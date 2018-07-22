const nogdb = require("./build/Debug/nogdb_js")

console.log("new ctx...");
const ctx = new nogdb.Context("sample.db");

// console.log("ctx getMaxVersionId..."); 
// console.log(ctx.getMaxVersionId());

// console.log("ctx getMaxTxnId...");
// console.log(ctx.getMaxTxnId());

// console.log("ctx getMinActiveTxnId...");
// console.log(ctx.getMinActiveTxnId());

console.log("new txn...");
var txn = new nogdb.Txn(ctx,"READ_WRITE");

// console.log("record size");
// console.log(r1.size());

// console.log("name..");
// console.log(r1.getReal("name"));
// console.log(r1.getText("name"));

// console.log(r1.getProperties());

// console.log("record unset...");
// r1.unset("name");

// console.log("record size");
// console.log(r1.size());

// console.log("record unset...");
// r1.clear();

// console.log("record size");
// console.log(r1.size());


// console.log("txn getTxnId...");
// console.log(txn.getTxnId());

// console.log("txn getVersionId...");
// console.log(txn.getVersionId());

// console.log("txn getTxnMode...");
// console.log(txn.getTxnMode());

console.log("create class...");
console.log(nogdb.Class.create(txn, 'my_vertex',"VERTEX"));

console.log("createExtend class...");
console.log(nogdb.Class.createExtend(txn, 'my_son','my_vertex'));

console.log("alter class...");
nogdb.Class.alter(txn, 'my_vertex','your_dad');

console.log("add property...");
console.log(nogdb.Property.add(txn,'my_son','first_name','TEXT'));
console.log(nogdb.Property.add(txn,'my_son','age','TINYINT'));

console.log("alter property...");
nogdb.Property.alter(txn,'my_son','first_name','name');

console.log("new record...");
let r1 = new nogdb.Record();

console.log("record set...");
r1.set("name","A");
r1.set("age",9);

console.log(r1.getProperties());

console.log("new vertex...");
recD = nogdb.Vertex.create(txn,'my_son',r1);
console.log(recD);

r1.clear();
r1.set("name","B");
r1.set("age",6);
recD2 = nogdb.Vertex.create(txn,'my_son',r1);

console.log("vertex get...");
res =  nogdb.Vertex.get(txn,'my_son');
console.log(res);

console.log("new classFilter...");
classF = new nogdb.ClassFilter([]);

console.log(classF.getClassName());

// console.log("classFilter add...");
// classF.add("your_dad");

// console.log(classF.getClassName());

console.log("vertex update...");
r1.unset("age");
nogdb.Vertex.update(txn,recD,r1);

console.log("vertex get...");
res =  nogdb.Vertex.get(txn,'my_son');
console.log(res);

console.log("vertex getInEdge...");
resIn =  nogdb.Vertex.getInEdge(txn,recD,classF);
console.log(resIn);

console.log("Db getRecord");
console.log(nogdb.Db.getRecord(txn,recD2));

console.log("vertex destroy...");
nogdb.Vertex.destroy(txn,recD);

console.log("vertex get...");
res =  nogdb.Vertex.get(txn,'my_son');
console.log(res);

// console.log("update vertex...");
// r1.unset("name");
// nogdb.Vertex.update(txn,r1D,r1);

// console.log("destroy vertex...");
// nogdb.Vertex.destroy(txn,r1D);

// console.log("createIndex property...");
// nogdb.Property.createIndex(txn,'my_son','name',true);
// nogdb.Property.createIndex(txn,'my_son','age',false);

// console.log("dropIndex property...");
// nogdb.Property.dropIndex(txn,'my_son','name');
// nogdb.Property.dropIndex(txn,'my_son','age');

console.log("remove property...");
nogdb.Property.remove(txn,'my_son','name');
nogdb.Property.remove(txn,'my_son','age');

console.log("Db getDbInfo...");
console.log(nogdb.Db.getDbInfo(txn));

console.log("Db getSchema...");
console.log(nogdb.Db.getSchema(txn));

console.log("drop class...");
nogdb.Class.drop(txn, 'your_dad');
nogdb.Class.drop(txn, 'my_son');

console.log("Db getDbInfo...");
console.log(nogdb.Db.getDbInfo(txn));

console.log("Db getSchema...");
console.log(nogdb.Db.getSchema(txn));

console.log("commit...");
txn.commit();

console.log("finish!")