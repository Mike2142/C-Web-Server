/**
 * webserver.c -- A webserver written in C
 * 
 * Test with curl (if you don't have it, install it):
 * 
 *    curl -D - http://localhost:3490/
 *    curl -D - http://localhost:3490/d20
 *    curl -D - http://localhost:3490/date
 * 
 * You can also test the above URLs in your browser! They should work!
 * 
 * Posting Data:
 * 
 *    curl -D - -X POST -H 'Content-Type: text/plain' -d 'Hello, sample data!' http://localhost:3490/save
 * 
 * (Posting data is harder to test from a browser.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/file.h>
#include <fcntl.h>
#include <ctype.h>
#include <pthread.h>

#include "net.h"
#include "file.h"
#include "mime.h"
#include "cache.h"

#define PORT "3490"  // the port users will be connecting to

#define SERVER_FILES "./serverfiles"
#define SERVER_ROOT "./serverroot"
#define COMMENTS_FILE "./serverroot/comments.html"

struct handler_args {
    int fd;
    void *cache;
    char *socket;
};

pthread_mutex_t lock;

char* get_time(){
  char output[20];
  time_t rawtime;
  struct tm * timeinfo;
  
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  
  sprintf(output, "[%.2d.%.2d.%d %.2d:%.2d:%.2d]", timeinfo->tm_mday,
          timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
          timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  return output;
}

/**
 * Send an HTTP response
 *
 * header:       "HTTP/1.1 404 NOT FOUND" or "HTTP/1.1 200 OK", etc.
 * content_type: "text/plain", etc.
 * body:         the data to send.
 * 
 * Return the value from the send() function.
 */
int send_response(int fd, char *header, char *content_type, void *body, int content_length)
{
    const int max_response_size = 262144;
    char response[max_response_size];

    // Build HTTP response and store it in response
    sprintf(response, "%s\nDate: date\nConnection: close\nContent-Length: %d\nContent-Type: %s\n\n%s", header, content_length, content_type, body);
    int response_length = strlen(response);

    // Send it all!
    int rv = send(fd, response, response_length, 0);

    if (rv < 0) {
        perror("send");
    }

    return rv;
}


/**
 * Send a /d20 endpoint response
 */
void get_d20(int fd)
{
    // Generate a random number between 0 and 20 inclusive
    char roll_result[50];
    sprintf(roll_result, "<h1>%d</h1><h1>refresh to roll dice</h1>", rand() % 21);
    int result_length = strlen(roll_result);

    send_response(fd, "HTTP/1.1 200 OK", "text/html", roll_result, result_length);
}

void get_ip(int fd, char *ip)
{
    // Generate a random number between 0 and 20 inclusive
    char html[200];
    sprintf(html, "<h1>Your IP is: %s</h1><h1>Nice to meet you!</h1>", ip);
    int html_length = strlen(html);

    send_response(fd, "HTTP/1.1 200 OK", "text/html", html, html_length);
}

/**
 * Send a 404 response
 */
void resp_404(int fd)
{
    char filepath[4096];
    struct file_data *filedata; 
    char *mime_type;

    // Fetch the 404.html file
    snprintf(filepath, sizeof filepath, "%s/404.html", SERVER_FILES);
    filedata = file_load(filepath);

    if (filedata == NULL) {
        // TODO: make this non-fatal
        fprintf(stderr, "cannot find system 404 file\n");
        exit(3);
    }

    mime_type = mime_type_get(filepath);

    send_response(fd, "HTTP/1.1 404 NOT FOUND", mime_type, filedata->data, filedata->size);

    file_free(filedata);
}

/**
 * Read and return a file from disk or cache
 */
