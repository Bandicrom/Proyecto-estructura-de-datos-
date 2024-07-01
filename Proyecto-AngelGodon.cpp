#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

/*
Codigo realizado por: Angel Godon, Paola Zambrano y Jose Peña 
Materia: Estructrua de datos
*/

//_____________________________________________Estructuras_______________________________________
//--------------------------------------------------Ambientes--------------------------------------------------

struct tAmbiente{
    string nombre;
    bool uso;
    tAmbiente* siguiente;
};

typedef tAmbiente *tAmbientePtr;

//--------------------------------------------------Razas--------------------------------------------------

struct tRaza{
    string nombre;
    int energia;
    int salud;
    string planeta;
    tRaza* siguiente;
};

typedef tRaza *tRazaPtr;

//--------------------------------------------------Accesorios--------------------------------------------------

struct tAccesorios{
    string nombre;
    string tipo;
    int valor;
    string recuperacion;
    int energia;
    int contenedor;
    tAccesorios* siguiente;
};

typedef tAccesorios *tAccesoriosPtr;

//--------------------------------------------------Mochilas--------------------------------------------------
typedef tAccesoriosPtr Mochila[5];
typedef tAccesoriosPtr Mochilab[3];

//--------------------------------------------------Personajes--------------------------------------------------

struct tPersonaje{
    string nombre;
    string raza;
    int salud;
    int energia;
    Mochila mochila;
    Mochilab mochila_b;
    tPersonaje* siguiente;
};

typedef tPersonaje *tPersonajePtr;


//_____________________________________________Funciones de Validaciones_______________________________________
int ConvertirNumero(string cadena) {
    string caracter;
    int numero=0;
    

    for (int i = 0; i < cadena.length(); i++) {
        caracter = cadena[i];

        if (caracter=="1"){
            numero = (numero*10)+1;
        }
        else if (caracter=="2"){
            numero = (numero*10)+2;
        }
        else if (caracter=="3"){
            numero = (numero*10)+3;
        }
        else if (caracter=="4"){
            numero = (numero*10)+4;
        }
        else if (caracter=="5"){
            numero = (numero*10)+5;
        }
        else if (caracter=="6"){
            numero = (numero*10)+6;
        }
        else if (caracter=="7"){
            numero = (numero*10)+7;
        }
        else if (caracter=="8"){
            numero = (numero*10)+8;
        }
        else if (caracter=="9"){
            numero = (numero*10)+9;
        }
        else if (caracter=="0"){
            numero = (numero*10);
        }
        else{
            cout<<"Por favor ingrese un numero entero positivo"<<endl;
            getline(cin,cadena);
            ConvertirNumero(cadena);
        }
    }
    return numero;
}

void VerificarTipo(string tipo){
    while(tipo!="Ataque" or tipo!="Defensa" or tipo!="Supervivencia" or tipo!="Acondicionamiento"){
        cout<<"Ingrese alguna de las 4 opciones mostradas anteriormente";
        getline(cin,tipo);
        VerificarTipo(tipo);
    }
}

void VerificarAmbiente(tAmbientePtr &ambientes, string nombre){
    tAmbientePtr actual;
    actual = ambientes;

    while(actual==NULL){
        if (actual->nombre==nombre){
            break;
        }
        else {
            actual=actual->siguiente;
        }
    }
    actual=ambientes;

    if (actual==NULL){
        cout<<"Ese planeta no existe, coloque uno de los existentes"<<endl;
        getline(cin,nombre);
        VerificarAmbiente(ambientes, nombre);
    }
}

void VerificarSoE(string se){
    while(se!="Salud" or se!="Energia"){
        cout<<"Ingrese la palabra Salud o la palabra Energia"<<endl;
        getline(cin,se);
    }
}




//___________________________________________Funciones de estructuras_______________________________________
//--------------------------------------------------Ambientes--------------------------------------------------


tAmbientePtr CrearAmbiente(){
    tAmbientePtr amb;
    string nombre;
    amb=new(tAmbiente);
    cout<<"¡Vaya!, parece que se ha avistado un nuevo plantea \n ¿Que nombre le pondras a este nuevo ambiente?"<<endl;
    getline(cin,nombre);
    amb->nombre=nombre;
    amb->uso=false;
    amb->siguiente=NULL;
    cout<<"¡El nuevo ambiente ha sido ingreasado a la base de datos de la nave!"<<endl;
    return amb;
}

void IngresarAmbiente(tAmbientePtr &ambientes,int limite){
    if (limite==10){
        cout<<"¡No hay espacio para mas ambientes en la base de datos! \n Debera borrar algunos de nuestros datos para poder ingresar nuevos"<<endl;
        
    }
    else{
        tAmbientePtr amb = CrearAmbiente();
        if(ambientes == NULL){
            ambientes = amb;
        }
        else{
            tAmbientePtr actual = ambientes;
            while(actual->siguiente != NULL){
			    actual = actual->siguiente;
		    }
		    actual->siguiente = amb;
        }
        limite+=1;
    }
}

void MostrarAmbientes(tAmbientePtr &ambientes){
    int num=1;
    if(ambientes != NULL){
        cout<<"-------------- Planetas del Sistema AJP --------------\n";
        while(ambientes != NULL){
            cout<<"   "<<num<<"."<<ambientes->nombre<<endl;
            ambientes = ambientes->siguiente;
            num += 1;
        }
        cout<<"------------------------------------------------------\n";
    }
    else{
        cout<<"El sistema de la nave no ha encontrado datos sobre los planetas del sistema\nParece que debera ingresar nuevos planetas capitan"<<endl;
    }
}

void EliminarAmbiente(tAmbientePtr &ambientes, int limite){
    if (ambientes == NULL){
        cout<<"Capitan en la base de datos no hay informacion sobre los planetas del sisetma en el que nos encontramos"<<endl;
    }
    else{
        MostrarAmbientes(ambientes);
        tAmbientePtr actual=ambientes;
        tAmbientePtr anterior=NULL;
        tAmbientePtr temporal=NULL;
        int num=1;
        string elim;
        int eliminar;

        while(actual != NULL){
            actual = actual->siguiente;
            num += 1;
        }
        actual = ambientes;
        cout<<"¿Que planetas desea eliminar de la base de datos del sistema?"<<endl;
        getline(cin,elim);
        eliminar=ConvertirNumero(elim);
        while((eliminar > num) and (eliminar < 1)){
            cout<<"Parece que no existe ese planeta en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
            getline(cin,elim);
            eliminar=ConvertirNumero(elim);
        }
        num=1;
        
        while(num != eliminar){
            anterior=actual;
            actual = actual->siguiente;
            num += 1;
        }
        
        temporal=actual;
        if (temporal->uso==false){
            if (actual == ambientes){
                ambientes = ambientes->siguiente;
            }
            else{
                anterior->siguiente = actual->siguiente;
            }
            cout<<"Eliminando datos de la base de la nave...\n...\n";
            cout<<"¡Listo! El planeta "<<temporal->nombre<<"Se ha borrado de la base de datos de la nave"<<endl;
            delete temporal;
            limite-=1;
        }
        else{
            cout<<"¡ESPERA! Parece que exiten una o mas razas que pertenecen a este planeta"<<endl<<"Elimina primero la(s) raza(s) pertenecientes a este planeta"<<endl;
        }
    }
}

void DestruirAmbientes(tAmbientePtr &ambientes){
    if (ambientes!=NULL) {
        tAmbientePtr actual=ambientes;
        tAmbientePtr temporal;
        while(actual!=NULL){
            temporal=actual;
            actual = actual->siguiente;
            delete temporal;
        }
    }                                  
}

//--------------------------------------------------Razas---------------------------------------------------


tAmbientePtr AmbienteDeRaza(tAmbientePtr &ambientes){
    MostrarAmbientes(ambientes);
    tAmbientePtr amb;
    tAmbientePtr actual=ambientes;
    int num=1;
    int seleccionar=0;
    string select;
    while(actual != NULL){
        actual = actual->siguiente;
        num += 1;
    }
    actual = ambientes;
    cout<<"¿De que planeta es su raza?"<<endl;
    getline(cin,select);
    seleccionar=ConvertirNumero(select);
    while((seleccionar > num) and (seleccionar < 1)){
        cout<<"Parece que no existe ese planeta en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
        getline(cin,select);
        seleccionar=ConvertirNumero(select);
    }
    num=1;
    while(num != seleccionar){
        actual = actual->siguiente;
        num += 1;
    }
    actual->uso=true;
    amb=actual;
    return amb;
}

