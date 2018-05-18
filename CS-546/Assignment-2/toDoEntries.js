var todos = module.exports = {};
var entries = [];

/**
 * Get all of the task entries
 *
 * @param string|null status The status of the elements to fetch, or null if fetching all entries
 * @return array The entries
 */
todos.getEntries = function (status) {
    var resultSet = [];

    if (status === null) {
        resultSet = entries.slice(0);
    } else {
        resultSet = entries.filter(function (entry) {
            return entry.status === status;
        });
    }
    
    return resultSet;
};

/**
 * Get a todo from the todo's ID
 *
 * @param number id The ID to fetch
 * @return object|undefined The found object, or undefined if not found
 */
todos.getTodoByID = function (id) {
    return entries.filter(function (entry) {
        return entry.id === id;
    }).shift();
}

/**
 * Create a new task
 *
 * @param string author The task's author
 * @param string title The task's title
 * @param string description The task's description
 * @return object The newly created task
 */
todos.createTask = function (author, title, description) {
    if (typeof author != "string" || typeof title != "string" || typeof description != "string" ||
        author === '' || title === '' || description === '') {
        throw "You must provide valid information in the request body to create an entry.";
    }

    // Create an empty object for the new task, and determine the ID
    var newTask = {};
    var id = (entries.length > 0) ? entries[entries.length - 1].id + 1 : 0;

    newTask.id = id;
    newTask.author = author;
    newTask.title = title;
    newTask.description = description;
    newTask.status = "open";
    newTask.taskNotes = [];

    entries.push(newTask);

    return newTask;
};

/**
 * Update a task
 *
 * @param number id The ID of the todo to update
 * @param string title The new title
 * @param string description The new description
 * @param string status The new status
 * @return int|object The error code, or the updated task
 */
todos.updateTask = function (id, title, description, status) {
    if ((title === undefined && description === undefined && status === undefined) || 
       (status !== undefined && status !== 'completed' && status !== 'open')) {
        return -1; // Invalid parameters
    }

    var task = todos.getTodoByID(id);

    if (task === undefined) {
        return -2; // Task not found
    }

    // Update the appropriate task information
    task.title = (title !== undefined) ? title : task.title;
    task.description = (description !== undefined) ? description : task.description;
    task.status = (status !== undefined) ? status : task.status;

    return task;
}

/**
 * Add a note to a task
 *
 * @param number id The ID of the todo to update
 * @param string note The note to add to the todo
 * @return int|object The error code, or the updated task
 */
todos.addNote = function (id, note) {
    if (id === '' || typeof note !== 'string' || note === '') {
        return -1;
    }

    var task = todos.getTodoByID(id);

    if (task === undefined) {
        return -2; // Task not found
    }

    task.taskNotes.push(note);

    return task;
};

/**
 * Delete a task
 *
 * @param number id The todo ID to delete
 */
todos.deleteTask = function (id) {
    var todo = todos.getTodoByID(id);

    if (todo === undefined) {
        throw "An entry with the ID of " + id + " could not be found";
    }

    entries.splice(entries.indexOf(todo), 1);
};