void get_file(int fd, struct cache *cache, char *request_path)
{
    struct cache_entry *cacheentry;
    char filepath[4096];
    struct file_data *filedata; 
    char *mime_type;

    int rootflag = strcmp(request_path, "/");
    int idxflag = strcmp(request_path, "/index.html");
    int commentsflag = strcmp(request_path, "/comments.html");

    if (rootflag == 0 || idxflag == 0) {
        request_path = "/cs.html";
    }

    pthread_mutex_lock(&lock);

    // check cache
    cacheentry = cache_get(cache, request_path);
    if (cacheentry && commentsflag != 0) {    
        fprintf(stderr, "cacheentry found: %s\n", cacheentry->path);
        send_response(fd, "HTTP/1.1 200 OK", cacheentry->content_type, cacheentry->content, cacheentry->content_length);
        
        pthread_mutex_unlock(&lock);
        return;
    }
    
    // fetch the file
    snprintf(filepath, sizeof filepath, "%s%s", SERVER_ROOT, request_path);
    filedata = file_load(filepath);

    if (filedata == NULL) {
        // show 404
        fprintf(stderr, "cannot find file %s\n", request_path);
        resp_404(fd);

        pthread_mutex_unlock(&lock);
        return;
    }

    mime_type = mime_type_get(filepath);
    send_response(fd, "HTTP/1.1 200 OK", mime_type, filedata->data, filedata->size);

    // store to cache
    if (commentsflag != 0) {
        cache_put(cache, request_path, mime_type, filedata->data, filedata->size);
        fprintf(stderr, "file cached: %s\n", request_path);
    }
    
    file_free(filedata);
    pthread_mutex_unlock(&lock);
}

void post_save(int fd, char *request, char *body, int bodylen)
{
    char *name;
    char *comment;
    char name_val[bodylen];
    char comment_val[bodylen];
    char string[1300];
    int dlecode = 16;

    if (strstr(body, "name") == NULL || strstr(body, "comment") == NULL) {
        fprintf(stderr, "POST request wrong\n");
        return;
    }

    // strings
    name = strtok(body, "&");
    comment = strtok(NULL, "&");

    // extract values
    sscanf(name, "%*5s%s", name_val);
    sscanf(comment, "%*8s%s", comment_val);

    // strtok() fix, DLE symbol
    int namelen = strlen(name_val);
    int comlen = strlen(comment_val);    
    int secval = (int)comment_val[1];

    if (comlen == 2 && secval == dlecode ) {
        comment_val[1] = '\0';
    }

    if (!namelen || !comlen) {
        return;
    }

    // decode utf to char
    urldecode2(name_val, name_val);
    urldecode2(comment_val, comment_val);

    // result
    snprintf(string, sizeof string, "<p>%s %s: %s</p>\n", get_time(), name_val, comment_val);
    
    pthread_mutex_lock(&lock);
    file_write(COMMENTS_FILE, string);
    pthread_mutex_unlock(&lock);
}

/**
 * Search for the end of the HTTP header
 * 
 * "Newlines" in HTTP can be \r\n (carriage return followed by newline) or \n
 * (newline) or \r (carriage return).
 */
int find_start_of_body(char *request, int reqlen)
{
    fprintf(stderr, "finding start of body\n");
    int sob = 0;

    // find last linebreak
    for (int i = 0; i < reqlen; i++) {
        if (request[i] == '\r' && request[i+1] == '\n') {
            sob = i + 2;
            continue;
        } 
        else if (request[i] == '\r' || request[i] == '\n') {
            sob = i + 1;
            continue;
        } 
    }

    return sob;
}

void close_conn(struct handler_args *args)
{
    int fd = args->fd;
    free(args);
    close(fd);
}

/**
 * Handle HTTP request and send response
 */ // void *arguments;
