var txt;

function analizar(elmnt) {
    getTexto(elmnt);
    alert(txt);
}

function getTexto(elmnt) {
    txt = "";
    var pageName = elmnt.value;
    txt = document.getElementById("txt_" + pestAct).value;
}