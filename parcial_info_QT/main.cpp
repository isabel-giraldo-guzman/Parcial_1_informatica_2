#include <iostream>
#include <fstream>
#include "funciones_parcial.h"
using namespace std;

unsigned long long tamaño_pensum(char*nom_pensum);
void leer_pensum1(unsigned long long  tamaño,char* datoss,char* pensum_nombrtxt);
void leer_pensum2(unsigned long long  tamaño,char* datoss,char* pensum_nombre);
unsigned long long tamaño_nombre_archivo(char* archivo);
char* nombre_archivo(char* nombrefinal,char *nombre,unsigned long long tamaño_text_archivo);
void incicializar_arreglo_char(char*arreglo,unsigned long long tamaño_inic,char caracter);
unsigned long long caracter_numero(char*datos,char caracter,unsigned long long tamaño_archivo);
void incicializar_arreglo_char_m_n(char(*arreglo)[5],unsigned long long tamaño_m,unsigned long long tamaño_n,char caracter_inic);
void separar_archivo_fin(unsigned long long  tamaño,unsigned long long tamaño_m,unsigned long long tamaño_n,char(*arreglo)[5],char*archivo);
unsigned long long tamaño_max_for(char* archivo,char caracter,unsigned long long cantidad_ln);
void separar_char_ln(char** separar_lineas,unsigned long long cantidad_salto_linea,unsigned long long max_tam_matriz, char caracter,char* archivo);
unsigned long long tamaño_matriz_conjuntos_punto_c(char **matriz,char caracter,unsigned long long cantidad_ln);
void matriz_separada(char** matriz_punter[5],char**spp_lineas,unsigned long long tamaño_Caracter_matriz,unsigned long long caracter_salto_linea,int conjuntos,unsigned long long max_tamaño);

void inc_matriz_3(char***matriz,unsigned long long tamaño_Caracter_matriz,int conjuntos,unsigned long long caracter_salto_linea);

int main()
{
    unsigned long long tamaño=0,tamañotxt=0;//este es para el tamaño del prensum y la ruta del pensum
     unsigned long long tamaño_inc=0;//tamaño de arreglo
    char nombre_pensum[1000];
    char*nom_pensum;
    nom_pensum=&nombre_pensum[0];
    tamaño_inc=1000;
    char caracter_inicializador='\0';
    incicializar_arreglo_char(nom_pensum,tamaño_inc,caracter_inicializador);
    cout<<"ingrese la ruta del pensum"<<endl;//D:/Pensum.txt
    cin>>nombre_pensum;

    tamaño=tamaño_pensum(nom_pensum);
    char datos[tamaño];
    for(unsigned long long i=0;i<tamaño;i++){datos[i]=' ';}//inicializamos datos con un espacio
  //char*pensum_nombrtxt;
    char *datoss;
    datoss=&datos[0];
    leer_pensum1(tamaño,datoss,nom_pensum);
    for(unsigned long long i=0;i<tamaño;i++){cout<<*(datos+i);}//aqui imprimimos lo que se almaceno en datos
    //contador de caracteres especiales
    unsigned long long caracter_salto_linea=0;
    char caracter='\n';
    caracter_salto_linea=caracter_numero(datoss,caracter,tamaño);
    cout<<caracter_salto_linea<<endl;// miramos el numeros de salto de linea
    char datos_separados[caracter_salto_linea];
    char *saltos_ln=&datos_separados[0];
    incicializar_arreglo_char(saltos_ln,caracter_salto_linea,caracter_inicializador);
    //mayor tamaño entre cada salto de linea

    unsigned long long max_tam=0;
    max_tam=tamaño_max_for(datoss,caracter,caracter_salto_linea);
    //separar por salto de linea
    char sp_lineas[caracter_salto_linea][max_tam];
    // inicializamos la matriz
  /*  for (unsigned long long i = 0; i < caracter_salto_linea; i++) {
        for (unsigned long long k = 0; k < max_tam; k++) {
            sp_lineas[i][k] = ' ';
        }
    }*/
    // llenar la funcion para ln
    char* spp_lineas[caracter_salto_linea];
    for(unsigned long long i=0;i<caracter_salto_linea;i++){spp_lineas[i] = &sp_lineas[i][0];}
    //spp_lineas[0] = &sp_lineas[0][0];

    //pasar info al char
    //void separar_char_ln(char*spp_lineas,unsigned long long caracter_salto_linea,unsigned long long max_tam, char caracter);
    separar_char_ln(spp_lineas,caracter_salto_linea,max_tam,caracter,datoss);
    //ahora separamos por comas..
//contamos el arreglo mas largo antes de una coma
    unsigned long long tamaño_Caracter_matriz;
    tamaño_Caracter_matriz=tamaño_matriz_conjuntos_punto_c(spp_lineas,caracter,caracter_salto_linea);
    int conjuntos=5;
    char matriz_F [caracter_salto_linea][conjuntos][tamaño_Caracter_matriz];
    char* matriz_punter[caracter_salto_linea][conjuntos];
    //char** matriz_p2[tamaño_Caracter_matriz];
/*    for(unsigned long long i=0;i<caracter_salto_linea;i++){
        for(unsigned long long k=0;i<conjuntos;i++){
            matriz_punter[i][k]=&matriz_F [i][k][0];

        }
    }*/
    //matriz final (saltos de linea)(conjuntos o grupos)(tamaño de caracteres)
    char matriz_fin[caracter_salto_linea][conjuntos][tamaño_Caracter_matriz];
    char ***puntero_final;
    //hacemos la matriz tridimencional
    char*** matriz = new char**[tamaño_Caracter_matriz];

    inc_matriz_3(matriz,tamaño_Caracter_matriz,conjuntos,caracter_salto_linea);
 /*   for (int i = 0; i < tamaño_Caracter_matriz; ++i) {
        matriz[i] = new char*[conjuntos];
        for (int j = 0; j < conjuntos; ++j) {
            matriz[i][j] = new char[caracter_salto_linea];
            for (int k = 0; k < caracter_salto_linea; ++k) {
                matriz[i][j][k] = '0'; // asignación de valores
            }
        }
    }*/


    puntero_final=matriz;//asignamos el puntero a la matriz no podemos olvidar eliminar luego los datos guardados

    //ahora hacemos una funcion para separar todos los datos que tenemos en n flas, m conjuntos con x cantidad de datos
 matriz_separada(puntero_final,spp_lineas,tamaño_Caracter_matriz,caracter_salto_linea,conjuntos,max_tam);
    //void matriz_separada(char*** matriz_Punter,char**spp_lineas,unsigned long long tamaño_Caracter_matriz,unsigned long long caracter_salto_linea,int conjuntos,unsigned long long max_tam)
  /*  //char (*arreglo)[5] = datos_separados;//aqui hacemos un puntero a la matriz seriaun puntero a un arreglo de caracteres de longitud 5
    unsigned long long tamaño_m,tamaño_n;
    char caracter_inic;
    tamaño_m=caracter_salto_linea;
    tamaño_n=5;
    caracter_inic=' ';
    incicializar_arreglo_char_m_n(arreglo,tamaño_m,tamaño_n,caracter_inic);
//asignamos los valores a datos separados
    //necesitamos archivo, tamaño archivo,tamaño m, tamaño n(5),puntero [5]
     separar_archivo_fin(tamaño,tamaño_m,tamaño_n,arreglo,datoss);
 // return 0;*/



}
