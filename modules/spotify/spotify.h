#pragma once
#include <array>
#include <string>
#include <vector>

// Eén regel in een lijst: [0] naam, [1] ondertitel (artiest/eigenaar), [2] uri om af te spelen.
// Een standaardtype, omdat de globals in packages/spotify.yaml vóór deze header gedeclareerd worden.
using SpItem = std::array<std::string, 3>;
enum { SP_NAAM = 0, SP_SUB = 1, SP_URI = 2 };

// Pagina tonen vanuit een lambda (zelfde als lvgl.page.show)
inline void sp_toon_pagina(esphome::lvgl::LvPageType *p) {
  p->get_parent()->show_page(p->index, LV_SCR_LOAD_ANIM_NONE, 0);
}

// Het response_template in packages/spotify.yaml maakt van het antwoord van Music Assistant
// een lijst van categorieën, elk een lijst van [naam, sub, uri]:
//   [[["Never Be Clever", "Herman Brood", "spotify://track/..."], ...], ...]
// Home Assistant geeft dat door als response["response"], soms als array en soms als tekst.
inline std::vector<std::vector<SpItem>> sp_parse(JsonObjectConst response) {
  std::vector<std::vector<SpItem>> uit;
  JsonDocument doc;
  JsonVariantConst r = response["response"];
  if (r.is<const char *>()) {
    if (deserializeJson(doc, r.as<const char *>()))
      return uit;
    r = doc.as<JsonVariantConst>();
  }
  for (JsonArrayConst cat : r.as<JsonArrayConst>()) {
    std::vector<SpItem> lijst;
    for (JsonArrayConst it : cat)
      lijst.push_back({std::string(it[0] | ""), std::string(it[1] | ""), std::string(it[2] | "")});
    uit.push_back(lijst);
  }
  return uit;
}
