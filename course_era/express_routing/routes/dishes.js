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
      res.writeHead(200, {'Content-Type': 'text/plain'});
      res.end('Dish create with id:' + dish._id);
    });    
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
    Dishes.findByIdAndUpdate(req.params.dishId, {
      $set: req.body
    },{
      new: true
    }, function(err, dish)
    {
      if(err) throw err;
      res.json(dish);
    });
})
.delete(function(req, res, next){
        Dishes.findByIdAndRemove(req.params.dishId, function(err, dish)
        {
          if(err) throw err;
          res.json(dish);
        }
        );
});

dishRouter.route('/:dishId/comments')
.get(function(req, res, next)
{
  Dishes.findById(req.params.dishId, function(err, dish)
  {
    if(err) throw err;
    res.json(dish.comments);
  });
})

.post(function(req, res, next)
{
  Dishes.findById(req.params.dishId, function(err, dish)
  {
    if(err) throw err;
    dish.comments.push(req.body);
    dish.save(function(err, dish)
    {
      if(err) throw err;
      console.log('comment added');
      res.json(dish);
    });
  });
})

.delete(function(req, res, next)
{
  Dishes.findById(req.params.dishId, function(err, dish)
  {
    if(err) throw err;
    for(var i = 0; i < dish.comments.length; i++)
    {
      dish.comments.id(dish.comments[i]).remove();
    }
    
    dish.save(function(err, result)
    {
      res.writeHead({'Content-Type': 'text/plain'});
      res.end('All the comments deleted');
    });    
  });
});

dishRouter.route('/:dishId/comments/:commentId')
.get(function(req, res, next)
{
  Dishes.findById(req.params.dishId, function(err, dish)
  {
    if(err) throw err;
    res.json(dish.comments.id(req.params.commentId));
  }
  );
})
.put(function(req, res, next)
{
  Dishes.findById(req.params.dishId, function(err, dish)
  {
    dish.comments.id(req.params.commentId).remove();
    dish.comments.push(req.body);
    dish.save(function(err, dish)
    {
      if(err) throw err;
      res.json(dish);
    });
  });
})
.delete(function(req, res, next)
{
  Dishes.findById(req.params.dishId, function(err, dish)
  {
    if(err) throw err;
    dish.comments.id(req.params.commentId).remove();
    dish.save(function(err, dish)
    {
      if(err) throw err;
      res.json(dish);
    }
    );
  }
  );
});

module.exports = dishRouter;


