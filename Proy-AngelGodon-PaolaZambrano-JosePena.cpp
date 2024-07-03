#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

/*
Codigo realizado por: Angel Godon, Paola Zambrano y Jose Peña 
Materia: Estructrua de datos
*/

//_____________________________________________Estructuras_______________________________________
//--------------------------------------------------Ambientes--------------------------------------------------

struct tAmbiente{
    string nombre;
    //bool uso;
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
    //amb->uso=false;
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

void MostrarAmbientes(tAmbientePtr &a){
    int num=1;
    tAmbientePtr ambientes=a;
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
        istringstream(elim) >> eliminar;
        while((eliminar > num) and (eliminar < 1)){
            cout<<"Parece que no existe ese planeta en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
            getline(cin,elim);
            istringstream(elim) >> eliminar;
        }
        num=1;
        
        while(num != eliminar){
            anterior=actual;
            actual = actual->siguiente;
            num += 1;
        }
        
        temporal=actual;
        //if (temporal->uso==false){
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
        //}
        /*else{
            cout<<"¡ESPERA! Parece que exiten una o mas razas que pertenecen a este planeta"<<endl<<"Elimina primero la(s) raza(s) pertenecientes a este planeta"<<endl;
        }*/
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
    istringstream(select) >> seleccionar;
    while((seleccionar > num) and (seleccionar < 1)){
        cout<<"Parece que no existe ese planeta en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
        getline(cin,select);
        istringstream(select) >> seleccionar;
    }
    num=1;
    while(num != seleccionar){
        actual = actual->siguiente;
        num += 1;
    }
    //actual->uso=true;
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
    r=new(tRaza);
    cout<<"Parece que se ha registrado una nueva especie \n ¿Cual es el nommbre de esta especie?"<<endl;
    getline(cin,nombre);
    r->nombre=nombre;
    cout<<"¿Cual es la salud base de esta especie?"<<endl;
    getline(cin,sal);
    istringstream(sal) >> salud;
    r->salud=salud;
    cout<<"¿Cual es la energia base de esta especie?"<<endl;
    getline(cin,ene);
    istringstream(ene) >> energia;
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

void MostrarRazas(tRazaPtr &r){
    int num=1;
    tRazaPtr razas=r;
    if(razas != NULL){
        cout<<"------------------------------------------------------\n";
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
        istringstream(elim) >> eliminar;
        //Crear funcion de validacion
        while((eliminar > num) and (eliminar < 1)){
            cout<<"Parece que no existe ese planeta en nuestra base de datos\nIntenta ingresar uno de los que se muestran arriba"<<endl;
            getline(cin,elim);
            istringstream(elim) >> eliminar;
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
        istringstream(val) >> valor;
        acc->valor=valor;
        valor=0;
        cout<<"¿Cuanta energia resta su arma?"<<endl;
        getline(cin,val);
        istringstream(val) >> valor;
        acc->energia=valor;
        valor=0;
    }
    else if (tipo=="Defensa"){
        acc->recuperacion="";
        cout<<"¿Cuanto cubre su proteccion?"<<endl;
        getline(cin,val);
        istringstream(val) >> valor;
        acc->valor=valor;
        valor=0;
        cout<<"¿Cuanta energia resta su proteccion?"<<endl;
        getline(cin,val);
        istringstream(val) >> valor;
        acc->energia=valor;
        valor=0;
        cout<<"¿Cuanta vida extra le otorga su proteccion?"<<endl;
        getline(cin,val);
        istringstream(val) >> valor;
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
        istringstream(val) >> valor;
        acc->valor=valor;
        cout<<"¿Cuanta energia resta su uso?"<<endl;
        getline(cin,val);
        istringstream(val) >> valor;
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

void MostrarAccesorios(tAccesoriosPtr &a){
    int num=1;
    tAccesoriosPtr accesorios=a;
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
        istringstream(elim) >> eliminar;
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
    istringstream(select) >> seleccionar;

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

void MostrarPersonajes(tPersonajePtr &p){
    int num=1;
    tPersonajePtr personajes=p;
    if(personajes != NULL){
        cout<<"------------------------------------------------------\n";
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
        istringstream(elim) >> eliminar;
        while((eliminar > num) or (eliminar < 1)){
            cout<<"Parece que no existe ese estudiante en nuestra academia\nIntenta ingresar uno de los que se muestran arriba"<<endl;
            getline(cin,elim);
            istringstream(elim) >> eliminar;
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

int ValidarUso(string opc, tPersonajePtr p){
    int n;
    if (opc=="1"){
        if (p->mochila_b[0]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p);
        }
        else{
            n= 0;
        }
    }
    else if (opc=="2"){
        if (p->mochila_b[1]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p);
        }
        else{
            n= 1;
        }
    }
    else if (opc=="3"){
        if (p->mochila_b[2]->valor==0){
            cout<<"Parece ser que ese objeto ya fue utilizado, no se encuentra en la mochila del personaje\nSera mejor que selecciones uno de los que estan arriba"<<endl;
            getline(cin,opc);
            ValidarUso(opc,p);
        }
        else{
            n= 2;
        }
    }
    else{
        cout<<"Opcion no valida, ingrese una de las mostradas anteriormente"<<endl;
        getline(cin,opc);
        ValidarUso(opc,p);
    }
    return n;
}


//_________________________________________Funciones de la batalla_________________________________________
int ContarPersonajes(tPersonajePtr &p){
    int i=0;
    tPersonajePtr personajes=p;
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

void PersonajesUsuarios(tPersonajePtr &j, tRazaPtr &razas, string j1){
    cout<<""<<endl;
    string nombre;
    string raza;
    tRazaPtr r=razas;
    tPersonajePtr p1=new tPersonaje;
    tPersonajePtr p2=new tPersonaje;
    tPersonajePtr p3=new tPersonaje;

    cout<<"[PRIMER SOLDADO]"<<endl;
    cout<<"Nombre:"<<endl;
    getline(cin,nombre);
    cout<<"Escriba el nombre de a que raza pertenece: "<<endl;
    while(r != NULL){
        cout<<" - "<<r->nombre<<endl;
        r=r->siguiente;
    }
    r=razas;
    getline(cin,raza);
    cout<<""<<endl;
    while(raza != r->nombre){
        if (r != NULL){
            r=r->siguiente;
        }
        else{
            cout<<"¿Seguro que ingreso una de las razas anteriores "<<j1<<" ?"<<endl;
            cout<<"Intente ingresar alguna de las anteriores mostradas"<<endl;
            getline(cin,raza);
            r=razas;
        }
    }
    p1->nombre=nombre;
    p1->raza=raza;
    p1->salud=r->salud;
    p1->energia=r->energia;
    r=razas;
    cout<<""<<endl;

    cout<<"[SEGUNDO SOLDADO]"<<endl;
    cout<<"Nombre:"<<endl;
    getline(cin,nombre);
    cout<<"Escriba el nombre de a que raza pertenece: "<<endl;
    while(r != NULL){
        cout<<" - "<<r->nombre<<endl;
        r=r->siguiente;
    }
    r=razas;
    getline(cin,raza);
    cout<<""<<endl;
    while(raza != r->nombre){
        if (r != NULL){
            r=r->siguiente;
        }
        else{
            cout<<"¿Seguro que ingreso una de las razas anteriores "<<j1<<" ?"<<endl;
            cout<<"Intente ingresar alguna de las anteriores mostradas"<<endl;
            getline(cin,raza);
            r=razas;
        }
    }
    p2->nombre=nombre;
    p2->raza=raza;
    p2->salud=r->salud;
    p2->energia=r->energia;
    r=razas;
    cout<<""<<endl;
    
    cout<<"[TERCER SOLDADO]"<<endl;
    cout<<"Nombre:"<<endl;
    getline(cin,nombre);
    cout<<"Escriba el nombre de a que raza pertenece: "<<endl;
    while(r != NULL){
        cout<<" - "<<r->nombre<<endl;
        r=r->siguiente;
    }
    r=razas;
    getline(cin,raza);
    cout<<""<<endl;
    while(raza != r->nombre){
        if (r != NULL){
            r=r->siguiente;
        }
        else{
            cout<<"¿Seguro que ingreso una de las razas anteriores "<<j1<<" ?"<<endl;
            cout<<"Intente ingresar alguna de las anteriores mostradas"<<endl;
            getline(cin,raza);
            r=razas;
        }
    }
    p3->nombre=nombre;
    p3->raza=raza;
    p3->salud=r->salud;
    p3->energia=r->energia;
    r=razas;
    cout<<""<<endl;

    p1->siguiente=p2;
    p2->siguiente=p3;
    p3->siguiente=NULL;

    j=p1;
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

    MostrarAccesorios(acc);

    while(actual!=NULL){

        cout<<"Que accesorios les va a poner a "<<actual->nombre<<"?"<<endl;
        cout<<"(Ingrese el numero que se encuetnra antes del nombre)"<<endl;
        cout<<"Primer accesorio:"<<endl;
        getline(cin,opci);
        istringstream(opci) >> opc;
        while(opc>num or opc==0){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            istringstream(opci) >> opc;       
        }
        actual->mochila[0]=vector[opc-1];

        cout<<"Segundo accesorio:";
        getline(cin,opci);
        istringstream(opci) >> opc;
        while(opc>num or opc==0){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
        istringstream(opci) >> opc;        
        }
        actual->mochila[1]=vector[opc-1];
        
        cout<<"Tercer accesorio:";
        getline(cin,opci);
        istringstream(opci) >> opc;
        while(opc>num or opc==0){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            istringstream(opci) >> opc;       
        }
        actual->mochila[2]=vector[opc-1];
        opc=0;

        cout<<"Cuarto accesorio:";
        getline(cin,opci);
        istringstream(opci) >> opc;
        while(opc>num or opc==0){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            istringstream(opci) >> opc;       
        }
        actual->mochila[3]=vector[opc-1];
        opc=0;

        cout<<"Quinto accesorio:";
        getline(cin,opci);
        istringstream(opci) >> opc;
        while(opc>num or opc==0){
            cout<<"Ese accesorio no esta diponible, escoge uno de los que estan arriba."<<endl;
            getline(cin,opci);
            istringstream(opci) >> opc;        
        }
        actual->mochila[4]=vector[opc-1];
        opc=0;
        actual=actual->siguiente;   
    }
}

void Lealtad1v1(tPersonajePtr &j1, tPersonajePtr &j2, string nombre1, string nombre2){
    srand(time(NULL));
    int num = rand()%2;
    tPersonajePtr aux1;
    tPersonajePtr aux2;
    tPersonajePtr actual;
    tPersonajePtr temporal;


    if (num==0){
        cout<<"Ambos discursos han motivado a sus respectivas tropas...\n¡Estan listos para luchar por sus causas!"<<endl;
    }
    /*else if (num==1){
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
        while (actual->siguiente != NULL){
            actual=actual->siguiente;
        }
        actual->siguiente=aux2;

        actual=j2;
        while (actual->siguiente != NULL){
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
    }*/
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

tAmbientePtr LugarPelea(tAmbientePtr &ambientes, int n){
    srand(time(NULL));
    int num = n;
    int i=1;
    tAmbientePtr actual=ambientes;

    while (i != num){
        if (actual->siguiente==NULL){
            i=num;
        }
        else{
            actual=actual->siguiente;
            i += 1;
        }
        
    }

    return actual;
}

tPersonajePtr ElegirPersonaje(tPersonajePtr jp, string nombre){
    string n_aux;
    int n;
    int i=0;
    tPersonajePtr actual=jp;
    tPersonajePtr p=jp;
    while(actual != NULL){
        actual = actual->siguiente;
        i+=1;
    }

    cout<<"Para este ataque "<< nombre << " va a mandar a: "<<endl;
    cout<<"(Indique solo el numero que esta antes del nombre)"<<endl;
    
    MostrarPersonajes(jp);

    getline(cin,n_aux);
    istringstream(n_aux) >> n;

    while(n>i or n==0){
        cout<<n_aux<<" no es una opcion valida, ingresa una de las mostradas anteriormente"<<endl;
        getline(cin,n_aux);
        istringstream(n_aux) >> n;
    }

    i=1;

    while(p!=NULL){
        if (n != i){
            p = p->siguiente;
            i+=1;
        }
        else{
            break;
        }
    }

    return p;
}

void MochilaDeBatalla(tPersonajePtr personaje){
    cout<<personaje->nombre<<" solo puede llevar 3 accesorios a la batalla, ¿Cuales va a llevar?"<<endl;
    int opc;
    string opci;
    int aux1;
    int aux2;
    cout<<""<<endl;

    for (int i=0; i<5; i++){
        cout<<i+1<<". "<<personaje->mochila[i]->nombre<<endl;
    }
    cout<<""<<endl;
    cout<<"Espacio 1:";
    //validacion que el usurio ingrese un numero entre el 1 al 5
    getline(cin,opci);
    istringstream(opci) >> opc;
    while(opc>5 or opc==0){
        cout<<"Ingrese un numero entre el 1 y el 5"<<endl;
        getline(cin,opci);
        istringstream(opci) >> opc;
    }
    aux1=opc;
    personaje->mochila_b[0]=personaje->mochila[opc-1];

    while (aux1 == opc){
        cout<<"Espacio 2:";
        getline(cin,opci);
        istringstream(opci) >> opc;
        while(opc>5 or opc==0){
            cout<<"Ingrese un numero entre el 1 y el 5"<<endl;
            getline(cin,opci);
            istringstream(opci) >> opc;
        }
        aux2=opc;
        personaje->mochila_b[1]=personaje->mochila[opc-1];
        if (aux1==opc){
            cout<<"Ya ese accesorio esta seleccionado, intenta elegir otro"<<endl;
        }
    }

    //system("cls");

    while (aux1 == opc or aux2 == opc){
        cout<<"Espacio 3:";
        getline(cin,opci);
        istringstream(opci) >> opc;
        while(opc>5 or opc==0){
            cout<<"Ingrese un numero entre el 1 y el 5"<<endl;
            getline(cin,opci);
            istringstream(opci) >> opc;
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
    cout<<""<<endl;
    cout<<"La mochila para la batalla de "<<personaje->nombre<<" queda asi:"<<endl;
    for (int i=0; i<3; i++){
        cout<<i+1<<". "<<personaje->mochila_b[i]->nombre<<endl;
    }
    cout<<""<<endl;

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

    cout<<p->nombre<<" recupero algo de energia"<<endl;
        
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
                cout<<p1->nombre<<" logro ponerse con exito su"<<p1->mochila_b[i]->nombre<<" ahora se encuentra protegido para el planeta de la pelea"<<endl;
                break;
            }
            else{
                efecto1v=(p1->salud)/3;
                efecto1e=(p1->energia)/3;
                turnoi=0;
            }
            if(p1->mochila_b[i]->tipo=="Acondicionamiento" && p1->mochila_b[i]->recuperacion!=lugar->nombre){
                cout<<"El accesorio "<<p1->mochila_b[i]->nombre<<" "<<p1->nombre<<" lo considero inutil asi que lo dejo..."<<endl;
            }
        }
    }

    if (p2->raza != lugar->nombre){
        for (int i=0;i<3;i++){
            if (p2->mochila_b[i]->tipo=="Acondicionamiento" && p2->mochila_b[i]->recuperacion==lugar->nombre){
                efecto2v=0;
                efecto2e=0;
                cout<<p2->nombre<<" logro ponerse con exito su "<<p2->mochila_b[i]->nombre<<" ahora se encuentra protegido para el planeta de la pelea"<<endl;
                break;
            }
            else{
                efecto2v=(p2->salud)/3;
                efecto2e=(p2->energia)/3;
                turnoi=1;
            }

            if(p2->mochila_b[i]->tipo=="Acondicionamiento" && p2->mochila_b[i]->recuperacion!=lugar->nombre){
                cout<<"El accesorio "<<p2->mochila_b[i]->nombre<<" "<<p2->nombre<<" lo considero inutil asi que lo dejo..."<<endl;
            }
        }
    }

    
    while(fin==0){
        if (turno%2==0){
            cout<<"TURNO "<<t<<": "<<j1<<endl;
            cout<<p1->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p1->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p1->energia<<endl;

            cout<<""<<endl;

            cout<<p2->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p2->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p2->energia<<endl;
            

            if (p1->mochila_b[0]->valor == 0 && p1->mochila_b[1]->valor == 0 && p1->mochila_b[2]->valor == 0){
                cout<<"Parece que "<<p1->nombre<<" no tiene nada que usar para la batalla"<<endl;
                cout<<"¡ "<<p2->nombre<<" aprovecho la confusion para matarlo por la espalda!"<<endl;
                p1->salud=0;
            }
            else{
                cout<<"¿Que vas a usar? "<<j1<<endl;
                for (int i=0; i<3; i++){
                    if (p1->mochila_b[i]->valor != 0){
                        cout<<i+1<<". "<<p1->mochila_b[i]->nombre<<endl;
                        cout<<p1->mochila_b[i]->tipo<<endl;
                        cout<<"Valor: "<<p1->mochila_b[i]->valor<<endl;
                        cout<<"Su uso resta "<<p1->mochila_b[i]->energia<<" de energia"<<endl;

                        if (p1->mochila_b[i]->tipo == "Defensa"){
                            cout<<"Cubre "<<p1->mochila_b[i]->contenedor<<endl;
                        }
                        if (p1->mochila_b[i]->tipo == "Supervivencia"){
                            cout<<"Recupera la "<<p1->mochila_b[i]->recuperacion<<endl;
                        }
                    }
                }
                getline(cin,opc);
                opv=ValidarUso(opc,p1);

                if (p1->mochila_b[opv]->tipo == "Ataque"){
                    daño= p1->mochila_b[opv]->valor - def2;
                    if (daño<1){
                        cout<<"El ataque no le hizo ni cosquillas a" <<p2->nombre<<" !"<<endl;
                    }
                    else{
                        if (conte2==0){
                            cout<<p2->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            p2->salud= p2->salud - daño;    
                        }
                        else{
                            cout<<p2->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            conte2= conte2 - daño;
                            if (conte2 >= 0){
                                cout<<"¡Pero parece que el objeto de defensa de "<<p2->nombre<<" contubo todo el golpe!"<<endl;
                                p2->mochila_b[aux_def]->contenedor=conte2;
                            }
                            else{
                                cout<<"¡Pero parece que el objeto de defensa de "<<p2->nombre<<" contubo parte del golpe!"<<endl;
                                p2->salud = p2->salud+conte2;
                                p2->mochila_b[aux_def]->contenedor=0;
                            }
                        }
                    }
                    cout<<p1->nombre<<" perdio "<<p1->mochila_b[opv]->energia<<" de energia "<<endl;
                    p1->energia=p1->energia - p1->mochila_b[opv]->energia;
                    def2=0;
                    conte2=0;
                    daño=0;
                }
                else if (p1->mochila_b[opv]->tipo == "Defensa"){
                    conte1=p1->mochila_b[opv]->contenedor;
                    aux_def=opv;
                    def1=p1->mochila_b[opv]->valor;
                    cout<<"El proximo ataque de tu rival hace "<<p1->mochila_b[opv]->valor<<" menos de daño"<<endl;
                    cout<<"Optubiste una covertura de "<<p1->mochila_b[opv]->contenedor<<" de daños"<<endl;
                    cout<<p1->nombre<<" perdio "<<p1->mochila_b[opv]->energia<<" energia"<<endl;
                    p1->energia=p1->energia - p1->mochila_b[opv]->energia;
                    
                }
                else if (p1->mochila_b[opv]->tipo == "Supervivencia"){
                    if (p1->mochila_b[opv]->recuperacion=="Salud"){
                        cout<<p1->nombre<<" ha recuperado "<<p1->mochila_b[opv]->valor<<" de vida "<<endl;
                        cout<<p1->nombre<<" perdio "<<p1->mochila_b[opv]->energia<<" energia "<<endl;
                        p1->salud=p1->salud+p1->mochila_b[opv]->valor;
                        p1->energia=p1->energia-p1->mochila_b[opv]->energia;
                        p1->mochila_b[opv]->valor=0;
                    }
                    else if (p1->mochila_b[opv]->recuperacion=="Energia"){
                        cout<<p1->nombre<<" ha recuperado "<<p1->mochila_b[opv]->valor<<" de energia "<<endl;
                        cout<<p1->nombre<<" perdio "<<p1->mochila_b[opv]->energia<<" energia "<<endl;
                        p1->energia+=p1->mochila_b[opv]->valor;
                        p1->energia-=p1->mochila_b[opv]->energia;
                        p1->mochila_b[opv]->valor=0;
                    }
                    
                }
                if (efecto1e!=0){
                    p1->energia=p1->energia-efecto1e;
                    cout<<p1->nombre<<" perdio"<< efecto1e<< "de energia por no estar  con proteccion"<<endl;
                    p1->salud=p1->salud-efecto1v;
                    cout<<p1->nombre<<" perdio"<< efecto1e<< "de vida por no estar  con proteccion"<<endl;
                }
                
                cout<<""<<endl;
                cout<<"Resumen del turno:"<<endl;
                cout<<p1->nombre<<endl;
                cout<<"Vida:"<<p1->salud<<endl;
                cout<<"Energia:"<<p1->energia<<endl;
                cout<<""<<endl;
                cout<<p2->nombre<<endl;
                cout<<"Vida:"<<p2->salud<<endl;
                cout<<"Energia:"<<p2->energia<<endl;
                cout<<""<<endl;

                if (p1->energia <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->energia <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->energia<=0){
                    fin=1;
                }
                else if (p1->salud<=0){
                    fin=1;
                }
                else if (p2->salud<=0){
                    fin=2;
                }
                else if (p2->energia<=0){
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
            cout<<"TURNO "<<t<<": "<<j2<<endl;
            cout<<p2->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p2->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p2->energia<<endl;

            cout<<""<<endl;

            cout<<p1->nombre<<endl;
            cout<<"웃"<<endl;
            cout<<"Vida:"<<endl;
            cout<<p1->salud<<endl;
            cout<<"Energia:"<<endl;
            cout<<p1->energia<<endl;
            

            if (p2->mochila_b[0]->valor == 0 && p2->mochila_b[1]->valor == 0 && p2->mochila_b[2]->valor == 0){
                cout<<"Parece que "<<p2->nombre<<" no tiene nada que usar para la batalla"<<endl;
                cout<<"¡ "<<p1->nombre<<" aprovecho la confusion para matarlo por la espalda!"<<endl;
                p2->salud=0;
            }
            else{
                cout<<"¿Que vas a usar? "<<j2<<endl;
                for (int i=0; i<3; i++){
                    if (p2->mochila_b[i]->valor != 0){
                        cout<<i+1<<". "<<p2->mochila_b[i]->nombre<<endl;
                        cout<<p2->mochila_b[i]->tipo<<endl;
                        cout<<"Valor: "<<p2->mochila_b[i]->valor<<endl;
                        cout<<"Su uso resta "<<p2->mochila_b[i]->energia<<" de energia"<<endl;

                        if (p2->mochila_b[i]->tipo == "Defensa"){
                            cout<<"Cubre "<<p2->mochila_b[i]->contenedor<<endl;
                        }
                        if (p2->mochila_b[i]->tipo == "Supervivencia"){
                            cout<<"Recupera la "<<p2->mochila_b[i]->recuperacion<<endl;
                        }
                    }
                }
                getline(cin,opc);
                opv=ValidarUso(opc,p2);

                if (p2->mochila_b[opv]->tipo == "Ataque"){
                    daño=p1->mochila_b[opv]->valor - def2;
                    if (daño<1){
                        cout<<"El ataque no le hizo ni cosquillas a" <<p1->nombre<<" !"<<endl;
                    }
                    else{
                        if (conte1==0){
                            cout<<p1->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            p1->salud=p1->salud-daño;    
                        }
                        else{
                            cout<<p1->nombre<<" perdio "<<daño<<" de vida"<<endl;
                            conte1=conte1-daño;
                            if (conte1>=0){
                                cout<<"¡Pero parece que el objeto de defensa de "<<p1->nombre<<" contubo todo el golpe!"<<endl;
                                p1->mochila_b[aux_def]->contenedor=conte2;
                            }
                            else{
                                cout<<"¡Pero parece que el objeto de defensa de "<<p1->nombre<<" contubo parte del golpe!"<<endl;
                                p1->salud=p1->salud+conte1;
                                p1->mochila_b[aux_def]->contenedor=0;
                            }
                        }
                    }
                    cout<<p2->nombre<<" perdio "<<p2->mochila_b[opv]->energia<<" de energia "<<endl;
                    p2->energia-=p2->mochila_b[opv]->energia;
                    def1=0;
                    conte1=0;
                    daño=0;
                }
                else if (p2->mochila_b[opv]->tipo == "Defensa"){
                    conte2=p2->mochila_b[opv]->contenedor;
                    aux_def=opv;
                    def2=p2->mochila_b[opv]->valor;
                    cout<<"El proximo ataque de tu rival hace "<<p2->mochila_b[opv]->valor<<" menos de daño"<<endl;
                    cout<<"Optubiste una covertura de "<<p2->mochila_b[opv]->contenedor<<" de daños"<<endl;
                    cout<<p2->nombre<<" perdio "<<p2->mochila_b[opv]->energia<<" energia"<<endl;
                    p2->energia = p2->energia - p2->mochila_b[opv]->energia;
                    
                }
                else if (p2->mochila_b[opv]->tipo == "Supervivencia"){
                    if (p2->mochila_b[opv]->recuperacion=="Salud"){
                        cout<<p2->nombre<<" ha recuperado "<<p2->mochila_b[opv]->valor<<" de vida "<<endl;
                        cout<<p2->nombre<<" perdio "<<p2->mochila_b[opv]->energia<<" energia "<<endl;
                        p2->salud=p2->salud+p2->mochila_b[opv]->valor;
                        p2->energia=p2->energia-p2->mochila_b[opv]->energia;
                    }
                    else if (p2->mochila_b[opv]->recuperacion=="Energia"){
                        cout<<p2->nombre<<" ha recuperado "<<p2->mochila_b[opv]->valor<<" de energia "<<endl;
                        cout<<p2->nombre<<" perdio "<<p2->mochila_b[opv]->energia<<" energia "<<endl;
                        p2->energia=p2->energia+p2->mochila_b[opv]->valor;
                        p2->energia=p2->energia-p2->mochila_b[opv]->energia;
                    }
                    
                }
                if (efecto2e!=0){
                    p2->energia=p2->energia-efecto2e;
                    cout<<p2->nombre<<" perdio"<< efecto2e<< "de energia por no estar  con proteccion"<<endl;
                    p2->salud=p2->salud-efecto2v;
                    cout<<p2->nombre<<" perdio"<< efecto2e<< "de vida por no estar  con proteccion"<<endl;
                }
                
                cout<<""<<endl;
                cout<<"Resumen del turno:"<<endl;
                cout<<p1->nombre<<endl;
                cout<<"Vida:"<<p1->salud<<endl;
                cout<<"Energia:"<<p1->energia<<endl;
                cout<<""<<endl;
                cout<<p2->nombre<<endl;
                cout<<"Vida:"<<p2->salud<<endl;
                cout<<"Energia:"<<p2->energia<<endl;
                cout<<""<<endl;

                if (p1->energia <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->energia <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->salud<=0){
                    fin=3;
                }
                else if (p1->salud <= 0 and p2->energia<=0){
                    fin=3;
                }
                else if (p1->energia<=0){
                    fin=1;
                }
                else if (p1->salud<=0){
                    fin=1;
                }
                else if (p2->salud<=0){
                    fin=2;
                }
                else if (p2->energia<=0){
                    fin=2;
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
        cout<<"¡Vaya! parece que ambos han caido en batalla "<<endl<<"¡Ningun bando gana!"<<endl;
    }
    else if(fin==2){
        cout<<"El peleador de "<<j2<<" ha caido en batalla, toda su energia ha sido abasorvida por el peleador de "<<j1<<endl;
        cout<<j1<<" gana el encuentro "<<endl;
        if(p2->energia > 0){
            p1->energia+=p2->energia;
        }
        EliminarPerosnajesPorNombre(prs2,p2);
        RecuperarEnergia(p1, razas);
    }
    else if(fin==1){
        cout<<"El peleador de "<<j1<<" ha caido en batalla, toda su energia ha sido abasorvida por el peleador de "<<j2<<endl;
        cout<<j2<<" gana el encuentro "<<endl;
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
}


//__________________LECTRUAS________________
//---------------------------------------------Ambientes-------------------------------------------
void AmbientesArchivo(const char* a, tAmbientePtr &amb) {
    ifstream archivo(a);
    if (archivo.is_open()) {
        string nombre;
        tAmbientePtr actual = amb;
        tAmbientePtr ambi = new tAmbiente;
        int cantidad_ambientes;
        int cont=0; 
        archivo >> cantidad_ambientes;
        while (cont<cantidad_ambientes) {
            archivo>>nombre;
            if (nombre.size()>2){
                ambi->nombre = nombre;
                
                ambi->siguiente = NULL;

               /* while(actual->siguiente!=NULL){
                    actual=actual->siguiente;
                }*/

                if (amb == NULL) {
                    amb = ambi;
                    //actual = ambi;
                } else {
                    actual->siguiente = ambi;
                    //actual = ambi;
                }
                //actual=amb;
                actual = ambi;
                //l+=1;
            }
         cont++;   
        }

        archivo.close();
        cout<<"Los ambientes se han cargado con exito"<<endl;
    } 
    else {
        cout << "Los datos han sido corrompidos en ambientes" << endl;
    }
}

//---------------------------------------------Accesorios---------------------------------------
void AccesoriosArchivo(const char*b, tAccesoriosPtr &acc){
    ifstream archivo(b);
    if (archivo.is_open()) {
        string nombre;
        string tipo;
        string valorstr;
        string recuperacionstr;
        string energiastr;
        string contenedorstr;
        tAccesoriosPtr actual = acc;
        tAccesoriosPtr acce = new tAccesorios;
        int cantidad_acc;
        int cont=0; 
        string aux; 
        getline(archivo, aux);
        cantidad_acc = stoi(aux); 
        while (cont<cantidad_acc) {
            getline(archivo, aux);
            getline(archivo, nombre);
            getline(archivo,tipo);
            getline(archivo, valorstr);
            getline(archivo, recuperacionstr);
            getline(archivo, energiastr);
            getline(archivo, contenedorstr);
            if (nombre.size()>2){
                if(tipo.size()>5){
                    tipo=tipo.erase(0, 5);
                    acce->tipo = tipo;
                }
                if(valorstr.size()>6){
                    valorstr = valorstr.erase(0, 6);
                    int valor = stoi(valorstr);
                    acce->valor = valor;
                }
                if (recuperacionstr.size()>14){
                    recuperacionstr = recuperacionstr.erase(0, 14);
                    acce->recuperacion = recuperacionstr;
                }
                  if(energiastr.size()>8){
                    energiastr = energiastr.erase(0, 8);
                    int energia = stoi(energiastr);
                    acce->energia = energia;
                }
                if(contenedorstr.size()>11){
                    contenedorstr = contenedorstr.erase(0, 11);
                    int contenedor = stoi(contenedorstr);
                    acce->contenedor = contenedor;
            
                }                

                acce->nombre = nombre;
                acce->siguiente = NULL;

               /* while(actual->siguiente!=NULL){
                    actual=actual->siguiente;
                }*/

                if (acc == NULL) {
                    acc = acce;
                    //actual = ambi;
                } else {
                    actual->siguiente = acce;
                    //actual = ambi;
                }
                //actual=amb;
                actual = acce;
                //l+=1;
            }
         cont++;   
        }

        archivo.close();
        cout<<"Los accesorios se han cargado con exito"<<endl;
    } 
    else {
        cout << "Los datos han sido corrompidos en accesorios" << endl;
    }
}

//---------------------------------------------Razas---------------------------------------
void RazasArchivo(const char*c, tRazaPtr &razas, tAmbientePtr &ambientes){
    ifstream archivo(c);
    if (archivo.is_open()){
        string nombre;
        string energiastr;
        string saludstr;
        string planeta;
        tRazaPtr actual = razas;
        tRazaPtr razs = new tRaza;
        int cantidad_razas;
        int cont=0; 
        string aux; 
        getline(archivo, aux);
        cantidad_razas = stoi(aux); 
        while (cont<cantidad_razas) {
            getline(archivo, aux);
            getline(archivo, nombre);
            getline(archivo, energiastr);
            getline(archivo, saludstr);
            getline(archivo, planeta);
            if (nombre.size()>2){
                if(energiastr.size()>8){
                    energiastr=energiastr.erase(0, 8);
                    int energia = stoi(energiastr);
                    razs->energia = energia;
                }
                if(saludstr.size()>6){
                    saludstr = saludstr.erase(0, 6);
                    int salud = stoi(saludstr);
                    razs->salud = salud;
                }
                if (planeta.size()>2){
                    razs->planeta = planeta;
                }      

                razs->nombre = nombre;
                razs->siguiente = NULL;

               /* while(actual->siguiente!=NULL){
                    actual=actual->siguiente;
                }*/

                if (razas == NULL) {
                    razas = razs;
                    //actual = ambi;
                } else {
                    actual->siguiente = razs;
                    //actual = ambi;
                }
                //actual=amb;
                actual = razs;
                //l+=1;
            }
         cont++;   
        }

        archivo.close();
        cout<<"Las razas se han cargado con exito"<<endl;
    } 
    else {
        cout << "Los datos han sido corrompidos en razas" << endl;
    }
}

//_____________________________________________________Main_______________________________________________
int main(){
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
    string nombre;
    string raza;
    int n;
    string nu;
    string o;

    cout << "The Big Red Fox 🦊 presenta:" << endl;
    cout << "     Starz: The gods talk to me     " << endl;
    cout<< " " << endl;
        
    cout<<"Solo por curiosidad, dime un numero del 1 al 10 ;)"<<endl;
    getline(cin,nu);
    istringstream(nu) >> n;
    while(n>10 or n<1){
        cout<<"Fui bastante claro con decir un numero entero del 1 al 10, intenta de nuevo..."<<endl;
        getline(cin,nu);
        istringstream(nu) >> n;
    }
    cout<<""<<endl;

    //AmbientesArchivo("ambientes.inv", ambientes);
    
    //RazasArchivo("especies.inv", razas,ambientes);
    
    //AccesoriosArchivo("accesorios.inv", accseorios);
    

    tAmbientePtr a4= new tAmbiente;
    a4->nombre="Vulcano";
    a4->siguiente=NULL;

    tAmbientePtr a3= new tAmbiente;
    a3->nombre="Atlantes";
    a3->siguiente=a4;

    tAmbientePtr a2= new tAmbiente;
    a2->nombre="Lunar";
    a2->siguiente=a3;

    tAmbientePtr a1= new tAmbiente;
    a1->nombre="Tierra";
    a1->siguiente=a2;

    ambientes=a1;

    tAccesoriosPtr ac23= new tAccesorios;
    ac23->nombre="Bomba de Pulsos Electromagnéticos";
    ac23->tipo="Ataque";
    ac23->valor=40;
    ac23->energia=20;
    ac23->contenedor=0;
    ac23->siguiente=NULL;

    tAccesoriosPtr ac22= new tAccesorios;
    ac22->nombre="Armadura de Energía Cinética";
    ac22->tipo="Defensa";
    ac22->valor=100;
    ac22->energia=110;
    ac22->contenedor=10;
    ac22->siguiente=ac23;

    tAccesoriosPtr ac21= new tAccesorios;
    ac21->nombre="Armadura de Energía Cinética";
    ac21->tipo="Defensa";
    ac21->valor=40;
    ac21->energia=20;
    ac21->contenedor=80;
    ac21->siguiente=ac22;

    tAccesoriosPtr ac20= new tAccesorios;
    ac20->nombre="Botiquín Nanotecnológico";
    ac20->tipo="Supervivencia";
    ac20->valor=100;
    ac20->recuperacion="Salud";
    ac20->energia=30;
    ac20->contenedor=0;
    ac20->siguiente=ac21;

    tAccesoriosPtr ac19= new tAccesorios;
    ac19->nombre="Mina de Singularidad";
    ac19->tipo="Ataque";
    ac19->valor=500;
    ac19->energia=300;
    ac19->contenedor=0;
    ac19->siguiente=ac20;

    tAccesoriosPtr ac18= new tAccesorios;
    ac18->nombre="Mochila Propulsora misilistica";
    ac18->tipo="Ataque";
    ac18->valor=80;
    ac18->energia=20;
    ac18->contenedor=0;
    ac18->siguiente=ac19;

    tAccesoriosPtr ac17= new tAccesorios;
    ac17->nombre="Cuchillo de Energía";
    ac17->tipo="Ataque";
    ac17->valor=5;
    ac17->energia=0;
    ac17->contenedor=0;
    ac17->siguiente=ac18;

    tAccesoriosPtr ac16= new tAccesorios;
    ac16->nombre="Armadura de Nanofibras Regenerativas";
    ac16->tipo="Supervivencia";
    ac16->valor=40;
    ac16->recuperacion="Salud";
    ac16->energia=20;
    ac16->contenedor=0;
    ac16->siguiente=ac17;

    tAccesoriosPtr ac15= new tAccesorios;
    ac15->nombre="Generador de Gravedad Inversa";
    ac15->tipo="Defensa";
    ac15->valor=30;
    ac15->energia=20;
    ac15->contenedor=100;
    ac15->siguiente=ac16;

    tAccesoriosPtr ac14= new tAccesorios;
    ac14->nombre="Pistola Neural";
    ac14->tipo="Ataque";
    ac14->valor=20;
    ac14->energia=2;
    ac14->contenedor=0;
    ac14->siguiente=ac15;

    tAccesoriosPtr ac13= new tAccesorios;
    ac13->nombre="Lanzallamas Criogénico";
    ac13->tipo="Ataque";
    ac13->valor=100;
    ac13->energia=80;
    ac13->contenedor=0;
    ac13->siguiente=ac14;

    tAccesoriosPtr ac12= new tAccesorios;
    ac12->nombre="Dispositivo de Terretransformador";
    ac12->tipo="Acondicionamiento";
    ac12->valor=0;
    ac12->recuperacion="Tierra";
    ac12->energia=0;
    ac12->contenedor=0;
    ac12->siguiente=ac13;

    tAccesoriosPtr ac11= new tAccesorios;
    ac11->nombre="Granada de Antimateria";
    ac11->tipo="Ataque";
    ac11->valor=80;
    ac11->energia=40;
    ac11->contenedor=0;
    ac11->siguiente=ac12;

    tAccesoriosPtr ac10= new tAccesorios;
    ac10->nombre="Traje de Adaptación Lunar";
    ac10->tipo="Acondicionamiento";
    ac10->valor=0;
    ac10->recuperacion="Lunar";
    ac10->energia=0;
    ac10->contenedor=0;
    ac10->siguiente=ac11;

    tAccesoriosPtr ac9= new tAccesorios;
    ac9->nombre="Visor de Espectro Vulcano";
    ac9->tipo="Acondicionamiento";
    ac9->valor=0;
    ac9->recuperacion="Vulcano";
    ac9->energia=0;
    ac9->contenedor=0;
    ac9->siguiente=ac10;

    tAccesoriosPtr ac8= new tAccesorios;
    ac8->nombre="Generador de Campos de Distorsión";
    ac8->tipo="Defensa";
    ac8->valor=40;
    ac8->energia=20;
    ac8->contenedor=100;
    ac8->siguiente=ac9;

    tAccesoriosPtr ac7= new tAccesorios;
    ac7->nombre="Escudo de Fase Pleunaral";
    ac7->tipo="Defensa";
    ac7->valor=30;
    ac7->energia=40;
    ac7->contenedor=200;
    ac7->siguiente=ac8;

    tAccesoriosPtr ac6= new tAccesorios;
    ac6->nombre="Blaster de Plasma";
    ac6->tipo="Ataque";
    ac6->valor=40;
    ac6->energia=20;
    ac6->contenedor=0;
    ac6->siguiente=ac7;

    tAccesoriosPtr ac5= new tAccesorios;
    ac5->nombre="Nanobots de Reparación";
    ac5->tipo="Supervivencia";
    ac5->valor=200;
    ac5->recuperacion="Salud";
    ac5->energia=60;
    ac5->contenedor=0;
    ac5->siguiente=ac6;

    tAccesoriosPtr ac4= new tAccesorios;
    ac4->nombre="Garras de Ácido";
    ac4->tipo="Ataque";
    ac4->valor=15;
    ac4->energia=5;
    ac4->contenedor=0;
    ac4->siguiente=ac5;

    tAccesoriosPtr ac3= new tAccesorios;
    ac3->nombre="Botas Gravitatorias";
    ac3->tipo="Acondicionamiento";
    ac3->valor=0;
    ac3->recuperacion="Atlante";
    ac3->energia=0;
    ac3->contenedor=0;
    ac3->siguiente=ac4;

    tAccesoriosPtr ac2= new tAccesorios;
    ac2->nombre="Generador de Campo de Fuerza";
    ac2->tipo="Defensa";
    ac2->valor=70;
    ac2->energia=90;
    ac2->contenedor=30;
    ac2->siguiente=ac3;

    tAccesoriosPtr ac1= new tAccesorios;
    ac1->nombre="Armadura Bioadaptativa";
    ac1->tipo="Supervivencia";
    ac1->valor=300;
    ac1->recuperacion="Energia";
    ac1->energia=50;
    ac1->contenedor=0;
    ac1->siguiente=ac2;

    accseorios=ac1;

    tRazaPtr r11= new tRaza;
    r11->nombre="Humanos";
    r11->energia=100;
    r11->salud=100;
    r11->planeta="Tierra";
    r11->siguiente=NULL;

    tRazaPtr r10= new tRaza;
    r10->nombre="Monstruo de Flatwoods";
    r10->energia=800;
    r10->salud=40;
    r10->planeta="Atlantes";
    r10->siguiente=r11;

    tRazaPtr r9= new tRaza;
    r9->nombre="Marcianos";
    r9->energia=120;
    r9->salud=60;
    r9->planeta="Vulcano";
    r9->siguiente=r10;

    tRazaPtr r8= new tRaza;
    r8->nombre="Ashtar";
    r8->energia=400;
    r8->salud=80;
    r8->planeta="Atlantes";
    r8->siguiente=r9;

    tRazaPtr r6= new tRaza;
    r6->nombre="Ummitas";
    r6->energia=150;
    r6->salud=100;
    r6->planeta="Lunar";
    r6->siguiente=r8;
    
    tRazaPtr r5= new tRaza;
    r5->nombre="Pleyadianos";
    r5->energia=200;
    r5->salud=200;
    r5->planeta="Vulcano";
    r5->siguiente=r6;
    
    tRazaPtr r4= new tRaza;
    r4->nombre="Zeta Reticulans";
    r4->energia=150;
    r4->salud=200;
    r4->planeta="Vulcano";
    r4->siguiente=r5;

    tRazaPtr r3= new tRaza;
    r3->nombre="Reptiliano";
    r3->energia=150;
    r3->salud=200;
    r3->planeta="Atlantes";
    r3->siguiente=r4;

    tRazaPtr r2= new tRaza;
    r2->nombre="Andromedanos";
    r2->energia=70;
    r2->salud=300;
    r2->planeta="Lunar";
    r2->siguiente=r3;

    tRazaPtr r1= new tRaza;
    r1->nombre="Arcturianos";
    r1->energia=600;
    r1->salud=50;
    r1->planeta="Tierra";
    r1->siguiente=r2;

    razas=r1;
    
    
    cout<<"Hace cientos de años no pensabamos que todo acabraia asi..."<<endl;
    cout<<"La humanidad llego a un punto de quiebre, empezo una guerra contra otras razas y asi nos encontramos ahora"<<endl;
    cout<<""<<endl;

    //system("pause");

    cout<<"Ingrese el nombre del J1:"<<endl;
    getline(cin,j1);
    cout<<""<<endl;

    cout<<"Ingrese el nombre del J2:"<<endl;
    getline(cin,j2);
    cout<<""<<endl;

    //system("pause");

    cout<<""<<endl;
    cout<<"Cuando la humanidad estaba a punto de llegar a su punto mas bajo, aparecio un hombre capaz de dar esperanza:"<<endl;
    cout<<j1<<endl;
    cout<<""<<endl;

    cout<<"Pero, ¿podra esta esperanza ganarle al temible "<<j2<<" ?"<<endl;
    cout<<""<<endl;

    //system("pause");

    cout<<""<<endl;
    cout<<j1<<" confiamos en usted para llevar la batalla que nos llevara a la victoria"<<endl;
    cout<<"Debe seleccionar con cuidado que soldados llevara a la disputa"<<endl;
    cout<<""<<endl;
    PersonajesUsuarios(j1p, razas, j1);
    cout<<""<<endl;
    cout<<j1<<" No se olvide del equipamento de los soldados!"<<endl;
    cout<<""<<endl;
    AccesoriosUsuarios(j1p, accseorios);
    cout<<""<<endl;

    //system("pause");

    cout<<""<<endl;
    cout<<j2<<" todas las tropas andromedianas se encuentran bajo su mandato"<<endl;
    cout<<"Solo ingrese sus nombres y sus razas para que podamos mandarselos"<<endl;
    cout<<""<<endl;
    PersonajesUsuarios(j2p, razas, j2);
    cout<<""<<endl;
    cout<<j2<<" No se olvide del equipamento de los soldados!"<<endl;
    cout<<""<<endl;
    AccesoriosUsuarios(j2p, accseorios);
    cout<<""<<endl;

    cout<<""<<endl;
    cout<<"[3 DIAS ANTES DEL DESASTRE]"<<endl;
    cout<<j1<<" y "<<j2<<" van a dar un discurso para motivar a sus tropas!"<<endl;
    Lealtad1v1(j1p,j2p,j1,j2);
    cout<<""<<endl;
    
    cout<<""<<endl;
    cout<<"[EL DIA DEL DESASTRE]"<<endl;
    lugar=LugarPelea(ambientes,n);
    cout<<"¡"<<j1<<"!"<<" ¡"<<j1<<"!"<<" nos informan que "<<j2<<" esta invadiendo "<<lugar->nombre<<endl;
    cout<<"Es nuestro momento de acabar con el"<<endl;
    cout<<""<<endl;
    
    while (j1p!=NULL and j2p!=NULL){
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
            
    
    
    DestruirAccesorios(accseorios);
    DestruirPersonajes(personajes);
    DestruirPersonajes(j1p);
    DestruirPersonajes(j2p);
    DestruirRazas(razas);
    DestruirAmbientes(ambientes);
    DestruirAmbientes(lugar);

    return 0;
}