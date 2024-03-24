#include <iostream>
#include <fstream>
#pragma warning (disable: 4996) 

constexpr int song_length = 64;
constexpr int content_length = 256;

enum class Genre : char {
    Rock = 'r',
    Pop = 'p',
    HipHop = 'h',
    Electronic = 'e',
    Jazz = 'j',
    Unknown = 0,
    RockPop,
    RockHipHop,
    RockElectornic,
    RockJazz,
    PopHipHop,
    PopElectronic,
    PopJazz,
    HipHopElectronic, 
    HipHopJazz,
    ElectronicJazz,
};

class Song {
private:
    char name[song_length + 1] = ""; // 64 characters + null terminator
    int duration = 0; // in seconds
    Genre genre = Genre::Unknown; // 'r' - rock, 'p' - pop, 'h' - hip-hop, 'e' - electronic, 'j' - jazz
    char content[content_length + 1] = ""; // song content
    int contentSize = 0; // size of content

public:
    // constructor
    Song() = default;

    Song(const char* name, int duration, Genre genre, const char* content, int contentSize) : duration(duration), genre(genre), contentSize(contentSize) {
        strcpy(this->name, name);
        strcpy(this->content, content);
        //memcpy(this->content, content, contentSize);
    }

    // destructor
    ~Song() { }

    // methods to get song data
    const char* getName() const { return name; }
    int getDuration() const { return duration; }
    Genre getGenre() const { return genre; }
    const char* getContent() const { return content; }
    int getContentSize() const { return contentSize; }

    // method to modify song content
    void modifyContent(int k) {
        for (int i = contentSize - k + 1; i >= 0; i -= k) {
            content[i] = '1'; 
        }
    }

    // method to mix with another song
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

    // method to save song content to binary file
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
    Song* songs[30]; // maximum 30 songs
    int count; // number of added songs

public:
    // constructor
    Playlist() : count(0) {}

    // method to add a song to the playlist
    void add(const char* name, int hours, int minutes, int seconds, const char* genreStr, const char* filename) {
        int duration = hours * 3600 + minutes * 60 + seconds;
        
        Genre genre = Genre::Unknown;

        // !!!!!!!!! add multiple genres
        if (strlen(genreStr) == 1) {
            switch ((int)*genreStr) {
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
            ifs.close();
            return;
        }

        ifs.seekg(0, std::ios::end);
        int contentSize = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        char* content = new char[contentSize];
        ifs.read((char*)&content, contentSize);
        ifs.close();

        songs[count] = new Song(name, duration, genre, content, contentSize);
        count++;
        std::cout << "Song \"" << name << "\" successfully added to the playlist." << std::endl;
        //delete[] content;
    }

    // method to print songs in the playlist
    void print() const {
        for (int i = 0; i < count; i++) {
            int hours = songs[i]->getDuration() / 3600;
            int minutes = (songs[i]->getDuration() % 3600) / 60;
            int seconds = songs[i]->getDuration() % 60;
            std::cout << songs[i]->getName() << ", " << hours << ":" << minutes << ":" << seconds << ", ";
            
            switch (songs[i]->getGenre()) {
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
        int hours = songs[songId]->getDuration() / 3600;
        int minutes = (songs[songId]->getDuration() % 3600) / 60;
        int seconds = songs[songId]->getDuration() % 60;
        std::cout << songs[songId]->getName() << ", " << hours << ":" << minutes << ":" << seconds << ", ";

        switch (songs[songId]->getGenre()) {
            case Genre::Rock: std::cout << "Rock"; break;
            case Genre::Pop: std::cout << "Pop"; break;
            case Genre::HipHop: std::cout << "Hip-hop"; break;
            case Genre::Electronic: std::cout << "Electronic"; break;
            case Genre::Jazz: std::cout << "Jazz"; break;
            default: std::cout << "Unknown"; break;
        }

        std::cout << std::endl;
    }
    

    // method to find a song by name
    void find(const char* name) const {
        for (int i = 0; i < count; i++) {
            if (strcmp(songs[i]->getName(), name) == 0) {
                printSong(i);
                return;
            }
        }
        std::cout << "Song with name \"" << name << "\" not found." << std::endl;
    }

    // method to find songs by genre
    void findGenre(char genre) const {
        for (int i = 0; i < count; i++) {
            if (songs[i]->getGenre() == (Genre)genre) {
                printSong(i);
            }
        }
        std::cout << "Song with genre \"" << genre << "\" not found." << std::endl;
    }

    // method to sort songs by duration
    void sortByDuration() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (songs[i]->getDuration() > songs[j]->getDuration()) {
                    std::swap(songs[i], songs[j]);
                }
            }
        }
    }

    // method to sort songs by name
    void sortByName() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = i + 1; j < count; ++j) {
                if (strcmp(songs[i]->getName(), songs[j]->getName()) > 0) {
                    std::swap(songs[i], songs[j]);
                }
            }
        }
    }

    // method to modify a song by name
    void modifySong(const char* name, int k) {
        for (int i = 0; i < count; ++i) {
            if (strcmp(songs[i]->getName(), name) == 0) {
                songs[i]->modifyContent(k);
                std::cout << "Song \"" << name << "\" modified successfully." << std::endl;
                return;
            }
        }
        std::cout << "Song with name \"" << name << "\" not found." << std::endl;
    }

    // method to mix two songs
    void mix(const char* name1, const char* name2) {
        Song* song1 = nullptr;
        Song* song2 = nullptr;
        
        for (int i = 0; i < count; ++i) {
            if (strcmp(songs[i]->getName(), name1) == 0) {
                song1 = songs[i];
            }
            if (strcmp(songs[i]->getName(), name2) == 0) {
                song2 = songs[i];
            }
        }
        
        if (song1 != nullptr && song2 != nullptr) {
            song1->mix(*song2);
            std::cout << "Songs \"" << name1 << "\" and \"" << name2 << "\" mixed successfully." << std::endl;
        }
        else {
            std::cout << "One or more songs not found." << std::endl;
        }
    }

    // method to save a song to a binary file
    void save(const char* name, const char* filename) const {
        for (int i = 0; i < count; ++i) {
            if (strcmp(songs[i]->getName(), name) == 0) {
                std::ofstream ofs(filename, std::ios::out | std::ios::binary);

                if (!ofs.is_open()) {
                    std::cout << "Couldn't open file" << std::endl;
                    ofs.close();
                    return;
                }

                ofs.write(songs[i]->getContent(), songs[i]->getContentSize());
                ofs.close();
                std::cout << "Song successfully saved to file: " << filename << std::endl;  
            }
        }
        std::cout << "Song with name \"" << name << "\" not found." << std::endl;
    }
};

int main() {
    Song song1("aaaaa", 75, 'r', "010110", 6);

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