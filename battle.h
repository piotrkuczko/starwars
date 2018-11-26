#ifndef PROJECT_BATTLE_H
#define PROJECT_BATTLE_H

#include <iostream>
#include <limits>
#include <queue>
#include <cassert>
#include "rebelfleet.h"
#include "imperialfleet.h"

template <typename T, T t0, T t1, typename ... S> class SpaceBattle {
private:
    std::queue<RebelStarship> rebelShips;
    std::queue<ImperialStarship> imperialShips;

    //TODO:
    // poprawić żeby działały templaty o nieznanej długości
    void add_ships(S ship, S ... ships){
        if(typeid(ship) == typeid(RebelStarship<S>))
            rebelShips.push(ship);
        else
            imperialShips.push(ship);
        if(sizeof...(ships)>0)
            add_ships(ships);
    }

public:
    template <typename S ...>
    explicit SpaceBattle(S ship, S ... ships){
        static_assert(t0 <= std::numeric_limits<T>::max() &&
                      t0 >= std::numeric_limits<T>::min(), "Starting time is not in range of given type");
        static_assert(t1 <= std::numeric_limits<T>::max() &&
                      t1 >= std::numeric_limits<T>::min(), "Ending time is not in range of given type");
        const int size = sizeof...(ships);

        add_ships(ships);

    }

    size_t countImperialFleet(){

    }

    size_t countRebelFleet(){

    }

    void tick(T timestep){

    }
};

#endif //PROJECT_BATTLE_H
/**
Klasa SpaceBattle<typename T, t0, T t1, typename... S>, gdzie:
T – typ przechowujący czas,
t0 – czas startowy,
        t1 – czas końcowy, po którego przekroczeniu następuje wyzerowanie licznika,
S... – typy statków.
Należy sprawdzać poprawność parametrów t0 i t1 w czasie kompilacji.

Klasa SpaceBattle przyjmuje w konstruktorze kolejno obiekty reprezentujące
statki biorące udział w bitwie.

Klasa SpaceBattle udostępnia metody publiczne:
size_t countImperialFleet() – zwraca liczbę niezniszczonych statków Imperium;
size_t countRebelFleet() - zwraca liczbę niezniszczonych statków Rebelii;
void tick(T timeStep) – na początku sprawdza aktualny czas; jeśli jest to
        czas ataku, to następuje atak statków Imperium na statki Rebelii; na koniec czas
        przesuwa się o timeStep.

SpaceBattle rozgrywa się w czasie międzygwiezdnym. Czas liczony jest
        w sekundach, od sekundy 0 do sekundy t1 i potem znów od sekundy 0, i tak
cyklicznie. Pierwsze odliczanie zaczyna się od sekundy t0. Ze względu na
        zakłócenia magnetyczne statki mogą atakować tylko w sekundach będących
kwadratami liczb całkowitych. Obliczenie wszystkich potrzebnych liczb
reprezentujących sekundy ataku i ich zapamiętanie w odpowiedniej kolekcji musi
odbyć się w czasie kompilacji.

Ataki podczas bitwy odbywają się sekwencyjnie. W sekundzie ataku każdy
niezniszczony statek imperialny po kolei atakuje wszystkie niezniszczone statki
        rebelianckie, czyli ma miejsce następująca sekwencja zdarzeń:

dla każdego statku Imperium
dla każdego statku Rebelii
jeśli oba statki nie nie zostały jeszcze zniszczone,
        statek Imperium atakuje statek Rebelii.

Kolejność atakowania (iterowania) jest zgodna z kolejnością, w jakiej statki
zostały przekazane w konstruktorze. Jeśli zaatakowana jednostka rebeliancka może
        się bronić (ma parametr attackPower), to wtedy obrażenia zadawane są
„jednocześnie” i oba statki odnoszą odpowiednie obrażenia zgodnie z siłami ataku.
Statek zostaje zniszczony, jeśli wytrzymałość jego tarczy spadnie do zera.

Wywołanie tick() na bitwie, podczas gdy wszystkie statki Imperium zostały
        zniszczone, powoduje wypisanie na standardowe wyjście napisu "REBELLION WON\n".
Wywołanie tick() na bitwie, podczas gdy wszystkie statki Rebelii zostały
        zniszczone, powoduje wypisanie na standardowe wyjście napisu "IMPERIUM WON\n".
Jeśli wszystkie statki zarówno Imperium jak i Rebelii są zniszczone, to zostaje
        wypisany napis "DRAW\n".
**/