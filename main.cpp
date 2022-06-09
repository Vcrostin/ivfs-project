#include <iostream>
#include "ivfs.h"

int main() {
    TestTask::IVFS ivfs;
    std::string fileName = "/new_dir/another_dir/new_file";
    auto file = ivfs.Create(fileName);
    TestTask::File *ptr = ivfs.Open(fileName);
    if (ptr != nullptr) {
        std::cerr << "Not expected Open" << "\n";
    }
    if (file != nullptr) {
        std::cerr << "Expected Create" << "\n";
    }
    int numBytes = ivfs.Write(file, "SOME USEFUL INFORMATION", 11);
    if (numBytes != 11) {
        std::cerr << "Not expected Write" << "\n";
    }
    ivfs.Close(file);
    auto file2 = ivfs.Open(fileName);
    if (file != file2) {
        std::cerr << "Not expected Equals" << "\n";
    }
    std::string res;
    ivfs.Read(file2, std::back_inserter(res), 11);
    if (res != "SOME USEFUL") {
        std::cerr << "Expected \"SOME USEFUL\" got " << res << "\n";
    }
    return 0;
}
