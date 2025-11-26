#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    char* nume;
    int nota;
    char** materii;
    int NrMaterii;
    int varsta;
    float medieGenerala;

public:
    Student() {
        nume = nullptr;
        nota = 0;
        materii = nullptr;
        NrMaterii = 0;
        varsta = 0;
        medieGenerala = 0;
    }

    Student(const char* nume, int nota, int nrMaterii,
        const char** materii, int varsta, float medieGenerala) {

        if (nota < 1 || nota > 10)
            this->nota = 1;
        else
            this->nota = nota;

        this->nume = new char[strlen(nume) + 1];
        strcpy_s(this->nume, strlen(nume) + 1, nume);

        this->NrMaterii = nrMaterii;
        this->materii = new char* [NrMaterii];
        for (int i = 0; i < NrMaterii; i++) {
            this->materii[i] = new char[strlen(materii[i]) + 1];
            strcpy_s(this->materii[i], strlen(materii[i]) + 1, materii[i]);
        }

        this->varsta = varsta;
        this->medieGenerala = medieGenerala;
    }

    Student(const Student& s) {
        nota = s.nota;
        medieGenerala = s.medieGenerala;
        varsta = s.varsta;

        if (s.nume != nullptr) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else
            nume = nullptr;

        NrMaterii = s.NrMaterii;
        if (NrMaterii > 0) {
            materii = new char* [NrMaterii];
            for (int i = 0; i < NrMaterii; i++) {
                materii[i] = new char[strlen(s.materii[i]) + 1];
                strcpy_s(materii[i], strlen(s.materii[i]) + 1, s.materii[i]);
            }
        }
        else
            materii = nullptr;
    }

    Student& operator=(const Student& s) {
        if (this == &s)
            return *this;

        if (nume != nullptr)
            delete[] nume;

        if (materii != nullptr) {
            for (int i = 0; i < NrMaterii; i++)
                delete[] materii[i];
            delete[] materii;
        }

        nota = s.nota;
        medieGenerala = s.medieGenerala;
        varsta = s.varsta;

        if (s.nume != nullptr) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else
            nume = nullptr;

        NrMaterii = s.NrMaterii;
        if (NrMaterii > 0) {
            materii = new char* [NrMaterii];
            for (int i = 0; i < NrMaterii; i++) {
                materii[i] = new char[strlen(s.materii[i]) + 1];
                strcpy_s(materii[i], strlen(s.materii[i]) + 1, s.materii[i]);
            }
        }
        else
            materii = nullptr;

        return *this;
    }

    ~Student() {
        if (nume != nullptr)
            delete[] nume;

        if (materii != nullptr) {
            for (int i = 0; i < NrMaterii; i++)
                delete[] materii[i];
            delete[] materii;
        }
    }

    int getNota() { return nota; }

    void setNota(int n) {
        if (n >= 1 && n <= 10)
            nota = n;
    }

    int getvarsta() { return varsta; }

    void setvarsta(int v) {
        if (v >= 18 && v <= 80)
            varsta = v;
    }

    float getMedie() { return medieGenerala; }

    void setMedie(float m) {
        if (m >= 1 && m <= 10)
            medieGenerala = m;
    }

    void afisare() {
        cout << "\nStudentul: " << (nume ? nume : "Necunoscut");
        cout << "\nNota: " << nota;
        cout << "\nVarsta: " << varsta;
        cout << "\nMedie generala: " << medieGenerala;
        cout << "\nMaterii:";
        for (int i = 0; i < NrMaterii; i++)
            cout << "\n  - " << materii[i];
        cout << "\n";
    }
};

int main() {
    const char* mat[] = { "POO", "Algoritmica", "Matematica" };

    Student s1("vasile", 10, 3, mat, 17, 9.50f);

    Student s2 = s1;   // constructor de copiere
    Student s3;
    s3 = s1;           // operator=

    s1.afisare();
    s2.afisare();
    s3.afisare();

    return 0;
}
