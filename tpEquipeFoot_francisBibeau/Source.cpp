#include <iostream>
#include "RockUtiles.h"
using namespace std;

const unsigned short TAILLE_NOM = 31;
const unsigned short TAILLE_PRENOM = 31;

enum Position {
	GARDIEN_DE_BUT = 1,
	ATTAQUANT,
	DEFENSEUR,
	MILIEU_DE_TERRAIN
};

struct joueur {
	unsigned short noDeJoueur;
	char nom[TAILLE_NOM];
	char prenom[TAILLE_PRENOM];
	unsigned short nbButs;
	Position position;
};

unsigned short afficherMenu();
void ajouterJoueur(joueur joueurs[], unsigned short& nbJoueurs);
int rechercherJoueur(joueur joueurs[], unsigned short nbJoueurs);
void modifierJoueur(joueur& joueur);
void retirerJoueur(joueur joueurs[], unsigned short& nbJoueurs, int indiceJoueurARetirer);
void afficherInfoJoueur(const joueur& JOUEUR);
void ajouterButJoueur(joueur& joueur);
void retirerButJoueur(joueur& joueur);
void afficherJoueursParPosition(joueur joueurs[], unsigned short nbJoueurs);
void afficherTotalDeButDeLEquipe(joueur joueurs[], unsigned short nbJoueurs);
int validationNumerique(int chiffre);
unsigned short compteurEquipe(joueur joueurs[]);
int validationMinMax(int min, int max, int choix);
Position selectionPosition();
int occurrencejoueur(joueur joueurs[], int numeroJoueur);
void affichagePositionJoueur(Position position);
void afficherJoueurs(joueur joueurs[], unsigned short nbJoueurs);
unsigned short validationNumeroJoueur( joueur joueurs[], unsigned short nbJoueurs);
	//MAIN------------------------------------------------------------------------------------------------------------------
int TAILLE = 14;
joueur equipe1[14];
unsigned short nombrejoueurEquipe = 0;

int main() {

	color(0x0020);
	const locale LOCALE = locale::global(locale(""));
	int numJoueur = 0;
	int indice = 0;
	short choixMenu = 0;
	choixMenu = afficherMenu();

	switch (choixMenu) {
	case 1: ajouterJoueur(equipe1, nombrejoueurEquipe);

		break;
	case 2: modifierJoueur(equipe1[0]);

		break;
	case 3:

		if (nombrejoueurEquipe != 0) {
			cout << "Le joueur se trouve a quel indice ? " << endl;
			cin >> indice;
			indice = validationMinMax(0, 13, indice);
			retirerJoueur(equipe1, nombrejoueurEquipe, indice);

		}
		else {
			color(0x0040);
			cout << "Il ny a pas de joiueur dans cette equipe " << endl;
			main();
		}
		break;
	case 4:
		numJoueur = rechercherJoueur(equipe1, nombrejoueurEquipe);
		afficherInfoJoueur(equipe1[numJoueur]);
		break;
	case 5:
		numJoueur = rechercherJoueur(equipe1, nombrejoueurEquipe);
		ajouterButJoueur(equipe1[numJoueur]);
		break;
	case 6:
		numJoueur = rechercherJoueur(equipe1, nombrejoueurEquipe);
		retirerButJoueur(equipe1[numJoueur]);
		break;
	case 7: afficherJoueursParPosition(equipe1, nombrejoueurEquipe);
		break;
	case 8: afficherTotalDeButDeLEquipe(equipe1, nombrejoueurEquipe);
		break;
	case 9:
		cout << "Quitter le programme.....";
		break;
	}
	return 0;
}
// FIN MAIN------------------------------------------------------------------------------------------------------------------

unsigned short afficherMenu() {

	cout << "Selectionnez un choix du menu :" << endl;
	cout << "1 - Ajouter un Joueur " << endl;
	cout << "2 - Modifier un Joueur " << endl;
	cout << "3 - Retirer un Joueur " << endl;
	cout << "4 - Afficher les informations d’un joueur selon son numéro de joueur " << endl;
	cout << "5 - Ajouter un but à un joueur selon son numéro de joueur " << endl;
	cout << "6 - Retirer un but à un joueur selon son numéro de joueur " << endl;
	cout << "7 - Afficher tous les joueurs (avec option de filtre) " << endl;
	cout << "8 - Afficher le nombre total de buts comptés pour l’équipe " << endl;
	cout << "9 - Quitter l'application " << endl;

	unsigned short choix = 0;
	cin >> choix;

	choix = validationMinMax(1, 9, choix);

	return choix;
}

