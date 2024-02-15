//------- WRITE FILE -------

function writeFile(id_form, func) {
    var element = document.createElement('a');

    let text1 = document.getElementById(id_form);
    let count = text1.elements.length;
    let textToSave = func;
    for (let i = 0; i < count - 1; i++) {
        textToSave += ";" + text1[i].value;
    }

    element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(textToSave));
    element.setAttribute('download', 'request.txt');

    element.style.display = 'none';
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);
    text1.submit();
}
// -------------------------

function ShutDown(){
    var element1 = document.createElement('a');

    element1.setAttribute('href', 'data:text/plain;charset=utf-8,');
    element1.setAttribute('download', 'shutdown.txt');

    element1.style.display = 'none';
    document.body.appendChild(element1);
    element1.click();
    document.body.removeChild(element1);
}
//-------Mes a jour l'option choisie----------------

function getSelectedOption() {
    // Récupérer l'élément select
    var selectOptions = document.getElementById("selectOptions");
    // Récupérer la valeur de l'option sélectionnée
    var optionValue = selectOptions.options[selectOptions.selectedIndex].value;
    // Retourner la valeur de l'option
    return optionValue;
}

//--------------------------------------


// ------- READ FILE -------
function readFileByName(fileName){

    let xhr = new XMLHttpRequest();
    do {
        xhr.open("GET", fileName, false);
        xhr.send(null);

    }while(xhr.status === 404);
    // assumes status 200
    return xhr.responseText;
}
function readFile() {
    readFileByName("ready.txt");
    var fileContent = readFileByName("result.txt");
    var lines = fileContent.split("\n");
    var results = [];

    for (var i = 0; i < lines.length; i++) {
        var data = lines[i].split(";"); // Assurez-vous que le séparateur correspond à celui utilisé dans le fichier
        if (data.length === 4) { // Vérifiez que chaque ligne a le bon nombre de colonnes
            var result = {
                realisateur: data[0],
                film: data[1],
                duree: data[2],
                genre: data[3]
            };
            results.push(result);
        }
        else{
            if(data.length === 2){
                let temps = data[0];
                document.getElementById("temps").textContent="Temps de recherche " + temps + "s";
            }else{
                if(data.length === 3){
                    let nom = data[0];
                    let nombre = data[1];
                    document.getElementById("directeurMax").textContent="Plus Grand Réalisateur : "+nom+" avec "+nombre+" Films";
                }
            }
        }
    }
    displayResults(results); // Ajoutez cet appel pour afficher les résultats dans le tableau
    return results;
}
// -------------------------
// Variables pour la pagination
var allData = [];
var currentPage = 1; // Page actuelle affichée
var rowsPerPage = 20; // Nombre de lignes par page;
function displayResults(results) {
    allData = results; // Stocke toutes les données du fichier
    currentPage = 1; // Réinitialise la page actuelle à 1
    rowsPerPage = 20; // Nombre de lignes par page;
    showDataInTable(); // Affiche les données dans le tableau
}
function showDataInTable() { //Fonction en partie écrite par ChatGPT
    var startIndex = (currentPage - 1) * rowsPerPage; // Index de départ pour la page
    var endIndex = startIndex + rowsPerPage; // Index de fin pour la page
    var pageData = allData.slice(startIndex, endIndex); // Données de la page
    var tableBody = document.getElementById("resultsTableBody");
    tableBody.innerHTML = ""; // Efface le contenu existant du tableau

    for (var i = 0; i < pageData.length; i++) {
        var row = document.createElement("tr");
        var result = pageData[i];
        var realisateurCell = document.createElement("td");
        realisateurCell.textContent = result.realisateur;
        row.appendChild(realisateurCell);

        var filmCell = document.createElement("td");
        filmCell.textContent = result.film;
        row.appendChild(filmCell);

        var dureeCell = document.createElement("td");
        dureeCell.textContent = result.duree;
        row.appendChild(dureeCell);

        var genreCell = document.createElement("td");
        genreCell.textContent = result.genre;
        row.appendChild(genreCell);
        tableBody.appendChild(row);
    }
    updatePagination(); // Met à jour les boutons de pagination
}

// Fonction pour mettre à jour la pagination
function updatePagination() { //Fonction en partie écrite par ChatGPT
    var totalPages = Math.ceil(allData.length / rowsPerPage); // Calculer le nombre total de pages
    var prevButton = document.getElementById('prevPage');
    var nextButton = document.getElementById('nextPage');
    var firstButton = document.getElementById('firstPage');
    var lastButton = document.getElementById('lastPage');
    var currentPageSpan = document.getElementById('currentPage');
    // Désactiver le bouton "Page précédente" si nous sommes sur la première page
    if (currentPage === 1) {
        prevButton.disabled = true;
        firstButton.disabled = true;
    } else {
        prevButton.disabled = false;
        firstButton.disabled = false;
    }

    // Désactive le bouton "Page suivante" si nous sommes sur la dernière page
    if (currentPage === totalPages) {
        nextButton.disabled = true;
        lastButton.disabled = true;
    } else {
        nextButton.disabled = false;
        lastButton.disabled = false;
    }

    currentPageSpan.textContent = "Page " + currentPage + " sur " + totalPages;
}

document.getElementById('firstPage').addEventListener('click', function() {
    if (currentPage > 1) {
        currentPage = 1;
        showDataInTable();
    }
});

// Gestionnaire d'événement pour le bouton "Page précédente"
document.getElementById('prevPage').addEventListener('click', function() {
    if (currentPage > 1) {
        currentPage--;
        showDataInTable(); // Afficher la page précédente
    }
});

// Gestionnaire d'événement pour le bouton "Page suivante"
document.getElementById('nextPage').addEventListener('click', function() {
    var totalPages = Math.ceil(allData.length / rowsPerPage); // Calculer le nombre total de pages
    console.log(rowsPerPage);
    if (currentPage < totalPages) {
        currentPage++;
        showDataInTable(); // Afficher la page suivante
    }
});

document.getElementById('lastPage').addEventListener('click', function() {
    var totalPages = Math.ceil(allData.length / rowsPerPage);

    if (currentPage < totalPages) {
        currentPage = totalPages;
        showDataInTable();
    }
});
