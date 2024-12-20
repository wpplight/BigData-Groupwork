// 选择所有具有 'card' 类的按钮
var resultPtr;
const buttons = document.querySelectorAll('.card');
var mm;  
function shuaxin()
{
    if (!sessionStorage.getItem("login")) {
        Module.onRuntimeInitialized = function () {
            // 现在运行时已经准备好
            resultPtr = _get();
            console.log(UTF8ToString(resultPtr));
            mm = UTF8ToString(resultPtr).split(" ");
            console.log(mm);
        let x=document.querySelectorAll('.card-title');
        for (let i = 0; i < 6; i++)
        {
           
            x[i].textContent = mm[i];   
            }
            localStorage.setItem("mm", JSON.stringify(mm));
             sessionStorage.setItem("login", "true");
        }
       
    }
    else
    {
        mm = localStorage.getItem("mm");
        mm=JSON.parse(mm)||[];
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

function addhistory(x)
{   let today = new Date().toISOString().split('T')[0];
    let history = JSON.parse(localStorage.getItem(today)) || [];
    let all = JSON.parse(localStorage.getItem('all')) || [];
    if(!all.includes(today))
        all.push(today);
        localStorage.setItem('all', JSON.stringify(all));
    if(!history.includes(x))
    history.push(x);
    
    localStorage.setItem(today, JSON.stringify(history));
}
// let all = JSON.parse(localStorage.getItem('all')) || [];
// localStorage.setItem(today, JSON.stringify(history));
