#include "pch.h"
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace System;
using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

int cuerpo[200][2];
int n = 1, tam = 6, dir = 1;
int x = 5, y = 43;
int xc, yc;
int velocidad = 300;
char tecla;
int puntaje = 0;

int CARATULA[30][50] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 1, 3, 1, 3, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 3, 3, 6, 6, 6, 0, 6, 0, 0, 6, 0, 6, 6, 6, 0, 6, 3, 3, 6, 3, 6, 6, 6, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 1, 3, 1, 3, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 3, 3, 6, 3, 3, 0, 6, 6, 0, 6, 0, 6, 0, 6, 0, 6, 3, 6, 3, 3, 6, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 1, 1, 3, 1, 3, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 3, 3, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 3, 6, 6, 3, 3, 3, 6, 6, 6, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 1, 3, 1, 3, 1, 3, 3, 0, 1, 0, 0, 0, 1, 1, 3, 3, 3, 3, 3, 3, 3, 6, 3, 6, 3, 6, 6, 0, 6, 0, 6, 3, 6, 3, 6, 3, 3, 6, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 1, 3, 1, 3, 1, 3, 3, 3, 1, 1, 1, 0, 1, 3, 1, 3, 3, 3, 3, 6, 6, 6, 3, 6, 3, 3, 6, 0, 6, 3, 6, 3, 6, 3, 3, 6, 3, 6, 6, 6, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 5, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 5, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 2, 2, 2, 3, 3, 5, 5, 5, 5, 3, 3, 2, 2, 2, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 3, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0},
};
int eleccion[6][50]{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,0,1,0,0,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,0,0,0,1,0,0,1,0,1,0,1,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0},
    {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,0,1,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,0,1,0,0,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,0,0,0,1,1,0,1,0,1,0,1,1,0,1,0,0,1,1,1,0,1,0,0,0,0,0,0},
    {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,0,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0},
    {0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,1,1,0,0,0,0},
};
int cuadroF[20][75] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,2,0,0,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,0,0,2,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,2,2,2,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,2,2,2,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,2,2,2,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,1,1,0,0,1,0,1,1,1,0,0,0,2,2,2,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,2,0,0,0,1,0,0,0,1,0,0,0,1,0,1,1,1,0,0,1,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,2,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

int Derrota[20][75] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,2,0,0,1,0,1,1,1,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,0,2,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,2,2,2,0,0,0,1,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,2,2,2,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,2,2,2,0,1,0,1,0,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,2,2,2,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,2,0,0,1,0,1,0,0,1,0,1,0,0,0,1,1,0,0,1,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,2,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,1,0,1,1,1,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0,1,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
void gotoxy(int x, int y)
{
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}
void OcultaCursor() {
    CONSOLE_CURSOR_INFO cci = { 100, FALSE };

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void mostrar_caratula() {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 50; j++) {
            switch (CARATULA[i][j]) {
            case 0:
                Console::ForegroundColor = ConsoleColor::White;
                cout << char(219); break;
            case 1:
                Console::ForegroundColor = ConsoleColor::DarkYellow;
                cout << char(219); break;
            case 2:
                Console::ForegroundColor = ConsoleColor::Black;
                cout << char(219); break;
            case 3:
                Console::ForegroundColor = ConsoleColor::DarkGreen;
                cout << char(219); break;
            case 4:
                Console::ForegroundColor = ConsoleColor::Black;
                cout << char(219); break;
            case 5:
                Console::ForegroundColor = ConsoleColor::White;
                cout << char(219); break;
            case 6:
                Console::ForegroundColor = ConsoleColor::DarkRed;
                cout << char(219); break;
            }
        }
        cout << endl;
    }


    getch();
    system("cls");
}


void mostrar_NIVEL1() {
    for (int i = 2; i <= 21; i++) {
        gotoxy(i, 1); cout << char(205);
        gotoxy(i, 45); cout << char(205);
    }
    for (int i = 1; i <= 45; i++) {
        gotoxy(2, i); cout << char(186);
        gotoxy(21, i); cout << char(186);
    }
    gotoxy(2, 1); cout << char(201);
    gotoxy(2, 45); cout << char(200);
    gotoxy(21, 1); cout << char(187);
    gotoxy(21, 45); cout << char(188);

    Console::ForegroundColor = ConsoleColor::Black;
    gotoxy(5, 2); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(11, 2); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 2); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(3, 4); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(4, 4); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(5, 4); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(6, 4); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(7, 4); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(8, 4); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(9, 4); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(10, 4); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(11, 4); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(12, 4); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(13, 4); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(14, 4); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(15, 4); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(16, 4); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(17, 4); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(18, 4); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(19, 4); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(20, 4); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(5, 6); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(11, 6); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 6); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(3, 7); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(7, 7); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(9, 7); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(13, 7); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(15, 7); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(19, 7); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(3, 9); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(4, 9); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(5, 9); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(6, 9); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(7, 9); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(8, 9); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(9, 9); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(10, 9); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(11, 9); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(12, 9); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(13, 9); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(14, 9); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(15, 9); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(16, 9); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(17, 9); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(18, 9); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(19, 9); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(20, 9); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(4, 11); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(7, 11); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(10, 11); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(13, 11); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(16, 11); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(19, 11); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(3, 12); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(9, 12); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(15, 12); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(5, 13); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(11, 13); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 13); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(7, 14); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(13, 14); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(19, 14); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(5, 16); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(11, 16); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(17, 16); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(3, 17); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(7, 17); Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(9, 17); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(13, 17); Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(15, 17); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(19, 17); Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(7, 19); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(13, 19); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(19, 19); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(5, 21); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(11, 21); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 21); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(3, 23); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(4, 23); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(5, 23); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(6, 23); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(7, 23); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(8, 23); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(9, 23); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(10, 23); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(11, 23); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(12, 23); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(13, 23); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(14, 23); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(15, 23); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(16, 23); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(17, 23); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(18, 23); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(19, 23); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(20, 23); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(5, 25); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(11, 25); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 25); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(3, 26); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(7, 26); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(9, 26); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(13, 26); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(15, 26); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(19, 26); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(3, 28); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(4, 28); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(5, 28); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(6, 28); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(7, 28); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(8, 28); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(9, 28); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(10, 28); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(11, 28); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(12, 28); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(13, 28); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(14, 28); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(15, 28); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(16, 28); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(17, 28); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(18, 28); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(19, 28); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(20, 28); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(4, 30); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(7, 30); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(10, 30); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(13, 30); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(16, 30); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(19, 30); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(3, 31); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(9, 31); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(15, 31); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(5, 32); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(11, 32); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 32); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(7, 33); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(13, 33); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(19, 33); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(5, 35); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(11, 35); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(17, 35); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(3, 36); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(7, 36); Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(9, 36); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(13, 36); Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(15, 36); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(19, 36); Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(7, 38); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(13, 38); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(19, 38); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";

}

