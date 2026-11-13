// ============================================================================
//  Unity_Dictionary.h — Dictionnaire des unités de mesure
//
//  Rôle : répondre à UNE question — « quel symbole afficher pour ce code ? »
//  Il ne gère AUCUNE magnitude : ni kilo, ni milli, ni méga. Le coefficient est
//  du ressort de la librairie Unity (C_UNITY), qui préfixe la valeur.
//
//  Complémentarité :
//    Unity_Dictionary  ->  code d'unité -> "V", "A", "W", "VA", "VAR", "°C"…
//    Unity             ->  valeur + unité -> "12.3 kVA" (préfixe SI appliqué)
//
//  Règle : une unité = une grandeur physique. S (apparente), Q (réactive) et
//  N (non active) se distinguent par l'identifiant de variable côté application,
//  pas par le code d'unité.
//
//  Auteur  : FOURNET Olivier (GPL-3.0)
//  Version : 1.2.0
// ============================================================================
#ifndef UNITY_DICTIONARY_H
#define UNITY_DICTIONARY_H

// Version de la librairie (source UNIQUE — agrégée par liste_lib.h)
#define __UNITY_DICTIONARY_H_VERSION__ "1.2.0"

#include <Arduino.h>

// ----------------------------------------------------------------------------
//  Unités de BASE — aucune magnitude
// ----------------------------------------------------------------------------
#define _Unit_Pas_Utiliser_    0    // emplacement libre / non défini
#define _Unit_Aucune_          1    // valeur sans dimension

#define _Unit_Volt_            2    // V
#define _Unit_Ampere_          3    // A
#define _Unit_Watt_            4    // W    puissance active (P)
#define _Unit_Ohms_            5    // Ω

#define _Unit_Kelvin_          6    // K
#define _Unit_Centigrade_      7    // °C
#define _Unit_Coulomb_         8    // C

#define _Unit_VA_              9    // VA   puissance apparente (S)
#define _Unit_VAR_            10    // VAR  puissance réactive  (Q et N)

#define _Unit_Seconde_        16    // s
#define _Unit_Min_            17    // min
#define _Unit_Heure_          18    // h
#define _Unit_Jour_           19    // j
#define _Unit_Mois_           20    // mois
#define _Unit_Annee_          21    // an

#define _Heures_Decimale_     22    // heure décimale
#define _C_Consigne_          23    // température de consigne
#define _etat_generale_radiateur_ 24 // état général des radiateurs
#define _T_fct_               25    // temps de fonctionnement
#define _DEG_H_               26    // degré/heure
#define _DATE_                27    // AAMMJJ
#define _epoch_               28    // epoch

#define _Unit_Hz_             30    // Hz
#define _Unit_PF_             31    // facteur de puissance
#define _Unit_Ah_             32    // Ah
#define _Unit_Wh_             33    // Wh   énergie
#define _Unit_dBm_            36    // dBm
#define _Unit_hPa_            37    // hPa
#define _Unit_Lux_            38    // lx
#define _Unit_DOD_            39    // Depth Of Discharge
#define _Unit_SOC_            40    // State Of Charge
#define _Unit_pourcent_       41    // %
#define _Unit_n_              42    // rendement (0 à 1)

// --- Puissances avec magnitude (ajout 13/11/2026, v1.2.0) --------------------
// DÉROGATION ASSUMÉE à la règle « unité de base seule ».
// Les capteurs d'énergie Domoticz sont configurés sur ces magnitudes précises :
// convertir à la frontière serait une source d'erreur de plus, sans bénéfice.
// Ces codes ne remplacent PAS _Unit_VA_ (9) / _Unit_VAR_ (10) : ils coexistent,
// et c'est l'application qui choisit ce qu'elle déclare.
#define _Unit_kVA_            43    // kVA   puissance apparente, magnitude k
#define _Unit_kVAR_           44    // kVAR  puissance réactive, magnitude k

#define _NAN_                255    // erreur de donnée

#define _TYPE_RS232_           0    // rendu texte brut
#define _TYPE_WEB_             1    // rendu HTML (entités &deg; &ohm;…)

// ----------------------------------------------------------------------------
//  Compatibilité — codes HISTORIQUES portant une magnitude
//  ⚠️ DETTE TECHNIQUE ASSUMÉE : ces trois codes contredisent la règle « unité
//  de base seule ». Ils restent DÉFINITIVEMENT exposés tant qu'ils circulent
//  sur la trame ESP-NOW : la valeur du code part sur le réseau et les autres
//  appareils du parc (Ordonnanceur, radiateurs, datalogger) la décodent.
//  Les renommer casserait l'affichage de tout le parc en une seule fois.
//  Migration possible seulement avec une révision du contrat de trame :
//              _Unit_kW_   -> _Unit_Watt_  + valeur en W
//              _Unit_kWh_  -> _Unit_Wh_    + valeur en Wh
//              _Unit_kOhms_-> _Unit_Ohms_  + valeur en Ω
// ----------------------------------------------------------------------------
#ifndef UNITY_DICTIONARY_COMPAT
  #define UNITY_DICTIONARY_COMPAT 1
