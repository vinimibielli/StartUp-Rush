//função responsável por fazer o envio da requisição POST para o backend
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

//função responsável por enviar os dados do cadastro para o backend em conjunto com a função executarPost
function cadastrarStartUp(event){
    event.preventDefault();

    let url = "/add_startup";

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
            alert(data.message);
        }
    });
}

//função responsável por enviar os dados de remoção para o backend em conjunto com a função executarPost
function deletarStartUp(event){
    event.preventDefault();

    let url = "/remove_startup";

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
            alert(data.message);
        }
    });
}

//função responsável por enviar os dados para validar o início das batalhas (manual) para o backend em conjunto com a função executarPost
function checkBattlesStart(event) {
    event.preventDefault();

    let url = "/start_battle";

    let method = 'POST';

    executarPost(url, "", method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            window.location.href = data.next;
        } else {
            alert(data.message);
        }
    });
}

//função responsável por enviar os dados para validar o início das batalhas (automático) para o backend em conjunto com a função executarPost
function checkBattlesStartAuto(event) {
    event.preventDefault();

    let url = "/auto_battle";

    let method = 'POST';

    executarPost(url, "", method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            window.location.href = data.next;
        } else {
            alert(data.message);
        }
    });
}

//função responsável por enviar os dados para reiniciar a competição para o backend em conjunto com a função executarPost
function restartStartUp(event) {
    event.preventDefault();

    let url = "/restart_startup";

    let method = 'POST';

    executarPost(url, "", method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            window.location.href = data.next;
        } else {
            alert(data.message);
        }
    });
}

//função responsável por enviar os dados para determinar os eventos das startups para o backend em conjunto com a função executarPost
function setTargets(event, id, battleId, eventId, nameA, nameB){
    event.preventDefault();

    let url = `/battle/${battleId}/events/${eventId}/target`;

    let body = {
        "name": id
    };

    let method = 'POST';

    executarPost(url, body, method, function(responseText) {
        let data = JSON.parse(responseText);
        if (data.next) {
            let next_page = data.next + '?battleID=' + battleId + "&nameA=" + nameA + '&nameB=' + nameB;
            window.location.href = next_page;
        } else {
            alert(data.message);
        }
    });
}

//função responsável por enviar os dados para verificar a finalização das batalhas para o backend em conjunto com a função executarPost
function checkFinalize(event, battleId) {
    event.preventDefault();

    let url = `/battle/${battleId}/finalize`;

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
            