void mostrar_NIVEL2() {
    Console::ForegroundColor = ConsoleColor::White;
    for (int i = 1; i <= 20; i++) {
        gotoxy(i, 1); cout << char(205);
        gotoxy(i, 45); cout << char(205);
    }
    for (int v = 1; v <= 45; v++) {
        gotoxy(1, v);  cout << char(186);
        gotoxy(20, v); cout << char(186);
    }
    gotoxy(1, 1);    cout << char(201);
    gotoxy(1, 45);    cout << char(200);
    gotoxy(20, 1);    cout << char(187);
    gotoxy(20, 45);    cout << char(188);


    Console::ForegroundColor = ConsoleColor::Black;

    gotoxy(5, 2); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(2, 2); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(3, 3); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(4, 3); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(6, 3); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(15, 3); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 3); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(9, 3); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(10, 3); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(14, 3); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(2, 4); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(5, 4); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(7, 4); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(8, 4); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(11, 4); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(12, 4); Console::BackgroundColor = ConsoleColor::Yellow; cout << "5";
    gotoxy(13, 4); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(14, 4); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(16, 4); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(18, 5); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(19, 5); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(2, 6); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(4, 6); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(6, 6); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(8, 6); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(10, 6); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(12, 6); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(14, 6); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(16, 6); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(18, 6); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(19, 7); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(17, 7); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(15, 7); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(13, 7); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(11, 7);  Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(4, 10); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(7, 10); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(5, 10); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(3, 10); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(19, 10); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(15, 10); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(11, 10); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(9, 9); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(8, 9); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(2, 9); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(3, 9); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(3, 12); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(2, 11); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(5, 11); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(7, 11); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(8, 11); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(11, 11); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(12, 11);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "5";
    gotoxy(13, 11); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(14, 11); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(16, 11); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(7, 12); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(5, 12); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(2, 12);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(2, 13); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(4, 13);  Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(6, 13); Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(8, 13); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(10, 13);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "7";
    gotoxy(12, 13); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(14, 13); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(16, 13); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(18, 13); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";

    gotoxy(5, 13); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(15, 13); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";

    gotoxy(17, 13); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(19, 15); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(17, 15); Console::BackgroundColor = ConsoleColor::Yellow; cout << "7";
    gotoxy(15, 15); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(13, 15); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(11, 15); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(9, 15); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(7, 15); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(5, 15); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(3, 15); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(3, 39); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(4, 39); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(6, 9); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(15, 9); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 9); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(9, 9); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(10, 9); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(14, 9); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(14, 15); Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(12, 15); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(18, 15); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(2, 15);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "4";
    gotoxy(5, 16); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(12, 16); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(10, 16); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(16, 16); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(6, 16); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(7, 16); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";

    gotoxy(2, 16); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(2, 17); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(4, 17); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(6, 17); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(8, 18);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "6";
    gotoxy(10, 18); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(12, 19); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(14, 18); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(16, 19); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(18, 18); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(4, 20); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(8, 20); Console::BackgroundColor = ConsoleColor::Yellow; cout << "7";
    gotoxy(12, 20); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(16, 20); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(17, 20); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(17, 21); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(10, 21); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(11, 21); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(4, 21); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(14, 22); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(12, 22); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(18, 22); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(2, 22);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "4";
    gotoxy(5, 21); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";

    gotoxy(10, 22); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(16, 22); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(6, 22); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(7, 23); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(8, 25); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(9, 24); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(10, 23); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(12, 25); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(10, 23); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(16, 25); Console::BackgroundColor = ConsoleColor::Yellow; cout << "5";
    gotoxy(6, 23); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(4, 27); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(5, 27); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(15, 27); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(16, 27); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(17, 27); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(2, 28); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(5, 28);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "5";
    gotoxy(8, 28);  Console::BackgroundColor = ConsoleColor::Yellow; cout << "9";
    gotoxy(11, 28); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(14, 28); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(4, 29); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(8, 29); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(12, 30); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(16, 30); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(17, 29); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(17, 31); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(10, 31); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(11, 31); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(4, 31); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(14, 33); Console::BackgroundColor = ConsoleColor::DarkRed; cout << "9";
    gotoxy(12, 33); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(18, 33); Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(2, 33); Console::BackgroundColor = ConsoleColor::White; cout << "6";
    gotoxy(2, 38); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(3, 37); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(4, 36); Console::BackgroundColor = ConsoleColor::DarkBlue; cout << "4";
    gotoxy(5, 35);  Console::BackgroundColor = ConsoleColor::Blue; cout << "7";
    gotoxy(6, 34); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(19, 38); Console::BackgroundColor = ConsoleColor::Yellow; cout << "2";
    gotoxy(18, 37);  Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(17, 36); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(16, 35); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(15, 34); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";
    gotoxy(16, 38); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(13, 38); Console::BackgroundColor = ConsoleColor::Yellow; cout << "8";
    gotoxy(8, 38); Console::BackgroundColor = ConsoleColor::DarkGreen; cout << "3";
    gotoxy(13, 39); Console::BackgroundColor = ConsoleColor::Cyan; cout << "1";
    gotoxy(2, 37); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(9, 37); Console::BackgroundColor = ConsoleColor::DarkCyan; cout << "2";
    gotoxy(10, 36); Console::BackgroundColor = ConsoleColor::Yellow; cout << "3";
    gotoxy(11, 35); Console::BackgroundColor = ConsoleColor::Gray; cout << "5";
    gotoxy(9, 34); Console::BackgroundColor = ConsoleColor::DarkYellow; cout << "8";



}
void mostrar_instrucciones() {
    Console::ForegroundColor = ConsoleColor::DarkYellow;
    Console::SetCursorPosition(28, 1);
    cout << "SOBRE EL JUEGO" << endl << endl;
    cout << " Al comenzar el juego, contaremos con una serpiente con 5 enlaces, la cual podremos " << endl;
    cout << " desplazar por el mapa aumentando nuestros enlaces o disminuyendolos. ." << endl;
    cout << " En el camino nos encontraremos con obstaculos que seran bloques de colores que " << endl;
    cout << " tendran un numero en el centro. Estos numeros indican la resistencia del bloque" << endl;
    cout << " y cuantos enlaces de la serpiente necesita para que la serpiente pueda romper el " << endl;
    cout << " bloque." << endl;
    cout << " Si la cantidad de este bloque es mayor a los enlaces de la serpiente, el jugador" << endl;
    cout << " perdera una vida y el juego se reiniciara." << endl;
    cout << " Ademas,en el camino, se encontraran bloques de 1 al 9 que aumentaran los enlaces segun" << endl;
    cout << " el numero que esta en el bloque. Estos bloques seran todos del color amarillo," << endl;
    cout << " sin importar el numero." << endl;
    cout << "Al lado izquierdo del mapa contaras con un contador de puntaje que aumentara dependiendo" << endl;
    cout << "a que numero del bloque amarillo atravieses." << endl;
    cout << "Al llegar a 50 puntos, la velocidad y fuerza de la serpiente aumetara. Esto significa que " << endl;
    cout << "los bloques valdran la mitad de su valor. Es decir, si chocas contra un bloque que te disminuira" << endl;
    cout << "6 enlaces, ahora solo te disminuara 3 puntos." << endl;
    cout << "Para poder ganar necesitas llegar con al menos con un enlace a la linea 0" << endl;

    Console::ForegroundColor = ConsoleColor::White;
    cout << "   TECLAS PARA DESPLAZARSE:" << endl << endl;
    cout << "   (" << char(24) << ") Para desplazarte hacia arriba  " << "(<-) para desplazarte hacia la izquierda" << endl;
    cout << endl;
    cout << "   (" << char(25) << ") para desplazarte hacia abajo   " << "(" << char(26) << ") para desplazarte hacia la derecha" << endl;
    getch();
    system("cls");
}
int Elegir_Dificultad(int& vidas) {
    int nivel;
    do {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 50; j++) {
                switch (eleccion[i][j]) {
                case 0:
                    Console::ForegroundColor = ConsoleColor::Black;
                    cout << char(219); break;
                case 1:
                    Console::ForegroundColor = ConsoleColor::Red;
                    cout << char(219); break;
                }
            }
            cout << endl;
        }
        cout << endl;
        Console::ForegroundColor = ConsoleColor::DarkYellow;
        cout << "                         __                                                               _____________" << endl;
        cout << "                        //||                                                                          ||" << endl;
        cout << "                       // ||                              _____                                       ||" << endl;
        cout << "                          ||                             ||   ||                                      ||" << endl;
        cout << "                          ||                             ||   ||                          ____________||" << endl;
        cout << "                          ||                             ||___||                          ||            " << endl;
        cout << "                          ||                                                              ||            " << endl;
        cout << "                          ||                                                              ||            " << endl;
        cout << "                        __||__                                                            ||____________" << endl;
        cin >> nivel;
        cout << "VIDAS DEL USUARIO" << endl;
        cin >> vidas; system("cls");
    } while (!(nivel == 1 || nivel == 2));
    return nivel;
    getch();
}

