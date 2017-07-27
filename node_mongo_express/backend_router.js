var express = require('express');
var bodyParser = require('body-parser');
var url = 'mongodb://localhost:27017/backend';  
var mongoClient = require('mongodb');
var mongoCon = require('./mongo_node');
var assert = require('assert');

var backend_router = express();

backend_router.use(bodyParser.json());

backend_router.all('/',function(req, res, next)
{
  res.head(200, {'Content-Type': 'application/json'});
  next();
}
);

backend_router.get('/workflow', function(req, res){
    mongoClient.connect(url, function(err, db)
    {
      assert.equal(null, err);
      mongoCon.findWorkflows(db, 'phase',
      function(docs)
      {//JSON.stringify(
        cursor.each(function(err, doc) {
        res.json(docs);
   });
          
          res.end("List all workflows");
          db.close();
      }
      )
    });
    
    
});

backend_router.get('/phases', function(req, res){
   res.end("List all phases");
});

backend_router.get('/phases/:phaseName', function(req, res){
   res.end('get phase details for:' + req.params.phaseName);
});

module.exports = backend_router;
