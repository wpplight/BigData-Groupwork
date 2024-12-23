
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
    var result;
    function renew_listen() {
        const x = document.querySelectorAll(".search-item");
        for (let i = 0; i < x.length; i++) {
            x[i].addEventListener("click", function () {
                window.location.href = "content.html"
                localStorage.setItem("now", this.querySelectorAll("h3")[0].textContent);
            });
        }
    }
    function getsearch() {

        if (history.length > 0) {
            const content = document.getElementById("list");

            for (let i =  result.length - 2; i >= 0; i--) {
                const li = document.createElement("li");
                li.classList.add("search-item");
                content.appendChild(li);
                const h3 = document.createElement("h3");
                h3.textContent = result[i];
                li.appendChild(h3);
                // const p_time = document.createElement("p");
                // p_time.textContent = "时间: " + day;
                // li.appendChild(p_time);
                const p_date = document.createElement("p");
                p_date.textContent = "价格：123";
                li.appendChild(p_date);

            }
            renew_listen();
        }

    }
    function calculate() {
        const inputStr = localStorage.getItem("search");
        const inputPtr = passStringToWasm(inputStr);
        const resultPtr = Module._search(inputPtr);
       result = getStringFromWasm(resultPtr);


        result = result.split("\r ");
        console.log(result);
        getsearch();

        Module._free(inputPtr);
        Module._free(resultPtr);
    }
    calculate();

};
