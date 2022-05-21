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


function envoyerCarteEtPositionAPoser(indiceCarte, abscisse, ordonnee) {
    game.send(sessionStorage.getItem("ID") + ";" + indiceCarte + ";" + abscisse + ";" + ordonnee);
}

function envoyerDemandeRepioche(veutRemelanger) {
    game.send(sessionStorage.getItem("ID") + ";" + (veutRemelanger ? 1 : 0));
}

// Fonction lisant le message et faisant en sorte de toujours avoir les bonnes informations sur la partie
function lireMessage(message) {
    // Premier message envoyé par le serveur, l'identifiant de notre faction
    if (message.includes("ID")) {
        // On le stocke dans le sessionStorage
        sessionStorage.setItem("ID", message.split(":")[1]);
        // activer l'écran d'attente
    }
    // Si on nous envoie le plateau de jeu, alors il faut mettre à jour notre copie
    if (message.includes("PLATEAU")) {
        // On récupère uniquement les infos, indice 0 -> grille, indice 1 -> faction 1, indice 2 -> faction 2
        const infos = (message.split("\n")).slice(1);

        plateau['grille'] = parseGrille(infos[0]);
        plateau['factions'] = [];
        plateau['factions'].push(parseFaction(infos[1]));
        plateau['factions'].push(parseFaction(infos[2]));
        console.log(plateau);
        // lancer mise à jour de la grille
    }
    if (message.includes("PIOCHE")) {
        demander_utilisateur_repioche = true;
        // faire apparaitre le bouton pour demander à l'utilisateur de piocher
        envoyerDemandeRepioche(false);
    }
    if (message.includes("POSE")) {
        demander_utilisateur_poser_carte = true;
        // demander à un utilisateur de poser une carte
        envoyerCarteEtPositionAPoser(1, 15, 15);
    }
    if (message.includes("RESULTAT")) {
        resultat = parseInt(message.split(":")[1]);
    }
}

function parseCarte(carteString) {
    let carte = {};
    const tableau = carteString.split(",");
    carte["nom"] = tableau[0];
    carte["position"] = {abscisse: tableau[1], ordonnee: tableau[2]};
    carte["identifiantFaction"] = tableau[3];
    carte["numeroPlateau"] = tableau[4];
    carte["estFaceCachee"] = tableau[5] === 1;
    return carte;
}

function parseGrille(grilleString) {
    const lignes = grilleString.split('|');
    const tableau = [];
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
    return tableau;
}

function parseFaction(factionString) {
    let faction = {};
    const tableau = factionString.split("|");
    faction["identifiant"] = tableau[0];
    faction["nom"] = tableau[1];
    faction["aRemelanger"] = tableau[2] === 1;
    faction["pointsDDRS"] = tableau[3];
    faction["manchesGagnees"] = tableau[4];
    const main = tableau[5].split(";");
    faction["main"] = [];
    main.forEach(carteString => {
        faction["main"].push(parseCarte(carteString))
    });
    return faction;
}