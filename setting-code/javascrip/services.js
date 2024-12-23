var time = new Date().toLocaleString().split(" ");
document.getElementById("now_time").textContent = time[1].split(":")[0] + ":" + time[1].split(":")[1];
document.getElementById("day").textContent = time[0];
document.getElementById('fuc').focus();
var t;
var button_s = document.querySelectorAll(".option");
function ajexj_one()
{
    document.getElementById("til").textContent = "收藏";
    
}
function ajexj_two()
{
    document.getElementById("til").textContent = "就餐记录";
}
function ajexj_three()
{
    document.getElementById("til").textContent = "花销";
}

function ajexj(s)
{
    if (s == "收藏")
    {
        ajexj_one();
    }
    else if (s == "就餐记录")
    {
        ajexj_two();
    }
    else if (s == "花销")
    {
        ajexj_three();
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
