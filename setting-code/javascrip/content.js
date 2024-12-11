const back = document.getElementById("back");
back.addEventListener("click", function () {
    window.history.back();
})

const title = localStorage.getItem("now");
const title_content = document.querySelector(".header-title");
title_content.innerHTML = title;
