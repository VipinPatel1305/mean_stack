var http = require('http');
var host = 'localhost';
var port = 3000;

var server = http.createServer(function(req, res)
{
  res.writeHead(200, {'Content-type': 'text/html'});
  res.end('Hello World');
})

server.listen(port, host, function()
{
  console.log('Server is up and running');
}
)