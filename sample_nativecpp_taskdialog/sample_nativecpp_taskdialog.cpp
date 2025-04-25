// sample_nativecpp_taskdialog.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
  name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
  processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


int main()
{
   TASKDIALOG_BUTTON buttons[] = {
       { 1001, L"オプション A\n説明 A" },
       { 1002, L"オプション B\n説明 B" }
   };

   TASKDIALOGCONFIG config = { };
   config.cbSize = sizeof(config);
   config.hwndParent = nullptr;
   config.hInstance = GetModuleHandle(nullptr); // 現在の実行ファイルの hInstance を取得
   config.dwFlags = TDF_USE_COMMAND_LINKS | TDF_ALLOW_DIALOG_CANCELLATION;
   config.pszWindowTitle = L"タスク ダイアログのサンプル";
   config.pszMainInstruction = L"操作を選択してください";
   config.pszContent = L"以下のオプションから選択できます。";
   config.cButtons = ARRAYSIZE(buttons);
   config.pButtons = buttons;
   config.nDefaultButton = 1001;
   config.pszVerificationText = L"次回からこのダイアログを表示しない";

   int nButton = 0;
   BOOL bVerificationChecked = FALSE;

   HRESULT hr = TaskDialogIndirect(&config, &nButton, nullptr, &bVerificationChecked);
   if (SUCCEEDED(hr)) {
       // ユーザーの選択に応じた処理
       if (nButton == 1001) {
           MessageBox(nullptr, L"オプション A が選択されました。", L"結果", MB_OK);
       }
       else if (nButton == 1002) {
           MessageBox(nullptr, L"オプション B が選択されました。", L"結果", MB_OK);
       }
       else {
           MessageBox(nullptr, L"キャンセルされました。", L"結果", MB_OK);
       }

       // 検証チェック ボックスの状態
       if (bVerificationChecked) {
           MessageBox(nullptr, L"次回からこのダイアログを表示しないがチェックされました。", L"確認", MB_OK);
       }
   }
   else {
       MessageBox(nullptr, L"タスク ダイアログの表示に失敗しました。", L"エラー", MB_ICONERROR);
   }
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
