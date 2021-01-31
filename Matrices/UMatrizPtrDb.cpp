//---------------------------------------------------------------------------

#pragma hdrstop

#include "UMatrizPtrDb.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

MatrizPD::MatrizPD(){
    ptrFil = NULL;
    df = dc = repe = 0;
    nt = 0;
}

void MatrizPD::dimensionar(int f,int c){
    df = f;
    dc = c;
}

int MatrizPD::dimension_fila(){
    return df;
}
int MatrizPD::dimension_columna(){
    return dc;
}

NodoMc* MatrizPD::buscar(int f, int c){
    NodoMf* auxf = ptrFil;
    while(auxf != NULL){
        if(auxf->fil == f){
            NodoMc* auxc = auxf->ptrCol;
            while(auxc != NULL){
                if(auxc->col == c)
                    return auxc;
                auxc = auxc->sigC;
            }
            return NULL;
        }
        auxf = auxf->sigF;
    }
    return NULL;
}

NodoMf* MatrizPD::buscar(int f){
    NodoMf* auxf = ptrFil;
    while(auxf != NULL){
        if(auxf->fil == f)
            return auxf;
        auxf = auxf->sigF;
    }
    return NULL;
}

NodoMf* MatrizPD::posicionIns(int f){
    NodoMf* aux = ptrFil;
    while(aux != NULL){
        if(f < aux->fil)
            return aux;
        aux = aux->sigF;
    }
    return NULL;
}

void MatrizPD::poner(int f, int c, int valor){
    if (f >= 1 && f <= df && c >= 1 && c <= dc) {
        NodoMc* dir = buscar(f, c);
        if(dir != NULL){
            dir->dato = valor;
            //Analizar si valor == repe
        }else{//Insercion nueva
            NodoMf* dirFila = buscar(f);
            if(dirFila != NULL){//Ya existe la fila
                NodoMc* x = new NodoMc;
                if (x != NULL) {
                    x->col = c;
                    x->dato = valor;
                    x->sigC = dirFila->ptrCol;
                    dirFila->ptrCol = x;
                }
                else
                    cout << "ERROR NO EXISTE ESPACIO DE MEMORIA\n";
            }else{//Insercion completamente nueva
                NodoMf* posF = posicionIns(f);
                NodoMf* xf = new NodoMf;
                xf->fil = f;
                xf->antF = NULL;
                xf->sigF = NULL;
                xf->ptrCol = NULL;
                if(posF == NULL){//Vacio todo o insercion a lo ultimo
                    if(ptrFil == NULL){//Vacio
                        ptrFil = xf;
                    }else{//A lo ultimo
                        NodoMf* fin = ptrFil;
                        while(fin->sigF != NULL)
                            fin = fin->sigF;
                        xf->antF = fin;
                        fin->sigF = xf;
                    }
                }else{
                    if(posF == ptrFil){//Inserta al incio
                        xf->sigF = ptrFil;
                        ptrFil->antF = xf;
                        ptrFil = xf;
                    }else{//Insercion por el medio
                        NodoMf* ant = posF->antF;
                        NodoMf* sig = posF;
                        xf->sigF = sig;
                        xf->antF = ant;
                        ant->sigF = xf;
                        sig->antF = xf;
                    }
                }
                NodoMc* xc = new NodoMc;
                if (xc != NULL) {
                    xc->col = c;
                    xc->dato = valor;
                    xc->sigC = xf->ptrCol;
                    xf->ptrCol = xc;
                }
                else
                    cout << "ERROR NO EXISTE ESPACIO DE MEMORIA\n";
            }
            nt++;
        }
    }
}

int MatrizPD::elemento(int f, int c){
    if (f >= 1 && f <= df && c >= 1 && c <= dc) {
        NodoMc* dir = buscar(f, c);
        if(dir != NULL)
            return dir->dato;
        else
            return repe;
    }
}

void MatrizPD:: definir_valor_repetido(int valor){
    repe = valor;
}

string MatrizPD::to_str(){
    	string r = "";
	for (int i = 1; i <= df; i++) {
		r += "| ";
		for (int j = 1; j <= dc; j++) {
			int e = elemento(i, j);
			r += to_string(e) + "  ";
		}
		r += "|\n";
	}
	r += "NT: " + to_string(nt) + "\n";
	return r;
}
