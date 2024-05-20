#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

/*
Codigo realizado por: Angel Godon, Paola Zambrano y Jose Peña 
Materia: Estructrua de datos
*/

typedef struct {
    string nombre;
    int sobrevive;
}tAmbiente;
/*Que razas sobreviven en los ambientes:
1-Humanos
2-Inferno
3-Viltrumiuta
4-Bloodice
*/
typedef tAmbiente *tAmbientePtr;

typedef struct {
    string nombre;
    int salud;
    int energia;
    tAmbientePtr ambiente;
}tRaza;
/*los ambientes se definen por un numero:
1-Tierra
2-Fuego
3-Espacio
4-Agua
*/
typedef tRaza *tRazaPtr;

typedef struct {
    int clase;
    string nombre;
    int valor;
    int tipo;
    int energia;
    int usos;
    int contenedor;
} tAccesorios;
/*Para las clases se usan un numero:
1-Ataque
2-Defensa
3-Supervivencia
4-acondicionamiento

Para el tipo tambien se usan numeros para diferenciarlos:
--Objetos de acondicionamiento--
1-Tierra
2-Fuego
3-Espacio
4-Fuego
--Objetos curativos--
5-Salud
6-Energia
--Objetos normales--
0
*/
typedef tAccesorios *tAccesoriosPtr;

typedef struct {
    tRazaPtr raza;
    string nombre;
    int salud;
    int energia;
    vector<tAccesoriosPtr> mochila[5];
} tPersonaje; 
typedef tPersonaje *tPersonPtr;

//Creacion de Arreglos para almacenar personajes:
const int nP=15;
typedef tPersonPtr tArrayPrs[nP];
typedef struct {
  tArrayPrs elemento;
  int cont;
}tListaPrs;
//Esta funcion busca dentro del arreglo de personajes para otras funciones como borrar
int buscarP (const tListaPrs &lista, int busc) {
  int ind = 0;
  bool encontrado = false;

  while ((ind < lista.cont) and !encontrado) {
    if (ind == busc) {
      encontrado = true;
    }                                                                                
    else { 
      ind++;
    }
  }

  if (!encontrado) {
    ind = -1;
  }
  return ind;
}        
//Esta funcion muestra los personajes disponibles para usar
void mostrarP (tListaPrs &lista){
  if (lista.cont==0){
    cout<<"No hay personajes, ¡Crea algunos para empezar el juego!"<<endl;
  } else{
  for (int i = 0; i < lista.cont; i++) {
    cout<< i+1<<". "<< lista.elemento[i]->nombre<<"  ";
  }      
  cout<<" "<<endl;
  }                            
}
//Esta funcion se usa SOLO al final de todo, se usa para destruir todo el arreglo 
void destruirP (tListaPrs &lista) {      
  for (int i = 0; i < lista.cont; i++) {
    delete lista.elemento[i];
  }                                  
  lista.cont = 0;
}                                    
//Esta funcion elimina solo un elemnto del arrelgo y luego lo acomoda
void eliminarP(tListaPrs &lista, int pos, bool &ok, tPersonPtr personaje){
  ok = true;
  int num = buscarP(lista, pos);
  if (num == -1) {
    ok = false;
  }
  else {
    personaje=lista.elemento[num];
    delete lista.elemento[num];
    for (int i = num +1; i<lista.cont;i++){
      lista.elemento[i-1]=lista.elemento[i];
    }
    lista.cont--;
    personaje=NULL;
  }
}
//Esta funcion pone un personaje nuevo en la lista de personajes disponibles
void insertarP(tListaPrs &lista, tPersonPtr personaje, bool &val){
  val = true;
  if (lista.cont==nP){
    cout<<"No caben mas personajes, elimine uno o use uno de los cargados"<<endl;
    val=false;
  }
  else {
    lista.elemento[lista.cont]= personaje;
    lista.cont++;
  }
}
//Termina aqui

