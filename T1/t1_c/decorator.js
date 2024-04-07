import { readFileSync } from 'fs';
function bocchiShutUp(flag, seq, size) {
    const wasmBuffer = readFileSync('t1_c/0404-1.wasm');

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
    return wasmInstance.exports.bocchiShutUp(flag, 0, size);
}

// 导出包装函数，以便其他 JavaScript 文件可以引入并调用
export { bocchiShutUp };
