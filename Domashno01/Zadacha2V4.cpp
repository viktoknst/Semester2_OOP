#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996) 

constexpr int song_length = 64;
constexpr int content_length = 256;
constexpr int number_of_songs = 30;

enum class Genre : char {
    Rock = 'r',
    Pop = 'p',
    HipHop = 'h',
    Electronic = 'e',
    Jazz = 'j',
    Unknown = 0,
};

class Song {
private:
    char name[song_length + 1] = ""; 
    int duration = 0; 
    Genre genre = Genre::Unknown; 
    unsigned char content[content_length + 1] = "";
    int contentSize = 0; 

public:
    Song() = default;

    Song(const char* name, int duration, Genre genre, const unsigned char* content, int contentSize) : duration(duration), genre(genre), contentSize(contentSize) {
        strcpy(this->name, name);
        memcpy(this->content, content, contentSize);
    }

    const char* getName() const { return name; }
    int getDuration() const { return duration; }
    Genre getGenre() const { return genre; }
    const unsigned char* getContent() const { return content; }
    int getContentSize() const { return contentSize; }

    void modifyContent(int k) {
        for (int i = contentSize - k + 1; i >= 0; i -= k) {
            content[i] = '1';
        }
    }

    void mix(const Song& other) {
        int minLength = std::min(contentSize, other.contentSize);
        for (int i = 0; i < minLength; i++) {
            if (content[i] != other.content[i]) {
                content[i] = '1';
            }
            else {
                content[i] = '0';
            }
        }
    }

    void saveToFile(const char* filename) {
        std::ofstream ofs(filename, std::ios::out | std::ios::binary);
        if (!ofs.is_open()) {
            std::cout << "Problem with locating file" << std::endl;
            ofs.close();
            return;
        }

        ofs.write((const char*)&content, contentSize);
        ofs.close();
        std::cout << "Song successfully saved to file: " << filename << std::endl;
    }
};

class Playlist {
private:
    Song songs[number_of_songs]; 
    int count = 0;

public:
    Playlist() {}

    void add(const char* name, int hours, int minutes, int seconds, const char* genreStr, const char* filename) {
        int duration = hours * 3600 + minutes * 60 + seconds;

        Genre genre = Genre::Unknown;

        if (strlen(genreStr) == 1) {
            switch (*genreStr) {
            case 'r': genre = Genre::Rock; break;
            case 'p': genre = Genre::Pop; break;
            case 'h': genre = Genre::HipHop; break;
            case 'e': genre = Genre::Electronic; break;
            case 'j': genre = Genre::Jazz; break;
            default: genre = Genre::Unknown; break;
            }
        }

        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        if (!ifs.is_open()) {
            std::cout << "Couldn't read from file" << std::endl;
            return;
        }

        ifs.seekg(0, std::ios::end);
        int contentSize = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        unsigned char* content = new unsigned char[contentSize];
        ifs.read(reinterpret_cast<char*>(content), contentSize);
        ifs.close();

        Song newSong(name, duration, genre, content, contentSize);

        std::ofstream ofs(filename, std::ios::out | std::ios::binary | std::ios::app); // Open file in append mode
        if (!ofs.is_open()) {
            std::cout << "Couldn't open file for writing" << std::endl;
            delete[] content; // Clean up dynamically allocated memory
            return;
        }

        ofs.write(reinterpret_cast<const char*>(content), contentSize); // Write song content to file
        ofs.close(); // Close the file

        songs[count++] = newSong; // Add the new song to the playlist
        std::cout << "Song \"" << name << "\" successfully added to the playlist and saved to file." << std::endl;
    }

    void print() const {
        for (int i = 0; i < count; i++) {
            int hours = songs[i].getDuration() / 3600;
            int minutes = (songs[i].getDuration() % 3600) / 60;
            int seconds = songs[i].getDuration() % 60;
            std::cout << songs[i].getName() << ", " << hours << ":" << minutes << ":" << seconds << ", ";

            switch (songs[i].getGenre()) {
            case Genre::Rock: std::cout << "Rock"; break;
            case Genre::Pop: std::cout << "Pop"; break;
            case Genre::HipHop: std::cout << "Hip-hop"; break;
            case Genre::Electronic: std::cout << "Electronic"; break;
            case Genre::Jazz: std::cout << "Jazz"; break;
            default: std::cout << "Unknown"; break;
            }

            std::cout << std::endl;
        }
    }

