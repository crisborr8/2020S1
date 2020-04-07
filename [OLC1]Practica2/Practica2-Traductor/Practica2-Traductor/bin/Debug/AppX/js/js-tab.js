var pestAct;

function crearPagina(i) {
    var nombre = "Nueva Pestaña ";
    if(i == -1)
        i = document.getElementsByClassName("tabcontent").length + 1;
    document.getElementById("botones").insertAdjacentHTML("beforeend", "<button class=\"tablink\" onclick = \"openPage(this)\" value=\"" + nombre + i + "\">" + nombre + i + "</button>");
    document.getElementById("contenido-botones").insertAdjacentHTML("beforeend", "<div id=\"" + nombre + i + "\" class=\"tabcontent\"></div>");
    document.getElementById(nombre + i).insertAdjacentHTML("beforeend", "<textarea class=\"textoCodigo\" id=\"txt_" + nombre + i + "\" rows=\"20\" cols=\"110\"></textarea>");
}

function abrir() {
    var fileToLoad = document.getElementById("abrir").files[0];
    var fileReader = new FileReader();
    fileReader.onload = function (fileLoadedEvent) {
        var textFromFileLoaded = fileLoadedEvent.target.result;
        document.getElementById("txt_" + pestAct).textContent = textFromFileLoaded;
        var tablinks = document.getElementsByClassName("tablink");
        for (i = 0; i < tablinks.length; i++) {
            if (tablinks[i].value == pestAct) {
                tablinks[i].innerHTML = fileToLoad.name;
                break;
            }
        }
    };

    fileReader.readAsText(fileToLoad, "UTF-8");
}

function salir() {
    if (confirm("¿Cerrar pestaña?")) {
        window.close();
    }
}

function guardar() {
    guardarC();
}

function guardarC() {
    var type = ".cs";
    var data = document.getElementById("txt_" + pestAct).value;

    var nombre = pestAct;
    var tablinks = document.getElementsByClassName("tablink");
    for (i = 0; i < tablinks.length; i++) {
        if (tablinks[i].value == pestAct) {
            nombre = tablinks[i].textContent.replace(".cs", "");
            break;
        }
    }

    var file = new Blob([data], { type: type });
    if (window.navigator.msSaveOrOpenBlob) // IE10+
        window.navigator.msSaveOrOpenBlob(file, nombre);
    else { // Others
        var a = document.createElement("a"),
            url = URL.createObjectURL(file);
        a.href = url;
        a.download = nombre + ".cs";
        document.body.appendChild(a);
        a.click();
        setTimeout(function () {
            document.body.removeChild(a);
            window.URL.revokeObjectURL(url);
        }, 0);
    }
}

function openPage(elmnt) {
    var pageName = elmnt.value;
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