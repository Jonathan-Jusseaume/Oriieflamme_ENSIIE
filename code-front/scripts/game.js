const game = new WebSocket('ws://localhost:8080');

let plateau = {};
let attente_autre_joueur = true;
let demander_utilisateur_repioche = false;
let demander_utilisateur_poser_carte = false;
let resultat;

// La connexion est ouverte
game.addEventListener('open', function (event) {

});

// Écouter les messages
game.addEventListener('message', function (event) {
    lireMessage(event.data);
});


function envoyerCarteEtPositionAPoser(abscisse, ordonnee) {
    if (previousCarteSelectedNumber !== null) {
        game.send(sessionStorage.getItem("ID") + ";" + (previousCarteSelectedNumber + 1) + ";" + abscisse + ";" + ordonnee);
    }
}

function envoyerDemandeRepioche(veutRemelanger) {
    game.send(sessionStorage.getItem("ID") + ";" + (veutRemelanger ? 1 : 0));
    document.getElementById('actions').innerHTML = '';
}

// Fonction lisant le message et faisant en sorte de toujours avoir les bonnes informations sur la partie
function lireMessage(message) {
    // Premier message envoyé par le serveur, l'identifiant de notre faction
    if (message.includes("ID")) {
        // On le stocke dans le sessionStorage
        sessionStorage.setItem("ID", message.split(":")[1]);
        // activer l'écran d'attente
        document.getElementsByClassName("attente-connexion")[0].classList.remove("hidden"); // Si on met un id, il prend le dessus sur la classe, et hidden ne fonctionnera pas
    }
    // Si on nous envoie le plateau de jeu, alors il faut mettre à jour notre copie
    if (message.includes("PLATEAU")) {
        document.getElementsByClassName("attente-connexion")[0].classList.add("hidden");
        // On récupère uniquement les infos, indice 0 -> grille, indice 1 -> faction 1, indice 2 -> faction 2
        const infos = (message.split("\n")).slice(1);
        const splitInfosGrille = infos[0].split("/")[0].split(',');
        plateau['grille'] = {
            minX: parseInt(splitInfosGrille[0]),
            minY: parseInt(splitInfosGrille[1]),
            maxX: parseInt(splitInfosGrille[2]),
            maxY: parseInt(splitInfosGrille[3]),
            contenu: parseGrille(infos[0].split("/")[1])
        };
        plateau['factions'] = [];
        plateau['factions'].push(parseFaction(infos[1]));
        plateau['factions'].push(parseFaction(infos[2]));
        // lancer mise à jour de la grille
        addMain(plateau.factions[parseInt(sessionStorage.getItem("ID"))].main);
        MAJScoreEtManche(plateau);
        afficherPlateau(plateau, false);
        document.getElementsByClassName("attente-pose-carte")[0].innerHTML = "Veuillez attendre que l'adversaire pose une carte...";
        document.getElementsByClassName("attente-pose-carte")[0].classList.remove("hidden"); // Si on met un id, il prend le dessus sur la classe, et hidden ne fonctionnera pas

    }
    if (message.includes("PIOCHE")) {
        demander_utilisateur_repioche = true;
        // faire apparaitre le bouton pour demander à l'utilisateur de piocher
        document.getElementById('actions').innerHTML =
            "<button id='bouton-garder-pioche' class='boutons-pioche-clignote' onclick='envoyerDemandeRepioche(false)'>GARDER</button>" +
            "<button id='bouton-repiocher' class='boutons-pioche-clignote' onclick='envoyerDemandeRepioche(true)'>MELANGER</button>";
    }
    if (message.includes("POSE")) {
        document.getElementsByClassName("attente-pose-carte")[0].classList.add("hidden"); // Si on met un id, il prend le dessus sur la classe, et hidden ne fonctionnera pas
        demander_utilisateur_poser_carte = true;
        // demander à un utilisateur de poser une carte
        document.getElementsByClassName("attente-pose-carte")[0].innerHTML = "Veuillez poser une carte de votre main...";
        document.getElementsByClassName("attente-pose-carte")[0].classList.remove("hidden"); // Si on met un id, il prend le dessus sur la classe, et hidden ne fonctionnera pas
        afficherPlateau(plateau, true);
    }
    if (message.includes("RESULTAT")) {
        resultat = parseInt(message.split(":")[1]);
        if (resultat !== -1) {
            document.getElementById('result').innerHTML = (resultat === sessionStorage.getItem('ID')) ? 'VICTOIRE' : 'DÉFAITE';
        }


    }
}

