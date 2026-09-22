#ifndef DATASET_LOADER_H
#define DATASET_LOADER_H

#include <fstream>
#include <string>
#include <vector>

const std::string DATASET_PATH = "data/spotify-2023.csv";

const int COL_TRACK_NAME = 0;
const int COL_ARTIST_NAME = 1;
const int COL_RELEASED_YEAR = 3;
const int COL_STREAMS = 8;

inline std::vector<std::string> parseCsvLine(const std::string &line) {
    std::vector<std::string> fields;
    std::string current;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        if (c == '"') {
            if (insideQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                current += '"';
                i++;
            } else {
                insideQuotes = !insideQuotes;
            }
        } else if (c == ',' && !insideQuotes) {
            fields.push_back(current);
            current.clear();
        } else if (c != '\r') {
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}

inline bool isNumeric(const std::string &text) {
    if (text.empty()) return false;
    for (char c : text) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

inline int loadSpotifyRecords(const std::string &path,
                              std::string titles[], std::string artists[],
                              int years[], long long streams[], int maxRecords) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return -1;
    }

    std::string line;
    std::getline(file, line);

    int count = 0;
    while (count < maxRecords && std::getline(file, line)) {
        std::vector<std::string> fields = parseCsvLine(line);
        if (fields.size() <= static_cast<size_t>(COL_STREAMS)) continue;
        if (!isNumeric(fields[COL_STREAMS])) continue;

        titles[count]  = fields[COL_TRACK_NAME];
        artists[count] = fields[COL_ARTIST_NAME];
        years[count]   = std::stoi(fields[COL_RELEASED_YEAR]);
        streams[count] = std::stoll(fields[COL_STREAMS]);
        count++;
    }
    return count;
}

#endif
