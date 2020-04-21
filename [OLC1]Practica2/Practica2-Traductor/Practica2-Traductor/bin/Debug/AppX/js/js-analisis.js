var pila;
var txt, txt_linea;
var pActual, cActual;
var i_fil, i_col;
var tabla, tablaCont;
var cSalida, T;
var L, D;


function analizar() {
    inicializar();
    ingresarDatos();
    inicio();
    finalizar();
}

//ESTADOS---------------------------------------------------------------------------
function inicio() {
    while (analizando == true) {
        getCharacter();
        alert(cActual);
        S0();
        estados();
    }
}
function estados() {
    if (pila.length > 0) {
        switch (pila.pop()) {
            case "S0": S0(); break;
            case "P1": P1(); break;
            case "Cla": Cla(); break;
            case "Se1": Se1(); break;
            case "P2": P2(); break;
            case "M": M(); break;
            case "Df": Df(); break;
            case "De1": De1(); break;
            case "De2": De2(); break;
            case "Pa1": Pa1(); break;
            case "Pa2": Pa2(); break;
            case "Pa3": Pa3(); break;
            case "Se2": Se2(); break;
            case "P3": P3(); break;
            case "P4": P4_1(); break;
            case "P4_2": P4_2(); break;
            case "If": If(); break;
            case "If2": If2(); break;
            case "El1": El1(); break;
            case "El2": El2(); break;
            case "Con1": Con1(); break;
            case "Con2": Con2(); break;
            case "Sw": Sw(); break;
            case "Cas": Cas(); break;
            case "Br": Br(); break;
            case "Br2": Br2(); break;
            case "Def": Def(); break;
            case "Val": Val(); break;
            case "Val2": Val2(); break;
            case "Fo": Fo(); break;
            case "Dec1": Dec1(); break;
            case "Dec2": Dec2(); break;
            case "Con3": Con3(); break;
            case "Inc1": Inc1(); break;
            case "Inc2": Inc2(); break;
            case "Inc3": Inc3(); break;
            case "It1": It1(); break;
            case "It2": It2(); break;
            case "It3": It3(); break;
            case "It4": It4(); break;
            case "It5": It5(); break;
            case "It6": It6(); break;
            case "SeR1": SeR1(); break;
            case "SeR2": SeR2(); break;
            case "SeR3": SeR3(); break;
            case "Ctn": Ctn(); break;
            case "Wh": Wh(); break;
            case "Dw": Dw(); break;
            case "Im": Im(); break;
            case "R": R(); break;
            case "Co": Co(); break;
            case "Co2": Co2(); break;
            case "Com": Com(); break;
            case "Col": Col(); break;
            case "Ex2": Ex2(); break;
            case "E": E(); break;
            case "Ea": Ea(); break;
            case "Eb": Eb(); break;
            case "Id2": Id2(); break;
            case "E2": E2(); break;
            case "E3": E3(); break;
        }
    }
}
function S0() {
    if (cActual == "/" || cActual == "v" || cActual == "c" || cActual == "i" || cActual == "d" || cActual == "s" || cActual == "b") {
        pila.push("S0");
        pila.push("P1");
        estados();
    }
    else if (cActual == "") {
        pila.pop();
        estados();
    }
    else setErrorLexico();
}
function P1() {
    if (cActual == "/") {
        pila.push("Co");
        estados();
    }
    else if (cActual == "v") {
        pila.push("Se1");
        estados();
    }
    else if (cActual == "c") {
        if (txt_linea[i_fil][i_col + 1] == "l") pila.push("Cla");
        else pila.push("Td");
        estados();
    }
    else if (cActual == "i" || cActual == "d" || cActual == "s" || cActual == "b") {
        pila.push("Td");
        estados();
    }
    else if (cActual == "") {
        pila.pop();
        estados();
    }
    else setErrorLexico();
}
function Cla() {
    getPalabra();
    if (pActual == "class") {
        pila.push("}");
        pila.push("Se1");
        pila.push("{");
        pila.push("Id");
        estados();
    }
    else setErrorSintactico("class");
}
function Se1() {
    if (cActual == "/") {
        pila.push("Co");
        estados();
    }
    else if (cActual == "v" || cActual == "c" || cActual == "i" || cActual == "d" || cActual == "s" || cActual == "b") {
        pila.push("Se1");
        pila.push("P2");
        estados();
    }
    else if (cActual == "}" || cActual == "") {
        pila.pop();
        estados();
    }
    else setErrorLexico();
}
function P2() {
    if (cActual == "/") {
        pila.push("Co");
        estados();
    }
    else if (cActual == "c" || cActual == "i" || cActual == "d" || cActual == "s" || cActual == "b") {
        pila.push("Df");
        pila.push("Id");
        pila.push("Td");
        estados();
    }
    else if (cActual == "v") {
        getPalabra();
        if (pActual == "void") {
            pila.push("M");
            estados();
        }
        else setErrorSintactico("void");
    }
}
function M() {
    if (L.includes(cActual)) {
        getPalabra();
        if (pActual == "main") {
            pila.push("Se2");
            pila.push(")");
            pila.push("(");
            estados();
        }
        else {
            pila.push("Pa1");
            estados();
        }
    }
    else setErrorLexico();
}
function Df() {
    if (cActual == "," || cActual == ";" || cActual == "=") {
        pila.push("De1");
        estados();
    }
    else if (cActual == "(") {
        pila.push("Pa1");
        estados();
    }
    else setErrorSintactico(";, =, ( o ,");
}
function De1() {
    if (cActual == "," || cActual == ";") {
        pila.push("De2");
        estados();
    }
    else if (cActual == "=") {
        getCharacter();
        pila.push("De2");
        pila.push("E");
        pila.push("=");
        estados();
    }
    else setErrorSintactico(";, = o ,");
}
function De2() {
    if (cActual == ";") {
        pila.push(";");
        estados();
    }
    else if (cActual == ",") {
        pila.push("De1");
        pila.push("Id");
        estados();
    }
    else setErrorSintactico("; o ,");
}
function Pa1() {
    if (cActual == "(") {
        pila.push("Se2");
        pila.push(")");
        pila.push("Pa2");
        pila.push("(");
        estados();
    }
    else setErrorSintactico("(");
}
function Pa2() {
    if (cActual == "c" || cActual == "i" || cActual == "d" || cActual == "s" || cActual == "b") {
        pila.push("Pa3");
        pila.push("Id");
        pila.push("Td");
        estados();
    }
    else if (cActual == ")" || cActual == "") {
        estados();
    }
    else setErrorSintactico("), char, int, double, string o bool");
}
function Pa3() {
    if (cActual == ",") {
        pila.push("Pa3");
        pila.push("Id");
        pila.push("Td");
        pila.push(",");
        estados();
    }
    else if (cActual == ")" || cActual == "") {
        pila.pop();
        estados();
    }
    else setErrorSintactico(") o ,");
}
function Se2() {
    if (cActual == "{") {
        pila.push("}");
        pila.push("P3");
        pila.push("{");
        estados();
    }
    else setErrorSintactico("{");
}
function P3() {
    if (cActual == "/" || L.includes(cActual)) {
        pila.push("P3");
        pila.push("P4");
        estados();
    }
    else if (cActual == "}" || cActual == "") {
        pila.pop();
        estados();
    }
    else setErrorSintactico("/, }, int, double, string, char, bool o Id");
}
function P4_1() {
    if (cActual == "/") {
        pila.push("Co");
        estados();
    }
    else if (L.includes(cActual)) {
        getPalabra();
        if (T.includes(pActual)) {
            pila.push("De1");
            pila.push("Id");
        }
        else if (pActual == "if") pila.push("If");
        else if (pActual == "for") pila.push("Fo");
        else if (pActual == "while") pila.push("Wh");
        else if (pActual == "return") pila.push("R");
        else if (pActual == "switch") pila.push("Sw");
        else if (pActual == "Console") pila.push("Im");
        else {
            pila.push(";");
            pila.push("Ex2");
        }
        estados();
    }
    else setErrorSintactico("/, int, double, string, char, bool, Id, if, switch, do, while, for, Console o return");
}
function P4_2() {
    if (cActual == "/") {
        pila.push("Co");
        estados();
    }
    else if (L.includes(cActual)) {
        getPalabra();
        if (T.includes(pActual)) {
            pila.push("De1");
            pila.push("Id");
        }
        else if (pActual == "if") pila.push("If");
        else if (pActual == "for") pila.push("Fo");
        else if (pActual == "while") pila.push("Wh");
        else if (pActual == "return") pila.push("R");
        else if (pActual == "break") pila.push("Br2");
        else if (pActual == "switch") pila.push("Sw");
        else if (pActual == "Console") pila.push("Im");
        else if (pActual == "continue") pila.push("Ctn");
        else {
            pila.push(";");
            pila.push("Ex2");
        }
        estados();
    }
    else setErrorSintactico("/, int, double, string, char, bool, Id, if, switch, do, while, for, console, continue, break o return");
}
function If() {
    pila.push("El1");
    pila.push("If2");
    estados();
}
function If2() {
    if (cActual == "(") {
        pila.push("Se2");
        pila.push(")");
        pila.push("Con1");
        pila.push("(");
        estados();
    }
    else setErrorSintactico("(");
}
function El1() {
    getPalabra();
    if (pActual == "else") {
        pila.push("El2");
        estados();
    }
    else setErrorSintactico("else");
}
function El2() {
    if (cActual == "{") {
        pila.push("El1");
        pila.push("Se2");
        estados();
    }
    else if (L.includes(cActual)) {
        if (pActual == "if") {
            pila.push("If2");
            estados();
        }
        else setErrorSintactico("if o {");
    }
    else setErrorSintactico("if o {");
}
function Con1() {
    if (cActual == "(") {
        pila.push(")");
        pila.push("Con1");
        pila.push("(");
        estados();
    }
    else if (cActual == "!") {
        pila.push("!");
        estados();
    }
    else if (L.includes(cActual) || cActual == "\"" || cActual == "'" || D.includes(cActual)) {
        pila.push("Con2");
        pila.push("O5");
        pila.push("Con2");
        estados();
    }
    else setErrorSintactico("(, !, Id, Numero, \", ', True o False");
}
function Con2() {
    if (cActual == "(" || cActual == "!") {
        pila.push("Con1");
        estados();
    }
    else if (L.includes(cActual) || cActual == "\"" || cActual == "'" || D.includes(cActual)) {
        pila.push("E");
        estados();
    }
    else setErrorSintactico("(, !, Id, Numero, \", ', True o False");
}
function Sw() {
    if (cActual == "(") {
        pila.push("}");
        pila.push("Def");
        pila.push("Cas");
        pila.push("{");
        pila.push(")");
        pila.push("Val");
        pila.push("(");
        estados();
    }
    else setErrorSintactico("(");
}
function Cas() {
    if (cActual == "c") {
        getPalabra();
        if (pActual == "case") {
            pila.push("Cas");
            pila.push("Br");
            pila.push("P3");
            pila.push(":");
            pila.push("Val");
            estados();
        }
        else setErrorSintactico("case");
    }
    else if (cActual == "d" || cActual == "}") estados();
    else setErrorSintactico("}");
}
function Br() {
    if (cActual == "b") {
        pila.push("Br2");
        estados();
    }
    else if (cActual == "c" || cActual == "d") estados();
    else setErrorSintactico("break, case o default");
}
function Br2() {
    if (cActual == "b") {
        getPalabra();
        if (pActual == "break") {
            pila.push(";");
            estados();
        }
        else setErrorSintactico("break");
    }
    else setErrorSintactico("break");
}
function Def() {
    if (cActual == "d") {
        getPalabra();
        if (pActual == "default") {
            pila.push("P3");
            pila.push(":");
            estados();
        }
        else setErrorSintactico("defuault");
    }
    else if (cActual == "}") estados();
    else setErrorSintactico("defuault");
}
function Val() {
    if (L.includes(cActual) || cActual == "\"" || cActual == "'" || D.includes(cActual)) {
        pila.push("Val2");
        pila.push("E");
        estados();
    }
    else if (cActual == "(") {
        pila.push(")");
        pila.push("Val");
        pila.push("(");
        estados();
    }
    else if (cActual == "!") {
        pila.push("!");
        estados();
    }
    else setErrorSintactico("Id, \", ', Numero, ( o !");
}
function Val2() {
    if (cActual == "&" || cActual == "|" || cActual == "*" || cActual == "/" || cActual == "-" || cActual == "+") {
        pila.push("Val");
        pila.push("O5");
        estados();
    }
    else if (cActual == ":" || cActual == ")") estados();
    else setErrorSintactico(":, ), &&, ||, *, +, - o /");
}
function Fo() {
    if (cActual == "(") {
        pila.push("SeR1");
        pila.push(")");
        pila.push("Inc1");
        pila.push(";");
        pila.push("Con3");
        pila.push(";");
        pila.push("Dec1");
        pila.push("(");
        estados();
    }
    else setErrorSintactico("(");
}
function Dec1() {
    if (L.includes(cActual)) {
        getPalabra();
        if (T.includes(pActual)) {
            pila.push("E");
            pila.push("=");
            pila.push("Id");
            estados();
        }
        else {
            pila.push("Dec2");
            pila.push("E");
            pila.push("=");
            estados();
        }
    }
    else setErrorSintactico("Id, int, string, double, char o bool");
}
function Dec2() {
    if (cActual == ",") {
        pila.push("Dec2");
        pila.push("E");
        pila.push("=");
        pila.push("Id");
        pila.push(",");
        estados();
    }
    else if (cActual == ";" || cActual == "") estados();
    else setErrorSintactico("; o ,");
}
function Con3() {
    if (L.includes(cActual)) {
        pila.push("Con1");
        pila.push("Id");
        estados();
    }
    else if(cActual == "(" || cActual == "!") {
        pila.push("Con1");
        pila.push(cActual);
        estados();
    }
    else if (cActual == ";") {
        pila.push(";");
        estados();
    }
    else setErrorSintactico("Id, (, ! o ;");
}
function Inc1() {
    if (cActual == "+" || cActual == "-") {
        pila.push("Id");
        pila.push("It1");
        estados();
    }
    else if (L.includes(cActual)) {
        pila.push("Inc2");
        estados();
    }
    else if (cActual == ";" || cActual == ")") {
        pila.push(cActual);
        estados();
    }
    else setErrorSintactico("+, -, Id, ; o )");
}
function Inc2() {
    if (L.includes(cActual)) {
        pila.push("Inc3");
        pila.push("It2");
        pila.push("Id");
        estados();
    }
    else setErrorSintactico("Id");
}
function Inc3() {
    if (cActual == ",") {
        pila.push("Inc2");
        pila.push(",");
        estados();
    }
    else if (cActual == ";" || cActual == ")" || cActual == "") {
        pila.push(cActual);
        estados();
    }
    else setErrorSintactico("; o ,");
}
function It1() {
    if (cActual == "+") {
        getCharacter();
        if (cActual == "+") {
            pila.push();
            estados();
        }
        else setErrorSintactico("+");
    }
    else if (cActual == "-") {
        getCharacter();
        if (cActual == "-") {
            pila.push();
            estados();
        }
        else setErrorSintactico("-");
    }
    else setErrorSintactico("++ o --");
}
function It2() {
    if (cActual == "/" || cActual == "*") {
        pila.push("It6");
        pila.push("It5");
        pila.push(cActual);
        estados();
    }
    else if (cActual == "+") {
        pila.push("It3");
        pila.push("+");
        estados();
    }
    else if (cActual == "-") {
        pila.push("It4");
        pila.push("-");
        estados();
    }
    else if (cActual == "=" || cActual == "") {
        pila.push("=");
        estados();
    }
    else setErrorSintactico("+, -, /, * o =");
}
function It3() {
    if (cActual = "+") {
        pila.push("+");
        estados();
    }
    if (cActual = "=") {
        pila.push("It6");
        pila.push("=");
        estados();
    }
    else setErrorSintactico("+ o =");
}
function It4() {
    if (cActual = "-") {
        pila.push("-");
        estados();
    }
    if (cActual = "=") {
        pila.push("It6");
        pila.push("=");
        estados();
    }
    else setErrorSintactico("- o =");
}
function It5() {
    if (cActual = "/" || cActual == "*") {
        pila.push(cActual);
        estados();
    }
    else if (cActual = "=") {
        pila.push("=");
        estados();
    }
    else setErrorSintactico("/, * o =");
}
function It6() {
    if (cActual = "=") {
        pila.push("E");
        pila.push("=");
        estados();
    }
    else setErrorSintactico("=");
}
function SeR1() {
    if (cActual == "{") {
        pila.push("}");
        pila.push("SeR2");
        pila.push("{");
        estados();
    }
    else setErrorSintactico("{");
}
function SeR2() {
    if (cActual == "/" || L.includes(cActual)) {
        pila.push("SeR2");
        pila.push("SeR3");
        estados();
    }
    else if (cActual == "}" || cActual == "") {
        estados();
    }
    else setErrorSintactico("/, }, Id, int, double, string, bool, char, if, for, do, while, continue, break, switch o continue");
}
function SeR3() {
    if (cActual == "/" || L.includes(cActual)) {
        pila.push("P4_2");
        estados();
    }
    else setErrorSintactico("/, }, Id, int, double, string, bool, char, if, for, do, while, continue, break, switch o continue");
}
function Ctn() {
    if (cActual == ";") {
        pila.push(";");
        estados();
    }
    else setErrorSintactico(";");
}
function Wh() {
    if (cActual == "(") {
        pila.push("SeR1");
        pila.push(")");
        pila.push("Con1");
        pila.push("(");
        estados();
    }
    else setErrorSintactico("(");
}
function Dw() {
    if (cActual == "{") {
        pila.push(";");
        pila.push(")");
        pila.push("Con1");
        pila.push("(");
        pila.push("while");
        pila.push("SeR1");
        estados();
    }
    else setErrorSintactico("{");
}
function Im() {
    if (cActual == ".") {
        pila.push(";");
        pila.push(")");
        pila.push("E");
        pila.push("(");
        pila.push("Write");
        pila.push(".");
        estados();
    }
    else setErrorSintactico(".");
}
function R() {
    if (L.includes(cActual)) {
        pila.push(";");
        pila.push("E");
        estados();
    }
    else if (cActual == ";") {
        estados();
    }
    else setErrorSintactico("Id o ;");
}
function Co() {
    if (cActual == "/") {
        pila.push("Co2");
        pila.push("/");
        estados();
    }
    else setErrorSintactico("/");
}
function Co2() {
    if (cActual == "/") {
        pila.push("Col");
        estados();
    }
    else if (cActual == "*") {
        pila.push("Com");
        estados();
    }
    else setErrorSintactico("/");
}
function Col() {
    if (cActual == "/") {
        i_fil++;
        i_col = 0;
        getCharacter();
    }
    else setErrorSintactico("/");
}
function Com() {
    if (cActual == "*") {
        i_col++;
        while (i_fil < txt_linea.length) {
            if (txt_linea[i_fil][i_col] == undefined) {
                i_fil++;
                i_col = 0;
            }
            else if (txt_linea[i_fil][i_col] == "*") {
                i_col++;
                if (txt_linea[i_fil][i_col] == "/") {
                    i_col++;
                    getCharacter();
                    break;
                }
            }
            else i_col++;
        }
    }
    else setErrorSintactico("/");
}
function Ex2() {
    if (cActual == "/" || cActual == "*" || cActual == "-" || cActual == "+") {
        pila.push("It2");
        estados();
    }
    else if (cActual == "(") {
        pila.push("Id2");
        estados();
    }
    else setErrorSintactico("/, *, -, + o (");
}
function E() {
    if (L.includes(cActual) || cActual == "(" || cActual == "\"" || cActual == "'" || D.includes(cActual)) {
        pila.push("Eb");
        pila.push("Ea");
        estados();
    }
    else setErrorSintactico("Id, \", ', Numero o (");
}
function Ea() {
    if (L.includes(cActual)) {
        pila.push("Id2");
        pila.push("Id");
        estados();
    }
    else if (cActual == "(") {
        pila.push(")");
        pila.push("E");
        pila.push("(");
        estados();
    }
    else if (cActual == "/" || cActual == "*" || cActual == "-" || cActual == "+") {
        pila.push("E");
        estados();
    }
    else if (cActual == "\"") {
        i_col++;
        while (i_fil < txt_linea.length) {
            if (txt_linea[i_fil][i_col] == undefined) {
                i_fil++;
                i_col = 0;
            }
            else if (txt_linea[i_fil][i_col] == "\"") {
                i_col++;
                getCharacter();
                break;
            }
            else i_col++;
        }
    }
    else if (cActual == "'") {
        i_col++;
        while (i_fil < txt_linea.length) {
            if (txt_linea[i_fil][i_col] == undefined) {
                i_fil++;
                i_col = 0;
            }
            else if (txt_linea[i_fil][i_col] == "'") {
                i_col++;
                getCharacter();
                break;
            }
            else i_col++;
        }
    }
    else if (D.includes(cActual)) {
        i_col++;
        while (i_fil < txt_linea.length && D.includes(txt_linea[i_fil][i_col])) {
            if (txt_linea[i_fil][i_col] == undefined) {
                i_fil++;
                i_col = 0;
                break;
            }
            else if (txt_linea[i_fil][i_col] == ".") {
                i_col++;
                if (D.includes(txt_linea[i_fil][i_col])) {
                    while (i_fil < txt_linea.length && D.includes(txt_linea[i_fil][i_col])) {
                        if (txt_linea[i_fil][i_col] == undefined) {
                            i_fil++;
                            i_col = 0;
                            break;
                        }
                        else i_col++;
                    }
                    break;
                }
                else setErrorSintactico("Numero");
                break;
            }
            else i_col++;
        }
    }
    else setErrorSintactico("Id, \", ', Numero o (");
}
function Eb() {
    if (cActual == "/" || cActual == "*" || cActual == "-" || cActual == "+") {
        pila.push("E");
        pila.push(cActual);
        estados();
    }
    else if (cActual == "," || cActual == ";" || cActual == ")") {
        estados();
    }
    else if (cActual == ">" || cActual == "<") {
        if (txt_linea[i_fil][i_col] == "=") getCharacter();
        getCharacter();
        estados();
    }
    else if (cActual == "&" || cActual == "|") {
        if (txt_linea[i_fil][i_col] == cActual) getCharacter();
        getCharacter();
        estados();
    }
    else setErrorSintactico("/, *, +, -, ;, ), <, <=, >, >=, &&, || o ,");
}
function Id2() {
    if (cActual == "(") {
        pila.push(")");
        pila.push("E2");
        estados();
    }
    else if (cActual == "," || cActual == ";") {
        estados();
    }
    else if (cActual == ">" || cActual == "<") {
        if (txt_linea[i_fil][i_col] == "=") getCharacter();
        getCharacter();
        estados();
    }
    else if (cActual == "&" || cActual == "|") {
        if (txt_linea[i_fil][i_col] == cActual) getCharacter();
        getCharacter();
        estados();
    }
    else setErrorSintactico("(, ;, <, <=, >, >=, &&, || o ,");
}
function E2() {
    if (cActual == "(" || cActual == "\"" || cActual == "'" || D.includes(cActual)) {
        pila.push("E3");
        pila.push("E");
        estados();
    }
    else if (cActual == "T") {
        getPalabra();
        if (pActual == "True") {
            estados();
        }
        else setErrorSintactico("True");
    }
    else if (cActual == "F") {
        getPalabra();
        if (pActual == "False") {
            estados();
        }
        else setErrorSintactico("False");
    }
    else if (cActual == ")") {
        estados();
    }
    else setErrorSintactico("(, ), \", ', Numero, True o False");
}
function E3() {
    if (cActual == ",") {
        pila.push("E3");
        pila.push("E");
        estados();
    }
    else if (cActual == ")") {
        estados();
    }
    else setErrorSintactico(") o ,");
}


