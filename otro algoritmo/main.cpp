#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

/**
 * Función que muestra los participantes del grupo
 */
void participantes();


/**
 *
 * @param fila una línea del archivo
 * @return vector con los puntajes. (0 -> rut)
 */
vector<int> obtenerPuntajes(std::string fila);

/**
 *
 * @param puntajes Arreglo con los valores
 * @return el promedio del elemento 1 - 7 (Recordar que 0 -> rut)
 */
double promediar(std::vector<int> puntajes);

int main(int argc, char** argv) {

    if (argc > 1) {
        std::string archivo(argv[1]);
        std::ifstream lectura(archivo);

        std::ofstream escritura("ordenado.csv");
        escritura.close();/**
        * Crean el arhivo y lo cierran de inmediato
        */

        std::ifstream lectura2;

        if (lectura) {

            int menor = 0;
            int mayor = 0;
            std::string linea2;
            std::ifstream lectura2;
            std::fstream escritura("ordenado.csv");

            for (std::string linea; getline(lectura,linea) ; ) {
                lectura2.open("ordenado.csv");
                escritura.open("ordenado.csv");
                std::vector<int> puntajes = obtenerPuntajes(linea);
                int rut = puntajes.at(0);
                //double promedio = promediar(puntajes);
                int promedio = puntajes.at(1);

                if (promedio >= mayor)
                {
                    std::string salida = std::to_string(rut) + ";" + std::to_string(promedio);
                    escritura << salida << std::endl;
                    mayor = promedio;

                    if (menor == 0){ menor = promedio; }
                }

                else if (mayor > promedio && promedio > menor)
                {
                    if (menor == 0){ menor = promedio; }  // condición del 1er menor

                    char* buffer;
                    std::string aux,menores,mayores;

                    while (getline(lectura2,linea2))
                    {
                        if (linea2.empty()){ break; }

                        std::vector<int> busqueda = obtenerPuntajes(linea2);
                        if (promedio > busqueda.at(1) && rut != busqueda.at(0))
                        {
                            aux = std::to_string(busqueda.at(0))+";"+std::to_string(busqueda.at(1))+'\n';
                            menores = menores+aux;
                        }
                        else
                        {
                            aux = std::to_string(busqueda.at(0))+";"+std::to_string(busqueda.at(1))+'\n';
                            mayores = mayores+aux;
                        }
                        busqueda.clear();
                    }

                    std::ofstream escritura("ordenado.csv");
                    std::string salida = std::to_string(rut)+";"+std::to_string(promedio);

                    buffer = new char[menores.length()+1];
                    std::strcpy(buffer,menores.c_str());
                    escritura.write(buffer,strlen(buffer));
                    delete[] buffer;

                    escritura << salida << std::endl;

                    buffer = new char[mayores.length()+1];
                    std::strcpy(buffer,mayores.c_str());
                    escritura.write(buffer,strlen(buffer));
                    delete[] buffer;
                }

                else
                {
                    char* buffer;
                    std::string aux,mayores;
                    menor = promedio;
                    std::string salida = std::to_string(rut) + ";" + std::to_string(promedio);

                    while(getline(lectura2,linea2))
                    {
                        if (linea2.empty()){ break; }

                        std::vector<int> puntajes = obtenerPuntajes(linea2);
                        aux = std::to_string(puntajes.at(0))+";"+std::to_string(puntajes.at(1))+'\n';
                        mayores = mayores+aux;
                        puntajes.clear();
                    }

                    std::ofstream escritura("ordenado.csv");

                    escritura << salida << std::endl;

                    buffer = new char[mayores.length()+1];
                    strcpy(buffer,mayores.c_str());
                    escritura.write(buffer,strlen(buffer));
                    delete[] buffer;
                }

                puntajes.clear();
                lectura2.close();
                escritura.close();
            }
        }
        else
        {
            std::cout << "\nEl archivo no existe" << std::endl;
            return EXIT_FAILURE;
        }
    }

    else
    {
        std::cout << "\nNo hay argumento para la lectura" << std::endl;
        return EXIT_FAILURE;
    }
    /**
     * Despliegue de participantes
     */
    participantes();
    return EXIT_SUCCESS;
}

void participantes() {
    std::cout << std::endl << "=== Taller 02 ===" << std::endl;
    std::cout << std::endl << "Edgar Matus";
    std::cout << std::endl << "Oscar Peñaloza";
    std::cout << std::endl << "Daniela Galleguillos" << std::endl;
}

vector<int> obtenerPuntajes(std::string fila) {
    vector<int> arreglo;
    std::stringstream ss(fila);
    std::string item;

    // 17424518;639;654;500;583;714;724 -> ss

    while (std::getline(ss, item, ';')) {
        int valor = atoi(item.c_str());
        arreglo.push_back(valor);
    }
    return arreglo;
}

double promediar(std::vector<int> puntajes) {
    double promedio = 0.0;
    if (puntajes.size() >= 6) {
        // int rut = puntajes.at(0);
        int nem = puntajes.at(1);
        int ranking = puntajes.at(2);
        int matematica = puntajes.at(3);
        int lenguaje = puntajes.at(4);
        int ciencias = puntajes.at(5);
        int historia = puntajes.at(6);

        promedio = (nem + ranking + matematica + lenguaje + ciencias + historia) / 6.0;
    }
    return promedio;
}
