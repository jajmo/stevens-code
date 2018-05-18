var exports = module.exports = {};

var questionList = [];

var makeAQuestion = function (title, text) {
    if (!title) throw "Must include a title";

    return { id: questionList.length, title: title, text: text, answer: null };
}

exports.getUnansweredQuestions = function () {
    return questionList.filter(function (question) {
        return question.answer === null;
    });
}

exports.getAnsweredQuestions = function () {
    return questionList.filter(function (question) {
        return question.answer !== null;
    });
};

exports.getAllQuestions = function () { 
    // return a copy of the array
    return questionList.slice(0);
};

exports.getQuestion = function (id) {
    if (typeof id === "string") id = parseInt(id);

    if (id !== 0 && !id) throw "Must provide ID";

    var question = questionList.filter(function (question) {
        return question.id === id;
    }).shift();

    if (!question) throw "Could not find question";

    return question;
};

exports.addQuestion = function (title, text) {
    var question = makeAQuestion(title, text);

    questionList.push(question);

    return question;
}

exports.updateQuestion = function (id, title, text) {
    if (!title) throw "Must include a title";

    var question = exports.getQuestion(id);
    question.title = title;
    question.text = text;

    return question;
};

exports.answerQuestion = function (id, answer) {
    if (!answer) throw "Answer must exist";

    var question = exports.getQuestion(id);
    question.answer = answer;

    return question;
};

exports.deleteQuestion = function (id) {
    var question = exports.getQuestion(id);
    var indexOfQuestion = questionList.indexOf(question);

    // remove the question
    question.splice(indexOfQuestion, 1);
}

// Let's pre-seed with some data
var firstQuestion = exports.addQuestion("How do I boil water?", "Help! I promised my mom I would make dinner, and I don't know how to boil the water!");
var secondQuestion = exports.addQuestion("Is winter at the same time of the year below the equator as it is above the equator?");