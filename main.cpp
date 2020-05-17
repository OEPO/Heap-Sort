#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

typedef class PSU{
    public:
        void setPuntaje(vector<double> puntaje)
        {
            puntajes.push_back(puntaje.at(1));
            ruts.push_back(puntaje.at(0));
        }
        int* getRuts_data(){ return ruts.data();}
        double* getPuntajes_data(){ return puntajes.data();}
        std::vector<int> getRuts_vector(){ return ruts;}
        std::vector<double> getvPuntajes_vector(){ return puntajes;}
        int getSize(){ return puntajes.size();}
    private:
        vector<int> ruts;
        vector<double> puntajes;
};
vector<double> obtenerPuntajes(string);
void participantes();


void heap(double arr[],int arr0[], int n, int i)
{
    int largo = i; // inicializa largo como raiz
    int l = 2*i + 1; // izq = 2*i + 1
    int r = 2*i + 2; // derecha = 2*i + 2

    // si izq es mas grande que raiz
    if (l < n && arr[l] > arr[largo])
        largo = l;

    // si der es mas grande que raiz
    if (r < n && arr[r] > arr[largo])
        largo = r;

    // si el largo no es raiz
    if (largo != i)
    {
        swap(arr[i], arr[largo]);
        swap(arr0[i], arr0[largo]);

        // heap recursivo que afecta al sub-arbol
        heap(arr,arr0, n, largo);
    }
}

// funcion principal de heap
void heap_ordenar(double arr[],int arr0[], int n)
{
    // armando el heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(arr, arr0, n, i);

    // extrae uno por uno los elementos del heap
    for (int i=n-1; i>0; i--)
    {
        // mueve la raiz actual al final
        swap(arr[0], arr[i]);
        swap(arr0[0], arr0[i]);

        // llama al heap max como el principal
        heap(arr,arr0, i, 0);
    }
}


int main(int argc, char** argv) // (            ) -> (int argc, char** argv)
{
    if (argc > 1)   // Comprueba si hay argumentos en **argv
    {
        PSU psu;
        ifstream psu_file;

        std::string archivo(argv[1]);
        psu_file.open(archivo);

        for(std::string linea;getline(psu_file,linea); )
        {
            //std::string rut;
            //std::string puntaje;
            //int Rut;
            //int Puntaje;

            //getline(psu_file, rut, ';');
            //getline(psu_file, puntaje);
            if(linea.empty()){ break; }
            std::vector<double> puntaje = obtenerPuntajes(linea);
            psu.setPuntaje(puntaje);

            //Puntaje = (int)round(stod(puntaje));
            //Rut = stoi(rut);

            //psu.RUT.push_back(Rut);
            //psu.PUNTAJE.push_back(Puntaje);
        }
        psu_file.close();

        //int* arr = psu.PUNTAJE.data();
        double* arr = psu.getPuntajes_data();

        //int n = psu.PUNTAJE.size();
        int n = psu.getSize();

        //int* arr0 = psu.RUT.data();
        int* arr0 = psu.getRuts_data();

        heap_ordenar(arr,arr0,n);

        std::ofstream escritura("ordenado.csv");
        //escritura.open ("ordenado.csv");
        for (int i = 0; i < n ;i++)
            escritura << arr0[i] << ";" << (arr[i]) << endl;    // myfile -> escritura

        escritura.close();
    }

    else
    {
        std::cout << "\nNo hay argumento para la lectura o el arhivo no existe." << std::endl;
        return EXIT_FAILURE;
    }

    participantes();    // implementar despliegue de participantes
    return EXIT_SUCCESS;    // return 0 -> return EXIT_SUCCESS
}

vector<double> obtenerPuntajes(std::string fila) {
    vector<double> arreglo;
    std::stringstream ss(fila);
    std::string item;

    while (std::getline(ss, item, ';')) {
        double valor = stod(item.c_str());
        arreglo.push_back(valor);
    }
    return arreglo;
}

void participantes() {
    std::cout << std::endl << "=== Taller 02 ===" << std::endl;
    std::cout << std::endl << "Daniela Galleguillos";
    std::cout << std::endl << "Oscar Peñaloza";
    std::cout << std::endl << "Edgar Matus" << std::endl;
}
