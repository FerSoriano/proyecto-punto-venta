#include <iostream>
#include <string>
#include <iomanip> // uso de setw()
#include <algorithm> // uso de sort()

using namespace std;
// definimos el Struct para almacenar los usuarios y productos
struct Usuario{
    string usuario;
    string pass;
    int tipo;
    int status;
};

struct Producto{
    int id;
    string producto;
    float pc;
    float pv;
    int existencias;
    int nivelReorden;
    int status;
};

// Prototipos funciones
int menuPrincipal();
void menuAdmin();
bool validarLogin(int tipoUsuario);
void validarInput();
void mostrarInventario();
void mostrarProductos(int tipoOrden);
void altaProducto();
Producto buscarProducto(string nombreProducto);
Usuario buscarUsuario(string nombreUsuario);
string convertirMinus(string str);
void consultarProducto();
void modificarProducto();
void bajaProducto();
void mostrarMenuAdminCuentasUsuario();
void altaUsuario();
void bajaUsuario();
void modificarUsuario();
void consultarUsuario();
void mostrarCuentasUsuarios();

// Funciones definidad antes de Main()
void limpiarConsola(){
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // macOS/Linux
    #endif
};

// variables globales
int totalUsuarios = 3;
Usuario usuarios[100] = {
    {"admin", "123", 1, 1}, 
    {"vend1", "123", 2, 1}, 
    {"vend2", "123", 2, 1}
};

int totalProductos = 5;
Producto productos[100] = {
    {1,"Agua",13.39,18.55,12,4,1},
    {2,"Leche",12.35,15.5,16,5,1},
    {3,"Huevos",22.4,30.39,20,7,1},
    {4,"Pan",5.5,7.95,18,6,1},
    {5,"Refresco",10.99,14.75,30,8,1}
};

int main(){
    bool isExcecute = true;
    int optionMenu;
    cout << "Bienvenido, pulsa cualquier tecla para comenzar...";
    while (isExcecute){
        optionMenu = menuPrincipal();
        switch (optionMenu){
            case 1:
                menuAdmin();
                break;
            case 2:
                // #TODO: Validacion login ventas
                // #TODO: Crear funcion Ventas()
                limpiarConsola();
                cout << "Mostrando menu Ventas...";
                break;
            case 3:
                cout << "\n-------------------------------------------------\n     SALIENDO DEL SISTEMA. FIN DEL PROGRAMA.\n-------------------------------------------------\n\n";
                isExcecute = false;
            default:
                break;
        }
    }
    return 0;
}

int menuPrincipal(){
    int option;
    while (true){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n\n\tMENU PRINCIPAL\n\n";
        cout << "1. Administrador\n2. Ventas\n3. Salir\n\n";
        cout << "\tOpcion: "; cin >> option;
        validarInput();
        if (option >= 1 && option <= 3) break;
        else {
            limpiarConsola();
            cout << "\n*** Opcion invalida. Intenta de nuevo. ***";
        }
    }
    return option;
}

// #TODO: Terminar de implementar funcion. Agregar Switch y funciones para cada opcion.
void menuAdmin(){
    if (validarLogin(1)){
        limpiarConsola();
        int option;
        bool ejecutarMenu = true;
        
        while(ejecutarMenu){
            cout << "\n\n\tMENU ADMINISTRADOR\n\n";
            cout << "1. Altas\n2. Bajas\n3. Consultas\n4. Modificaciones\n5. Mostrar Inventario\n6. Administracion de Cuentas de Usuario\n7. Corte de caja general\n8. Regresar al menu anterior.\n\n";
            cout << "\tOpcion: ";
            cin >> option;
            validarInput();
            switch (option){
                case 1:
                    limpiarConsola();
                    altaProducto();
                    break;
                case 2:
                    limpiarConsola();
                    bajaProducto();
                    break;
                case 3:
                    limpiarConsola();
                    consultarProducto();
                    break;
                case 4:
                    limpiarConsola();
                    modificarProducto();
                    break;
                case 5:
                    limpiarConsola();
                    mostrarInventario();
                    break;
                case 6:
                    limpiarConsola();
                    mostrarMenuAdminCuentasUsuario();
                    break;
                case 7:
                    limpiarConsola();
                    cout << "Insertar codigo: Corte de Caja General"<<endl;
                    break;
                case 8:
                    limpiarConsola();
                    ejecutarMenu = false;
                    break;
                default:
                    limpiarConsola();
                    cout << "\n*** Opcion invalida. Intenta de nuevo. ***";
                    break;
            }
        }
    }
}

