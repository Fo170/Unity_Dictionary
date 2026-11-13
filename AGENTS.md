# AGENTS.md — Unity_Dictionary

Instructions pour les agents IA travaillant sur ce dépôt.

## Informations générales

- **Nom de la librairie** : Unity_Dictionary
- **Version** : 1.2.0
- **Compte GitHub** : https://github.com/Fo170/
- **Auteur** : Olivier FOURNET
- **Email** : olivier.fournet@free.fr
- **Licence** : GNU General Public License v3.0
- **Langue** : français pour les réponses

## Rôle — à ne jamais déborder

Unity_Dictionary répond à **une seule** question : « quel symbole afficher pour ce
code d'unité ? ».

- ❌ **Aucune magnitude** : ni kilo, ni milli, ni méga. `kVA`, `kW`, `kWh` ne sont
  **pas** des unités ici.
- ❌ **Aucun calcul** : pas de conversion, pas d'arrondi, pas de formatage de valeur.
- ❌ **Aucune dépendance** : ce dépôt ne dépend de rien, et Unity dépend de lui —
  jamais l'inverse.
- ✅ Un code entier par grandeur physique, et un symbole par code.

## Complémentarité avec Unity

| | Unity_Dictionary | Unity |
|---|---|---|
| Entrée | code `9` | valeur `1234.5` + code `9` |
| Sortie | `"VA"` | `"1.23 kVA"` |
| Préfixe SI | non | oui |

## Structure

- Un seul header : `Unity_Dictionary.h`
- Examples : `examples/Exemple/`
- Fichiers de librairie : `library.json`, `library.properties`
- Documentation : `README.md`, `CHANGELOG.md`

## Règles de développement

- Un seul fichier `.h` pour la librairie.
- Toujours renseigner les **deux** rendus (`_TYPE_RS232_` et `_TYPE_WEB_`) pour un
  nouveau code.
- Ne **jamais** réutiliser un code libéré : on ajoute, on ne recycle pas.
- Codes 11 à 15, 43 à 254 : libres.
- `Str_Unit()` doit renvoyer une chaîne vide pour un code inconnu — jamais de crash.
- En cas de bump : synchroniser `Unity_Dictionary.h`, `library.json`,
  `library.properties`, `README.md`, `CHANGELOG.md`.

## Dette technique connue

`_Unit_kW_` (29), `_Unit_kWh_` (34) et `_Unit_kOhms_` (35) portent encore une
magnitude. Ils sont protégés par `UNITY_DICTIONARY_COMPAT` (actif par défaut) et
doivent disparaître en **v1.1.0**, après migration des 5 projets consommateurs.
