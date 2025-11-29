#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    const int idStudent;
    static int numarStudenti;
    char* nume;
    string facultate;
    float medieGenerala;
    int anStudiu;
    bool areBursa;

public:
    Student() : idStudent(++numarStudenti) {
        nume = nullptr;
        facultate = "Necunoscuta";
        medieGenerala = 0;
        anStudiu = 0;
        areBursa = false;
    }

    Student(const char* nume, string facultate, float medieGenerala, int anStudiu, bool areBursa)
        : idStudent(++numarStudenti)
    {
        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = new char[8];
            strcpy_s(this->nume, 8, "Anonim");
        }

        if (!facultate.empty()) {
            this->facultate = facultate;
        }
        else {
            this->facultate = "Necunoscuta";
        }

        if (medieGenerala >= 1 && medieGenerala <= 10) {
            this->medieGenerala = medieGenerala;
        }
        else {
            this->medieGenerala = 0;
        }

        if (anStudiu >= 1 && anStudiu <= 6) {
            this->anStudiu = anStudiu;
        }
        else {
            this->anStudiu = 0;
        }

        this->areBursa = areBursa;
    }

    Student(const Student& s) : idStudent(++numarStudenti) {
        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else {
            nume = nullptr;
        }

        facultate = s.facultate;
        medieGenerala = s.medieGenerala;
        anStudiu = s.anStudiu;
        areBursa = s.areBursa;
    }

    Student& operator=(const Student& s) {
        if (this == &s) return *this;

        if (nume) delete[] nume;

        if (s.nume) {
            nume = new char[strlen(s.nume) + 1];
            strcpy_s(nume, strlen(s.nume) + 1, s.nume);
        }
        else {
            nume = nullptr;
        }

        facultate = s.facultate;
        medieGenerala = s.medieGenerala;
        anStudiu = s.anStudiu;
        areBursa = s.areBursa;

        return *this;
    }

    ~Student() {
        if (nume) delete[] nume;
    }

    int getIdStudent() const { return idStudent; }

    static int getNumarStudenti() { return numarStudenti; }

    char* getNume() const { return nume; }
    void setNume(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (nume) delete[] nume;
            nume = new char[strlen(numeNou) + 1];
            strcpy_s(nume, strlen(numeNou) + 1, numeNou);
        }
    }

    string getFacultate() const { return facultate; }
    void setFacultate(string fac) {
        if (!fac.empty()) facultate = fac;
    }

    float getMedieGenerala() const { return medieGenerala; }
    void setMedieGenerala(float medie) {
        if (medie >= 1 && medie <= 10) medieGenerala = medie;
    }

    int getAnStudiu() const { return anStudiu; }
    void setAnStudiu(int an) {
        if (an >= 1 && an <= 6) anStudiu = an;
    }

    bool getAreBursa() const { return areBursa; }
    void setAreBursa(bool bursa) { areBursa = bursa; }

    void afisare() const {
        cout << "Student #" << idStudent << ": ";
        if (nume) cout << nume; else cout << "N/A";
        cout << ", facultate: " << facultate
            << ", medie: " << medieGenerala
            << ", an: " << anStudiu
            << ", bursa: " << (areBursa ? "da" : "nu") << endl;
    }
};

int Student::numarStudenti = 0;

int main() {
    Student s1;
    s1.afisare();

    Student s2("Ana", "FIA", 9.35f, 2, true);
    s2.afisare();

    s2.setMedieGenerala(8.9f);
    s2.setAnStudiu(3);
    s2.setAreBursa(false);
    s2.afisare();

    Student s3 = s2;
    s3.afisare();

    Student s4("Ion", "IMST", 7.5f, 1, false);
    s4 = s2;
    s4.afisare();

    cout << "Numar studenti creati: " << Student::getNumarStudenti() << endl;

    return 0;
}
