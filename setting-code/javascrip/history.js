function gethistory(day) {
 
    let history = JSON.parse(localStorage.getItem(day)) || [];
    if (history.length > 0)
    {
        const content=document.getElementById("history");
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
            p_date.textContent = "价格：123";
            li.appendChild(p_date);
           
        }
    }
    
}

let today = new Date().toISOString().split('T')[0];
gethistory(today);
