//
//  image.h
//  algoprog_tp1
//
//  Created by Pierre-Antoine Porte on 30/09/2015.
//  Copyright (c) 2015 Porlat. All rights reserved.
//

#ifndef __algoprog_tp1__image__
#define __algoprog_tp1__image__

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>
#include <time.h>
#include <stdio.h>
#include "string.h"
using namespace std;

#define CODE_PBM "P1"
#define CODE_PPM "P3"
#define NB_COULEURS 255

class Image {
public:
    Image();
    ~Image();
    int read(string filepath);
    void analyseLigne(string ligne, int position);
    void generer(int largeur, int hauteur);
    void write(string filepath);
private:
    string m_type;
    int m_largeur;
    int m_hauteur;
    vector<int> m_pixels;
    
    int compteChiffresDansNombre(int nombre);
};

#endif /* defined(__algoprog_tp1__image__) */
