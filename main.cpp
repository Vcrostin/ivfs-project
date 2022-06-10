#include <iostream>
#include "ivfs.h"

int main() {
    TestTask::IVFS ivfs;
    ivfs.LoadTree("json_file.txt");
    std::string res;
    std::string fileName = "/new_dir/another_dir/new_file";
    auto file = ivfs.Open(fileName);
//    TestTask::File *ptr = ivfs.Open(fileName);
//    if (ptr != nullptr) {
//        std::cerr << "Not expected Open" << "\n";
//    }
//    if (file != nullptr) {
//        std::cerr << "Expected Create" << "\n";
//    }
//    size_t numBytes = ivfs.Write(file, "SOME USEFUL INFORMATION", 11);
//    if (numBytes != 11) {
//        std::cerr << "Not expected Write" << "\n";
//    }
//    ivfs.Close(file);
//    auto file2 = ivfs.Open(fileName);
//    if (file != file2) {
//        std::cerr << "Not expected Equals" << "\n";
//    }
    ivfs.Read(file, std::back_inserter(res), 11);
    if (res != "SOME USEFUL") {
        std::cerr << "Expected \"SOME USEFUL\" got " << res << "\n";
    }
    //ivfs.SaveTree("json_file.txt");
    return 0;
}
