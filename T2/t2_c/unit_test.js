import assert from "assert";

// Choose proper "import" depending on your PL.
import { mancalaResult } from "./decorator.js";
// import { mancala_result as mancalaResult } from "./t2_rust/pkg/t1_rust.js"
// [Write your own "import" for other PLs.]

assert.strictEqual(mancalaResult(1,[11,12],2),30001);
assert.strictEqual(mancalaResult(1,[14],1),20001);
assert.strictEqual(mancalaResult(1,[13,16,26,12,16,11,22,25,13,16,15,21,16,14,25,22,16,15,24,16,14,23,15,21,16,14,24,12,26,13,16,15,16,14,16,15,25,16,11,26],40), 15024);
assert.strictEqual(mancalaResult(1,[13,16,26,12,16,11,22,25,13,16,15,21,16,14,25,22,16,15,24,16,14,23,15,21,16,14,24,12,26,13,16,15,16,14,16,15,25,16],38), 20030);
assert.strictEqual(mancalaResult(1,[13,16,26,12,16,11,22,25,13,16,15,21,16,14,25,22,16,15,24,16,14,11,15,21,16,14,24,12,26,13,16,15,16,14,16,15,25,16,11,26],40), 30021);
console.log("🎉 You have passed all the tests provided.");
