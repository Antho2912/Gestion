#include <iostream>
#include <string>
using namespace std;

// ----------------------
// ESTRUCTURAS BÁSICAS
// ----------------------

struct Proceso {
    int id;
    string nombre;
    int prioridad;
};

// variables globales
Proceso procesos[100];
int totalProcesos = 0;

// Para la cola de CPU
int cola[100];
int inicioCola = 0, finCola = 0;

// Para la pila de memoria
int pila[100];
int tope = 0;

// ----------------------
// FUNCIONES DEL GESTOR DE PROCESOS
// ----------------------

// Inserta un nuevo proceso en la lista principal
void insertarProceso() {
    if (totalProcesos < 100) {
        cout << "\nID: ";
        cin >> procesos[totalProcesos].id;
        cout << "Nombre: ";
        cin >> procesos[totalProcesos].nombre;
        cout << "Prioridad (Orden): ";
        cin >> procesos[totalProcesos].prioridad;
        totalProcesos++;
        cout << "Proceso agregado.\n";
    } else {
        cout << "Lista llena.\n";
    }
}

// Elimina un proceso de la lista por su ID
void eliminarProceso() {
    int id;
    cout << "Ingrese ID a eliminar: ";
    cin >> id;
    bool encontrado = false;

    for (int i = 0; i < totalProcesos; i++) {
        if (procesos[i].id == id) {
            for (int j = i; j < totalProcesos - 1; j++) {
                procesos[j] = procesos[j + 1];
            }
            totalProcesos--;
            encontrado = true;
            cout << "Proceso eliminado.\n";
            break;
        }
    }

    if (!encontrado)
        cout << "No se encontro el proceso.\n";
}

// Muestra todos los procesos registrados
void mostrarProcesos() {
    if (totalProcesos == 0) {
        cout << "No hay procesos.\n";
        return;
    }
    cout << "\n--- LISTA DE PROCESOS ---\n";
    for (int i = 0; i < totalProcesos; i++) {
        cout << "ID: " << procesos[i].id
             << " | Nombre: " << procesos[i].nombre
             << " | Prioridad (Orden): " << procesos[i].prioridad << endl;
    }
}

// Modifica la prioridad de un proceso según su ID
void modificarPrioridad() {
    int id, nueva;
    cout << "ID del proceso: ";
    cin >> id;
    cout << "Nueva prioridad: ";
    cin >> nueva;

    for (int i = 0; i < totalProcesos; i++) {
        if (procesos[i].id == id) {
            procesos[i].prioridad = nueva;
            cout << "Prioridad modificada.\n";
            return;
        }
    }
    cout << "Proceso no encontrado.\n";
}

// ----------------------
// FUNCIONES DEL PLANIFICADOR CPU (Cola FIFO)   ---->First In, First Out/Primero en entrar, primero en salir
// ----------------------

// Agrega un proceso al final de la cola (FIFO)
void encolarProceso() {
    if (finCola < 100) {
        int id;
        cout << "ID del proceso a encolar: ";
        cin >> id;
        cola[finCola] = id;
        finCola++;
        cout << "Proceso agregado a la cola.\n";
    } else {
        cout << "Cola llena.\n";
    }
}

// Ejecuta (elimina) el primer proceso de la cola
void ejecutarProceso() {
    if (inicioCola == finCola) {
        cout << "No hay procesos en cola.\n";
        return;
    }
    int id = cola[inicioCola];
    inicioCola++;
    cout << "Ejecutando proceso con ID " << id << endl;
}

// Muestra todos los procesos en la cola de CPU
void mostrarCola() {
    if (inicioCola == finCola) {
        cout << "Cola vacia.\n";
        return;
    }
    cout << "\n--- COLA DE CPU ---\n";
    for (int i = inicioCola; i < finCola; i++) {
        cout << "ID: " << cola[i] << endl;
    }
}

// ----------------------
// FUNCIONES DEL GESTOR DE MEMORIA (Pila LIFO) -->LIFO== Last In, First Out/Ultimo en entrar, primero en salir
// ----------------------

// Asigna memoria a un proceso (se apila)
void asignarMemoria() {
    if (tope < 100) {
        int id;
        cout << "ID del proceso: ";
        cin >> id;
        pila[tope] = id;
        tope++;
        cout << "Memoria asignada.\n";
    } else {
        cout << "Memoria llena.\n";
    }
}

// Libera memoria del último proceso agregado (desapilar)
void liberarMemoria() {
    if (tope > 0) {
        tope--;
        cout << "Memoria liberada del proceso con ID " << pila[tope] << endl;
    } else {
        cout << "No hay memoria asignada.\n";
    }
}

// Muestra el estado actual de la pila de memoria
void mostrarMemoria() {
    if (tope == 0) {
        cout << "Memoria vacia.\n";
        return;
    }
    cout << "\n--- ESTADO DE MEMORIA ---\n";
    for (int i = tope - 1; i >= 0; i--) {
        cout << "Memoria asignada al proceso ID: " << pila[i] << endl;
    }
}

// ----------------------
// MENÚ PRINCIPAL DEL SISTEMA
// ----------------------

// Controla las tres funcionalidades del sistema
int main() {
    int opcion;

    do {
        cout << "\n===== SISTEMA DE GESTION DE PROCESOS =====\n";
        cout << "1. Gestionar Procesos\n";
        cout << "2. Planificar CPU\n";
        cout << "3. Gestionar Memoria\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int op2;
            do {
                cout << "\n--- GESTION DE PROCESOS ---\n";
                cout << "1. Insertar Proceso\n";
                cout << "2. Eliminar Proceso\n";
                cout << "3. Mostrar Procesos\n";
                cout << "4. Modificar Prioridad\n";
                cout << "0. Volver\n";
                cout << "Opcion: ";
                cin >> op2;

                if (op2 == 1) insertarProceso();
                else if (op2 == 2) eliminarProceso();
                else if (op2 == 3) mostrarProcesos();
                else if (op2 == 4) modificarPrioridad();
            } while (op2 != 0);
        }

        else if (opcion == 2) {
            int op3;
            do {
                cout << "\n--- PLANIFICADOR CPU ---\n";
                cout << "1. Encolar Proceso\n";
                cout << "2. Ejecutar Proceso\n";
                cout << "3. Mostrar Cola\n";
                cout << "0. Volver\n";
                cout << "Opcion: ";
                cin >> op3;

                if (op3 == 1) encolarProceso();
                else if (op3 == 2) ejecutarProceso();
                else if (op3 == 3) mostrarCola();
            } while (op3 != 0);
        }

        else if (opcion == 3) {
            int op4;
            do {
                cout << "\n--- GESTOR DE MEMORIA ---\n";
                cout << "1. Asignar Memoria\n";
                cout << "2. Liberar Memoria\n";
                cout << "3. Mostrar Memoria\n";
                cout << "0. Volver\n";
                cout << "Opcion: ";
                cin >> op4;

                if (op4 == 1) asignarMemoria();
                else if (op4 == 2) liberarMemoria();
                else if (op4 == 3) mostrarMemoria();
            } while (op4 != 0);
        }

    } while (opcion != 0);

    cout << "Saliendo del sistema...\n";
    return 0;
}
