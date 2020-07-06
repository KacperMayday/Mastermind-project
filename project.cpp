#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>

// returns true if two given vectors not match with user input
bool evaluate(std::vector<unsigned int> first, std::vector<unsigned int> second, const int original_correct, const int original_missplaced) {
    if (first == second) return true;

    int correct = 0, missplaced = 0;
    for (unsigned int i = 0; i < first.size(); ++i) {
        if (first[i] == second[i]) {
            ++correct;
            second[i] = 0;
            first[i] = 0;
        }
    }

    if (correct != original_correct) return true;

    for (unsigned int i = 0; i < first.size(); ++i) {
        for (unsigned int j = 0; j < first.size(); ++j) {
            if (first[i] != 0 && first[i] == second[j]) {
                ++missplaced;
                second[j] = 0;
                break;
            }
        }
    }

    if (missplaced != original_missplaced) return true;

    return false;
}

// creates permutations with numbers from 1 to n and store it as a vector of size k in permutations vector
void create_set(std::vector< std::vector<unsigned int> > &permutations, const int &k, const int &n, const bool &repetitions, std::vector<unsigned int> current={}) {
    if (current.size() == k) permutations.push_back(current);
    else {
        for (unsigned int i = 1; i <= n; ++i) {
            bool flag = true;
            if (not repetitions) {
                for (unsigned int e: current) {
                    if (e == i) {
                        flag = false;
                        break;
                    }
                }
            }

            if (flag) {
                std::vector<unsigned int> temp = current;
                temp.push_back(i);
                create_set(permutations, k, n, repetitions, temp);
            }
        }
    }
}

void print_vector(std::vector<unsigned int> &vec) {
    for (unsigned int e: vec) {
            std::cout << e << " ";
    }
}

// game loop
void game() {
    system("cls");
    std::vector< std::vector<unsigned int> > permutations;
    unsigned int k, n;
    bool repetitions;

    std::cout << "Wprowadz k liczb od 1 do n. N i k musza byc liczbami naturalnymi dodatnimi." << std::endl;
    std::cout << "Mimo ze w teorii k moze byc wieksze od 5, lepiej wybrac liczbe z przedzialu 1-4," << std::endl;
    std::cout << "szczegolnie gdy liczba n jest wieksza niz 8." << std::endl;
    std::cout << "Wprowadz k:" << std::endl;
    std::cin >> k;
    std::cout << "Wprowadz n:" << std::endl;
    std::cin >> n;
    std::cout << "Wybierz tryb gry: (0/1 dla kombinacji bez/z powtorzeniami)" << std::endl;
    std::cin >> repetitions;
    std::cout << "Gotowy?" << std::endl;
    system("pause");
    system("cls");

    create_set(permutations, k, n, repetitions);

    for (std::vector< std::vector<unsigned int> >::iterator pointer = permutations.begin(); pointer != permutations.end(); pointer = permutations.begin()) {

        print_vector(*pointer);
        std::cout << "Pozostale kombinacje: " << permutations.size() << std::endl;

        int correct, missplaced;
        std::cin >> correct >> missplaced;

        if (correct == k) {
            std::cout << std::endl << "Twoja kombinacja to: " << std::endl;
            print_vector(*pointer);
            std::cout << std::endl;
            break;
        }

        for (int i = permutations.size() - 1; i >= 0;) {
            if (evaluate(*pointer, permutations[i], correct, missplaced)) {
                permutations.erase(permutations.begin() + i);
            }
            --i;
        }
    }

    if (permutations.size() == 0) std::cout << "Zle odpowiedzi... Brak mozliwych kombinacji" << std::endl;
}