void ajouterJoueur(joueur joueurs[], unsigned short& nbJoueurs) {
	joueur joueur;
	Position positionChoisi = Position::ATTAQUANT;
	cout << "Quel est le nom du joueur ?" << endl;
	cin >> joueur.nom;
	cout << "Quel est le prenom du joueur?" << endl;
	cin >> joueur.prenom;
	joueur.nbButs = 0;
	positionChoisi = selectionPosition();
	joueur.position = positionChoisi;
	cout << "Quel est le numero du joueur?" << endl;
	cin >> joueur.noDeJoueur;
	joueurs[nbJoueurs] = joueur;
	color(0x0010);
	cout << "Joureur ajoute ." << endl;
	nbJoueurs++;
	main();

}

int occurrencejoueur(joueur joueurs[], int numeroJoueur) {
	int retour = -1;
	for (int i = 0; i < 14; i++) {
		if (joueurs[i].noDeJoueur == numeroJoueur) {
			retour = i;
		}
	}
	return retour;

}
int rechercherJoueur(joueur joueurs[], unsigned short nbJoueurs) {
	int numeroJoueur = 0;
	cout << "Quel joueur " << endl << "Entrez un numeros de joueur : " << endl;
	cin >> numeroJoueur;

	if (occurrencejoueur(joueurs, numeroJoueur) != -1) {

		return occurrencejoueur(joueurs, numeroJoueur);
	}
	else {
		return -1;

	}

	main();

}

void modifierJoueur(joueur& joueur) {

	int choix = 0;

	cout << "Quelle information voulez vous modifier ? " << endl;
	cout << "1-Pour modifier le numero du joueur " << endl;
	cout << "2-Pour modifier le nom du joueur " << endl;
	cout << "3-Pour modifier le prenom du joueur  " << endl;
	cout << "4-Pour modifier le position du joueur  " << endl;
	cin >> choix;
	choix = validationMinMax(1, 4, choix);
	int numeroJoueur = 0;
	color(0x0010);
	switch (choix) {
	case 1:

		cout << "Le numero est presentement " << joueur.noDeJoueur << ", quel numero voulez vous lui assigner ?" << endl;
		cin >> numeroJoueur;
		validationNumerique(numeroJoueur);
		joueur.noDeJoueur = numeroJoueur;

		break;
	case 2:
		cout << "Le nom du joueur est presentement " << joueur.nom << ", quel nom voulez vous lui assigner ?" << endl;
		cin >> joueur.nom;

		break;
	case 3:
		cout << "Le prenom du joueur est presentement " << joueur.prenom << ", quel position voulez vous lui assigner ?" << endl;
		cin >> joueur.prenom;

		break;
	case 4:
		cout << "La position du joueur est presentement ";
		affichagePositionJoueur(joueur.position);
		joueur.position = selectionPosition();

		break;
	}

	main();


}

void retirerJoueur(joueur joueurs[], unsigned short& nbJoueurs, int indiceJoueurARetirer) {

	int i = 0;

	while (joueurs[i].position != 0) {
		for (int j = 0; j < 14; j++) {
			if (j != indiceJoueurARetirer) {
				joueurs[i] = joueurs[j];
				i++;
				nbJoueurs--;
			}
			else {
				j++;
				joueurs[i] = joueurs[j];
				i++;
			}
		}

	}
	color(0x0010);
	cout << "Joueur retire" << endl;
	main();
}

void afficherInfoJoueur(const joueur& JOUEUR) {
	if (JOUEUR.position != 0) {
		color(0x0010);
		cout << JOUEUR.prenom << " ";
		cout << JOUEUR.nom << " ";
		cout << JOUEUR.noDeJoueur << " ";
		affichagePositionJoueur(JOUEUR.position);
		cout << " " << endl;
	}
	else {
		color(0x0040);
		cout << "Ce joueur n'existe pas" << endl;
	}
	main();
}

void ajouterButJoueur(joueur& joueur) {
	joueur.nbButs++;
	color(0x0010);
	cout << "Le joueur a " << joueur.nbButs << " buts" << endl;
	main();
}

