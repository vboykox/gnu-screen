/* Copyright (c) 1991
 *      Juergen Weigert (jnweiger@immd4.informatik.uni-erlangen.de)
 *      Michael Schroeder (mlschroe@immd4.informatik.uni-erlangen.de)
 * Copyright (c) 1987 Oliver Laumann
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see the file COPYING); if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Noteworthy contributors to screen's design and implementation:
 *	Wayne Davison (davison@borland.com)
 *	Patrick Wolfe (pat@kai.com, kailand!pat)
 *	Bart Schaefer (schaefer@cse.ogi.edu)
 *	Nathan Glasser (nathan@brokaw.lcs.mit.edu)
 *	Larry W. Virden (lwv27%cas.BITNET@CUNYVM.CUNY.Edu)
 *	Howard Chu (hyc@hanauma.jpl.nasa.gov)
 *	Tim MacKenzie (tym@dibbler.cs.monash.edu.au)
 *	Markku Jarvinen (mta@{cc,cs,ee}.tut.fi)
 *	Marc Boucher (marc@CAM.ORG)
 *
 ****************************************************************
 * $Id$ FAU
 */


/*
 *		Beginning of User Configuration Section
 *
 * First off, you should decide if you intend to install screen set-uid to
 * root.  This isn't necessary to use screen, but it allows the pseudo-ttys
 * to be set to their proper owner (for security purposes), /etc/utmp to be
 * updated, and /dev/kmem to be accessed to read the load average values.
 *
 * An alternative to installing screen set-uid root is to install it set-gid
 * utmp (with the file /etc/utmp installed to be group-utmp writable) or
 * set-gid kmem (with /dev/kmem set to be group-kmem readable) or some other
 * custom group to give you both.  The final alternative is to omit /etc/utmp
 * updating and the /dev/kmem reading (see the following defines) and simply
 * run screen as a regular program -- its major functions will be unaffected.
 */


/*
 * Define POSIX if your system supports IEEE Std 1003.1-1988 (POSIX).
 */
#ifndef POSIX
# define POSIX
#endif

/*
 * Define BSDJOBS if you have BSD-style job control (both process
 * groups and a tty that deals correctly with them).
 */
#define BSDJOBS

/*
 * Define TERMIO if you have struct termio instead of struct sgttyb.
 * This is usually the case for SVID systems, where BSD uses sgttyb.
 * POSIX systems should define this anyway, even though they use
 * struct termios.
 */
#define TERMIO

/*
 * Define TERMINFO if your machine emulates the termcap routines
 * with the terminfo database.
 * Thus the .screenrc file is parsed for
 * the command 'terminfo' and not 'termcap'.
 */
#undef TERMINFO

/*
 * Define SYSV if your machine is SYSV complient (Sys V, HPUX, A/UX)
 */
#undef SYSV

/*
 * Define SIGVOID if your signal handlers return void.  On older
 * systems, signal returns int, but on newer ones, it returns void.
 */
#define SIGVOID 

/*
 * Define DIRENT if your system has <dirent.h> instead of <sys/dir.h>
 */
#define DIRENT

/*
 * If screen is going to be installed set-uid root, you MUST define SUIDROOT.
 */
#undef SUIDROOT

/*
 * If screen is installed with permissions to update /etc/utmp (such as if
 * it is installed set-uid root), define UTMPOK.  Set LOGINDEFAULT to one (1)
 * if you want entries added to /etc/utmp by default, else set it to zero (0).
 */
#undef UTMPOK
#define LOGINDEFAULT	0

/*
 * If your system has getutent(), pututline(), etc. to write to the
 * utmp file, define GETUTENT.
 */
#undef GETUTENT

/*
 * Define UTHOST if the utmp file has a host field.
 */
#undef UTHOST

/*
 * If UTMPOK is defined and your system (incorrectly) counts logins by
 * counting non-null entries in /etc/utmp (instead of counting non-null
 * entries with no hostname that are not on a pseudo tty), define USRLIMIT
 * to have screen put an upper-limit on the number of entries to write
 * into /etc/utmp.  This helps to keep you from exceeding a limited-user
 * license.
 */
#undef USRLIMIT

