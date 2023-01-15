#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;


class Evenimente {
protected:
    string nume;
    int dataIncepere{};
    int oraIncepere{};
    int durata{};
    string sala;
    int numarMaximVizitatori{};
    vector<int> idParticipanti;

public:
    Evenimente() {}

    virtual ~Evenimente() {}

    Evenimente(const string &nume, int dataIncepere, int oraIncepere, int durata, const string &sala,
               int numarMaximVizitatori, const vector<int> &idParticipanti) : nume(nume),
                                                                              dataIncepere(dataIncepere),
                                                                              oraIncepere(oraIncepere),
                                                                              durata(durata), sala(sala),
                                                                              numarMaximVizitatori(
                                                                                      numarMaximVizitatori),
                                                                              idParticipanti(idParticipanti) {}

    friend istream &operator>>(istream &is, Evenimente &evenimente) {
        evenimente.citire(is);
        return is;
    }

    virtual istream &citire(istream &is) {
        cout << "nume:";
        is >> nume;

        cout << "dataIncepere:";
        is >> dataIncepere;

        cout << "oraIncepere:";
        is >> oraIncepere;

        cout << "durata:";
        is >> durata;

        cout << "sala:";
        is >> sala;

        return is;
    }

    friend ostream &operator<<(ostream &os, const Evenimente &evenimente) {
        evenimente.afisare(os);
        return os;
    }

    virtual ostream &afisare(ostream &os) const {
        os << "nume: " << nume << "\n";
        os << "dataIncepere: " << dataIncepere << "\n";
        os << "oraIncepere: " << oraIncepere << "\n";
        os << "durata: " << durata << "\n";
        os << "sala: " << sala << "\n";
        os << "numarMaximVizitatori: " << numarMaximVizitatori << "\n";

        os << "\tparticipanti:" << "\n";
        int i = 0;
        for (auto &participant: idParticipanti) {
            i++;
            os << "participantul " << i << " :" << participant << "\n";
        }

        return os;
    }

    const string &getNume() const {
        return nume;
    }

    int getDataIncepere() const {
        return dataIncepere;
    }
};


struct CreatiiArta {
    string numeLucrare;
    string numeArtist;
};

class ExpozitiiArta : public Evenimente {
private:
    vector<CreatiiArta> creatiiArta;

public:
    ExpozitiiArta() {}

    ~ExpozitiiArta() override {}

    ExpozitiiArta(const string &nume, int dataIncepere, int oraIncepere, int durata, const string &sala,
                  int numarMaximVizitatori, const vector<int> &idParticipanti, const vector<CreatiiArta> &creatiiArta)
            : Evenimente(nume, dataIncepere, oraIncepere, durata, sala, numarMaximVizitatori, idParticipanti),
              creatiiArta(creatiiArta) {}

    istream &citire(istream &is) override {
        Evenimente::citire(is);

        cout << "numarul de creatii de arta:";
        int numarCreatii;
        is >> numarCreatii;

        for (int i = 0; i < numarCreatii; i++) {
            cout << "creatia " << i + 1 << " :" << "\n";

            string numeLucrare, numeArtist;
            cout << "numeLucrare:";
            cin >> numeLucrare;

            cout << "numeArtist";
            cin >> numeArtist;

            creatiiArta.push_back({numeLucrare, numeArtist});
        }

        return is;
    }

    ostream &afisare(ostream &os) const override {
        Evenimente::afisare(os);

        os << "creatii de arta:\n";
        int i = 0;
        for (auto &creatieArta: creatiiArta) {
            i++;
            os << "creatia " << i << ": ";
            os << "numeLucrare: " << creatieArta.numeLucrare << ", numeArtist: " << creatieArta.numeArtist << "\n";
        }

        return os;
    }
};

struct CreatiiCulinare {
    vector<string> listaPreparate;
    string numeBucatar;
};

class ExpozitiiCulinare : public Evenimente {
private:
    vector<CreatiiCulinare> creatiiCulinare;

public:
    ExpozitiiCulinare() {}

    ~ExpozitiiCulinare() override {}

    ExpozitiiCulinare(const string &nume, int dataIncepere, int oraIncepere, int durata, const string &sala,
                      int numarMaximVizitatori, const vector<int> &idParticipanti,
                      const vector<CreatiiCulinare> &creatiiCulinare) : Evenimente(nume, dataIncepere, oraIncepere,
                                                                                   durata, sala, numarMaximVizitatori,
                                                                                   idParticipanti),
                                                                        creatiiCulinare(creatiiCulinare) {}

