#ifndef ARBOL_H
#define ARBOL_H

#include <string>
#include <vector>

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
    Arbol(const std::string& nombreArchivo = "arbol.txt");
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
