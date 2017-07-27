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
      mongoCon.findDistinct(db, 'workflow',
      function(docs)
      {//JSON.stringify(
	  res.write('<!DOCTYPE html>');
	  res.write('<html><body>');
	  res.write('<h1>Workflows</h1>');
	  res.write('<ul>');
		docs = JSON.parse(JSON.stringify(docs));
		for(var i = 0; i < docs.length; i++) {
			res.write('<li>');
			res.write(JSON.stringify(docs[i]));
			res.write('</li>');
		}		
		res.write('</ul>');
		res.write('</body></html>');
		res.end("End of Doc");
		db.close();
	  });
   })
});


backend_router.get('/phases', function(req, res){
	mongoClient.connect(url, function(err, db)
    {
      assert.equal(null, err);
	  mongoCon.findDistinct(db, 'phase', function(docs)
	  {
	  res.write('<!DOCTYPE html>');
	  res.write('<html><body>');
	  res.write('<h1>Phases</h1>');
	  res.write('<ul>');
	  docs = JSON.parse(JSON.stringify(docs));
		for(var i = 0; i < docs.length; i++) {
			res.write('<li>');
			res.write(JSON.stringify(docs[i]));
			res.write('</li>');
		}		
		res.write('</ul>');
		res.write('</body></html>');
		res.end("End of Doc");
		db.close();
	  });
	});   
});

backend_router.get('/phases/:phaseName', function(req, res){
	mongoClient.connect(url, function(err, db)
    {
      assert.equal(null, err);
	  mongoCon.findWorkflows(db, req.params.phaseName, function(docs)
	  {
		docs = JSON.parse(JSON.stringify(docs));
		res.write('<!DOCTYPE html>');
		res.write('<html><body>');
		res.write('<h1>Phase Details</h1>');
		res.write('<h2>');
		res.write('PhaseName: ' + req.params.phaseName);
		res.write('</h2>');
		res.write('<h2>');
		res.write('ResourceLevel: ' + docs[0].resource_level);
		res.write('</h2>');	
		res.write('<h2>');
		res.write('ConfigFiles' );
		res.write('</h2>');	
		res.write('<ul>');
		configFiles = JSON.parse(JSON.stringify(docs[0].files));
		for(var j = 0; j < configFiles.length; j++)
		{
			res.write('<li>');
			res.write(configFiles[j]);
			res.write('</li>');
		}
		res.write('</ul>');
		res.write('</body></html>');
		res.end('get phase details for:' + req.params.phaseName);
		db.close();
	  });
	}); 	
   
});

module.exports = backend_router;
