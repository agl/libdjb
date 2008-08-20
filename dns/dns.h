#ifndef DNS_H
#define DNS_H

#include "stralloc.h"
#include "iopause.h"
#include "taia.h"

#define DNS_C_IN "\0\1"
#define DNS_C_ANY "\0\377"

#define DNS_T_A "\0\1"
#define DNS_T_NS "\0\2"
#define DNS_T_CNAME "\0\5"
#define DNS_T_SOA "\0\6"
#define DNS_T_PTR "\0\14"
#define DNS_T_HINFO "\0\15"
#define DNS_T_MX "\0\17"
#define DNS_T_TXT "\0\20"
#define DNS_T_RP "\0\21"
#define DNS_T_SIG "\0\30"
#define DNS_T_KEY "\0\31"
#define DNS_T_AAAA "\0\34"
#define DNS_T_AXFR "\0\374"
#define DNS_T_ANY "\0\377"

/**
 * struct dns_transmit - the state of a running query
 * @query: a copy of the query *packet* (not string)
 * @packet: a copy of the recved packet
 * @udploop: the number of times we've retransmitted a packet (starts at one
 *   for recursive queries) at a given nameserver
 * @tcpstate:
 *   0 -> UDP mode
 *   1 -> connecting
 *   2 -> connected, writing
 *   3 -> reading reply
 *   4 -> have read one byte
 *   5 -> have read two bytes (packet length), reading rest
 */
struct dns_transmit {
  char *query; /* 0, or dynamically allocated */
  unsigned int querylen;
  char *packet; /* 0, or dynamically allocated */
  unsigned int packetlen;
  int s1; /* 0, or 1 + an open file descriptor */
  int tcpstate;
  unsigned int udploop;
  unsigned int curserver;
  struct taia deadline;
  unsigned int pos;
  const char *servers;
  char localip[4];
  char qtype[2];
} ;

/**
 * dns_random_init - seed PRNG
 * @seed: 128 random bytes
 */
extern void dns_random_init(const char *seed);

/**
 * dns_random - get pseudo-random number
 * @n: result is reduced modulo this
 */
extern unsigned int dns_random(unsigned int n);

extern void dns_sortip(char *,unsigned int);

/**
 * dns_domain_free - free a label list
 */
extern void dns_domain_free(char **);

/**
 * dns_domain_copy - duplicate a label list
 * out: the pointer to the new label list is written here. Also, if *out is
 *   non-NULL, it's freed on success
 * src: the input label set
 * returns: 0 on failure
 */
extern int dns_domain_copy(char **out, const char *src);

/**
 * dns_domain_length - get the sum of the label lengths
 * @s: a pointer to a DNS style label list
 * returns: the length of the label list, inc the final NUL
 */
extern unsigned int dns_domain_length(const char *s);

/**
 * dns_domain_equal - compare two label lists
 * returns: 1 on equality, 0 otherwise
 */
extern int dns_domain_equal(const char *,const char *);

extern int dns_domain_suffix(const char *big, const char *little);

extern unsigned int dns_domain_suffixpos(const char *,const char *);

/**
 * dns_domain_fromdot - convert a domain string to DNS format
 * @out: the result pointer is written here. Also, if *out is non-NULL, *out is
 *   free'ed first
 * @src: the source string
 * @len: the length of @src
 * returns: 1 on success
 *
 * DNS specifies a format where each label is prefixed with an 8-bit length,
 * NUL terminated. This converts from the human form "a.b.com" to this format
 */
extern int dns_domain_fromdot(char **out, const char *src, unsigned int len);

/**
 * dns_domain_todot_cat - append a domain name to a stralloc
 * src: a label list
 * returns: 1 on success
 */
extern int dns_domain_todot_cat(stralloc *dest, const char *src);

/**
 * dns_packet_copy - copy bytes
 * @buf: the source buffer
 * @len: number of bytes in @buf
 * @pos: starting position
 * @out: destination buffer
 * @outlen: number of bytes at @out
 * returns: the number of bytes copied, or 0 if we ran off the end of @buf
 */
extern unsigned int dns_packet_copy(const char *input, unsigned int len,
                                    unsigned int start, char *dest, unsigned int outlen);

/**
 * dns_packet_getname - read a label list from a packet
 * @buf: the packet buffer
 * @len: length of @buf
 * @pos: offset to start at
 * @out: (output) new label list is written to *out. If *out is non-NULL, it's
 *   freed on success
 * returns: number of bytes consumed, or 0 on error
 */
extern unsigned int dns_packet_getname(const char *buf, unsigned int len,
                                       unsigned int pos, char **out);

/**
 * dns_packet_skipname - seek over a DNS name
 * @buf: a buffer
 * @len: number of bytes in @buf
 * @pos: starting position
 * returns: number of bytes in the name at @pos, or 0 on error
 */
extern unsigned int dns_packet_skipname(const char *buf, unsigned int len, unsigned int pos);

extern int dns_transmit_start(struct dns_transmit *,const char *,int,const char *,const char *,const char *);
extern void dns_transmit_free(struct dns_transmit *);
extern void dns_transmit_io(struct dns_transmit *,iopause_fd *,struct taia *);
extern int dns_transmit_get(struct dns_transmit *,const iopause_fd *,const struct taia *);

/**
 * dns_resolvconfip - get the addresses of the nameservers
 * @ips: (output) an array of 4-byte IP addresses, 0 terminated
 * returns: 0 on success, -1 otherwise
 */
extern int dns_resolvconfip(char *ips);

extern int dns_resolve(const char *query, const char *rrtype);
extern struct dns_transmit dns_resolve_tx;

extern int dns_ip4_packet(stralloc *,const char *,unsigned int);
extern int dns_ip4(stralloc *,const stralloc *);
extern int dns_name_packet(stralloc *,const char *,unsigned int);
extern void dns_name4_domain(char *,const char *);
#define DNS_NAME4_DOMAIN 31
extern int dns_name4(stralloc *,const char *);
extern int dns_txt_packet(stralloc *,const char *,unsigned int);
extern int dns_txt(stralloc *,const stralloc *);
extern int dns_mx_packet(stralloc *,const char *,unsigned int);
extern int dns_mx(stralloc *,const stralloc *);

extern int dns_resolvconfrewrite(stralloc *);
extern int dns_ip4_qualify_rules(stralloc *,stralloc *,const stralloc *,const stralloc *);
extern int dns_ip4_qualify(stralloc *,stralloc *,const stralloc *);

#endif
