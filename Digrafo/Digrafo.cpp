#include "Digrafo.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

Digrafo::Digrafo(string nombreArchivo) {
    archivo = nombreArchivo;
    cargar();
}

bool Digrafo::existeArista(const string& a, const string& b) const {
    auto it = adyacencia.find(a);
    if (it == adyacencia.end()) return false;
    return find(it->second.begin(), it->second.end(), b) != it->second.end();
}

void Digrafo::agregarNodo(const string& nodo) {
    if (adyacencia.count(nodo)) {
        cout << "El nodo \"" << nodo << "\" ya existe.\n";
        return;
    }
    adyacencia[nodo];
    guardar();
    cout << "Nodo \"" << nodo << "\" agregado y guardado en " << archivo << "\n";
}

void Digrafo::eliminarNodo(const string& nodo) {
    if (!adyacencia.count(nodo)) {
        cout << "El nodo \"" << nodo << "\" no existe.\n";
        return;
    }
    for (auto& par : adyacencia) {
        auto& vecinos = par.second;
        vecinos.erase(remove(vecinos.begin(), vecinos.end(), nodo), vecinos.end());
    }
    adyacencia.erase(nodo);
    guardar();
    cout << "Nodo \"" << nodo << "\" eliminado y guardado en " << archivo << "\n";
}

void Digrafo::agregarArista(const string& origen, const string& destino) {
    if (existeArista(origen, destino)) {
        cout << "La arista " << origen << " -> " << destino << " ya existe.\n";
        return;
    }
    adyacencia[origen].push_back(destino);
    adyacencia[destino]; // asegura que el nodo destino tambien quede registrado
    guardar();
    cout << "Arista " << origen << " -> " << destino << " agregada y guardada en " << archivo << "\n";
}

void Digrafo::eliminarArista(const string& origen, const string& destino) {
    if (!existeArista(origen, destino)) {
        cout << "La arista " << origen << " -> " << destino << " no existe.\n";
        return;
    }
    auto& vecinos = adyacencia[origen];
    vecinos.erase(remove(vecinos.begin(), vecinos.end(), destino), vecinos.end());
    guardar();
    cout << "Arista " << origen << " -> " << destino << " eliminada y guardada en " << archivo << "\n";
}

void Digrafo::mostrarGrafo() const {
    if (adyacencia.empty()) {
        cout << "\nEl digrafo esta vacio.\n";
        return;
    }
    cout << "\n--- Digrafo actual ---\n";
    for (const auto& par : adyacencia) {
        cout << par.first << " -> ";
        if (par.second.empty()) {
            cout << "(sin salidas)";
        } else {
            for (size_t i = 0; i < par.second.size(); i++) {
                cout << par.second[i];
                if (i != par.second.size() - 1) cout << ", ";
            }
        }
        cout << "\n";
    }
}

void Digrafo::mostrarCamino(const string& origen, const string& destino) const {
    if (!adyacencia.count(origen) || !adyacencia.count(destino)) {
        cout << "Uno o ambos nodos no existen en el digrafo.\n";
        return;
    }
    if (origen == destino) {
        cout << "Camino de " << origen << " hacia " << destino << ": " << origen << "\n";
        return;
    }

    map<string, string> padre;
    map<string, bool> visitado;
    queue<string> cola;
    visitado[origen] = true;
    cola.push(origen);
    bool encontrado = false;

    while (!cola.empty() && !encontrado) {
        string actual = cola.front();
        cola.pop();
        for (const string& vecino : adyacencia.at(actual)) {
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                padre[vecino] = actual;
                if (vecino == destino) { encontrado = true; break; }
                cola.push(vecino);
            }
        }
    }

    if (!encontrado) {
        cout << "No existe un camino de " << origen << " hacia " << destino << ".\n";
        return;
    }

    vector<string> camino;
    string nodo = destino;
    while (nodo != origen) {
        camino.push_back(nodo);
        nodo = padre[nodo];
    }
    camino.push_back(origen);

    cout << "Camino de " << origen << " hacia " << destino << ": ";
    for (auto it = camino.rbegin(); it != camino.rend(); ++it) {
        cout << *it;
        if (it + 1 != camino.rend()) cout << " -> ";
    }
    cout << "\n";
}

void Digrafo::guardar() {
    ofstream out(archivo);

    out << "NODOS\n";
    for (const auto& par : adyacencia) out << par.first << "\n";

    out << "ARISTAS\n";
    for (const auto& par : adyacencia)
        for (const string& destino : par.second)
            out << par.first << "->" << destino << "\n";
}

void Digrafo::cargar() {
    ifstream in(archivo);
    if (!in.is_open()) return; // todavia no existe, se creara al guardar por primera vez

    string linea;
    bool leyendoAristas = false;

    while (getline(in, linea)) {
        if (linea.empty()) continue;
        if (linea == "NODOS") { leyendoAristas = false; continue; }
        if (linea == "ARISTAS") { leyendoAristas = true; continue; }

        if (!leyendoAristas) {
            adyacencia[linea];
        } else {
            size_t pos = linea.find("->");
            if (pos != string::npos) {
                string origen = linea.substr(0, pos);
                string destino = linea.substr(pos + 2);
                adyacencia[origen].push_back(destino);
                adyacencia[destino];
            }
        }
    }
}
