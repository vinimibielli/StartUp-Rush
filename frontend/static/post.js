function executarPost(url, body, method, callback) {
    console.log("Body=", body);

    let request = new XMLHttpRequest();
    request.open(method, url, true);

    request.setRequestHeader("Content-Type", "application/json");
    request.send(JSON.stringify(body));

    request.onload = function () {
        console.log("Resposta:", this.responseText);
        if (callback) {
            callback(this.responseText);
        }
    };
}

function cadastrarStartUp(event){
    event.preventDefault();

    let url = "http://127.0.0.1:8080/add_startup";

    let name = document.getElementById("name").value;
    let slogan = document.getElementById("slogan").value;
    let foundation = parseInt(document.getElementById("foundation").value);

    console.log(name);
    console.log(slogan);
    console.log(foundation);

    let body = {
        "name": name,
        "slogan": slogan,
        "foundation": foundation
    };

    let method = 'POST';

    executarPost(url, body, method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            window.location.href = data.next;
        } else {
            alert("StartUp cadastrada, mas sem redirecionamento!");
        }
    });
}

function deletarStartUp(event){
    event.preventDefault();

    let url = "http://127.0.0.1:8080/remove_startup";

    let name = document.getElementById("name").value;

    let body = {
        "name": name
    };

    let method = 'DELETE';

    executarPost(url, body, method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            window.location.href = data.next;
        } else {
            alert("StartUp removida, mas sem redirecionamento!");
        }
    });
}

function checkBattlesStart(event) {
    event.preventDefault();

    let url = "http://127.0.0.1:8080/start_battle";

    let method = 'POST';

    executarPost(url, "", method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            window.location.href = data.next;
        } else {
            alert("Insira um número válido de StartUps!");
        }
    });
}

function setTargets(event, id, battleId, eventId){
    event.preventDefault();

    let url = `http://127.0.0.1:8080/battle/${battleId}/events/${eventId}/target`;

    let body = {
        "name": id
    };

    let method = 'POST';

    executarPost(url, body, method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            let next_page = data.next + '?battleID=' + battleId;
            window.location.href = next_page;
        } else {
            alert("StartUp removida, mas sem redirecionamento!");
        }
    });
}

function checkFinalize(event, battleId) {
    event.preventDefault();

    let url = `http://127.0.0.1:8080/battle/${battleId}/finalize`;

    let method = 'POST';

    executarPost(url, "", method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            window.location.href = data.next;
        } else {
            alert("Erro na finalização");
        }
    });
}
            