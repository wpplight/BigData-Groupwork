var UTF8ArrayToString = (heapOrArray, idx = 0, maxBytesToRead = NaN) => {
    var endIdx = idx + maxBytesToRead;
    var endPtr = idx;
    while (heapOrArray[endPtr] && !(endPtr >= endIdx)) ++endPtr;

    if (endPtr - idx > 16 && heapOrArray.buffer && UTF8Decoder) {
        return UTF8Decoder.decode(heapOrArray.subarray(idx, endPtr));
    }
    var str = '';
    while (idx < endPtr) {

        var u0 = heapOrArray[idx++];
        if (!(u0 & 0x80)) { str += String.fromCharCode(u0); continue; }
        var u1 = heapOrArray[idx++] & 63;
        if ((u0 & 0xE0) == 0xC0) { str += String.fromCharCode(((u0 & 31) << 6) | u1); continue; }
        var u2 = heapOrArray[idx++] & 63;
        if ((u0 & 0xF0) == 0xE0) {
            u0 = ((u0 & 15) << 12) | (u1 << 6) | u2;
        } else {
            if ((u0 & 0xF8) != 0xF0) warnOnce('Invalid UTF-8 leading byte ' + ptrToString(u0) + ' encountered when deserializing a UTF-8 string in wasm memory to a JS string!');
            u0 = ((u0 & 7) << 18) | (u1 << 12) | (u2 << 6) | (heapOrArray[idx++] & 63);
        }

        if (u0 < 0x10000) {
            str += String.fromCharCode(u0);
        } else {
            var ch = u0 - 0x10000;
            str += String.fromCharCode(0xD800 | (ch >> 10), 0xDC00 | (ch & 0x3FF));
        }
    }
    return str;
};
var UTF8ToString = (ptr, maxBytesToRead) => {
    assert(typeof ptr == 'number', `UTF8ToString expects a number (got ${typeof ptr})`);
    return ptr ? UTF8ArrayToString(HEAPU8, ptr, maxBytesToRead) : '';
};
async function loadWasm() {
    const response = await fetch('test.wasm'); // 加载 WASM 文件
    return await WebAssembly.instantiateStreaming(response);
}
