#include "Estructuras.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

// JSON

JsonValor::JsonValor() : tipo(JsonTipo::NUMERO), valorNumero(0) {}

JsonValor JsonValor::crearTexto(const std::string& s) {
    JsonValor v;
    v.tipo = JsonTipo::TEXTO;
    v.valorTexto = s;
    return v;
}

JsonValor JsonValor::crearNumero(double n) {
    JsonValor v;
    v.tipo = JsonTipo::NUMERO;
    v.valorNumero = n;
    return v;
}

JsonValor JsonValor::crearArreglo() {
    JsonValor v;
    v.tipo = JsonTipo::ARREGLO;
    return v;
}

JsonValor JsonValor::crearObjeto() {
    JsonValor v;
    v.tipo = JsonTipo::OBJETO;
    return v;
}

void JsonValor::agregar(const JsonValor& v) {
    valorArreglo.push_back(v);
}

void JsonValor::agregar(const std::string& clave, const JsonValor& v) {
    valorObjeto.push_back(std::make_pair(clave, v));
}

const JsonValor* JsonValor::obtener(const std::string& clave) const {
    for (size_t i = 0; i < valorObjeto.size(); i++) {
        if (valorObjeto[i].first == clave) return &valorObjeto[i].second;
    }
    return nullptr;
}

static std::string escaparTexto(const std::string& s) {
    std::string resultado;
    for (char c : s) {
        if (c == '"' || c == '\\') resultado += '\\';
        resultado += c;
    }
    return resultado;
}

static std::string formatearNumero(double valor) {
    std::ostringstream oss;
    if (valor == (long long)valor) {
        oss << (long long)valor;
    } else {
        oss << valor;
    }
    return oss.str();
}

static void serializar(const JsonValor& v, std::ostringstream& out, int indent) {
    std::string sangria(indent * 2, ' ');
    std::string sangriaInterna((indent + 1) * 2, ' ');

    switch (v.tipo) {
        case JsonTipo::NUMERO:
            out << formatearNumero(v.valorNumero);
            break;
        case JsonTipo::TEXTO:
            out << "\"" << escaparTexto(v.valorTexto) << "\"";
            break;
        case JsonTipo::ARREGLO:
            if (v.valorArreglo.empty()) {
                out << "[]";
            } else {
                out << "[\n";
                for (size_t i = 0; i < v.valorArreglo.size(); i++) {
                    out << sangriaInterna;
                    serializar(v.valorArreglo[i], out, indent + 1);
                    if (i != v.valorArreglo.size() - 1) out << ",";
                    out << "\n";
                }
                out << sangria << "]";
            }
            break;
        case JsonTipo::OBJETO:
            if (v.valorObjeto.empty()) {
                out << "{}";
            } else {
                out << "{\n";
                for (size_t i = 0; i < v.valorObjeto.size(); i++) {
                    out << sangriaInterna << "\"" << escaparTexto(v.valorObjeto[i].first) << "\": ";
                    serializar(v.valorObjeto[i].second, out, indent + 1);
                    if (i != v.valorObjeto.size() - 1) out << ",";
                    out << "\n";
                }
                out << sangria << "}";
            }
            break;
    }
}

std::string JsonValor::aTexto() const {
    std::ostringstream out;
    serializar(*this, out, 0);
    return out.str();
}

static void saltarEspacios(const std::string& s, size_t& i) {
    while (i < s.size() && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) i++;
}

static JsonValor parsearValor(const std::string& s, size_t& i);

static std::string parsearTexto(const std::string& s, size_t& i) {
    std::string resultado;
    i++; // saltar comilla inicial
    while (i < s.size() && s[i] != '"') {
        if (s[i] == '\\' && i + 1 < s.size()) {
            i++;
            resultado += s[i];
        } else {
            resultado += s[i];
        }
        i++;
    }
    i++; // saltar comilla final
    return resultado;
}

static JsonValor parsearArreglo(const std::string& s, size_t& i) {
    JsonValor v = JsonValor::crearArreglo();
    i++; // saltar '['
    saltarEspacios(s, i);
    if (i < s.size() && s[i] == ']') { i++; return v; }

    while (i < s.size()) {
        saltarEspacios(s, i);
        v.agregar(parsearValor(s, i));
        saltarEspacios(s, i);
        if (i < s.size() && s[i] == ',') { i++; continue; }
        if (i < s.size() && s[i] == ']') { i++; break; }
        break;
    }
    return v;
}

