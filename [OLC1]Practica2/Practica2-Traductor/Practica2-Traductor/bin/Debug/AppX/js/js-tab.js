var pestAct;

function crearPagina(nombre, i) {
    if(i == -1)
        i = document.getElementsByClassName("tabcontent").length + 1;
    document.getElementById("botones").insertAdjacentHTML("beforeend", "<button class=\"tablink\" onclick = \"openPage('" + nombre + i + "', this)\" >" + nombre + i + "</button>");
    document.getElementById("contenido-botones").insertAdjacentHTML("beforeend", "<div id=\"" + nombre + i + "\" class=\"tabcontent\"></div>");
    document.getElementById(nombre + i).insertAdjacentHTML("beforeend", "<textarea class=\"textoCodigo\" id=\"txt_" + nombre + i + "\" rows=\"20\" cols=\"110\"></textarea>");
}

function abrir() {
    var fileToLoad = document.getElementById("abrir").files[0];
    var fileReader = new FileReader();
    fileReader.onload = function (fileLoadedEvent) {
        var textFromFileLoaded = fileLoadedEvent.target.result;
        document.getElementById("txt_" + pestAct).textContent = textFromFileLoaded;
    };

    fileReader.readAsText(fileToLoad, "UTF-8");
}

function guardarC() {
    var type = ".txt";
    var data = document.getElementById("txt_" + pestAct).value;
    var file = new Blob([data], { type: type });
    if (window.navigator.msSaveOrOpenBlob) // IE10+
        window.navigator.msSaveOrOpenBlob(file, pestAct);
    else { // Others
        var a = document.createElement("a"),
            url = URL.createObjectURL(file);
        a.href = url;
        a.download = pestAct;
        document.body.appendChild(a);
        a.click();
        setTimeout(function () {
            document.body.removeChild(a);
            window.URL.revokeObjectURL(url);
        }, 0);
    }
}

function openPage(pageName, elmnt) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    
    tablinks = document.getElementsByClassName("tablink");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].style.backgroundColor = "";
    }
    
    document.getElementById(pageName).style.display = "block";
    
    elmnt.style.backgroundColor = "gray";
    pestAct = pageName;
}

document.getElementById("defaultOpen").click();