#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct YearException : public exception {
    const string message() const throw() {
        return "Nie można wydać. Data wydania nie została jeszcze osiągnieta.";
    }
};
class Song {
   private:
    string Artist;
    string Name;

   public:
    Song(string artist, string name) {
        Artist = artist;
        Name = name;
    }

    string GetSongName() {
        return Name;
    }

    string GetArtist() {
        return Artist;
    }
};

class AbstractAlbum {
    virtual void Release() = 0;
};

class Album : AbstractAlbum {
   private:
    string Name;
    string Artist;
    int ReleaseYear;
    bool Released;
    vector<Song> Tracklist;

   public:
    Album() {}

    Album(string name, string artist, int year) {
        Name = name;
        Artist = artist;
        ReleaseYear = year;
        Released = false;
    }

    ~Album() {
        cout << "Usunięto z pamięci album " << GetFullName() << endl;
    }

    void operator+(Song &s) {
        AddSong(s);
    }

    void SetName(string name) {
        Name = name;
    }

    void SetArtist(string artist) {
        Artist = artist;
    }

    void SetReleaseYear(int year) {
        ReleaseYear = year;
    }

    string GetName() {
        return Name;
    }

    string GetArtist() {
        return Artist;
    }

    int GetReleaseYear() {
        return ReleaseYear;
    }

    string GetFullName() {
        return Artist + " - " + Name + " (" + to_string(ReleaseYear) + ")";
    }

    void AddSong(Song &song) {
        if (song.GetArtist() != GetArtist()) {
            cout << "Nie można do albumu wykonawcy " << GetArtist() << " dodać piosenki wykonawcy " << song.GetArtist() << endl;
            return;
        }

        Tracklist.push_back(song);
        cout << "Dodano piosenkę " << song.GetArtist() << " - " << song.GetSongName() << endl;
    }

    void PrintTracklist() {
        vector<Song>::iterator itr;

        cout << "\nTracklista albumu " << GetFullName() << ": " << endl;

        for (itr = Tracklist.begin(); itr < Tracklist.end(); itr++) {
            int idx = distance(Tracklist.begin(), itr);
            cout << "(" << idx + 1 << ") " << itr->GetSongName() << endl;
        }

        cout << endl;
    }

    void Release() {
        if (Released) {
            cout << "Ten album został już wydany." << endl;
            return;
        }

        if (ReleaseYear > 2021) {
            throw YearException();
        }

        Released = true;
        cout << GetFullName() << " został pomyślnie wydany!" << endl;
    }
};

int main() {
    Album a1 = Album("Science Fiction", "Brand New", 2017);
    Song s1 = Song("Brand New", "Lit Me Up");
    Song s2 = Song("Brand New", "Cant Get It Out");
    a1.AddSong(s1);
    a1 + s2;
    a1.PrintTracklist();
    a1.Release();

    Album a2 = Album("Dobry album", "lil bażant", 2024);
    Song sa2 = Song("ktoś inny", "jakiś tytuł");
    a2.AddSong(sa2);

    try {
        a2.Release();
    } catch (YearException &e) {
        cout << "Złapano błąd: " << e.message() << endl;
    }

    return 0;
}
