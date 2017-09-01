module.exports.homelist = function(req, res, next)
{
  res.render('index', {title: 'Home'});
};

module.exports.locationInfo = function(req, res, next)
{
  res.render('index', {title: 'Location Info'});
};

module.exports.addReview = function(req, res, next)
{
  res.render('index', {title: 'New'});
};