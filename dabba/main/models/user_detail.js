var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var transT = ['credit', 'debit'];

var transSchema = new Schema({
  quantity:{
    type: Number,
    require: true
  },
  cost:{
    type: Number,
    required: true
  },
  transType:{
    type: String,
    required: true,
    enum: transT
  }, 
  transTime:{
    type: Date,
    default: Date.now
  }
});

var UserSchema = new Schema({
  name:{
    type: String,
    required: true
  },
  contact:{
    type: Number,
    required: true
  },
  transDate: [transSchema]
});

var userModel = mongoose.model('User', UserSchema);
module.exports = userModel;