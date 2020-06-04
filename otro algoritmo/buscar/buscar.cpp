#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <string>
#include<fstream>
#include<cstdlib>
using namespace std;

void buscar(const char *ruta,const char *rut);

int main(int argc, char const *argv[]) {

   buscar(argv[2],argv[1]);

}

void buscar(const char *ruta,const char *rut) {
   struct dirent *entry;
   DIR *dir = opendir(ruta);
   if (dir == NULL) {
      return;
   }
   bool terminar = 1;
   string r = ruta;
   while ((entry = readdir(dir)) != NULL && terminar) {
    string archivo = entry->d_name;
    string fullruta = r + "/" + archivo;
    ifstream fin;
    if(archivo.size()>3){
	fin.open(fullruta);
	if(fin.fail())
	{
		cout << "ERROR AL ABRIR EL ARCHIVO.\n";
		exit(1);
	}
	string rut_buscado = rut;
	bool Encontrado=0;
	while(!fin.eof())
	{
		string temp = "";
		getline(fin,temp);
		for(int i=0;i<rut_buscado.size();i++)
		{
			if(temp[i]==rut_buscado[i])
				Encontrado = 1;
			else
			{
				Encontrado =0;
				break;
			}
		}

		if(Encontrado)
		{
			cout << "RUT: " << rut << "\nArchivo: " << archivo << "\nPuntaje: ";
			for(int i = rut_buscado.size()+1;i<temp.size();i++)
				cout << temp[i];
            terminar = 0;
			break;
		}
	}
  }
	fin.close();
   }
   closedir(dir);
   if(terminar){
    cout <<"No encontrado";
   }
}
