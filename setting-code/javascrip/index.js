// 选择所有具有 'card' 类的按钮
const buttons = document.querySelectorAll('.card');

// 遍历所有按钮并添加事件监听器
buttons.forEach(button => {
    button.addEventListener('click', function () {
        // 在这里处理点击事件
        
        var x = this.querySelector('.card-title').textContent;
        addhistory(x);
        alert(`按钮 ${this.querySelector('.card-title').textContent} 被点击了!`);
    });
});

function addhistory(x)
{   let today = new Date().toISOString().split('T')[0];
    let history = JSON.parse(localStorage.getItem(today)) || [];
    if (history == []) 
    {
        let all = JSON.parse(localStorage.getItem('all')) || [];
        all.push(today);
        if (all.length > 7)
        {
            while (all.length > 7)
            {
                const first = all[0];
                all.shift();
                localStorage.removeItem(first);
            }
            localStorage.setItem('all', JSON.stringify(all));
        }
        
    }
    if(!history.includes(x))
    history.push(x);
    
    localStorage.setItem(today, JSON.stringify(history));
}