function goto(name,price)
{
    localStorage.setItem("now", name);
    localStorage.setItem("nowprice", price);
    window.location.href = "webpages/content.html"
}
    
   

