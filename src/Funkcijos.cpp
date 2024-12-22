#include "Funkcijos.h"

wstring isvalytiZodi(const wstring& zodis) {
    wregex urlRegex(L"(https?://[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(www\\.[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(\\b[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}\\b)");
    if (regex_match(zodis, urlRegex)) {
        return zodis;
    }

    wstring svarusZodis = zodis;

    size_t start = svarusZodis.find_first_not_of(L"0123456789.,!?\"'()[]{}<>;:-„“”");
    size_t end = svarusZodis.find_last_not_of(L"0123456789.,!?\"'()[]{}<>;:-„“”");

    if (start == wstring::npos || end == wstring::npos) {
        return L"";
    }

    return svarusZodis.substr(start, end - start + 1);
}

void toLower(wstring& str) {
    transform(str.begin(), str.end(), str.begin(), ::towlower);
}

void skaitytiFaila(const string& failoPavadinimas, map<wstring, int>& zodziuDaznis, map<wstring, set<int>>& zodziuEilutes) {
    setlocale(LC_ALL, "lt_LT.UTF-8");

    ifstream failas(failoPavadinimas, ios::binary);

    if (!failas.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        return;
    }

    wstring_convert<codecvt_utf8<wchar_t>> keitiklis;

    string eilute;
    int eilutesNumeris = 1;

    while (getline(failas, eilute)) {
        wstring platiEilute = keitiklis.from_bytes(eilute);
        toLower(platiEilute);

        wstringstream srautas(platiEilute);
        wstring zodis;
        while (srautas >> zodis) {
            wstring svarusZodis = isvalytiZodi(zodis);
            if (!svarusZodis.empty()) {
                ++zodziuDaznis[svarusZodis];
                zodziuEilutes[svarusZodis].insert(eilutesNumeris);
            }
        }
        eilutesNumeris++;
    }

    failas.close();
}

vector<wstring> surastiURL(const wstring& tekstas) {

    vector<wstring> urlai;

    wregex regex(L"(https?://[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(www\\.[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(\\b[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}\\b)");
    wsregex_iterator pradzia(tekstas.begin(), tekstas.end(), regex);
    wsregex_iterator pabaiga;

    while (pradzia != pabaiga) {
        urlai.push_back(pradzia->str());
        ++pradzia;
    }
    return urlai;
}

void rasytiFaila(const map<wstring, int>& zodziuDaznis, const map<wstring, set<int>>& zodziuEilutes, const string& isvestiesFailoPavadinimas) {
    ofstream isvestiesFailas(isvestiesFailoPavadinimas, ios::out);

    if (!isvestiesFailas.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << isvestiesFailoPavadinimas << endl;
        return;
    }

    isvestiesFailas.imbue(locale("lt_LT.UTF-8"));

    wstring_convert<codecvt_utf8<wchar_t>> keitiklis;

    string skiltis1 = keitiklis.to_bytes(L"Daugiau nei kartà tekste pasikartojantys þodþiai:\n");
    isvestiesFailas << skiltis1;
    for (const auto& zodis : zodziuDaznis) {
        if (zodis.second > 1) {
            string eilute = keitiklis.to_bytes(zodis.first + L": " + to_wstring(zodis.second) + L"\n");
            isvestiesFailas << eilute;
        }

    }

    string skiltis2 = keitiklis.to_bytes(L"\nCross-reference lentelë:\n");
    isvestiesFailas << skiltis2;
    for (const auto& zodis : zodziuDaznis) {
        if (zodis.second > 1) {
            string eilute = keitiklis.to_bytes(zodis.first + L": ");
            for (const auto& eiluteNr : zodziuEilutes.at(zodis.first)) {
                eilute += to_string(eiluteNr) + ", ";
            }
            eilute = eilute.substr(0, eilute.length() - 2);
            eilute += "\n";
            isvestiesFailas << eilute;
        }
    }

    isvestiesFailas.close();
}

void rasytiURLFaila(const vector<wstring>& urlai, const string& isvestiesFailoPavadinimas) {
    ofstream isvestiesFailas(isvestiesFailoPavadinimas, ios::out);

    if (!isvestiesFailas.is_open()) {
        cerr << "Nepavyko atidaryti failo: " << isvestiesFailoPavadinimas << endl;
        return;
    }

    isvestiesFailas.imbue(locale("lt_LT.UTF-8"));

    wstring_convert<codecvt_utf8<wchar_t>> keitiklis;

    isvestiesFailas << "Surasti URL adresai:\n";
    for (const auto& url : urlai) {
        isvestiesFailas << keitiklis.to_bytes(url) << "\n";
    }

    isvestiesFailas.close();
}