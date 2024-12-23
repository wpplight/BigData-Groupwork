var time = new Date().toLocaleString().split(" ");
document.getElementById("now_time").textContent = time[1].split(":")[0] + ":" + time[1].split(":")[1];
document.getElementById("day").textContent = time[0];
document.getElementById('fuc').focus();