function getCharacter() {
    cActual = "";
    while (txt_linea[i_fil][i_col] == undefined || txt_linea[i_fil][i_col] == " ") {
        i_col++;
        if (txt_linea[i_fil][i_col] == undefined) {
            i_col = 0;
            i_fil++;
        }
    }
    if (txt_linea.length <= i_fil) analizando = false;
    else cActual = txt_linea[i_fil][i_col];
    i_col++;
}
function getPalabra() {
    pActual = "";
    while (cActual != undefined && cSalida.includes(cActual) && txt_linea <= i_fil) {
        pActual += cActual;
        cActual = txt_linea[i_fil][i_col];
        i_col++;
    }
    getCharacter();
}

function Panico() {
    while (cActual != ";" || cActual != "}") {
        getCharacter();
        if (txt_linea.length <= i_fil) break;
    }
}
//ERRORES---------------------------------------------------------------------------
function setErrorLexico() {
    setError("Lexico", "El caracter " + cActual + " no pertenece al lenguaje");
}
function setErrorSintactico(esp) {
    setError("Sintactico", "Se esperaba " + esp + " (Se encontro " + pActual + ")");
    Panico();
}
function setError(tip, des) {
    repErrores += "<tr><th>" + contErrores + "</th>";
    repErrores += "<th>" + tip + "</th><th>" + (i_col + 1) + "</th><th>" + (i_fil + 1) + "</th>";
    repErrores += "<th>" + des + "</th></tr>\n";
    contErrores++;
}