    istream &citire(istream &is) override {
        Evenimente::citire(is);

        cout << "numarul de creatii culinare:";
        int numarCreatii;
        is >> numarCreatii;

        for (int i = 0; i < numarCreatii; i++) {
            cout << "creatia " << i + 1 << " :";

            cout << "numarul de preparate:";
            int numarPreparate;
            is >> numarPreparate;
            vector<string> tempPreparate;
            for (int j = 0; j < numarPreparate; j++) {
                cout << "preparatul " << j << " :";
                string tempPreparat;
                is >> tempPreparat;
                tempPreparate.push_back(tempPreparat);
            }

            cout << "nume bucatar:";
            string tempBucatar;
            is >> tempBucatar;

            creatiiCulinare.push_back({tempPreparate, tempBucatar});
        }

        return is;
    }

    ostream &afisare(ostream &os) const override {
        Evenimente::afisare(os);

        os << "\t\tcreatii culinare:\n";
        int i = 0;
        for (auto &creatieCulinara: creatiiCulinare) {
            i++;
            os << "\tcreatia culinara " << i << " : ";
            os << "preparate: ";
            for (auto &preparat: creatieCulinara.listaPreparate) {
                os << preparat << " ";
            }
            os << "\n" << "nume bucatar: " << creatieCulinara.numeBucatar << "\n";
        }

        return os;
    }
};

class Spectacole : public Evenimente {
private:
    string tipSpectacol;

public:
    Spectacole() {}

    ~Spectacole() override {}

    Spectacole(const string &nume, int dataIncepere, int oraIncepere, int durata, const string &sala,
               int numarMaximVizitatori, const vector<int> &idParticipanti, const string &tipSpectacol) : Evenimente(
            nume, dataIncepere, oraIncepere, durata, sala, numarMaximVizitatori, idParticipanti), tipSpectacol(
            tipSpectacol) {}

    istream &citire(istream &is) override {
        Evenimente::citire(is);

        cout << "tipSpectacol:";
        is >> tipSpectacol;

        return is;
    }

    ostream &afisare(ostream &os) const override {
        Evenimente::afisare(os);
        os << "tipSpectacol: " << tipSpectacol << "\n";

        return os;
    }
};

class EvenimentCaritabil : public Evenimente {
private:
    string beneficiar;
    float sumaBaniNecesara;

public:
    EvenimentCaritabil() {}

    ~EvenimentCaritabil() override {}

    EvenimentCaritabil(const string &nume, int dataIncepere, int oraIncepere, int durata, const string &sala,
                       int numarMaximVizitatori, const vector<int> &idParticipanti, const string &beneficiar,
                       float sumaBaniNecesara) : Evenimente(nume, dataIncepere, oraIncepere, durata, sala,
                                                            numarMaximVizitatori, idParticipanti),
                                                 beneficiar(beneficiar), sumaBaniNecesara(sumaBaniNecesara) {}

    istream &citire(istream &is) override {
        Evenimente::citire(is);

        cout << "beneficiar:";
        is >> beneficiar;

        cout << "sumaBaniNecesara:";
        is >> sumaBaniNecesara;

        return is;
    }

    ostream &afisare(ostream &os) const override {
        Evenimente::afisare(os);
        os << "beneficiar: " << beneficiar << "\n";
        os << "sumaBaniNecesara: " << sumaBaniNecesara << "\n";

        return os;
    }
};

class Pavilion {
private:
    static int staticIdPavilion;
    int idPavilion{};
    string locatie;
    int oraIntrare{};
    int oraIesire{};
    float suprafata{};
    string numeCoordonator;

    vector<shared_ptr<Evenimente>> evenimente;

public:
    Pavilion() : idPavilion(++staticIdPavilion) {}

    ~Pavilion() {}

    Pavilion(const string &locatie, int oraIntrare, int oraIesire, float suprafata,
             const string &numeCoordonator, const vector<shared_ptr<Evenimente>> &evenimente) : idPavilion(
            ++staticIdPavilion), locatie(locatie), oraIntrare(oraIntrare), oraIesire(oraIesire), suprafata(suprafata),
                                                                                                numeCoordonator(
                                                                                                        numeCoordonator),
                                                                                                evenimente(
                                                                                                        evenimente) {}

    friend istream &operator>>(istream &is, Pavilion &pavilion) {
        pavilion.citire(is);
        return is;
    }

