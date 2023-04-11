#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define PER_FROMAT "%c%c%c%c%c%c%c%c%c"

void 
print_file_info(const char *file) {
    struct stat file_stat;
    if (stat(file, &file_stat) == -1) {
        perror("Error");
        return;
    }

    printf("Inode: %lu\n", (unsigned long)file_stat.st_ino);
    printf("Size: %ld\n", (long)file_stat.st_size);

    char permissions[11] = {0};
    snprintf(permissions, 
             sizeof(permissions), 
             PER_FROMAT,
             (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
             (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
             (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
             (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
             (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
             (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
             (file_stat.st_mode & S_IROTH) ? 'r' : '-',
             (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
             (file_stat.st_mode & S_IXOTH) ? 'x' : '-');
             
    printf("Permissions: %s\n", permissions);
}

void 
create_hard_link(const char *src, const char *dest) {
    if (link(src, dest) == -1) {
        perror("Error");
    }
}

void 
create_sym_link(const char *src, const char *dest) {
    if (symlink(src, dest) == -1) {
        perror("Error");
    }
}

void 
remove_file(const char *file) {
    struct stat file_stat;
    if (stat(file, &file_stat) == -1) {
        perror("Error: No such file or directory\n");
        return;
    }

    if (S_ISDIR(file_stat.st_mode)) {
        fprintf(stderr, "Error: Cannot remove directory\n");
    } else {
        if (remove(file) == -1) {
            perror("Error");
        }
    }
}

int 
main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./files <action> <args>...\n");
        return EXIT_FAILURE;
    }

    const char *action = argv[1];

    if (strcmp(action, "info") == 0) {
        if (argc != 3) {
            printf("Usage: ./files info <file>\n");
            return EXIT_FAILURE;
        }
        print_file_info(argv[2]);
    } else if (strcmp(action, "link") == 0) {
        if (argc != 4) {
            printf("Usage: ./files link <src> <dest>\n");
            return EXIT_FAILURE;
        }
        create_hard_link(argv[2], argv[3]);
    } else if (strcmp(action, "symlink") == 0) {
        if (argc != 4) {
            printf("Usage: ./files symlink <src> <dest>\n");
            return EXIT_FAILURE;
        }
        create_sym_link(argv[2], argv[3]);
    } else if (strcmp(action, "rm") == 0) {
        if (argc != 3) {
            printf("Usage: ./files rm <file>\n");
            return EXIT_FAILURE;
        }
        remove_file(argv[2]);
    } else {
        printf("Unkown command out of <info, link, symlink, rm>: %s\n", action);
    }

    return EXIT_SUCCESS;
}
