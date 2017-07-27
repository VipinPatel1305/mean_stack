
var assert = require('assert');



exports.findDistinct = function(db, colName, callback)
{
  // Get the documents collection
    var coll = db.collection('phase');
	
   // Find some documents
   coll.distinct(colName, function(err, docs)
   {
	   assert.equal(err, null);
	   callback(docs);
   });
};

exports.findWorkflows = function(db, phaseName, callback)
{
  // Get the documents collection
    var coll = db.collection('phase');
   // Find some documents
  coll.find({phase: phaseName}).toArray(function(err, docs) {
    assert.equal(err, null);
    callback(docs);
  });
};

var findPhases = function(db, callback) {
   var cursor = db.collection('phase').find({"phase":'FEATURE_ATTRIBUTION'});
   cursor.each(function(err, doc) {
      assert.equal(err, null);
      if (doc != null) {
         console.dir(doc.files);
      } else {
         callback();
      }
   });
};