void retirerButJoueur(joueur& joueur) {
	if (joueur.nbButs > 0) {
		joueur.nbButs--;
		color(0x0010);
		cout << "Le joueur a " << joueur.nbButs << " buts" << endl;
		main();
	}
	else {
		color(0x0040);
		cout << "Le joueurr ne peut pas avoir moin de 0 buts" << endl;
		main();

	}
}

void afficherJoueursParPosition(joueur joueurs[], unsigned short nbJoueurs) {

	Position positionRecherchee = selectionPosition();
	for (int i = 0; i < nbJoueurs; i++) {
		if (joueurs[i].position == positionRecherchee) {
			afficherInfoJoueur(joueurs[i]);
		}

	}


}

void afficherTotalDeButDeLEquipe(joueur joueurs[], unsigned short nbJoueurs) {
	int totalDesPointsEquipe = 0;
	for (int i = 0; i < nbJoueurs; i++) {
		totalDesPointsEquipe = totalDesPointsEquipe + joueurs[i].nbButs;
	}
	color(0x0002);
	cout << "Le nombre Total des buts est de " << totalDesPointsEquipe << endl;
	main();
}
int validationNumerique(int chiffre) {
	int chiffreR = chiffre;
	while (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(512, '\n');
		color(0x0040);
		cout << "Attention : Saisir une valeur numérique seulement : ";
		cin >> chiffreR;
	}
	return chiffreR;
}
Position selectionPosition() {
	int choix = 0;
	Position position = Position::ATTAQUANT;

	cout << "Quelle est la position ? " << endl;
	cout << Position::GARDIEN_DE_BUT << "-Gardien de but selectionnez " << endl;
	cout << Position::ATTAQUANT << "-Attanquant selectionnez " << endl;
	cout << Position::DEFENSEUR << "-Defenseur selectionnez " << endl;
	cout << Position::MILIEU_DE_TERRAIN << "-Milieu de terrain selectionnez " << endl;
	cin >> choix;
	validationNumerique(choix);
	while (choix > 4 || choix < 1) {
		cout << "Un chiffre entre 1 et 4 svp." << endl;
		cin >> choix;
		validationNumerique(choix);
	}
	switch (choix) {
	case 1:
		return Position::GARDIEN_DE_BUT;
		break;
	case 2:
		return Position::ATTAQUANT;
		break;
	case 3:
		return Position::DEFENSEUR;
		break;
	case 4:
		return Position::MILIEU_DE_TERRAIN;
		break;
	}
}
unsigned short compteurEquipe(joueur joueurs[]) {
	unsigned short cpt = 0;
	while (joueurs[cpt].position != 0) {
		cpt++;
	}

	return cpt;
}
int validationMinMax(int min, int max, int choix) {

	while (choix > max || choix < min) {
		color(0x0004);
		cout << "Un chiffre entre " << min << " et " << max << " svp." << endl;
		cin >> choix;
		validationNumerique(choix);
	}
	return choix;
}
void affichagePositionJoueur(Position position) {
	if (position == Position::GARDIEN_DE_BUT)
		cout << "Gardien de but";
	else if (position == Position::ATTAQUANT)
		cout << "Attaquant";
	else if (position == Position::DEFENSEUR)
		cout << "Defenseur";
	else if (position == Position::MILIEU_DE_TERRAIN)
		cout << "Milieu de terrain";
}
void afficherJoueurs(joueur joueurs[], unsigned short nbJoueurs) {
	if (nbJoueurs != 0) {
		for (int i = 0; i < nbJoueurs; i++) {
			if (joueurs[i].position != 0) {
				cout << joueurs[i].prenom << " ";
				cout << joueurs[i].nom << " ";
				cout << joueurs[i].noDeJoueur << " ";
				cout << joueurs[i].nbButs << " ";
				affichagePositionJoueur(joueurs[i].position);

				cout << " " << endl;
			}
		}

	}


}
unsigned short validationNumeroJoueur( joueur joueurs[], unsigned short nbJoueurs) {

	unsigned short numeroRetour = 0;
	int numeroL = 0;

	cin >> numeroL;
	numeroL = validationNumerique(numeroL);
	for (int i = 0; i < nbJoueurs; i++) {

		while (joueurs[i].noDeJoueur == numeroL) {

			cout << "Choisissez un autre numero , ce numero est dejas pris :" << endl;
			cin >> numeroL;
			numeroRetour = validationNumerique(numeroL);

		}
	}

	return numeroRetour;
}