void mostrar_puntaje(int vidas) {
    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(23, 1); cout << "____________________";
    Console::SetCursorPosition(23, 2); cout << "|PUNTAJE:" << puntaje << "          |";
    Console::SetCursorPosition(23, 3); cout << "|___________________|";

    for (int i = 0; i < vidas; i++)
    {
        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(23, 4); cout << "VIDAS: ";
        Console::ForegroundColor = ConsoleColor::Red;
        Console::SetCursorPosition(23 + i, 5); cout << char(259);
    }
    if (puntaje == 50) {
        tam = tam * 2;
    }

}

void guardar_posicion() {
    cuerpo[n][0] = x;
    cuerpo[n][1] = y;
    n++;
    if (n == tam) n = 1;
}
void dibujar_cuerpo() {
    for (int i = 1; i < tam; i++) {
        gotoxy(cuerpo[i][0], cuerpo[i][1]); Console::ForegroundColor = ConsoleColor::DarkRed;
        Console::BackgroundColor = ConsoleColor::Black; cout << char(259);
    }
}
void borrar_cuerpo() {
    gotoxy(cuerpo[n][0], cuerpo[n][1]); cout << " ";
}
void teclear() {
    if (kbhit()) {
        tecla = getch();
        switch (tecla) {
        case ARRIBA: if (dir != 2) dir = 1; break;
        case ABAJO: if (dir != 1) dir = 2; break;
        case DERECHA: if (dir != 4) dir = 3; break;
        case IZQUIERDA: if (dir != 3) dir = 4; break;
        }
    }
}
void comer1() {

    if (x == 5 && y == 2) {
        tam -= 4;
        puntaje++;
    }if (x == 11 && y == 2) {
        tam -= 4;
        puntaje++;
    }if (x == 17 && y == 2) {
        tam -= 4;
        puntaje++;
    }if (x == 3 && y == 4) {
        tam -= 4;
        puntaje++;
    }if (x == 4 && y == 4) {
        tam -= 8;
        puntaje++;
    }if (x == 5 && y == 4) {
        tam -= 2;
        puntaje++;
    }if (x == 6 && y == 4) {
        tam -= 9;
        puntaje++;
    }if (x == 7 && y == 4) {
        tam -= 6;
        puntaje++;
    }if (x == 8 && y == 4) {
        tam -= 3;
        puntaje++;
    }if (x == 9 && y == 4) {
        tam -= 4;
        puntaje++;
    }if (x == 10 && y == 4) {
        tam -= 8;
        puntaje++;
    }if (x == 11 && y == 4) {
        tam -= 2; puntaje++;
    }if (x == 12 && y == 4) {
        tam -= 9; puntaje++;
    }if (x == 13 && y == 4) {
        tam -= 6; puntaje++;
    }if (x == 14 && y == 4) {
        tam -= 3; puntaje++;
    }if (x == 15 && y == 4) {
        tam -= 4; puntaje++;
    }if (x == 16 && y == 4) {
        tam += 8; puntaje++;
    }if (x == 17 && y == 4) {
        tam -= 2; puntaje++;
    }if (x == 18 && y == 4) {
        tam -= 9; puntaje++;
    }if (x == 19 && y == 4) {
        tam -= 6; puntaje++;
    }if (x == 20 && y == 4) {
        tam -= 3; puntaje++;
    }if (x == 5 && y == 6) {
        tam -= 4; puntaje++;
    }if (x == 11 && y == 6) {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 6) {
        tam -= 4; puntaje++;
    }if (x == 3 && y == 7) {
        tam += 8; puntaje++;
    }if (x == 7 && y == 7) {
        tam += 9; puntaje++;
    }if (x == 9 && y == 7) {
        tam += 8; puntaje++;
    }if (x == 13 && y == 7) {
        tam += 9; puntaje++;
    }if (x == 15 && y == 7) {
        tam += 8; puntaje++;
    }if (x == 19 && y == 7) {
        tam += 9; puntaje++;
    } if (x == 3 && y == 9) {
        tam -= 7; puntaje++;
    }if (x == 4 && y == 9) {
        tam += 8; puntaje++;
    }if (x == 5 && y == 9) {
        tam -= 2; puntaje++;
    }if (x == 6 && y == 9) {
        tam -= 9; puntaje++;
    }if (x == 7 && y == 9) {
        tam -= 6; puntaje++;
    }if (x == 8 && y == 9) {
        tam -= 3; puntaje++;
    }if (x == 9 && y == 9) {
        tam -= 7; puntaje++;
    }if (x == 10 && y == 9) {
        tam += 8; puntaje++;
    }if (x == 11 && y == 9) {
        tam -= 2; puntaje++;
    }if (x == 12 && y == 9) {
        tam -= 9; puntaje++;
    }if (x == 13 && y == 9) {
        tam -= 6; puntaje++;
    }if (x == 14 && y == 9) {
        tam -= 3; puntaje++;
    }if (x == 15 && y == 9) {
        tam -= 7; puntaje++;
    }if (x == 16 && y == 9) {
        tam += 8; puntaje++;
    }if (x == 17 && y == 9) {
        tam -= 2; puntaje++;
    }if (x == 18 && y == 9) {
        tam -= 9; puntaje++;
    }if (x == 19 && y == 9) {
        tam -= 6; puntaje++;
    }if (x == 20 && y == 9) {
        tam -= 3; puntaje++;
    }if (x == 4 && y == 11) {
        tam += 9; puntaje++;
    }if (x == 7 && y == 11) {
        tam += 3; puntaje++;
    }if (x == 10 && y == 11) {
        tam += 9; puntaje++;
    }if (x == 13 && y == 11) {
        tam += 3; puntaje++;
    }if (x == 16 && y == 11) {
        tam += 9; puntaje++;
    }if (x == 19 && y == 11) {
        tam += 3; puntaje++;
    }if (x == 3 && y == 12) {
        tam -= 3; puntaje++;
    }if (x == 9 && y == 12) {
        tam -= 3; puntaje++;
    }if (x == 15 && y == 12) {
        tam -= 3; puntaje++;
    }if (x == 5 && y == 13) {
        tam -= 4; puntaje++;
    }if (x == 11 && y == 13) {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 13) {
        tam -= 4; puntaje++;
    }if (x == 7 && y == 14) {
        tam -= 5; puntaje++;
    }if (x == 13 && y == 14) {
        tam -= 5; puntaje++;
    }if (x == 19 && y == 14) {
        tam -= 5; puntaje++;
    }if (x == 5 && y == 16) {
        tam -= 3; puntaje++;
    }if (x == 11 && y == 16) {
        tam -= 3; puntaje++;
    }if (x == 17 && y == 16) {
        tam -= 3; puntaje++;
    }if (x == 3 && y == 17) {
        tam -= 1; puntaje++;
    }if (x == 7 && y == 17) {
        tam += 6; puntaje++;
    }if (x == 9 && y == 17) {
        tam -= 1; puntaje++;
    }if (x == 13 && y == 17) {
        tam += 6; puntaje++;
    }if (x == 15 && y == 17) {
        tam -= 1; puntaje++;
    }if (x == 19 && y == 17) {
        tam += 6; puntaje++;
    }if (x == 7 && y == 19) {
        tam -= 3; puntaje++;
    }if (x == 13 && y == 19) {
        tam -= 3; puntaje++;
    }if (x == 19 && y == 19) {
        tam -= 3; puntaje++;
    }if (x == 5 && y == 21) {
        tam -= 4; puntaje++;
    }if (x == 11 && y == 21) {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 21) {
        tam -= 4; puntaje++;
    }if (x == 3 && y == 23) {
        tam -= 4; puntaje++;
    }if (x == 4 && y == 23) {
        tam -= 8; puntaje++;
    }if (x == 5 && y == 23) {
        tam -= 2; puntaje++;
    }if (x == 6 && y == 23) {
        tam -= 9; puntaje++;
    }if (x == 7 && y == 23) {
        tam -= 6; puntaje++;
    }if (x == 8 && y == 23) {
        tam -= 3; puntaje++;
    }if (x == 9 && y == 23) {
        tam -= 4; puntaje++;
    }if (x == 10 && y == 23) {
        tam -= 8; puntaje++;
    }if (x == 11 && y == 23) {
        tam -= 2; puntaje++;
    }if (x == 12 && y == 23) {
        tam -= 9; puntaje++;
    }if (x == 13 && y == 23) {
        tam -= 6; puntaje++;
    }if (x == 14 && y == 23) {
        tam -= 3; puntaje++;
    }if (x == 15 && y == 23) {
        tam -= 4; puntaje++;
    }if (x == 16 && y == 23) {
        tam -= 8; puntaje++;
    }if (x == 17 && y == 23) {
        tam -= 2; puntaje++;
    }if (x == 18 && y == 23) {
        tam -= 9; puntaje++;
    }if (x == 19 && y == 23) {
        tam -= 6; puntaje++;
    }if (x == 20 && y == 23) {
        tam -= 3; puntaje++;
    }if (x == 5 && y == 25) {
        tam -= 4; puntaje++;
    }if (x == 11 && y == 25) {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 25) {
        tam -= 4; puntaje++;
    }if (x == 3 && y == 26) {
        tam += 8; puntaje++;
    }if (x == 7 && y == 26) {
        tam += 9; puntaje++;
    }if (x == 9 && y == 26) {
        tam += 8; puntaje++;
    }if (x == 13 && y == 26) {
        tam += 9; puntaje++;
    }if (x == 15 && y == 26) {
        tam += 8; puntaje++;
    }if (x == 19 && y == 26) {
        tam += 9; puntaje++;
    }if (x == 3 && y == 28) {
        tam -= 7; puntaje++;
    }if (x == 4 && y == 28) {
        tam -= 8; puntaje++;
    }if (x == 5 && y == 28) {
        tam -= 2; puntaje++;
    }if (x == 6 && y == 28) {
        tam -= 9; puntaje++;
    }if (x == 7 && y == 28) {
        tam -= 6; puntaje++;
    }if (x == 8 && y == 28) {
        tam -= 3; puntaje++;
    }if (x == 9 && y == 28) {
        tam -= 7; puntaje++;
    }if (x == 10 && y == 28) {
        tam -= 8; puntaje++;
    }if (x == 11 && y == 28) {
        tam -= 2; puntaje++;
    }if (x == 12 && y == 28) {
        tam -= 9; puntaje++;
    }if (x == 13 && y == 28) {
        tam -= 6; puntaje++;
    }if (x == 14 && y == 28) {
        tam -= 3; puntaje++;
    }if (x == 15 && y == 28) {
        tam -= 7; puntaje++;
    }if (x == 16 && y == 28) {
        tam -= 8; puntaje++;
    }if (x == 17 && y == 28) {
        tam -= 2; puntaje++;
    }if (x == 18 && y == 28) {
        tam -= 9; puntaje++;
    }if (x == 19 && y == 28) {
        tam -= 6; puntaje++;
    }if (x == 20 && y == 28) {
        tam -= 3; puntaje++;
    }if (x == 4 && y == 30) {
        tam += 9; puntaje++;
    }if (x == 7 && y == 30) {
        tam += 3; puntaje++;
    }if (x == 10 && y == 30) {
        tam += 9; puntaje++;
    }if (x == 13 && y == 30) {
        tam += 3; puntaje++;
    }if (x == 16 && y == 30) {
        tam += 9; puntaje++;
    }if (x == 19 && y == 30) {
        tam += 3; puntaje++;
    }if (x == 3 && y == 31) {
        tam -= 3; puntaje++;
    }if (x == 9 && y == 31) {
        tam -= 3; puntaje++;
    }if (x == 15 && y == 31) {
        tam -= 3; puntaje++;
    }if (x == 5 && y == 32) {
        tam -= 4; puntaje++;
    }if (x == 11 && y == 32) {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 32) {
        tam -= 4; puntaje++;
    }if (x == 7 && y == 33) {
        tam -= 5; puntaje++;
    }if (x == 13 && y == 33) {
        tam -= 5; puntaje++;
    }if (x == 19 && y == 33) {
        tam -= 5; puntaje++;
    }if (x == 5 && y == 35) {
        tam -= 3; puntaje++;
    }if (x == 11 && y == 35) {
        tam -= 3; puntaje++;
    }if (x == 17 && y == 35) {
        tam -= 3; puntaje++;
    }if (x == 3 && y == 36) {
        tam -= 1; puntaje++;
    }if (x == 7 && y == 36) {
        tam += 6; puntaje++;
    }if (x == 9 && y == 36) {
        tam -= 1; puntaje++;
    }if (x == 13 && y == 36) {
        tam += 6; puntaje++;
    }if (x == 15 && y == 36) {
        tam -= 1; puntaje++;
    }if (x == 19 && y == 36) {
        tam += 6; puntaje++;
    }if (x == 7 && y == 38) {
        tam -= 3; puntaje++;
    }if (x == 13 && y == 38) {
        tam -= 3; puntaje++;
    }if (x == 19 && y == 38) {
        tam -= 3; puntaje++;
    }

}

