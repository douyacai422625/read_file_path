#include <iostream>
#include <memory.h>
#include <dirent.h>
#include <vector>
using namespace std;

vector<string> getFilesList(string dir);

int main()
{
    string dir = "/home/pxierra/文档/实验数据/pic";
    vector<string>allFileName = getFilesList(dir);
    for (size_t i = 0; i < allFileName.size(); i++)
    {
        cout << allFileName[i] << endl;
    }
    return 0;
}

std::vector<std::string> getFilesList(std::string dirpath){
    DIR *dir = opendir(dirpath.c_str());
    if (dir == NULL)
    {
        std::cout << "opendir error" << std::endl;
    }

    std::vector<std::string> allPath;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR){//It's dir
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            std::string dirNew = dirpath + "/" + entry->d_name;
            std::vector<std::string> tempPath = getFilesList(dirNew);
            allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());

        }else {
            //cout << "name = " << entry->d_name << ", len = " << entry->d_reclen << ", entry->d_type = " << (int)entry->d_type << endl;
            std::string name = entry->d_name;
            std::string imgdir = dirpath +"/"+ name;
            //sprintf("%s",imgdir.c_str());
            allPath.push_back(imgdir);
        }

    }
    closedir(dir);
    //system("pause");
    return allPath;
}
