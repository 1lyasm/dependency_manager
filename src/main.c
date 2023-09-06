#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void err(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int validUrl(char *url) {
    const char proto[] = "http", site[] = "://github.com/";
    const int protoLen = strlen(proto), siteLen = strlen(site);
    int urlLen = strlen(url);
    if (strncmp(url, proto, protoLen) != 0) return 0;
    int cur = protoLen;
    if (url[cur] == 's') ++cur;
    if (strncmp(url + cur, site, siteLen) != 0) return 0;
    cur += siteLen;
    int fWordLen = 0;
    while (cur + fWordLen < urlLen && (isalnum(url[cur + fWordLen]) || url[cur + fWordLen] == '_')) ++fWordLen;
    if (!fWordLen) return 0;
    cur += fWordLen;
    if (cur >= urlLen - 1 || url[cur] != '/') return 0;
    ++cur;
    while (cur < urlLen && (isalnum(url[cur]) || url[cur] == '_')) ++cur;
    if (cur == urlLen)
        return 1;
    else
        return 0;
}

char *getLastW(char *url) {
    char *cur;
    for (cur = &url[strlen(url) - 1]; *cur != '/'; --cur)
        ;
    return cur + 1;
}

void pull() {
    struct stat s;
    int statRes;
    statRes = stat("requirements.txt", &s);
    if (statRes == -1 || S_ISDIR(s.st_mode))
        err("pull: requirements.txt not found");
    system("mkdir -p dependencies");
    FILE *f = fopen("requirements.txt", "r");
    if (!f) err("pull: fopen failed");
    int urlSize = 128;
    char *url = malloc(urlSize * sizeof(char));
    if (!url) err("pull: malloc failed");
    url[urlSize - 1] = 0;
    int bufSize = 128;
    char *buf = malloc(bufSize * sizeof(char));
    if (!buf) err("pull: malloc failed");
    buf[bufSize - 1] = 0;
    while (fgets(url, urlSize, f)) {
        int urlLen = strlen(url);
        if (urlLen == 1) continue;
        url[urlLen - 1] = 0;
        if (!validUrl(url)) {
		fprintf(stderr, "pull: invalid URL: %s\n", url);
		exit(EXIT_FAILURE);
	}
        char *folderName = getLastW(url);
        snprintf(buf, bufSize, "%s/%s", "dependencies", folderName);
        statRes = stat(buf, &s);
        if (statRes == -1) {
            printf("pull: Cloning %s\n", url);
            snprintf(buf, bufSize, "cd dependencies && git clone %s", url);
            system(buf);
        } else {
            printf("pull: Updating %s\n", url);
            snprintf(buf, bufSize, "cd dependencies/%s && git pull",
                     folderName);
            system(buf);
        }
    }
    free(url);
    free(buf);
}

void help() {
    printf(
        "usage: gdep <command>\n\
\nGitHub dependency manager\n\nCommands:\n\
\tpull: update all dependencies to the latest commit\n\
\thelp: print this text\n");
}

#ifndef TEST

int main(int argc, char **argv) {
    if (argc < 2) {
        help();
        exit(EXIT_FAILURE);
    }
    char *cmd = argv[1];
    if (strcmp(cmd, "help") == 0) {
        help();
    } else if (strcmp(cmd, "pull") == 0) {
        pull();
    } else {
        fprintf(stderr, "gdep: '%s' is not a gdep command. See 'gdep help'\n",
                argv[1]);
        exit(EXIT_FAILURE);
    }
    return 0;
}

#endif

