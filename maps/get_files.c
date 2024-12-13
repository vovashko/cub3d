#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void list_files(const char *path)
{
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    printf("Files in directory '%s':\n", path);
    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) { // Only list regular files
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
}

int main()
{
    const char *path = "good";
    list_files(path);
    return 0;
}