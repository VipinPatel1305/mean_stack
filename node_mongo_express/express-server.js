var express = require('express');
var backend_router = require('./backend_router');
var morgan = require('morgan');

var hostname = 'localhost';
var port = 3000;


var app = express();

app.use(morgan('dev'));

app.use('/', backend_router);
app.use(express.static(__dirname + '/public'));


app.listen(port, hostname, function()
{
    console.log('server is up and running');
}
)