void comer2() {
    if (x == 5 && y == 2)
    {
        tam -= 1;
        puntaje++;
    }if (x == 2 && y == 2)
    {
        tam -= 4; puntaje++;
    }if (x == 3 && y == 3)
    {
        tam -= 8; puntaje++;
    }if (x == 4 && y == 3)
    {
        tam -= 2; puntaje++;
    }if (x == 6 && y == 3)
    {
        tam -= 1; puntaje++;
    }if (x == 15 && y == 3)
    {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 3)
    {
        tam -= 1; puntaje++;
    }if (x == 9 && y == 3)
    {
        tam -= 5; puntaje++;
    }if (x == 10 && y == 3)
    {
        tam -= 2; puntaje++;
    }if (x == 14 && y == 3)
    {
        tam -= 9; puntaje++;
    }if (x == 2 && y == 4)
    {
        tam -= 1; puntaje++;
    }if (x == 5 && y == 4)
    {
        tam -= 4; puntaje++;
    }if (x == 7 && y == 4)
    {
        tam -= 7; puntaje++;
    }if (x == 8 && y == 4)
    {
        tam -= 3; puntaje++;
    }if (x == 11 && y == 4)
    {
        tam -= 3; puntaje++;
    }if (x == 12 && y == 4)
    {
        tam += 5; puntaje++;
    }if (x == 13 && y == 4)
    {
        tam -= 1; puntaje++;
    }if (x == 14 && y == 4)
    {
        tam -= 7; puntaje++;
    }if (x == 16 && y == 4)
    {
        tam -= 4; puntaje++;
    }if (x == 18 && y == 5)
    {
        tam += 3; puntaje++;
    }if (x == 19 && y == 5)
    {
        tam -= 8; puntaje++;
    }if (x == 2 && y == 6)
    {
        tam += 8; puntaje++;
    }if (x == 4 && y == 6)
    {
        tam -= 5; puntaje++;
    }if (x == 4 && y == 6)
    {
        tam -= 5; puntaje++;
    }if (x == 6 && y == 6)
    {
        tam -= 3; puntaje++;
    }if (x == 8 && y == 6)
    {
        tam -= 2; puntaje++;
    }if (x == 10 && y == 6)
    {
        tam -= 1; puntaje++;
    }if (x == 12 && y == 6)
    {
        tam -= 1; puntaje++;
    }if (x == 14 && y == 6)
    {
        tam -= 9; puntaje++;
    }if (x == 16 && y == 6)
    {
        tam -= 4; puntaje++;
    }if (x == 18 && y == 6)
    {
        tam -= 6; puntaje++;
    }if (x == 19 && y == 7)
    {
        tam -= 8; puntaje++;
    }if (x == 17 && y == 7)
    {
        tam -= 2; puntaje++;
    }if (x == 15 && y == 7)
    {
        tam -= 4; puntaje++;
    }if (x == 13 && y == 7)
    {
        tam -= 3; puntaje++;
    }if (x == 11 && y == 7)
    {
        tam -= 2; puntaje++;
    }if (x == 4 && y == 10)
    {
        tam += 9; puntaje++;
    }if (x == 7 && y == 10)
    {
        tam -= 3; puntaje++;
    }if (x == 5 && y == 10)
    {
        tam -= 4; puntaje++;
    }if (x == 3 && y == 10)
    {
        tam -= 7; puntaje++;
    }if (x == 19 && y == 10)
    {
        tam -= 2; puntaje++;
    }if (x == 15 && y == 10)
    {
        tam -= 2; puntaje++;
    }if (x == 11 && y == 10)
    {
        tam -= 1; puntaje++;
    }if (x == 9 && y == 9)
    {
        tam -= 4; puntaje++;
    }if (x == 8 && y == 9)
    {
        tam -= 6; puntaje++;
    }if (x == 2 && y == 9)
    {
        tam -= 7; puntaje++;
    }if (x == 3 && y == 9)
    {
        tam += 3; puntaje++;
    }if (x == 3 && y == 12)
    {
        tam -= 1; puntaje++;
    }if (x == 5 && y == 11)
    {
        tam -= 4; puntaje++;
    }if (x == 2 && y == 11)
    {
        tam -= 1; puntaje++;
    }if (x == 7 && y == 11)
    {
        tam -= 7; puntaje++;
    }if (x == 8 && y == 11)
    {
        tam -= 3; puntaje++;
    }if (x == 11 && y == 11)
    {
        tam -= 3; puntaje++;
    }if (x == 12 && y == 11)
    {
        tam += 5; puntaje++;
    }if (x == 13 && y == 11)
    {
        tam -= 1; puntaje++;
    }if (x == 14 && y == 11)
    {
        tam -= 8; puntaje++;
    }if (x == 16 && y == 11)
    {
        tam -= 3; puntaje++;
    }if (x == 7 && y == 12)
    {
        tam -= 5; puntaje++;
    }if (x == 5 && y == 12)
    {
        tam -= 4; puntaje++;
    }if (x == 2 && y == 12)
    {
        tam += 3; puntaje++;
    }if (x == 2 && y == 13)
    {
        tam -= 3; puntaje++;
    }if (x == 4 && y == 13)
    {
        tam -= 5; puntaje++;
    }if (x == 6 && y == 13)
    {
        tam += 6; puntaje++;
    }if (x == 8 && y == 13)
    {
        tam -= 6; puntaje++;
    }if (x == 8 && y == 13)
    {
        tam -= 6; puntaje++;
    }if (x == 10 && y == 13)
    {
        tam += 7; puntaje++;
    }if (x == 12 && y == 13)
    {
        tam -= 3; puntaje++;
    }if (x == 14 && y == 13)
    {
        tam -= 2; puntaje++;
    }if (x == 16 && y == 13)
    {
        tam -= 1; puntaje++;
    }if (x == 18 && y == 13)
    {
        tam -= 1; puntaje++;
    }if (x == 5 && y == 13)
    {
        tam -= 8; puntaje++;
    }if (x == 15 && y == 13)
    {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 13)
    {
        tam -= 2; puntaje++;
    }if (x == 19 && y == 15)
    {
        tam -= 1; puntaje++;
    }if (x == 17 && y == 15)
    {
        tam += 7; puntaje++;
    }if (x == 15 && y == 15)
    {
        tam -= 7; puntaje++;
    }if (x == 13 && y == 15)
    {
        tam -= 6; puntaje++;
    }if (x == 11 && y == 15)
    {
        tam -= 3; puntaje++;
    }if (x == 9 && y == 15)
    {
        tam -= 1; puntaje++;
    }if (x == 7 && y == 15)
    {
        tam -= 2; puntaje++;
    }if (x == 5 && y == 15)
    {
        tam -= 2; puntaje++;
    }if (x == 3 && y == 15)
    {
        tam -= 2; puntaje++;
    }if (x == 3 && y == 39)
    {
        tam -= 8; puntaje++;
    }if (x == 4 && y == 39)
    {
        tam -= 5; puntaje++;
    }if (x == 6 && y == 9)
    {
        tam -= 1; puntaje++;
    }if (x == 15 && y == 9)
    {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 9)
    {
        tam -= 1; puntaje++;
    }if (x == 9 && y == 9)
    {
        tam -= 5; puntaje++;
    }if (x == 10 && y == 9)
    {
        tam -= 2; puntaje++;
    }if (x == 14 && y == 9)
    {
        tam -= 9; puntaje++;
    }if (x == 14 && y == 15)
    {
        tam += 9; puntaje++;
    }if (x == 12 && y == 15)
    {
        tam -= 7; puntaje++;
    }if (x == 18 && y == 15)
    {
        tam -= 3; puntaje++;
    }if (x == 2 && y == 15)
    {
        tam += 4; puntaje++;
    }if (x == 5 && y == 16)
    {
        tam -= 9; puntaje++;
    }if (x == 12 && y == 16)
    {
        tam -= 2; puntaje++;
    }if (x == 10 && y == 16)
    {
        tam -= 1; puntaje++;
    }if (x == 16 && y == 16)
    {
        tam -= 1; puntaje++;
    }if (x == 6 && y == 16)
    {
        tam -= 1; puntaje++;
    }if (x == 7 && y == 16)
    {
        tam -= 5; puntaje++;
    }if (x == 2 && y == 16)
    {
        tam -= 3; puntaje++;
    }if (x == 2 && y == 17)
    {
        tam -= 3; puntaje++;
    }if (x == 4 && y == 17)
    {
        tam -= 5; puntaje++;
    }if (x == 6 && y == 17)
    {
        tam -= 6; puntaje++;
    }if (x == 8 && y == 18)
    {
        tam += 6; puntaje++;
    }if (x == 10 && y == 18)
    {
        tam -= 7; puntaje++;
    }if (x == 12 && y == 19)
    {
        tam -= 3; puntaje++;
    }if (x == 14 && y == 18)
    {
        tam -= 2; puntaje++;
    }if (x == 16 && y == 19)
    {
        tam -= 1; puntaje++;
    }if (x == 18 && y == 18)
    {
        tam -= 1; puntaje++;
    }if (x == 4 && y == 20)
    {
        tam -= 5; puntaje++;
    }if (x == 8 && y == 20)
    {
        tam += 7; puntaje++;
    }if (x == 12 && y == 20)
    {
        tam -= 3; puntaje++;
    }if (x == 16 && y == 20)
    {
        tam -= 3; puntaje++;
    }if (x == 17 && y == 20)
    {
        tam += 8; puntaje++;
    }if (x == 17 && y == 21)
    {
        tam -= 5; puntaje++;
    }if (x == 10 && y == 21)
    {
        tam -= 7; puntaje++;
    }if (x == 11 && y == 21)
    {
        tam -= 4; puntaje++;
    }if (x == 4 && y == 21)
    {
        tam -= 2; puntaje++;
    }if (x == 5 && y == 21)
    {
        tam -= 9; puntaje++;
    }if (x == 14 && y == 22)
    {
        tam -= 9; puntaje++;
    }if (x == 12 && y == 22)
    {
        tam -= 7; puntaje++;
    }if (x == 18 && y == 22)
    {
        tam -= 3; puntaje++;
    }if (x == 2 && y == 22)
    {
        tam += 4; puntaje++;
    }if (x == 5 && y == 21)
    {
        tam -= 9; puntaje++;
    }if (x == 10 && y == 22)
    {
        tam -= 1; puntaje++;
    }if (x == 16 && y == 22)
    {
        tam -= 1; puntaje++;
    }if (x == 6 && y == 22)
    {
        tam -= 1; puntaje++;
    }if (x == 7 && y == 23)
    {
        tam -= 3; puntaje++;
    }if (x == 8 && y == 25)
    {
        tam -= 9; puntaje++;
    }if (x == 9 && y == 24)
    {
        tam -= 3; puntaje++;
    }if (x == 10 && y == 23)
    {
        tam -= 8; puntaje++;
    }if (x == 12 && y == 25)
    {
        tam -= 4; puntaje++;
    }if (x == 10 && y == 23)
    {
        tam -= 7; puntaje++;
    }if (x == 16 && y == 25)
    {
        tam += 5; puntaje++;
    }if (x == 6 && y == 23)
    {
        tam -= 6; puntaje++;
    }if (x == 4 && y == 27)
    {
        tam -= 6; puntaje++;
    }if (x == 5 && y == 27)
    {
        tam -= 3; puntaje++;
    }if (x == 15 && y == 27)
    {
        tam -= 2; puntaje++;
    }if (x == 16 && y == 27)
    {
        tam -= 9; puntaje++;
    }if (x == 17 && y == 27)
    {
        tam -= 4; puntaje++;
    }if (x == 2 && y == 28)
    {
        tam -= 5; puntaje++;
    }if (x == 5 && y == 28)
    {
        tam += 5; puntaje++;
    }if (x == 8 && y == 28)
    {
        tam += 9; puntaje++;
    }if (x == 11 && y == 28)
    {
        tam -= 8; puntaje++;
    }if (x == 14 && y == 28)
    {
        tam -= 8; puntaje++;
    }if (x == 4 && y == 29)
    {
        tam -= 1; puntaje++;
    }if (x == 8 && y == 29)
    {
        tam -= 2; puntaje++;
    }if (x == 12 && y == 30)
    {
        tam -= 3; puntaje++;
    }if (x == 16 && y == 30)
    {
        tam -= 4; puntaje++;
    }if (x == 17 && y == 29)
    {
        tam -= 5; puntaje++;
    }if (x == 17 && y == 31)
    {
        tam -= 6; puntaje++;
    }if (x == 10 && y == 31)
    {
        tam -= 7; puntaje++;
    }if (x == 11 && y == 31)
    {
        tam += 8; puntaje++;
    }if (x == 4 && y == 31)
    {
        tam -= 9; puntaje++;
    }if (x == 14 && y == 33)
    {
        tam -= 9; puntaje++;
    }if (x == 12 && y == 33)
    {
        tam -= 8; puntaje++;
    }if (x == 18 && y == 33)
    {
        tam -= 7; puntaje++;
    }if (x == 2 && y == 33)
    {
        tam -= 6; puntaje++;
    }if (x == 2 && y == 38)
    {
        tam -= 5; puntaje++;
    }if (x == 3 && y == 37)
    {
        tam -= 3; puntaje++;
    }if (x == 4 && y == 36)
    {
        tam -= 4; puntaje++;
    }if (x == 5 && y == 35)
    {
        tam -= 7; puntaje++;
    }if (x == 6 && y == 34)
    {
        tam -= 8; puntaje++;
    }if (x == 19 && y == 38)
    {
        tam += 2; puntaje++;
    }if (x == 18 && y == 37)
    {
        tam -= 1; puntaje++;
    }if (x == 17 && y == 36)
    {
        tam -= 3; puntaje++;
    }if (x == 16 && y == 35)
    {
        tam -= 5; puntaje++;
    }if (x == 15 && y == 34)
    {
        tam -= 8; puntaje++;
    }if (x == 16 && y == 38)
    {
        tam -= 3; puntaje++;
    }if (x == 13 && y == 38)
    {
        tam += 8; puntaje++;
    }if (x == 8 && y == 38)
    {
        tam -= 3; puntaje++;
    }if (x == 13 && y == 39)
    {
        tam -= 1; puntaje++;
    }if (x == 2 && y == 37)
    {
        tam -= 2; puntaje++;
    }if (x == 9 && y == 37)
    {
        tam -= 2; puntaje++;
    }if (x == 10 && y == 36)
    {
        tam += 3; puntaje++;
    }if (x == 11 && y == 35)
    {
        tam -= 5; puntaje++;
    }if (x == 9 && y == 34)
    {
        tam -= 8; puntaje++;
    }

}


