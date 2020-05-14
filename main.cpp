#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>


using namespace std;

class PSU{
    public:
        vector<int> RUT;
        vector<int> PUNTAJE;
};

void heap(int arr[],int arr0[], int n, int i)
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
void heap_ordenar(int arr[],int arr0[], int n)
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




int main()
{
    PSU psu;
    ifstream psu_file;
    psu_file.open("promedio.csv");

    while(psu_file.good()){
        string rut;
        string puntaje;
        int Rut;
        int Puntaje;

        getline(psu_file, rut, ';');
        getline(psu_file, puntaje);
        Puntaje = (int)round(stod(puntaje));
        Rut = stoi(rut);

        psu.RUT.push_back(Rut);
        psu.PUNTAJE.push_back(Puntaje);
    }

    int* arr = psu.PUNTAJE.data();
    int n = psu.PUNTAJE.size();
    int* arr0 = psu.RUT.data();


    heap_ordenar(arr,arr0, n);

    ofstream myfile;
    myfile.open ("ordenado.csv");
    for (int i = 0; i < n ;i++){
        myfile << arr0[i]<< "," <<arr[i]<< endl;
    }
myfile.close();

return 0;
}

