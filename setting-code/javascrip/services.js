var time = new Date().toLocaleString().split(" ");
document.getElementById("now_time").textContent = time[1].split(":")[0] + ":" + time[1].split(":")[1];
document.getElementById("day").textContent = time[0];
document.getElementById('fuc').focus();
var t;
var button_s = document.querySelectorAll(".option");
function ajexj_one()
{
    document.getElementById("til").textContent = "收藏";
    const content = document.getElementById("brutalist-card");
    content.innerHTML = "";
    const shoucang = JSON.parse(localStorage.getItem("add_list")) || [];
    let len = shoucang.length;
    for (let i = 0; i < len; i++)
    {
        let obj = document.createElement("div");
        obj.classList.add("brutalist-card__message");
        obj.textContent = shoucang[i];
        content.appendChild(obj);
        obj.addEventListener("click", function () {
            localStorage.setItem("now", shoucang[i]);
            window.location.href = "content.html"
            
        });
    }
    
}
function ajexj_two()
{
    document.getElementById("til").textContent = "就餐";
    const content = document.getElementById("brutalist-card");
    content.innerHTML = "";
    const shoucang = JSON.parse(localStorage.getItem("buy")) || [];
    let len = shoucang.length;
    for (let i = 0; i < len; i++) {
        let obj = document.createElement("div");
        obj.classList.add("brutalist-card__message");
        obj.textContent = shoucang[i];
        content.appendChild(obj);
        obj.addEventListener("click", function () {
            localStorage.setItem("now", shoucang[i]);
            window.location.href = "content.html"

        });
    }
}
function ajexj_three()
{
    document.getElementById("til").textContent = "花销";
    const content = document.getElementById("brutalist-card");
    content.innerHTML = "";
    const shoucang = JSON.parse(localStorage.getItem("buy")) || [];
    const price = JSON.parse(localStorage.getItem("price")) || {};
    let len = shoucang.length;
    let total = 0;
    for (let i = 0; i < len; i++) {
        let obj = document.createElement("div");
        obj.classList.add("brutalist-card__message");
        total += parseInt(price[shoucang[i]]);
        obj.textContent = shoucang[i]+" "+price[shoucang[i]]+"元";
        content.appendChild(obj);
    }
    let obj = document.createElement("div");
    obj.classList.add("brutalist-card__message");
    obj.textContent = "总花销: " +total+ "元";
    content.appendChild(obj);
}
function ajexj_four()
{
    document.getElementById("til").textContent = "健康";
    const content = document.getElementById("brutalist-card");
    content.innerHTML = "";
    function addmap() {
        let buy = JSON.parse(localStorage.getItem("buy")) || [];
        if (!buy.includes(title)) {
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
        let d = [];
        for (let i = 0; i < 5; i++) {
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

}

function ajexj(s)
{
    if (s == "收藏")
    {
        ajexj_one();
    }
    else if (s == "就餐")
    {
        ajexj_two();
    }
    else if (s == "花销")
    {
        ajexj_three();
    }
    else if (s == "健康")
    {
        ajexj_four();
    }
}
for (let i = 0; i < button_s.length; i++)
{
    button_s[i].addEventListener("click", function () {
        t = document.querySelectorAll(".span")[i].textContent;
        console.log(t);
        ajexj(t);
    })
}


if (!sessionStorage.getItem("theme"))
{
    ajexj("收藏");
}
