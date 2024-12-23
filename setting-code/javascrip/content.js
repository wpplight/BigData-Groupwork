const back = document.getElementById("back");
back.addEventListener("click", function () {
    window.history.back();
})

function add(title)
{

        const index = x.indexOf(title);

        if (index !== -1) { // 检查元素是否存在
            x.splice(index, 1); // 删除索引为 index 的元素
            add_.setAttribute('fill', 'none'); // 添加引号
        }
    else
        {
            x.push(title);
            add_.setAttribute('fill', '#ffe381'); // 添加引号
    }
    localStorage.setItem("add_list", JSON.stringify(x));
    
}

const title = localStorage.getItem("now");
document.querySelector(".header-title").innerHTML = title;
document.querySelector(".name").innerHTML = title;
var x = JSON.parse(localStorage.getItem("add_list")) || [];
var add_ = document.getElementById("add_like");
if (x.indexOf(title)!=-1)
{
    add_.setAttribute('fill', '#ffe381'); // 添加引号
}
document.getElementById("add").addEventListener("click", function () {
    add(title);
})

