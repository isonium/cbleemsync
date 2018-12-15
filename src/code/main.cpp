/* 
 * File:   main.cpp
 * Author: screemer
 *
 * Created on 11 Dec 2018, 20:37
 */

#include <iostream>

#include "database.h"
#include "filesystem.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "USAGE: bleemsync dbfilename.db /path/to/games" << endl;
        return EXIT_FAILURE;
    }
    Database *db = new Database();
    if (!db->connect(argv[1]))
    {
        delete db;
        return EXIT_FAILURE;
    }
    if (!db->createInitialDatabase()) {
        cout << "Error creating db structure" << endl;
        db->disconnect();
        delete db;
        return EXIT_FAILURE;
    };
    if (scan_directory_folders(argv[2]) != 0) {
        cout << "Error scanning folders" << endl;
        db->disconnect();
        delete db;
        return EXIT_FAILURE;
    }
    save_database(db);
    db->disconnect();
    delete db;

    return (EXIT_SUCCESS);
}