bool validarLogin(int tipoUsuario){
    bool isValid = false;
    string usuario, pass;
    do{
        cout << "\nUsuario: ";
        cin >> usuario;
        if(usuario == "*"){limpiarConsola(); break;}
        cout << "\nPassword: ";
        cin >> pass;

        for (int i = 0; i < totalUsuarios; i++){
            if (usuarios[i].usuario == usuario && usuarios[i].pass == pass && usuarios[i].tipo == tipoUsuario && usuarios[i].status == 1){
                isValid = true;
                break;
            }
        }
        if (isValid == false) cout << "\n\n*** Usuario o contraseña incorrectos. Intenta de nuevo. ***" << endl;
    } while (!isValid);
    return isValid;
}

void validarInput(){
    // si el usuario ingresa un dato no numerico, se limpia el cache de cin.
    if (!cin.good()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void mostrarInventario(){
    int option;
    bool ejecutarMenu = true;
    
    while(ejecutarMenu){
        cout << "\n\n\tMOSTRAR INVENTARIO\n\nOrdenado por:\n";
        cout << "1. Por Id\n2. Por producto\n3. Regresar al menú anterior.\n\n";
        cout << "\tOpcion: "; cin >> option;
        validarInput();
        switch (option)
        {
        case 1:
            limpiarConsola();
            mostrarProductos(1);
            break;
        case 2:
            limpiarConsola();
            mostrarProductos(2);
            break;
        case 3:
            limpiarConsola();
            ejecutarMenu = false;
            break;
        default:
            limpiarConsola();
            cout << "\n*** Opcion invalida. Intenta de nuevo. ***";
            break;
        }
    }
}

bool compararPorId(const Producto &a, const Producto &b) {return a.id < b.id;}
bool compararPorNombre(const Producto &a, const Producto &b) {
    // se convierten a minusculas para poderlos ordenar correctamente.
    string producto_a = convertirMinus(a.producto);
    string producto_b = convertirMinus(b.producto);
    return producto_a < producto_b;
}

void mostrarProductos(int tipoOrden){
    char resurtir;
    if 
        (tipoOrden == 1) sort(productos,productos + totalProductos,compararPorId); // se ordena por ID
    else 
        sort(productos,productos + totalProductos,compararPorNombre); // se ordena por nombre producto

    cout << "---------------------------------------------------------------------------\n\t\t\t\tINVENTARIO\n---------------------------------------------------------------------------\n";
        cout << left << setw(5) << "Id"
                    << setw(15) << "Producto"
                    << setw(10) << "PC"
                    << setw(10) << "PV"
                    << setw(15) << "Existencias"
                    << setw(10) << "NR"
                    << "Resurtir" << endl;

        for (int i = 0; i < totalProductos; i++){
            if(productos[i].status == 1){
                resurtir = (productos[i].existencias <= productos[i].nivelReorden) ? '*' : ' ';
                cout << left << setw(5) << productos[i].id
                            << setw(15) << productos[i].producto
                            << setw(10) << productos[i].pc
                            << setw(10) << productos[i].pv
                            << setw(15) << productos[i].existencias
                            << setw(10) << productos[i].nivelReorden
                            << resurtir << endl;
            }
        }
}

void altaProducto(){
    Producto producto;
    string nombreProducto;
    float pc, pv;
    int existencia, nivelReorden;

    cout << "\n\n\tALTA DE PRODUCTO\n\n";
    while(true){
        cout << "Producto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}

        producto = buscarProducto(nombreProducto);
        if(producto.status == 1){cout << "\n\n*** El producto \"" << nombreProducto << "\"  ya existe. Intenta de nuevo. ***\n\n"; continue;} // validacion estatus.

        if(producto.id == 0){    
            cout << "Precio compra: "; cin >> pc; validarInput();
            cout << "Precio venta: "; cin >> pv; validarInput();
            if(pc>pv) {cout << "\n\n*** El PC no puede ser mayor al PV. Intenta de nuevo. ***\n\n"; continue;}

            cout << "Existencia: "; cin >> existencia; validarInput();
            cout << "Nivel de Reorden: "; cin >> nivelReorden; validarInput();
            if(existencia<nivelReorden){cout << "\n\n*** La Existencia no puede ser menor que el Nivel de Reorden. Intenta de nuevo ***\n\n"; continue;}

            // se agrega el producto.
            productos[totalProductos].id = totalProductos + 1;
            productos[totalProductos].producto = nombreProducto;
            productos[totalProductos].pc = pc;
            productos[totalProductos].pv = pv;
            productos[totalProductos].existencias = existencia;
            productos[totalProductos].nivelReorden = nivelReorden;
            productos[totalProductos].status = 1;
            totalProductos++; // se incrementa en 1 la cantidad de productos.
            cout << "\n\nEl producto \"" << nombreProducto << "\" se agrego correctamente.\n\n";
        } else { 
            sort(productos,productos + totalProductos,compararPorId); // ordenamos la lista para poderla modificar.
            productos[producto.id - 1].status = 1;
            cout << "El producto " << producto.producto << " se dio de alta." << endl;
        }
    }
}

Producto buscarProducto(string nombreProducto){
    Producto producto = {0, "", 0.0, 0.0, 0, 0, 0};
    for(int i = 0; i < totalProductos; i++){
        if(convertirMinus(productos[i].producto) == convertirMinus(nombreProducto)) { producto = productos[i]; break; }
    }
    return producto;
}

Usuario buscarUsuario(string nombreUsuario){
    Usuario usuario = {"", "", 0, 0};
    for(int i = 0; i < totalUsuarios; i++){
        if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario)) { usuario = usuarios[i]; break; }
    }
    return usuario;
}

