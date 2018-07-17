const nogdb = require("./build/Release/nogdb_js")

console.log("new ctx...");
const ctx = new nogdb.Context("sample.db");

console.log("new txn...");
var txn = new nogdb.Txn(ctx);

console.log("create class...");
nogdb.Class.create(txn, 'my_vertex');

console.log("commit...");
txn.commit();

console.log("finish!")