#ifndef MUSIC_H
#define MUSIC_H
#include <iostream>
#include <QString>
using namespace std ;

class Music
{
public:
    QString P_name ;
    QString P_song_path ;
    Music( QString name , QString song_path);
};

#endif // MUSIC_H
