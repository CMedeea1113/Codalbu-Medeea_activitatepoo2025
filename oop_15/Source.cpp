#include <iostream>
#include <cstring>
using namespace std;

class Restaurant {
private:
    const int idRestaurant;
    static int numarRestaurante;
    char* nume;
    string adresa;
    float rating;
    int nrMese;
    int* locuriLaMasa;

public:
    Restaurant() : idRestaurant(++numarRestaurante) {
        nume = nullptr;
        adresa = "Necunoscuta";
        rating = 0;
        nrMese = 0;
        locuriLaMasa = nullptr;
    }

    Restaurant(const char* nume, string adresa, float rating,
        int nrMese, const int* locuri)
        : idRestaurant(++numarRestaurante)
    {
        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        this->adresa = adresa;
        this->rating = (rating >= 0 && rating <= 5) ? rating : 0;
        this->nrMese = (nrMese > 0) ? nrMese : 0;

        if (this->nrMese > 0 && locuri) {
            this->locuriLaMasa = new int[this->nrMese];
            for (int i = 0; i < this->nrMese; i++)
                this->locuriLaMasa[i] = locuri[i];
        }
        else {
            this->locuriLaMasa = nullptr;
            this->nrMese = 0;
        }
    }

    Restaurant(const Restaurant& r) : idRestaurant(++numarRestaurante) {
        adresa = r.adresa;
        rating = r.rating;
        nrMese = r.nrMese;

        if (r.nume) {
            nume = new char[strlen(r.nume) + 1];
            strcpy_s(nume, strlen(r.nume) + 1, r.nume);
        }
        else nume = nullptr;

        if (r.locuriLaMasa && r.nrMese > 0) {
            locuriLaMasa = new int[r.nrMese];
            for (int i = 0; i < r.nrMese; i++)
                locuriLaMasa[i] = r.locuriLaMasa[i];
        }
        else locuriLaMasa = nullptr;
    }

    void operator=(const Restaurant& r) {
        if (this == &r) return;

        adresa = r.adresa;
        rating = r.rating;
        nrMese = r.nrMese;

        if (nume) delete[] nume;
        if (r.nume) {
            nume = new char[strlen(r.nume) + 1];
            strcpy_s(nume, strlen(r.nume) + 1, r.nume);
        }
        else nume = nullptr;

        if (locuriLaMasa) delete[] locuriLaMasa;
        if (r.locuriLaMasa && r.nrMese > 0) {
            locuriLaMasa = new int[r.nrMese];
            for (int i = 0; i < r.nrMese; i++)
                locuriLaMasa[i] = r.locuriLaMasa[i];
        }
        else {
            locuriLaMasa = nullptr;
            nrMese = 0;
        }
    }

    ~Restaurant() {
        if (nume) delete[] nume;
        if (locuriLaMasa) delete[] locuriLaMasa;
    }

    void setNume(const char* numeNou) {
        if (numeNou && strlen(numeNou) > 0) {
            if (nume) delete[] nume;
            nume = new char[strlen(numeNou) + 1];
            strcpy_s(nume, strlen(numeNou) + 1, numeNou);
        }
    }

    char* getNume() { return nume; }

    void setAdresa(string adr) {
        if (!adr.empty()) adresa = adr;
    }

    string getAdresa() { return adresa; }

    void setRating(float r) {
        if (r >= 0 && r <= 5) rating = r;
    }

    float getRating() { return rating; }

    int getIdRestaurant() { return idRestaurant; }

    static int getNumarRestaurante() { return numarRestaurante; }

    int getNrMese() { return nrMese; }

    int getLocuriMasa(int index) {
        if (index >= 0 && index < nrMese) return locuriLaMasa[index];
        throw 404;
    }

    void setLocuriLaMasa(int nrMese, int* locuri) {
        if (nrMese > 0 && locuri) {
            this->nrMese = nrMese;
            if (locuriLaMasa) delete[] locuriLaMasa;
            locuriLaMasa = new int[nrMese];
            for (int i = 0; i < nrMese; i++)
                locuriLaMasa[i] = locuri[i];
        }
    }

    void afisare() {
        cout << endl << idRestaurant << ". Restaurant "
            << (nume ? nume : "Fara nume")
            << " | Adresa: " << adresa
            << " | Rating: " << rating
            << " | Nr. mese: " << nrMese;
        if (nrMese > 0 && locuriLaMasa) {
            cout << " | Locuri pe masa: ";
            for (int i = 0; i < nrMese; i++)
                cout << locuriLaMasa[i] << (i < nrMese - 1 ? ", " : "");
        }
    }

    void operator+=(float x) {
        rating += x;
        if (rating > 5) rating = 5;
    }

    friend Restaurant operator+=(float x, Restaurant& r) {
        r.rating += x;
        if (r.rating > 5) r.rating = 5;
        return r;
    }

    bool operator<(const Restaurant& r) {
        return rating < r.rating;
    }

    bool operator!() {
        return rating == 0;
    }

    int operator()(int index) {
        return getLocuriMasa(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        int total = 0;
        for (int i = 0; i < nrMese; i++) total += locuriLaMasa[i];
        return total;
    }

    Restaurant operator++(int) {
        Restaurant copie = *this;
        rating += 0.1f;
        if (rating > 5) rating = 5;
        return copie;
    }

    Restaurant operator++() {
        rating += 0.1f;
        if (rating > 5) rating = 5;
        return *this;
    }

    friend void operator<<(ostream& out, Restaurant r) {
        out << endl << "ID: " << r.idRestaurant;
        out << endl << "Nume: " << (r.nume ? r.nume : (char*)"N/A");
        out << endl << "Adresa: " << r.adresa;
        out << endl << "Rating: " << r.rating;
        out << endl << "Nr. mese: " << r.nrMese;
        if (r.locuriLaMasa && r.nrMese > 0) {
            out << endl << "Locuri la mese: ";
            for (int i = 0; i < r.nrMese; i++)
                out << r.locuriLaMasa[i] << " ";
        }
    }

    friend void operator>>(istream& in, Restaurant& r) {
        char buf[100];
        in >> buf;
        r.setNume(buf);
        in >> r.adresa;
        in >> r.rating;
        in >> r.nrMese;
        if (r.locuriLaMasa) {
            delete[] r.locuriLaMasa;
            r.locuriLaMasa = nullptr;
        }
        if (r.nrMese > 0) {
            r.locuriLaMasa = new int[r.nrMese];
            for (int i = 0; i < r.nrMese; i++)
                in >> r.locuriLaMasa[i];
        }
    }
};

int Restaurant::numarRestaurante = 0;

int main() {
    int v[4] = { 2, 4, 4, 6 };

    Restaurant r1("LaMare", "Bd. Kogalniceanu 10", 4.3f, 4, v);
    Restaurant r2 = r1;

    r1.afisare();
    r2.afisare();

    cout << r1;

    r1 += 0.5f;
    r1.afisare();

    cout << endl << "Locuri la masa 2: " << r1(1);
    cout << endl << "Litera din nume[1]: " << r1[1];

    cout << endl << "Total locuri (cast la int): " << (int)r1;

    cout << endl << "Numar restaurante create: " << Restaurant::getNumarRestaurante();

    return 0;
}
