#include <iostream>
#include "UMatrizV.h"
#include "UMatrizVC.h"

using namespace std;

int main() {
	MatrizVC* m = new MatrizVC();
	m->dimensionar(5, 5);
	m->poner(1, 1, 1);
	m->poner(2, 2, 64);
	m->poner(1, 3, 80);
	m->poner(4, 4, 1);
	m->poner(5, 5, 1);
	m->poner(2, 2, 0);
	cout << m->to_str() << endl;
	///	m->poner(4, 4, 0);
	m->definfir_valor_repetido(1);
	cout << m->to_str() << endl;
	system("pause");
	return 0;
}