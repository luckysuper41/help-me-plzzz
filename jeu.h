#ifndef JEU_H
#define JEU_H

#include <list>
using namespace std;

typedef enum {VIDE, MUR, GOMME, PORTE, BONUS} Case;
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction;

class Jeu;

class Fantome
{
    friend class Jeu;

  protected:
    int posX, posY;
    Direction dir;

  public:
    Fantome();
    int getPosX() const;
    int getPosY() const;
};

class Pacman                // Creer un class Pacman pour 2 joueurs
{
    friend class Jeu;

  protected:
    int PosPacX, PosPacY;
    int PointVie;

  public:
    Pacman();
    // Retourner les dimenssions des pacmans
    int getPosPacX() const;
    int getPosPacY() const;
    // Mettre les dimenssions des pacmans
    void SetPosPacX(const int);
    void SetPosPacY(const int);
    // Retourner Point de Vie
    int Get_PointVie() const;
    // Mettre Point de Vie
    void Set_PointVie(const int);

};

class Jeu
{
  protected:
    Case *terrain;
    int largeur, hauteur;           // Nombre de cases en largeur et en hauteur
    int NbGomme;                    // Nombre de gommes dans la terrain
    int niveau;               // Niveau du jeu
    int NbJoueur;                   // Nombre de joueurs

  public:
    list<Fantome> fantomes;
    Pacman Pacman1,Pacman2;         // Pacman represente joueur


  public:
    Jeu();
    Jeu(const Jeu &)=delete;
    ~Jeu();

    Jeu &operator=(const Jeu &)=delete;

    // Initialiser Pacman
    void Pacman_Init(Pacman *);
    bool init();
    void evolue();
    bool niveau2();      // Augmenter le niveau du jeu

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Set Largeur et Hauteur du jeu
    void set_Largeur(const int);
    void set_Hauteur(const int);

    // Retourne la case à une position donnée
    Case getCase(int, int) const;

    // Indique si la case à une position donnée existe et est vide
    // (Pacman ou les fantomes peuvent l'occuper)
    bool posValide(int, int) const;

    // Déplace Pacman dans une direction (si la case à atteindre est valide)
    bool deplacePacman(Pacman *,Direction);

    // Mettre nombre de joueurs
    void Set_NbJoueur(const int);

    // Retouer nombre de joueurs
    int Get_NbJoueur() const;

    // Verifier les Collisions entre pacman et fantomes
    bool Verifier_collisions(Pacman *);

    // Collisions entre pacman et fantomes
    void Handle_collisions(Pacman *);

    // Bonus point de Vie
    void Handle_Bonus(Pacman *);

    // Verifier Gagner
    bool Verifier_Gagner(Pacman);

    // Set Nombre de gommes
    void Set_NBGommes();

    // Get Nombre de gommes;
    int Get_NBGommes() const;

    // Handle Gomme
    void Handle_Gomme(Pacman );

    // Set niveau du jeu
    void Set_Niveau(int);

    // Get niveau du jeu
    int Get_Niveau();

};

#endif
