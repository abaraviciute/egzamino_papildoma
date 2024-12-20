#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <map>
#include <sstream>
#include <algorithm>

std::wstring isvalytiZodi(const std::wstring& zodis) {
    std::wstring svarusZodis = zodis;

    size_t start = svarusZodis.find_first_not_of(L"0123456789.,!?\"'()[]{}<>;:-„“”");
    size_t end = svarusZodis.find_last_not_of(L"0123456789.,!?\"'()[]{}<>;:-„“”");

    if (start == std::wstring::npos || end == std::wstring::npos) {
        return L"";
    }

    return svarusZodis.substr(start, end - start + 1);
}

void skaitytiFaila(const std::string& failoPavadinimas, std::wstring& platusTurinys) {
    std::setlocale(LC_ALL, "lt_LT.UTF-8");

    std::ifstream failas(failoPavadinimas, std::ios::binary);

    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }
    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    std::string eilute;
    while (std::getline(failas, eilute)) {
        std::wstring platiEilute = keitiklis.from_bytes(eilute);

        std::wstringstream srautas(platiEilute);
        std::wstring zodis;
        while (srautas >> zodis) {
            std::wstring svarusZodis = isvalytiZodi(zodis);
            if (!svarusZodis.empty()) {
                platusTurinys += svarusZodis + L" ";
            }
        }
    }

    failas.close();
}


void rasytiFaila(const std::map<std::wstring, int>& zodziuDaznis, const std::string& isvestiesFailoPavadinimas) {
    std::ofstream isvestiesFailas(isvestiesFailoPavadinimas, std::ios::binary);

    if (!isvestiesFailas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << isvestiesFailoPavadinimas << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    for (const auto& zodis : zodziuDaznis) {
        if (zodis.second > 1) {
            std::string eilute = keitiklis.to_bytes(zodis.first + L": " + std::to_wstring(zodis.second) + L"\n");
            isvestiesFailas << eilute;
        }

    }

    isvestiesFailas.close();
}

void skaiciuotiZodzius(const std::wstring& turinys, std::map<std::wstring, int>& zodziuDaznis) {
    std::wstringstream srautas(turinys);
    std::wstring zodis;

    while (srautas >> zodis) {
        std::wstring svarusZodis = isvalytiZodi(zodis);
        if (!svarusZodis.empty()) {
            ++zodziuDaznis[zodis];
        }     
    }
}

int main() {
    const std::string failoPavadinimas = "tekstas.txt";
    const std::string isvestiesFailoPavadinimas = "rezultatai.txt";

    std::setlocale(LC_ALL, "lt_LT.UTF-8");

    std::wstring platusTurinys;
    skaitytiFaila(failoPavadinimas, platusTurinys);

    std::map<std::wstring, int> zodziuDaznis;
    skaiciuotiZodzius(platusTurinys, zodziuDaznis);

    rasytiFaila(zodziuDaznis, isvestiesFailoPavadinimas);

    return 0;
}