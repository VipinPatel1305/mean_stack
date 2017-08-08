var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var menuSchema = new Schema({
  details:{
    type: String,
    required: true,    
  },
  cost:{
    type: Number,
    required: true
  }
});

var menuModel = mongoose.model('Menu', menuSchema);
module.exports = menuModel;