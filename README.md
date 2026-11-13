# Unity_Dictionary — Dictionnaire des unités de mesure

> Associe un **code d'unité** à son **symbole d'affichage**, sans jamais gérer de
> magnitude. Complémentaire de [Unity](https://github.com/Fo170/Unity), qui applique
> le préfixe SI (k, M, m, µ…) à la valeur.

[![GitHub release](https://img.shields.io/github/v/release/Fo170/Unity_Dictionary)](https://github.com/Fo170/Unity_Dictionary/releases)

---

## Pourquoi deux librairies

| | **Unity_Dictionary** | **Unity** |
|---|---|---|
| Répond à | « quel symbole pour ce code ? » | « comment formater cette valeur ? » |
| Entrée | `9` | `1234.5` + `9` |
| Sortie | `"VA"` | `"1.23 kVA"` |
| Gère les préfixes SI | ❌ non | ✅ oui |
| Dépendance | aucune | Unity_Dictionary |

Séparer les deux permet de **changer d'unité sans toucher au formatage**, et de
**changer le formatage sans toucher au dictionnaire**.

---

## Installation

```ini
lib_deps =
    https://github.com/Fo170/Unity_Dictionary.git@^1.0.0
    https://github.com/Fo170/Unity.git@^1.0.0
```

---

## Utilisation

```cpp
#include <Unity_Dictionary.h>

Serial.println(Str_Unit(_Unit_VA_,  _TYPE_RS232_));   // "VA"
Serial.println(Str_Unit(_Unit_Centigrade_, _TYPE_WEB_)); // "&deg;C"
```

`Str_Unit(unit, type)` renvoie une chaîne vide pour un code inconnu — jamais
d'exception, jamais de plantage.

---

## Codes d'unités

### Unités de base (aucune magnitude)

| Code | Constante | RS232 | Web |
|---|---|---|---|
| 1 | `_Unit_Aucune_` | *(vide)* | *(vide)* |
| 2 | `_Unit_Volt_` | `V` | `V` |
| 3 | `_Unit_Ampere_` | `A` | `A` |
| 4 | `_Unit_Watt_` | `W` | `W` |
| 5 | `_Unit_Ohms_` | `Ohms` | `&ohm;` |
| 6 | `_Unit_Kelvin_` | `'K` | `&deg;K` |
| 7 | `_Unit_Centigrade_` | `'C` | `&deg;C` |
| 8 | `_Unit_Coulomb_` | `Coulombs` | `Coulombs` |
| **9** | **`_Unit_VA_`** | **`VA`** | **`VA`** |
| **10** | **`_Unit_VAR_`** | **`VAR`** | **`VAR`** |

### Temps et divers

| Code | Constante | Symbole |
|---|---|---|
| 16 | `_Unit_Seconde_` | `s` |
| 17 | `_Unit_Min_` | `Min` |
| 18 | `_Unit_Heure_` | `h` |
| 19 | `_Unit_Jour_` | `j` |
| 20 | `_Unit_Mois_` | `mois` |
| 21 | `_Unit_Annee_` | `an` |
| 22 | `_Heures_Decimale_` | `h dec` |
| 25 | `_T_fct_` | `s` |
| 26 | `_DEG_H_` | `deg/h` |
| 28 | `_epoch_` | `epoch` |

### Électricité et mesures

| Code | Constante | Symbole |
|---|---|---|
| 30 | `_Unit_Hz_` | `Hz` |
| 31 | `_Unit_PF_` | `PF` |
| 32 | `_Unit_Ah_` | `Ah` |
| 33 | `_Unit_Wh_` | `Wh` |
| 36 | `_Unit_dBm_` | `dBm` |
| 37 | `_Unit_hPa_` | `hPa` |
| 38 | `_Unit_Lux_` | `Lux` |
| 39 | `_Unit_DOD_` | `DOD` |
| 40 | `_Unit_SOC_` | `SOC` |
| 41 | `_Unit_pourcent_` | `%` |
| 42 | `_Unit_n_` | `n` |
| 255 | `_NAN_` | `NaN` |

---

## Les quatre puissances

| Grandeur | Unité | Code | Remarque |
|---|---|---|---|
| **P** — active | W | `_Unit_Watt_` (4) | |
| **S** — apparente | VA | `_Unit_VA_` (9) | |
| **Q** — réactive | VAR | `_Unit_VAR_` (10) | |
| **N** — non active | VAR | `_Unit_VAR_` (10) | distinguée par l'`id_var`, pas par l'unité |

Le coefficient (kVA, kVAR) n'est **pas** un code : c'est Unity qui le calcule à
l'affichage.

---

## ⚠️ Dette technique : trois codes historiques

Ces codes portent encore une magnitude, contrairement à la règle :

| Code | Constante | À remplacer par |
|---|---|---|
| 29 | `_Unit_kW_` | `_Unit_Watt_` + valeur en **W** |
| 34 | `_Unit_kWh_` | `_Unit_Wh_` + valeur en **Wh** |
| 35 | `_Unit_kOhms_` | `_Unit_Ohms_` + valeur en **Ω** |

Ils sont conservés pour que les projets non encore migrés continuent de compiler
et d'afficher correctement. Désactivables via :

```cpp
#define UNITY_DICTIONARY_COMPAT 0   // avant l'include
```

**Suppression prévue en v1.1.0**, une fois les 5 projets concernés migrés
(ESP8266-Radiateur, ESP8266-Thermometre, PZEM004T, Station_Meteo,
WeMosMini_BME280_Garage).

---

## Migration depuis `unity_define.h` / `unity_fct.h`

Ces deux headers du dossier partagé `0_INCLUDE_/Arduino/` fusionnent ici.

```diff
- #include "unity_define.h"
- #include "unity_fct.h"
+ #include <Unity_Dictionary.h>
```

`Str_Unit(unit, type)` garde exactement la même signature : aucun appel à modifier.

---

## Licence

GPL-3.0-only — Olivier FOURNET
