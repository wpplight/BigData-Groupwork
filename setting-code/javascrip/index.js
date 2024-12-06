// 选择所有具有 'card' 类的按钮
const buttons = document.querySelectorAll('.card');

// 遍历所有按钮并添加事件监听器
buttons.forEach(button => {
    button.addEventListener('click', function () {
        // 在这里处理点击事件
        alert(`按钮 ${this.querySelector('.card-title').textContent} 被点击了!`);
        var x = this.querySelector('.card-title').textContent;
    });
});