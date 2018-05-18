Assignment 1 - Calendar
=======================

Author: Jason Ajmo

Email: jajmo@stevens.edu

Usage
-----
To run the calendar, run `npm install && npm start`. The project has been submitted with CSS and JS already compiled/minified.

The default save location is `./config/autosave.json`. The file that stores the last opened file is `./config/config.json`.
If `config.json` doesn't exist, it will be automatically created on startup, using the default last save location of `./config/autosave.json`.

SASS is compiled and minified into `./dist/css`, using `gulp sass`.

JavaScript is minified into `./dist/js`, using `gulp js`. Running `gulp` or `gulp watch`
 will watch both the js and sass tasks.

The App
-------
* The default view is the monthly view, focused on the current month.
* Navigation between months can be done by clicking the arrows on top, or using the arrow keys.
* The "Add Event" window can be closed with the escape key.
* Clicking on a day will bring you to the daily view.
  * Clicking an event name will take you to the page for that event.
  * The boxes on the bottom with the dates are clickable, as well as the arrows. The arrows will take you forward 7 days.
* Events can be added on both the monthly and daily view. On the monthly view, a drop-down will appear, allowing you to select a day.
* The lower year limit is 1900, and there is no upper limit.

Notes
-----
* If you change modes via the menu (instead of resizing the window manually), you must click anywhere for the arrow key event handler to work properly.
* If you change modes via the menu (instead of resizing the window manually), the scrollbar will never appear. I wasn't able to fix this.