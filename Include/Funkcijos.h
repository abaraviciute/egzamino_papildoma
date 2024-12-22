#pragma once

#include "Lib.h"

wstring isvalytiZodi(const wstring& zodis);
void toLower(wstring& str);
void skaitytiFaila(const string& failoPavadinimas, map<wstring, int>& zodziuDaznis, map<wstring, set<int>>& zodziuEilutes);
void rasytiFaila(const map<wstring, int>& zodziuDaznis, const map<wstring, set<int>>& zodziuEilutes, const string& isvestiesFailoPavadinimas);
vector<wstring> surastiURL(const wstring& tekstas);
void rasytiURLFaila(const vector<wstring>& urlai, const string& isvestiesFailoPavadinimas);