#pragma once
#include <cctype>
#include <string>

// group_members komt uit Home Assistant als tekst, bijv. "['media_player.woonkamer', 'media_player.keuken']"

// Staat entity_id ent in de lijst? (media_player.woonkamer mag niet matchen op media_player.woonkamer_2)
inline bool sonos_bevat(const std::string &leden, const std::string &ent) {
  for (size_t pos = leden.find(ent); pos != std::string::npos; pos = leden.find(ent, pos + 1)) {
    size_t eind = pos + ent.size();
    if (eind == leden.size() || !(std::isalnum((unsigned char) leden[eind]) || leden[eind] == '_'))
      return true;
  }
  return false;
}

// Aantal spelers in de groep
inline int sonos_aantal(const std::string &leden) {
  int n = 0;
  for (size_t pos = leden.find("media_player."); pos != std::string::npos; pos = leden.find("media_player.", pos + 1))
    n++;
  return n;
}
