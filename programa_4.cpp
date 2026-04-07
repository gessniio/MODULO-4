
#include <iostream>   // cout, cin
#include <fstream>    // ofstream, ifstream (archivos)
#include <cstring>    // strcpy, strlen

using namespace std;


// ---------------------------------------------------------
// ---------------------------------------------------------
// CONSTANTES
// ---------------------------------------------------------
// ---------------------------------------------------------
const int TOTAL_EQUIPOS  = 20;  // TOTAL DE EQUIPOS
const int MAX_REGISTROS  = 10;  // MAXIMO DE VISITANTES
const int TAM            = 50;  // TAMAÑO MAXIMO DE TEXTO

// ---------------------------------------------------------
// ---------------------------------------------------------
// ARREGLO 1D: Estado de equipos  (0=disponible, 1=ocupado)
// ---------------------------------------------------------
// ---------------------------------------------------------
int equipos[TOTAL_EQUIPOS];     // Se llena de ceros en inicializar()

// ---------------------------------------------------------
// ---------------------------------------------------------


// ARREGLO 2D: BITACORA DIARIA DE VISITANTES
//   Filas    → registro del visitante (máx. 10)
//   Columna 0 → ID usuario
//   Columna 1 → Nombre
//   Columna 2 → Hora de entrada
// ---------------------------------------------------------
// ---------------------------------------------------------
char bitacora[MAX_REGISTROS][3][TAM];

int totalRegistros = 0;         // CUANTOS VISITANTES SE REGISTRARON HOY
// =========================================================
//  Inicializar arreglos en 0 / vacío
// =========================================================
void inicializar() {
    // Ponemos todos los equipos como disponibles (0)
    for (int i = 0; i < TOTAL_EQUIPOS; i++) {
        equipos[i] = 0;
    }
    // LIMPIEZA DE BITACORA: SE PONEN CADENAS VACIAS EN CADA DE NUESTROS CAMPOS
    for (int i = 0; i < MAX_REGISTROS; i++) {
        for (int j = 0; j < 3; j++) {
            bitacora[i][j][0] = '\0';   // CADENA VACIA
        }
    }
}

// =========================================================
//  FUNCIÓN 1 — VISTA DE EQUIPOS DISPONIBLES (Arreglo 1D)
// =========================================================
void verEquipos() {
    int disponibles = 0;
    int ocupados    = 0;

    cout << "\n===== EQUIPOS DE COMPUTO =====" << endl;

    for (int i = 0; i < TOTAL_EQUIPOS; i++) {
        cout << "Equipo " << (i + 1) << ": ";

        if (equipos[i] == 0) {
            cout << "DISPONIBLE" << endl;
            disponibles++;
        } else {
            cout << "OCUPADO   " << endl;
            ocupados++;
        }
    }

    cout << "------------------------------" << endl;
    cout << "Disponibles : " << disponibles << endl;
    cout << "Ocupados    : " << ocupados    << endl;
    cout << "==============================" << endl;
}

// =========================================================
//  FUNCIÓN AUXILIAR — ASIGANACION DE EQUIPO DISPONIBLE
// =========================================================
void asignarEquipo() {
    int num;
    cout << "Numero de equipo a asignar (1-" << TOTAL_EQUIPOS << "): ";
    cin  >> num;
    cin.ignore();

    int idx = num - 1;  // El arreglo empieza en 0

    if (idx < 0 || idx >= TOTAL_EQUIPOS) {
        cout << "Numero invalido." << endl;
        return;
    }
    if (equipos[idx] == 1) {
        cout << "El equipo " << num << " ya esta ocupado." << endl;
    } else {
        equipos[idx] = 1;
        cout << "Equipo " << num << " asignado." << endl;
    }
}

// =========================================================
//  FUNCIÓN 2 — REGISTRO DE VISITANTES
// =========================================================
void registrarVisitante() {
    cout << "\n===== REGISTRAR VISITANTE =====" << endl;

    // SE VERIFICA SI YA SE LLENO NUESTRA BITACORA
    if (totalRegistros >= MAX_REGISTROS) {
        cout << "Bitacora llena (maximo " << MAX_REGISTROS << " registros)." << endl;
        return;
    }

    // COLUMNA 0: ID USUARIO
    cout << "ID de usuario  : ";
    cin.ignore();
    cin.getline(bitacora[totalRegistros][0], TAM);

    // COLUMNA 1: NOMBRE
    cout << "Nombre         : ";
    cin.getline(bitacora[totalRegistros][1], TAM);

    // COLUMNA 2: HORA DE ENTRADA
    cout << "Hora de entrada: ";
    cin.getline(bitacora[totalRegistros][2], TAM);

    totalRegistros++;   // Aumentamos el contador de registros

    cout << "Visitante registrado. ("
         << totalRegistros << "/" << MAX_REGISTROS << ")" << endl;

    // PREGUNTARA SI SE ASIGNA EQUIPO O NO
    char resp;
    cout << "Asignar equipo ahora? (s/n): ";
    cin  >> resp;
    if (resp == 's' || resp == 'S') {
        asignarEquipo();
    }
}