    istream &citire(istream &is) {
        cout << "locatie:";
        is >> locatie;
        cout << "oraIntrare:";
        is >> oraIntrare;
        cout << "oraIesire:";
        is >> oraIesire;
        cout << "suprafata:";
        is >> suprafata;
        cout << "numeCoordonator:";
        is >> numeCoordonator;

        cout << "numarul de evenimente: ";
        int numarEvenimente;
        is >> numarEvenimente;

        for (int i = 0; i < numarEvenimente; i++) {
            cout << "evenimentul " << i << " :";
            int opt, citireValida = 0;

            shared_ptr<Evenimente> tempEveniment;
            while (!citireValida) {
                cout
                        << "Introduceti optiunea dorita(1-ExpozitiiArta, 2-ExpozitiiCulinare, 3-Spectacole, 4-EvenimentCaritabil):";
                cin >> opt;
                citireValida = 1;
                try {
                    if (opt == 1) {
                        tempEveniment = make_shared<ExpozitiiArta>();
                    } else if (opt == 2) {
                        tempEveniment = make_shared<ExpozitiiCulinare>();
                    } else if (opt == 3) {
                        tempEveniment = make_shared<Spectacole>();
                    } else if (opt == 4) {
                        tempEveniment = make_shared<EvenimentCaritabil>();
                    } else {
                        throw opt;
                    }
                    tempEveniment->citire(is);
                    evenimente.push_back(tempEveniment);
                }
                catch (...) {
                    cout << "Optiunea este invalida!\n";
                    citireValida = 0;
                }
            }

            return is;
        }
    }


    friend ostream &operator<<(ostream &os, const Pavilion &pavilion) {
        pavilion.afisare(os);
        return os;
    }

    ostream &afisare(ostream &os) const {
        os << "idPavilion: " << idPavilion << "\n";
        os << "locatie: " << locatie << "\n";
        os << "oraIntrare: " << oraIntrare << "\n";
        os << "oraIesire: " << oraIesire << "\n";
        os << "suprafata: " << suprafata << "\n";
        os << "numeCoordonator: " << numeCoordonator << "\n";

        os << "\tevenimente: ";
        int i = 0;
        for (auto &eveniment: evenimente) {
            i++;
            os << "evenimentul " << i << " :\n";
            os << *eveniment;
        }

        return os;
    }

    const string &getLocatie() const {
        return locatie;
    }

    const vector<shared_ptr<Evenimente>> &getEvenimente() const {
        return evenimente;
    }

};

int Pavilion::staticIdPavilion = 0;


class Bilete {
private:
    static int staticIdBilet;
    int idBilet{};
    string numeParticipant;
    string prenumeParticipant;
    int varsta{};
    string nationalitate;
    int dataInceput{};
    int dataExpirare{};
    float suma{};

public:
    Bilete() : idBilet(++staticIdBilet) {}

    ~Bilete() {}

    Bilete(const string &numeParticipant, const string &prenumeParticipant, int varsta,
           const string &nationalitate, int dataInceput, int dataExpirare, float suma) : idBilet(++staticIdBilet),
                                                                                         numeParticipant(
                                                                                                 numeParticipant),
                                                                                         prenumeParticipant(
                                                                                                 prenumeParticipant),
                                                                                         varsta(varsta),
                                                                                         nationalitate(nationalitate),
                                                                                         dataInceput(dataInceput),
                                                                                         dataExpirare(dataExpirare),
                                                                                         suma(suma) {}

    friend istream &operator>>(istream &is, Bilete &bilete) {
        bilete.citire(is);
        return is;
    }

    istream &citire(istream &is) {
        cout << "idBilet:";
        is >> idBilet;

        cout << "numeParticipant:";
        is >> numeParticipant;

        cout << "prenumeParticipant:";
        is >> prenumeParticipant;

        cout << "varsta:";
        is >> varsta;

        cout << "nationalitate:";
        is >> nationalitate;

        cout << "dataInceput:";
        is >> dataInceput;

        cout << "dataExpirare:";
        is >> dataExpirare;

        cout << "suma:";
        is >> suma;

        return is;
    }


    friend ostream &operator<<(ostream &os, const Bilete &bilete) {
        bilete.afisare(os);
        return os;
    }

    ostream &afisare(ostream &os) const {
        os << "idBilet: " << idBilet << "\n";
        os << "numeParticipant: " << numeParticipant << "\n";
        os << "prenumeParticipant: " << prenumeParticipant << "\n";
        os << "varsta: " << varsta << "\n";
        os << "nationalitate: " << nationalitate << "\n";
        os << "dataInceput: " << dataInceput << "\n";
        os << "dataExpirare: " << dataExpirare << "\n";
        os << "suma: " << suma << "\n";

        return os;
    }
};

class Meniu {
private:
    Meniu() {}

    static Meniu *_instance;

    unsigned int optiune{};
    vector<shared_ptr<Pavilion>> pavilioane;
    vector<shared_ptr<Bilete>> bilete;