//Creacion de arreglo para almacenar accesorios 
const int nA=50;
typedef tAccesoriosPtr tArrayAcc[nA];
typedef struct {
  tArrayAcc elemento;
  int cont;
}tListaAcc;
//Esta funcion busca dentro del arreglo de accesorios para otras funciones como borrar
int buscarAcc (const tListaAcc &lista, int busc) {
  int ind = 0;
  bool encontrado = false;

  while ((ind < lista.cont) and !encontrado) {
    if (ind == busc) {
      encontrado = true;
    }                                                                                
    else { 
      ind++;
    }
  }

  if (!encontrado) {
    ind = -1;
  }
  return ind;
}        
//Esta funcion muestra los accesorios disponibles para usar
void mostrarAcc (tListaAcc &lista){
  if (lista.cont==0){
    cout<<"No hay accesorios, ¡Crea algunos para empezar el juego!"<<endl;
  } else{
  for (int i = 0; i < lista.cont; i++) {
    cout<< i+1<<". "<< lista.elemento[i]->nombre<<"  ";
  }      
  cout<<" "<<endl;
  }                            
}
//Esta funcion se usa SOLO al final de todo, se usa para destruir todo el arreglo 
void destruirAcc (tListaAcc &lista) {      
  for (int i = 0; i < lista.cont; i++) {
    delete lista.elemento[i];
  }                                  
  lista.cont = 0;
}                                    
//Esta funcion elimina solo un elemnto del arrelgo y luego lo acomoda
void eliminarAcc (tListaAcc &lista, int pos, bool &ok, tAccesoriosPtr accesorio){
  ok = true;
  int num = buscarAcc(lista, pos);
  if (num == -1) {
    ok = false;
  }
  else {
    accesorio=lista.elemento[num];
    delete lista.elemento[num];
    for (int i = num +1; i<lista.cont;i++){
      lista.elemento[i-1]=lista.elemento[i];
    }
    lista.cont--;
    accesorio=NULL;
  }
}
//Esta funcion pone un accesorio nuevo en la lista de personajes disponibles
void insertarAcc(tListaAcc &lista, tAccesoriosPtr accesorio, bool &val){
  val = true;
  if (lista.cont==nA){
    cout<<"No caben mas accesorios, elimine uno o use uno de los cargados"<<endl;
    val=false;
  }
  else {
    lista.elemento[lista.cont] = accesorio;
    lista.cont++;
  }
}
//Termina aqui

//Creacion de Arreglos para almacenar razas:
const int nR=10;
typedef tRazaPtr tArrayRaza[nR];
typedef struct {
  tArrayRaza elemento;
  int cont;
}tListaRaza;
//Esta funcion busca dentro del arreglo de razas para otras funciones como borrar
int buscarR (const tListaRaza &lista, int busc) {
  int ind = 0;
  bool encontrado = false;

  while ((ind < lista.cont) and !encontrado) {
    if (ind == busc) {
      encontrado = true;
    }                                                                                
    else { 
      ind++;
    }
  }

  if (!encontrado) {
    ind = -1;
  }
  return ind;
}        
//Esta funcion muestra las razas disponibles para usar
void mostrarR (tListaRaza &lista){
  if (lista.cont==0){
    cout<<"No hay Razas, ¡Crea algunas para empezar el juego!"<<endl;
  } else{
  for (int i = 0; i < lista.cont; i++) {
    cout<< i+1<<". "<< lista.elemento[i]->nombre<<"  ";
  }      
  cout<<" "<<endl;
  }                            
}
//Esta funcion se usa SOLO al final de todo, se usa para destruir todo el arreglo 
void destruirR (tListaRaza &lista) {      
  for (int i = 0; i < lista.cont; i++) {
    delete lista.elemento[i];
  }                                  
  lista.cont = 0;
}                                    
//Esta funcion elimina solo un elemnto del arrelgo y luego lo acomoda
void eliminarR(tListaRaza &lista, int pos, bool &ok, tRazaPtr raza){
  ok = true;
  int num = buscarR(lista, pos);
  if (num == -1) {
    ok = false;
  }
  else {
    raza=lista.elemento[num];
    delete lista.elemento[num];
    for (int i = num +1; i<lista.cont;i++){
      lista.elemento[i-1]=lista.elemento[i];
    }
    lista.cont--;
    raza=NULL;
  }
}
//Esta funcion pone una raza nueva en la lista de personajes disponibles
void insertarR(tListaRaza &lista, tRazaPtr raza, bool &val){
  val = true;
  if (lista.cont==nR){
    cout<<"No caben mas personajes, elimine uno o use uno de los cargados"<<endl;
    val=false;
  }
  else {
    lista.elemento[lista.cont]= raza;
    lista.cont++;
  }
}
//Termina aqui

