#include <stdio.h>

// Makro K urcujuce pocet koni, ktore sa pouzije ak nie je
// zadefinovane ako argument GCC v prikazovom riadku.
#ifndef K
#define K 4
#endif

#define MIN_TRACK 10 // minimalna dlzka trate
#define MAX_TRACK 100 // max. dlzka trate (pouzite ako kapacitu pola pre zavodnu trat)


////////////////// NEMENIT !!! /////////////////////

// Vo vasom rieseni vyuzite tieto tieto funkcie na
// generovanie pseudo-nahodnych cisiel.
//
// Funkcia srnd(seed):
// * Zavolajte 1-krat na zaciatku programu na
// inicializaciu generovanej postupnosti cisiel.
//
// Funkcia rnd(from, to):
// * Sluzi na vygenerovanie dalsieho nahodneho
// cisla z intervalu <from,to>.

#define R_MAX 2147483647

static long long unsigned int SEED = 0x1; // seed generatora

void srnd(int seed) {
    SEED = seed;
}

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

/////////////////////////////////////////////////////////////

int main() {

    int n, p, seed;
    // 1. Nacitanie vstupnych parametrov n, p, seed.
    scanf("%d %d %d", &n, &p, &seed);
    // 2. Inicializacia generatora nahodnych cisiel.
    // Treba zavolat funkciu srnd() a odovzdat do nej nacitanu hodnotu parametra seed.
    srnd(seed);
    // 3. Osetrenie dlzky trate (E1)
    if (n<MIN_TRACK || n>MAX_TRACK)
    {
        printf("E1\n");
        return 0;
    }
    // 4. Osetrenie poctu prekazok (E2)
    if (p>n/2)
    {
        printf("E2\n");
        return 0;
    }
    // 5. Vygenerovanie prekazok na trati
    int trat[MAX_TRACK], pos, prekazok = 0;
    for (int i = 0; i < n; i++)
    {
        trat[i] = 0;
    }
    
    while(prekazok < p)
    {
        pos = rnd(1, n-2);
        if (trat[pos] != 1)
        {
            trat[pos] = 1;
            prekazok++;
        }    
    }
    
    // Treba osetrit chybovu situaciu E3 - objavenie viac ako 3 po sebe iducich vygenerovanych prekazok.
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (trat[i] == 1)
        {
            count++;

            if (count>3)
            {
                printf("E3");
                return 0;
            }

        } else if (trat[i] == 0)
        {
            count = 0;
        }
            
    }
    // 6. Vypis vstupnych parametrov.
    printf("%d %d %d %d\n", K, n,p, seed);
    // 7. Vypis dostihovej trate.
    for (int i = 0; i < n; i++)
    {
        printf("%d", trat[i]);
    }
    printf("\n");
    // 8. Vypis pretekov.
    // 9. Vypis poradia koni v cieli.

    return 0;
}