string convertirMinus(string str){
    for (char &c : str) c = tolower(c);
    return str;
}

void consultarProducto(){
    Producto producto;
    string nombreProducto;
    while (true){
        cout << "\n\n\tCONSULTA\n\nProducto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}
        producto = buscarProducto(nombreProducto);
        if(producto.status == 1){
            cout << "\n" << left << setw(5) << "Id"
                    << setw(15) << "Producto"
                    << setw(10) << "PC"
                    << setw(10) << "PV"
                    << setw(15) << "Existencias"
                    << setw(20) << "Nivel de Reorden"
                    << "St" << endl;
            cout << left << setw(5) << producto.id
                    << setw(15) << producto.producto
                    << setw(10) << producto.pc
                    << setw(10) << producto.pv
                    << setw(15) << producto.existencias
                    << setw(20) << producto.nivelReorden
                    << producto.status << endl;
            continue;
        }
        cout << "\n\n*** No se encontro el producto \"" << nombreProducto << "\" ***\n\n";
    }
}

void modificarProducto(){
    Producto producto;
    string nombreProducto;
    float pc, pv;
    int existencia, nivelReorden, opcion;

    sort(productos,productos + totalProductos,compararPorId); // ordenamos la lista para poderla modificar.
    
    while (true){
        bool mostrarOpciones = true;
        cout << "\n\n\tMODIFICACIONES\n\nProducto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}
        producto = buscarProducto(nombreProducto);
        if(producto.status == 1){
            while (mostrarOpciones){
                    cout << "\n\n\tMODIFICACIONES\n\nProducto: "<< producto.producto << endl;
                    cout << "\n1. Precio de compra\n2. Precio de venta\n3. Existencias\n4. Nidel de reorden\n5. Regresar al menu anterior\n\n";
                    cout << "\tOpcion: "; cin >> opcion; validarInput();
                    switch(opcion){
                        case 1:
                            cout << "\nPC actual: "<< producto.pc;
                            cout << "\nPC nuevo: "; cin >> pc; validarInput();
                            productos[producto.id - 1].pc = pc; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nPrecio de compra actualizado\n\n";
                            break;
                        case 2:
                            cout << "\nPV actual: "<< producto.pv;
                            cout << "\nPV nuevo: "; cin >> pv; validarInput();
                            productos[producto.id - 1].pv = pv; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nPrecio de venta actualizado\n\n";
                            break;
                        case 3:
                            cout << "\nExistencias actuales: "<< producto.existencias;
                            cout << "\nExistencias nuevas: "; cin >> existencia; validarInput();
                            productos[producto.id - 1].existencias = existencia; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nExistencia actualizada\n\n";
                            break;
                        case 4:
                            cout << "\nNivel de reorden actual: "<< producto.nivelReorden;
                            cout << "\nNivel de reorden nuevo: "; cin >> nivelReorden; validarInput();
                            productos[producto.id - 1].nivelReorden = nivelReorden; // actualizamos el producto original con el ID.
                            producto = buscarProducto(nombreProducto); // actualizamos nuestro producto temporal.
                            cout << "\n\nNivel de reorden actualizado\n\n";
                            break;
                        case 5:
                            limpiarConsola();
                            mostrarOpciones = false;
                            break;
                        default:
                            cout << "*** Opcion incorrecta. Intenta de nuevo. ***";
                            break;
                    }
                }
        } else { limpiarConsola(); cout << "\n\n*** No se encontro el producto \"" << nombreProducto << "\" ***\n\n"; }
    }
}

