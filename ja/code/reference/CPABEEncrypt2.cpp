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

int encryptionCPABE(const std::string& mpkfilename, const std::string& policy, const std::string& plaintext, const std::string& ctfilename) {

    std::string mpkCP;
    loadCPABE_MPK(mpkfilename,mpkCP);

    InitializeOpenABE();

    OpenABECryptoContext cpabe("CP-ABE");

    cpabe.importPublicParams(mpkCP);

    std::string ct;
    cpabe.encrypt(policy,plaintext,ct);

    std::ofstream outfile_ct(ctfilename);
    if(!outfile_ct){
        std::cerr << "Error: Could not open file " << ctfilename << "\n";
        return 1;
    }
    outfile_ct << ct << "\n";
    outfile_ct.close();

    return 0;
    
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

    //属性role_leaderを持つか属性role_staffを持ち、かつ、属性employ_contractを持つユーザだけが復号可能なように平文plaintextを暗号化し、暗号化したデータをファイル名ciphertext1.datとして出力
    std::string plaintext = "Hello, this is user test for OpenABE.";
    std::string ciphertext;
    std::string encrypted_filename = "ciphertext2.dat";
    std::string encryption_policy_2 = "(role_leader or role_staff) and employ_contract";
    encryptionCPABE(CPmasterpublic, encryption_policy_2, plaintext, encrypted_filename);

    //動作確認用
    std::uintmax_t size = getFileSize(encrypted_filename);
    if(size==1017){
        std::cout << "暗号化2：正常終了\n";
        return 0;  // 正常終了
    }
    else{
        std::cout << "暗号化2：エラー終了\n";
        return 1;  // エラー終了
    }
    
}