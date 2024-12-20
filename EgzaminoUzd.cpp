#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>

void skaitytiFaila(const std::string& failoPavadinimas) {
    std::setlocale(LC_ALL, "lt_LT.UTF-8");

    std::ifstream failas(failoPavadinimas, std::ios::binary);

    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    std::string failoTurinys((std::istreambuf_iterator<char>(failas)),
        std::istreambuf_iterator<char>());

    std::wstring platusTurinys = keitiklis.from_bytes(failoTurinys);

    failas.close();
}

void rasytiFaila(const std::wstring& turinys, const std::string& isvestiesFailoPavadinimas) {
    std::ofstream isvestiesFailas(isvestiesFailoPavadinimas, std::ios::binary);

    if (!isvestiesFailas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << isvestiesFailoPavadinimas << std::endl;
        return;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;

    std::string utf8Turinys = keitiklis.to_bytes(turinys);

    isvestiesFailas << utf8Turinys;

    isvestiesFailas.close();
}

int main() {
    const std::string failoPavadinimas = "tekstas.txt";
    const std::string isvestiesFailoPavadinimas = "rezultatai.txt";

    std::setlocale(LC_ALL, "lt_LT.UTF-8");

    std::ifstream failas(failoPavadinimas, std::ios::binary);
    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return 1;
    }

    std::wstring_convert<std::codecvt_utf8<wchar_t>> keitiklis;
    std::string failoTurinys((std::istreambuf_iterator<char>(failas)), std::istreambuf_iterator<char>());
    std::wstring platusTurinys = keitiklis.from_bytes(failoTurinys);

    failas.close();

    rasytiFaila(platusTurinys, isvestiesFailoPavadinimas);

    return 0;
}