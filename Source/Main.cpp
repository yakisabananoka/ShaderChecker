#include <Windows.h>
#include "System/Application.h"

//エントリーポイント
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//アプリケーションを作成して実行
	Application application;
	return application.Run() ? 0 : -1;
}