static JsonValor parsearObjeto(const std::string& s, size_t& i) {
    JsonValor v = JsonValor::crearObjeto();
    i++; // saltar '{'
    saltarEspacios(s, i);
    if (i < s.size() && s[i] == '}') { i++; return v; }

    while (i < s.size()) {
        saltarEspacios(s, i);
        std::string clave = parsearTexto(s, i);
        saltarEspacios(s, i);
        if (i < s.size() && s[i] == ':') i++;
        saltarEspacios(s, i);
        JsonValor val = parsearValor(s, i);
        v.agregar(clave, val);
        saltarEspacios(s, i);
        if (i < s.size() && s[i] == ',') { i++; continue; }
        if (i < s.size() && s[i] == '}') { i++; break; }
        break;
    }
    return v;
}

static JsonValor parsearValor(const std::string& s, size_t& i) {
    saltarEspacios(s, i);
    if (i >= s.size()) return JsonValor();

    char c = s[i];
    if (c == '{') return parsearObjeto(s, i);
    if (c == '[') return parsearArreglo(s, i);
    if (c == '"') return JsonValor::crearTexto(parsearTexto(s, i));

    // numero
    size_t inicio = i;
    while (i < s.size() && (isdigit((unsigned char)s[i]) || s[i] == '-' || s[i] == '+' || s[i] == '.' || s[i] == 'e' || s[i] == 'E')) i++;
    std::string numStr = s.substr(inicio, i - inicio);
    if (numStr.empty()) { i++; return JsonValor(); }
    return JsonValor::crearNumero(std::stod(numStr));
}

JsonValor JsonValor::parsear(const std::string& texto) {
    size_t i = 0;
    return parsearValor(texto, i);
}

//lógica de grafo y digrafo en conjunto

Grafo::Grafo(string nombreArchivo, bool esDirigido) {
    archivo = nombreArchivo;
    dirigido = esDirigido;
    cargar();
}

double Grafo::aMetros(double valor, const string& unidad) const {
    if (unidad == "cm") return valor * 0.01;
    if (unidad == "km") return valor * 1000.0;
    return valor; 
}

double Grafo::aSegundos(double valor, const string& unidad) const {
    if (unidad == "min") return valor * 60.0;
    if (unidad == "h") return valor * 3600.0;
    return valor; 
}

bool Grafo::existeArista(const string& a, const string& b) const {
    return buscarArista(a, b) != nullptr;
}

const Arista* Grafo::buscarArista(const string& a, const string& b) const {
    auto it = adyacencia.find(a);
    if (it == adyacencia.end()) return nullptr;
    for (const Arista& ar : it->second) {
        if (ar.destino == b) return &ar;
    }
    return nullptr;
}

void Grafo::agregarNodo(const string& nodo) {
    if (adyacencia.count(nodo)) {
        cout << "El nodo \"" << nodo << "\" ya existe.\n";
        return;
    }
    adyacencia[nodo];
    guardar();
    cout << "Nodo \"" << nodo << "\" agregado y guardado en " << archivo << "\n";
}

void Grafo::eliminarNodo(const string& nodo) {
    if (!adyacencia.count(nodo)) {
        cout << "El nodo \"" << nodo << "\" no existe.\n";
        return;
    }
    // quita cualquier arista que apunte hacia este nodo, sin importar si es dirigido o no
    for (auto& par : adyacencia) {
        auto& vecinos = par.second;
        vecinos.erase(remove_if(vecinos.begin(), vecinos.end(),
            [&](const Arista& ar) { return ar.destino == nodo; }), vecinos.end());
    }
    adyacencia.erase(nodo);
    guardar();
    cout << "Nodo \"" << nodo << "\" eliminado y guardado en " << archivo << "\n";
}

void Grafo::agregarArista(const string& a, const string& b,
                                    double distValor, const string& distUnidad,
                                    double tiempoValor, const string& tiempoUnidad) {
    if (existeArista(a, b)) {
        cout << "La arista " << a << (dirigido ? " -> " : "-") << b << " ya existe.\n";
        return;
    }

    Arista ar;
    ar.destino = b;
    ar.distanciaValor = distValor;
    ar.distanciaUnidad = distUnidad;
    ar.distanciaMetros = aMetros(distValor, distUnidad);
    ar.tiempoValor = tiempoValor;
    ar.tiempoUnidad = tiempoUnidad;
    ar.tiempoSegundos = aSegundos(tiempoValor, tiempoUnidad);

    adyacencia[a].push_back(ar);

    if (!dirigido) {
        Arista inversa = ar;
        inversa.destino = a;
        adyacencia[b].push_back(inversa);
    } else {
        adyacencia[b]; // asegura que el destino tambien quede registrado como nodo
    }

    guardar();
    cout << "Arista " << a << (dirigido ? " -> " : "-") << b << " agregada (distancia: " << distValor << " " << distUnidad
         << ", tiempo: " << tiempoValor << " " << tiempoUnidad << ") y guardada en " << archivo << "\n";
}

