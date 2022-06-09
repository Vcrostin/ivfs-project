//
// Created by brostin on 09.06.22.
//

#pragma once

#include <unordered_map>
#include <map>
#include <utility>
#include <cstring>
#include <iterator>
#include "utils.h"

namespace TestTask {
    struct File {
        bool isDirectory;
    private:
        bool isWriteOpen;
        bool isReadOpen;
    public:

        inline bool IsReadOpen() const {
            return isReadOpen;
        }

        inline bool IsWriteOpen() const {
            return isWriteOpen;
        }

        void SetWrite() {
            isWriteOpen = true;
            isReadOpen = false;
        }

        void SetRead() {
            isReadOpen = true;
            isWriteOpen = false;
        }

        void Close() {
            isReadOpen = false;
            isWriteOpen = false;
        }

        std::pair<size_t, std::string> Read(size_t maxSize) {
            if (isReadOpen && !isDirectory) {
                std::string res;
                for (const auto &[key, value]: contents) {
                    res += value.substr(0, maxSize - res.size());
                    if (res.size() == maxSize)
                        break;
                }
                return {res.size(), res};

            }
            return {0, ""};
        }

        size_t Write(std::string_view stringView) {
            if (isWriteOpen && !isDirectory) {
                contents[contents.size()] = stringView;
                return stringView.size();
            }
            return 0;
        }

        std::unordered_map<std::string, File *> children;
        std::map<size_t, std::string> contents;

        explicit File(bool isDirectory = false) : isDirectory(isDirectory), isWriteOpen(false), isReadOpen(false) {
        }
    };

    struct IVFS {
        File *Open(std::string_view fileName) {
            File *cur = FindFile(fileName);
            if (cur == nullptr) {
                return nullptr;
            }
            if (cur->IsWriteOpen())
                return nullptr;
            cur->SetRead();
            return cur;
        }

        File *Create(std::string_view fileName) {
            File *createdFile = CreateFile(fileName);
            if (createdFile == nullptr) {
                return nullptr;
            }
            if (createdFile->IsReadOpen()) {
                return nullptr;
            }
            createdFile->SetWrite();
            return createdFile;
        }

        size_t Read(File *f, std::back_insert_iterator<std::string>&& backInserterString, size_t len) {
            auto pr = f->Read(len);
            if (pr.first != 0) {
                for (auto s : pr.second) {
                    backInserterString = s;
                }
            }
            return pr.first;
        }

        size_t Write(File *f, std::string_view str, size_t len) {
            return f->Write(str.substr(0, len));
        }

        void Close(File *f) {
            f->Close();
        }

    private:
        File *FindFile(std::string_view fileName) {
            auto splittedStr = StringSplit(fileName, '/');
            if (splittedStr.empty())
                return nullptr;
            File *cur = root;
            for (auto &partPath: splittedStr) {
                if (cur->children.contains(std::string(partPath))) {
                    cur = cur->children[std::string(partPath)];
                } else {
                    return nullptr;
                }
            }
            if (cur->isDirectory) {
                return nullptr;
            }
            return cur;
        }

        File *CreateFile(std::string_view fileName) {
            auto splittedStr = StringSplit(fileName, '/');
            if (splittedStr.empty())
                return nullptr;
            File *cur = root;
            for (size_t i = 0; i < splittedStr.size(); ++i) {
                if (cur->children.contains(std::string(splittedStr[i]))) {
                    cur = cur->children[std::string(splittedStr[i])];
                } else {
                    File *newFile;
                    if (i == splittedStr.size() - 1) {
                        newFile = new File(false);
                    } else {
                        newFile = new File(true);
                    }
                    cur->children[std::string(splittedStr[i])] = newFile;
                    cur = newFile;
                }
            }
            if (cur->isDirectory) {
                return nullptr;
            }
            return cur;
        }

        File *root = new File(true);
    };

}