bool perder(int nivel)
{
    if (nivel == 1) {
        if (y == 45 || x == 2 || x == 21)
            return false;
        for (int j = tam - 1; j > 0; j--) {
            if (cuerpo[j][0] == x && cuerpo[j][1] == y)
                return false;
        }
        if (tam < 1 || tam == 0) return false;
        return true;
    }
    if (nivel == 2) {
        if (y == 45 || x == 1 || x == 20)
            return false;
        for (int j = tam - 1; j > 0; j--) {
            if (cuerpo[j][0] == x && cuerpo[j][1] == y)
                return false;
        }
        if (tam < 1 || tam == 0) return false;
        return true;
    }


}

void WIN() {

    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 75; ++j) {
            Console::SetCursorPosition(j, i);
            if (cuadroF[i][j] == 0) {
                Console::ForegroundColor = ConsoleColor::Black;
                cout << (char)219;
            }
            else if (cuadroF[i][j] == 1) {
                Console::ForegroundColor = ConsoleColor::DarkBlue;
                cout << (char)219;
            }
            else if (cuadroF[i][j] == 2) {
                Console::ForegroundColor = ConsoleColor::DarkYellow;
                cout << (char)219;
            }
            else if (cuadroF[i][j] == 3) {
                Console::ForegroundColor = ConsoleColor::DarkRed;
                cout << (char)219;
            }
        }
    }
    getch();
    system("cls");

}

