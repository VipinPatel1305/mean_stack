var express = require('express');
var morgan = require('morgan');
var bodyParser = require('body-parser');

var dishRouter = express();

dishRouter.use(morgan('dev'));
dishRouter.use(bodyParser.json());

dishRouter.all('/', function(req,res,next) {
      res.writeHead(200, { 'Content-Type': 'text/plain' });
      next();
});

dishRouter.get('/', function(req,res,next){
        res.end('Will send all the dishes to you!');
});

dishRouter.post('/', function(req, res, next){
     res.end('Will add the dish: ' + req.body.name + ' with details: ' + req.body.description);
});

dishRouter.delete('/', function(req, res, next){
        res.end('Deleting all dishes');
});

dishRouter.get('/:dishId', function(req,res,next){
        res.end('Will send details of the dish: ' + req.params.dishId +' to you!');
});

dishRouter.put('/:dishId', function(req, res, next){
    res.write('Updating the dish: ' + req.params.dishId + '\n');
    res.end('Will update the dish: ' + req.body.name + 
            ' with details: ' + req.body.description);
});

dishRouter.delete('/:dishId', function(req, res, next){
        res.end('Deleting dish: ' + req.params.dishId);
});

module.exports = dishRouter;