function parseCarte(carteString) {
    let carte = {};
    const tableau = carteString.split(",");
    carte["nom"] = tableau[0];
    carte["position"] = {abscisse: parseInt(tableau[1]), ordonnee: parseInt(tableau[2])};
    carte["identifiantFaction"] = tableau[3];
    carte["numeroPlateau"] = tableau[4];
    carte["estFaceCachee"] = parseInt(tableau[5]) === 1;
    return carte;
}

function parseGrille(grilleString) {
    const tableau = [];
    if (grilleString !== '') {
        const lignes = grilleString.split('|');
        lignes.forEach((ligne, indice) => {
            tableau.push([]);
            const colonnes = ligne.split(';');
            colonnes.forEach(colonne => {
                if (colonne !== '') {
                    tableau[indice].push(parseCarte(colonne));
                } else {
                    tableau[indice].push(null);
                }
            })
        })
    }

    return tableau;
}

function parseFaction(factionString) {
    let faction = {};
    const tableau = factionString.split("|");
    faction["identifiant"] = tableau[0];
    faction["nom"] = tableau[1];
    faction["aRemelanger"] = parseInt(tableau[2]) === 1;
    faction["pointsDDRS"] = tableau[3];
    faction["manchesGagnees"] = tableau[4];
    faction["main"] = [];
    const main = tableau[5].split(";");
    if (tableau[5] !== "") {
        main.forEach(carteString => {
            faction["main"].push(parseCarte(carteString))
        });
    }
    return faction;
}

// TODO : (echec) Faire disparaitre la séléction d'une carte au clic autre part sur la page

let previousCarteSelectedNumber = null;

function rightClick(event, number) {
    if (event.button === 2) {
        console.log(document.getElementsByClassName("gradient-border")[number]);
        document.getElementById('footer').getElementsByClassName("gradient-border")[number].classList.add("zoom-zoom");
        console.log(document.getElementsByClassName("gradient-border")[number]);
    }
}

function leftClick(currentCarteNumber) {
    if (previousCarteSelectedNumber === null) {
        document.getElementById('footer').getElementsByClassName("gradient-border")[currentCarteNumber].classList.add("carte-select");
        previousCarteSelectedNumber = currentCarteNumber;
    } else {
        document.getElementById('footer').getElementsByClassName("gradient-border")[previousCarteSelectedNumber].classList.remove("carte-select");
        document.getElementById('footer').getElementsByClassName("gradient-border")[currentCarteNumber].classList.add("carte-select");
        previousCarteSelectedNumber = currentCarteNumber;
    }
}

function rightUp(number) {
    document.getElementById('footer').getElementsByClassName("gradient-border")[number].classList.remove("zoom-zoom");
}

document.addEventListener('click', (e) => {
    let carteSelectionnee = document.getElementsByClassName("carte-select")[0];
    if (carteSelectionnee !== undefined) {
        // Une carte est bel et bien séléctionnée
        if (e.target.className !== document.getElementsByClassName("gradient-border")[0].className &&
            e.target.className !== document.getElementsByClassName("carte-creation")[0].className &&
            e.target.className !== document.getElementsByClassName("back")[0].className &&
            e.target.className !== document.getElementsByClassName("carte-creation")[0].className &&
            e.target.className !== document.getElementsByClassName("contenu-carte")[0].className &&
            e.target.className !== document.getElementsByClassName("carte-title")[0].className &&
            e.target.className !== document.getElementsByClassName("carte-img-face-visible")[0].className &&
            e.target.className !== document.getElementsByClassName("carte-description")[0].className) {
            // Si on ne clique pas sur une carte, alors la carte séléctionnée est délésectionnée
            carteSelectionnee.classList.remove('carte-select');
        }
    }
});

