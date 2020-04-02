#include <iostream>
#include "pacmanwindow.h"

using namespace std;
PacmanButton::PacmanButton(const QString& str, QWidget *pParent):QPushButton(str, pParent){}

void PacmanButton::keyPressEvent(QKeyEvent *e)
{
    if(parent() != NULL)
        QCoreApplication::sendEvent(parent(), e);
}

PacmanWindow::PacmanWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags)
{
    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    if (pixmapPacman1.load("./data/pacman1.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman1.png"<<endl;
        exit(-1);
    }
    if (pixmapPacman2.load("./data/pacman2.bmp")==false)
    {
        cout<<"Impossible d'ouvrir pacman2.png"<<endl;
        exit(-1);
    }

    if (pixmapFantome.load("./data/fantome.bmp")==false)
    {
        cout<<"Impossible d'ouvrir fantome.bmp"<<endl;
        exit(-1);
    }

    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }

    if (pixmapGomme.load("./data/gomme.bmp")==false)
    {
        cout<<"Impossible d'ouvrir gomme.bmp"<<endl;
        exit(-1);
    }

    if (pixmapPorte.load("./data/porte.bmp")==false)
    {
        cout<<"Impossible d'ouvrir porte.bmp"<<endl;
        exit(-1);
    }
    if (pixmapPointVie.load("./data/coeur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir coeur.bmp"<<endl;
        exit(-1);
    }
    if (pixmapBonus.load("./data/bonus.bmp")==false)
    {
        cout<<"Impossible d'ouvrir bonus.bmp"<<endl;
        exit(-1);
    }

    // Ajouter le button "AJOUTER FANTOME"
    PacmanButton *btA = new PacmanButton("1 Joueur",this);
    btA->setGeometry(5,5,90,25);
    connect(btA,PacmanButton::clicked, this, PacmanWindow::Mode_1_Joueur);

    // Ajouter le button "Supprimer FANTOME"
    PacmanButton *btS = new PacmanButton("2 Joueur",this);
    connect(btS,PacmanButton::clicked, this, PacmanWindow::Mode_2_Joueur);
    btS->setGeometry(5,35,90,25);

    jeu.init();

    QTimer *timer = new QTimer(this);
    connect(timer, QTimer::timeout, this, PacmanWindow::handleTimer);
    timer->start(120);

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase);
}

void PacmanWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    list<Fantome>::const_iterator itFantome;
    int x, y;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine les cases
    for (y=0;y<jeu.getNbCasesY();y++)
        for (x=0;x<jeu.getNbCasesX();x++)
			if (jeu.getCase(x,y)==MUR)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapMur);
            else if(jeu.getCase(x,y) == GOMME)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapGomme);
            else if(jeu.getCase(x,y) == PORTE)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapPorte);
            else if(jeu.getCase(x,y) == BONUS)
                painter.drawPixmap(x*largeurCase, y*hauteurCase, pixmapBonus);
    // Dessine les fantomes
    for (itFantome=jeu.fantomes.begin(); itFantome!=jeu.fantomes.end(); itFantome++)
        {painter.drawPixmap(itFantome->getPosX()*largeurCase, itFantome->getPosY()*hauteurCase, pixmapFantome);}

	// Dessine Pacman 1
	painter.drawPixmap(jeu.Pacman1.getPosPacX()*largeurCase, jeu.Pacman1.getPosPacY()*hauteurCase, pixmapPacman1);

	// Dessine Pacman 2
	if (jeu.Get_NbJoueur()==2)
        painter.drawPixmap(jeu.Pacman2.getPosPacX()*largeurCase, jeu.Pacman2.getPosPacY()*hauteurCase, pixmapPacman2);

    // Dessine Instruction
    painter.drawText(100,23,"Touches Flechees");
    painter.drawText(100,53,"Touches A,W,S,D");

	// Dessine PointdeVie

            // Dans le cas 1 joueur
    painter.drawText(330,23,"Joueur 1 :");
	for (int i =1; i <= jeu.Pacman1.Get_PointVie();i++)
    {
        painter.drawPixmap(400+(i-1)*40,10,40,20,pixmapPointVie);
    }
            // Dans le cas 2 joueurs
    if (jeu.Get_NbJoueur()==2)
    {
        painter.drawText(330,50,"Joueur 2 :");
        for (int j =1; j <= jeu.Pacman2.Get_PointVie();j++)
        {
            painter.drawPixmap(400+(j-1)*40,35,40,20,pixmapPointVie);
        }
    }
}

