#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Estudiante {
public:
    string nombre;
    double promedio;
    bool aprobado;
};

void imprimirMenu() {
    cout << "\nMENU PRINCIPAL\n";
    cout << "1. Operaciones basicas\n";
    cout << "2. Registro de notas\n";
    cout << "3. Guardar resultados\n";
    cout << "4. Salir\n";
    cout << "Opcion: ";
}

void cargarEstudiantes(vector<Estudiante> &estudiantes) {
    estudiantes.clear();

    ifstream archivo("estudiantes.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir estudiantes.txt\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.size() == 0) continue;

        Estudiante e;
        e.nombre = linea;
        e.promedio = 0;
        e.aprobado = false;

        estudiantes.push_back(e);
    }

    archivo.close();
    cout << "Estudiantes cargados: " << estudiantes.size() << "\n";
}

void operacionesBasicas() {
    int op;
    cout << "\nOPERACIONES BASICAS\n";
    cout << "1. Suma\n";
    cout << "2. Resta\n";
    cout << "3. Multiplicacion\n";
    cout << "4. Division\n";
    cout << "Opcion: ";
    cin >> op;

    double a, b;

    
    for (int i = 1; i <= 2; i++) {
        if (i == 1) {
            cout << "Ingrese numero 1: ";
            cin >> a;
        } else {
            cout << "Ingrese numero 2: ";
            cin >> b;
        }
    }

    if (op == 1) {
        cout << "Resultado: " << (a + b) << "\n";
    }
    else if (op == 2) {
        cout << "Resultado: " << (a - b) << "\n";
    }
    else if (op == 3) {
        cout << "Resultado: " << (a * b) << "\n";
    }
    else if (op == 4) {
        
        while (b == 0) {
            cout << "Error: no se puede dividir para 0.\n";
            cout << "Ingrese numero 2 nuevamente: ";
            cin >> b;
        }
        cout << "Resultado: " << (a / b) << "\n";
    }
    else {
        cout << "Opcion invalida.\n";
    }
}

void registrarNotas(vector<Estudiante> &estudiantes,
                    int &aprobados, int &reprobados,
                    double &mayorGeneral, double &menorGeneral) {

    aprobados = 0;
    reprobados = 0;

    
    mayorGeneral = -1e9;
    menorGeneral =  1e9;

    if (estudiantes.size() == 0) {
        cout << "No hay estudiantes cargados.\n";
        return;
    }

    int numnotas = 5;

    for (int i = 0; i < (int)estudiantes.size(); i++) {
        double suma = 0;
        double mayor = -1e9;
        double menor =  1e9;

        cout << "\nEstudiante: " << estudiantes[i].nombre << "\n";

        for (int j = 0; j < numnotas; j++) {
            double nota;
            cout << "Nota " << (j + 1) << ": ";
            cin >> nota;

            suma += nota;

            if (nota > mayor) mayor = nota;
            if (nota < menor) menor = nota;
        }

        estudiantes[i].promedio = suma / numnotas;          // promedio con for
        estudiantes[i].aprobado = (estudiantes[i].promedio >= 7.0); // bool aprobado

        if (estudiantes[i].aprobado) aprobados++;
        else reprobados++;

        // Mayor/menor general
        if (mayor > mayorGeneral) mayorGeneral = mayor;
        if (menor < menorGeneral) menorGeneral = menor;

        cout << "Promedio: " << estudiantes[i].promedio << "\n";
        cout << "Estado: " << (estudiantes[i].aprobado ? "Aprobado" : "Reprobado") << "\n";
        cout << "Mayor (este estudiante): " << mayor << "\n";
        cout << "Menor (este estudiante): " << menor << "\n";
    }

    cout << "\nResumen general:\n";
    cout << "Aprobados: " << aprobados << "\n";
    cout << "Reprobados: " << reprobados << "\n";
    cout << "Nota mayor general: " << mayorGeneral << "\n";
    cout << "Nota menor general: " << menorGeneral << "\n";
}

void guardarResultados(const vector<Estudiante> &estudiantes,
                    int aprobados, int reprobados,
                    double mayorGeneral, double menorGeneral) {

    ofstream out("resultados.txt", ios::app);
    if (!out.is_open()) {
        cout << "No se pudo abrir resultados.txt\n";
        return;
    }

    
    out << "Lenguaje: C++\n";
    out << "Aprobados: " << aprobados << " | Reprobados: " << reprobados << "\n";
    out << "Mayor general: " << mayorGeneral << " | Menor general: " << menorGeneral << "\n";
    out << "Listado:\n";

    for (int i = 0; i < (int)estudiantes.size(); i++) {
        out << estudiantes[i].nombre
            << " | Promedio: " << estudiantes[i].promedio
            << " | Estado: " << (estudiantes[i].aprobado ? "Aprobado" : "Reprobado")
            << "\n";
    }

    out << "------------------------------\n";
    out.close();

    cout << "Guardado en resultados.txt\n";
}

int main() {
    vector<Estudiante> estudiantes;

    int aprobados = 0, reprobados = 0;
    double mayorGeneral = 0, menorGeneral = 0;

    
    cargarEstudiantes(estudiantes);

    int opcion;
    do {
        imprimirMenu();
        cin >> opcion;

        if (opcion == 1) {
            operacionesBasicas();
        }
        else if (opcion == 2) {
            registrarNotas(estudiantes, aprobados, reprobados, mayorGeneral, menorGeneral);
        }
        else if (opcion == 3) {
            guardarResultados(estudiantes, aprobados, reprobados, mayorGeneral, menorGeneral);
        }
        else if (opcion == 4) {
            cout << "Saliendo...\n";
        }
        else {
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 4);

    return 0;
}