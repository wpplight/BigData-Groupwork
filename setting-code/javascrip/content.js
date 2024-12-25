Module.onRuntimeInitialized = function () {
    
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

    const back = document.getElementById("back");
    back.addEventListener("click", function () {
        window.history.back();
    })

    function add(title) {

        const index = x.indexOf(title);

        if (index !== -1) { // 检查元素是否存在
            x.splice(index, 1); // 删除索引为 index 的元素
            add_.setAttribute('fill', 'none'); // 添加引号
        }
        else {
            x.push(title);
            add_.setAttribute('fill', '#ffe381'); // 添加引号
        }
        localStorage.setItem("add_list", JSON.stringify(x));
    
    }
    function addmap() {
        let buy = JSON.parse(localStorage.getItem("buy")) || [];
        if (!buy.includes(title))
        {
            buy.push(title);
            localStorage.setItem("buy", JSON.stringify(buy));
        }

        const chu = [8, 7, 12, 4, 3];
        const inputStr = title;
        const inputPtr = passStringToWasm(inputStr);
        const resultPtr = _getmark(inputPtr);
        r = getStringFromWasm(resultPtr);
        Module._free(inputPtr);
        Module._free(resultPtr);
        r = r.split("|");
        let d=[];
        for (let i = 0; i < 5; i++)
        {
            d.push(parseFloat(r[i]) / chu[i]);
        }
        const ctx = document.getElementById('radarChart').getContext('2d');

        const data = {
            labels: ['蛋白质', '脂肪', '碳水化合物', '维生素', '膳食纤维'], // 五个能力标签
            datasets: [{
                label: '营养成分',
                data: d, // 对应每个能力的评分
                backgroundColor: 'rgba(251, 148, 170, 0.2)', // 填充颜色
                borderColor: 'rgb(254, 112, 143)', // 边框颜色
                borderWidth: 1 // 边框宽度
            }]
        };

        const radarChart = new Chart(ctx, {
            type: 'radar',
            data: data,
            options: {
                scale: {
                    ticks: {
                        beginAtZero: true,
                        max: 5, // 根据评分的范围设置最大值
                    },
                    pointLabels: { // 设置标签样式
                        font: {
                            size: 20 // 设置点标签（能力标签）字体大小
                        }
                    }
                },
                elements: {
                    line: {
                        tension: 0 // 线性连接
                    }
                }
            }
        });
    
    }
    function get_market()
    {
        

            const inputPtr = passStringToWasm(title);
            const resultPtr = Module._getmarket(inputPtr);
        re = getStringFromWasm(resultPtr);
            Module._free(inputPtr);
            Module._free(resultPtr);
            document.getElementById("market").textContent = "店铺:" + re;
        
        
    }
    document.getElementById("buttonto").addEventListener("click", function () {
        addmap();
    });
    const title = localStorage.getItem("now");
    var price = JSON.parse(localStorage.getItem("price"))||{};
    document.querySelector(".header-title").innerHTML = title;
    document.querySelector(".name").innerHTML = title;
    document.querySelector(".price").innerHTML = "￥" + price[title];
    var x = JSON.parse(localStorage.getItem("add_list")) || [];
    var add_ = document.getElementById("add_like");
    get_market();
    if (x.indexOf(title) != -1) {
        add_.setAttribute('fill', '#ffe381'); // 添加引号
    }
    document.getElementById("add").addEventListener("click", function () {
        add(title);
    })

};