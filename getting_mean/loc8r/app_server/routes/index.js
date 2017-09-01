var express = require('express');
var router = express.Router();
var cntrlLocations = require('../controllers/locations');
var cntrlOthers = require('../controllers/others');
/* Location pages */
router.get('/', cntrlLocations.homelist);
router.get('/location', cntrlLocations.locationInfo);
router.get('/location/reivew/new', cntrlLocations.addReview);

/*About page*/

router.get('/about', cntrlOthers.about);


module.exports = router;
