const back = document.getElementById("back");
back.addEventListener("click", function () {
    window.history.back();
})

const title = localStorage.getItem("now");
document.querySelector(".header-title").innerHTML = title;
document.querySelector(".name").innerHTML = title;