void PacmanWindow::keyPressEvent(QKeyEvent *event)
{

        if (event->key()==Qt::Key_Left)
        jeu.deplacePacman(&jeu.Pacman1,GAUCHE);
    else if (event->key()==Qt::Key_Right)
        jeu.deplacePacman(&jeu.Pacman1,DROITE);
    else if (event->key()==Qt::Key_Up)
        jeu.deplacePacman(&jeu.Pacman1,HAUT);
    else if (event->key()==Qt::Key_Down)
        jeu.deplacePacman(&jeu.Pacman1,BAS);


        // Si il y a 2 joueurs
        // On utilise clavier anglais

    if (event->key()==Qt::Key_A)
        jeu.deplacePacman(&jeu.Pacman2,GAUCHE);
    else if (event->key()==Qt::Key_D)
        jeu.deplacePacman(&jeu.Pacman2,DROITE);
    else if (event->key()==Qt::Key_W)
        jeu.deplacePacman(&jeu.Pacman2,HAUT);
    else if (event->key()==Qt::Key_S)
        jeu.deplacePacman(&jeu.Pacman2,BAS);


    update();
}

void PacmanWindow::handleTimer()
{
    jeu.evolue();
    Handle_perdu_MSG();
    Handle_Gagner_MSG();
    Handle_Continuer_MSG();
    jeu.Handle_collisions(&jeu.Pacman1);
    jeu.Handle_Gomme(jeu.Pacman1);
    jeu.Handle_Bonus(&jeu.Pacman1);
    if (jeu.Get_NbJoueur() == 2)
    {
        jeu.Handle_collisions(&jeu.Pacman2);
        jeu.Handle_Gomme(jeu.Pacman2);
        jeu.Handle_Bonus(&jeu.Pacman2);
    }

    update();
}

//// mode 1 joueur
void PacmanWindow :: Mode_1_Joueur()
{

    QMessageBox msg;

    jeu.Set_NbJoueur(1);

    msg.setText(" Vous avez changer en mode 1 joueur ");

    msg.exec();
}

//// mode 2 joueur
void PacmanWindow :: Mode_2_Joueur()
{
    QMessageBox msg;

    jeu.Set_NbJoueur(2);

    msg.setText(" Vous avez changer en mode 2 joueur ");

    msg.exec();
}

//// Button rejouer
void PacmanWindow:: Button_Rejouer()
{
    jeu.init();
}

//// Button Sortir
void PacmanWindow:: Button_Sortir()
{
    this->close();
}

//// Button Hard
void PacmanWindow:: Button_Continuer()
{
    jeu.niveau2();
}

//// Message perdu
void PacmanWindow :: Handle_perdu_MSG()
{
    QString ABC;
    string text;
    QMessageBox msg;
    text = "Vinh Hoa";
    ABC = QString::fromLocal8Bit(text.c_str());
    if(jeu.Pacman1.Get_PointVie() == 0 || jeu.Pacman2.Get_PointVie() == 0)
    {
        msg.setText("Vous avez perdu, essayez-vous ?");

        QPushButton *btn_rejouer = msg.addButton("Rejouer", QMessageBox::AcceptRole);
        connect(btn_rejouer, QPushButton::clicked, this, PacmanWindow::Button_Rejouer);

        QPushButton *btn_sortir = msg.addButton("Sortir", QMessageBox::AcceptRole);
        connect(btn_sortir, QPushButton::clicked, this, PacmanWindow::Button_Sortir);

        msg.exec();
    }
}
void PacmanWindow :: Handle_Gagner_MSG()
{
    QMessageBox msg;
    if((jeu.Verifier_Gagner(jeu.Pacman1) == true || jeu.Verifier_Gagner(jeu.Pacman2) == true )&& jeu.Get_Niveau() < 5)
    {
        msg.setText("Bien Joue, Continuez Niveau Suivant ?");

        QPushButton *btn_continuer = msg.addButton("OK", QMessageBox::AcceptRole);
        connect(btn_continuer, QPushButton::clicked, this, PacmanWindow::Button_Continuer);

        QPushButton *btn_sortir = msg.addButton("Sortir", QMessageBox::AcceptRole);
        connect(btn_sortir, QPushButton::clicked, this, PacmanWindow::Button_Sortir);

        msg.exec();
    }
}
void PacmanWindow :: Handle_Continuer_MSG()
{
    QMessageBox msg;
    if(jeu.Get_Niveau() > 4)
    {
        msg.setText("Felicitation, Vous avez gagner ");

        QPushButton *btn_rejouer = msg.addButton("Rejouer", QMessageBox::AcceptRole);
        connect(btn_rejouer, QPushButton::clicked, this, PacmanWindow::Button_Rejouer);

        QPushButton *btn_sortir = msg.addButton("Sortir", QMessageBox::AcceptRole);
        connect(btn_sortir, QPushButton::clicked, this, PacmanWindow::Button_Sortir);

        msg.exec();
    }
}

