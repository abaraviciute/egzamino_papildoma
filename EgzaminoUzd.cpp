#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <map>
#include <sstream>

void skaitytiFaila(const std::string& failoPavadinimas, std::wstring& platusTurinys) {
    std::setlocale(LC_ALL, "lt_LT.UTF-8");

    std::ifstream failas(failoPavadinimas, std::ios::binary);

    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    std::string failoTurinys((std::istreambuf_iterator<char>(failas)),
        std::istreambuf_iterator<char>());

    platusTurinys = keitiklis.from_bytes(failoTurinys);

    failas.close();
}

void rasytiFaila(const std::map<std::wstring, int>& zodziuDaznis, const std::string& isvestiesFailoPavadinimas) {
    std::ofstream isvestiesFailas(isvestiesFailoPavadinimas, std::ios::binary);

    if (!isvestiesFailas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << isvestiesFailoPavadinimas << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    for (const auto& pora : zodziuDaznis) {
        std::string eilute = keitiklis.to_bytes(pora.first + L": " + std::to_wstring(pora.second) + L"\n");
        isvestiesFailas << eilute;
    }

    isvestiesFailas.close();
}

void skaiciuotiZodzius(const std::wstring& turinys, std::map<std::wstring, int>& zodziuDaznis) {
    std::wstringstream srautas(turinys);
    std::wstring zodis;

    while (srautas >> zodis) {
        ++zodziuDaznis[zodis];
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