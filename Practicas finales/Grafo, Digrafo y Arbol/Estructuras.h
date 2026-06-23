#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>
#include <vector>
#include <map>
#include <utility>

// JSON

enum class JsonTipo { NUMERO, TEXTO, ARREGLO, OBJETO };

class JsonValor {
public:
    JsonTipo tipo;
    double valorNumero;
    std::string valorTexto;
    std::vector<JsonValor> valorArreglo;
    std::vector<std::pair<std::string, JsonValor>> valorObjeto; // conserva el orden de insercion

    JsonValor();

    static JsonValor crearTexto(const std::string& s);
    static JsonValor crearNumero(double n);
    static JsonValor crearArreglo();
    static JsonValor crearObjeto();

    void agregar(const JsonValor& v);                            // para arreglos
    void agregar(const std::string& clave, const JsonValor& v);  // para objetos

    const JsonValor* obtener(const std::string& clave) const;    // busca una clave dentro de un objeto
    std::string aTexto() const;                                  // serializa este valor a un string JSON legible

    static JsonValor parsear(const std::string& texto);          // convierte un string JSON en un JsonValor
};

// Garfo y digrafo

struct Arista {
    std::string destino;
    double distanciaValor;
    std::string distanciaUnidad;
    double distanciaMetros;   
    double tiempoValor;
    std::string tiempoUnidad;
    double tiempoSegundos;    
};

struct ResultadoCamino {
    bool encontrado;
    double total;
    std::vector<std::string> camino;
};

class Grafo {
private:
    std::map<std::string, std::vector<Arista>> adyacencia;
    std::string archivo;
    bool dirigido;

    bool existeArista(const std::string& a, const std::string& b) const;
    double aMetros(double valor, const std::string& unidad) const;
    double aSegundos(double valor, const std::string& unidad) const;
    const Arista* buscarArista(const std::string& a, const std::string& b) const;
    ResultadoCamino dijkstra(const std::string& origen, const std::string& destino, bool usarTiempo) const;
    void mostrarResultado(const ResultadoCamino& resultado, bool esTiempo) const;

    void guardar();
    void cargar();

public:
    Grafo(std::string nombreArchivo, bool esDirigido);

    void agregarNodo(const std::string& nodo);
    void eliminarNodo(const std::string& nodo);
    void agregarArista(const std::string& a, const std::string& b,
                        double distValor, const std::string& distUnidad,
                        double tiempoValor, const std::string& tiempoUnidad);
    void eliminarArista(const std::string& a, const std::string& b);

    void mostrarGrafo() const;
    void mostrarCamino(const std::string& origen, const std::string& destino) const;
};

////árbol

struct NodoArbol {
    std::string valor;
    NodoArbol* izquierdo;
    NodoArbol* derecho;
    NodoArbol(const std::string& v) : valor(v), izquierdo(nullptr), derecho(nullptr) {}
};

class Arbol {
private:
    NodoArbol* raiz;
    std::string archivo;

    bool esNumero(const std::string& s) const;
    int comparar(const std::string& a, const std::string& b) const;

    NodoArbol* insertarAux(NodoArbol* nodo, const std::string& valor, bool& insertado);
    NodoArbol* eliminarAux(NodoArbol* nodo, const std::string& valor, bool& eliminado);
    bool buscarAux(NodoArbol* nodo, const std::string& valor) const;
    NodoArbol* encontrarMinimo(NodoArbol* nodo) const;
    void liberarArbol(NodoArbol* nodo);
    int alturaAux(NodoArbol* nodo) const;

    // tipo: 0 = preorder, 1 = inorder, 2 = postorder
    void recorrerAux(NodoArbol* nodo, int tipo, std::vector<std::string>& resultado) const;
    void mostrarRecorrido(int tipo, const std::string& titulo) const;

    void guardar();
    void cargar();

public:
    Arbol(const std::string& nombreArchivo = "arbol.json");
    ~Arbol();

    void insertar(const std::string& valor);
    void eliminar(const std::string& valor);
    bool buscar(const std::string& valor) const;

    void mostrarPreorder() const;
    void mostrarInorder() const;
    void mostrarPostorder() const;

    void mostrarAltura() const;
    void mostrarProfundidad(const std::string& valor) const;
    void mostrarAmplitud() const;
};

#endif
