console.log("searchs.js is running");
Module.onRuntimeInitialized = function () {
    // JavaScript 代码
    function passStringToWasm(jsString) {
        const utf8Bytes = new TextEncoder().encode(jsString);
        const ptr = Module._malloc(utf8Bytes.length + 1); // +1 是为了终止符 '\0'
        Module.HEAPU8.set(utf8Bytes, ptr);
        Module.HEAPU8[ptr + utf8Bytes.length] = 0; // 添加终止符
        return ptr;
    }

    function getStringFromWasm(ptr) {
        const bytes = [];
        let byte = Module.HEAPU8[ptr];
        while (byte !== 0) {
            bytes.push(byte);
            byte = Module.HEAPU8[++ptr];
        }
        return new TextDecoder().decode(new Uint8Array(bytes));
    }

    function calculate() {
        const inputStr = localStorage.getItem("search");
        alert(inputStr);
        const inputPtr = passStringToWasm(inputStr);
        const resultPtr = Module._search(inputPtr);
        const result = getStringFromWasm(resultPtr);


        console.log(result.split("\r "));

        Module._free(inputPtr);
        Module._free(resultPtr);
    }
    calculate();

};