tRazaPtr CrearRaza(tAmbientePtr &ambientes){
    tRazaPtr r;
    string nombre;
    int salud=0;
    string sal;
    int energia=0;
    string ene;
    tAmbiente planeta;
    r=new(tRaza);
    cout<<"Parece que se ha registrado una nueva especie \n ¿Cual es el nommbre de esta especie?"<<endl;
    getline(cin,nombre);
    r->nombre=nombre;
    cout<<"¿Cual es la salud base de esta especie?"<<endl;
    getline(cin,sal);
    salud=ConvertirNumero(sal);
    r->salud=salud;
    cout<<"¿Cual es la energia base de esta especie?"<<endl;
    getline(cin,ene);
    energia=ConvertirNumero(ene);
    r->energia=energia;
    cout<<"¿A que planeta pertenece esta especie?"<<endl;
    getline(cin,r->planeta);
    r->siguiente=NULL;
    cout<<"¡El nuevo ambiente ha sido ingreasado a la base de datos de la nave!"<<endl;
    return r;
}

void IngresarRaza(tRazaPtr &razas,int limite,tAmbientePtr &ambientes){
    if (limite==10){
        cout<<"¡No hay espacio para mas razas en la base de datos! \n Debera borrar algunas de nuestros datos para poder ingresar nuevas"<<endl;
        
    }
    else{
        tRazaPtr r = CrearRaza(ambientes);
        if(razas == NULL){
            razas = r;
        }
        else{
            tRazaPtr actual = r;
            while(actual->siguiente != NULL){
			    actual = actual->siguiente;
		    }
		    actual->siguiente = r;
        }
        limite+=1;
    }
}

void MostrarRazas(tRazaPtr &razas){
    int num=1;
    if(razas != NULL){
        cout<<"-------------- Razas del Sistema AJP --------------\n";
        while(razas != NULL){
            cout<<"   "<<num<<"."<<razas->nombre<<endl;
            razas = razas->siguiente;
            num += 1;
        }
        cout<<"------------------------------------------------------\n";
    }
    else{
        cout<<"No existen registros sobre especies en nuestra base de datos.\nParece que debera registrar nuevas razas capitan"<<endl;
    }
}

void EliminarRaza(tRazaPtr &razas,int limite){
    if (razas == NULL){
        cout<<"Capitan en la base de datos no hay informacion sobre los planetas del sisetma en el que nos encontramos"<<endl;
    }
    else{
        tRazaPtr actual=razas;
        tRazaPtr anterior=NULL;
        tRazaPtr temporal=NULL;
        int num=1;
        int eliminar=0;
        string elim;
        while(actual != NULL){
            actual = actual->siguiente;
            num += 1;
        }
        actual = razas;
        MostrarRazas(razas);
        cout<<"¿Que planetas desea eliminar de la base de datos del sistema?"<<endl;
        getline(cin,elim);
        eliminar=ConvertirNumero(elim);
        //Crear funcion de validacion
        while((eliminar > num) and (eliminar < 1)){
            cout<<"Parece que no existe ese planeta en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
            getline(cin,elim);
            eliminar=ConvertirNumero(elim);
        }
        num=1;
        while(num != eliminar){
            anterior=actual;
            actual = actual->siguiente;
            num += 1;
        }
        
        temporal=actual;
        if (actual == razas){
            razas = razas->siguiente;
        }
        else{
            anterior->siguiente = actual->siguiente;
        }
        cout<<"Eliminando datos de la base de la nave...\n...\n";
        cout<<"¡Listo! La raza "<<temporal->nombre<<"Se ha borrado de la base de datos de la nave"<<endl;
        delete temporal;
        limite-=1;
    }
}

void DestruirRazas(tRazaPtr &raza){
    if (raza!=NULL) {
        tRazaPtr actual=raza;
        tRazaPtr temporal;
        while(actual!=NULL){
            temporal=actual;
            actual = actual->siguiente;
            delete temporal;
        }
    }                                  
}

//--------------------------------------------------Accesorios---------------------------------------------------


tAccesoriosPtr CrearAccesorios(tAmbientePtr &ambientes){
    tAccesoriosPtr acc;
    string nombre;
    string tipo;
    int valor;
    string val;
    string recuperacion;
    int energia;
    int contenedor;
    acc=new(tAccesorios);

    cout<<"Un nuevo objeto se ha registrado en el sistema \n ¿De que clase es el objeto?"<<endl;
    cout<<"Ataque"<<endl;
    cout<<"Defensa"<<endl;
    cout<<"Supervivencia"<<endl;
    cout<<"Acondicionamiento"<<endl;
    getline(cin,tipo);
    VerificarTipo(tipo);
    acc->tipo=tipo;
    cout<<"¿Cual es el nombre del objeto?"<<endl;
    getline(cin,nombre);
    acc->nombre=nombre;
    if(tipo=="Acondicionamiento"){
        acc->valor=0;
        acc->energia=0;
        acc->contenedor=0;
        cout<<"¿Para que ambiente es su accesorio de acondicionamiento?(Ingrese el nombre del ambiente)"<<endl;
        MostrarAmbientes(ambientes);
        getline(cin,recuperacion);
        VerificarAmbiente(ambientes, recuperacion);
        acc->recuperacion=recuperacion;
    }
    else if (tipo=="Ataque"){
        acc->recuperacion="";
        acc->contenedor=0;
        cout<<"¿Cuanto daño hace su arma?"<<endl;
        getline(cin,val);
        valor=ConvertirNumero(val);
        acc->valor=valor;
        valor=0;
        cout<<"¿Cuanta energia resta su arma?"<<endl;
        getline(cin,val);
        valor=ConvertirNumero(val);
        acc->energia=valor;
        valor=0;
    }
    else if (tipo=="Defensa"){
        acc->recuperacion="";
        cout<<"¿Cuanto cubre su proteccion?"<<endl;
        getline(cin,val);
        valor=ConvertirNumero(val);
        acc->valor=valor;
        valor=0;
        cout<<"¿Cuanta energia resta su proteccion?"<<endl;
        getline(cin,val);
        valor=ConvertirNumero(val);
        acc->energia=valor;
        valor=0;
        cout<<"¿Cuanta vida extra le otorga su proteccion?"<<endl;
        getline(cin,val);
        valor=ConvertirNumero(val);
        acc->contenedor=valor;
        valor=0;
    }
    else if (tipo=="Supervivencia"){
        acc->contenedor=0;
        cout<<"¿Que atributo recupera el objeto?\n[Salud]\n[Energia]"<<endl;
        getline(cin,recuperacion);
        VerificarSoE(recuperacion);
        acc->recuperacion=recuperacion;
        cout<<"¿Cuanto recupera el objeto?"<<endl;
        getline(cin,val);
        valor=ConvertirNumero(val);
        acc->valor=valor;
        cout<<"¿Cuanta energia resta su uso?"<<endl;
        getline(cin,val);
        valor=ConvertirNumero(val);
        acc->energia=valor;
        
    }
    return acc;
}

void IngresarAccesorio(tAccesoriosPtr &accesorios, int limite, tAmbientePtr &ambientes){
    if (limite==50){
        cout<<"¡No hay espacio para mas accesorios en la armeria! \n Debera desaserce de algunos para ingresar nuevos"<<endl;
        
    }
    else{
        tAccesoriosPtr acc = CrearAccesorios(ambientes);
        if(accesorios == NULL){
            accesorios = acc;
        }
        else{
            tAccesoriosPtr actual = acc;
            while(actual->siguiente != NULL){
			    actual = actual->siguiente;
		    }
		    actual->siguiente = acc;
        }
        limite+=1;
    }
}

void MostrarAccesorios(tAccesoriosPtr &accesorios){
    int num=1;
    if(accesorios != NULL){
        cout<<"-------------- Armeria --------------\n";
        while(accesorios != NULL){
            cout<<"   "<<num<<"."<<accesorios->nombre<<endl;
            accesorios = accesorios->siguiente;
            num += 1;
        }
        cout<<"------------------------------------------------------\n";
    }
    else{
        cout<<"¡La armeria esta vacia!.\nParece que debera pedir nuevas armas a la base capitan"<<endl;
    }
}

