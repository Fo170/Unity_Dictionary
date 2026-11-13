# Changelog — Unity_Dictionary

Toutes les dates sont au format AAAA-MM-JJ.
Le versionnage suit [SemVer](https://semver.org/lang/fr/).

## [1.1.0] - 2026-11-13

### ✨ Ajouté

- `Str_Unit_RS232(unit)` et `Str_Unit_Web(unit)` — raccourcis `inline` vers
  `Str_Unit(unit, type)`. Ils complètent la parité d'API avec l'ancien
  `unity_fct.h`, ce qui permet à un projet de migrer **sans réécrire un seul
  appel** (cas de PZEM004T : ~30 sites `Str_Unit_Web(...)`).

### 🔧 Modifié

- La dette technique `UNITY_DICTIONARY_COMPAT` n'est **plus** planifiée pour
  suppression. Les codes 29 / 34 / 35 circulent dans la trame ESP-NOW : les
  autres appareils du parc les décodent, une renumérotation casserait leur
  affichage. La migration exige une révision du contrat de trame, pas un
  simple changement de librairie.

### Migration depuis 1.0.0

Aucune action. Les ajouts sont purement additifs.

---

## [1.0.0] - 2026-11-13

### ✨ Création

Extraction du dictionnaire d'unités hors du dossier partagé
`0_INCLUDE_/Arduino/` (`unity_define.h` + `unity_fct.h`) vers une librairie
PlatformIO versionnée, pour qu'elle soit utilisable par l'écosystème ESP-NOW.

### Principe

- **Aucune magnitude** : le dictionnaire ne connaît que les unités de base.
  Le préfixe SI (k, M, m, µ…) est appliqué par la librairie
  [Unity](https://github.com/Fo170/Unity), qui formate la valeur.
- **Un code par grandeur physique** : P = W (4), S = VA (9), Q = VAR (10),
  N = VAR (10) — la distinction S/Q/N se fait par l'identifiant de variable
  côté application, pas par l'unité.

### Ajouté

- `_Unit_VA_` (9) — puissance apparente (S).
- `_Unit_VAR_` (10) — puissance réactive (Q) et non active (N).
- `Str_Unit(unit, type)` — rendu `_TYPE_RS232_` (texte brut) et `_TYPE_WEB_`
  (entités HTML `&deg;`, `&ohm;`).

### Compatibilité

- `_Unit_kW_` (29), `_Unit_kWh_` (34), `_Unit_kOhms_` (35) sont conservés derrière
  `UNITY_DICTIONARY_COMPAT` (actif par défaut) pour que les projets non migrés
  continuent de compiler **et** d'afficher correctement.
- `Str_Unit()` garde la signature de `unity_fct.h` : aucun appel à modifier.
- Migration : `#include "unity_define.h"` + `#include "unity_fct.h"`
  → `#include <Unity_Dictionary.h>`.