    void printSong(const int songId) const {
        int hours = songs[songId].getDuration() / 3600;
        int minutes = (songs[songId].getDuration() % 3600) / 60;
        int seconds = songs[songId].getDuration() % 60;
        std::cout << songs[songId].getName() << ", " << hours << ":" << minutes << ":" << seconds << ", ";

        switch (songs[songId].getGenre()) {
        case Genre::Rock: std::cout << "Rock"; break;
        case Genre::Pop: std::cout << "Pop"; break;
        case Genre::HipHop: std::cout << "Hip-hop"; break;
        case Genre::Electronic: std::cout << "Electronic"; break;
        case Genre::Jazz: std::cout << "Jazz"; break;
        default: std::cout << "Unknown"; break;
        }

        std::cout << std::endl;
    }

    void find(const char* name) const {
        for (int i = 0; i < count; i++) {
            if (strcmp(songs[i].getName(), name) == 0) {
                printSong(i);
                return;
            }
        }
        std::cout << "Song with name \"" << name << "\" not found." << std::endl;
    }

    void findGenre(char genre) const {
        for (int i = 0; i < count; i++) {
            if (songs[i].getGenre() == (Genre)genre) {
                printSong(i);
            }
        }
        std::cout << "Song with genre \"" << genre << "\" not found." << std::endl;
    }

    void sortByDuration() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (songs[i].getDuration() > songs[j].getDuration()) {
                    std::swap(songs[i], songs[j]);
                }
            }
        }
    }

    void sortByName() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (strcmp(songs[i].getName(), songs[j].getName()) > 0) {
                    std::swap(songs[i], songs[j]);
                }
            }
        }
    }

    void modifySong(const char* name, int k) {
        for (int i = 0; i < count; ++i) {
            if (strcmp(songs[i].getName(), name) == 0) {
                songs[i].modifyContent(k);
                std::cout << "Song \"" << name << "\" modified successfully." << std::endl;
                return;
            }
        }
        std::cout << "Song with name \"" << name << "\" not found." << std::endl;
    }

    void mix(const char* name1, const char* name2) {
        Song song1;
        Song song2;

        for (int i = 0; i < count; ++i) {
            if (strcmp(songs[i].getName(), name1) == 0) {
                song1 = songs[i];
            }
            if (strcmp(songs[i].getName(), name2) == 0) {
                song2 = songs[i];
            }
        }

        song1.mix(song2);
        std::cout << "Songs \"" << name1 << "\" and \"" << name2 << "\" mixed successfully." << std::endl;

    }

    void save(const char* name, const char* filename) const {
        for (int i = 0; i < count; ++i) {
            if (strcmp(songs[i].getName(), name) == 0) {
                std::ofstream ofs(filename, std::ios::out | std::ios::binary);

                if (!ofs.is_open()) {
                    std::cout << "Couldn't open file" << std::endl;
                    ofs.close();
                    return;
                }

                ofs.write((char*)songs[i].getContent(), songs[i].getContentSize());
                ofs.close();
                std::cout << "Song successfully saved to file: " << filename << std::endl;
            }
        }
        std::cout << "Song with name \"" << name << "\" not found." << std::endl;
    }
};

int main() {
    unsigned char content1[] = "V"; 
    unsigned char content2[] = "Ua";

    Song song1("song11", 190, Genre::Electronic, content1, sizeof(content1) - 1);
    song1.saveToFile("song1.dat");

    Song song2("song12", 191, Genre::Pop, content2, sizeof(content2) - 1);
    song2.saveToFile("song2.dat");

    Playlist p;
    p.add("Song 2", 0, 1, 55, "r", "song2.dat");
    p.add("Song 1", 0, 1, 5, "p", "song1.dat");

    std::cout << "Songs in the playlist:" << std::endl;
    p.print();

    p.sortByName();
    std::cout << "\nSorted songs by name:" << std::endl;
    p.print();

    std::cout << "\nFinding a song by name:" << std::endl;
    p.find("Song 1");

    std::cout << "\nFinding songs by genre:" << std::endl;
    p.findGenre('p');

    p.modifySong("Song 1", 3);
    std::cout << "\nModified song:" << std::endl;
    p.print();

    p.mix("Song 1", "Song 2");

    p.save("Song 1", "song3.dat");

    return 0;
}
