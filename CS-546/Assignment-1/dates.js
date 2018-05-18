var datesModule = {};

/**
 * daysUntil()
 *
 * Calculate the days until the date passed in
 *
 * @param Date date The date to calculate the days until
 * @return number The days until `date`
 */
datesModule.daysUntil = function (date) {

    // We only accept date objects
    if (date === null || typeof date.getMonth !== 'function') {
        throw "Invalid date format"
    }

    // Calculate seconds between `date` and now
    var now = Date.now();
    var seconds = date.valueOf() - now;

    if (seconds < 0) {
        throw "Date is in the past!";
    }

    // Date.valueOf() and Date.now() return milliseconds since epoch,
    // so this is milliseconds * seconds * minutes * hours
    return Math.round(seconds / (1000 * 60 * 60 * 24));
};

/**
 * daysLeftInYear()
 *
 * Calculate the number of days left in the current year
 *
 * @return number The number of days left in the year
 */
datesModule.daysLeftInYear = function () {
    return datesModule.daysUntil(new Date((new Date()).getFullYear() + "-12-31"));
};

/**
 * daysSince()
 *
 * Calculate the number of days since a given date
 *
 * @param Date date The date to calculate the days since
 * @return number The number of days that have passed since `date`
 */
datesModule.daysSince = function (date) {

    // We only accept date objects
    if (date === null || typeof date.getMonth !== 'function') {
        throw "Invalid date format"
    }

    // Calculate seconds between `date` and now
    var now = Date.now();
    var seconds = now - date.valueOf();

    if (seconds < 0) {
        throw "Date is in the future!";
    }

    // Date.valueOf() and Date.now() return milliseconds since epoch,
    // so this is milliseconds * seconds * minutes * hours
    return (seconds / (1000 * 60 * 60 * 24));
};

/**
 * nextFridayTheThirteenth()
 *
 * Get the next occurence of friday the 13th
 *
 * @return string The next date that will be friday the 13th
 */
datesModule.nextFridayTheThirteenth = function () {
    var now = new Date();

    // We only care about the 13th
    if (now.getDate() >= 13) {
        now.setMonth(now.getMonth() + 1);
    }

    now.setDate(13);

    // 0 == Sunday, so 5 == Friday
    while (now.getDay() != 5) {
        if (now.getMonth() == 11) {
            // Checked December, onto next year
            now.setMonth(0);
            now.setFullYear(now.getFullYear() + 1);
        } else {
            // Check next month
            now.setMonth(now.getMonth() + 1);
        }
    }

    return now.toDateString();
};

module.exports = datesModule;