//Creacion de Arreglos para almacenar ambientes:
const int nAm=10;
typedef tAmbientePtr tArrayAmbiente[nAm];
typedef struct {
  tArrayAmbiente elemento;
  int cont;
}tListaAmbiente;
//Esta funcion busca dentro del arreglo de ambientes para otras funciones como borrar
int buscarAm (const tListaAmbiente &lista, int busc) {
  int ind = 0;
  bool encontrado = false;

  while ((ind < lista.cont) and !encontrado) {
    if (ind == busc) {
      encontrado = true;
    }                                                                                
    else { 
      ind++;
    }
  }

  if (!encontrado) {
    ind = -1;
  }
  return ind;
}        
//Esta funcion muestra los ambientes disponibles para usar
void mostrarAm(tListaAmbiente &lista){
  if (lista.cont==0){
    cout<<"No hay Ambientes, ¡Crea algunos para empezar el juego!"<<endl;
  } else{
  for (int i = 0; i < lista.cont; i++) {
    cout<< i+1<<". "<< lista.elemento[i]->nombre<<"  ";
  }      
  cout<<" "<<endl;
  }                            
}
//Esta funcion se usa SOLO al final de todo, se usa para destruir todo el arreglo 
void destruirAm (tListaAmbiente &lista) {      
  for (int i = 0; i < lista.cont; i++) {
    delete lista.elemento[i];
  }                                  
  lista.cont = 0;
}                                    
//Esta funcion elimina solo un elemnto del arrelgo y luego lo acomoda
void eliminarAm(tListaAmbiente &lista, int pos, bool &ok, tAmbientePtr ambiente){
  ok = true;
  int num = buscarAm(lista, pos);
  if (num == -1) {
    ok = false;
  }
  else {
    ambiente=lista.elemento[num];
    delete lista.elemento[num];
    for (int i = num +1; i<lista.cont;i++){
      lista.elemento[i-1]=lista.elemento[i];
    }
    lista.cont--;
    ambiente=NULL;
  }
}
//Esta funcion pone un ambiente nuevo en la lista de personajes disponibles
void insertarAm(tListaAmbiente &lista, tAmbientePtr raza, bool &val){
  val = true;
  if (lista.cont==nP){
    cout<<"No caben mas ambientes, elimine uno o use uno de los cargados"<<endl;
    val=false;
  }
  else {
    lista.elemento[lista.cont]= raza;
    lista.cont++;
  }
}
//Termina aqui

//Esta funcion se usa para ejecutar el menu
int menu(int x){
    int opcion=x;
    switch(x){
    case 1: opcion = 1;
    return opcion;
    case 2: opcion = 2;
    return opcion;
    case 3: opcion = 3;
    return opcion;
    default: cout << "Opcion no valida, ingrese una de las opciones indicadas anteriormente\n";
    cout<<"Ingrese la opción: ";
    cin>>opcion;
    return menu(opcion);
    }

}

