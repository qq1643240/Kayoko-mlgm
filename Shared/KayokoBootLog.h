// -*- coding: utf-8 -*-
//  KayokoBootLog.h
//  Kayoko
//
//  Temporary boot-stage file logger for freeze diagnosis.
//

#import <Foundation/Foundation.h>

static inline void KayokoBootLog(NSString *stage) {
    static NSString *path = nil;
    static dispatch_once_t once;
    dispatch_once(&once, ^{
      path = @"/var/mobile/Library/kayoko_boot.log";
    });
    static NSFileHandle *handle = nil;
    @synchronized(path) {
      if (!handle) {
          if (![[NSFileManager defaultManager] fileExistsAtPath:path]) {
              [@"" writeToFile:path atomically:YES encoding:NSUTF8StringEncoding error:nil];
          }
          handle = [NSFileHandle fileHandleForWritingAtPath:path];
          if (handle) {
              [handle seekToEndOfFile];
          }
      }
      if (handle) {
          NSString *line = [NSString stringWithFormat:@"%@\n", stage];
          [handle writeData:[line dataUsingEncoding:NSUTF8StringEncoding]];
      }
    }
}
