
var assert = require('assert');



exports.findWorkflows = function(db, collection, callback)
{
  // Get the documents collection
  var coll = db.collection(collection);
  var cursor = db.collection('phase').find({"phase":'FEATURE_ATTRIBUTION'});
  callback(cursor);
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
