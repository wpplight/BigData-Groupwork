Module.onRuntimeInitialized = function () {
    // 选择所有具有 'card' 类的按钮
 
    const buttons = document.querySelectorAll('.card');
    var mm;
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
  
    function shuaxin() {
        if (!sessionStorage.getItem("login")) {
            alert("请先登录！");
            // 现在运行时已经准备好
            let inputStr="";
            const ii = JSON.parse(localStorage.getItem("buy")) || [];
            for (let i = 0; i < ii.length-1; i++)
            {
                inputStr += ii[i] + "|";
            }
            inputStr += ii[ii.length - 1];
            alert(inputStr);
            const inputPtr = passStringToWasm(inputStr);
            const resultPtr = Module._getstring(inputPtr);
            mm = getStringFromWasm(resultPtr);
            Module._free(inputPtr);
            Module._free(resultPtr);
            mm=mm.split(" ");
            let x = document.querySelectorAll('.card-title');
            for (let i = 0; i < 6; i++) {
                x[i].textContent = mm[i];
            }
            localStorage.setItem("mm", JSON.stringify(mm));
            sessionStorage.setItem("login", "true");
        
       
        }
        else {
            mm = localStorage.getItem("mm");
            mm = JSON.parse(mm) || [];
            let x = document.querySelectorAll('.card-title');
            for (let i = 0; i < 6; i++) {
                x[i].textContent = mm[i];
            }
        }
        
        
        
    }

    shuaxin();
    

    // 遍历所有按钮并添加事件监听器

    buttons.forEach(button => {

        button.addEventListener('click', function () {
            // 在这里处理点击事件
            var x = this.querySelector('.card-title').textContent;
            addhistory(x);
            goto(x);
        });
    });

    function addhistory(x) {
        let today = new Date().toISOString().split('T')[0];
        let history = JSON.parse(localStorage.getItem(today)) || [];
        let all = JSON.parse(localStorage.getItem('all')) || [];
        if (!all.includes(today))
            all.push(today);
        localStorage.setItem('all', JSON.stringify(all));
        if (!history.includes(x))
            history.push(x);
    
        localStorage.setItem(today, JSON.stringify(history));
    }
    // let all = JSON.parse(localStorage.getItem('all')) || [];
    // localStorage.setItem(today, JSON.stringify(history));
    const container = document.getElementById('content');
    const refreshIndicator = document.getElementById('refresh');
    let startY = 0;
    let isPullingDown = false;
    const maxPullDistance = 150; // 设定最大下拉距离

    document.getElementById('fuc').focus();

    // index.js 中添加日志输出
    container.addEventListener('touchstart', (e) => {
        if (container.scrollTop === 0) {
            startY = e.touches[0].clientY;
            isPullingDown = true;
        }
    });

    container.addEventListener('touchmove', (e) => {
        if (isPullingDown) {
            const currentY = e.touches[0].clientY;
            const distance = currentY - startY;

            if (distance > maxPullDistance) {
                refreshIndicator.style.transform = `translateX(-50%) translateY(${maxPullDistance}px)`;
            } else if (distance > 0) {
                e.preventDefault();
                refreshIndicator.style.display = 'block';
                refreshIndicator.style.transform = `translateX(-50%) translateY(${distance}px)`;
            }
        }
    });

    container.addEventListener('touchend', () => {
        if (isPullingDown) {
            const transformValue = refreshIndicator.style.transform;
            const match = transformValue.match(/translateY\(([^)]+)px\)/);
            const distance = match ? parseFloat(match[1]) : 0;



            if (distance >= maxPullDistance) {
                refresh();
            } else {
                resetIndicator();
            }
        }

        isPullingDown = false;
    });
    function resetIndicator() {
        refreshIndicator.style.transform = 'translateX(-50%) translateY(0)';
        refreshIndicator.style.display = 'none';
    }

    function refresh() {
        refreshIndicator.innerText = '正在加载...';

        resultPtr = _get();
       
        mm = UTF8ToString(resultPtr).split(" ");
     
        let x = document.querySelectorAll('.card-title');
        for (let i = 0; i < 6; i++) {

            x[i].textContent = mm[i];
        }
        localStorage.setItem("mm", JSON.stringify(mm));
        sessionStorage.setItem("login", "true");
        resetIndicator();
    }
    function gg() { 
    localStorage.setItem("search", document.getElementById('search-input').value);
    window.location.href = "webpages/search.html";
    }
    document.getElementById('search-button').addEventListener('click', gg);
};




