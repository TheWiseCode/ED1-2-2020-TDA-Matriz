// ---------------------------------------------------------------------------

#pragma hdrstop

#include "UMatrizVC.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

MatrizVC::MatrizVC() {
	df = dc = repe = nt = 0;
	vd = new int[df * dc];
	vc = new int[df * dc];
	vf = new int[df + 1];
	for(int i = 0; i < df + 1; i++)
		vf[i] = 1;
}

int MatrizVC::existe_elemento(int f, int c) {
    int lug_antes = 0;
    for(int i = 0;i < (f - 1); i++){
        lug_antes += (vf[i+1] - vf[i]);
    }
    int max_elem = vf[f + 1 - 1] - vf[f - 1];
    for(int i = 0;i < max_elem; i++){
        if(vc[lug_antes + i] == c)
            return lug_antes + i;
    }
    return -1;
} // busca en vd,vc y vf si existe el elemento

int MatrizVC::donde_insertar(int f, int c) {
    int lug_antes = 0;
    for(int i = 0;i < (f - 1); i++){
        lug_antes += (vf[i+1] - vf[i]);
    }
    int nuevo_lugar = lug_antes;
    int lugar = lug_antes;
    int max_elem = vf[f + 1 - 1] - vf[f - 1];
    for(int i = 0; i < max_elem; i++){
        lugar = lug_antes + i;
        if(c > vc[lugar])
            nuevo_lugar = lugar;
    }
	return nuevo_lugar;
} // determina donde insertar en vd,vc y vf

void MatrizVC::dimensionar(int f, int c) {
	df = f;
	dc = c;
    vd = new int[df * dc];
	vc = new int[df * dc];
	vf = new int[df + 1];
	for(int i = 0; i < df + 1; i++)
		vf[i] = 1;
}

int MatrizVC::dimension_fila() {
    return df;
}

int MatrizVC::dimension_columna() {
    return dc;
}

void MatrizVC::poner(int f, int c, int valor) {
    if (f >= 1 && f <= df && c >= 1 && c <= dc) {
        int lugar = existe_elemento(f, c);
        if(lugar != -1){
            vd[lugar] = valor;
            //Analizar si valor == repe
            if(valor == repe){
                for(int i = lugar; i < nt;i ++){
                    vd[i] = vd[i+1];
                    vc[i] = vc[i+1];
                }
                for(int i = f; i < df + 1; i++)
                   vf[i]--;
                nt--;
            }
        }else{
			int pos = donde_insertar(f, c);
			for(int i = nt; i > pos; i--){
				vd[i] = vd[i - 1];
				vc[i] = vc[i - 1];
			}
			vd[pos] = valor;
			vc[pos] = c;
			nt++;
			for(int i = f; i < df + 1; i++)
                vf[i]++;
        }
    }

}

int MatrizVC::elemento(int f, int c) {
    if (f >= 1 && f <= df && c >= 1 && c <= dc) {
        int lugar = existe_elemento(f, c);
        if(lugar == -1)
            return repe;
        else
            return vd[lugar];
    }else
        cout<<"ERROR DE RANGO\n";
}

int MatrizVC::fila(int indiceVC){
    int c = 0;
    for(int i = 0; i < df; i++){
        int m = vf[i + 1] - vf[i];
        int n = c + m;
        if(indiceVC >= c && indiceVC < n)
            return i + 1;
        c += m;
    }
}

void MatrizVC::definfir_valor_repetido(int valor) {
    repe = valor;
    int i = 0;
	while (i < nt) {
		if (vd[i] == valor) {
			for (int j = i; j < nt; j++) {
				vc[j] = vc[j + 1];
				vd[j] = vd[j + 1];
			}
            int f = fila(i);
            for(int i = f;i < df + 1; i++)
                vf[i]--;
			nt--;
		}else
			i++;
	}
}

string MatrizVC::to_str() {
    string r = "";
	for (int i = 1; i <= df; i++) {
		r += "| ";
		for (int j = 1; j <= dc; j++) {
			int e = elemento(i, j);
			r += to_string(e) + "  ";
		}
		r += "|\n";
	}
    int max = df * dc;
	r += "vd: ";
	for (int i = 0; i < max; i++)
		r += to_string(vd[i]) + ",";
	r += "\nvc: ";
	for (int i = 0; i < max; i++)
		r += to_string(vc[i]) + ",";
	r += "\nvf: ";
	for (int i = 0; i < df+ 1; i++)
		r += to_string(vf[i]) + ",";
    return r;
}