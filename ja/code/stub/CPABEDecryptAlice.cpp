#include <iostream>
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

int loadCPABE_Key(const std::string& keyfilename, std::string& key) {

    std::ifstream infile_key(keyfilename);
    if(!infile_key){
        std::cerr << "Error: Could not open file " << keyfilename << "\n";
        return 1;
    }

    std::getline(infile_key, key);
    infile_key.close();

    return 0;

}

int loadCPABE_CipherText(const std::string& ctfilename, std::string& ct) {

    std::ifstream infile_ct(ctfilename);
    if(!infile_ct){
        std::cerr << "Error: Could not open file " << ctfilename << "\n";
        return 1;
    }

    std::getline(infile_ct, ct);
    infile_ct.close();

    return 0;

}

int decryptionCPABE(const std::string& mpkfilename, const std::string& key, const std::string& ciphertext, const std::string& decfilename) {

    std::string mpkCP;
    loadCPABE_MPK(mpkfilename,mpkCP);

    InitializeOpenABE();

    OpenABECryptoContext cpabe("CP-ABE");

    cpabe.importPublicParams(mpkCP);

    cpabe.importUserKey("key0",key);

    std::string dt;
    cpabe.decrypt("key0",ciphertext,dt);

    std::ofstream outfile_dt(decfilename);
    if(!outfile_dt){
        std::cerr << "Error: Could not open file " << decfilename << "\n";
        return 1;
    }
    outfile_dt << dt << "\n";
    outfile_dt.close();

    return 0;
    
}


int main() {

    std::string CPmasterpublic = "example_CP_public_parameters";

    //暗号化メッセージファイルciphertext1.datを読み込み、鍵ファイルalice.keyを読み込み、暗号化メッセージを復号し、復号したデータをファイル名dextext_alice.datとして出力
    //-------------------
    //--ここに復号をするコードを書いてください
    //-------------------


    //動作確認用
    std::string dttext;
    std::ifstream infile_dt(decrypted_filename);
    if(!infile_dt){
        std::cerr << "Error: Could not open file " << decrypted_filename << "\n";
        return 1;
    }
    std::getline(infile_dt, dttext);
    if(dttext=="Hello, this is user test for OpenABE."){
        std::cout << "復号Dave：正常終了\n";
        return 0;  // 正常終了
    }
    else{
        std::cout << "復号Dave：エラー終了\n";
        return 1;  // エラー終了
    }
        
}
