/*
 * pcapdemo.c --
 *
 *      Demonstrates the usage of the libpcap API to read pcap save
 *      files. The packets are optionally filtered before the packet
 *      handler function is called to print some meta information for
 *      each filtered paket.
 *
 * Copyright (c) 2013 J. Schoenwaelder, Jacobs University Bremen
 * Copyright (c) 2002 J. Schoenwaelder, University of Osnabrueck
 */

#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pcap.h>

static int count = 0;

static void
handler(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *data)
{
    pcap_t *pc = (pcap_t *) user;
    int link;

    link = pcap_datalink(pc);
    count++;
    printf("frame.number=%d frame.time=%lu.%06lus "
	   "frame.cap_len=%d frame.len=%d",
	    count, pkthdr->ts.tv_sec, pkthdr->ts.tv_usec,
	    pkthdr->caplen, pkthdr->len);
    switch (link) {
    case DLT_EN10MB:
	/* decode an ethernet frame in data with the packet length
	   pkthdr->len and a capture length pkthdr->caplen */
	break;
    default:
	fprintf(stderr, "pcapdemo.c: unable to handle data link type %d\n", link);
	break;
    }

    printf("\n");
}

int
main(int argc, char **argv)
{
    char ebuf[PCAP_ERRBUF_SIZE];
    pcap_t *pc;

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "usage: pcapdemo <file> [<filter>]\n");
        exit(1);
    }

    pc = pcap_open_offline(argv[1], ebuf);
    if (! pc) {
        fprintf(stderr, "failed to open file: %s\n", ebuf);
        exit(2);
    }

    if (argc == 3) {
        struct bpf_program bpf;
        if (pcap_compile(pc, &bpf, argv[2], 1, 0) == -1) {
            fprintf(stderr, "failed to compile filter: %s\n", pcap_geterr(pc));
            exit(3);        
        }
        if (pcap_setfilter(pc, &bpf) == -1) {
            fprintf(stderr, "failed to set filter: %s\n", pcap_geterr(pc));
            exit(4);        
        }
    }

    if (pcap_loop(pc, -1, handler, (u_char *) pc) == -1) {
        fprintf(stderr, "failed to process packets: %s\n", pcap_geterr(pc));
        exit(5);
    }

    pcap_close(pc);
    return 0;
}
