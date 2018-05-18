var stringModule = require('../string.js');

// Test occurencesOfSubstring
var num = stringModule.occurrencesOfSubstring("abcdef", "def");
console.log((num == 1) ? 'occurrencesOfSubstring test 1 passed' : 'occurrencesOfSubstring test 1 FAILED!');
num = stringModule.occurrencesOfSubstring("abcdefdef", "def");
console.log((num == 2) ? 'occurrencesOfSubstring test 2 passed' : 'occurrencesOfSubstring test 2 FAILED!');
num = stringModule.occurrencesOfSubstring("abc", "def");
console.log((num == 0) ? 'occurrencesOfSubstring test 3 passed' : 'occurrencesOfSubstring test 3 FAILED!');
num = stringModule.occurrencesOfSubstring("", "def");
console.log((num == 0) ? 'occurrencesOfSubstring test 4 passed' : 'occurrencesOfSubstring test 4 FAILED!');
num = stringModule.occurrencesOfSubstring("ABCDEF", "def");
console.log((num == 0) ? 'occurrencesOfSubstring test 5 passed' : 'occurrencesOfSubstring test 5 FAILED!');
try {
    num = stringModule.occurencesOfSubstring(null, "abc");
    console.log("occurencesOfSubstring test 6 FAILED!");
} catch (err) {
    console.log("occurencesOfSubstring test 6 passed");
}
try {
    num = stringModule.occurencesOfSubstring("abc", "");
    console.log("occurencesOfSubstring test 7 FAILED!");
} catch (err) {
    console.log("occurencesOfSubstring test 7 passed");
}
try {
    num = stringModule.occurencesOfSubstring("abc", " ");
    console.log("occurencesOfSubstring test 8 FAILED!");
} catch (err) {
    console.log("occurencesOfSubstring test 8 passed");
}
try {
    num = stringModule.occurencesOfSubstring("abc", null);
    console.log("occurencesOfSubstring test 9 FAILED!");
} catch (err) {
    console.log("occurencesOfSubstring test 9 passed");
}
num = stringModule.occurrencesOfSubstring("foofoofoo", "foofoo");
console.log((num == 2) ? 'occurrencesOfSubstring test 9 passed' : 'occurrencesOfSubstring test 9 FAILED!');

// Test occurrencesOfSubstringInsensivie
// Not being too exhaustive with this because it uses occurrencesOfSubstring()
num = stringModule.occurrencesOfSubstringInsensivie("ABCDEF", "def");
console.log((num == 1) ? 'occurrencesOfSubstringInsensivie test 1 passed' : 'occurrencesOfSubstringInsensivie test 1 FAILED!');
num = stringModule.occurrencesOfSubstringInsensivie("ABC", "def");
console.log((num == 0) ? 'occurrencesOfSubstringInsensivie test 2 passed' : 'occurrencesOfSubstringInsensivie test 2 FAILED!');
num = stringModule.occurrencesOfSubstringInsensivie("", "def");
console.log((num == 0) ? 'occurrencesOfSubstringInsensivie test 3 passed' : 'occurrencesOfSubstringInsensivie test 3 FAILED!');

// Test randomizeSentences
// This can't be tested since it's random
console.log(stringModule.randomizeSentences("What's up. How are you. What are you doing. I am well."));
console.log(stringModule.randomizeSentences("What's up. How are you. What are you doing. I am well"));
console.log(stringModule.randomizeSentences("What's up."));
console.log(stringModule.randomizeSentences("Hello. How are you? I'm doing well, thanks!"));
try {
    console.log(stringModule.randomizeSentences(""));
    console.log("randomizeSentences test 1 FAILED!");
} catch (err) {
    console.log("randomizeSentences test 1 passed");
}