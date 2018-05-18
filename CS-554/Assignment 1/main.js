const express = require("express");
const bodyParser = require("body-parser");
const calendar = require('./calendar.js');
const app = express();
const static = express.static(__dirname + '/dist');
const exphbs = require('express-handlebars');
const Handlebars = require('handlebars');
const {Menu} = require('electron');
const dialog = require('electron').dialog;

const handlebarsInstance = exphbs.create({
    defaultLayout: 'main',
    // Specify helpers which are only registered on this instance.
    helpers: {
        asJSON: (obj, spacing) => {
            if (typeof spacing === "number")
                return new Handlebars.SafeString(JSON.stringify(obj, null, spacing));

            return new Handlebars.SafeString(JSON.stringify(obj));
        }
    },
    partialsDir: [
        'views/partials/'
    ]
});

// Build the electron menu
const menuTemplate = [
    {
        label: 'File',
        submenu: [
        {
            label: 'Save Calendar (To File)',
            click: () => {
                dialog.showSaveDialog(function (fileName) {
                    if (fileName === undefined) {
                        return;
                    }

                    calendar.saveCalendar(fileName.trim());
                });
            }
        },
        {
            label: 'Load Calendar (From File)',
            click: (item, focusedWindow) => {
                dialog.showOpenDialog(function (fileName) {
                    if (fileName === undefined || fileName[0] == undefined) {
                        return;
                    }

                    calendar.loadCalendar(fileName[0].trim());
                    focusedWindow.reload();
                });
            }
        }
        ]
    },
    {
        label: 'Modes',
        submenu : [
            {
                label: 'Tablet',
                click (item, focusedWindow) {
                    focusedWindow.setSize(768, 1024, true)
                }
            },
            {
                label: 'Desktop',
                click (item, focusedWindow) {
                    focusedWindow.setSize(1200, 900, true)
                }
            },
            {
                label: 'Mobile',
                click (item, focusedWindow) {
                    focusedWindow.setSize(375, 667, true)
                }
            }
        ]
    }
];

const electronApp = require("./electron-app");

const rewriteUnsupportedBrowserMethods = (req, res, next) => {
    // If the user posts to the server with a property called _method, rewrite the request's method
    // To be that method; so if they post _method=PUT you can now allow browsers to POST to a route that gets
    // rewritten in this middleware to a PUT route
    if (req.body && req.body._method) {
        req.method = req.body._method;
        delete req.body._method;
    }

    // let the next middleware run:
    next();
};

app.use("/public", static);
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(rewriteUnsupportedBrowserMethods);

app.engine('handlebars', handlebarsInstance.engine);
app.set('view engine', 'handlebars');

// Month names
var monthNames = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];

// Weekdays
var weekdays = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];

// Number suffixes
var suffixes = ['th', 'st', 'nd', 'rd', 'th', 'th', 'th', 'th', 'th', 'th'];

/* Routes */
app.get("/", function (req, res) {
    calendar.load().then(function (result) {
        res.redirect("/" + (new Date()).getMonth() + "/" + (new Date()).getFullYear);
    });
});

app.get("/monthnum/:month/:year", function (req, res) {
    res.redirect("/" + monthNames.indexOf(req.params.month) + "/" + req.params.year);
});

app.get("/:month/:year", function (req, res) {
    // Parse out the month and year from the parameters
    month = parseInt(req.params.month);
    year = parseInt(req.params.year);

    // Save the month number
    monthNum = month;

    // Error check and parse the month and year
    month = (month !== month) ? monthNames[(new Date()).getMonth()] : monthNames[month];
    year = (year !== year) ? (new Date()).getFullYear() : year;
    year = (year < 1900) ? 1900 : year;

    // Calculate the day of the week the month starts on
    offset = parseInt((new Date(year + "-" + month + "-01")).getDay());

    // Calculate the number of days in the month
    daysInMonth = (new Date(year, monthNum + 1, 0)).getDate();

    // What calendar size do we need? (5x7 or 6x7)
    var size = ((daysInMonth == 30 || daysInMonth == 31) && offset == 6) ? 42 : 35;

    // Get the events for the month being viewed
    var events = calendar.getEventsForMonth(monthNum, year);
    
    // Actually generate the thing
    var dates = [];
    var days = [];
    var mobile = [];
    var curr = "";

    if (Object.keys(events).length == 0) {
        mobile.push("<h1>No events found</h1>");
    }

    for (var day in events) {
        var currDate = new Date(year, monthNum, day);
        curr = "<div class='day-mobile'><h1><a href='/view/" + year + "/" + month + "/" + day + "'>" + weekdays[currDate.getDay()] + ", " + monthNames[monthNum] + " " + day + "</a></h1>";

        for (var event in events[day]) {
            curr += "<div class='event'>&bull;<a href='/event/" + year + "/" + month + "/" + day + "/" + event + "'>" + event + "</a></div>";
        }

        curr += "</div>";
        mobile.push(curr);
    }

    var base = "";
    for(var i = 1, week = 0; i <= size; i++, week++) {
        if (week == 0) {
            dates.push('<div class="week-row">');
        }
    
        if (i <= offset || (i - offset) > daysInMonth) {
            dates.push('<div class="day"></div>');
        } else {
            base = '<div class="day" data-day="' + (i - offset) + '">' + (i - offset);
            days.push(i - offset);

            if (events.hasOwnProperty(i - offset)) {
                var count = 0;
                for (var key in events[i - offset]) {
                    if (count < 4) {
                        base += '<div class="event">&bull; ' + key + '</div>';
                    }

                    count++;
                }

                if (count > 4) {
                    base += '<div class="event">...and ' + (count - 4) + ' more</div>';
                }
            }

            base += '</div>';
            dates.push(base);
        }

        if (week == 6) {
            dates.push('</div>');
            week = -1;
        }
    }

    res.render("partials/month", { month: month, year: year, cal: dates, days: days, mobile: mobile });
});

