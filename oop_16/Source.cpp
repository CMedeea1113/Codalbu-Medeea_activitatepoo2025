#include <iostream>
#include <cstring>
using namespace std;

class Cinema {
private:
    const int idCinema;
    static int numarCinemauri;
    char* nume;
    string oras;
    float rating;
    int nrSali;
    int* locuriPeSala;

public:
    Cinema() : idCinema(++numarCinemauri) {
        nume = nullptr;
        oras = "Necunoscut";
        rating = 0;
        nrSali = 0;
        locuriPeSala = nullptr;
    }

    Cinema(const char* nume, string oras, float rating,
        int nrSali, const int* locuri)
        : idCinema(++numarCinemauri)
    {
        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        this->oras = oras;
        this->rating = (rating >= 0 && rating <= 10) ? rating : 0;
        this->nrSali = (nrSali > 0) ? nrSali : 0;

        if (this->nrSali > 0 && locuri) {
            this->locuriPeSala = new int[this->nrSali];
            for (int i = 0; i < this->nrSali; i++)
                this->locuriPeSala[i] = locuri[i];
        }
        else {
            this->locuriPeSala = nullptr;
            this->nrSali = 0;
        }
    }

    Cinema(const Cinema& c) : idCinema(++numarCinemauri) {
        oras = c.oras;
        rating = c.rating;
        nrSali = c.nrSali;

        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (c.locuriPeSala && c.nrSali > 0) {
            locuriPeSala = new int[c.nrSali];
            for (int i = 0; i < c.nrSali; i++)
                locuriPeSala[i] = c.locuriPeSala[i];
        }
        else locuriPeSala = nullptr;
    }

    void operator=(const Cinema& c) {
        if (this == &c) return;

        oras = c.oras;
        rating = c.rating;
        nrSali = c.nrSali;

        if (nume) delete[] nume;
        if (c.nume) {
            nume = new char[strlen(c.nume) + 1];
            strcpy_s(nume, strlen(c.nume) + 1, c.nume);
        }
        else nume = nullptr;

        if (locuriPeSala) delete[] locuriPeSala;
        if (c.locuriPeSala && c.nrSali > 0) {
            locuriPeSala = new int[c.nrSali];
            for (int i = 0; i < c.nrSali; i++)
                locuriPeSala[i] = c.locuriPeSala[i];
        }
        else {
            locuriPeSala = nullptr;
            nrSali = 0;
        }
    }

    ~Cinema() {
        if (nume) delete[] nume;
        if (locuriPeSala) delete[] locuriPeSala;
    }

    void setNume(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (nume) delete[] nume;
            nume = new char[strlen(numeNou) + 1];
            strcpy_s(nume, strlen(numeNou) + 1, numeNou);
        }
    }

    char* getNume() { return nume; }

    void setOras(string o) {
        if (!o.empty()) oras = o;
    }

    string getOras() { return oras; }

    void setRating(float r) {
        if (r >= 0 && r <= 10) rating = r;
    }

    float getRating() { return rating; }

    void setLocuriPeSala(int nr, int* locuri) {
        if (nr > 0 && locuri) {
            nrSali = nr;
            if (locuriPeSala) delete[] locuriPeSala;
            locuriPeSala = new int[nr];
            for (int i = 0; i < nr; i++)
                locuriPeSala[i] = locuri[i];
        }
    }

    int getLocuriSala(int index) {
        if (index >= 0 && index < nrSali) return locuriPeSala[index];
        throw 404;
    }

    int getNrSali() { return nrSali; }

    int getIdCinema() { return idCinema; }

    static int getNumarCinemauri() { return numarCinemauri; }

    void afisare() {
        cout << endl << idCinema << ". Cinema "
            << (nume ? nume : "Fara nume")
            << " | Oras: " << oras
            << " | Rating: " << rating
            << " | Nr. sali: " << nrSali;
        if (nrSali > 0 && locuriPeSala) {
            cout << " | Locuri/sala: ";
            for (int i = 0; i < nrSali; i++)
                cout << locuriPeSala[i] << (i < nrSali - 1 ? ", " : "");
        }
    }

    void operator+=(float x) {
        rating += x;
        if (rating > 10) rating = 10;
    }

    friend Cinema operator+=(float x, Cinema& c) {
        c.rating += x;
        if (c.rating > 10) c.rating = 10;
        return c;
    }

    bool operator<(const Cinema& c) {
        return rating < c.rating;
    }

    bool operator!() {
        return rating == 0;
    }

    int operator()(int index) {
        return getLocuriSala(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        int total = 0;
        for (int i = 0; i < nrSali; i++) total += locuriPeSala[i];
        return total;
    }

    Cinema operator++(int) {
        Cinema copie = *this;
        rating += 0.5f;
        if (rating > 10) rating = 10;
        return copie;
    }

    Cinema operator++() {
        rating += 0.5f;
        if (rating > 10) rating = 10;
        return *this;
    }

    friend void operator<<(ostream& out, Cinema c) {
        out << endl << "ID: " << c.idCinema;
        out << endl << "Nume: " << (c.nume ? c.nume : (char*)"N/A");
        out << endl << "Oras: " << c.oras;
        out << endl << "Rating: " << c.rating;
        out << endl << "Nr. sali: " << c.nrSali;
        if (c.locuriPeSala && c.nrSali > 0) {
            out << endl << "Locuri la sali: ";
            for (int i = 0; i < c.nrSali; i++)
                out << c.locuriPeSala[i] << " ";
        }
    }

    friend void operator>>(istream& in, Cinema& c) {
        char buf[100];
        in >> buf;
        c.setNume(buf);
        in >> c.oras;
        in >> c.rating;
        in >> c.nrSali;
        if (c.locuriPeSala) {
            delete[] c.locuriPeSala;
            c.locuriPeSala = nullptr;
        }
        if (c.nrSali > 0) {
            c.locuriPeSala = new int[c.nrSali];
            for (int i = 0; i < c.nrSali; i++)
                in >> c.locuriPeSala[i];
        }
    }
};

int Cinema::numarCinemauri = 0;

int main() {
    int v[3] = { 120, 150, 80 };

    Cinema c1("CineStar", "Bucuresti", 8.7f, 3, v);
    Cinema c2 = c1;

    c1.afisare();
    c2.afisare();

    cout << c1;

    c1 += 0.8f;
    c1.afisare();

    cout << endl << "Locuri in sala 2: " << c1(1);
    cout << endl << "Litera din nume[1]: " << c1[1];

    cout << endl << "Total locuri (cast la int): " << (int)c1;

    cout << endl << "Numar cinematografe create: " << Cinema::getNumarCinemauri();

    return 0;
}
