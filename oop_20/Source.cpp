#include <iostream>
#include <cstring>
using namespace std;

class Hotel {
private:
    const int idHotel;
    static int numarHoteluri;
    char* nume;
    string oras;
    float pretNoapte;
    int nrCamere;
    int* locuriPeCamera;

public:
    Hotel() : idHotel(++numarHoteluri) {
        nume = nullptr;
        oras = "Necunoscut";
        pretNoapte = 0;
        nrCamere = 0;
        locuriPeCamera = nullptr;
    }

    Hotel(const char* nume, string oras, float pretNoapte,
        int nrCamere, const int* locuri)
        : idHotel(++numarHoteluri)
    {
        if (nume && strlen(nume) > 0) {
            this->nume = new char[strlen(nume) + 1];
            strcpy_s(this->nume, strlen(nume) + 1, nume);
        }
        else {
            this->nume = nullptr;
        }

        this->oras = oras;
        this->pretNoapte = pretNoapte >= 0 ? pretNoapte : 0;
        this->nrCamere = nrCamere > 0 ? nrCamere : 0;

        if (this->nrCamere > 0 && locuri) {
            this->locuriPeCamera = new int[this->nrCamere];
            for (int i = 0; i < this->nrCamere; i++)
                this->locuriPeCamera[i] = locuri[i];
        }
        else {
            this->locuriPeCamera = nullptr;
            this->nrCamere = 0;
        }
    }

    Hotel(const Hotel& h) : idHotel(++numarHoteluri) {
        oras = h.oras;
        pretNoapte = h.pretNoapte;
        nrCamere = h.nrCamere;

        if (h.nume) {
            nume = new char[strlen(h.nume) + 1];
            strcpy_s(nume, strlen(h.nume) + 1, h.nume);
        }
        else nume = nullptr;

        if (h.locuriPeCamera && h.nrCamere > 0) {
            locuriPeCamera = new int[h.nrCamere];
            for (int i = 0; i < h.nrCamere; i++)
                locuriPeCamera[i] = h.locuriPeCamera[i];
        }
        else locuriPeCamera = nullptr;
    }

    void operator=(const Hotel& h) {
        if (this == &h) return;

        oras = h.oras;
        pretNoapte = h.pretNoapte;
        nrCamere = h.nrCamere;

        if (nume) delete[] nume;
        if (h.nume) {
            nume = new char[strlen(h.nume) + 1];
            strcpy_s(nume, strlen(h.nume) + 1, h.nume);
        }
        else nume = nullptr;

        if (locuriPeCamera) delete[] locuriPeCamera;
        if (h.locuriPeCamera && h.nrCamere > 0) {
            locuriPeCamera = new int[h.nrCamere];
            for (int i = 0; i < h.nrCamere; i++)
                locuriPeCamera[i] = h.locuriPeCamera[i];
        }
        else {
            locuriPeCamera = nullptr;
            nrCamere = 0;
        }
    }

    ~Hotel() {
        if (nume) delete[] nume;
        if (locuriPeCamera) delete[] locuriPeCamera;
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

    void setPretNoapte(float p) {
        if (p >= 0) pretNoapte = p;
    }

    float getPretNoapte() { return pretNoapte; }

    void setLocuriPeCamera(int nr, int* locuri) {
        if (nr > 0 && locuri) {
            nrCamere = nr;
            if (locuriPeCamera) delete[] locuriPeCamera;
            locuriPeCamera = new int[nr];
            for (int i = 0; i < nr; i++)
                locuriPeCamera[i] = locuri[i];
        }
    }

    int getLocuriCamera(int index) {
        if (index >= 0 && index < nrCamere) return locuriPeCamera[index];
        throw 404;
    }

    int getNrCamere() { return nrCamere; }

    int getIdHotel() { return idHotel; }

    static int getNumarHoteluri() { return numarHoteluri; }

    void afisare() {
        cout << endl << idHotel << ". Hotel "
            << (nume ? nume : "Fara nume")
            << " | Oras: " << oras
            << " | Pret/noapte: " << pretNoapte
            << " | Nr. camere: " << nrCamere;
        if (nrCamere > 0 && locuriPeCamera) {
            cout << " | Locuri/camera: ";
            for (int i = 0; i < nrCamere; i++)
                cout << locuriPeCamera[i] << (i < nrCamere - 1 ? ", " : "");
        }
    }

    void operator+=(float x) {
        pretNoapte += x;
    }

    friend Hotel operator+=(float x, Hotel& h) {
        h.pretNoapte += x;
        return h;
    }

    bool operator<(const Hotel& h) {
        return pretNoapte < h.pretNoapte;
    }

    bool operator!() {
        return pretNoapte == 0;
    }

    int operator()(int index) {
        return getLocuriCamera(index);
    }

    char& operator[](int index) {
        if (!nume) throw "Nume inexistent!";
        if (index < 0 || index >= (int)strlen(nume)) throw "Index invalid!";
        return nume[index];
    }

    explicit operator int() {
        int total = 0;
        for (int i = 0; i < nrCamere; i++) total += locuriPeCamera[i];
        return total;
    }

    Hotel operator++(int) {
        Hotel copie = *this;
        pretNoapte++;
        return copie;
    }

    Hotel operator++() {
        pretNoapte++;
        return *this;
    }

    friend void operator<<(ostream& out, Hotel h) {
        out << endl << "ID: " << h.idHotel;
        out << endl << "Nume: " << (h.nume ? h.nume : (char*)"N/A");
        out << endl << "Oras: " << h.oras;
        out << endl << "Pret/noapte: " << h.pretNoapte;
        out << endl << "Nr. camere: " << h.nrCamere;
        if (h.locuriPeCamera && h.nrCamere > 0) {
            out << endl << "Locuri pe camera: ";
            for (int i = 0; i < h.nrCamere; i++)
                out << h.locuriPeCamera[i] << " ";
        }
    }

    friend void operator>>(istream& in, Hotel& h) {
        char buf[100];
        in >> buf;
        h.setNume(buf);
        in >> h.oras;
        in >> h.pretNoapte;
        in >> h.nrCamere;
        if (h.locuriPeCamera) {
            delete[] h.locuriPeCamera;
            h.locuriPeCamera = nullptr;
        }
        if (h.nrCamere > 0) {
            h.locuriPeCamera = new int[h.nrCamere];
            for (int i = 0; i < h.nrCamere; i++)
                in >> h.locuriPeCamera[i];
        }
    }
};

int Hotel::numarHoteluri = 0;

int main() {
    int v[4] = { 2, 3, 4, 1 };

    Hotel h1("SkyView", "Cluj", 350.0f, 4, v);
    Hotel h2 = h1;

    h1.afisare();
    h2.afisare();

    cout << h1;

    h1 += 25;
    h1.afisare();

    cout << endl << "Locuri in camera 2: " << h1(1);
    cout << endl << "Litera din nume[1]: " << h1[1];

    cout << endl << "Total locuri (cast la int): " << (int)h1;

    cout << endl << "Numar hoteluri create: " << Hotel::getNumarHoteluri();

    return 0;
}