void bajaProducto(){
    Producto producto;
    string nombreProducto;

    sort(productos,productos + totalProductos,compararPorId); // ordenamos la lista para poderla modificar.

    while(true){
        cout << "\n\n\tBAJA DE PRODUCTO\n\n";
        cout << "Producto: "; cin >> nombreProducto;
        if (nombreProducto == "*"){limpiarConsola(); break;}

        producto = buscarProducto(nombreProducto);
        if(producto.status == 0){cout << "\n\n***Prodcuto \"" << nombreProducto << "\" no encontrado. Intenta de nuevo. ***\n\n"; continue;}

        productos[producto.id - 1].status = 0;
        cout << "El producto \"" << producto.producto << "\" se dio de baja\n";
    }
}

void mostrarMenuAdminCuentasUsuario(){
    int option;
    bool ejecutarMenu = true;
    
    while(ejecutarMenu){
        cout << "\n\n\tMENU ADMINISTRACION DE CUENTAS DE USUARIOS\n\n";
        cout << "1. Altas\n2. Bajas\n3. Consultas\n4. Modificaciones\n5. Mostrar cuentas de usuarios\n6. Regresar al menu anterior.\n\n";
        cout << "\tOpcion: ";
        cin >> option;
        validarInput();
        switch (option){
            case 1:
                limpiarConsola();
                altaUsuario();
                break;
            case 2:
                limpiarConsola();
                bajaUsuario();
                break;
            case 3:
                limpiarConsola();
                consultarUsuario();
                break;
            case 4:
                limpiarConsola();
                modificarUsuario();
                break;
            case 5:
                limpiarConsola();
                mostrarCuentasUsuarios();
                break;
            case 6:
                limpiarConsola();
                ejecutarMenu = false;
                break;
            default:
                limpiarConsola();
                cout << "\n*** Opcion invalida. Intenta de nuevo. ***";
                break;
        }
    }
}

void altaUsuario(){
    Usuario usuario;
    string nombreUsuario;
    string pass;
    int tipo;

    cout << "\n\n\tALTA USUARIO\n\n";
    while(true){
        cout << "Usuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}

        usuario = buscarUsuario(nombreUsuario);
        if(usuario.status == 1){cout << "\n\n*** El usuario \"" << nombreUsuario << "\"  ya existe. Intenta de nuevo. ***\n\n"; continue;} // validacion estatus.

        cout << "Contraseña: "; cin >> pass;
        cout << "Tipo (1 admin / 2 vendedor): "; cin >> tipo; validarInput();

        // se agrega el producto.
        usuarios[totalUsuarios].usuario = nombreUsuario;
        usuarios[totalUsuarios].pass = pass;
        usuarios[totalUsuarios].tipo = tipo;
        usuarios[totalUsuarios].status = 1;
        totalUsuarios++; // se incrementa en 1 la cantidad de usuarios.

        cout << "\n\nEl Usuario \"" << nombreUsuario << "\" se agrego correctamente.\n\n";
    }
}