void EliminarAccesorio(tAccesoriosPtr &accesorios, int l){
    //Crear opcion de validacion para el entero eliminar 
    if (accesorios == NULL){
        cout<<"Capitan en la base de datos no hay informacion sobre los planetas del sisetma en el que nos encontramos"<<endl;
    }
    else{
        tAccesoriosPtr actual=accesorios;
        tAccesoriosPtr anterior=NULL;
        tAccesoriosPtr temporal=NULL;
        int num=1;
        int eliminar=0;
        string elim;

        while(actual != NULL){
            actual = actual->siguiente;
            num += 1;
        }
        actual = accesorios;
        MostrarAccesorios(accesorios);
        cout<<"¿Que planetas desea eliminar de la base de datos del sistema?"<<endl;
        getline(cin,elim);
        eliminar=ConvertirNumero(elim);
        while((eliminar > num) and (eliminar < 1)){
            cout<<"Parece que no existe ese planeta en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
            cin>>eliminar;
        }
        num=1;
        while(num != eliminar){
            anterior=actual;
            actual = actual->siguiente;
            num += 1;
        }
        
        temporal=actual;
        if (actual == accesorios){
            accesorios = accesorios->siguiente;
        }
        else{
            anterior->siguiente = actual->siguiente;
        }
        cout<<"Eliminando de la armeria...\n...\n";
        cout<<"¡Listo! El accesorio "<<temporal->nombre<<"Se ha eliminado de la armeria"<<endl;
        delete temporal;
        l-=1;
    }
}

void DestruirAccesorios(tAccesoriosPtr &acc){
    if (acc!=NULL) {
        tAccesoriosPtr actual=acc;
        tAccesoriosPtr temporal;
        while(actual!=NULL){
            temporal=actual;
            actual = actual->siguiente;
            delete temporal;
        }
    }                                  
}

//--------------------------------------------------Personajes--------------------------------------------------


tRazaPtr RazaDePersonaje(tRazaPtr &razas){
    MostrarRazas(razas);
    tRazaPtr r;
    tRazaPtr actual=razas;
    int num=1;
    int seleccionar=0;
    string select;

    while(actual != NULL){
        actual = actual->siguiente;
        num += 1;
    }

    actual = razas;
    cout<<"¿A que raza pertenece el estudiante?"<<endl;
    getline(cin,select);
    seleccionar=ConvertirNumero(select);

    while((seleccionar > num) and (seleccionar < 1)){
        cout<<"Parece que la raza no en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
        cin>>seleccionar;
    }

    num=1;
    while(num != seleccionar){
        actual = actual->siguiente;
        num += 1;
    }
    
    r=actual;
    return r;
}

tPersonajePtr CrearPerosnaje(tRazaPtr &razas){
    tPersonajePtr p;
    string nombre;
    tRazaPtr r;
    p=new(tPersonaje);
    cout<<"Un nuevo alumno ha llegado a la academia \n ¿Cual es su nombre?"<<endl;
    getline(cin,nombre);
    p->nombre=nombre;
    r=RazaDePersonaje(razas);
    p->raza=r->nombre;
    p->salud=r->salud;
    p->energia=r->energia;
    p->siguiente=NULL;
    cout<<"¡El nuevo estudiante ha sido matriculado en la academia!"<<endl;
    return p;
}

void IngresarPerosnaje(tPersonajePtr &personajes,int limite, tRazaPtr &razas){
    if (limite==20){
        cout<<"¡No hay espacio para mas estudiantes en la academia!"<<endl;
        
    }
    else{
        tPersonajePtr p = CrearPerosnaje(razas);
        if(personajes == NULL){
            personajes = p;
        }
        else{
            tPersonajePtr actual = personajes;
            while(actual->siguiente != NULL){
			    actual = actual->siguiente;
		    }
		    actual->siguiente = p;
        }
        limite+=1;
    }
}

void MostrarPersonajes(tPersonajePtr &personajes){
    int num=1;
    if(personajes != NULL){
        cout<<"-------------- Estudiantes Matriculados --------------\n";
        while(personajes != NULL){
            cout<<"   "<<num<<"."<<personajes->nombre<<endl;
            personajes = personajes->siguiente;
            num += 1;
        }
        cout<<"------------------------------------------------------\n";
    }
    else{
        cout<<"No hay ningun estudiante matriculado\nParece que tendremos que reclutar nuevos estudiantes"<<endl;
    }
}

void EliminarPersonaje(tPersonajePtr &personajes,int l){ 
    if (personajes == NULL){
        cout<<"Capitan en la base de datos no hay informacion sobre los planetas del sisetma en el que nos encontramos"<<endl;
    }
    else{
        MostrarPersonajes(personajes);
        tPersonajePtr actual=personajes;
        tPersonajePtr anterior=NULL;
        tPersonajePtr temporal=NULL;
        int num=1;
        int eliminar=0;
        string elim;
        while(actual != NULL){
            actual = actual->siguiente;
            num += 1;
        }
        actual = personajes;
        cout<<"¿Que estudiante desea expulsar de la academia?"<<endl;
        getline(cin,elim);
        eliminar=ConvertirNumero(elim);
        while((eliminar > num) and (eliminar < 1)){
            cout<<"Parece que no existe ese estudiante en nuestra academia\nIntenta ingresar uno de los que se muestran arriba"<<endl;
            cin>>eliminar;
        }
        num=1;
        while(num != eliminar){
            anterior=actual;
            actual = actual->siguiente;
            num += 1;
        }
        
        temporal=actual;
        
        if (actual == personajes){
            personajes = personajes->siguiente;
        }
        else{
            anterior->siguiente = actual->siguiente;
        }
        cout<<"Expulsando estudiante...\n...\n";
        cout<<"¡Listo! El estudiante "<<temporal->nombre<<"Ya no es parte de la academia"<<endl;
        delete temporal;
        l-=1;
    }
}

void EliminarPerosnajesPorNombre(tPersonajePtr &personajes, tPersonajePtr p){
    tPersonajePtr actual=personajes;
    tPersonajePtr anterior=NULL;
    tPersonajePtr temporal=NULL;
    
    actual = personajes;
    
    while(p->nombre != actual->nombre){
        anterior=actual;
        actual = actual->siguiente;
    }
    
    temporal=actual;
    
    if (actual == personajes){
        personajes = personajes->siguiente;
    }
    else{
        anterior->siguiente = actual->siguiente;
    }

    delete temporal;
}


void DestruirPersonajes(tPersonajePtr &personajes){
    if (personajes!=NULL) {
        tPersonajePtr actual=personajes;
        tPersonajePtr temporal;
        while(actual!=NULL){
            temporal=actual;
            actual = actual->siguiente;
            delete temporal;
        }
    }                                  
}

//_____________________________________________Funciones de Validaciones de Batalla_______________________________________

void ValidarUso(string opc, tPersonajePtr p, int n){
    if (opc=="1"){
        if (p->mochila_b[0]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p,n);
        }
        else{
            n=0;
        }
    }
    else if (opc=="2"){
        if (p->mochila_b[1]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p,n);
        }
        else{
            n=1;
        }
    }
    else if (opc=="3"){
        if (p->mochila_b[2]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p,n);
        }
        else{
            n=2;
        }
    }
    else{
        cout<<"Opcion no valida, ingrese una de las mostradas anteriormente"<<endl;
        getline(cin,opc);
        ValidarUso(opc,p,n);
    }
}


//_________________________________________Funciones de la batalla_________________________________________
int ContarPersonajes(tPersonajePtr &personajes){
    int i=0;
    while(personajes->siguiente != NULL){
        personajes = personajes->siguiente;
        i+=1;
    }
    return i;
}

/*void PersonajesCPU(tPersonajePtr &personajes,tPersonajePtr &CPU,int limite){
    srand(time(NULL));
    tPersonajePtr actual=personajes;
    int i = ContarPersonajes(personajes);
    int num = rand()%i;
    int n = 0;
    if (limite<3){
        while(num!=n){
            actual = actual->siguiente;
            n+=1;
        } 
        actual->siguiente=NULL;
        if (CPU == NULL){
            CPU = actual;
        }
        else{
            tPersonajePtr temporal = CPU;
            while(temporal->siguiente != NULL){
                temporal = temporal->siguiente;
            }
            temporal->siguiente = actual;
        }
        limite+=1;
        PersonajesCPU(personajes,CPU,limite);
    }
}*/

