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
                printf("E3\n");
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
    //koniec dostihov = vestky kone v ciely alrbo vsetky kone eliminovane
    //vytazi => poradie vytazov, vyrhali, vyhral[i] = 1/0 ci kon na indexe i uz vyhral alebo nie
    int kone[K], PosBefore[K], PosAfter[K], Nadzigal[K], vytazi[K], vyhral[K];
    int zivychKonov = K, roll, round = 1, indexVytazov = 0;
    for (int i = 0; i < K; i++)
    {
        kone[i] = 1;       //vsetky kone na zaciatku ziju
        PosBefore[i] = -1; //pociatocna pozicia vsetkych konov je -1
        PosAfter[i] = -1;  //Na zaciatku je befora a after 1 a ten isty stav
        Nadzigal[i] = 0;   //Defaultne nikto nenarazil
        vyhral[i] = 0;
    }
    
    //test for
    while(zivychKonov!= 0)
    {
        // kde i je cislo kona(pri vypisoch i+1 aby som pocital od 1)
        for (int i = 0; i < K; i++)
        {
            //ak je kon mrtvy tak sa ide na dalsieho kona
            if (kone[i] == 0)
            {
                continue;
            }
            // ak narazil, vypise sa cakanie, ide sa na dalsieho kona
            if (Nadzigal[i] == 1)
            {
                printf("%3d %3d   -   -   -\n", round, i+1);
                Nadzigal[i] = 0;
                continue;
            }

            if (vyhral[i] == 1)
            {
                continue;
            }
            
            //pozicie sa indexuju od 0 cize pri vsetkych okrem prveho kola treba priratat 1
            if (round != 1)
            {
                PosBefore[i] = PosBefore[i] +1;
            }
            
            roll = rnd(1, 6);
            PosAfter[i] = PosAfter[i] + roll;
            
            //check ci nadzigali
            if (trat[PosAfter[i]] == 1)
            {
                PosAfter[i] = PosAfter[i] + 1;
                if (trat[PosAfter[i]] == 1)
                { 
                    printf("%3d %3d %3d %3d %3d F\n", round, i+1, PosBefore[i], roll, PosAfter[i]);
                    zivychKonov--; 
                    kone[i] = 0; 
                }
                else
                {
                    
                    printf("%3d %3d %3d %3d %3d N\n", round, i+1, PosBefore[i], roll, PosAfter[i]+1);
                    Nadzigal[i] = 1;
                }
                PosBefore[i] = PosAfter[i];
                continue;
            }
            // check ci vyhral 
            if ((PosAfter[i]+1) > n)
            {
                printf("%3d %3d %3d %3d %3d *\n", round, i+1, PosBefore[i], roll, PosAfter[i] + 1);
                vyhral[i] = 1;
                vytazi[indexVytazov] = i+1; //i+1 je cislo kona ktory vyhral
                indexVytazov++;
                continue;
            }
            
            printf("%3d %3d %3d %3d %3d\n", round, i+1, PosBefore[i], roll, PosAfter[i] + 1);
            PosBefore[i] = PosAfter[i];
        }
        round++;
        if (zivychKonov == indexVytazov)
        {
            break;
        }
    }
    
    
    // 9. Vypis poradia koni v cieli.
    printf("ORDER:");
    for (int i = 0; i < zivychKonov; i++)
    {
        printf(" %d", vytazi[i]);
    }
    
    return 0;
}