#include "csapp.h"
/*
http://www.recipepuppy.com/about/api/

> telnet www.recipepuppy.com 80
> GET /api?q=salad HTTP/1.1
  Host: www.recipepuppy.com
  -- blank line --

- The Tiny web server is going to run our “website.” Tiny can receive HTTP requests and handle them.

- We can send a GET request to Tiny that tells it to open recipe.c, like we told it to run adder.c
by doing GET /cgi-bin/adder?1500&1400 HTTP/1.0. Instead of 1500 and 1400, it would contain the
parameters for the recipe search (like q=salad).

- recipe.c would then be run and it would connect to the recipepuppy API, send the request, and
receive the response data and deal with it
- then Tiny displays everything on browser

**recipepuppy.com (and most APIs) uses HTTP 1.1, NOT HTTP 1.0. So the request looks like this:
	GET /api HTTP/1.1
	Host: www.recipepuppy.com

(requires a host header)

 */

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1=0, n2=0;
    rio_t rio;
    char *host, *port;
    host = "www.recipepuppy.com"  /* just be able to connect to homepage of main website for now */
    port = "80";

    /*
    a client establishes a connection with a server by calling open_clientfd

    PARAMETERS: it establishes a connection with a server running on host 'hostname' and
    listening for connection requesst on port number 'port'

        -int open_clientfd(char *hostname, char *port)
        -return desriptor if OK and -1 on error
    */

    /* establish connection with API */
    int connection = open_clientfd(host, port);

    if (connection == -1) {
      printf("ERROR: connection could not be established.");
    }

    /*
    REQUEST TO TINY:
        GET /cgi-bin/recipe?salad&... HTTP/1.1
        Host: www.recipepuppy.com                --> does tiny know to ignore host header?
        blank line

        OR

        GET /cgi-bin/recipe?salad&... HTTP/1.0
        blank line

    REQUEST TO API:

          GET /api?q=arg1... HTTP/1.1
          Host: www.recipepuppy.com
          blank line

         i.e. --> "GET /api?q=salad HTTP/1.1\r\nHost: www.recipepuppy.com\r\n\r\n"
    */

    /*       */
    Rio_writen(&rio, connection);




    /* ---------------------------------- adder.c ------------------------------------------- */

    /* Extract the two arguments */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
	     p = strchr(buf, '&');
	     *p = '\0';
	     strcpy(arg1, buf);
	     strcpy(arg2, p+1);
	     n1 = atoi(arg1);
	     n2 = atoi(arg2);
    }

    /* Make the response body */
    sprintf(content, "Welcome to add.com: ");
    sprintf(content, "%sTHE Internet addition portal.\r\n<p>", content);
    sprintf(content, "%sThe answer is: %d + %d = %d\r\n<p>",
	    content, n1, n2, n1 + n2);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    /* Generate the HTTP response */
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);

    Close(connection);
    exit(0);
}
/* $end adder */
