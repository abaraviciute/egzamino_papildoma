#include "Funkcijos.h"

std::wstring isvalytiZodi(const std::wstring& zodis) {
    std::wregex urlRegex(L"(https?://[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(www\\.[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(\\b[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}\\b)");
    if (std::regex_match(zodis, urlRegex)) {
        return zodis;
    }

    std::wstring svarusZodis = zodis;

    size_t start = svarusZodis.find_first_not_of(L"0123456789.,!?\"'()[]{}<>;:-„“”");
    size_t end = svarusZodis.find_last_not_of(L"0123456789.,!?\"'()[]{}<>;:-„“”");

    if (start == std::wstring::npos || end == std::wstring::npos) {
        return L"";
    }

    return svarusZodis.substr(start, end - start + 1);
}

void toLower(std::wstring& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::towlower);
}

void skaitytiFaila(const std::string& failoPavadinimas, std::map<std::wstring, int>& zodziuDaznis, std::map<std::wstring, std::set<int>>& zodziuEilutes) {
    std::setlocale(LC_ALL, "lt_LT.UTF-8");

    std::ifstream failas(failoPavadinimas, std::ios::binary);

    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    std::string eilute;
    int eilutesNumeris = 1;

    while (std::getline(failas, eilute)) {
        std::wstring platiEilute = keitiklis.from_bytes(eilute);
        toLower(platiEilute);

        std::wstringstream srautas(platiEilute);
        std::wstring zodis;
        while (srautas >> zodis) {
            std::wstring svarusZodis = isvalytiZodi(zodis);
            if (!svarusZodis.empty()) {
                ++zodziuDaznis[svarusZodis];
                zodziuEilutes[svarusZodis].insert(eilutesNumeris);
            }
        }
        eilutesNumeris++;
    }

    failas.close();
}

std::vector<std::wstring> surastiURL(const std::wstring& tekstas) {

    std::vector<std::wstring> urlai;

    std::wregex regex(L"(https?://[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(www\\.[\\w.-]+(/[\\w._~:/?#[\\]@!$&'()*+,;=%-]*)?)|(\\b[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}\\b)");
    std::wsregex_iterator pradzia(tekstas.begin(), tekstas.end(), regex);
    std::wsregex_iterator pabaiga;

    while (pradzia != pabaiga) {
        urlai.push_back(pradzia->str());
        ++pradzia;
    }
    return urlai;
}

void rasytiFaila(const std::map<std::wstring, int>& zodziuDaznis, const std::map<std::wstring, std::set<int>>& zodziuEilutes, const std::string& isvestiesFailoPavadinimas) {
    std::ofstream isvestiesFailas(isvestiesFailoPavadinimas, std::ios::out);

    if (!isvestiesFailas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << isvestiesFailoPavadinimas << std::endl;
        return;
    }

    isvestiesFailas.imbue(std::locale("lt_LT.UTF-8"));

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    std::string skiltis1 = keitiklis.to_bytes(L"Daugiau nei kartà tekste pasikartojantys þodþiai:\n");
    isvestiesFailas << skiltis1;
    for (const auto& zodis : zodziuDaznis) {
        if (zodis.second > 1) {
            std::string eilute = keitiklis.to_bytes(zodis.first + L": " + std::to_wstring(zodis.second) + L"\n");
            isvestiesFailas << eilute;
        }

    }

    std::string skiltis2 = keitiklis.to_bytes(L"\nCross-reference lentelë:\n");
    isvestiesFailas << skiltis2;
    for (const auto& zodis : zodziuDaznis) {
        if (zodis.second > 1) {
            std::string eilute = keitiklis.to_bytes(zodis.first + L": ");
            for (const auto& eiluteNr : zodziuEilutes.at(zodis.first)) {
                eilute += std::to_string(eiluteNr) + ", ";
            }
            eilute = eilute.substr(0, eilute.length() - 2);
            eilute += "\n";
            isvestiesFailas << eilute;
        }
    }

    isvestiesFailas.close();
}

void rasytiURLFaila(const std::vector<std::wstring>& urlai, const std::string& isvestiesFailoPavadinimas) {
    std::ofstream isvestiesFailas(isvestiesFailoPavadinimas, std::ios::out);

    if (!isvestiesFailas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << isvestiesFailoPavadinimas << std::endl;
        return;
    }

    isvestiesFailas.imbue(std::locale("lt_LT.UTF-8"));

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    isvestiesFailas << "Surasti URL adresai:\n";
    for (const auto& url : urlai) {
        isvestiesFailas << keitiklis.to_bytes(url) << "\n";
    }

    isvestiesFailas.close();
}