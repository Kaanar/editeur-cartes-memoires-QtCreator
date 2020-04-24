#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_FermerMain_clicked();//Ferme la fenêtre principale//

    void on_NouveauDeckBouton_clicked();//Affiche la fenêtre permettant la création d'un deck//

    void on_OuvrirDeckBouton_clicked();/*Permet d'ouvrir
    une carte dans un deck et d'afficher le deck dans lequel elle se situe, son nom, sa question et sa réponse*/

    void on_SupprimerDeckBouton_clicked();/*Fonction qui permet la suppression d'un
    répertoire choisi par l'utilisateur via l'explorateur de fichiers*/

    void on_AjouterCarteBouton_clicked();//Affiche la fenêtre permettant l'ajout d'une carte dans un deck//

    void on_SupprimerCarteBouton_clicked();/*Cette fonction permet de supprimer une carte en
    utilisant l'explorateur de fichiers*/

    void on_ValiderNomDeck_clicked();/*Permet de créer un deck du nom de son choix après l'avoir indiqué dans
    une QLineEdit*/

    void on_QuitterAjouterDeck_clicked();//Permet de cacher la fenêtre d'ajout de Deck//


    void on_ValiderAjoutCarte_clicked();/*Fonction qui permet d'ajouter une carte dans un deck.J'aurais pu demander
    à l'utilisateur de parcourir l'ensemble des decks, mais je pense que pour un éditeur de cartes, renseigner le nom
    manuellement est plus rapide lorsque l'on veut ajouter plusieurs cartes dans le même deck*/

    void on_FermerAjoutCartePage_clicked();//Permet de cacher la fenêtre d'ajout de carte//

    void on_ModifierCarteBouton_clicked();/*Permet de modifier le nom, la question et la réponse
    d'une carte*/


    void on_VoirReponseBouton_clicked();//Permet d'afficher la QLineEdit comportant la réponse de la carte

    void on_CacherReponseBouton_clicked();//Permet de cacher la QLineEdit comportant la réponse de la carte

    void on_DeplacerCarteBouton_clicked();//Permet de déplacer une carte vers un autre deck

    void on_CarteParcourirBouton_clicked();/*Slot quasiment équivalent à l'ouverture de cartes, seulement ici
                                           l'explorateur de fichiers nous ménera directement à l'intérieur du deck*/


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