// displays hanoi stacks
void display(std::vector<int> A, std::vector<int> B, std::vector<int> C) {
    std::vector< std::vector<int> > vec{A, B, C};
    for (int i=1; i <= 3; ++i) {
        for (int j=0; j < vec.size(); ++j) {
            if (vec[j][0] == i) std::swap(vec[j], vec[i-1]);
        }
    }
    for (int i=1; i <= 3; ++i) {
        std::cout << i << ": ";
        for (int e = 1; e < vec[i-1].size(); ++e) {
                std::cout << vec[i-1][e] << " ";}
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// recurrent hanoi function
void hanoi(int n, std::vector<int> &A, std::vector<int> &B, std::vector<int> &C) {
    if (n > 0) {
        hanoi(n-1, A, C, B);
        C.push_back(A.back());
        A.pop_back();
        display(A, B, C);
        hanoi(n-1, B, A, C);
    }
}

// secret function which triggers hanoi recurrence
void secret() {
    system("cls");
    int discs;
    std::cout << "Wprowadz liczbe krazkow do ulozenia:" << std::endl;
    std::cin >> discs;
    system("cls");
    std::vector<int> A{1}, B{2}, C{3};
    for (int i=0; i < discs; ++i) {A.push_back(discs - i);}
    display(A, B, C);
    hanoi(discs, A, B, C);
}

// help menu
void help() {
    system("cls");
    bool run = true;
    std::cout << "W grze obowiazuja oryginalne zasady gry Mastermind" << std::endl << std::endl;
    std::cout << "Przyklad rozgrywki oraz opis zasad znajduje sie w pliku z zadaniami na stronie 84 pod numerem 16.1.5" << std::endl << std::endl;
    while (run) {
        std::cout << "Wybierz opcje: (wprowadz liczbe 1-4)" << std::endl;
        std::cout << "\t1. Przyklad" << std::endl;
        std::cout << "\t2. Zasady (skopiowane z pliku z zadaniami)" << std::endl;
        std::cout << "\t3. Menu" << std::endl;
        int input;
        std::cin >> input;
        switch (input) {
            case 1:
                system("cls");
                std::cout << "Przyklad dla k = 4 i n = 6 w trybie z powtorzeniami." << std::endl << std::endl;
                std::cout << "Out: 1 1 1 1 In: 1 0" << std::endl;
                std::cout << "Out: 1 2 2 2 In: 1 1" << std::endl;
                std::cout << "Out: 3 1 2 3 In: 0 3" << std::endl;
                std::cout << "Out: 4 2 3 1 In: 0 3" << std::endl;
                std::cout << "Out: 5 3 1 2 In: 3 0" << std::endl;
                std::cout << "Out: 6 3 1 2 In: 4 0" << std::endl;
                std::cout << std::endl;
                break;
            case 2:
                system("cls");
                std::cout << "Mastermind to gra polegajaca na odgadywaniu ulozenia k pionkow numerowanych od 1 do n. Pionki" << std::endl;
                std::cout << "umieszcza sie w rzedzie od lewej do prawej. Zaleznie od umowy, pionek o tym samym numerze moze" << std::endl;
                std::cout << "sie powtarzac lub nie. Pierwszy gracz uklada w ukryciu pionki, na przyklad 6 3 1 2. Aby odgadnac to" << std::endl;
                std::cout << "ulozenie, drugi gracz pokazuje pierwszemu dowolne ulozenie pionkow, na przyklad 2 6 1 6. " << std::endl;
                std::cout << "W odpowiedzi pierwszy informuje go, ze aby z tego ulozenia uzyskac ukryte, powinien a pionkow pozostawic na" << std::endl;
                std::cout << "dotychczasowym miejscu, b pionkow przestawic, a reszte wymienic na inne. W przedstawionym przykladzie nalezy" << std::endl;
                std::cout << "pozostawic jedynke na trzeciej pozycji, dwojke i jedna szostke przestawic, a jedna szostke" << std::endl;
                std::cout << "wymienic na inny numer, wiec a = 1 i b = 2. Pierwszy gracz przekazuje drugiemu jedynie wartosci" << std::endl;
                std::cout << "a i b, nie ujawniajac, ktore pionki nalezy pozostawic lub przestawic. Znajac a oraz b zgadujacy przedstawia" << std::endl;
                std::cout << "kolejne probne ulozenie i tak dalej, az do odgadniecia ukrytego ulozenia." << std::endl;
                std::cout << std::endl;
                break;
            default:
                run = false;
        }
    }
}

// main menu
void menu() {
    bool secret_enabled = false;
    bool run = true;
    while (run)
    {
        system("cls");
        std::cout << "<" << std::setfill('-') << std::setw(18) << "Menu" << std::setw(14) << "" << ">" << std::endl << std::endl;
        std::cout << "Wybierz opcje: (wprowadz liczbe 1-4)" << std::endl;
        std::cout << "\t1. Start" << std::endl;
        std::cout << "\t2. Pomoc" << std::endl;
        std::cout << "\t3. O mnie" << std::endl;
        std::cout << "\t4. Wyjdz :(" << std::endl;
        if (secret_enabled) std::cout << "\t5. Hanoi :D" << std::endl;
        int input;
        std::cin >> input;
        switch (input)
        {
            case 1:
                game();
                system("pause");
                break;
            case 2:
                help();
                break;
            case 3:
                system("cls");
                std::cout << "Nie spodziewalem sie ze ktos sprawdzi te opcje :D" << std::endl;
                std::cout << "Na wszelki wypadek przygotowalem maly sekret" << std::endl;
                secret_enabled = true;
                system("pause");
                break;
            case 4:
                run = false;
                break;
            case 5:
                secret();
                system("pause");
                secret_enabled = true;
        }
    }
}

int main() {
    menu();
}
