# Gestion de Scolarité - BUT Informatique (SAÉ S1.01)

[cite_start]Ce projet a été réalisé dans le cadre de la **SAÉ S1.01 : Implémentation d'un besoin client** à l'IUT de Paris - Rives de Seine (Université Paris Cité)[cite: 1, 2].

[cite_start]L'objectif est de développer une application en **langage C** permettant de gérer la scolarité d'une promotion d'étudiants en BUT Informatique via un interpréteur de commandes[cite: 5].

## 📋 Fonctionnalités

[cite_start]Le programme fonctionne comme un interpréteur qui lit des commandes sur l'entrée standard et produit les résultats sur la sortie standard[cite: 29]. [cite_start]Il respecte les règles de gestion officielles du BUT (validation des UE, compensation, jurys, passage en année supérieure)[cite: 11, 15].

L'application gère :
* [cite_start]**Les étudiants** : Inscription, démission, défaillance[cite: 34, 89].
* [cite_start]**Les notes** : Saisie des notes (0-20) pour les 6 UE de chaque semestre[cite: 9, 68].
* [cite_start]**Le cursus** : Affichage du relevé de notes, calcul des moyennes (RCUE) et codes de décision (ADM, AJ, ADC, etc.)[cite: 10, 87].
* [cite_start]**Les jurys** : Validation automatique des semestres impairs et délibération pour les semestres pairs (passage ou ajournement)[cite: 18, 19].
* [cite_start]**Le bilan** : Statistiques annuelles sur la promotion[cite: 428].

## 🛠️ Commandes supportées

[cite_start]Le projet interprète les 9 commandes suivantes[cite: 25]:

| Commande | Action |
| :--- | :--- |
| `INSCRIRE Prénom Nom` | [cite_start]Inscrit un nouvel étudiant (max 100)[cite: 35, 450]. |
| `NOTE Id UE Note` | [cite_start]Enregistre une note pour une UE donnée[cite: 67]. |
| `CURSUS Id` | [cite_start]Affiche le parcours complet et le statut d'un étudiant[cite: 46]. |
| `DEMISSION Id` | [cite_start]Enregistre la démission d'un étudiant[cite: 90]. |
| `DEFAILLANCE Id` | [cite_start]Enregistre une défaillance (absences injustifiées)[cite: 90]. |
| `JURY Semestre` | [cite_start]Lance le jury pour un semestre donné (1 à 6)[cite: 106]. |
| `ETUDIANTS` | [cite_start]Affiche la liste de tous les étudiants et leur état[cite: 411]. |
| `BILAN Année` | [cite_start]Affiche le bilan statistique d'une année (1, 2 ou 3)[cite: 429]. |
| `EXIT` | [cite_start]Quitte le programme[cite: 32]. |

## 💻 Technique

* **Langage** : C
* [cite_start]**Structure de données** : Utilisation de `struct` pour les étudiants et la promotion afin d'optimiser la mémoire[cite: 892, 901].
* [cite_start]**Limites** : Gestion jusqu'à 100 étudiants, prénoms/noms limités à 30 caractères[cite: 450].
* [cite_start]**Précision** : Les notes sont stockées en `float` mais affichées avec une décimale tronquée[cite: 452, 455].

## 🚀 Installation et Utilisation

1.  **Cloner le dépôt :**
    ```bash
    git clone [https://github.com/votre-nom/gestion-scolarite-but.git](https://github.com/votre-nom/gestion-scolarite-but.git)
    ```
2.  **Compiler le projet :**
    ```bash
    gcc main.c -o gestion_scolarite
    ```
3.  **Lancer le programme :**
    ```bash
    ./gestion_scolarite
    ```

### Tests
Le projet a été validé via des jeux de tests fournis (`in.txt` et `out.txt`). Vous pouvez tester le programme en redirigeant l'entrée standard :

```bash
./gestion_scolarite < in.txt > resultat.txt
diff resultat.txt out.txt
