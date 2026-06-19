#ifndef DIGRAFO_H
#define DIGRAFO_H

#include <string>
#include <map>
#include <vector>

class Digrafo {
private:
    std::map<std::string, std::vector<std::string>> adyacencia;
    std::string archivo;

    bool existeArista(const std::string& a, const std::string& b) const;
    void guardar();
    void cargar();

public:
    Digrafo(std::string nombreArchivo = "digrafo.txt");

    void agregarNodo(const std::string& nodo);
    void eliminarNodo(const std::string& nodo);
    void agregarArista(const std::string& origen, const std::string& destino);
    void eliminarArista(const std::string& origen, const std::string& destino);

    void mostrarGrafo() const;
    void mostrarCamino(const std::string& origen, const std::string& destino) const;
};

#endif
