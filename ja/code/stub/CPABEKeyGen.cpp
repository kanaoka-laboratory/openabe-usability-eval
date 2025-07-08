#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cassert>
#include <openabe/openabe.h>
#include <openabe/zsymcrypto.h>

using namespace std;
using namespace oabe;
using namespace oabe::crypto;

int loadCPABE_MPK(const std::string& mpkfilename, std::string& mpk) {

    std::ifstream infile_mpk(mpkfilename);
    if(!infile_mpk){
        std::cerr << "Error: Could not open file " << mpkfilename << "\n";
        return 1;
    }

    std::getline(infile_mpk, mpk);
    infile_mpk.close();

    return 0;

}

int loadCPABE_MSK(const std::string& mskfilename, std::string& msk) {

    std::ifstream infile_msk(mskfilename);
    if(!infile_msk){
        std::cerr << "Error: Could not open file " << mskfilename << "\n";
        return 1;
    }

    std::getline(infile_msk, msk);
    infile_msk.close();

    return 0;
}


int keygenCPABE(const std::string& mpkfilename, const std::string& mskfilename, const std::string& keyfilename, const std::string& keyattribute) {

    // スタブ関数: 
    // 概要：CP-ABEでの鍵生成を行う
    // 内容詳細：
    // - 引数で指定された文字列mpkfilenameをファイル名として公開パラメータをインポート
    // - 引数で指定された文字列mskfilenameをファイル名としてマスターシークレットをインポート
    // - 引数で指定された文字列keyattributeをそのユーザが持つ属性情報として鍵生成を行う
    // - 作成された鍵を引数で指定された文字列keyfilenameをファイル名として鍵をエクスポート
    // - 鍵生成が完了しファイル出力も完了したら0を返す
    // - ファイルが見つからないなどのエラーがあったら1を返す
    // 入力：
    //    mpkfilename 公開パラメータファイル名
    //    mskfilename マスターシークレットファイル名
    //    keyfilename 鍵ファイル名
    //    keyattribute ユーザ属性情報
    // 出力：
    //    0 正常終了
    //    1 エラー
}

std::uintmax_t getFileSize(const std::string& filePath) {
    try {
        if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath)) {
            return std::filesystem::file_size(filePath);
        } else {
            std::cerr << "Error: File does not exist or is not a regular file.\n";
            return 0;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
        return 0;
    }
}

int main() {


    std::string CPmasterpublic = "example_CP_public_parameters";
    std::string CPmastersecret = "example_CP_master_secret";

    //
    //属性role_manager（部長）、employ_full（正社員）、 func_project_manager（プロジェクトマネージャ）、 location_hq、 proj_TeamA、years=15 を持つユーザaliceさんの鍵を作成し、その鍵をファイルalice.keyに出力
    //-------------------
    //--ここにaliceさんの鍵作成をするコードを書いてください
    //-------------------

    //属性 role_leader、employ_full, func_ junior_engineer、location_hq、location_branch、years=8、を持つユーザbobさんの鍵を作成し、その鍵をファイルbob.keyに出力
    std::string bob_key = "bob.key";
    std::string attribute_bob = "role_leader|employ_full|func_junior_engineer|location_hq|location_branch|years=8";
    keygenCPABE(CPmasterpublic, CPmastersecret, bob_key, attribute_bob);

    //属性 role_staff、employ_contract、location_branch、proj_TeamA、years=2、を持つユーザcarolさんの鍵を作成し、その鍵をファイルcarol.keyに出力
    std::string carol_key = "carol.key";
    std::string attribute_carol = "role_staff|employ_contract|location_branch|proj_TeamA|years=2";
    keygenCPABE(CPmasterpublic, CPmastersecret, carol_key, attribute_carol);

    //属性 role_staff、employ_full、location_hq、years=1、を持つユーザdaveさんの鍵を作成し、その鍵をファイルdave.keyに出力
    //-------------------
    //--ここにdaveさんの鍵作成をするコードを書いてください
    //-------------------
    std::string dave_key = "dave.key";
    std::string attribute_dave = "role_staff|employ_full|location_hq|years=1";
    keygenCPABE(CPmasterpublic, CPmastersecret, dave_key, attribute_dave);



    // 動作確認用
    std::uintmax_t sizeAlice = getFileSize(alice_key);
    std::uintmax_t sizeBob = getFileSize(bob_key);
    std::uintmax_t sizeCarol = getFileSize(carol_key);
    std::uintmax_t sizeDave = getFileSize(dave_key);
    if(sizeAlice==3241){
        std::cout << "Alice鍵生成：正常終了\n";
    }
    else{
        std::cout << "Alice鍵生成：エラー終了\n";
        return 1;  // エラー終了
    }
    if(sizeBob==3249){
        std::cout << "Bob鍵生成：正常終了\n";
    }
    else{
        std::cout << "Bob鍵生成：エラー終了\n";
        return 1;  // エラー終了
    }
    if(sizeCarol==3149){
        std::cout << "Carol鍵生成：正常終了\n";
    }
    else{
        std::cout << "Carol鍵生成：エラー終了\n";
        return 1;  // エラー終了
    }
    if(sizeDave==3041){
        std::cout << "Dave鍵生成：正常終了\n";
        return 0;  // 正常終了
    }
    else{
        std::cout << "Dave鍵生成：エラー終了\n";
        return 1;  // エラー終了
    }


    return 0;
}
