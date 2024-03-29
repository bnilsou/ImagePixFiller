//
//  tools.cpp
//  algoprog_tp1
//
//  Created by Pierre-Antoine Porte on 30/09/2015.
//  Copyright (c) 2015 Porlat. All rights reserved.
//

#include "image.h"

Image::Image() {
}

Image::~Image() {
}

int Image::read(string filepath) {
    
    std::ifstream ifs;
    // Doesn't work with relative path... Investigate later
    // This issue seems to be on Mac only.
    ifs.open (filepath, ifstream::in);
    
    if (ifs.is_open()) {
//        srand(time_t(NULL));
        string bufferLigne = "";
        int numeroLigne = 0;
        
        char c = ifs.get();
        int ligne = 0;
        int colonne = 0;
        
        while (ifs.good()) {
            bufferLigne += c;
            if (c == '\n') {
                if (numeroLigne == 0) {
                    m_type = bufferLigne;
                } else if (numeroLigne == 1) {
                    size_t pos = bufferLigne.find(" ");
                    m_largeur = stoi(bufferLigne.substr(0, pos));
                    m_hauteur = stoi(bufferLigne.substr(pos));
                }
                numeroLigne++;
                bufferLigne = "";
            }
            if ((c == '0' || c == '1' ) && numeroLigne >= 2) {
                int val = 0;
                if (c == '0') {
                    val = NB_COULEURS; // Blanc
                }
                Pixel pix = Pixel(val, val, val);
                pix.setColonne(colonne);
                pix.setLigne(ligne);
                m_pixels.push_back(pix);
                colonne++;
                if (colonne >= m_largeur) {
                    colonne = 0;
                    ligne++;
                }
            }
            c = ifs.get();
        }
        cout << '\n';
        
        // Début affichage pour test
        
        for (unsigned i=0; i < m_hauteur; i++) {
            for (unsigned j=0; j < m_largeur; j++) {
                cout << m_pixels[j+i*m_largeur].getString() << " ";
            }
            cout << '\n';
        }
        
    }
    else {
        // show message:
        std::cout << "Error opening file";
    }
    
    ifs.close();
    
    return 0;
}

void Image::generer(int largeur, int hauteur) {
    m_largeur = largeur;
    m_hauteur = hauteur;

        m_type = CODE_PPM;
        
        m_pixels.clear();
        
        for (int i=0; i<m_largeur*m_hauteur; i++) {

                    int color = rand() % 2;
                    Pixel pix = Pixel(color, color, color);
                    m_pixels.push_back(pix);
        }
    }

void Image::write(string filepath) {
    // Création d'un fichier (mode out)
    std::ofstream ofs;
    ofs.open (filepath, std::ofstream::out);
    
    if (ofs.is_open()) {
        // Préparation du type (P3) en char*
        char* type = (char*)malloc(m_type.size());
        strcpy(type, m_type.c_str());
        
        // Préparation du '\n' en char*
        char* retourLigne = (char*)malloc(1);
        string retourLigneString = "\n";
        strcpy(retourLigne, retourLigneString.c_str());
        
        // Préparation de l'espace ' ' en char*
        char* espace = (char*)malloc(1);
        string espaceString = " ";
        strcpy(espace, espaceString.c_str());
        
        // Préparation de la largeur et de la hauteur
        char* largeur = (char*)malloc(compteChiffresDansNombre(m_largeur));
        string largeurString = to_string(m_largeur);
        strcpy(largeur, largeurString.c_str());
        char* hauteur = (char*)malloc(compteChiffresDansNombre(m_hauteur));
        string hauteurString = to_string(m_hauteur);
        strcpy(hauteur, hauteurString.c_str());
        
        // Préparation du nombre de couleurs (NB_COULEURS)
        char* nbCouleurs = (char*)malloc(compteChiffresDansNombre(NB_COULEURS));
        string nbCouleursString = to_string(NB_COULEURS);
        strcpy(nbCouleurs, nbCouleursString.c_str());
        
        
        // ECRITURE DU HEADER DANS LE FICHIER
        ofs.write(type, sizeof(type));
        ofs.write(largeur, sizeof(largeur));
        ofs.write(espace, sizeof(espace));
        ofs.write(hauteur, sizeof(hauteur));
        ofs.write(retourLigne, sizeof(retourLigne));
        ofs.write(nbCouleurs, sizeof(nbCouleurs));
        ofs.write(retourLigne, sizeof(retourLigne));
        
        // BOUCLE D'ECRITURE DES PIXELS
        cout << endl << endl << endl;
        
        for (int i = 0; i < m_pixels.size(); i++) {
            // Préparation de pixels
            string pixelString = m_pixels[i].getString();
            cout << pixelString << " ";
            char* pixel = (char*)malloc(sizeof(pixelString));
            strcpy(pixel, pixelString.c_str());
            
//            // Espace si (i % 5) == 0
//            if (i % 5 == 0 && i != 0) {
//                ofs.write(retourLigne, sizeof(retourLigne));
//            }
            
            // Écriture
            ofs.write(pixel, sizeof(pixel));
            ofs.write(espace, sizeof(espace));
        }
        
        // FIN BOUCLE
        
        free(type);
        free(retourLigne);
        free(espace);
        free(largeur);
        free(hauteur);
        free(nbCouleurs);
    }
    else {
        // show message:
        std::cout << "Error creating file";
    }
    
    ofs.close();
}

