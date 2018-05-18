var stringModule = {};

/**
 * occurrencesOfSubstring()
 *
 * Count the occurrences of `substr` in `str`
 *
 * @param String str The haystack
 * @param String substr The needle
 * @return Number The number of occurrences of `substr` in `str`
 */
stringModule.occurrencesOfSubstring = function (str, substr) {
    var count = 0;
    var nextIndex = 0;

    if (typeof str != "string" || typeof substr != "string") {
        throw "Invalid string(s)";
    }

    str = str.trim();
    substr = substr.trim();

    if (substr == "") {
        throw "Invalid substring";
    }

    while ((nextIndex = str.indexOf(substr, nextIndex)) !== -1) {
        count++;
        nextIndex++;
    }

    return count;
};

/**
 * occurrencesOfSubstringInsensivie()
 *
 * Count the occurrences of `substr` in `str`, case insensitive
 *
 * @param String str The haystack
 * @param String substr The needle
 * @return Number The number of occurrences of `substr` in `str`
 */
stringModule.occurrencesOfSubstringInsensivie = function (str, substr) {
    if (typeof str != "string" || typeof substr != "string") {
        throw "Invalid string(s)";
    }

    return this.occurrencesOfSubstring(str.toLowerCase(), substr.toLowerCase());
};

/**
 * randomizeSentences()
 *
 * Given a paragraph, randomize the sentences
 *
 * @param String paragraph The paragraph
 * @return String The paragraph, with the sentences randomized
 */
stringModule.randomizeSentences = function (paragraph) {
    if (typeof paragraph != "string" || paragraph == "") {
        throw "Invalid paragraph";
    }

    paragraph = paragraph.trim();

    var sentences = paragraph.match(/[^\.!\?]+[\.!\?]+/g);
        
    // No valid sentences, return the original text
    if (sentences == null) {
        return paragraph;
    }

    // Randomly sort array
    sentences = sentences.sort(function (elem) {
        return Math.round(Math.random()) - 0.5;
    });

    // Trim excess spaces
    sentences = sentences.map(function (elem) {
        return elem.trim();
    });

    return sentences.join(' ');
};

module.exports = stringModule;