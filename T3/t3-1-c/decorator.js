import { readFileSync } from 'fs';
import { fileURLToPath } from 'url';
import { dirname, join } from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);
function mancalaBoard(flag, seq, size) {
    const wasmBuffer = readFileSync(join(__dirname, 't3.wasm'));

// 创建 Uint8Array 对象
    const wasmCode = new Uint8Array(wasmBuffer);

    // 定义需要传递给 WebAssembly 模块的数组
    const wasmModule = new WebAssembly.Module(wasmCode); 
    const wasmInstance = new WebAssembly.Instance(wasmModule);
    const memory = new Int32Array(wasmInstance.exports.memory.buffer);
    seq.forEach((value, index) => {
        memory[index] = value;
    });
    // 调用 WebAssembly 模块中的函数，并传递起始地址和数组长度
    wasmInstance.exports.mancalaBoard(flag, 0, size);
    const newArray = [];

    // 将内存的前 15 个元素拷贝到新数组
    for (let i = 0; i < 15; i++) {
        newArray.push(memory[i]);
    }
    return newArray;
}
// 导出包装函数，以便其他 JavaScript 文件可以引入并调用
//console.log(mancalaBoard(1,[13,16,26,12,16,11,22,25,13,16,15,21,16,14,25,22,16,15,24,16,14,23,15,21,16,14,24,12,26,13,16,15,16,14,16,15,25,16],38))
export { mancalaBoard };