void PersonajesUsuarios(tPersonajePtr &personajes,tPersonajePtr &j){
    cout<<"Elige tus tres personajes"<<endl;
    int p1;
    string p1s;
    int p2;
    string p2s;
    int p3;
    string p3s;
    MostrarPersonajes(personajes);
    //Aqui para todos estos datos hay que usar una validacion de numeros
    cout<<"Personaje 1:"<<endl;
    getline(cin,p1s);
    p1=ConvertirNumero(p1s);
    cout<<"Personaje 2:"<<endl;
    getline(cin,p2s);
    p2=ConvertirNumero(p2s);
    cout<<"Personaje 3:"<<endl;
    getline(cin,p3s);
    p3=ConvertirNumero(p3s);

    int i = 1;
    tPersonajePtr actual = personajes;

    while(i != p1){
        actual = actual->siguiente;
        i+=1;
    }
    actual->siguiente=NULL;
    j = actual;

    actual=personajes;
    i=1;

    while(i != p2){
        actual = actual->siguiente;
        i+=1;
    }
    actual->siguiente=NULL;
    tPersonajePtr temporal = j;
    while(temporal->siguiente != NULL){
        temporal = temporal->siguiente;
    }
    temporal->siguiente = actual;

    actual=personajes;
    i=1;

    while(i != p3){
        actual = actual->siguiente;
        i+=1;
    }
    actual->siguiente=NULL;
    temporal = j;
    while(temporal->siguiente != NULL){
        temporal = temporal->siguiente;
    }
    temporal->siguiente = actual;
}

void AccesoriosUsuarios(tPersonajePtr &j, tAccesoriosPtr acc){
    tPersonajePtr actual = j;
    int opc;
    string opci;
    int num=1;
    tAccesoriosPtr accac = acc;

    while(accac->siguiente != NULL){
        accac=accac->siguiente;
        num+=1;
    }
    accac=acc;

    tAccesoriosPtr vector[num];
    for (int i=0; i<num; i++){
        vector[i]=accac;
        accac=accac->siguiente;
    }

    while(actual!=NULL){
        cout<<"Que accesorios les va a poner a "<<actual->nombre<<"?"<<endl;
        cout<<"Primer accesorio:";
        getline(cin,opci);
        opc=ConvertirNumero(opci);
        while(opc>num){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            opc=ConvertirNumero(opci);        
        }
        actual->mochila[0]=vector[opc-1];
        opc=0;

        cout<<"Segundo accesorio:";
        while(opc>num){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            opc=ConvertirNumero(opci);        
        }
        actual->mochila[1]=vector[opc-1];
        opc=0;
        
        cout<<"Tercer accesorio:";
        while(opc>num){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            opc=ConvertirNumero(opci);        
        }
        actual->mochila[2]=vector[opc-1];
        opc=0;

        cout<<"Cuarto accesorio:";
        while(opc>num){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            opc=ConvertirNumero(opci);        
        }
        actual->mochila[3]=vector[opc-1];
        opc=0;

        cout<<"Quinto accesorio:";
        while(opc>num){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            opc=ConvertirNumero(opci);        
        }
        actual->mochila[4]=vector[opc-1];
        opc=0;
        actual=actual->siguiente;   
    }
}

void Lealtad1v1(tPersonajePtr &j1, tPersonajePtr &j2, string nombre1, string nombre2){
    srand(time(NULL));
    int num = rand()%4;
    tPersonajePtr aux1;
    tPersonajePtr aux2;
    tPersonajePtr actual;
    tPersonajePtr temporal;


    if (num==0){
        cout<<"Ambos discursos han motivado a sus respectivas tropas...\n¡Estan listos para luchar por sus causas!"<<endl;
    }
    else if (num==1){
        cout<<"Parece que los discursos no han motivado a los novatos...\n¡Vaya! Parece que los novatos de ambos bandos han desistido de su causa"<<endl;
        
        actual=j1;
        while (actual->siguiente!=NULL){
            actual=actual->siguiente;
        }
        aux1=actual;
        delete actual;

        actual=j2;
        while (actual->siguiente!=NULL){
            actual=actual->siguiente;
        }
        aux2=actual;
        delete actual;

        actual=j1;
        while (actual->siguiente!=NULL){
            actual=actual->siguiente;
        }
        actual->siguiente=aux2;

        actual=j2;
        while (actual->siguiente!=NULL){
            actual=actual->siguiente;
        }
        actual->siguiente=aux1;

        cout<<"¡Parce ser que los novatos de ambas causas se cambiaron de bandos!\nLos bandos quedaron asi:"<<endl;
        cout<<nombre1<<endl;
        MostrarPersonajes(j1);
        cout<<"\n"<< nombre2<<endl;
        MostrarPersonajes(j2);
    }
    else if(num==2){
        cout<<"Parece que los discursos solo han motivado a los veteranos\n¡Casi todos los miembros de cada equipo han abandonado la causa!"<<endl;
        
        actual=j1->siguiente;
        aux1=actual;
        while(actual!=NULL){
            temporal = actual;
            actual = actual->siguiente;
            delete temporal;
        }

        actual=j2->siguiente;
        aux2=actual;
        while(actual!=NULL){
            temporal = actual;
            actual = actual->siguiente;
            delete temporal;
        }

        actual=j1;
        actual->siguiente=aux2;

        actual=j2;
        actual->siguiente=aux1;


        cout<<"¡Y se han cambiado de bando!\nLos bandos quedaron asi:"<<endl;
        cout<<nombre1<<endl;
        MostrarPersonajes(j1);
        cout<<"\n"<< nombre2<<endl;
        MostrarPersonajes(j2);
    }
    else{
        cout<<"Parece que los discursos han llegado al publico equivocado...\n"<<nombre1<<" parece haber motivado a los del bando de "<<nombre2<<endl;
        cout<<"Mientras que "<< nombre2<<" parece haber motivado al bando de "<<nombre1<<endl;
        
        
        aux1=j1;
        aux2=j2;
        j1=aux2;
        j2=aux1;


        cout<<"¡Todos se han cambiado de bando!\nLos bandos quedaron asi:"<<endl;
        cout<<nombre1<<endl;
        MostrarPersonajes(j1);
        cout<<"\n"<< nombre2<<endl;
        MostrarPersonajes(j2);
    }
}

tAmbientePtr LugarPelea(tAmbientePtr &ambientes){
    int i=0;
    int num;
    tAmbientePtr actual;

    while (actual->siguiente=NULL){
        actual=actual->siguiente;
        i += 1;
    }

    num= rand()%i;

    actual=ambientes;
    i=0;

    while (i != num){
        actual=actual->siguiente;
        i += 1;
    }

    return actual;
}

tPersonajePtr ElegirPersonaje(tPersonajePtr jp, string nombre){
    string name_aux;
    tPersonajePtr actual=jp;
    cout<<"Para este ataque"<< nombre << "va a mandar a "<<endl;
    
    MostrarPersonajes(jp);
    cout<<("Insique el nombre de a quien va a mandar:");
    getline(cin,name_aux);

    while(name_aux != actual->nombre){
        actual=actual->siguiente;
        
        if (actual==NULL){
            cout<<"Capitan este soldado no es parte de su flota, escoga uno que pertenezca a la flota actual:"<<endl;
            getline(cin,name_aux);
            actual=jp;
        }
    }

    system("cls");

    return actual;
}

void MochilaDeBatalla(tPersonajePtr personaje){
    cout<<"Su personaje solo puede llevar 3 accesorios a la batalla, ¿Cuales va a llevar?"<<endl;
    int opc;
    string opci;
    int aux1;
    int aux2;

    cout<<"Espacio 1"<<endl;
    //validacion que el usurio ingrese un numero entre el 1 al 5
    for (int i=0; i<5; i++){
        cout<<i+1<<". "<<personaje->mochila[i]->nombre<<endl;
    }
    getline(cin,opci);
    opc=ConvertirNumero(opci);
    while(opc>5){
        cout<<"Ingrese un numero entre el 1 y el 5"<<endl;
        getline(cin,opci);
        opc=ConvertirNumero(opci);
    }
    aux1=opc;
    personaje->mochila_b[0]=personaje->mochila[opc-1];

    //system("cls");

    while (aux1 == opc){
        cout<<"Espacio 2"<<endl;
        //validacion que el usurio ingrese un numero entre el 1 al 5
        for (int i=0; i<5; i++){
            cout<<i+1<<". "<<personaje->mochila[i]->nombre<<endl;
        }
        getline(cin,opci);
        opc=ConvertirNumero(opci);
        while(opc>5){
            cout<<"Ingrese un numero entre el 1 y el 5"<<endl;
            getline(cin,opci);
            opc=ConvertirNumero(opci);
        }
        aux2=opc;
        personaje->mochila_b[1]=personaje->mochila[opc-1];
        if (aux1==opc){
            cout<<"Ya ese accesorio esta seleccionado, intenta elegir otro"<<endl;
        }
    }

    //system("cls");

    while (aux1 == opc or aux2 == opc){
        cout<<"Espacio 3"<<endl;
        //validacion que el usurio ingrese un numero entre el 1 al 5
        for (int i=0; i<5; i++){
            cout<<i+1<<". "<<personaje->mochila[i]->nombre<<endl;
        }
        getline(cin,opci);
        opc=ConvertirNumero(opci);
        while(opc>5){
            cout<<"Ingrese un numero entre el 1 y el 5"<<endl;
            getline(cin,opci);
            opc=ConvertirNumero(opci);
        }
        personaje->mochila_b[2]=personaje->mochila[opc-1];
        if (aux1==opc){
            cout<<"Ya ese accesorio esta seleccionado, intenta elegir otro"<<endl;
        }
        if (aux2==opc){
            cout<<"Ya ese accesorio esta seleccionado, intenta elegir otro"<<endl;
        }
    }

    //system("cls");
    
    cout<<"La mochila para la batalla de"<<personaje->nombre<<"queda asi:"<<endl;
    for (int i=0; i<3; i++){
        cout<<i+1<<". "<<personaje->mochila_b[i]->nombre<<endl;
    }

    //system("cls");
}

