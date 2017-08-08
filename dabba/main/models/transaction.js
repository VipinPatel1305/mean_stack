var mongoose = require('mongoose');
var transT = ['credit', 'debit'];
var Schema = mongoose.Schema;

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
}},
  {
    timestamps: true  
  }
);

var transModel = mongoose.model('trans', transSchema);
module.exports = transModel;