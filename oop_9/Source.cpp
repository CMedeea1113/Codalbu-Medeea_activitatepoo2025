#include <iostream>
#include <cstring>
using namespace std;

class JocVideo {
private:
    const int idJoc;
    static int numarJocuri;
    char* titlu;
    string gen;
    float rating;
    int anLansare;
    int nrExpansions;
    float* pretExpansions;

public:
    void setRating(float rating) {
        if (rating >= 0 && rating <= 10) this->rating = rating;
    }

    float getRating() { return this->rating; }

    char* getTitlu() { return this->titlu; }

    void setTitlu(const char* titlu) {
        if (titlu && strlen(titlu) > 0) {
            if (this->titlu) delete[] this->titlu;
            this->titlu = new char[strlen(titlu) + 1];
            strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
        }
    }

    void setGen(string gen) {
        if (!gen.empty()) this->gen = gen;
    }

    void setPretExpansions(int nr, float* src) {
        if (nr > 0 && src) {
            this->nrExpansions = nr;
            if (pretExpansions) delete[] pretExpansions;
            pretExpansions = new float[nr];
            for (int i = 0; i < nr; i++) pretExpansions[i] = src[i];
        }
    }

    float getPretExpansion(int index) {
        if (index >= 0 && index < nrExpansions) return pretExpansions[index];
        throw 404;
    }

    int getNrExpansions() { return nrExpansions; }
    int getIdJoc() { return idJoc; }
    string getGen() { return gen; }
    int getAnLansare() { return anLansare; }
    static int getNumarJocuri() { return numarJocuri; }

    JocVideo() : idJoc(++numarJocuri) {
        titlu = nullptr;
        gen = "Necunoscut";
        rating = 0;
        anLansare = 0;
        nrExpansions = 0;
        pretExpansions = nullptr;
    }

    JocVideo(const char* titlu, string gen, float rating,
        int anLansare, int nrExpansions, const float* preturi)
        : idJoc(++numarJocuri)
    {
        this->gen = gen;
        this->rating = rating;
        this->anLansare = anLansare;
        this->nrExpansions = nrExpansions;

        if (titlu && strlen(titlu) > 0) {
            this->titlu = new char[strlen(titlu) + 1];
            strcpy_s(this->titlu, strlen(titlu) + 1, titlu);
        }
        else {
            this->titlu = nullptr;
        }

        if (nrExpansions > 0 && preturi) {
            pretExpansions = new float[nrExpansions];
            for (int i = 0; i < nrExpansions; i++) pretExpansions[i] = preturi[i];
        }
        else {
            pretExpansions = nullptr;
            this->nrExpansions = 0;
        }
    }

    JocVideo(const JocVideo& j) : idJoc(++numarJocuri) {
        gen = j.gen;
        rating = j.rating;
        anLansare = j.anLansare;
        nrExpansions = j.nrExpansions;

        if (j.titlu) {
            titlu = new char[strlen(j.titlu) + 1];
            strcpy_s(titlu, strlen(j.titlu) + 1, j.titlu);
        }
        else titlu = nullptr;

        if (j.pretExpansions && j.nrExpansions > 0) {
            pretExpansions = new float[j.nrExpansions];
            for (int i = 0; i < j.nrExpansions; i++)
                pretExpansions[i] = j.pretExpansions[i];
        }
        else pretExpansions = nullptr;
    }

    void operator=(const JocVideo& j) {
        if (this == &j) return;

        gen = j.gen;
        rating = j.rating;
        anLansare = j.anLansare;
        nrExpansions = j.nrExpansions;

        if (titlu) delete[] titlu;
        if (j.titlu) {
            titlu = new char[strlen(j.titlu) + 1];
            strcpy_s(titlu, strlen(j.titlu) + 1, j.titlu);
        }
        else titlu = nullptr;

        if (pretExpansions) delete[] pretExpansions;
        if (j.pretExpansions && j.nrExpansions > 0) {
            pretExpansions = new float[j.nrExpansions];
            for (int i = 0; i < j.nrExpansions; i++)
                pretExpansions[i] = j.pretExpansions[i];
        }
        else {
            pretExpansions = nullptr;
            nrExpansions = 0;
        }
    }

    ~JocVideo() {
        if (titlu) delete[] titlu;
        if (pretExpansions) delete[] pretExpansions;
    }

    void operator+=(float x) { rating += x; }

    bool operator<(const JocVideo& j) {
        return rating < j.rating;
    }

    bool operator!() {
        return rating == 0;
    }

    float operator()(int i) {
        return getPretExpansion(i);
    }

    char& operator[](int i) {
        if (!titlu) throw "Titlu inexistent!";
        if (i < 0 || i >= (int)strlen(titlu)) throw "Index invalid!";
        return titlu[i];
    }

    explicit operator int() { return anLansare; }

    JocVideo operator++(int) {
        JocVideo aux = *this;
        rating += 0.1f;
        return aux;
    }

    JocVideo operator++() {
        rating += 0.1f;
        return *this;
    }

    void afisare() {
        cout << endl << idJoc << ". "
            << (titlu ? titlu : "Fara titlu")
            << " | " << gen
            << " | Rating: " << rating
            << " | Lansare: " << anLansare
            << " | Expansions: " << nrExpansions;
    }

    friend void operator<<(ostream& out, JocVideo j) {
        out << endl << "ID: " << j.idJoc;
        out << endl << "Titlu: " << (j.titlu ? j.titlu : "N/A");
        out << endl << "Gen: " << j.gen;
        out << endl << "Rating: " << j.rating;
        out << endl << "An lansare: " << j.anLansare;
        out << endl << "Expansions: " << j.nrExpansions << " -> ";
        if (j.pretExpansions)
            for (int i = 0; i < j.nrExpansions; i++) out << j.pretExpansions[i] << " ";
    }

    friend void operator>>(istream& in, JocVideo& j) {
        char buf[100];
        in >> buf;
        j.setTitlu(buf);
        in >> j.gen;
        in >> j.rating;
        in >> j.anLansare;
        in >> j.nrExpansions;
        if (j.pretExpansions) delete[] j.pretExpansions;
        if (j.nrExpansions > 0) {
            j.pretExpansions = new float[j.nrExpansions];
            for (int i = 0; i < j.nrExpansions; i++) in >> j.pretExpansions[i];
        }
        else {
            j.pretExpansions = nullptr;
        }
    }
};

int JocVideo::numarJocuri = 0;

int main() {
    float v[3] = { 19.9f, 24.9f, 14.9f };

    JocVideo j("Nexus", "RPG", 9.2f, 2022, 3, v);
    JocVideo j2 = j;

    j.afisare();
    j2.afisare();

    cout << j;

    j += 0.3f;
    j.afisare();

    cout << endl << j(1);
    cout << endl << j[2];

    cout << endl << "Numar jocuri create: " << JocVideo::getNumarJocuri();

    return 0;
}