void RecuperarVida(tPersonajePtr &p, tRazaPtr &r, tPersonajePtr pa){
    tPersonajePtr actual=p;
    tRazaPtr actualr=r;
    while (actual!=NULL){
        if (actual != pa){
            while(actualr->nombre != actual->raza){
                actualr=actualr->siguiente;
            }
            if (actual->salud < actualr->salud){
                if (actual->salud > actualr->salud*0.60){
                    actual->salud += actualr->salud*0.15;
                }
                else{
                    actual->salud += actualr->salud*0.05;
                }
                
                if (actual->salud > actualr->salud){
                    actual->salud = actualr->salud;
                }
            }
        }
        actual=actual->siguiente;
        actualr=r;
    }
}

void RecuperarEnergia(tPersonajePtr p, tRazaPtr &r){
    tPersonajePtr actual=p;
    tRazaPtr actualr=r;
     
    while(actualr->nombre != actual->raza){
        actualr=actualr->siguiente;
    }
    if (actual->energia < actualr->energia){
        actual->salud += actualr->salud*0.25;
        
        if (actual->salud > actualr->salud){
            actual->salud = actualr->salud;
        }
    }

    cout<<p->nombre<<"Recupero algo de energia"<<endl;
        
}



void Batalla(tPersonajePtr p1, string j1, tPersonajePtr &prs1, tPersonajePtr p2, string j2, tPersonajePtr &prs2, int turnoi, tAmbientePtr lugar, tRazaPtr &razas){
    int efecto1v;
    int efecto1e;
    int efecto2v;
    int efecto2e;
    int conte1=0;
    int def1=0;
    int conte2=0;
    int def2=0;
    int fin=0;
    int t=1;
    int aux_def;
    int daño;
    int opv;
    string opc;
    int turno;

    turnoi+=1; 
    turno=turnoi;

    if (p1->raza != lugar->nombre){
        for (int i=0;i<3;i++){
            if (p1->mochila_b[i]->tipo=="Acondicionamiento" && p1->mochila_b[i]->recuperacion==lugar->nombre){
                efecto1v=0;
                efecto1e=0;
                cout<<p1->nombre<<"Logro ponerse con exito su"<<p1->mochila_b[i]->nombre<<"ahora se encuentra protegido para el planeta de la pelea"<<endl;
                break;
            }
            else{
                efecto1v=(p1->salud)/3;
                efecto1e=(p1->energia)/3;
                turnoi=0;
            }
            if(p1->mochila_b[i]->tipo=="Acondicionamiento" && p1->mochila_b[i]->recuperacion!=lugar->nombre){
                cout<<"El accesorio"<<p1->mochila_b[i]->nombre<<p1->nombre<<"lo considero inutil asi que lo dejo..."<<endl;
            }
        }
    }

    if (p2->raza != lugar->nombre){
        for (int i=0;i<3;i++){
            if (p2->mochila_b[i]->tipo=="Acondicionamiento" && p2->mochila_b[i]->recuperacion==lugar->nombre){
                efecto2v=0;
                efecto2e=0;
                cout<<p2->nombre<<"Logro ponerse con exito su"<<p2->mochila_b[i]->nombre<<"ahora se encuentra protegido para el planeta de la pelea"<<endl;
                break;
            }
            else{
                efecto2v=(p2->salud)/3;
                efecto2e=(p2->energia)/3;
                turnoi=1;
            }

            if(p2->mochila_b[i]->tipo=="Acondicionamiento" && p2->mochila_b[i]->recuperacion!=lugar->nombre){
                cout<<"El accesorio"<<p2->mochila_b[i]->nombre<<p2->nombre<<"lo considero inutil asi que lo dejo..."<<endl;
            }
        }
    }

    
    while(fin==0){
        if (turno%2==0){
            cout<<"TURNO"<<t<<":"<<j1<<endl;
            cout<<j1<<"                                          "<<j2<<endl;
            cout<<p1->nombre<<"                                "<<p2->nombre<<endl;
            cout<<"웃                                                  웃"<<endl;
            cout<<"Vida:                                            Vida:"<<endl;
            cout<<p1->salud<<"                                 "<<p2->salud<<endl;
            cout<<"Energia:                                          Energia:"<<endl;
            cout<<p1->energia<<"                                 "<<p2->energia<<endl;

            if (p1->mochila_b[0]->valor == 0 && p1->mochila_b[1]->valor == 0 && p1->mochila_b[2]->valor == 0){
                cout<<"Parece que"<<p1->nombre<<"no tiene nada que usar para la batalla"<<endl;
                cout<<"¡"<<p2->nombre<<"aprovecho la confusion para matarlo por la espalda!"<<endl;
                p1->salud=0;
            }
            else{
                cout<<"¿Que vas a usar?"<<j1<<endl;
                for (int i=0; i<3; i++){
                    if (p1->mochila_b[i]->valor != 0){
                        cout<<i+1<<p1->mochila_b[i]->nombre<<endl;
                        cout<<p1->mochila_b[i]->tipo<<endl<<"Valor:"<<p1->mochila_b[i]->valor<<endl<<"Resta"<<p1->mochila_b[i]->energia<<"de energia su uso";
                        if (p1->mochila_b[i]->tipo == "Defensa"){
                            cout<<"Cubre"<<p1->mochila_b[i]->contenedor<<endl;
                        }
                        if (p1->mochila_b[i]->tipo == "Supervivencia"){
                            cout<<"Recupera la "<<p1->mochila_b[i]->recuperacion<<endl;
                        }
                    }
                }
                getline(cin,opc);
                ValidarUso(opc,p1,opv);

                if (p1->mochila_b[opv]->tipo == "Ataque"){
                    daño=p1->mochila_b[opv]->valor - def2;
                    if (daño<1){
                        cout<<"¡El ataque no le hizo ni cosquillas a"<<p2->nombre<<endl;
                    }
                    else{
                        if (conte2==0){
                            cout<<p2->nombre<<"perdio"<<daño<<"de vida"<<endl;
                            p2->salud-=daño;    
                        }
                        else{
                            cout<<p2->nombre<<"perdio"<<daño<<"de vida"<<endl;
                            conte2-=daño;
                            if (conte2>=0){
                                cout<<"¡Pero parece que el objeto de defensa de"<<p2->nombre<<"contubo todo el golpe!"<<endl;
                                p2->mochila_b[aux_def]->contenedor=conte2;
                            }
                            else{
                                cout<<"¡Pero parece que el objeto de defensa de"<<p2->nombre<<"contubo parte del golpe!"<<endl;
                                p2->salud+=conte2;
                                p2->mochila_b[aux_def]->contenedor=0;
                            }
                        }
                    }
                    cout<<p1->nombre<<"perdio"<<p1->mochila_b[opv]->energia<<"energia"<<endl;
                    p1->energia-=p1->mochila_b[opv]->energia;
                    def2=0;
                    conte2=0;
                    daño=0;
                }
                else if (p1->mochila_b[opv]->tipo == "Defensa"){
                    conte1=p1->mochila_b[opv]->contenedor;
                    aux_def=opv;
                    def1=p1->mochila_b[opv]->valor;
                    cout<<"El proximo ataque de tu rival hace"<<p1->mochila_b[opv]->valor<<"menos de daño"<<endl;
                    cout<<"Optubiste una covertura de"<<p1->mochila_b[opv]->contenedor<<"de daños"<<endl;
                    cout<<p1->nombre<<"perdio"<<p1->mochila_b[opv]->energia<<"energia"<<endl;
                    p1->energia-=p1->mochila_b[opv]->energia;
                    
                }
                else if (p1->mochila_b[opv]->tipo == "Supervivencia"){
                    if (p1->mochila_b[opv]->recuperacion=="Salud"){
                        cout<<p1->nombre<<"ha recuperado"<<p1->mochila_b[opv]->valor<<"de vida"<<endl;
                        cout<<p1->nombre<<"perdio"<<p1->mochila_b[opv]->energia<<"energia"<<endl;
                        p1->salud+=p1->mochila_b[opv]->valor;
                        p1->energia-=p1->mochila_b[opv]->energia;
                    }
                    else if (p1->mochila_b[opv]->recuperacion=="Energia"){
                        cout<<p1->nombre<<"ha recuperado"<<p1->mochila_b[opv]->valor<<"de energia"<<endl;
                        cout<<p1->nombre<<"perdio"<<p1->mochila_b[opv]->energia<<"energia"<<endl;
                        p1->energia+=p1->mochila_b[opv]->valor;
                        p1->energia-=p1->mochila_b[opv]->energia;
                    }
                    
                }
                p1->energia-=efecto1e;
                p1->salud-=efecto1v;
                cout<<"Resumen del turno:"<<endl;
                cout<<p1->nombre<<endl;
                cout<<"Vida:"<<p1->salud<<endl;
                cout<<"Energia:"<<p1->energia<<endl;
                cout<<p2->nombre<<endl;
                cout<<"Vida:"<<p2->salud<<endl;
                cout<<"Energia:"<<p2->energia<<endl;

                if (p1->energia <= 0 && p2->salud<=0){
                    fin=3;
                }
                else if (p1->energia<=0){
                    fin=1;
                }
                else if (p2->salud<=0){
                    fin=2;
                }
                else{
                    fin=0;
                    t+=1;
                    turno+=1;
                }
                
            }

        }
        else{
            cout<<"TURNO"<<t<<":"<<j2<<endl;
            cout<<j2<<"                                          "<<j1<<endl;
            cout<<p2->nombre<<"                                "<<p1->nombre<<endl;
            cout<<"웃                                                  웃"<<endl;
            cout<<"Vida:                                            Vida:"<<endl;
            cout<<p2->salud<<"                                 "<<p1->salud<<endl;
            cout<<"Energia:                                          Energia:"<<endl;
            cout<<p2->energia<<"                                 "<<p1->energia<<endl;

            if (p2->mochila_b[0]->valor == 0 && p2->mochila_b[1]->valor == 0 && p2->mochila_b[2]->valor == 0){
                cout<<"Parece que"<<p2->nombre<<"no tiene nada que usar para la batalla"<<endl;
                cout<<"¡"<<p1->nombre<<"aprovecho la confusion para matarlo por la espalda!"<<endl;
                p1->salud=0;
            }
            else{
                cout<<"¿Que vas a usar?"<<j2<<endl;
                for (int i=0; i<3; i++){
                    if (p2->mochila_b[i]->valor != 0){
                        cout<<i+1<<p2->mochila_b[i]->nombre<<endl;
                        cout<<p2->mochila_b[i]->tipo<<endl<<"Valor:"<<p2->mochila_b[i]->valor<<endl<<"Resta"<<p2->mochila_b[i]->energia<<"de energia su uso";
                        if (p2->mochila_b[i]->tipo == "Defensa"){
                            cout<<"Cubre"<<p1->mochila_b[i]->contenedor<<endl;
                        }
                        if (p2->mochila_b[i]->tipo == "Supervivencia"){
                            cout<<"Recupera la "<<p2->mochila_b[i]->recuperacion<<endl;
                        }
                    }
                }
                getline(cin,opc);
                ValidarUso(opc,p2,opv);

                if (p2->mochila_b[opv]->tipo == "Ataque"){
                    daño=p2->mochila_b[opv]->valor - def1;
                    if (daño<1){
                        cout<<"¡El ataque no le hizo ni cosquillas a"<<p1->nombre<<endl;
                    }
                    else{
                        if (conte1==0){
                            cout<<p1->nombre<<"perdio"<<daño<<"de vida"<<endl;
                            p1->salud-=daño;    
                        }
                        else{
                            cout<<p1->nombre<<"perdio"<<daño<<"de vida"<<endl;
                            conte1-=daño;
                            if (conte2>=0){
                                cout<<"¡Pero parece que el objeto de defensa de"<<p1->nombre<<"contubo todo el golpe!"<<endl;
                                p1->mochila_b[aux_def]->contenedor=conte1;
                            }
                            else{
                                cout<<"¡Pero parece que el objeto de defensa de"<<p1->nombre<<"contubo parte del golpe!"<<endl;
                                p1->salud+=conte1;
                                p1->mochila_b[aux_def]->contenedor=0;
                            }
                        }
                    }
                    cout<<p2->nombre<<"perdio"<<p2->mochila_b[opv]->energia<<"energia"<<endl;
                    p2->energia-=p2->mochila_b[opv]->energia;
                    def1=0;
                    conte1=0;
                    daño=0;
                }
                else if (p2->mochila_b[opv]->tipo == "Defensa"){
                    conte2=p2->mochila_b[opv]->contenedor;
                    aux_def=opv;
                    def2=p2->mochila_b[opv]->valor;
                    cout<<"El proximo ataque de tu rival hace"<<p2->mochila_b[opv]->valor<<"menos de daño"<<endl;
                    cout<<"Optubiste una covertura de"<<p2->mochila_b[opv]->contenedor<<"de daños"<<endl;
                    cout<<p2->nombre<<"perdio"<<p2->mochila_b[opv]->energia<<"energia"<<endl;
                    p2->energia-=p2->mochila_b[opv]->energia;
                    
                }
                else if (p2->mochila_b[opv]->tipo == "Supervivencia"){
                    if (p2->mochila_b[opv]->recuperacion=="Salud"){
                        cout<<p2->nombre<<"ha recuperado"<<p2->mochila_b[opv]->valor<<"de vida"<<endl;
                        cout<<p2->nombre<<"perdio"<<p2->mochila_b[opv]->energia<<"energia"<<endl;
                        p2->salud+=p2->mochila_b[opv]->valor;
                        p2->energia-=p2->mochila_b[opv]->energia;
                    }
                    else if (p2->mochila_b[opv]->recuperacion=="Energia"){
                        cout<<p2->nombre<<"ha recuperado"<<p2->mochila_b[opv]->valor<<"de energia"<<endl;
                        cout<<p2->nombre<<"perdio"<<p2->mochila_b[opv]->energia<<"energia"<<endl;
                        p2->energia+=p2->mochila_b[opv]->valor;
                        p2->energia-=p1->mochila_b[opv]->energia;
                    }
                    
                }
                p2->energia-=efecto2e;
                p2->salud-=efecto2v;
                cout<<"Resumen del turno:"<<endl;
                cout<<p2->nombre<<endl;
                cout<<"Vida:"<<p2->salud<<endl;
                cout<<"Energia:"<<p2->energia<<endl;
                cout<<p1->nombre<<endl;
                cout<<"Vida:"<<p1->salud<<endl;
                cout<<"Energia:"<<p1->energia<<endl;

                if (p2->energia <= 0 && p1->salud <= 0){
                    fin=3;
                }
                else if (p2->energia<=0){
                    fin=2;
                }
                else if (p1->salud<=0){
                    fin=1;
                }
                else{
                    fin=0;
                    t+=1;
                    turno+=1;
                }
                
            }

        }
    }
    if (fin==3){
        cout<<"¡Vaya! parece que ambos han caido en batalla"<<endl<<"¡Ningun bando gana!"<<endl;
    }
    else if(fin==2){
        cout<<"El peleador de"<<j2<<"ha caido en batalla, toda su energia ha sido abasorvida por el peleador de"<<j1<<endl;
        if(p2->energia > 0){
            p1->energia+=p2->energia;
        }
        EliminarPerosnajesPorNombre(prs2,p2);
        RecuperarEnergia(p1, razas);
    }
    else if(fin==1){
        cout<<"El peleador de"<<j1<<"ha caido en batalla, toda su energia ha sido abasorvida por el peleador de"<<j2<<endl;
        if(p1->energia > 0){
            p2->energia+=p1->energia;
        }
        EliminarPerosnajesPorNombre(prs1,p1);
        RecuperarEnergia(p2, razas);
    }
    turnoi+=1;
    RecuperarVida(prs1, razas, p1);
    RecuperarVida(prs2, razas, p2);
    cout<<"¡Aviso, los peleadores que no lucharon se recuperaron!"<<endl;
    system("cls");
}