void PERDISTE() {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 75; ++j) {
            Console::SetCursorPosition(j, i);
            if (Derrota[i][j] == 0) {
                Console::ForegroundColor = ConsoleColor::Black;
                cout << (char)219;
            }
            else if (Derrota[i][j] == 1) {
                Console::ForegroundColor = ConsoleColor::DarkBlue;
                cout << (char)219;
            }
            else if (Derrota[i][j] == 2) {
                Console::ForegroundColor = ConsoleColor::DarkRed;
                cout << (char)219;
            }
            else if (Derrota[i][j] == 3) {
                Console::ForegroundColor = ConsoleColor::DarkRed;
                cout << (char)219;
            }
        }
    }
}


int main() {
    int nivel, vidas;
    OcultaCursor();
    mostrar_caratula();
    nivel = Elegir_Dificultad(vidas);
    if (nivel == 1) {
        mostrar_instrucciones();
        mostrar_NIVEL1();
    }if (nivel == 2) {
        mostrar_instrucciones();
        mostrar_NIVEL2();
    }
    while (tecla != ESC && perder(nivel))

    {
        mostrar_puntaje(vidas);
        borrar_cuerpo();
        guardar_posicion();
        dibujar_cuerpo();
        if (nivel == 2) {
            comer2();
        }if (nivel == 1) {
            comer1();
        }
        teclear();
        teclear();
        if (dir == 1) y--;
        if (dir == 2) y++;
        if (dir == 3) x++;
        if (dir == 4) x--;
        Sleep(velocidad);
        //GANAR();
        if (y == 1) {
            system("cls");
            WIN();
        }
    }
    system("cls");
    PERDISTE();
    getch();
    return 0;
}