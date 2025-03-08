#include <iostream>
#include <string>

using namespace std;

// Prototipos funciones
int menuPrincipal();
void menuAdmin();
bool validarLogin(int tipoUsuario);

// #TODO : Crear funciones:
int mostrarMenuAdminCuentasUsuario();
void agregarUsuarios();
void eliminarUsuarios();

// Funciones definidad antes de Main()
void limpiarConsola(){
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // macOS/Linux
    #endif
};

// definimos el Struct para almacenar los usuarios
struct Usuario{
    string usuario;
    string pass;
    int tipo;
    int status;
};

// variables globales
Usuario usuarios[100] = {{"admin", "123", 1, 1}, {"vend1", "123", 2, 1}, {"vend2", "123", 2, 1}};
int totalUsuarios = 3;

int main(){
    bool isExcecute = true;
    int optionMenu;
    cout << "Bienvenido, pulsa cualquier tecla para comenzar...";
    while (isExcecute){
        optionMenu = menuPrincipal();
        switch (optionMenu){
            case 1:
                menuAdmin();
                limpiarConsola();
                break;
            case 2:
                // #TODO: Validacion login
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
        cout << "\t1. Administrador\n\t2. Ventas\n\t3. Salir\n\n";
        cout << "\tOpcion: "; cin >> option;
        // si el usuario ingresa un dato no numerico, se limpia el cache de cin.
        if (!cin.good()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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
        cout << "\n\n\tMENU ADMINISTRADOR\n\n";
        cout << "\t1. Altas\n\t2. Bajas\n\t3. Consultas\n\t4. Modificaciones\n\t5. Mostrar Inventario\n\t6. Administracion de Cuentas de Usuario\n\t7.Corte de caja general\n\t8.Regresar al menu anterior.\n\n";
        cout << "\tOpcion: ";
        cin >> option;
    }
}

bool validarLogin(int tipoUsuario){
    bool isValid = false;
    string usuario, pass;
    do{
        cout << "\nUsuario: ";
        cin >> usuario;
        cout << "\nPassword: ";
        cin >> pass;

        for (int i = 0; i < totalUsuarios; i++){
            if (usuarios[i].usuario == usuario && usuarios[i].pass == pass && usuarios[i].tipo == tipoUsuario){
                isValid = true;
                break;
            }
        }
        if (isValid == false) cout << "\n\n*** Usuario o contraseña incorrectos. Intenta de nuevo. ***" << endl;
    } while (!isValid);
    return isValid;
}