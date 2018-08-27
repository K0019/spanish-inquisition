#include <Windows.h>
#include "MusicManager.h"
#include <iostream>
#pragma comment( lib, "winmm.lib" )

std::vector<MLoaded> LoadedFiles;

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Mshutdown()
{
	mciSendCommand(MCI_ALL_DEVICE_ID, MCI_CLOSE,MCI_WAIT,NULL);
}
void MusicInit()
{
	MLoaded loaded;
	// mpegvideo is Audio for MP3 (*.mp3) [VOLUME WILL NOT WORK IS WAVEAUDIO IS USED (*.wav)!!]
	// volume is a string eg "0" - "100"
	// &loaded is a MLoaded Struct.
	MusicLoad("./MusicManager/01Heart.mp3", "mpegvideo", "001", "40", &loaded);
	LoadedFiles.push_back(loaded);
	MusicLoad("./MusicManager/02Alone.mp3", "mpegvideo", "002", "40", &loaded);
	LoadedFiles.push_back(loaded);
	MusicLoad("./MusicManager/03IfISeeYouAgain.mp3", "mpegvideo", "003", "40", &loaded);
	LoadedFiles.push_back(loaded);
	MusicLoad("./MusicManager/04NightTheme.mp3", "mpegvideo", "004", "40", &loaded);
	LoadedFiles.push_back(loaded);
	MusicLoad("./MusicManager/05RacingHeart.mp3", "mpegvideo", "005", "40", &loaded);
	LoadedFiles.push_back(loaded);
	MusicLoad("./MusicManager/06Delta(Remaster).mp3", "mpegvideo", "006", "40", &loaded);
	LoadedFiles.push_back(loaded);
	MusicLoad("./MusicManager/07FromUpHere.mp3", "mpegvideo", "007", "40", &loaded);
	LoadedFiles.push_back(loaded);
}
bool MusicLoad(std::string file, std::string type, std::string alias, std::string initalvolume, MLoaded* Returnfile)
{
	MCIERROR me;
	std::string buff;
	buff = "open \"" + file + "\" type " + type + " alias " + alias;
	me = mciSendString(s2ws(buff).c_str(), NULL, 0, NULL);
    if (me == 0)
    {
		Returnfile->status = 0;
		Returnfile->file = file;
		Returnfile->type = type;
		Returnfile->alias = alias;
		buff = "setaudio " + alias + " volume to " + initalvolume;
        me = mciSendString(s2ws(buff).c_str(), NULL, 0, NULL);
        return true;
    }
    else
    {
		(*Returnfile).status = me;
        return false;
    }
	
}
bool MusicPlay(std::string alias, std::string arguments)
{
	MCIERROR ME;
	std::string constructstring = "play ";
	constructstring += alias;
	constructstring += " " + arguments;
	ME = mciSendString(s2ws(constructstring).c_str(), NULL, 0, NULL);
	if (ME != 0)
		return false;
	else
		return true;
}
bool MusicStop(std::string alias)
{
	MCIERROR ME;
	std::string constructstring = "stop ";
	constructstring += alias;
	ME = mciSendString(s2ws(constructstring).c_str(), NULL, 0, NULL);
	if (ME != 0)
		return false;
	else
		return true;
}

void stopAllMusic()
{
	MusicStop("001");
	MusicStop("002");
	MusicStop("003");
	MusicStop("004");
	MusicStop("005");
	MusicStop("006");
	MusicStop("007");
}