#endif
#if UNITY_DICTIONARY_COMPAT
  #define _Unit_kW_           29    // DÉPRÉCIÉ -> _Unit_Watt_ + valeur en W
  #define _Unit_kWh_          34    // DÉPRÉCIÉ -> _Unit_Wh_ + valeur en Wh
  #define _Unit_kOhms_        35    // DÉPRÉCIÉ -> _Unit_Ohms_ + valeur en Ω
#endif

// ----------------------------------------------------------------------------
//  Str_Unit — symbole d'affichage d'un code d'unité
//  type : _TYPE_RS232_ (texte brut) ou _TYPE_WEB_ (entités HTML)
//  Renvoie une chaîne vide pour un code inconnu.
// ----------------------------------------------------------------------------
inline String Str_Unit(uint16_t unit, int type)
{
    String str = "";

    switch (unit)
    {
        case _Unit_Aucune_:                 str = "";               break;
        case _Unit_Volt_:                   str = "V";              break;
        case _Unit_Ampere_:                 str = "A";              break;
        case _Unit_Watt_:                   str = "W";              break;
        case _Unit_VA_:                     str = "VA";             break;
        case _Unit_VAR_:                    str = "VAR";            break;
        case _Unit_Ohms_:
            if (type == _TYPE_RS232_)       str = "Ohms";
            else                            str = "&ohm;";
            break;

        case _Unit_Kelvin_:
            if (type == _TYPE_RS232_)       str = "\'K";
            else                            str = "&deg;K";
            break;
        case _Unit_Centigrade_:
            if (type == _TYPE_RS232_)       str = "\'C";
            else                            str = "&deg;C";
            break;

        case _Unit_Coulomb_:                str = "Coulombs";       break;

        case _Unit_Seconde_:                str = "s";              break;
        case _Unit_Min_:                    str = "Min";            break;
        case _Unit_Heure_:                  str = "h";              break;
        case _Unit_Jour_:                   str = "j";              break;
        case _Unit_Mois_:                   str = "mois";           break;
        case _Unit_Annee_:                  str = "an";             break;

        case _Heures_Decimale_:             str = "h dec";          break;
        case _C_Consigne_:                  str = "consigne";       break;
        case _etat_generale_radiateur_:     str = "etat";           break;
        case _T_fct_:                       str = "s";              break;
        case _DEG_H_:                       str = "deg/h";          break;
        case _DATE_:                        str = "date";           break;
        case _epoch_:                       str = "epoch";          break;

        case _Unit_Hz_:                     str = "Hz";             break;
        case _Unit_PF_:                     str = "PF";             break;
        case _Unit_Ah_:                     str = "Ah";             break;
        case _Unit_Wh_:                     str = "Wh";             break;
        case _Unit_dBm_:                    str = "dBm";            break;
        case _Unit_hPa_:                    str = "hPa";            break;
        case _Unit_Lux_:                    str = "Lux";            break;
        case _Unit_DOD_:                    str = "DOD";            break;
        case _Unit_SOC_:                    str = "SOC";            break;
        case _Unit_pourcent_:               str = "%";              break;
        case _Unit_n_:                      str = "n";              break;
        case _Unit_kVA_:                    str = "kVA";            break;
        case _Unit_kVAR_:                   str = "kVAR";           break;

#if UNITY_DICTIONARY_COMPAT
        case _Unit_kW_:                     str = "kW";             break;
        case _Unit_kWh_:                    str = "kWh";            break;
        case _Unit_kOhms_:
            if (type == _TYPE_RS232_)       str = "kOhms";
            else                            str = "k&ohm;";
            break;
#endif

        case _NAN_:                         str = "NaN";            break;
        default:                            str = "";               break;
    }
    return str;
}

// ----------------------------------------------------------------------------
//  Raccourcis — parité d'API avec l'ancien `unity_fct.h` du dossier partagé.
//  Permettent de migrer un projet sans réécrire ses appels.
// ----------------------------------------------------------------------------
inline String Str_Unit_RS232(uint16_t unit) { return Str_Unit(unit, _TYPE_RS232_); }
inline String Str_Unit_Web(uint16_t unit)   { return Str_Unit(unit, _TYPE_WEB_);   }

#endif // UNITY_DICTIONARY_H
