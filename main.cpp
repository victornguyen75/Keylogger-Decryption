#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Global constants
const std::string &SALT1 = "LM::TB::BB";
const std::string &SALT2 = "__:/__77";
const std::string &SALT3 = "line=wowC++";
const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Function prototypes
std::string DecryptB64 (std::string s);
std::string base64_decode(const std::string &s);

// This main function will accept a few arguments
int main(int argc, char *argv[]){
    if (argc != 3)
        return std::cout << "Program needs TWO arguments, input and output! " << std::endl, 2;

    std::string in  (argv[1]), out (argv[2]);

    // Input file manipulation
    std::ifstream Ifile (in);     // Input file
    if (!Ifile)                   // Does the file exist?
        return std::cout << "Cannot read input file '" << in << "'" << std::endl, 3;

    // Store the input file info into a string known as data
    std::string data;
    Ifile >> data;

    if (!Ifile)                  // If the file still has a problem after receiving input
        return std::cout << "Input file '" << in << "' corrupted!" << std::endl, 4;

    // Decrypt the file to a readable format
    data = DecryptB64(data);

    // Output file manipulation
    std::ofstream Ofile (out);   // Output File
    if (!Ofile)
        return std::cout << "Cannot write output file '" << out << "'" << std::endl, 5;

    Ofile << data;
    std::cout << "Decoding was successful" << std::endl;
    return 0;
}

// This function will decrypt the strings
// to be readable for the user.
std::string DecryptB64 (std::string s){
        s = s.erase (7, 1);
        s = s.erase (1, 1);
        s = base64_decode (s);
        s = s.substr (SALT2.length() + SALT3.length());
        s = s.substr (0, s.length() - SALT1.length());
        s = base64_decode (s);
        s = s.substr (0, s.length() - SALT1.length());
        s = s.erase (7, SALT3.length());
        s = base64_decode (s);
        s = s.substr (SALT1.length());
        s = s.substr (0, s.length() - SALT2.length() - SALT3.length());
        return s;
}

std::string base64_decode(const std::string &s){
    std::string ret;
    std::vector<int> vec(256, -1);
    for (int i = 0; i < 64; i++)
        vec [BASE64_CODES[i]] = i;
    int val = 0, bits = -8;
    for (const auto &c : s){
            if (vec[c] == -1) break;
            val = (val << 6) + vec[c];
            bits += 6;

            if (bits >= 0){
                    ret.push_back(char((val >> bits) & 0xFF));
                    bits -= 8;
            }
    }
    return ret;
}