function carteTemplate(carte, indice = null) {
    let resultatHTML = "";
    if (indice === null) {
        if (carte.estFaceCachee) {
            resultatHTML +=
                '<div class="gradient-border">' +
                '<div  class="carte-creation carte-creation-face-cachee">' +
                '<div class="carte-img-face-cachee"> <img alt="logo-ensiie" src="' + "img/logo-ensiie.png" + '"></div>' +
                '</div>' +
                '</div>';
        } else { // Les cartes sur le plateau
            resultatHTML +=
                '<div class="gradient-border">' +
                '<div  class="carte-creation">' +
                '<div class="back">' +
                '<div class="carte-title">' + carte.nom + '</div>' +
                '<div class="carte-img-face-visible"> <img alt="image-carte" src="' + getImageByCardName(carte.nom) + '""></div>' +
                '<div class="contenu-carte">' +
                '<div class="carte-description">' + getDescriptionByCardName(carte.nom) + '</div>' +
                '</div>' +
                '</div>' +
                '</div>' +
                '</div>';
        }
    } else {
        resultatHTML +=
            '<div class="gradient-border" onclick="leftClick(' + indice + ')" oncontextmenu="event.preventDefault(); return false;" onmousedown="rightClick(event,' + indice + ')" ' +
            'onmouseup="rightUp(' + indice + ')">' +
            '<div  class="carte-creation">' +
            '<div class="back">' +
            '<div class="carte-title">' + carte.nom + '</div>' +
            '<div class="carte-img-face-visible"> <img alt="image-carte" src="' + getImageByCardName(carte.nom) + '""></div>' +
            '<div class="contenu-carte">' +
            '<div class="carte-description">' + getDescriptionByCardName(carte.nom) +
            '</div>' +
            '</div>' +
            '</div>' +
            '</div>' +
            '</div>';
    }
    return resultatHTML;
}

function afficherPlateau(plateau, estCliquable) {
    previousCarteSelectedNumber = null;
    if (plateau.grille.contenu.length && plateau.grille.contenu[0]?.length) {
        const nombreLignes = plateau.grille.contenu.length + 2;
        const nombreColonnes = plateau.grille.contenu[0].length + 2;
        document.getElementById('plateau').setAttribute('style', 'grid-template-columns:' + 'repeat(' + nombreColonnes + ',194px);' + 'grid-template-rows: ' + 'repeat(' + nombreLignes + ',' + '266px);');
        let grilleHTML = "";
        // On ajoute une ligne en haut
        for (let i = -1; i < nombreColonnes - 1; i++) {
            grilleHTML += templateCaseVide(grilleHTML, {
                abscisse: plateau.grille.minX + i,
                ordonnee: plateau.grille.minY - 1
            }, estCliquable);
        }
        plateau.grille.contenu.forEach((colonne, indice) => {
            grilleHTML += templateCaseVide(grilleHTML, {
                abscisse: plateau.grille.minX - 1,
                ordonnee: plateau.grille.minY + indice
            }, estCliquable);


            colonne.forEach((carte, indexX) => {
                if (carte == null) {
                    grilleHTML += templateCaseVide(grilleHTML, {
                        abscisse: plateau.grille.minX + indexX,
                        ordonnee: plateau.grille.minY + indice
                    }, estCliquable);
                } else {
                    grilleHTML += carteTemplate(carte);
                }
            })


            grilleHTML += templateCaseVide(grilleHTML, {
                abscisse: plateau.grille.maxX + 1,
                ordonnee: plateau.grille.minY + indice
            }, estCliquable);
        });

        // On ajoute une ligne en bas
        for (let i = -1; i < nombreColonnes - 1; i++) {
            grilleHTML += templateCaseVide(grilleHTML, {
                abscisse: plateau.grille.minX + i,
                ordonnee: plateau.grille.maxY + 1
            }, estCliquable);
        }

        document.getElementById('plateau').innerHTML = grilleHTML;
    } else {
        document.getElementById('plateau').setAttribute('style', 'grid-template-columns:' + 'repeat(' + 1 + ',194px);' + 'grid-template-rows: ' + 'repeat(' + 1 + ',' + '266px);');
        let grilleHTML = ""
        if (estCliquable) {
            grilleHTML = "<button class='pose-carte' onclick='envoyerCarteEtPositionAPoser( " + 15 + "," + 15 + ")'></button>";
        }
        document.getElementById('plateau').innerHTML = grilleHTML;
    }
}

