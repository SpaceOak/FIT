var context_calculator = SAGE2_App.extend({

    init: function (data) {
        // Vytváříme "div" HTML uzel
        this.SAGE2Init("div", data);
        // Nastavuje jeho id
        this.element.id = "calkulator example";
        // Obarvíme pozadi
        this.element.style.background = "white";
        // Voláme funkce, která inicializuje základní parametry
        this.clearAll();
    },

    draw: function (date) {
        // Zapisuje do kontejneru "div" kontent pomoci parametru "this.element.innerHTML" v závislosti na parametru "this.status"
        if (this.status == "numbers")
            this.element.innerHTML = "Enter two numbers.";
        else if (this.status == "operation")
            this.element.innerHTML = this.number_1 + " | " + this.number_2 + "<br>Select operation.";
        else if (this.status == "result")
            this.element.innerHTML = this.number_1 + " | " + this.number_2 + "<br>" + this.operator + "<br>" + this.result;
    },

    getContextEntries: function () {
        // Funkce zaručuje použití kontextového menu.
        // Seznam vstupů, který musí funkce vrátit. Do tohoto seznamu mohou být uloženy tlačítka, textové vstupy a separatory.
        var entries = [];
        // Ukládame separator (horizontalní čáru mezi vstupy). 
        var separator = { description: "separator" };
    
        if (this.status == "numbers") {
            /*
             * Přidame vstupní textové pole do contextového menu.
             * 
             * description - co bude napsáno uvnítř.
             * callback - nazev funkce, která bude zavolaná po stisknutí tlačítka "OK".
             * parameters - parametry, které budou předány funkci v callbacku.
             * inputField - pukud true, udělá vstupní textové pole.
             * inputFieldSize - maximalní počet symbolů
             */ 
            entries.push({
                description: "Number1 Number2",
                callback: "saveNums",
                parameters: {},
                inputField: true,
                inputFieldSize: 20
            });
        }
        else if (this.status == "operation") {
            // Přidame tlačítko do contextového menu
            entries.push({
                description: "+",
                callback: "setOperation",
                parameters: {
                    operator: "+"
                }
            });
            // Přidame separator do contextového menu
            entries.push(separator);

            entries.push({
                description: "-",
                callback: "setOperation",
                parameters: {
                    operator: "-"
                }
            });

            entries.push(separator);
            
            entries.push({
                description: "x",
                callback: "setOperation",
                parameters: {
                    operator: "x"
                }
            });
            
            entries.push(separator);
            
            entries.push({
                description: "/",
                callback: "setOperation",
                parameters: {
                    operator: "/"
                }
            });
        }
        else if (this.status == "result") {
            entries.push({
                description: "Clear",
                entryColor: "lightred",
                callback: "clearAll",
                parameters: {}
            });
        }
    
        return entries;
    },

    saveNums: function (responseObject) {
        // Callback funkce. Pokud uživatel napišé dvá čisla, funkce uloží je a přepné stav.
        // Uživatelský vstup lze nalezt uvnitř parametru "responseObgect.clientInput". 
        var numArray = responseObject.clientInput.split(" ");
        if (numArray.length == 2 && Number(numArray[0]) != NaN && Number(numArray[1]) != NaN) {
            this.number_1 = Number(numArray[0]);
            this.number_2 = Number(numArray[1]);
            this.status = "operation";
            // Po volání funkce aktualizuje contextové menu(znovu zavolá "getContextEntries()")
            this.getFullContextMenuAndUpdate();
        }
    },

    setOperation: function (responseObject) {
        // V yávislosti na parametru "responseObject.operator" zavolá určitou operaci a uloží vysledek
        if (responseObject.operator == "+") {
            this.result = this.number_1 + this.number_2;
            this.operator = "+";
        }
        else if (responseObject.operator == "-") {
            this.result = this.number_1 - this.number_2;
            this.operator = "-";
        }
        else if (responseObject.operator == "x") {
            this.result = this.number_1 * this.number_2;
            this.operator = "x";
        }
        else if (responseObject.operator == "/") {
            this.result = this.number_1 / this.number_2;
            this.operator = "/";
        }

        this.status = "result";
        this.getFullContextMenuAndUpdate();
    },

    clearAll: function () {
        // Nastaví všechny parametry do počatečného stavu
        this.status = "numbers";
        this.number_1 = 0;
        this.number_2 = 0;
        this.result = 0;
        this.operator = "";

        this.getFullContextMenuAndUpdate();
    }
});