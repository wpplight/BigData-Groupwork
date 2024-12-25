function goto(name) {
    window.location.href = "content.html"
    localStorage.setItem("now", name);
}
function renew_listen() {
    const x = document.querySelectorAll(".history-item");
    for (let i = 0; i < x.length; i++) {
        x[i].addEventListener("click", function () {
            goto(this.querySelectorAll("h3")[0].textContent);
        });
    }
}
function gethistory(day) {
    let history = JSON.parse(localStorage.getItem(day)) || [];
    let price = JSON.parse(localStorage.getItem( "price")) || {};
    if (history.length > 0)
    {
        const content = document.getElementById("history");
        
        for (let i =history.length-1 ; i >=0 ; i--)
        {
            const li = document.createElement("li");
            li.classList.add("history-item");
            content.appendChild(li);
            const h3 = document.createElement("h3");
            h3.textContent = history[i];
            li.appendChild(h3);
            const p_time = document.createElement("p");
            p_time.textContent = "时间: " + day;
            li.appendChild(p_time);
            const p_date = document.createElement("p");
            p_date.textContent = "价格:"+ price[history[i]];
            li.appendChild(p_date);
           
        }
        renew_listen();
    }
    
}
function creatla(date)
{
    const conten = document.getElementById("label-box");
    const ii = document.createElement("label");
    ii.classList.add("label-i");
    const input = document.createElement("input");
    input.type = "radio";
    input.name = "radio";
    ii.appendChild(input);
    const span = document.createElement("span");
    span.classList.add("label-span");
    span.textContent = date;
    ii.appendChild(span);
    conten.appendChild(ii);
}
function addlable()
{   
    for (let i = allt.length - 1; i > allt.length - 6; i--)
    {
        if (i < 0) break;
            let c = allt[i].split('-');
            c = c[1] + '.' + c[2];
            mm.set(c, allt[i]);
            creatla(c);
        

    }

}
var allt = JSON.parse(localStorage.getItem('all')) || [];
while (allt.length > 18) {
    const first = allt[0];
    allt.shift();
    localStorage.removeItem(first);
}
let today =new Date().toISOString().split('T')[0];
var mm =new Map();
addlable();
const day = sessionStorage.getItem("history");
if (!day)
{
    gethistory(today);
}
else
{
    gethistory(day);
}

document.getElementById('fuc').focus();

const x = document.querySelectorAll(".label-span");
for (let i = 0; i < x.length; i++) {
    x[i].addEventListener("click", function () {
        const date = mm.get(this.textContent);
        sessionStorage.setItem("history", date);
        document.getElementById("history").innerHTML = "";
        gethistory(date);
    });
}