function addMain(main) {
    let resultatHTML = "";
    main.forEach((element, indice) => {
        resultatHTML += carteTemplate(element, indice);
    })
    document.getElementsByTagName("footer")[0].innerHTML = resultatHTML;
}

function MAJScoreEtManche(plateau) {
    let scoreFaction1 = parseInt(plateau.factions[parseInt(sessionStorage.getItem("ID"))].pointsDDRS);
    let scoreFaction2 = parseInt(plateau.factions[(parseInt(sessionStorage.getItem("ID")) + 1) % 2].pointsDDRS);
    let nombreManchesGagneesFaction1 = parseInt(plateau.factions[parseInt(sessionStorage.getItem("ID"))].manchesGagnees);
    let nombreManchesGagneesFaction2 = parseInt(plateau.factions[(parseInt(sessionStorage.getItem("ID")) + 1) % 2].manchesGagnees);
    let numeroMancheCourante = parseInt(plateau.factions[parseInt(sessionStorage.getItem("ID"))].manchesGagnees) + parseInt(plateau.factions[(parseInt(sessionStorage.getItem("ID")) + 1) % 2].manchesGagnees) + 1;
    document.getElementById("scoreFaction1").innerHTML = scoreFaction1.toString();
    document.getElementById("scoreFaction2").innerHTML = scoreFaction2.toString();
    document.getElementById("nombre-manche-gagnees-faction1").innerHTML = nombreManchesGagneesFaction1.toString();
    document.getElementById("nombre-manche-gagnees-faction2").innerHTML = nombreManchesGagneesFaction2.toString();
    if (numeroMancheCourante < 4) {
        document.getElementById("manche-courante").innerHTML = numeroMancheCourante.toString();
    }
}


function templateCaseVide(grille, position, estCliquable) {
    if (estCliquable && ACarteACote(plateau.grille.contenu, position)) {
        return "<button class='pose-carte' onclick='envoyerCarteEtPositionAPoser( " + position.abscisse + "," + position.ordonnee + ")'></button>";
    } else {
        return "<div class='empty'></div>";
    }
}

function ACarteACote(grille, position) {
    for (let i = 0; i < grille.length; i++) {
        for (let j = 0; j < grille[i].length; j++) {
            if (grille[i][j] != null) {
                const carte = grille[i][j];
                if ((carte.position.abscisse - 1 === position.abscisse && carte.position.ordonnee === position.ordonnee)
                    || (carte.position.abscisse + 1 === position.abscisse && carte.position.ordonnee === position.ordonnee)
                    || (carte.position.abscisse === position.abscisse && carte.position.ordonnee + 1 === position.ordonnee)
                    || (carte.position.abscisse === position.abscisse && carte.position.ordonnee - 1 === position.ordonnee)) {
                    return true;
                }
            }
        }
    }

    return false;
}