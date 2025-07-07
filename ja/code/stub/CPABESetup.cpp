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

int setupCPABE(const std::string& masterpublic, const std::string& mastersecret) {
    // -- スタブ関数 
    // 概要：CP-ABEでのセットアップを行う
    // 内容詳細：
    // - パラメータを生成する
    // - 引数で指定された文字列masterpublicをファイル名として公開パラメータをファイルにエクスポート
    // - 引数で指定された文字列mastersecretをファイル名としてマスターシークレットをファイルにエクスポートする
    // - セットアップが完了しエクスポートも完了したら0を返す
    // - ファイルが見つからないなどのエラーがあったら1を返す
    // 入力：
    //    masterpublic 公開パラメータファイル名
    //    mastersecret マスターシークレットファイル名
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
    
    setupCPABE(CPmasterpublic, CPmastersecret);
    
    //------------
    // 動作確認用
    //------------
    
    std::uintmax_t size1 = getFileSize(CPmasterpublic);
    if(size1==665 || size1==664){
        std::cout << "公開パラメータ生成：正常終了\n";
    }
    else{
        std::cout << "公開パラメータ生成：エラー終了\n";
        return 1;  // エラー終了
    }

    std::uintmax_t size2 = getFileSize(CPmastersecret);
    if(size2==201 || size2==200){
        std::cout << "マスターシークレット生成：正常終了\n";
        return 0;  // 正常終了
    }
    else{
        std::cout << "マスターシークレット生成：エラー終了\n";
        return 1;  // エラー終了
    }

    return 0;
}