void Grafo::eliminarArista(const string& a, const string& b) {
    if (!existeArista(a, b)) {
        cout << "La arista " << a << (dirigido ? " -> " : "-") << b << " no existe.\n";
        return;
    }
    auto& va = adyacencia[a];
    va.erase(remove_if(va.begin(), va.end(), [&](const Arista& ar) { return ar.destino == b; }), va.end());

    if (!dirigido) {
        auto& vb = adyacencia[b];
        vb.erase(remove_if(vb.begin(), vb.end(), [&](const Arista& ar) { return ar.destino == a; }), vb.end());
    }

    guardar();
    cout << "Arista " << a << (dirigido ? " -> " : "-") << b << " eliminada y guardada en " << archivo << "\n";
}

void Grafo::mostrarGrafo() const {
    if (adyacencia.empty()) {
        cout << "\nEl " << (dirigido ? "digrafo" : "grafo") << " esta vacio.\n";
        return;
    }
    cout << "\n--- " << (dirigido ? "Digrafo" : "Grafo") << " actual ---\n";
    for (const auto& par : adyacencia) {
        cout << par.first << " -> ";
        if (par.second.empty()) {
            cout << (dirigido ? "(sin salidas)" : "(sin conexiones)");
        } else {
            for (size_t i = 0; i < par.second.size(); i++) {
                const Arista& ar = par.second[i];
                cout << ar.destino << " [" << ar.distanciaValor << " " << ar.distanciaUnidad
                     << ", " << ar.tiempoValor << " " << ar.tiempoUnidad << "]";
                if (i != par.second.size() - 1) cout << ", ";
            }
        }
        cout << "\n";
    }
}

ResultadoCamino Grafo::dijkstra(const string& origen, const string& destino, bool usarTiempo) const {
    ResultadoCamino resultado;
    resultado.encontrado = false;

    map<string, double> dist;
    map<string, string> previo;
    map<string, bool> visitado;

    for (const auto& par : adyacencia) dist[par.first] = numeric_limits<double>::infinity();
    dist[origen] = 0;

    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> cola;
    cola.push(make_pair(0.0, origen));

    while (!cola.empty()) {
        pair<double, string> top = cola.top();
        cola.pop();
        double dActual = top.first;
        string actual = top.second;

        if (visitado[actual]) continue;
        visitado[actual] = true;
        if (actual == destino) break;

        for (const Arista& ar : adyacencia.at(actual)) {
            double peso = usarTiempo ? ar.tiempoSegundos : ar.distanciaMetros;
            double nueva = dActual + peso;
            if (nueva < dist[ar.destino]) {
                dist[ar.destino] = nueva;
                previo[ar.destino] = actual;
                cola.push(make_pair(nueva, ar.destino));
            }
        }
    }

    if (dist.find(destino) == dist.end() || dist[destino] == numeric_limits<double>::infinity()) {
        return resultado; // no se encontro camino
    }

    resultado.encontrado = true;
    resultado.total = dist[destino];

    vector<string> camino;
    string nodo = destino;
    while (nodo != origen) {
        camino.push_back(nodo);
        nodo = previo[nodo];
    }
    camino.push_back(origen);
    reverse(camino.begin(), camino.end());
    resultado.camino = camino;

    return resultado;
}

void Grafo::mostrarResultado(const ResultadoCamino& resultado, bool esTiempo) const {
    string etiqueta = esTiempo ? "tiempo" : "distancia";
    string unidadBase = esTiempo ? "segundos" : "metros";

    if (!resultado.encontrado) {
        cout << "No existe un camino (criterio: " << etiqueta << ").\n";
        return;
    }

    cout << "Camino mas conveniente por " << etiqueta << ": ";
    for (size_t i = 0; i < resultado.camino.size(); i++) {
        cout << resultado.camino[i];
        if (i + 1 < resultado.camino.size()) {
            const Arista* ar = buscarArista(resultado.camino[i], resultado.camino[i + 1]);
            if (ar != nullptr) {
                if (esTiempo) cout << " -[" << ar->tiempoValor << " " << ar->tiempoUnidad << "]-> ";
                else cout << " -[" << ar->distanciaValor << " " << ar->distanciaUnidad << "]-> ";
            } else {
                cout << " -> ";
            }
        }
    }
    cout << "\nTotal: " << resultado.total << " " << unidadBase << "\n";
}

void Grafo::mostrarCamino(const string& origen, const string& destino) const {
    if (!adyacencia.count(origen) || !adyacencia.count(destino)) {
        cout << "Uno o ambos nodos no existen en el " << (dirigido ? "digrafo" : "grafo") << ".\n";
        return;
    }
    if (origen == destino) {
        cout << "Ya estas en el nodo \"" << origen << "\".\n";
        return;
    }

    for (int i = 0; i < 2; i++) {
        bool esTiempo = (i == 1);
        mostrarResultado(dijkstra(origen, destino, esTiempo), esTiempo);
        if (i == 0) cout << "\n";
    }
}

