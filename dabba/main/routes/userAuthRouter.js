var express = require('express');
var passport = require('passport');
var router = express.Router();
var UserAuth = require('../models/userAuth');
var Verify = require('./verify');

router.get('/', function(req, res, next)
{
  res.send('get all users');
});

router.post('/register', function(req, res, next)
{
  UserAuth.register(new UserAuth({username: req.body.username}), req.body.password, function(err, user)
    {
      if(err)
      {
        console.log('error registering user');
        return res.status(500).end(err);
      }
      else
      {
        passport.authenticate('local')(req, res, function()
        {
          return res.status(200).end('Registration successful');
        });
      }
    });
});


router.post('/login', function(req, res, next) {
  passport.authenticate('local', function(err, user, info) {
    if (err) {
      return res.status(404).end('error logging');
    }
    if (!user) {
      return res.status(404).end('user doesnot exist');
    }
    req.logIn(user, function(err) {
      if (err) {
        return res.status(404).end('login failed');
      }
        
      var token = Verify.getToken(user);
              res.status(200).json({
        status: 'Login successful!',
        success: true,
        token: token
      });
    });
  })(req,res,next);
});

router.get('/logout', function(req, res) {
    req.logout();
    res.status(200).end('Bye');
});

module.exports = router;