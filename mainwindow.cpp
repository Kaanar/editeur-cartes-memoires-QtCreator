#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <iostream>
#include <QTextStream>
#include <QStringList>
#include <QDirIterator>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //On cache quelques éléments de l'éditeur de cartes lors de son ouverture
    ui->setupUi(this);
    ui->NouveauDeckPage->hide();
    ui->AjouterCartePage->hide();
    ui->CarteReponse->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_FermerMain_clicked()
{
    this->close();
}


void MainWindow::on_NouveauDeckBouton_clicked()
{
    ui->NouveauDeckPage->setVisible(true);
}


void MainWindow::on_OuvrirDeckBouton_clicked()//Il faut ici changer le chemin, qui est dans cette version unique pour mon pc//
{
    //On demande d'abord à l'utilisateur de choisir un deck, puis une carte//
    QString path = QFileDialog::getExistingDirectory(this, "Choisissez un dossier","C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks");
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks");

    QDir dir(path);
    QString nomDuDossier = dir.dirName();//On extrait le nom du deck à partir du chemin que l'utilisateur a choisi//
    QFile fichier(filename);//on déclare filename comme un chemin vers un fichier texte(une carte)//
    QFileInfo Nomfichier(filename);// On utilise QFileInfo pour extraire le nom de la carte//
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);//On ouvre le fichier en lecture seule//
    QTextStream flux(&fichier);
    QString ligne;

/*Ensuite, on va afficher le nom du deck, celui de la carte ainsi que sa question et sa réponse dans les QLabel et
QLineEdit correspondants*/
    ui->CarteDeck->setText(nomDuDossier);
    ui->CarteNom->setText(Nomfichier.baseName());
    ligne = flux.readLine();
    ui->CarteQuestion->setText(ligne);//On utilise la methode readLine() car on veut que seule la première ligne soit
    ligne = flux.readLine();          //affichée dans CarteQuestion
    ligne = flux.readLine();
    ui->CarteReponse->setText(ligne);//et seule la troisième ligne soit affichée dans CarteReponse//
    ui->CarteReponse->hide();


}



void MainWindow::on_SupprimerDeckBouton_clicked()//Il faut ici changer le chemin, qui est dans cette version unique pour mon pc//
{
    //On indique le chemin du deck à supprimer//
        QString CurrentDir = QFileDialog::getExistingDirectory(this, "Supprimer","C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks");
        QDir folder(CurrentDir);
            folder.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
            foreach(QFileInfo fileInfo, folder.entryInfoList())//On supprime d'abord les cartes contenues dans le deck//
            {
              QFile::remove(fileInfo.filePath());
            }
            folder.rmdir(CurrentDir);
}



void MainWindow::on_AjouterCarteBouton_clicked()
{
    ui->AjouterCartePage->setVisible(true);
}


void MainWindow::on_SupprimerCarteBouton_clicked()//Il faut ici changer le chemin, qui est dans cette version unique pour mon pc//
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks");
    QFile::remove(filename);
}




void MainWindow::on_ValiderNomDeck_clicked()//Il faut ici changer le chemin, qui est dans cette version unique pour mon pc//
{
    QDir directory("C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks");
    QString nom=ui->NomDeck->text();
    QDir(directory).mkdir(nom);//Cette opération permet la création du deck avec la variable "nom" comme nom
    ui->VerifDeckName->setText("Deck crée");
}



void MainWindow::on_QuitterAjouterDeck_clicked()
{
    ui->NouveauDeckPage->setVisible(false);
    ui->VerifDeckName->setText("");

}