// =========================================================
//  FUNCIÓN AUXILIAR — VISTA DE BITACORA
// =========================================================
void verBitacora() {
    cout << "\n===== BITACORA DEL DIA =====" << endl;

    if (totalRegistros == 0) {
        cout << "No hay registros aun." << endl;
        return;
    }

    for (int i = 0; i < totalRegistros; i++) {
        cout << "--- Registro #" << (i + 1) << " ---" << endl;
        cout << "ID     : " << bitacora[i][0]          << endl;
        cout << "Nombre : " << bitacora[i][1]          << endl;
        cout << "Hora   : " << bitacora[i][2]          << endl;
    }
    cout << "============================" << endl;
}

// =========================================================
//  FUNCIÓN 3 — GUARDAR REPORTE EN ARCHIVO
// =========================================================
void generar_reporte() {
    // SE ABRIRA EL ARCHIVO PARA ESCRITURA (SE CREARA SI NO EXISTE)
    ofstream archivo("reporte_dia.txt");

    if (!archivo.is_open()) {
        cout << "ERROR: No se pudo crear reporte_dia.txt" << endl;
        return;
    }

    // Encabezado
    archivo << "=====================================" << endl;
    archivo << "     REPORTE DIARIO DE VISITANTES    " << endl;
    archivo << "=====================================" << endl;
    archivo << "Total de registros: " << totalRegistros  << endl;
    archivo << "-------------------------------------" << endl;

    // ESCRIBIMOS CADA REGISTRO DEL ARREGLO 2
    for (int i = 0; i < totalRegistros; i++) {
        archivo << "Registro #" << (i + 1)         << endl;
        archivo << "  ID    : " << bitacora[i][0]  << endl;
        archivo << "  Nombre: " << bitacora[i][1]  << endl;
        archivo << "  Hora  : " << bitacora[i][2]  << endl;
        archivo << "-------------------------------------" << endl;
    }

    archivo.close();    // CERRAMOS EL ARCHIVO
    cout << "Reporte guardado en 'reporte_dia.txt'." << endl;
}

// =========================================================
//  FUNCIÓN 4 — LECTURA DE REPORTE DESDE NUESTRO ARCHIVO
// =========================================================
void consultar_reporte() {
    // SE ABRIRA EL ARCHIVO PARA LECTURA
    ifstream archivo("reporte_dia.txt");

    if (!archivo.is_open()) {
        cout << "No se encontro 'reporte_dia.txt'." << endl;
        cout << "Primero genera el reporte (opcion 4)." << endl;
        return;
    }

    cout << "\n===== CONTENIDO DEL REPORTE =====" << endl;

    char linea[200];
    //SE LEERA LINEA POR LINEA Y SE MOSTRARA EN PANTALLA
    while (archivo.getline(linea, 200)) {
        cout << linea << endl;
    }

    archivo.close();    // SE CIERRA ARCHIVO
}

// =========================================================
//  MENU PRINCIPAL
// =========================================================
void mostrarMenu() {
    cout << "\n============================================================================\n";
    cout << "   MM           MM   AAAAAA   -RRRRRRRRR   VV         VV   II   NNNN     NN\n";
    cout << "   MMMM       MMMM  AA    AA  -RR     RR    VV       VV    II   NN NN    NN\n";
    cout << "   MM  MM    MM MM  AA    AA  -RR    RR      VV     VV     II   NN  NN   NN\n";
    cout << "   MM   MM MM   MM  AAAAAAAA  -RRRRRR         VV   VV      II   NN   NN  NN\n";
    cout << "   MM    MMM    MM  AA    AA  -RR    RRR       VV VV       II   NN    NN NN\n";
    cout << "   MM     M     MM  AA    AA  -RR      RRR      VVV        II   NN     NNNN\n";
    cout << "============================================================================\n";
    cout << "============================================================================\n";
    cout << "                                 UNRC                                       " << endl;
    cout << "\n==========================================================================" << endl;
    cout << "                          CONTROL DE VISITANTES                             " << endl;
    cout << "============================================================================" << endl;
    cout << "                       1. Ver equipos disponibles                           " << endl;
    cout << "                       2. Registrar visitante                               " << endl;
    cout << "                       3. Ver bitacora del dia                              " << endl;
    cout << "                       4. Generar reporte (archivo)                         " << endl;
    cout << "                       5. Consultar reporte                                 " << endl;
    cout << "                       6. Salir                                             " << endl;
    cout << "============================================================================" << endl;
    cout << " Opcion: ";
}

// =========================================================
//  FUNCIÓN PRINCIPAL
// =========================================================
int main() {
    inicializar();  // PONE TODO LOS EQUIPOS EN 0 Y HACE LIMPIEZA EN NUESTRA BITACORA
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1: verEquipos();         break;
            case 2: registrarVisitante(); break;
            case 3: verBitacora();        break;
            case 4: generar_reporte();    break;
            case 5: consultar_reporte();  break;
            case 6: cout << "\nHasta luego!" << endl; break;
            default: cout << "Opcion invalida." << endl;
        }

    } while (opcion != 6);  // SE REPITARA HASTA SELEECIONAR SALIR

    return 0;
}
