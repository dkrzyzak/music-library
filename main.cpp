#include "main.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// wyjątki
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

    // konstruktor kopiujący
    Song(const Song &s1) {
        Artist = s1.Artist;
        Name = s1.Name;
    }

    string GetSongName() {
        return Name;
    }

    void SetSongName(string name) {
        Name = name;
    }

    string GetArtist() {
        return Artist;
    }

    void SetArtist(string artist) {
        Artist = artist;
    }
};

// klasa abstrakcyjna
class AbstractAlbum {
    // czysto wirtualne metody
    virtual void Release() = 0;
    virtual void PrintTracklist() = 0;
};

// dziedziczenie
class Album : AbstractAlbum {
   private:
    string Name;
    string Artist;
    int ReleaseYear;
    bool Released;
    // wektory
    vector<Song> Tracklist;

   public:
    // konstruktor domyślny
    Album() {}

    Album(string name, string artist, int year) {
        Name = name;
        Artist = artist;
        ReleaseYear = year;
        Released = false;
    }

    // destruktor
    ~Album() {
        cout << "Usunięto z pamięci album " << GetFullName() << endl;
    }

    // przeciążenie operatora +
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
        // iteratory
        vector<Song>::iterator itr;

        // pętla zakresowa
        // for (auto s : Tracklist) {
        //     cout << s.GetSongName() << endl;
        // }

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
    Song s3 = s2;
    s3.SetSongName("Waste");
    a1.AddSong(s1);
    a1 + s2;
    a1 + s3;
    a1.PrintTracklist();
    a1.Release();

    Album a2 = Album("Dobry album", "Wykonawca 1", 2024);
    Song sa2 = Song("Wykonawca 2", "jakiś tytuł");
    a2.AddSong(sa2);

    try {
        a2.Release();
    } catch (YearException &e) {
        cout << "Złapano błąd: " << e.message() << endl;
    }

    return 0;
}