void MainWindow::on_ValiderAjoutCarte_clicked()//Il faut ici changer le chemin, qui est dans cette version unique pour mon pc//
{
//On récupère dans les Qlabel les informations de l'utilisateur pour créer la nouvelle carte//
    QString nom=ui->NomCarteAAjouter->text();
    QString deck=ui->NomDeckPourcarte->text();
    QString question=ui->CarteQuestionAAjouter->text();
    QString reponse=ui->CarteReponseAAjouter->text();

//Création du chemin//
    QFile file("C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks/"+deck+"/"+nom);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
//Création d'un TextStream pour pouvoir écrire dans le fichier
    QTextStream flux(&file);
    flux.setCodec("UTF-8");
    flux <<question<<endl<<""<<endl;//On écrit à la première ligne la question entrée dans le QlineEdit CarteQuestionAAjouter
    flux <<reponse<<endl;//On écrit à la troisième ligne la réponse entrée dans le QLineEdit CarteReponseAAjouter
    file.close();
}


void MainWindow::on_FermerAjoutCartePage_clicked()
{
    ui->AjouterCartePage->setVisible(false);
}


void MainWindow::on_ModifierCarteBouton_clicked()
{//On suppose ici qu'on ne peut pas changer le nom de la carte.//

//On va récupérer les infos nécessaires: Le nom du deck, celui de la carte, ainsi que la nouvelle question et la nouvelle réponse
    QString Deck=ui->CarteDeck->text();
    QString Nom=ui->CarteNom->text();
    QString question=ui->CarteQuestion->text();
    QString reponse=ui->CarteReponse->text();

//Il faut ici changer le chemin, qui est dans cette version unique pour mon pc//
    QFile file("C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks/"+Deck+"/"+Nom);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

//Création d'un TextStream pour pouvoir écrire dans le fichier
    QTextStream flux(&file);
    flux.setCodec("UTF-8");
    flux <<question<<endl<<""<<endl;//On remplace ici la question et la réponse précédente par
    flux <<reponse<<endl;            //les nouveaux champs récupérés dans les QLabel
    file.close();

}



void MainWindow::on_VoirReponseBouton_clicked()
{
    ui->CarteReponse->show();

}

void MainWindow::on_CacherReponseBouton_clicked()
{
    ui->CarteReponse->hide();

}

void MainWindow::on_DeplacerCarteBouton_clicked()
{
        QString Deck=ui->CarteDeck->text();
        QString Nom=ui->CarteNom->text();
        QString chemin="C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks/"+Deck+"/"+Nom;
        QFile source(chemin);
        QString destination= QFileDialog::getExistingDirectory(this, "Déplacer vers","C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks");
        QDir dir(destination);
        QString nomDuDossier = dir.dirName();
        QFile ephemere(destination+"/"+Nom);
        destination=destination+"/"+Nom;
        source.copy(destination);
        QFile::remove(chemin);

        ui->CarteDeck->setText(nomDuDossier);
}

void MainWindow::on_CarteParcourirBouton_clicked()//Il faut ici changer le chemin, qui est dans cette version unique pour mon pc//
{
    QString Deck=ui->CarteDeck->text();//on récupère le nom du deck ouvert
    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),"C:/Users/Ver de Terre/Documents/Projet_POO_Cartes_2/Decks/"+Deck);
    QFile fichier(filename);//on déclare filename comme un chemin vers un fichier texte(une carte)//
    QFileInfo Nomfichier(filename);// On utilise QFileInfo pour extraire le nom de la carte//
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);//On ouvre le fichier en lecture seule//
    QTextStream flux(&fichier);
    QString ligne;

/*Ensuite, on va afficher le nom de la carte ainsi que sa question et sa réponse dans les QLabel et
QLineEdit correspondants*/
    ui->CarteNom->setText(Nomfichier.baseName());
    ligne = flux.readLine();
    ui->CarteQuestion->setText(ligne);//On utilise la methode readLine() car on veut que seule la première ligne soit
    ligne = flux.readLine();          //affichée dans CarteQuestion
    ligne = flux.readLine();
    ui->CarteReponse->setText(ligne);//et seule la troisième ligne soit affichée dans CarteReponse//
    ui->CarteReponse->hide();
}
