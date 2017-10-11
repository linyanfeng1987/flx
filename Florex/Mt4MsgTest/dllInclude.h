#pragma once

#ifdef DLL_MT4MSG_EXPORTS

#define MT4_EXPFUNC __declspec(dllexport)

#else

#define MT4_EXPFUNC __declspec(dllimport)

#endif

MT4_EXPFUNC wchar_t* __stdcall beat(wchar_t* strInfo);
MT4_EXPFUNC wchar_t* __stdcall setHisValue(wchar_t* strInfo);
MT4_EXPFUNC wchar_t* __stdcall setCurValue(wchar_t* strInfo);