/*
 * Course: CIS-25 - Programming Using C++
 * Student: H Cheng
 * Module: Module 4 - Datasets, Arrays, and Pointers
 *
 * dataset_loader.h
 * Reusable functions for reading the Kaggle "Top Spotify Songs 2023" CSV
 * (data/spotify-2023.csv, pulled by download_dataset.sh) into parallel C++ arrays.
 *
 * CSV columns used (0-based index in the Kaggle file):
 *   0 track_name | 1 artist(s)_name | 3 released_year | 8 streams
 */

#ifndef DATASET_LOADER_H
#define DATASET_LOADER_H

#include <fstream>
#include <string>
#include <vector>

// Relative path of the CSV downloaded from Kaggle by download_dataset.sh
const std::string DATASET_PATH = "data/spotify-2023.csv";

// Column positions inside the Kaggle CSV header row
const int COL_TRACK_NAME = 0;
const int COL_ARTIST_NAME = 1;
const int COL_RELEASED_YEAR = 3;
const int COL_STREAMS = 8;

// Splits one CSV line into fields. Handles quoted fields such as
// "Latto, Jung Kook" (comma inside quotes) and doubled quotes ("").
inline std::vector<std::string> parseCsvLine(const std::string &line) {
    std::vector<std::string> fields;
    std::string current;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            if (insideQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"';   // escaped quote
                i++;
            } else {
                insideQuotes = !insideQuotes;
            }
        } else if (c == ',' && !insideQuotes) {
            fields.push_back(current);
            current.clear();
        } else if (c != '\r') {   // ignore Windows line endings
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}

// Returns true if the text is made only of digits (e.g. a valid stream count)
inline bool isNumeric(const std::string &text) {
    if (text.empty()) return false;
    for (char c : text) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

// Reads up to maxRecords rows from the Kaggle CSV into parallel arrays.
// Returns the number of records loaded, or -1 if the file could not be opened.
inline int loadSpotifyRecords(const std::string &path,
                              std::string titles[], std::string artists[],
                              int years[], long long streams[], int maxRecords) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return -1;
    }

    std::string line;
    std::getline(file, line);   // skip the header row

    int count = 0;
    while (count < maxRecords && std::getline(file, line)) {
        std::vector<std::string> fields = parseCsvLine(line);
        if (fields.size() <= static_cast<size_t>(COL_STREAMS)) continue;   // malformed row
        if (!isNumeric(fields[COL_STREAMS])) continue;                    // bad stream value

        titles[count]  = fields[COL_TRACK_NAME];
        artists[count] = fields[COL_ARTIST_NAME];
        years[count]   = std::stoi(fields[COL_RELEASED_YEAR]);
        streams[count] = std::stoll(fields[COL_STREAMS]);
        count++;
    }
    return count;
}

#endif // DATASET_LOADER_H