    void arataOptiuni() {
        cout << "1. Afisarea pavilioanelor\n";
        cout << "2. Adaugarea unui pavilion\n";
        cout << "3. Adaugarea unui participant\n";
        cout << "4. Ordonarea pavilioanelor dupa zone\n";
        cout << "5. Ordonarea pavilioanelor dupa numarul de evenimente\n";
        cout << "6. Listarea evenimentelor disponibile\n";
        cout << "7. Rezervarea locurilor la evenimentele listate\n";
        cout << "8. Statistica unui pavilion\n";
        cout << "0. Iesire\n";
    }

public:
    static Meniu *getInstance() {
        if (_instance == nullptr)
            _instance = new Meniu;
        return _instance;
    }

    void afisarePavilioane() {
        if (pavilioane.empty())
            cout << "Nu s-au inregistrat pavilioane!\n";

        for (auto &pavilion: pavilioane) {
            cout << *pavilion;
        }
    }

    void adaugarePavilion() {
        shared_ptr<Pavilion> tempPavilion = make_shared<Pavilion>();
        tempPavilion->citire(cin);
        pavilioane.push_back(tempPavilion);
    }

    void adaugareParticipant() {
        shared_ptr<Bilete> tempBilete = make_shared<Bilete>();
        tempBilete->citire(cin);
        bilete.push_back(tempBilete);
    }

    void ordonareZone() {
        sort(pavilioane.begin(), pavilioane.end(),
             [](const shared_ptr<Pavilion> &a, const shared_ptr<Pavilion> &b) -> bool {
                 return a->getLocatie() > b->getLocatie();
             });
    }

    void ordonareNumarParticipanti() {
        sort(pavilioane.begin(), pavilioane.end(),
             [](const shared_ptr<Pavilion> &a, const shared_ptr<Pavilion> &b) -> bool {
                 return a->getEvenimente().size() < b->getEvenimente().size();
             });
    }

    void listareEvenimente() {
//        sort(pavilioane.begin(), pavilioane.end(),
//             [](const shared_ptr<Pavilion> &a, const shared_ptr<Pavilion> &b) -> bool {
//                 return a->getEvenimente().getNume() < b->getEvenimente().getNume();
//             });

        for (auto &pavilion: pavilioane) {
            for (auto &eveniment: pavilion->getEvenimente())
                cout << pavilion->getLocatie() << eveniment->getNume() << eveniment->getDataIncepere();
        }
    }

    void rezervaLocuri() {

    }

    void statisticaPavilion() {
        afisarePavilioane();
        cout << "Introduceti numarul pavilionului a carei statistica va fi afisata:";
        int opt;
        cin >> opt;

        int numarEvenimente = pavilioane[opt]->getEvenimente().size();
        int frecventaEvenimente[4] = {0, 0, 0, 0};

        vector<shared_ptr<Evenimente>> evenimente = pavilioane[opt]->getEvenimente();

        for (auto &eveniment: pavilioane[opt]->getEvenimente()) {
            if (dynamic_pointer_cast<ExpozitiiArta>(eveniment)) {
                frecventaEvenimente[0]++;
            } else if (dynamic_pointer_cast<ExpozitiiCulinare>(eveniment)) {
                frecventaEvenimente[1]++;
            } else if (dynamic_pointer_cast<Spectacole>(eveniment)) {
                frecventaEvenimente[2]++;
            } else if (dynamic_pointer_cast<EvenimentCaritabil>(eveniment)) {
                frecventaEvenimente[3]++;
            }
        }

        cout << "Pavilionul " << opt << ", al tarii " << pavilioane[opt]->getLocatie() << ", a gazduit "
             << numarEvenimente;
        cout << " dintre care " << frecventaEvenimente[0] << "sunt expozitii de arta,";
        cout << " dintre care " << frecventaEvenimente[1] << "sunt expozitii culinare,";
        cout << " dintre care " << frecventaEvenimente[2] << "sunt spectacole,";
        cout << " dintre care " << frecventaEvenimente[3] << "sunt spectacole.";
    }

    void arataMeniu() {
        cout << "Introduceti o optiune din meniul de mai jos:\n";
        arataOptiuni();

        cout << "Optiune:";
        cin >> optiune;

        while (optiune) {
            if (optiune == 1) {
                afisarePavilioane();
            } else if (optiune == 2) {
                adaugarePavilion();
            } else if (optiune == 3) {
                adaugareParticipant();
            } else if (optiune == 4) {
                ordonareZone();
            } else if (optiune == 5) {
                ordonareNumarParticipanti();
            } else if (optiune == 6) {
                listareEvenimente();
            } else if (optiune == 7) {
                rezervaLocuri();
            } else if (optiune == 8) {
                statisticaPavilion();
            } else {
                cout << "Optiunea introdusa nu este corecta!\n";
            }
            arataOptiuni();
            cout << "Optiune:";
            cin >> optiune;
        }
    }
};

Meniu *Meniu::_instance;

int main() {
    Meniu *meniu = Meniu::getInstance();
    meniu->arataMeniu();

    return 0;
}
