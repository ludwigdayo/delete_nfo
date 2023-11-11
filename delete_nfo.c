#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void delete_nfo_files(const char *dir_path) {
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(dir_path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // 忽略 "." 和 ".."
            if (ent->d_name[0] != '.' || (ent->d_name[1] != '\0' && ent->d_name[1] != '.')) {

                char file_path[1024];
                snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, ent->d_name);

                if (ent->d_type == DT_DIR) {
                    delete_nfo_files(file_path);
                } else {
                    // 如果是 .nfo 文件，删除之
                    if (strstr(ent->d_name, ".nfo") != NULL) {
                        if (remove(file_path) == 0) {
                            printf("已删除文件: %s\n", file_path);
                        } else {
                            fprintf(stderr, "无法删除文件: %s\n", file_path);
                        }
                    }
                }
            }
        }
        closedir(dir);
    } else {
        perror("无法打开目录");
        exit(EXIT_FAILURE);
    }
}

void print_usage(const char *program_name) {
    printf("用法: %s [目录路径]\n", program_name);
    printf("删除指定目录及其子目录中的所有 .nfo 文件。\n");
}

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_usage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    const char *directory_path = (argc > 1) ? argv[1] : ".";

    delete_nfo_files(directory_path);

    return 0;
}

