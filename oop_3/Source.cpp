#include <iostream>
#include <cstring>
using namespace std;

class Film {
private:
    char* titlu;
    char* regizor;
    double durata;
    int anAparitie;
    bool disponibilOnline;

public:
    Film() {
        titlu = nullptr;
        regizor = nullptr;
        durata = 0;
        anAparitie = 0;
        disponibilOnline = false;
    }

    Film(const char* titlu, const char* regizor, double durata, int anAparitie, bool disponibilOnline) {
        if (titlu && strlen(titlu) > 0) {
            this->titlu = new char[strlen(titlu) + 1];
            strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
        }
        else {
            this->titlu = new char[8];
            strcpy_s(this->titlu, 8, "Anonim");
        }

        if (regizor && strlen(regizor) > 0) {
            this->regizor = new char[strlen(regizor) + 1];
            strcpy_s(this->regizor, strlen(regizor) + 1, regizor);
        }
        else {
            this->regizor = new char[8];
            strcpy_s(this->regizor, 8, "Anonim");
        }

        if (durata > 0) this->durata = durata;
        else this->durata = 0;

        if (anAparitie > 1800) this->anAparitie = anAparitie;
        else this->anAparitie = 0;

        this->disponibilOnline = disponibilOnline;
    }

    Film(const Film& f) {
        if (f.titlu) {
            titlu = new char[strlen(f.titlu) + 1];
            strcpy_s(titlu, strlen(f.titlu) + 1, f.titlu);
        }
        else titlu = nullptr;

        if (f.regizor) {
            regizor = new char[strlen(f.regizor) + 1];
            strcpy_s(regizor, strlen(f.regizor) + 1, f.regizor);
        }
        else regizor = nullptr;

        durata = f.durata;
        anAparitie = f.anAparitie;
        disponibilOnline = f.disponibilOnline;
    }

    Film& operator=(const Film& f) {
        if (this == &f) return *this;

        if (titlu) delete[] titlu;
        if (regizor) delete[] regizor;

        if (f.titlu) {
            titlu = new char[strlen(f.titlu) + 1];
            strcpy_s(titlu, strlen(f.titlu) + 1, f.titlu);
        }
        else titlu = nullptr;

        if (f.regizor) {
            regizor = new char[strlen(f.regizor) + 1];
            strcpy_s(regizor, strlen(f.regizor) + 1, f.regizor);
        }
        else regizor = nullptr;

        durata = f.durata;
        anAparitie = f.anAparitie;
        disponibilOnline = f.disponibilOnline;

        return *this;
    }

    ~Film() {
        if (titlu) delete[] titlu;
        if (regizor) delete[] regizor;
    }

    double getDurata() const { return durata; }
    void setDurata(double durata) { if (durata > 0) this->durata = durata; }

    int getAnAparitie() const { return anAparitie; }
    void setAnAparitie(int an) { if (an > 1800) anAparitie = an; }

    bool getDisponibilOnline() const { return disponibilOnline; }
    void setDisponibilOnline(bool val) { disponibilOnline = val; }

    void afisare() const {
        cout << "Film: ";
        if (titlu) cout << titlu; else cout << "N/A";
        cout << ", regizor: ";
        if (regizor) cout << regizor; else cout << "N/A";
        cout << ", durata: " << durata
            << ", an aparitie: " << anAparitie
            << ", disponibil online: " << (disponibilOnline ? "da" : "nu") << endl;
    }
};

int main() {
    Film f1;
    f1.afisare();

    Film f2("Inception", "Christopher Nolan", 148, 2010, true);
    f2.afisare();

    f2.setDurata(150);
    cout << f2.getDurata() << endl;

    f2.setAnAparitie(2012);
    cout << f2.getAnAparitie() << endl;

    f2.setDisponibilOnline(false);
    cout << (f2.getDisponibilOnline() ? "da" : "nu") << endl;

    Film f3 = f2;
    f3.afisare();

    Film f4("Avatar", "James Cameron", 160, 2009, true);
    f4 = f2;
    f4.afisare();

    f4 = f4;

    return 0;
}
