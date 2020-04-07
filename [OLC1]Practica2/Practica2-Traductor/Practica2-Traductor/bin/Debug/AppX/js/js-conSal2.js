function pagSal1(pageName, elmnt){
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent-Sal1");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }

    tablinks = document.getElementsByClassName("tab-Sal1");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].style.backgroundColor = "";
    }

    document.getElementById(pageName).style.display = "block";
    elmnt.style.backgroundColor = "gray";
}


document.getElementById("defualt-Sal1").click();