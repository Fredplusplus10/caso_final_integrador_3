// Created by JA24U on 25/11/2024.
//
#include <iostream>
#include <string>
#include <cstdio>
#include <memory> // Para usar punteros inteligentes

using namespace std;

struct ColorConsole {
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox {
    void new_text() {
        // Implementación de la función new_text
        cout << "[ConsoleBox] Preparando para mostrar texto..." << endl;
    }
    void set_text(const string& text) {
        cout << "[ConsoleBox] Texto: " << endl << text << endl;
    }
};

// Usar un puntero inteligente para evitar fugas de memoria
unique_ptr<ConsoleBox> consoleBox = make_unique<ConsoleBox>();

void load_script(const string& filename, bool show_script = false) {
    string script;
    FILE* f = nullptr;

    try {
        f = fopen(filename.c_str(), "rb");
        if (!f) {
            cerr << "Error de apertura de " << filename << endl;
            return;
        }

        char buf[4001];
        size_t c;
        while ((c = fread(buf, 1, 4000, f)) > 0) {
            buf[c] = '\0'; // Agregar carácter nulo al final del buffer
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script) {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << "\033[0m" << endl; // Restablecer formato
        }

        consoleBox->new_text();
        consoleBox->set_text(script);

    } catch (...) {
        cerr << "Error durante la lectura del archivo" << endl;
        if (f) fclose(f);
    }
}

void load_script() {
    string filename;
    cout << "Archivo: ";
    getline(cin, filename); // Leer el nombre del archivo sin riesgo de desbordamiento
    load_script(filename, true);
}

int main() {
    // Llamada a la función load_script() para probar
    load_script();
    return 0;
}