void bajaUsuario(){
    string nombreUsuario;
    
    while(true){
        bool usuarioEncontrado = false;
        cout << "\n\n\tBAJA USUARIO\n\n";
        cout << "Usuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}

        for(int i = 0; i<totalUsuarios; i++){
            if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario) && usuarios[i].status == 1) {
                usuarios[i].status = 0; 
                cout << "El usuario \"" << usuarios[i].usuario << "\" se dio de baja\n";
                usuarioEncontrado = true;
                break; 
            }
        }

        if(!usuarioEncontrado){cout << "\n\n***Usuario \"" << nombreUsuario << "\" no encontrado. Intenta de nuevo. ***\n\n";}
    }
}

void modificarUsuario(){
    string nombreUsuario, pass;
    int opcion, tipo;

    while (true){
        bool usuarioEncontrado = false;
        bool mostrarOpciones = true;
        cout << "\n\n\tMODIFICACIONES\n\nUsuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}
        for(int i = 0; i<totalUsuarios; i++){
            if(convertirMinus(usuarios[i].usuario) == convertirMinus(nombreUsuario) && usuarios[i].status == 1) {
                limpiarConsola();
                while (mostrarOpciones){
                    cout << "\n\n\tMODIFICACIONES\n\nUsuario: "<< nombreUsuario << endl;
                    cout << "\n1. Contraseña\n2. Tipo\n3. Regresar al menu anterior\n\n";
                    cout << "\tOpcion: "; cin >> opcion; validarInput();
                    switch(opcion){
                        case 1:
                            cout << "\nContraseña actual: "<< usuarios[i].pass;
                            cout << "\nContraseña nueva: "; cin >> pass;
                            usuarios[i].pass = pass; // actualizamos el password
                            cout << "\n\nContraseña actualizada\n\n";
                            break;
                        case 2:
                            cout << "\nTipo actual: "<< usuarios[i].tipo;
                            cout << "\nTipo nuevo: "; cin >> tipo; validarInput();
                            usuarios[i].tipo = tipo; // actualizamos el tipo
                            cout << "\n\nTipo actualizado\n\n";
                            break;
                        case 3:
                            limpiarConsola();
                            mostrarOpciones = false;
                            break;
                        default:
                            cout << "*** Opcion incorrecta. Intenta de nuevo. ***";
                            break;
                    }
                }
                usuarioEncontrado = true;
            }
        }
        if(!usuarioEncontrado){cout << "\n\n***Usuario \"" << nombreUsuario << "\" no encontrado. Intenta de nuevo. ***\n\n";}
    }
}

void consultarUsuario(){
    Usuario usuario;
    string nombreUsuario;
    while (true){
        cout << "\n\n\tCONSULTA\n\nUsuario: "; cin >> nombreUsuario;
        if (nombreUsuario == "*"){limpiarConsola(); break;}
        usuario = buscarUsuario(nombreUsuario);
        if(usuario.status == 1){
            cout << "\n" << left << setw(15) << "Usuario"
                    << setw(10) << "Pass"
                    << setw(10) << "Tipo"
                    << "St" << endl;
            cout << left << setw(15) << usuario.usuario
                    << setw(10) << usuario.pass
                    << setw(10) << usuario.tipo
                    << usuario.status << endl;
            continue;
        }
        cout << "\n\n*** No se encontro el usuario \"" << nombreUsuario << "\" ***\n\n";
    }
}

void mostrarCuentasUsuarios(){
    cout << "---------------------------------------------------------------------------\n\t\t\tMOSTRAR CUENTAS DE USUARIOS\n---------------------------------------------------------------------------\n";
    cout << "\n" << left << setw(15) << "Usuario"
                    << setw(10) << "Pass"
                    << setw(10) << "Tipo"
                    << "St" << endl;
    for(int i = 0; i < totalUsuarios; i++){
        if(usuarios[i].status == 1){
            cout << left << setw(15) << usuarios[i].usuario
                    << setw(10) << usuarios[i].pass
                    << setw(10) << usuarios[i].tipo
                    << usuarios[i].status << endl;
        }
    }
    cout << "\n\n";
}