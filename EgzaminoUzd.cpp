#include "Lib.h"
#include "Funkcijos.h"

int main() {
    const std::string failoPavadinimas = "tekstas.txt";
    const std::string isvestiesFailoPavadinimas = "rezultatai.txt";

    const std::string urlFailoPavadinimas = "tekstas_url.txt";
    const std::string urlIsvestiesFailoPavadinimas = "rezultatai_url.txt";

    std::setlocale(LC_ALL, "lt_LT.UTF-8");

    std::map<std::wstring, int> zodziuDaznis;
    std::map<std::wstring, std::set<int>> zodziuEilutes;

    std::wstring urlTurinys;
    std::vector<std::wstring> urlai;

    skaitytiFaila(failoPavadinimas, zodziuDaznis, zodziuEilutes);
    rasytiFaila(zodziuDaznis, zodziuEilutes, isvestiesFailoPavadinimas);

    std::wifstream urlFailas(urlFailoPavadinimas);
    urlFailas.imbue(std::locale("lt_LT.UTF-8"));
    std::wstringstream buffer;
    buffer << urlFailas.rdbuf();
    urlTurinys = buffer.str();
    urlai = surastiURL(urlTurinys);
    rasytiURLFaila(urlai, urlIsvestiesFailoPavadinimas);

    return 0;
}