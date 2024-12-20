#pragma once

#include "Lib.h"

std::wstring isvalytiZodi(const std::wstring& zodis);
void toLower(std::wstring& str);
void skaitytiFaila(const std::string& failoPavadinimas, std::map<std::wstring, int>& zodziuDaznis, std::map<std::wstring, std::set<int>>& zodziuEilutes);
void rasytiFaila(const std::map<std::wstring, int>& zodziuDaznis, const std::map<std::wstring, std::set<int>>& zodziuEilutes, const std::string& isvestiesFailoPavadinimas);
std::vector<std::wstring> surastiURL(const std::wstring& tekstas);
void rasytiURLFaila(const std::vector<std::wstring>& urlai, const std::string& isvestiesFailoPavadinimas);