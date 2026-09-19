//
//  KayokoJailbreakPaths.h
//  Kayoko
//
//  Cross-scheme jailbreak path helper.
//
//  - roothide scheme: use the real roothide.h jbroot() so paths map into the
//    bootstrap's private /var/jb prefix.
//  - rootless / other schemes: identity. /var/mobile is a real path there, so
//    returning the input unchanged is correct.
//

#ifndef KAYOKO_JAILBREAK_PATHS_H
#define KAYOKO_JAILBREAK_PATHS_H

#ifdef KAYOKO_SCHEME_ROOTHIDE
#import <roothide.h>
#else
#import <Foundation/Foundation.h>

static inline NSString *jbroot(NSString *path) {
    return path;
}

#endif

#endif /* KAYOKO_JAILBREAK_PATHS_H */