void Grafo::guardar() {
    JsonValor raiz = JsonValor::crearObjeto();

    JsonValor nodos = JsonValor::crearArreglo();
    for (const auto& par : adyacencia) nodos.agregar(JsonValor::crearTexto(par.first));
    raiz.agregar("nodos", nodos);

    JsonValor aristas = JsonValor::crearArreglo();
    for (const auto& par : adyacencia) {
        for (const Arista& ar : par.second) {
            // si no es dirigido, evita guardar cada arista dos veces (A-B y B-A)
            if (dirigido || par.first < ar.destino) {
                JsonValor a = JsonValor::crearObjeto();
                a.agregar("origen", JsonValor::crearTexto(par.first));
                a.agregar("destino", JsonValor::crearTexto(ar.destino));

                JsonValor dist = JsonValor::crearObjeto();
                dist.agregar("valor", JsonValor::crearNumero(ar.distanciaValor));
                dist.agregar("unidad", JsonValor::crearTexto(ar.distanciaUnidad));
                a.agregar("distancia", dist);

                JsonValor tiempo = JsonValor::crearObjeto();
                tiempo.agregar("valor", JsonValor::crearNumero(ar.tiempoValor));
                tiempo.agregar("unidad", JsonValor::crearTexto(ar.tiempoUnidad));
                a.agregar("tiempo", tiempo);

                aristas.agregar(a);
            }
        }
    }
    raiz.agregar("aristas", aristas);

    ofstream out(archivo);
    out << raiz.aTexto();
}

void Grafo::cargar() {
    ifstream in(archivo);
    if (!in.is_open()) return; // todavia no existe, se creara al guardar por primera vez

    stringstream buffer;
    buffer << in.rdbuf();
    string contenido = buffer.str();
    if (contenido.empty()) return;

    JsonValor raiz = JsonValor::parsear(contenido);

    const JsonValor* nodos = raiz.obtener("nodos");
    if (nodos != nullptr) {
        for (const JsonValor& n : nodos->valorArreglo) {
            adyacencia[n.valorTexto];
        }
    }

    const JsonValor* aristas = raiz.obtener("aristas");
    if (aristas != nullptr) {
        for (const JsonValor& a : aristas->valorArreglo) {
            const JsonValor* origenV = a.obtener("origen");
            const JsonValor* destinoV = a.obtener("destino");
            const JsonValor* distV = a.obtener("distancia");
            const JsonValor* tiempoV = a.obtener("tiempo");
            if (!origenV || !destinoV || !distV || !tiempoV) continue;

            string origen = origenV->valorTexto;
            string destino = destinoV->valorTexto;
            double distValor = distV->obtener("valor")->valorNumero;
            string distUnidad = distV->obtener("unidad")->valorTexto;
            double tiempoValor = tiempoV->obtener("valor")->valorNumero;
            string tiempoUnidad = tiempoV->obtener("unidad")->valorTexto;

            Arista ab;
            ab.destino = destino;
            ab.distanciaValor = distValor;
            ab.distanciaUnidad = distUnidad;
            ab.distanciaMetros = aMetros(distValor, distUnidad);
            ab.tiempoValor = tiempoValor;
            ab.tiempoUnidad = tiempoUnidad;
            ab.tiempoSegundos = aSegundos(tiempoValor, tiempoUnidad);

            adyacencia[origen].push_back(ab);

            if (!dirigido) {
                Arista ba = ab;
                ba.destino = origen;
                adyacencia[destino].push_back(ba);
            } else {
                adyacencia[destino]; // asegura que el destino quede registrado
            }
        }
    }
}

//árbol

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

    JsonValor raizJson = JsonValor::crearObjeto();
    JsonValor arreglo = JsonValor::crearArreglo();
    for (const string& valor : resultado) arreglo.agregar(JsonValor::crearTexto(valor));
    raizJson.agregar("valores_preorder", arreglo);

    ofstream out(archivo);
    out << raizJson.aTexto();
}

void Arbol::cargar() {
    ifstream in(archivo);
    if (!in.is_open()) return; // todavia no existe, se creara al guardar por primera vez

    stringstream buffer;
    buffer << in.rdbuf();
    string contenido = buffer.str();
    if (contenido.empty()) return;

    JsonValor raizJson = JsonValor::parsear(contenido);
    const JsonValor* arreglo = raizJson.obtener("valores_preorder");
    if (arreglo == nullptr) return;

    for (const JsonValor& v : arreglo->valorArreglo) {
        bool insertado;
        raiz = insertarAux(raiz, v.valorTexto, insertado);
    }
}