//EXTRAS----------------------------------------------------------------------------
//TAB
function getTab(cont) {
    var tab = "";
    for (var i = 0; i < cont; i++) tab += '\t';
    return tab;
}
//STRING DE DATOS DE SALIDA --------------------------------------------------------
function ingresarDatos() {
    document.getElementById("txt_Salida").textContent = txt_phyton;
    document.getElementById("txt_HTML").textContent = txt_html;
    document.getElementById("txt_JAVA").textContent = txt_json;
}

//INICIALIZACION -------------------------------------------------------------------
function inicializar() {
    txt = document.getElementById("txt_" + pestAct).value + " $";
    txt_linea = txt.split('\n');

    tabla = [];
    tablaCont = 0;

    T = new Array(5);
    T[0] = "int";
    T[1] = "double";
    T[2] = "bool";
    T[3] = "char";
    T[4] = "string";

    cSalida = new Array(15);
    cSalida[0] = " ";
    cSalida[1] = "(";
    cSalida[2] = ")";
    cSalida[3] = "{";
    cSalida[4] = "}";
    cSalida[5] = ";";
    cSalida[6] = ":";
    cSalida[7] = ",";
    cSalida[8] = "+";
    cSalida[9] = "-";
    cSalida[10] = "/";
    cSalida[11] = "*";
    cSalida[12] = "=";
    cSalida[13] = "!";
    cSalida[14] = ".";

    pila = [];
    pila.push("$");

    L = ["A" - "z"];
    D = [0 - 9];

    i_col = i_fil = 0;

    analizando = true;

    repErrores = "<table>\n<tr><th>No.</th><th>Tipo error</th><th>Columna</th><th>Fila</th><th>Descripcion</th></tr>\n";
    contErrores = 1;
}

//FINALIZACION----------------------------------------------------------------------
function finalizar() {
    repErrores += "</table>";
}