//_____________________________________________________LECTRUAS_______________________________________________
//---------------------------------------------Ambientes-------------------------------------------
void AmbientesArchivo(const char* a, tAmbientePtr &amb, int l) {
    ifstream archivo(a);

    if (archivo.is_open()) {
        string nombre;
        tAmbientePtr actual = amb;
        tAmbientePtr ambi = new tAmbiente;

        while (archivo >> nombre) {
            if (nombre.size()>2){
                
                ambi->nombre = nombre;
                ambi->uso = false;
                ambi->siguiente = NULL;

                while(actual->siguiente!=NULL){
                    actual=actual->siguiente;
                }

                if (amb == NULL) {
                    amb = ambi;
                } else {
                    actual->siguiente = ambi;
                }

                actual = amb;
                l+=1;
            }
            
        }

        archivo.close();
        cout<<"Los ambientes se han cargado con exito"<<endl;
    } 
    else {
        cout << "Los datos han sido corrompidos en ambientes" << endl;
    }
}

//---------------------------------------------Accesorios---------------------------------------
void AccesoriosArchivo(const char*b, tAccesoriosPtr &acc, int l){
    ifstream archivo(b);

    if (archivo.is_open()) {
        string nombre;
        tAccesoriosPtr actual = acc;;
        int num=0;
        int aux=0;
        string caracter;
        int condicion=0;
        tAccesoriosPtr acce = new tAccesorios;

        while (archivo >> nombre){
            if (nombre.size()>2) {
                if (num=0){
                    acce->nombre=nombre;
                    num+=1;
                }
                else if (num=1){                 
                    for (int i = 0; i < nombre.size(); i++){
                        caracter=nombre[i];
                        if (condicion == 1){
                            acce->tipo = acce->tipo + caracter;
                        }        
                        if (caracter==":"){
                            condicion=1;
                        }
                    }
                    condicion=0;
                    num+=1;
                }
                else if (num=2){
                    for(int i = nombre.size(); i > -1; i--){
                        caracter=nombre[i];
                        if (caracter=="1"){
                            aux = (aux*10)+1;
                        }
                        else if (caracter=="2"){
                            aux = (aux*10)+2;
                        }
                        else if (caracter=="3"){
                            aux = (aux*10)+3;
                        }
                        else if (caracter=="4"){
                            aux = (aux*10)+4;
                        }
                        else if (caracter=="5"){
                            aux = (aux*10)+5;
                        }
                        else if (caracter=="6"){
                            aux = (aux*10)+6;
                        }
                        else if (caracter=="7"){
                            aux = (aux*10)+7;
                        }
                        else if (caracter=="8"){
                            aux = (aux*10)+8;
                        }
                        else if (caracter=="9"){
                            aux = (aux*10)+9;
                        }
                        else if (caracter=="0"){
                            aux = (aux*10);
                        }
                    }
                    acce->valor=aux;
                    aux=0;
                    num+=1;
                }
                else if (num=3){
                    for (int i = 0; i < nombre.size(); i++){
                        caracter=nombre[i];
                        if (condicion == 1){
                            acce->recuperacion = acce->recuperacion + caracter;
                        }        
                        if (caracter==":"){
                            condicion=1;
                        }
                    }
                    condicion=0;
                    num+=1;
                }
                else if (num=4){
                    for(int i = nombre.size(); i > -1; i--){
                        caracter=nombre[i];
                        if (caracter=="1"){
                            aux = (aux*10)+1;
                        }
                        else if (caracter=="2"){
                            aux = (aux*10)+2;
                        }
                        else if (caracter=="3"){
                            aux = (aux*10)+3;
                        }
                        else if (caracter=="4"){
                            aux = (aux*10)+4;
                        }
                        else if (caracter=="5"){
                            aux = (aux*10)+5;
                        }
                        else if (caracter=="6"){
                            aux = (aux*10)+6;
                        }
                        else if (caracter=="7"){
                            aux = (aux*10)+7;
                        }
                        else if (caracter=="8"){
                            aux = (aux*10)+8;
                        }
                        else if (caracter=="9"){
                            aux = (aux*10)+9;
                        }
                        else if (caracter=="0"){
                            aux = (aux*10);
                        }
                    }
                    acce->energia=aux;
                    aux=0;
                    num+=1;
                }
                else if (num=5){
                    for(int i = nombre.size(); i > -1; i--){
                        caracter=nombre[i];
                        if (caracter=="1"){
                            aux = (aux*10)+1;
                        }
                        else if (caracter=="2"){
                            aux = (aux*10)+2;
                        }
                        else if (caracter=="3"){
                            aux = (aux*10)+3;
                        }
                        else if (caracter=="4"){
                            aux = (aux*10)+4;
                        }
                        else if (caracter=="5"){
                            aux = (aux*10)+5;
                        }
                        else if (caracter=="6"){
                            aux = (aux*10)+6;
                        }
                        else if (caracter=="7"){
                            aux = (aux*10)+7;
                        }
                        else if (caracter=="8"){
                            aux = (aux*10)+8;
                        }
                        else if (caracter=="9"){
                            aux = (aux*10)+9;
                        }
                        else if (caracter=="0"){
                            aux = (aux*10);
                        }
                    }
                    acce->contenedor=aux;
                    aux=0;
                    acce->siguiente=NULL;

                    while(actual->siguiente!=NULL){
                        actual=actual->siguiente;
                    }
                    if (actual == NULL) {
                        acc = acce;
                    } 
                    else {
                        actual->siguiente = acce;
                    }
                    actual=acc;
                    l+=1;
                    num=0;

                }   
            }
        }

        archivo.close();
        cout<<"Los accesorios se han cargado con exito"<<endl;
    }
    else {
        cout << "Error al abrir el archivo" << endl;
    }
}

