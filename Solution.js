/**
 * @param {string[]} words
 * @param {string} pattern
 * @return {string[]}
 */
var findAndReplacePattern = function (words, pattern) {
    var ans = new Array();
    var n = pattern.length, m = words.length, a = 'a'.charCodeAt(0);
    var m1 = new Array(), m2 = new Array();
    var word;
    for (let idx = 0; idx < m; ++idx) {
        word = words[idx];
        for (let i = 0; i < 26; ++i) {
            m1[i] = -1;
            m2[i] = -1;
        }
        let p = false;
        for (let i = 0; i < n; ++i) {
            let x = word.charCodeAt(i) - 'a', y = pattern.charCodeAt(i) - 'a';
            if (m1[x] == -1) m1[x] = y;
            if (m2[y] == -1) m2[y] = x;
            if (m1[x] != y || m2[y] != x) {
                p = true;
                break;
            }
        }
        if (p) ans.push(word);
    }
    return ans;
};