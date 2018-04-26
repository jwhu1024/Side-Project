var createError     = require('http-errors'),
	express         = require('express'),
	path            = require('path'),
	cookieParser    = require('cookie-parser'),
	logger          = require('morgan'),
	firebase        = require('firebase'),
	list 			= require('./drink.json');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use('/views', express.static(path.join(__dirname, '/views')));
app.use('/images', express.static(path.join(__dirname, '/images')));

(function(){
	var config = {
		apiKey: "AIzaSyBWBPP0Qxt4epzlD4ZlkzOGU7pMC15ZnVs",
		authDomain: "lunch-picker-3066c.firebaseapp.com",
		databaseURL: "https://lunch-picker-3066c.firebaseio.com",
		projectId: "lunch-picker-3066c",
		storageBucket: "lunch-picker-3066c.appspot.com",
		messagingSenderId: "557419931185"
  	};
	firebase.initializeApp(config);
}())

function firebase_set_data (data)
{
	var db 		= firebase.database(),
		ref 	= db.ref("/"),
		value 	= {
			lunch: data
		};
	ref.set(value);
}

/* GET home page. */
app.get('/', function(req, res, next) {
	firebase_set_data(list);
	res.sendFile(__dirname + '/views/index.html');
});

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