app.post("/events/create", function (req, res) {
    var month = req.body.month;
    var year = req.body.year;
    var day = req.body.day;
    var title = req.body.title;
    var description = req.body.description;
    var location = req.body.location;

    calendar.createEvent(year, monthNames.indexOf(month), day, title, description, location);

    if (req.body.page == "monthly") {
        res.redirect("/" + monthNames.indexOf(month) + "/" + year);
    } else {
        res.redirect("/view/" + year + "/" + month + "/" + day);
    }
});

app.get("/viewnum/:year/:month/:day", function (req, res) {
    res.redirect("/view/" + req.params.year + "/" + monthNames.indexOf(req.params.month) + "/" + req.params.day);
});

app.get("/view/:year/:month/:day", function (req, res) {
    var year = parseInt(req.params.year);
    var month = req.params.month;
    var day = parseInt(req.params.day);

    if (!year || !month || !day) {
        return false;
    }

    if (!isNaN(parseInt(month))) {
        monthNum = parseInt(month) - 1;
        month = monthNames[parseInt(month) - 1];
    } else {
        monthNum = monthNames.indexOf(month);
    }
    var weekday = weekdays[(new Date(year, monthNum, day)).getDay()];
    var events = JSON.parse(JSON.stringify(calendar.getEventsForDay(monthNum, year, day)));

    // Figure out which day of the year this day is, and how many days are left
    var now = new Date(year + "-" + month + "-" + day);
    var start = new Date(year, 0, 0);
    var end = new Date(year, 12, 0);
    var diff = now - start;
    var endDiff = end - now;
    var dayNum = Math.round(diff / (1000 * 60 * 60 * 24));
    var daysLeft = Math.round(endDiff / (1000 * 60 * 60 * 24));

    // Get the proper suffix (th, nd, st, etc.)
    if ((dayNum % 100) >= 11 && (dayNum % 100) <= 13) {
        dayNum += 'th';
    } else {
        dayNum += suffixes[dayNum % 10];
    }

    for (var event in events) {
        events[event]['link'] = "<a href='/event/" + year + "/" + month + "/" + day + "/" + event + "'>";
    }

    now.setDate(now.getDate() - 3);
    var days = [];
    for (var i = 0, days = [], dateStr = "", dataStr = ""; i < 7; i++) {
        if (i == 3) {
            dateStr = "<b>" + (now.getMonth() + 1) + "/" + now.getDate() + "</b>";
        } else {
            dateStr = (now.getMonth() + 1) + "/" + now.getDate();
        }

        dataStr = now.getMonth() + "/" + now.getDate() + "/" + now.getFullYear();
        days.push("<div class='slider-day' data-date='" + dataStr + "'>" + dateStr + "</div>");
        now.setDate(now.getDate() + 1);
    }

    res.render("partials/daily", { monthNum: monthNum + 1, events: events, month: month, year: year, day: day, weekday: weekday, dayNum: dayNum, daysLeft: daysLeft, days: days });
});

app.get("/open/:file", function (req, res) {
    console.log("Got request");
    calendar.loadCalendar(req.params.file);
});

app.get("/event/:year/:month/:day/:event", function (req, res) {
    var year = req.params.year;
    var month = monthNames.indexOf(req.params.month);
    var day = req.params.day;
    var title = req.params.event;
    var event = calendar.getEvent(year, month, day, title);

    var back = "<a href='/view/" + year + "/" + (month + 1) + "/" + day + "'>";

    if (!event || event == {}) {
        res.redirect("/");
    }

    var location = event['location'];
    var description = event['description'];

    res.render("partials/event", { back: back, year: year, month: req.params.month, day: day, title: title, location: location, description: description });
});

app.get('/event/delete/:year/:month/:day/:task', function (req, res) {
    var task = req.params.task;
    var month = monthNames.indexOf(req.params.month);
    var year = parseInt(req.params.year);
    var day = parseInt(req.params.day);

    if (!task || month < 0 || !year || !day) {
        res.json({ url: "/" });
    }

    calendar.deleteEvent(year, month, day, task);
    res.json({ url: "/view/" + year + "/" + (month + 1) + "/" + day });
});

app.get("*", function (req, res) {
    res.redirect("/");
});

// Set application menu
const menu = Menu.buildFromTemplate(menuTemplate);
Menu.setApplicationMenu(menu);

app.listen(3000, () => {  
    console.log("We've now got a server!");
    console.log("Your routes will be running on http://localhost:3000");
    console.log("Now launching electron app");
    electronApp();
});