int main(){
  int i;
  bool ok=true;
  int accaux;
  int prsjaux;
    tListaPrs personajes;
    personajes.cont=0;
    tListaAcc accesorios;
    accesorios.cont=0;
    tListaAmbiente ambientes;
    ambientes.cont=0;
    tListaRaza razas;
    razas.cont=0;

    tPersonPtr p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15 = NULL;
    tAccesoriosPtr a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50 = NULL;
    tAmbientePtr am1,am2,am3,am4,am5,am6,am7,am8,am9,am10 = NULL;
    tRazaPtr r1,r2,r3,r4,r5,r6,r7,r8,r9,r10 = NULL;

    vector<tPersonPtr> vecP{p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15};
    vector<tAccesoriosPtr> vecAcc{a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31,a32,a33,a34,a35,a36,a37,a38,a39,a40,a41,a42,a43,a44,a45,a46,a47,a48,a49,a50};
    vector<tAmbientePtr> vecAm{am1,am2,am3,am4,am5,am6,am7,am8,am9,am10};
    vector<tRazaPtr> vecR{r1,r2,r3,r4,r5,r6,r7,r8,r9,r10};

    //Se definen los ambientes bases.
    am1 = new tAmbiente{"Tierra",1};
    insertarAm(ambientes,am1,ok);
    am2 = new tAmbiente{"Fuego",2};
    insertarAm(ambientes,am2,ok);
    am3 = new tAmbiente{"Espacio",3};
    insertarAm(ambientes,am3,ok);
    am4 = new tAmbiente{"Agua",4};
    insertarAm(ambientes,am4,ok);

    //Se definen las razas base.
    r1 = new tRaza{"Humano",100,100,am1};
    insertarR(razas,r1,ok);
    r2 = new tRaza{"Andromedano",150,70,am3};
    insertarR(razas,r2,ok);
    r3 = new tRaza{"Bloodice",120,100,am4};
    insertarR(razas,r3,ok);
    r4 = new tRaza{"Inferno",80,150,am2};
    insertarR(razas,r4,ok);

    //Se definen todos los personajes. Humanos:
    p1 = new tPersonaje{r1,"Ragnar",r1->salud,r1->energia};
    insertarP(personajes,p1,ok);
    p2 = new tPersonaje{r1, "Aaron", r1->salud,r1->energia};
    insertarP(personajes,p2,ok);
    p3 = new tPersonaje{r1, "Scarlet", r1->salud,r1->energia};
    insertarP(personajes,p3,ok);
    //Bloodice
    p4 = new tPersonaje{r3, "Leviatan", r3->salud,r3->energia};
    insertarP(personajes,p4,ok);
    p5 = new tPersonaje{r3, "Undine", r3->salud,r3->energia};
    insertarP(personajes,p5,ok);
    p6 = new tPersonaje{r3, "Katara", r3->salud,r3->energia};
    insertarP(personajes,p6,ok);
    //Andromedanos
    p7 = new tPersonaje{r2, "Nahomi", r2->salud,r2->energia};
    insertarP(personajes,p7,ok);
    p8 = new tPersonaje{r2, "Yoda", r2->salud,r2->energia};
    insertarP(personajes,p8,ok);
    p9 = new tPersonaje{r2, "Lando", r2->salud,r2->energia};
    insertarP(personajes,p9,ok);
    //Infernos
    p10 = new tPersonaje{r4, "Ignis", r4->salud,r4->energia};
    insertarP(personajes,p10,ok);
    p11 = new tPersonaje{r4, "Volkanus", r4->salud,r4->energia};
    insertarP(personajes,p11,ok);
    p12 = new tPersonaje{r2, "Iroh", r4->salud,r4->energia};
    insertarP(personajes,p12,ok);



    //Aqui se definen los accesorios junto a sus atributos

    //Armas
    a1 = new tAccesorios{1,"Espada laser",33,0,10,10,0};
    insertarAcc(accesorios,a1,ok);
    a2 = new tAccesorios{1,"Machete",69,0,40,3,0};;
    insertarAcc(accesorios,a2,ok);
    a3 = new tAccesorios{1,"Mjolnir",70,0,45,2,0};
    insertarAcc(accesorios,a3,ok);
    a4 = new tAccesorios{1,"Bomba",20,0,5,5,0};
    insertarAcc(accesorios,a4,ok);
    a5 = new tAccesorios{1,"Cañon laser",90,0,85,1,0};
    insertarAcc(accesorios,a5,ok);
    a6 = new tAccesorios{1,"Buster Sword",45,0,20,2,0};
    insertarAcc(accesorios,a6,ok);
    a7 = new tAccesorios{1,"Batarang",7,0,2,10,0};
    insertarAcc(accesorios,a7,ok);
    a8 = new tAccesorios{1,"Pistola Laser",15,0,10,3,0};
    insertarAcc(accesorios,a8,ok);
    a9 = new tAccesorios{1,"AK-47",30,0,20,3,0};
    insertarAcc(accesorios,a9,ok);
    a10 = new tAccesorios{1,"lanza Misiles",70,0,50,2,0};
    insertarAcc(accesorios,a10,ok);
    a11 = new tAccesorios{1,"M-16",16,0,16,4,0};
    insertarAcc(accesorios,a11,ok);
    a12 = new tAccesorios{1,"Revolver",15,0,5,5,0};
    insertarAcc(accesorios,a12,ok);
    a13 = new tAccesorios{1,"S.I.M.P: Super snIper Monkey Pucca",90,0,70,1,0};
    insertarAcc(accesorios,a13,ok);
    a14 = new tAccesorios{1,"Escopeta",40,0,30,2,0};
    insertarAcc(accesorios,a14,ok);
    a15 = new tAccesorios{1,"Genkidama",150,0,100,1,0};
    insertarAcc(accesorios,a15,ok);
    
    //Defensa
    a16 = new tAccesorios{2,"Escudo",10,0,5,5,10};
    insertarAcc(accesorios,a16,ok);
    a17 = new tAccesorios{2,"Escudo de plasma",30,0,15,3,30};
    insertarAcc(accesorios,a17,ok);
    a18 = new tAccesorios{2,"Armadura de hierro",20,0,10,5,20};
    insertarAcc(accesorios,a18,ok);
    a19 = new tAccesorios{2,"Armadura bionica",40,0,20,2,40};
    insertarAcc(accesorios,a19,ok);
    a20 = new tAccesorios{2,"Traje de vibranium",50,0,20,2,10};
    insertarAcc(accesorios,a20,ok);
    a21 = new tAccesorios{2,"Muralla celestial",80,0,50,1,80};
    insertarAcc(accesorios,a21,ok);
    a22 = new tAccesorios{2,"Hulk buster",70,0,40,1,50};
    insertarAcc(accesorios,a22,ok);
    a23 = new tAccesorios{2,"Capa de invisibilidad",30,0,5,3,0};
    insertarAcc(accesorios,a23,ok);

    //Supervivencia (Salud)
    a24 = new tAccesorios{3,"Sopa de pollo", 50,5,40,2,0};
    insertarAcc(accesorios,a24,ok);
    a25 = new tAccesorios{3,"Empanada rompecolchon", 20,5,2,1,0};
    insertarAcc(accesorios,a25,ok);
    a26 = new tAccesorios{3,"Reina pepiada", 35,5,20,1,0};
    insertarAcc(accesorios,a26,ok);
    a27 = new tAccesorios{3,"Perro de 1$", 15,5,10,1,0};
    insertarAcc(accesorios,a27,ok);
    a28 = new tAccesorios{3,"Cangre Burger", 25,5,15,1,0};
    insertarAcc(accesorios,a28,ok);
    a29 = new tAccesorios{3,"Hallaca", 45,5,30,1,0};
    insertarAcc(accesorios,a29,ok);

    //Energia-Acondicionamiento
    a30 = new tAccesorios{4,"Celsius", 30,6,1,0};
    insertarAcc(accesorios,a30,ok);
    a31 = new tAccesorios{4,"Toddy", 18,6,2,0};
    insertarAcc(accesorios,a31,ok);
    a32 = new tAccesorios{4,"Cafe", 20,6,2,0};
    insertarAcc(accesorios,a32,ok);
    a33 = new tAccesorios{4,"Nutrichicha", 15,6,3,0};
    insertarAcc(accesorios,a33,ok);
    a34 = new tAccesorios{4,"Barra energetica", 25,6,2,0};
    insertarAcc(accesorios,a34,ok);
    a35 = new tAccesorios{4,"Creatina", 35,6,1,0};
    insertarAcc(accesorios,a35,ok);
    int mn=0;

    //menu
    cout << "The Big Red Fox 🦊 presenta:" << endl;
    cout << "     [DEMO]Figth Academy" << endl;
    cout<< " " << endl;
    cout << "1.Empezar Juego"<<endl;
    cout << "2.Crear Personaje"<<endl;
    cout << "3.Eliminar datos"<<endl;
    cout << "4.Cerrar Juego"<<endl;
    cout<< "Ingrese la opción que guste: ";
    cin>>mn;

    int opc= menu(mn);

    if(opc==1){
      cout<<"Elige tu primer peleador"<<endl;
      mostrarP(personajes);
      cin>>prsjaux;
      cout<<"Elige su primer accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su segundo accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su tercer accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su cuarto accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su quinto accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Perfecto! Siguente personaje"<<endl;
      cout<<"Elige tu segundo peleador"<<endl;
      mostrarP(personajes);
      cin>>prsjaux;
      cout<<"Elige su primer accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su segundo accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su tercer accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su cuarto accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su quinto accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Perfecto! Siguente personaje"<<endl;
      cout<<"Elige tu tercer peleador"<<endl;
      mostrarP(personajes);
      cin>>prsjaux;
      cout<<"Elige su primer accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su segundo accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su tercer accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su cuarto accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Elige su quinto accesorio"<<endl;
      mostrarAcc(accesorios);
      cin>>accaux;
      cout<<"Listo! Lamentablemente hasta aqui llega esta DEMO, para seguir con el juego espere la version completa"<<endl;
    }
    if(opc==2){
        tRazaPtr razaux;
        string nomaux;
        int salaux;
        int eneaux;
        tAmbientePtr ambiaux;
        int posaux;
        int valaux;
        int clasaux;
        int tipaux;
        int usoaux;
        int z = 0;
        cout<<"Elija que desea crear: "<<endl;
        cout<<"1.Crear una raza"<<endl;
        cout<<"2.Crear un personaje"<<endl;
        cout<<"3.Crear un ambiente"<<endl;
        cout<<"4.Crear un accesorio"<<endl;
        cin >> z;
        if (z==1){ //Raza
            for (i=0 ; i < vecR.size();i++){
                if (vecR[i]==NULL){
                    cout<<"Cual es el nombre de su raza?"<<endl;
                    cin>>nomaux;
                    cout<<"Cuanta salud tendra su raza?"<<endl;
                    cin>>salaux;
                    cout<<"Cuanta energia tendra su raza?"<<endl;
                    cin>>eneaux;
                    cout<<"En que ambiente sobrevive su raza?"<<endl;
                    mostrarAm(ambientes);
                    cin>>posaux;
                    vecR[i]=new tRaza{nomaux,salaux,eneaux,ambientes.elemento[posaux-1]};
                    insertarR(razas,vecR[i],ok);
                }
            }
        }
        if (z==2){ //Personaje
            for (i=0 ; i < vecP.size();i++){
                if (vecP[i]==NULL){
                    cout<<"En que ambiente sobrevive su raza?"<<endl;
                    mostrarR(razas);
                    cin>>posaux;
                    cout<<"Cual es el nombre de su personaje?"<<endl;
                    cin>>nomaux;                
                    vecP[i]=new tPersonaje{razas.elemento[posaux-1],nomaux};
                    insertarP(personajes,vecP[i],ok);
                }
            }
        }   

        if(z==3){//Ambiente
            for (i=0 ; i < vecAm.size();i++){
                if (vecAm[i]==NULL){
                    cout<<"Cual raza sobrevive en este ambiente?"<<endl;
                    mostrarR(razas);
                    cin>>posaux;
                    cout<<"Cual es el nombre de su nuevo ambiente?"<<endl;
                    cin>>nomaux;                
                    vecAm[i]=new tAmbiente{nomaux,posaux-1};
                    insertarAm(ambientes,vecAm[i],ok);
                }
            }  
        }
        if(z==4){ //Accesorios             
            for (i=0 ; i < vecR.size();i++){
                if (vecR[i]==NULL){
                    cout<<"Cual es el nombre de su accesorio"<<endl;
                    cin>>nomaux;                    
                    cout<<"Cuanto valor tendra su accesorio?"<<endl;
                    cin>>valaux;
                    cout<<"Cuanta energia tendra su accesorio?"<<endl;
                    cin>>eneaux;
                    cout<<"Cuantos usos tendra su accesorio?"<<endl;
                    cin>>usoaux;                    
                    cout<<"Cual es el tipo de su accesorio?"<<endl;
                    cout<<"1.Ataque"<<endl;
                    cout<<"2.Defensa"<<endl;
                    cout<<"3.Supervivencia"<<endl;
                    cout<<"4.Acondicionamiento"<<endl;
                    cin>>clasaux;
                    if(clasaux==1);
                        tipaux = 0;
                        vecAcc[i]=new tAccesorios{clasaux,nomaux,valaux,tipaux,eneaux,usoaux,0};
                        insertarAcc(accesorios,vecAcc[i],ok);
                    if(clasaux==2);
                        tipaux = 0;
                        vecAcc[i]=new tAccesorios{clasaux,nomaux,valaux,tipaux,eneaux,usoaux,valaux};
                        insertarAcc(accesorios,vecAcc[i],ok);  
                    if(clasaux==3){
                        cout<<"Que funcion tendra el accesorio?"<<endl;
                        cout<<"1.Salud"<<endl;
                        cout<<"2.Energia"<<endl;
                        cin>>tipaux;
                        vecAcc[i]=new tAccesorios{clasaux,nomaux,valaux,tipaux+4,eneaux,usoaux,0};
                        insertarAcc(accesorios,vecAcc[i],ok); 
                    }     
                } 
            }                            
        }
        menu(mn);

    }  
    if (opc==3){
        tPersonPtr paux;
        tAccesoriosPtr accaux;
        tRazaPtr raux;
        tAmbientePtr amaux;
        int n;
        int opc;
        cout<<"Que desea borrar?"<<endl;
        cout<<"1.Persoanje"<<endl;
        cout<<"2.Raza"<<endl;
        cout<<"3.Ambiente"<<endl;
        cout<<"4.Accesorio"<<endl;
        cin>>n;
        if (n==1){
            cout<<"Que personaje desea borrar"<<endl;
            mostrarP(personajes);
            cin>>opc;
            eliminarP(personajes, opc-1,ok, paux);
        }
        if (n==2){
            cout<<"Que raza desea borrar"<<endl;
            mostrarR(razas);
            cin>>opc;
            eliminarR(razas, opc-1,ok, raux);
        }
        if (n==3){
            cout<<"Que ambiente desea borrar"<<endl;
            mostrarAm(ambientes);
            cin>>opc;
            eliminarAm(ambientes, opc-1,ok, amaux);
        }
        if (n==4){
            cout<<"Que accesorio desea borrar"<<endl;
            mostrarAcc(accesorios);
            cin>>opc;
            eliminarAcc(accesorios, opc-1,ok, accaux);
        }
        menu(mn);
    }
    
    
    if (opc==4){
        cout<<"Fin del Juego"<<endl;
      } 
    destruirAcc(accesorios);
    destruirAm(ambientes);
    destruirP(personajes);
    destruirR(razas);
    return 0;
    
}
