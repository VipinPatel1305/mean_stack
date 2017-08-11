var express = require('express');
var bodyParser = require('body-parser');
var menuModel = require('../models/price_menu');
var userModel = require('../models/user_detail');
var Verify = require('./verify');

app = express();
app.use(bodyParser.json());

app.get('/normalUser/:userId', Verify.verifyOrdinaryUser, function(req, res, next)
{
  res.end('get request for:' + req.params.userId);
});

app.get('/normalUser/:userId/transactions', Verify.verifyOrdinaryUser, function(req, res, next)
{
  userModel.findById(req.params.userId, function(err, user)
  {
    if(err) throw err;
    res.json(user.transDate);
  });
}
);

app.post('/normalUser/:userId/transactions', function(req, res, next)
{
  userModel.findById(req.params.userId, function(err, user)
  {
    if(err) throw err;
    user.transDate.push(req.body);
    user.save(function(err, transaction)
    {
      if(err) throw err;
      res.json(transaction);
    });
  });  
}
);

app.get('/normalUser', Verify.verifyOrdinaryUser, function(req, res, next)
{
    userModel.find({}, function(err, user)
    {
      res.json(user);
    });
});

app.post('/normalUser', function(req, res, next)
{
  userModel.create(req.body, function(err, user)
  {
    if(err) throw err;
    res.json(user);
  });
}
);

app.get('/admin/:userId', function(req, res, next)
{
  res.end('get admin request for:' + req.params.userId);
});

app.get('/caterer/menu', Verify.verifyOrdinaryUser, function(req, res, next)
{
    menuModel.find({}, function(err, menu)
    {
      if(err) throw err;
      res.json(menu);
    });
});

app.post('/caterer/menu', function(req, res, next)
{
  menuModel.create(req.body, function(err, menu)
  {
    if(err) throw err;
    res.json(menu);
  });  
});

app.put('/caterer/menu/:itemId', function(req, res, next)
{
  menuModel.update({_id: req.params.itemId}, {$set: req.body}, function(err, raw)
  {
    if(err)
    {
      console.log('unable to update menu item with id: ' + req.params.itemId);
      res.end('Error');
    }
    else
    {
      res.end('Update Successful: ' + raw);
    }
  });
});


app.delete('/caterer/menu/:itemId', function(req, res, next)
{
  menuModel.findByIdAndRemove(req.params.itemId, function(err, menu)
  {
    if(err) throw err;
    res.json(menu);
  });
});


module.exports = app;