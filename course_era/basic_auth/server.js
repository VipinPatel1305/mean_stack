var express = require('express');
var morgan = require('morgan');
var cookieParser = require('cookie-parser');
var hostname = 'localhost';
var port = 3000;

var app = express();
app.use(morgan('dev'));
app.use(cookieParser('12345-45871-12334-34551'));


function auth(req, res, next)
{
  console.log(req.headers);
  
  if(!req.signedCookies.choclate54)
  {
    var authHeader = req.headers.authorization;
    if(!authHeader)
    {    
      var err = new Error('You are not authenticated');
      err.status = 401;
      next(err);
      return;
    }
    
    var auth = new Buffer(authHeader.split(' ')[1], 'base64').toString().split(':');
    var user = auth[0];
    var pass = auth[1];    
    
    if(user == 'admin' && pass == 'password54')
    {
      res.cookie('choclate', 'admin', {signed: true});
      next();
    }
    else
    {
      var err = new Error('Incorrect password or username');
      err.status = 401;
      next(err);
    }    
  }else
  {
    if(req.signedCookies.choclate == 'admin')
    {
      next();
    }
    else{
      var err = new Error('Mangled cookies');
      err.status = 401;
      next(err);
    }
  }
};

function errHandler(err, req, res, next)
{
  res.writeHead(err.status || 500, {'WWW-Authenticate':'Basic', 'Content-Type':'text/plain'});
  res.end(err.message);
}

app.use(auth);




app.use(express.static(__dirname + '/public'));
app.use(errHandler);

app.listen(port, hostname, function(){
  console.log(`Server running at http://${hostname}:${port}/`);
});