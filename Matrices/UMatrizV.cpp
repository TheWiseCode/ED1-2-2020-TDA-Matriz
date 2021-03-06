// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UMatrizV.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

MatrizV::MatrizV() {
	/* df = 0;
	 dc = 0;
	 repe = 0;
	 nt = 0; */
	df = dc = repe = nt = 0;
	vf = new int[0];
	vc = new int[0];
	vd = new int[0];
}

void MatrizV::dimensionar(int f, int c) {
	df = f;
	dc = c;
	// MAX_MV = f * c;
	// Se vacian los vectores
	/*
	 vf = new int[MAX_MV];
	 vc = new int[MAX_MV];
	 vd = new int[MAX_MV]; */
	vf = new int[df * dc];
	vc = new int[df * dc];
	vd = new int[df * dc];
}

int MatrizV::dimension_fila() {
	return df;
}

int MatrizV::dimension_columna() {
	return dc;
}

int MatrizV::posicion(int f, int c) {
	for (int i = 0; i < nt; i++) {
		if (vf[i] == f && vc[i] == c)
			return i;
	}
	return -1;
}

void MatrizV::poner(int f, int c, int valor) {
	if (f >= 1 && f <= df && c >= 1 && c <= dc) {
		int lugar = posicion(f, c);
		if (lugar == -1 && valor != repe && nt < (df * dc)) // nt < MAX_MV
		{ // insertar a lo ultimo
			vd[nt] = valor;
			vf[nt] = f;
			vc[nt] = c;
			nt++;
		}
		else {
			vd[lugar] = valor;
			if (valor == repe) {
				for (int i = lugar; i < nt; i++) {
					vf[i] = vf[i + 1];
					vc[i] = vc[i + 1];
					vd[i] = vd[i + 1];
				}
				nt--;
			}
		}
	}
}

int MatrizV::elemento(int f, int c) {
	if (f >= 1 && f <= df && c >= 1 && c <= dc) {
		int lugar = posicion(f, c);
		if (lugar >= 0)
			return vd[lugar];
		else
			return repe;
	}
	else
		cout << "ERROR FUERA DE RANGO\n";
}

void MatrizV::definir_valor_repetido(int valor) {
	repe = valor;
	//
	int i = 0;
	while (i < nt) {
		if (vd[i] == valor) {
			for (int j = i; j < nt; j++) {
				vf[j] = vf[j + 1];
				vc[j] = vc[j + 1];
				vd[j] = vd[j + 1];
			}
			nt--;
		}else
			i++;
	}
}

/*
 | 3 0 5 |
 | 0 1 0 |
 | 0 0 9 | */
string MatrizV::to_str() {
	string r = "";
	for (int i = 1; i <= df; i++) {
		r += "| ";
		for (int j = 1; j <= dc; j++) {
			int e = elemento(i, j);
			r += to_string(e) + "  ";
		}
		r += "|\n";
	}
	/*
	int max = df * dc;
	r += "vf: ";
	for (int i = 0; i < max; i++)
		r += to_string(vf[i]) + ",";
	r += "\nvc: ";
	for (int i = 0; i < max; i++)
		r += to_string(vc[i]) + ",";
	r += "\nvd: ";
	for (int i = 0; i < max; i++)
		r += to_string(vd[i]) + ",";
	*/
	return r;
}
