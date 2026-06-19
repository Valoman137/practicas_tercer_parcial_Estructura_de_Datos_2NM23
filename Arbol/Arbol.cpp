#include "Arbol.h"
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

Arbol::Arbol(const string& nombreArchivo) {
    raiz = nullptr;
    archivo = nombreArchivo;
    cargar();
}

Arbol::~Arbol() {
    liberarArbol(raiz);
}

void Arbol::liberarArbol(NodoArbol* nodo) {
    if (nodo == nullptr) return;
    liberarArbol(nodo->izquierdo);
    liberarArbol(nodo->derecho);
    delete nodo;
}

bool Arbol::esNumero(const string& s) const {
    if (s.empty()) return false;
    try {
        size_t pos;
        stod(s, &pos);
        return pos == s.size(); // toda la cadena debe ser un numero valido
    } catch (...) {
        return false;
    }
}

int Arbol::comparar(const string& a, const string& b) const {
    if (esNumero(a) && esNumero(b)) {
        double da = stod(a), db = stod(b);
        if (da < db) return -1;
        if (da > db) return 1;
        return 0;
    }
    // si alguno de los dos no es numero, se comparan como texto
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

NodoArbol* Arbol::insertarAux(NodoArbol* nodo, const string& valor, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoArbol(valor);
    }

    int cmp = comparar(valor, nodo->valor);
    if (cmp < 0) nodo->izquierdo = insertarAux(nodo->izquierdo, valor, insertado);
    else if (cmp > 0) nodo->derecho = insertarAux(nodo->derecho, valor, insertado);
    else insertado = false; // el valor ya existe, no se duplica

    return nodo;
}

void Arbol::insertar(const string& valor) {
    bool insertado = false;
    raiz = insertarAux(raiz, valor, insertado);

    if (insertado) {
        guardar();
        cout << "Valor \"" << valor << "\" insertado y guardado en " << archivo << "\n";
    } else {
        cout << "El valor \"" << valor << "\" ya existe en el arbol.\n";
    }
}

NodoArbol* Arbol::encontrarMinimo(NodoArbol* nodo) const {
    while (nodo->izquierdo != nullptr) nodo = nodo->izquierdo;
    return nodo;
}

NodoArbol* Arbol::eliminarAux(NodoArbol* nodo, const string& valor, bool& eliminado) {
    if (nodo == nullptr) {
        eliminado = false;
        return nullptr;
    }

    int cmp = comparar(valor, nodo->valor);
    if (cmp < 0) {
        nodo->izquierdo = eliminarAux(nodo->izquierdo, valor, eliminado);
    } else if (cmp > 0) {
        nodo->derecho = eliminarAux(nodo->derecho, valor, eliminado);
    } else {
        eliminado = true;

        if (nodo->izquierdo == nullptr) {
            NodoArbol* temp = nodo->derecho;
            delete nodo;
            return temp;
        }
        if (nodo->derecho == nullptr) {
            NodoArbol* temp = nodo->izquierdo;
            delete nodo;
            return temp;
        }

        // nodo con dos hijos: se reemplaza con el sucesor in-order
        NodoArbol* sucesor = encontrarMinimo(nodo->derecho);
        nodo->valor = sucesor->valor;
        bool aux;
        nodo->derecho = eliminarAux(nodo->derecho, sucesor->valor, aux);
    }

    return nodo;
}

void Arbol::eliminar(const string& valor) {
    bool eliminado = false;
    raiz = eliminarAux(raiz, valor, eliminado);

    if (eliminado) {
        guardar();
        cout << "Valor \"" << valor << "\" eliminado y guardado en " << archivo << "\n";
    } else {
        cout << "El valor \"" << valor << "\" no existe en el arbol.\n";
    }
}

bool Arbol::buscarAux(NodoArbol* nodo, const string& valor) const {
    if (nodo == nullptr) return false;

    int cmp = comparar(valor, nodo->valor);
    if (cmp == 0) return true;
    return cmp < 0 ? buscarAux(nodo->izquierdo, valor) : buscarAux(nodo->derecho, valor);
}

