#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <map>
#include <vector>

class Grafo {
private:
    std::map<std::string, std::vector<std::string>> adyacencia;
    std::string archivo;

    bool existeArista(const std::string& a, const std::string& b) const;
    void guardar();
    void cargar();

public:
    Grafo(std::string nombreArchivo = "grafo.txt");

    void agregarNodo(const std::string& nodo);
    void eliminarNodo(const std::string& nodo);
    void agregarArista(const std::string& a, const std::string& b);
    void eliminarArista(const std::string& a, const std::string& b);

    void mostrarGrafo() const;
    void mostrarCamino(const std::string& origen, const std::string& destino) const;
};

#endif