Maillon* Image::findSet(Pixel* pixel) {
    for (int i=0; i<m_sets.size(); i++) {
        
        for (Maillon* maillon = m_sets[i]; maillon->getSuivant() != nullptr ; maillon->getSuivant()) {
            if (maillon->getPixel()->getString() == pixel->getString()) {
                return maillon;
            }
        }
//        test purpose
        cout << m_sets[i]->getRepresentant() << " ";
    }
    return nullptr;
}

Maillon* Image::makeSet(Pixel* pixel) {
    pixel->setCouleur(rand()%255, rand()%255, rand()%255);
    return new Maillon(pixel);
}

void Image::colorierImage() {
//    Boucler sur les pixels de l'image
//    pour créer l'ensemble de set et peupler m_sets
//    Unioner les sets blabla...
//    for (int l=0; l<m_largeur; l++) {
//        for (int h = 0; h<m_hauteur; h++) {
//            if (m_pixels)
//            Maillon* maillon = makeSet(m_pixels[l+h*m_largeur]);
//            m_sets.push_back(maillon);
//        }
//
    m_type = CODE_PPM;
    
    // ETAPE 1 - Créer un ensemble pour chaque pixel blanc de l'image
    for (int i = 0; i < m_pixels.size(); i++) {
        if (m_pixels[i].nEstPasNoir()) {
            Maillon* maillon = makeSet(&m_pixels[i]);
            m_sets.push_back(maillon);
        }
    }
    
    // ETAPE 2 - Pour chaque pixel blanc, pour chacun de ses voisins blancs, si ils ne sont pas dans le même ensemble alors faire l'union
    for (int i = 0; i < m_sets.size(); i++) {
        Maillon* maillon = m_sets[i];
        
        if (maillon->getPixel()->nEstPasNoir()) {
            
            // Voisin de gauche
            if (maillon->getPixel()->getColonne() > 0
                && m_pixels[maillon->getPixel()->getColonne() + maillon->getPixel()->getLigne()*m_largeur-1].nEstPasNoir()) {
                
                // Si ils ne sont pas dans le même ensemble on fusionne
                if (!maillon->sameEnsemble(m_pixels[maillon->getPixel()->getColonne() + maillon->getPixel()->getLigne()*m_largeur-1].getMaillon())) {
                    maillon->getRepresentant()->unionSet(m_pixels[maillon->getPixel()->getColonne() + maillon->getPixel()->getLigne()*m_largeur-1].getMaillon()->getRepresentant());
                }
            }
            
            // Voisin de droite
            if (maillon->getPixel()->getColonne() < m_largeur-1
                && m_pixels[maillon->getPixel()->getColonne() + maillon->getPixel()->getLigne()*m_largeur+1].nEstPasNoir()) {
                
                // Si ils ne sont pas dans le même ensemble on fusionne
                if (!maillon->sameEnsemble(m_pixels[maillon->getPixel()->getColonne() + maillon->getPixel()->getLigne()*m_largeur+1].getMaillon())) {
                    maillon->getRepresentant()->unionSet(m_pixels[maillon->getPixel()->getColonne() + maillon->getPixel()->getLigne()*m_largeur+1].getMaillon()->getRepresentant());
                }
            }
            
            // Voisin du bas
            if (maillon->getPixel()->getLigne() < m_hauteur-1
                && m_pixels[maillon->getPixel()->getColonne() + (maillon->getPixel()->getLigne()+1)*m_largeur].nEstPasNoir()) {
                
                // Si ils ne sont pas dans le même ensemble on fusionne
                if (!maillon->sameEnsemble(m_pixels[maillon->getPixel()->getColonne() + (maillon->getPixel()->getLigne()+1)*m_largeur].getMaillon())) {
                    maillon->getRepresentant()->unionSet(m_pixels[maillon->getPixel()->getColonne() + (maillon->getPixel()->getLigne()+1)*m_largeur].getMaillon()->getRepresentant());
                }
            }
            
            // Voisin du haut
            if (maillon->getPixel()->getLigne() > 0
                && m_pixels[maillon->getPixel()->getColonne() + (maillon->getPixel()->getLigne()-1)*m_largeur].nEstPasNoir()) {
                
                // Si ils ne sont pas dans le même ensemble on fusionne
                if (!maillon->sameEnsemble(m_pixels[maillon->getPixel()->getColonne() + (maillon->getPixel()->getLigne()-1)*m_largeur].getMaillon())) {
                    maillon->getRepresentant()->unionSet(m_pixels[maillon->getPixel()->getColonne() + (maillon->getPixel()->getLigne()-1)*m_largeur].getMaillon()->getRepresentant());
                }
            }
        }
    }
}

int Image::compteChiffresDansNombre(int nombre) {
    int nb_chiffres = 0;
    
    do {
        nb_chiffres++;
        nombre /= 10;
    } while (nombre != 0);
    return nb_chiffres;
}
