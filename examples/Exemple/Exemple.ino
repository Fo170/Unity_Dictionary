#include <Unity_Dictionary.h>

// Affiche le symbole d'affichage de chaque unité, en RS232 puis en web.
// Aucune magnitude ici : "VA" reste "VA", c'est Unity qui affichera "kVA".

struct ExempleUnite {
  uint16_t code;
  const char* nom;
};

const ExempleUnite unites[] = {
  { _Unit_Volt_,        "tension"          },
  { _Unit_Ampere_,      "courant"          },
  { _Unit_Watt_,        "puissance active" },
  { _Unit_VA_,          "puissance apparente" },
  { _Unit_VAR_,         "puissance reactive"  },
  { _Unit_kVA_,         "apparente, magnitude k" },
  { _Unit_kVAR_,        "reactive, magnitude k" },
  { _Unit_Centigrade_,  "temperature"      },
  { _Unit_Wh_,          "energie"          },
  { _Unit_Lux_,         "luminosite"       },
  { _Unit_pourcent_,    "humidite"         },
  { _Unit_n_,           "rendement"        },
};

void setup()
{
  Serial.begin(115200);
  delay(300);

  Serial.println(F("=== Unity_Dictionary — exemple ==="));
  Serial.println(F("code | nom                 | RS232  | WEB"));
  Serial.println(F("-----+---------------------+--------+--------"));

  for (const ExempleUnite& u : unites)
  {
    Serial.printf("%4u | %-19s | %-6s | %s\n",
                  (unsigned)u.code,
                  u.nom,
                  Str_Unit(u.code, _TYPE_RS232_).c_str(),
                  Str_Unit(u.code, _TYPE_WEB_).c_str());
  }

  // Code inconnu : chaîne vide, jamais de plantage.
  Serial.print(F("code 200 (inconnu) -> ["));
  Serial.print(Str_Unit(200, _TYPE_RS232_));
  Serial.println(F("]"));
}

void loop()
{
  delay(1000);
}
