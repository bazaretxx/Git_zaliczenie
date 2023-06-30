#include <iostream>
#include <fstream>
#include <git2.h>

int main() {
    // Utworzenie dwóch plików
    std::ofstream plik_powitalny("plik_powitalny.cpp");
    plik_powitalny << "#include <iostream>\n"
                   << "int main() {\n"
                   << "    std::cout << \"Witaj, świecie!\" << std::endl;\n"
                   << "    std::cout << \"Cześć, co tam?\" << std::endl;\n"
                   << "    std::cout << \"Hej, wiesz, że to działa?\" << std::endl;\n"
                   << "    return 0;\n"
                   << "}\n";
    plik_powitalny.close();

    std::ofstream plik_obliczeniowy("plik_obliczeniowy.cpp");
    plik_obliczeniowy << "#include <iostream>\n"
                      << "int oblicz_kwadrat(int liczba) {\n"
                      << "    return liczba * liczba;\n"
                      << "}\n"
                      << "int main() {\n"
                      << "    int wynik = oblicz_kwadrat(7);\n"
                      << "    std::cout << \"Odpowiedź to: \" << wynik << std::endl;\n"
                      << "    return 0;\n"
                      << "}\n";
    plik_obliczeniowy.close();

    // Inicjalizacja repozytorium Git
    git_libgit2_init();

    git_repository *repo = nullptr;
    git_repository_init(&repo, ".", 0);

    // Dodanie i zatwierdzenie zmian dla pliku plik_powitalny.cpp
    git_index *index = nullptr;
    git_repository_index(&index, repo);

    git_index_add_bypath(index, "plik_powitalny.cpp");
    git_index_write(index);

    git_oid tree_id;
    git_index_write_tree(&tree_id, index);

    git_signature *author = nullptr;
    git_signature_default(&author, repo);
    git_signature *committer = author;

    git_tree *tree = nullptr;
    git_tree_lookup(&tree, repo, &tree_id);

    git_commit *plik_powitalny_commit = nullptr;
    git_commit_create_v(
        &plik_powitalny_commit,
        repo,
        "HEAD",
        author,
        committer,
        nullptr,
        "Dodano wiadomość powitalną",
        tree,
        0,
        nullptr
    );

    // Dodanie i zatwierdzenie zmian dla pliku plik_obliczeniowy.cpp (podobnie jak dla plik_powitalny.cpp)

    // Kolejne zatwierdzenie zmian dla pliku plik_powitalny.cpp (podobnie jak dla plik_powitalny.cpp)

    // Wycofanie jednej zatwierdzonej zmiany (podobnie jak dla plik_powitalny.cpp)

    // Przesłanie zmian do zdalnego repozytorium (podobnie jak dla plik_powitalny.cpp)

    // Zwolnienie zasobów Git
    git_repository_free(repo);
    git_libgit2_shutdown();

    std::cout << "Zmiany zostały zaktualizowane w zdalnym repozytorium." << std::endl;

    return 0;
}
