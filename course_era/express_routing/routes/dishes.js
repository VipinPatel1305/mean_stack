var express = require('express');
var morgan = require('morgan');
var bodyParser = require('body-parser');
var mongoose = require('mongoose');

var dishRouter = express();
var Dishes = require('../models/dishes');
dishRouter.use(morgan('dev'));
dishRouter.use(bodyParser.json());

dishRouter.route('/')
.get(function(req,res,next){
   Dishes.find({}, function(err, dish)
     {
       if(err) throw err;
       res.json(dish);
     }
   );
})
.post(function(req, res, next){
    Dishes.create(req.body, function(err, dish)
    {
      if(err) throw err;
      console.log('dish created with id:' + dish._id);
      res.writeHead({'Content-Type': 'text/plain'});
      res.end('Dish create with id:' + dish_id);
    });
    res.end('Will add the dish: ' + req.body.name + ' with details: ' + req.body.description);
})
.delete(function(req, res, next){
        Dishes.remove({}, function(err, resp)
        {
          if(err) throw err;
          res.end(resp);
        });
});

dishRouter.route('/:dishId')
.get(function(req,res,next){
        Dishes.findById(req.params.dishId, function(err, dish)
        {
            if(err) throw err;
            res.json(dish);
        });
})
.put(function(req, res, next){
    res.write('Updating the dish: ' + req.params.dishId + '\n');
    res.end('Will update the dish: ' + req.body.name + 
            ' with details: ' + req.body.description);
})
.delete(function(req, res, next){
        res.end('Deleting dish: ' + req.params.dishId);
});

module.exports = dishRouter;


