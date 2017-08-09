var express = require('express');
var app = express();

app.get('/', function(req, res)
{
  res.json({message: "Express is up"});
}
);

app.listen(3000, function()
{
  console.log('server is up and running');
});