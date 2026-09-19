//
//  KayokoBootLog.h
//  Kayoko
//
//  Temporary boot-stage logger (pure C, no ObjC/Foundation dependency) for
//  freeze diagnosis.
//

#ifndef KAYOKO_BOOT_LOG_H
#define KAYOKO_BOOT_LOG_H

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static inline void KayokoBootLog(const char *stage) {
    int fd = open("/var/mobile/Library/kayoko_boot.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        fd = open("/var/tmp/kayoko_boot.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    if (fd >= 0) {
        if (stage) {
            write(fd, stage, strlen(stage));
        }
        write(fd, "\n", 1);
        close(fd);
    }
}

#endif /* KAYOKO_BOOT_LOG_H */