//---------------------------------------------Accesorios---------------------------------------
void RazasArchivo(const char*b, tRazaPtr &razas, int l, tAmbientePtr &ambientes){
    ifstream archivo(b);

    if (archivo.is_open()) {
        string nombre;
        tRazaPtr actual = razas;
        tAmbientePtr actual_amb = ambientes;
        int num=0;
        int aux=0;
        string caracter;
        int condicion=0;
        tRazaPtr r = new tRaza;

        while (archivo >> nombre){
            if (nombre.size()>2) {
                if (num=0){
                    r->nombre=nombre;
                    num+=1;
                }
                else if (num=1){
                    for(int i = nombre.size(); i > -1; i--){
                        caracter=nombre[i];
                        if (caracter=="1"){
                            aux = (aux*10)+1;
                        }
                        else if (caracter=="2"){
                            aux = (aux*10)+2;
                        }
                        else if (caracter=="3"){
                            aux = (aux*10)+3;
                        }
                        else if (caracter=="4"){
                            aux = (aux*10)+4;
                        }
                        else if (caracter=="5"){
                            aux = (aux*10)+5;
                        }
                        else if (caracter=="6"){
                            aux = (aux*10)+6;
                        }
                        else if (caracter=="7"){
                            aux = (aux*10)+7;
                        }
                        else if (caracter=="8"){
                            aux = (aux*10)+8;
                        }
                        else if (caracter=="9"){
                            aux = (aux*10)+9;
                        }
                        else if (caracter=="0"){
                            aux = (aux*10);
                        }
                    }
                    r->energia=aux;
                    aux=0;
                    num+=1;
                }
                else if (num=2){
                    for(int i = nombre.size(); i > -1; i--){
                        caracter=nombre[i];
                        if (caracter=="1"){
                            aux = (aux*10)+1;
                        }
                        else if (caracter=="2"){
                            aux = (aux*10)+2;
                        }
                        else if (caracter=="3"){
                            aux = (aux*10)+3;
                        }
                        else if (caracter=="4"){
                            aux = (aux*10)+4;
                        }
                        else if (caracter=="5"){
                            aux = (aux*10)+5;
                        }
                        else if (caracter=="6"){
                            aux = (aux*10)+6;
                        }
                        else if (caracter=="7"){
                            aux = (aux*10)+7;
                        }
                        else if (caracter=="8"){
                            aux = (aux*10)+8;
                        }
                        else if (caracter=="9"){
                            aux = (aux*10)+9;
                        }
                        else if (caracter=="0"){
                            aux = (aux*10);
                        }
                    }
                    r->salud=aux;
                    aux=0;
                    num+=1;
                    condicion=0;
                    num+=1;
                }
                else if (num=3){
                    while(actual_amb->nombre!=nombre){
                        actual_amb=actual_amb->siguiente;
                    }

                    actual_amb->uso=true;

                    r->planeta=nombre;
                    r->siguiente=NULL;

                    while(actual->siguiente!=NULL){
                        actual=actual->siguiente;
                    }

                    if (actual == NULL) {
                        razas = r;
                    
                    } 
                    else {
                        actual->siguiente = r;
                    }
                    actual=r;
                    l+=1;
                    num=0;
                    
                }   
            }
        }

        archivo.close();
        cout<<"Las razas se han cargado con exito"<<endl;
    }
    else {
        cout << "Error al abrir el archivo" << endl;
    }
}

