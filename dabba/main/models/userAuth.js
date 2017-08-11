var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var passportLocalMongoose = require('passport-local-mongoose');

var UserAuth = new Schema(
{
  username:
  {
    type: String,
    require: true,
    unique: true
  },
  password:
  {
    type: String,
    require: true
  },
  admin:
  {
    type: Boolean,
    default: false
  }
}
);

UserAuth.plugin(passportLocalMongoose);

module.exports = mongoose.model('UserAuth', UserAuth);