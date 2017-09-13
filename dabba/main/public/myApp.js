
var myController = function($scope)
{
	$scope.myInput = "World!";
};

angular
.module('myApp', [])
.controller('myController', myController);