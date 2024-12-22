#include "Lib.h"
#include "Funkcijos.h"

int main() {
    const string failoPavadinimas = "tekstas.txt";
    const string isvestiesFailoPavadinimas = "rezultatai.txt";

    const string urlFailoPavadinimas = "tekstas_url.txt";
    const string urlIsvestiesFailoPavadinimas = "rezultatai_url.txt";

    setlocale(LC_ALL, "lt_LT.UTF-8");

    map<wstring, int> zodziuDaznis;
    map<wstring, set<int>> zodziuEilutes;

    wstring urlTurinys;
    vector<wstring> urlai;

    skaitytiFaila(failoPavadinimas, zodziuDaznis, zodziuEilutes);
    rasytiFaila(zodziuDaznis, zodziuEilutes, isvestiesFailoPavadinimas);

    wifstream urlFailas(urlFailoPavadinimas);
    urlFailas.imbue(locale("lt_LT.UTF-8"));
    wstringstream buffer;
    buffer << urlFailas.rdbuf();
    urlTurinys = buffer.str();
    urlai = surastiURL(urlTurinys);
    rasytiURLFaila(urlai, urlIsvestiesFailoPavadinimas);

    return 0;
}