/*
 * If screen is NOT installed set-uid root, screen can provide tty security
 * by exclusively locking the ptys.  While this keeps other users from
 * opening your ptys, it also keeps your own subprocesses from being able
 * to open /dev/tty.  Define LOCKPTY to add this exclusive locking.
 */
#undef LOCKPTY

/*
 * If your system does not have the calls setreuid() and setregid(), define
 * NOREUID to force screen to use a forked process to safely create output
 * files without retaining any special privileges.  (Output logging will be
 * disabled, however.)
 */
#undef NOREUID

/*
 * If you want the "time" command to display the current load average
 * you must install screen with the needed privileges to read /dev/kmem
 * and have a load average format that screen understands.  We handle the
 * following formats:  3 doubles (BSD), 3 longs (sun), and 4 longs (alliant).
 */
#define  LOADAV_3DOUBLES
#undef LOADAV_3LONGS
#undef  LOADAV_4LONGS

/*
 * If your system has the new format /etc/ttys (like 4.3 BSD) and the
 * getttyent(3) library functions, define GETTTYENT.
 */
#define GETTTYENT

/*
 * If your version of NFS supports named sockets and you install screen
 * suid root, you may need to define NFS_HACK for screen to be able to
 * open the sockets.
 */
#undef NFS_HACK

/*
 * By default screen will create a directory named ".screen" in the user's
 * HOME directory to contain the named sockets.  If this causes you problems
 * (e.g. some user's HOME directories are NFS-mounted and don't support
 * named sockets) you can have screen create the socket directories in a
 * common subdirectory, such as /tmp or /usr/tmp.  It makes things a little
 * more secure if you choose a directory where the "sticky" bit is on, but
 * this isn't required.  Screen will name the subdirectories "S-$USER"
 * (e.g /tmp/S-davison).
 * Do not define TMPTEST unless it's for debugging purpose.
 * If you want to have your socket directory in "/tmp/screens" then
 * define LOCALSOCKDIR and change the definition of SOCKDIR below.
 */
#undef LOCALSOCKDIR
#undef TMPTEST

#ifdef LOCALSOCKDIR
# ifndef TMPTEST
#  define SOCKDIR "/local/screens"
# else
#  define SOCKDIR "/tmp/screens"
# endif
#endif

/*
 * Define USEBCOPY if the bcopy() from your system's C library supports the
 * overlapping of source and destination blocks.  When undefined, screen
 * uses its own (probably slower) version of bcopy().
 */
#undef USEBCOPY

/*
 * If you'd rather see the status line on the first line of your
 * terminal rather than the last, define TOPSTAT.
 */
#undef TOPSTAT

/*
 * If your system has vsprintf() and requires the use of the macros in
 * "varargs.h" to use functions with variable arguments,
 * define USEVARARGS.
 */
#undef USEVARARGS

/*
 * Define this if your system supports named pipes.
 */
#define NAMEDPIPE

/*
 * here come the erlangen extensions to screen:
 * define LOCK if you want to use a lock program for a screenlock.
 * define PASSWORD for secure reattach of your screen.
 * define COPY_PASTE to use the famous hacker's treasure zoo.
 * define POW_DETACH to have a detach_and_logout key.
 * define REMOTE_DETACH (-d option) to move screen between terminals.
 * (jw)
 */
#define LOCK
#define PASSWORD
#define COPY_PASTE
#define REMOTE_DETACH
#define POW_DETACH

/*
 * As error messages are mostly meaningless to the user, we
 * try to throw out phrases that are somewhat more familiar
 * to ...well, at least familiar to us NetHack players.
 */
#define NETHACK

/*
 * and another sneaky feature: screen sources two startup files.
 * first a global file with a path specified here, second
 * your local $HOME/.screenrc
 * Don't define this, if you don't want it.
 */
#define ETCSCREENRC "/users/en-eeen/martind/.../global.screenrc"

/*
 * Set if you want to suppress the intial display of the copyright notice 
 */
#define SUPPRESS_CR

/*
 * Set if you want it to rename the background part of the process in the 
 * following manner.  If argv[0] == screen then renames it SCREEN
 * and if some other name then just changes first letter to 'S'.  Useful if 
 * you need to distinguish the two screen processes.
 */
#undef RENAME_PROCESS

/*
 *	End of User Configuration Section
 */


#define NEEDSETENV
