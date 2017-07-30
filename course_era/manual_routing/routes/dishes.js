var express = require('express');
var morgan = require('morgan');
var bodyParser = require('body-parser');

var dishRouter = express();

dishRouter.use(morgan('dev'));
dishRouter.use(bodyParser.json());

dishRouter.all('/dishes', function(req,res,next) {
      res.writeHead(200, { 'Content-Type': 'text/plain' });
      next();
});

dishRouter.get('/dishes', function(req,res,next){
        res.end('Will send all the dishes to you!');
});

dishRouter.post('/dishes', function(req, res, next){
     res.end('Will add the dish: ' + req.body.name + ' with details: ' + req.body.description);
});

dishRouter.delete('/dishes', function(req, res, next){
        res.end('Deleting all dishes');
});

dishRouter.get('/dishes/:dishId', function(req,res,next){
        res.end('Will send details of the dish: ' + req.params.dishId +' to you!');
});

dishRouter.put('/dishes/:dishId', function(req, res, next){
    res.write('Updating the dish: ' + req.params.dishId + '\n');
    res.end('Will update the dish: ' + req.body.name + 
            ' with details: ' + req.body.description);
});

dishRouter.delete('/dishes/:dishId', function(req, res, next){
        res.end('Deleting dish: ' + req.params.dishId);
});