bool Arbol::buscar(const string& valor) const {
    return buscarAux(raiz, valor);
}

void Arbol::recorrerAux(NodoArbol* nodo, int tipo, vector<string>& resultado) const {
    if (nodo == nullptr) return;
    if (tipo == 0) resultado.push_back(nodo->valor); // preorder
    recorrerAux(nodo->izquierdo, tipo, resultado);
    if (tipo == 1) resultado.push_back(nodo->valor); // inorder
    recorrerAux(nodo->derecho, tipo, resultado);
    if (tipo == 2) resultado.push_back(nodo->valor); // postorder
}

void Arbol::mostrarRecorrido(int tipo, const string& titulo) const {
    vector<string> resultado;
    recorrerAux(raiz, tipo, resultado);

    cout << titulo << ": ";
    if (resultado.empty()) {
        cout << "(arbol vacio)";
    } else {
        for (size_t i = 0; i < resultado.size(); i++) {
            cout << resultado[i];
            if (i != resultado.size() - 1) cout << ", ";
        }
    }
    cout << "\n";
}

void Arbol::mostrarPreorder() const { mostrarRecorrido(0, "Recorrido Preorder"); }
void Arbol::mostrarInorder() const { mostrarRecorrido(1, "Recorrido Inorder"); }
void Arbol::mostrarPostorder() const { mostrarRecorrido(2, "Recorrido Postorder"); }

int Arbol::alturaAux(NodoArbol* nodo) const {
    if (nodo == nullptr) return 0;
    int izq = alturaAux(nodo->izquierdo);
    int der = alturaAux(nodo->derecho);
    return 1 + (izq > der ? izq : der);
}

void Arbol::mostrarAltura() const {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio.\n";
        return;
    }
    cout << "Altura del arbol: " << alturaAux(raiz) << "\n";
}

void Arbol::mostrarProfundidad(const string& valor) const {
    NodoArbol* actual = raiz;
    int profundidad = 0;

    while (actual != nullptr) {
        int cmp = comparar(valor, actual->valor);
        if (cmp == 0) {
            cout << "Profundidad de \"" << valor << "\": " << profundidad << "\n";
            return;
        }
        actual = (cmp < 0) ? actual->izquierdo : actual->derecho;
        profundidad++;
    }

    cout << "El valor \"" << valor << "\" no existe en el arbol.\n";
}

void Arbol::mostrarAmplitud() const {
    if (raiz == nullptr) {
        cout << "El arbol esta vacio.\n";
        return;
    }

    queue<NodoArbol*> cola;
    cola.push(raiz);
    int maxAncho = 0;

    while (!cola.empty()) {
        int nivelTam = (int)cola.size();
        if (nivelTam > maxAncho) maxAncho = nivelTam;

        for (int i = 0; i < nivelTam; i++) {
            NodoArbol* actual = cola.front();
            cola.pop();
            if (actual->izquierdo != nullptr) cola.push(actual->izquierdo);
            if (actual->derecho != nullptr) cola.push(actual->derecho);
        }
    }

    cout << "Amplitud (ancho maximo de un nivel): " << maxAncho << "\n";
}

void Arbol::guardar() {
    // se guarda el recorrido Preorder: reinsertando los valores en este mismo
    // orden se reconstruye exactamente la misma forma del arbol
    vector<string> resultado;
    recorrerAux(raiz, 0, resultado);

    ofstream out(archivo);
    out << "VALORES (preorder)\n";
    for (const string& valor : resultado) out << valor << "\n";
}

void Arbol::cargar() {
    ifstream in(archivo);
    if (!in.is_open()) return; // todavia no existe, se creara al guardar por primera vez

    string linea;
    bool primeraLinea = true;

    while (getline(in, linea)) {
        if (linea.empty()) continue;
        if (primeraLinea) { primeraLinea = false; continue; } // se salta el encabezado

        bool insertado;
        raiz = insertarAux(raiz, linea, insertado);
    }
}
