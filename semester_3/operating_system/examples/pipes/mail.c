/*
 * pipe/mail.c --
 *
 *	This program sends an email by opening a pipe to sendmail.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>

typedef struct inet_mail {
    char *from;
    char *to;
    char *subject;
    char *content;
} inet_mail_t;

static int send(inet_mail_t *mail)
{
    FILE *pipe;
    int rc;

    pipe = popen("sendmail -t", "w");
    if (! pipe) {
	return -1;
    }
    fprintf(pipe, "From: %s\n", mail->from);
    fprintf(pipe, "To: %s\n", mail->to);
    fprintf(pipe, "Subject: %s\n", mail->subject);
    fprintf(pipe, "\n%s", mail->content);
    fflush(pipe);
    rc = ferror(pipe) ? -1 : 0;
    if (pclose(pipe) == -1) {
	rc = -1;
    }
    return rc;
}

int main(void)
{
    inet_mail_t mail = {
	.from = "<me@example.com>",
	.to = "<you@example.com>",
	.subject = "test email - please ignore",
	.content = "Hi,\n\n"
	           "This is a test email. Please excuse.\n\n"
	           "Chears, me.\n",
    };

    if (send(&mail) == -1) {
	fprintf(stderr, "mail: sending failed\n");
	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
