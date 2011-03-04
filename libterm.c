#include <windows.h>

static HANDLE	_in;

initterm() {
	if (_in)
		return 0;
	_in=CreateFile("conin$",GENERIC_READ,FILE_SHARE_READ,
		0,OPEN_EXISTING,FILE_FLAG_NO_BUFFERING,0);
	SetStdHandle(STD_INPUT_HANDLE,_in);
	return 1;
}

tgetsc() {
	INPUT_RECORD	in;
	DWORD		ign;
	initterm();
	while (!ReadConsoleInput(_in,&in,1,&ign)
	  || in.EventType!=KEY_EVENT
	  || !in.Event.KeyEvent.bKeyDown
	  || !in.Event.KeyEvent.uChar.AsciiChar);
	return in.Event.KeyEvent.uChar.AsciiChar;
}
