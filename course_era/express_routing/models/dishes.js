var mongoose = require('mongoose');
require('mongoose-currency').loadType(mongoose);
var Schema = mongoose.Schema;
var Currency = mongoose.Types.Currency;

var commentSchema = new Schema({
    rating:{
      type: Number,
      min: 1,
      max: 5,
      requied: true
    },
    comment:{
      type: String,
      required: true
    },
    author:{
      type: String,
      required: true
    }
    },
    {
      timestamps: true
    }
);

var dishSchema = new Schema({
    name: {
      type: String,
      required: true,
      unique: true
    },
    description:{
      type: String,
      required: true
    },
    image:{
      type: String,
      required: true
    },
    category:{
      type: String,
      required: true
    },
    label:{
      type: String,
      default: ''
    },
    price:{
      type: Currency,
      required: true
    },
    comments: [commentSchema]
},
{
  timestamps: true
}
);

var Dishes = mongoose.model('Dish', dishSchema);
module.exports = Dishes;