/* swo-tracer: listen for and parse ARM SWO trace output
 *
 * Copyright (c) 2013 Andrey Yurovsky
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the author.  The name of the
 * author may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/inotify.h>

#include "frame.h"

const char *usage_str = "usage: %s [-t] <trace_path>\n";
int running = 1;
/*
static void handle_signal(int sig)
{
	if (sig == SIGINT)
		running = 0;
}

static void process_events(int fd, int fd_d)
{
	struct inotify_event ev;

	if (read(fd, &ev, sizeof(ev)) > 0) {
		if (ev.mask & IN_MODIFY)
			read_frame(fd_d);
	}
}

static int check_event(int fd)
{
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	return select(FD_SETSIZE, &rfds, NULL, NULL, NULL);
}
*/
int main(int argc, char **argv)
{
	int fd_d;
	int ret = 0;

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  int portno;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  if (argc < 3) {
    fprintf(stdout,"usage %s hostname port\n", argv[0]);
    exit(0);
  }
  portno = atoi(argv[2]);
  fd_d = socket(AF_INET, SOCK_STREAM, 0);
  if (fd_d < 0) 
    fprintf(stdout, "ERROR opening socket");
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stdout,"ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
      (char *)&serv_addr.sin_addr.s_addr,
      server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(fd_d,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    fprintf(stdout, "ERROR connecting");
//
//	fd_d = open(argv[optind], flags);

  //	if (!(flags & O_TRUNC))
    fprintf(stdout, "yolo\n");
  while ( read_frame(fd_d) > 0) {
    ;
  };
/*
	fd = inotify_init();

	if (fd >= 0 && fd_d >= 0) {
		int wd;
		struct sigaction sa;

		sa.sa_handler = handle_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);

		wd = inotify_add_watch(fd, argv[optind], IN_MODIFY);

		while (running) {
			if (check_event(fd) > 0)
				process_events(fd, fd_d);
			else
				break;
		}

		fprintf(stdout, " Exiting..\n");

		close(fd_d);
		inotify_rm_watch(fd, wd);
	} else {
		fprintf(stdout, "unable to open \"%s\" for reading\n", argv[optind]);
		ret = EXIT_FAILURE;
	}
*/
	return ret;
}
