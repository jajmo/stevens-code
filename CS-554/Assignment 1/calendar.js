var exports = module.exports = { };

/**
 * Data structure:
 * {
 *   year: {
 *     month: {
 *       day: {
 *         name: {
 *           description: text,
 *           location: text
 *         }
 *       }
 *     }  
 *   }
 * }
 */

// The calendar events. The primary data store
var calendarEvents = { };
const fs = require('fs');
const xss = require('xss');

// The file that stores the last opened filename
const lastOpened = "./config/config.json";

// The default last save location
let lastSave = "./config/autosave.json";

// Is this the first run?
let first = true;

exports.load = function () {
    return new Promise(function (resolve, reject) {
        if (!first) {
            resolve();
        }

        fs.readFile(lastOpened, function (err, data) {
            if (err) {
                // File doesn't exist
                fs.writeFile(lastOpened, JSON.stringify({ 'lastOpened': lastSave }));
            } else {
                try {
                    data = JSON.parse(data.toString().trim());
                    if ('lastOpened' in data) {
                        lastSave = data['lastOpened'];
                    } else {
                        fs.writeFile(lastOpened, JSON.stringify({ 'lastOpened': lastSave }));
                    }
                } catch (e) { 
                    // File was invalid format or something
                    fs.writeFile(lastOpened, JSON.stringify({ 'lastOpened': lastSave }));
                }
            }

            fs.readFile(lastSave, function (err, data) {
                if (!err) {
                    try {
                        calendarEvents = JSON.parse(data.toString());
                    } catch (e) {
                        calendarEvents = { }; // For invalid JSON or if they open a bad file
                    }
                }

                first = false;
                resolve();
            });
        });
    });
}

exports.saveToFile = function () {
    fs.writeFile(lastSave, JSON.stringify(calendarEvents));
}

exports.loadCalendar = function (fileName) {
    fs.readFile(fileName, function (err, data) {
        if (!err) {
            try {
                calendarEvents = JSON.parse(data.toString().trim());
                fs.writeFile(lastOpened, JSON.stringify({ 'lastOpened': fileName }));
                lastSave = fileName;
            } catch (e) { 
                /* Bad file - do noting */
            }
        }
    })
}

exports.saveCalendar = function (fileName) {
    fs.writeFile(fileName, JSON.stringify(calendarEvents));
}

exports.createEvent = function (year, month, day, name, description, location) {
    if (!calendarEvents.hasOwnProperty(year)) {
        calendarEvents[year] = { };
    }

    if (!calendarEvents[year].hasOwnProperty(month)) {
        calendarEvents[year][month] = { };
    }

    if (!calendarEvents[year][month].hasOwnProperty(day)) {
        calendarEvents[year][month][day] = { };
    }

    name = xss(name);

    calendarEvents[year][month][day][name] = {
        description: xss(description),
        location: xss(location)
    }

    exports.saveToFile();
}

exports.getEventsForMonth = function (month, year) {
    ret = {};

    if (exports.eventExists(year, month, false, false)) {
        ret = calendarEvents[year][month];
    }

    return ret;
}

exports.getEventsForDay = function (month, year, day) {
    var res = {};

    if (exports.eventExists(year, month, day, false)) {
        res = calendarEvents[year][month][day];
    }

    return res;
}

exports.getEvent = function (year, month, day, title) {
    var res = {};

    if (exports.eventExists(year, month, day, title)) {
        res = calendarEvents[year][month][day][title];
    }
    
    return res;
}

exports.deleteEvent = function (year, month, day, title) {
    if (exports.eventExists(year, month, day, title)) {
        delete calendarEvents[year][month][day][title];

        // Clean up the object
        if (Object.keys(calendarEvents[year][month][day]).length === 0) {
            delete calendarEvents[year][month][day];
        }
        
        if (Object.keys(calendarEvents[year][month]).length === 0) {
            delete calendarEvents[year][month];
        }

        if (Object.keys(calendarEvents[year]).length === 0) {
            delete calendarEvents[year];
        }

        exports.saveToFile();
    }
}

exports.eventExists = function (year, month, day, title) {
    var res = true;

    if (year) {
        res = calendarEvents.hasOwnProperty(year);
    }

    if (res && month) {
        res = calendarEvents[year].hasOwnProperty(month);
    }

    if (res && day) {
        res = calendarEvents[year][month].hasOwnProperty(day);
    }

    if (res && title) {
        res = calendarEvents[year][month][day].hasOwnProperty(title);
    }

    return res;
}