//void handle_http_request(int fd, struct cache *cache, char *ipaddr)
void handle_http_request(struct handler_args *args)
{
    pthread_cleanup_push(close_conn, args);

    int fd = args->fd;
    struct cache *cache = args->cache;
    char *ipaddr = args->socket;

    int request_buffer_size = 65536; // 64K
    char request[request_buffer_size];
    char http_method[4];
    char request_path[30];

    // Read request
    int bytes_recvd = recv(fd, request, request_buffer_size - 1, 0);

    if (bytes_recvd <= 0) {
        perror("recv");
        return;
    }

    sscanf(request, "%s %s\n", http_method, request_path);
    int req_len = strlen(request_path);
    if (req_len > 50) {
        fprintf(stderr, "request_path is too long: %s\n", request_path);
        return;
    }

    int get_flag = !strcmp(http_method, "GET"); 
    int post0_flag = !strcmp(http_method, "POST");
    int post1_flag = !strcmp(http_method, "POST/");
    int post2_flag = !strcmp(http_method, "POST/index.html"); 
    int post3_flag = !strcmp(http_method, "POST/server.html");

    int d20_flag = !strcmp(request_path, "/d20");
    int myip_flag = !strcmp(request_path, "/myip");
    int index0_flag = !strcmp(request_path, "/");
    int index1_flag = !strcmp(request_path, "/index.html");
    int server_flag = !strcmp(request_path, "/server.html");

    fprintf(stderr, "\nhttp_method: %s\n", http_method);
    fprintf(stderr, "request_path: %s\n", request_path);

    if (d20_flag)  {
        get_d20(fd);
    }
    else if (myip_flag) {
        get_ip(fd, ipaddr);
    }
    else if (get_flag) {
        get_file(fd, cache, request_path);
    }

    if ((index0_flag || index1_flag || server_flag) && (post0_flag || post1_flag || post2_flag || post3_flag)) {
        int sob = find_start_of_body(request, bytes_recvd);
        int bodylen = bytes_recvd - sob;

        if (sob && bodylen < 1000) {
            char body[bodylen];
            strncpy(body, request+sob, bodylen);
            body[bodylen] = '\0';

            post_save(fd, request, body, bodylen);
            get_file(fd, cache, "/comments.html");
        } else {
            fprintf(stderr, "no body in request");
        }
    }

    pthread_cleanup_pop(1);
    return;
}

void urldecode2(char *dst, const char *src)
{
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {
                if (a >= 'a')
                        a -= 'a'-'A';
                if (a >= 'A')
                        a -= ('A' - 10);
                else
                        a -= '0';
                if (b >= 'a')
                        b -= 'a'-'A';
                if (b >= 'A')
                        b -= ('A' - 10);
                else
                        b -= '0';
                *dst++ = 16*a+b;
                src+=3;
        } else if (*src == '+') {
                *dst++ = ' ';
                src++;
        } else {
                *dst++ = *src++;
        }
    }
    *dst++ = '\0';
}

/**
 * Main
 */
int main(void)
{
    int newfd;  // listen on sock_fd, new connection on newfd
    struct sockaddr_storage their_addr; // connector's address information
    char s[INET6_ADDRSTRLEN];

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    struct cache *cache = cache_create(10, 0);

    // Get a listening socket
    int listenfd = get_listener_socket(PORT);

    if (listenfd < 0) {
        fprintf(stderr, "webserver: fatal error getting listening socket\n");
        exit(1);
    }

    printf("webserver: waiting for connections on port %s...\n", PORT);

    // This is the main loop that accepts incoming connections and
    // responds to the request. The main parent process
    // then goes back to waiting for new connections.
    
    while(1) {
        socklen_t sin_size = sizeof their_addr;

        // Parent process will block on the accept() call until someone
        // makes a new connection:
        newfd = accept(listenfd, (struct sockaddr *)&their_addr, &sin_size);
        if (newfd == -1) {
            perror("accept");
            continue;
        }

        // Print out a message that we got the connection
        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("%s server: got connection from %s\n", get_time(), s);
        
        // newfd is a new socket descriptor for the new connection.
        // listenfd is still listening for new connections.

        // prepare http handler
        struct handler_args *hargs = malloc(sizeof(hargs));
        hargs->fd = newfd;
        hargs->cache = cache;
        hargs->socket = s;

        // create thread
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_http_request, hargs);
    }

    // Unreachable code
    return 0;
}