//_____________________________________________________Main_______________________________________________
int main(){
    int l_amb=0;
    int l_acc=0;
    int l_p=0;
    int l_r=0;
    tAmbientePtr ambientes=NULL;
    tRazaPtr razas=NULL;
    tPersonajePtr personajes=NULL;
    tAccesoriosPtr accseorios=NULL;
    string opcion;
    string j1;
    string j2;
    tPersonajePtr j1p;
    tPersonajePtr j2p;
    tPersonajePtr peleador1;
    tPersonajePtr peleador2;
    tAmbientePtr lugar;
    int turno_i=rand()%2;
    int limite_cpu=0;
    string opc;
    string mn;

    cout << "The Big Red Fox 🦊 presenta:" << endl;
    cout << "     Starz: The gods talk to me     " << endl;
    cout<< " " << endl;
    //AmbientesArchivo("ambiente.inv", ambientes, l_amb);
    //RazasArchivo("especies.inv", razas,l_r ,ambientes);
    //AccesoriosArchivo("accesorios.inv", accseorios, l_acc);
    


    //--------------------------------------------------MENÚ--------------------------------------------------    
    while(mn != "0"){
        cout<<"--------------Menu Principal--------------"<<endl;
        cout << "1.Empezar Juego"<<endl;
        cout << "2.Creador de datos"<<endl;
        cout << "3.Eliminar datos"<<endl;
        cout << "0.Cerrar Juego"<<endl;
        cout<<"------------------------------------------"<<endl;
        cout<< "Ingrese la opcion que desee: ";
        getline(cin,mn);
        //system("cls");

        if(mn=="1"){
            //---------------------------------------------Eleccion de Jugadores-------------------------------------------
            if (ContarPersonajes(personajes) < 6){
                cout<<"No hay suficientes personajes para empezar la campaña"<<endl;
            }
            else{
                cout<<"Ingrese su nombre Jugador 1"<<endl;
                getline(cin,j1);
                PersonajesUsuarios(personajes, j1p);
                cout<<"Ingrese su nombre Jugador 2"<<endl;
                getline(cin,j2);
                PersonajesUsuarios(personajes, j2p);

                cout<<"Jugador "<<j1<<" indique cuales van a ser los accesorios de los siguentes personajes"<<endl;
                MostrarAccesorios(accseorios);
                AccesoriosUsuarios(j1p,accseorios);

                //system("cls");

                cout<<"Jugador "<<j2<<" indique cuales van a ser los accesorios de los siguentes personajes"<<endl;
                MostrarAccesorios(accseorios);
                AccesoriosUsuarios(j2p,accseorios);

                //system("cls");

                cout<<"La guerra esta por emepezar, pero antes ambos capitanes deberan dar un discruso para motivar a sus tropas"<<endl;
                cout<<"..."<<endl<<"Los discursos ya se han emitido por todos los confines de la galaxia"<<endl<<"Y parece que..."<<endl;
                Lealtad1v1(j1p,j2p,j1,j2);

                //system("cls");

                lugar=LugarPelea(ambientes);

                cout<<"Tras mucho tiempo de amenzas de guerra finalmente"<< j2 << "Decidio empezar su ataque en" <<lugar->nombre<< "Lugar donde residia una base de "<< j1 <<endl;

                //system("pause");
                //system("cls");

                while (j1p!=NULL and j2p!=NULL){
                    system("cls");
                    peleador1=ElegirPersonaje(j1p,j1);
                    peleador2=ElegirPersonaje(j2p,j2);
                    MochilaDeBatalla(peleador1);
                    MochilaDeBatalla(peleador2);
                    Batalla(peleador1, j1, j1p, peleador2, j2, j2p, turno_i, lugar, razas);
                }

                if(j1p!=NULL and j2p!=NULL){
                    cout<<"Ambos bandos han perdido, la batalla fue solo un monton de muertes...incesesarias"<<endl;
                }
                else if(j1p!=NULL){
                    cout<<j2<<"¡Es el ganador!"<<endl;
                }
                else if(j2p!=NULL){
                    cout<<j1<<"¡Es el ganador!"<<endl;
                }
            
                //system("cls");
                cout<<"¡FIN DEL JUEGO!\nGracias por jugar";
                mn="0";
            }

            /*cout<<"--------------Elige un modo--------------"<<endl;
            cout<<"|1. Jugador VS CPU"<<endl;
            cout<<"|2. Jugador VS Jugador"<<endl;
            cout<<"-----------------------------------------"<<endl;
            getline(cin,opcion);
            //VALIDAR QUE SE INGRESE UN 1 o UN 2
            //system("cls");
            if (opcion == "1"){
                J2="CPU";
                cout<<"Ingrese su nombre Jugador 1"<<endl;
                getline(cin,J1);
                PersonajesUsuarios(personajes, J1p);
                PersonajesCPU(personajes, J2p, limite_cpu);
            
                cout<<"Modo en desarrollo, disponible cuando nos de orientada a objetos ;)"<<endl;
                //system("pause");
            */
            
            
        }    

        if(mn=="2"){
            while (opc!="0"){
                cout<<"BIENVENIDO AL MENÚ DE CREACION DE BIG RED FOX 🦊"<<endl;
                cout<<"Elija que desea crear: "<<endl;
                cout<<"Para seleccionar la opción marque solamente el digito numerico"<<endl;
                cout<<"Por ejemplo si quisiera crear un ambiente marque solamente 3"<<endl;
                cout<<"1.Raza"<<endl;
                cout<<"2.Personaje"<<endl;
                cout<<"3.Ambiente"<<endl;
                cout<<"4.Accesorio"<<endl;
                cout<<"0. Salir del menu de creacion"<<endl;
                getline(cin,opc);

                
                if(opc=="1"){  //Crear Raza
                    IngresarRaza(razas,l_r,ambientes);
                }
                if(opc=="2"){ //Crear Personaje
                    IngresarPerosnaje(personajes,l_p,razas);
                }
                if(opc=="3"){
                    IngresarAmbiente(ambientes,l_amb);
                }
                if(opc=="4"){
                    IngresarAccesorio(accseorios,l_acc,ambientes);
                }
                if(opc=="0"){
                    cout<<"Regresando al menu"<<endl;
                }
                else{
                    cout<<"La opción no es válida, por favor introduzca una opción valida"<<endl;
                }
                
            }
            //system("cls");
            opc="ok";
        }
        if(mn=="3"){
            while(opc!="0"){
                cout<<"BIENVENIDO AL MENÚ DE ELIMINACION DE BIG RED FOX 🦊"<<endl;
                cout<<"Para seleccionar la opción marque solamente el digito numerico"<<endl;
                cout<<"Por ejemplo si quisiera eliminar un ambiente marque solamente 3"<<endl;
                cout<<"Que desea borrar?"<<endl;
                cout<<"1.Persoanje"<<endl;
                cout<<"2.Raza"<<endl;
                cout<<"3.Ambiente"<<endl;
                cout<<"4.Accesorio"<<endl;
                cout<<"0.Salir del menu de elimacion"<<endl;
                getline(cin,opc);

                if(opc=="1"){ //Eliminar personaje
                    EliminarPersonaje(personajes,l_p);
                    opc="0";
                }
                if(opc=="2"){ //Eliminar Raza
                    EliminarRaza(razas,l_r);
                    opc="0";
                }
                if(opc=="3"){ //Eliminar Ambiente
                    EliminarAmbiente(ambientes,l_amb);
                    opc="0";
                }
                if(opc=="4"){ //Eliminar Accesorio
                    EliminarAccesorio(accseorios,l_acc);
                    opc="0";
                }
                if(opc=="0"){ //Eliminar Accesorio
                    cout<<"Regresando al menu"<<endl;
                }
                else{
                    cout<<"La opción no es válida, por favor introduzca una opción valida"<<endl;
                }
            }
            //system("cls");
            opc="ok";
        }  
        else if(mn=="0"){
            cout<<"Cerrando el juego";

        }
        else{
            cout<<"La opción no es válida, por favor ingrese una opción de las anteriores"<<endl; 
        }
    }

    DestruirAccesorios(accseorios);
    DestruirPersonajes(personajes);
    DestruirPersonajes(j1p);
    DestruirPersonajes(j2p);
    DestruirRazas(razas);
    DestruirAmbientes(ambientes);
    DestruirAmbientes(lugar);

    return 0;
}