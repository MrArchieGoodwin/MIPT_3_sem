#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
 
int symlinks_count(const char* path, int* answer) {
    DIR *current = opendir(path);
    if (current == NULL) {
        return -1;
    }
    int count = 0;
    struct dirent* entry;
    while (entry = readdir(current)) {
        if (entry->d_type == DT_LNK) {
            count++;
        }
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            fprintf(stdout, "%s\n", entry->d_name);
            symlinks_count(entry->d_name, answer);
        }
    }
    closedir(current);
    if (*answer < count) {
        *answer = count;
    }
    return 0;
} 
    
int main(int argc, char* argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s <DIRECTORY>\n", argv[0]);
        return 1;
    }
    int result = 0;
    symlinks_count(argc == 1 ? "." : argv[1], &result);
    fprintf(stdout, "%d\n", result);
    return 0;
}
